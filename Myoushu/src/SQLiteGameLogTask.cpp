/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morné Chamberlain & Stellenbosch University

The ASD Assist VE Platform is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (with the added restriction
that this work and any derivative works may only be used for non-commercial purposes)
as published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASD Assist VE Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file SQLiteGameLogTask.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include <string>
#include <sstream>

#include "SQLiteGameLogTask.h"
#include "SQLiteGameLogManager.h"
#include "NotificationManager.h"
#include "Config.h"
#include "EngineLog.h"
#include "Value.h"

namespace Myoushu
{
	// Global functions
	int sqliteCallback(void *pGameLogEntity, int argc, char **argv, char **colNames)
	{
		std::list<Value> values;
		GameLogEntity *pEntity;

		if (pGameLogEntity == NULL)
		{
			return SQLITE_OK;
		}

		// If we received an empty result set, do nothing
		if (argc == 0)
		{
			return SQLITE_OK;
		}

		pEntity = reinterpret_cast<GameLogEntity*>(pGameLogEntity);

		// Construct a list of values and add this row as entry to pEntity
		for (int i = 0; i < argc; i++)
		{
			Value val;
			val.set(std::string(argv[i]));
			values.push_back(val);
		}

		// Add this row as an entry to the entity. Any existing entry with the same primary key will
		// be replaced.
		GameLogEntityEntry *pEntry = pEntity->addEntry(values);
		if (pEntry != NULL)
		{
			// We do not want the changed flag to be true, since we now know this entry is up to date with the
			// with the one on secondary storage, and any changes we may have made before reading would be lost anyway
			pEntry->setChanged(false);
		}

		return SQLITE_OK;
	}

	int sqliteTableInfoCallback(/*std::list<std::pair<std::string, bool> >*/void *pList, int argc, char **argv, char **colNames)
	{
		std::list<std::pair<std::string, bool> >* pListOfColNames;
		bool pKey;

		if (pList == NULL)
		{
			return SQLITE_OK;
		}

		pKey = false;

		pListOfColNames = reinterpret_cast<std::list<std::pair<std::string, bool> > * >(pList);
		// for a PRAGMA table_info query, the second column returns the name of a column, the last column says whether the table column is a primary key
		if (strcmp(argv[argc - 1], "0") != 0)
		{
			pKey = true;
		}
		pListOfColNames->push_back(make_pair(std::string(argv[1]), pKey));

		return SQLITE_OK;
	}

	CLASS_NAME(SQLiteGameLogTask, "Myoushu::SQLiteGameLogTask");

	const std::string SQLiteGameLogTask::SQLITE_DB_PATH_KEY = "gamelog.sqlitePath";

	const std::string SQLiteGameLogTask::DEFAULT_SQLITE_DB_PATH = "sqlite.db";

	SQLiteGameLogTask::SQLiteGameLogTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit)
		: Task(name, priority, executionInterval, iterationLimit), mMaxNumberOfMessagesPerIteration(0)
	{
	}

	SQLiteGameLogTask::SQLiteGameLogTask() : Task(0)
	{
	}

	SQLiteGameLogTask::~SQLiteGameLogTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		NotificationManager::getSingletonPtr()->removeQueue(reinterpret_cast<memUInt>(this));
	}

	void SQLiteGameLogTask::init() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Initializing SQLiteGameLogTask.");

		NotificationManager::getSingletonPtr()->addObserver(this, &SQLiteGameLogTask::receiveGameLogMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_INITIALIZED;
	}

	void SQLiteGameLogTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void SQLiteGameLogTask::execute(unsigned long timeDelta)
	{
		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		// Tell the NotificationManager to deliver all queued messages for this task
		NotificationManager::getSingletonPtr()->dispatchQueuedNotifications((memUInt) this);
	}

	void SQLiteGameLogTask::kill()
	{
		NotificationManager::getSingleton().removeObserver(this, &SQLiteGameLogTask::receiveGameLogMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	int SQLiteGameLogTask::checkIfTableExists(sqlite3 *db, const std::string& name)
	{
		std::stringstream checkTableStringStream;
		int result;
		char *pErrMsg;
		int nRows;
		int nCols;
		char **pResultTable;

		// Check if the table already exists for the entity, create it if it does not exist
		checkTableStringStream << "SELECT name FROM sqlite_master WHERE type='table' AND name='" << name << "'";
		result = sqlite3_get_table(db, checkTableStringStream.str().c_str(), &pResultTable, &nRows, &nCols, &pErrMsg);
		sqlite3_free_table(pResultTable);
		if (result != SQLITE_OK)
		{
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::checkIfTableExists(): error while verifying table existence: " << pErrMsg);
			sqlite3_free(pErrMsg);

			// Return a negative number if an error occurred
			return -1;
		}

		// Return the number of rows
		return nRows;
	}

	int SQLiteGameLogTask::checkIfRowExists(sqlite3 *db, const std::string& tableName, const std::string& whereClause)
	{
		std::stringstream sqlStatement;
		int result;
		char *pErrMsg;
		int nRows;
		int nCols;
		char **pResultTable;

		sqlStatement << "SELECT * FROM " << tableName << " " << whereClause;
		result = sqlite3_get_table(db, sqlStatement.str().c_str(), &pResultTable, &nRows, &nCols, &pErrMsg);
		sqlite3_free_table(pResultTable);
		if (result != SQLITE_OK)
		{
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::checkIfRowExists(): error while verifying row existence: " << pErrMsg);
			sqlite3_free(pErrMsg);

			// Return a negative number if an error occurred
			return -1;
		}

		// Return the number of rows
		return nRows;
	}

	int SQLiteGameLogTask::commitEntity(sqlite3 *db, const GameLogEntity *pEntity) throw (Exception)
	{
		GameLogEntity::ConstIterator iter;
		GameLogEntityEntry::AttributeNamesVector::const_iterator columnNamesIter;
		std::list<std::string>::const_iterator keyAttributesIter;
		std::stringstream createTableStringStream;
		int result;
		char *pErrMsg;

		// Check that pEntity is not NULL
		if (pEntity == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SQLiteGameLogTask::commitEntity(): pEntity is NULL.");
		}

		// Check if the table already exists for the entity, create it if it does not exist
		result = checkIfTableExists(db, pEntity->getName());

		// If result > 0 then the table exists, otherwise it does not
		// If the table exists, we have to get a list of its column names and which of these columns are part of the primary key.
		if (result < 0)
		{
			// an error occurred
			return result;
		}
		else if (result == 0)
		{
			createTableStringStream << "CREATE TABLE " << pEntity->getName() << " (" << std::endl;
			// Insert the column names and types into the string
			for (columnNamesIter = pEntity->attributeNamesBegin(); columnNamesIter != pEntity->attributeNamesEnd(); ++columnNamesIter)
			{
				if (columnNamesIter != pEntity->attributeNamesBegin())
				{
					createTableStringStream << ", ";
				}
				createTableStringStream << *columnNamesIter << " varchar(255)";
			}
			// Add the primary key CONSTRAINT
			createTableStringStream << ", CONSTRAINT pKey PRIMARY KEY (";
			for (keyAttributesIter = pEntity->keyAttributesBegin(); keyAttributesIter != pEntity->keyAttributesEnd(); ++keyAttributesIter)
			{
				if (keyAttributesIter != pEntity->keyAttributesBegin())
				{
					createTableStringStream << ", ";
				}
				createTableStringStream << *keyAttributesIter;
			}

			createTableStringStream << ") )";

			// Execute the query
			result = sqlite3_exec(db, createTableStringStream.str().c_str(), NULL, NULL, &pErrMsg);
			// If an error is encountered, log it and exit the function
			if (result != SQLITE_OK)
			{
				LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::commitEntity(): error whilst ensuring the existence of the table " << pEntity->getName() << ": " << pErrMsg);
				sqlite3_free(pErrMsg);

				return result;
			}
		}

		// Commit each changed entry
		for (iter = pEntity->begin(); iter != pEntity->end(); ++iter)
		{
			const GameLogEntityEntry *pEntry = iter->second;

			if (pEntry->getChanged())
			{
				commitEntry(db, pEntity, pEntry);
			}
		}

		return SQLITE_OK;
	}

	int SQLiteGameLogTask::commitEntry(sqlite3 *db, const GameLogEntity *pEntity, const GameLogEntityEntry *pEntry) throw (Exception)
	{
		std::stringstream sqlStatementStringStream;
		std::stringstream whereClauseStringStream;
		std::stringstream insertValuesStringStream;
		std::stringstream updateValuesStringStream;
		std::list<std::string>::const_iterator keyAttributesIter;
		GameLogEntityEntry::AttributeNamesVector::const_iterator columnNamesIter;
		char *pErrMsg;
		int result;

		if ((pEntry == NULL) || (pEntity == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "SQLiteGameLogTask::commitEntry(): pEntity or pEntry is NULL.");
		}

		// Construct the WHERE clause with the primary keys
		whereClauseStringStream << "where ";
		for (keyAttributesIter = pEntity->keyAttributesBegin(); keyAttributesIter != pEntity->keyAttributesEnd(); ++keyAttributesIter)
		{
			const std::string& columnName = *keyAttributesIter;

			if (keyAttributesIter != pEntity->keyAttributesBegin())
			{
				whereClauseStringStream << " AND ";
			}
			whereClauseStringStream << columnName << " = '" << pEntry->getValue(columnName).toString() << "'";
		}

		// Construct the column=value and (value1, value2, ... ) etc clauses for update and insert respectively
		updateValuesStringStream << "set ";
		insertValuesStringStream << "values (";
		for (columnNamesIter = pEntity->attributeNamesBegin(); columnNamesIter != pEntity->attributeNamesEnd(); ++columnNamesIter)
		{
			const std::string& columnName = *columnNamesIter;
			const std::string& valueStr = pEntry->getValue(columnName).toString();

			if (columnNamesIter != pEntity->attributeNamesBegin())
			{
				updateValuesStringStream << ", ";
				insertValuesStringStream << ", ";
			}
			
			updateValuesStringStream << columnName << " = '" << valueStr << "'";
			insertValuesStringStream << "'" << valueStr << "'";
		}
		insertValuesStringStream << ")";

		// Check whether the row with this primary key already exists, if it does it is updated, if it
		// does not a new row is inserted.
		result = checkIfRowExists(db, pEntity->getName(), whereClauseStringStream.str());
		// if result < 0, an error occurred

		// Construct the SQL statement
		if (result < 0)
		{
			// if result < 0, an error occurred
			return result;
		}
		else if (result == 0)
		{
			// Row doesn't exist, insert
			sqlStatementStringStream << "INSERT INTO " << pEntity->getName() << " " << insertValuesStringStream.str();
		}
		else if (result > 0)
		{
			// Row exists, update
			sqlStatementStringStream << "UPDATE " << pEntity->getName() << " " << updateValuesStringStream.str()
			<< " " << whereClauseStringStream.str();
		}

		result = sqlite3_exec(db, sqlStatementStringStream.str().c_str(), NULL, NULL, &pErrMsg);
		if (result != SQLITE_OK)
		{
			// An error occurred during execution of the SQL statement
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::commitEntry(): error during exec of SQL statement: " << pErrMsg << " : statement: " << sqlStatementStringStream.str());
			sqlite3_free(pErrMsg);
		}

		// Mark the entry as not changed.
		const_cast<GameLogEntityEntry*>(pEntry)->setChanged(false);

		return SQLITE_OK;
	}

	int SQLiteGameLogTask::updateEntity(sqlite3 *db, GameLogEntity *pEntity) throw (Exception)
	{
		GameLogEntity::Iterator iter;

		if (pEntity == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SQLiteGameLogTask::commitEntity(): pEntity is NULL.");
		}

		// Commit each changed entry
		for (iter = pEntity->begin(); iter != pEntity->end(); ++iter)
		{
			GameLogEntityEntry *pEntry = iter->second;

			updateEntry(db, pEntity, pEntry);
		}

		return SQLITE_OK;
	}

	int SQLiteGameLogTask::updateEntry(sqlite3 *db, GameLogEntity *pEntity, GameLogEntityEntry *pEntry) throw (Exception)
	{
		std::stringstream whereClauseStringStream;
		std::list<std::string>::const_iterator keyAttributesIter;
		std::stringstream sqlStatementStringStream;
		int result;
		char *pErrMsg;

		// Construct the WHERE clause with the primary keys
		whereClauseStringStream << "where ";
		for (keyAttributesIter = pEntity->keyAttributesBegin(); keyAttributesIter != pEntity->keyAttributesEnd(); ++keyAttributesIter)
		{
			const std::string& columnName = *keyAttributesIter;

			if (keyAttributesIter != pEntity->keyAttributesBegin())
			{
				whereClauseStringStream << " AND ";
			}
			whereClauseStringStream << columnName << " = '" << pEntry->getValue(columnName).toString() << "'";
		}

		sqlStatementStringStream << "SELECT * FROM " << pEntity->getName() << " " << whereClauseStringStream.str(); 

		result = sqlite3_exec(db, sqlStatementStringStream.str().c_str(), sqliteCallback, reinterpret_cast<void*>(pEntity), &pErrMsg);
		if (result != SQLITE_OK)
		{
			// An error occurred during execution of the SQL statement
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::commitEntry(): error during exec of SQL statement: " << pErrMsg);
			sqlite3_free(pErrMsg);

			return result;
		}

		return SQLITE_OK;
	}

	int SQLiteGameLogTask::readEntity(sqlite3 *db, const std::string& entityName) throw (Exception)
	{
		std::stringstream sqlStatementStringStream;
		int result;
		char *pErrMsg;
		std::list<std::pair<std::string, bool> > columnNames;
		std::list<std::pair<std::string, bool> >::iterator iter;
		std::vector<std::string> attributeNames;
		GameLogEntity *pEntity;

		// Check that the table exists
		result = checkIfTableExists(db, entityName);

		// If nRows > 0 then the table exists, otherwise it does not
		// If the table exists, we have to get a list of its column names and which of these columns are part of the primary key.
		if (result < 0)
		{
			// Error verifying table existence
			return result;
		}
		else if (result == 0)
		{
			// Table does not exist, can not read it
			return SQLITE_OK;
		}

		// We need to get the column names and primary key for the table
		sqlStatementStringStream << "PRAGMA table_info(" << entityName << ")";
		result = sqlite3_exec(db, sqlStatementStringStream.str().c_str(), sqliteTableInfoCallback, reinterpret_cast<void*>(&columnNames), &pErrMsg);
		if (result != SQLITE_OK)
		{
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::readEntity(): error while getting table column names and primary key: " << pErrMsg);
			sqlite3_free(pErrMsg);

			return result;
		}

		// Now that we have the column names and primary key, we need to create a list of attribute names for the new GameLogEntity we are creating
		for (iter = columnNames.begin(); iter != columnNames.end(); ++iter)
		{
			// Add the column name to the vector
			attributeNames.push_back(iter->first);
		}

		pEntity = SQLiteGameLogManager::getSingleton().makeEntity(entityName, attributeNames);
		LOG(EngineLog::LM_INFO_ENGINE, "Entity made: " << pEntity->getName());
		// Set the primary key attributes for the entity
		for (iter = columnNames.begin(); iter != columnNames.end(); ++iter)
		{
			if (iter->second == true)
			{
				pEntity->addAttributeToPrimaryKey(iter->first);
			}
		}

		sqlStatementStringStream.str("");
		sqlStatementStringStream << "SELECT * FROM " << entityName;
		result = sqlite3_exec(db, sqlStatementStringStream.str().c_str(), sqliteCallback, reinterpret_cast<void*>(pEntity), &pErrMsg);
		if (result != SQLITE_OK)
		{
			// An error occurred during execution of the SQL statement
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::commitEntry(): error during exec of SQL statement: " << pErrMsg);
			sqlite3_free(pErrMsg);

			return result;
		}

		return SQLITE_OK;
	}

	int SQLiteGameLogTask::readEntry(sqlite3 *db, GameLogEntity *pEntity, std::list<std::string> primaryKeyValues) throw (Exception)
	{
		std::stringstream whereClauseStringStream;
		std::list<std::string>::const_iterator keyAttributesIter;
		std::list<std::string>::const_iterator primaryKeyValuesIter;
		std::stringstream sqlStatementStringStream;
		int result;
		char *pErrMsg;

		// Construct the WHERE clause with the primary keys
		whereClauseStringStream << "WHERE ";
		primaryKeyValuesIter = primaryKeyValues.begin();
		for (keyAttributesIter = pEntity->keyAttributesBegin(); (keyAttributesIter != pEntity->keyAttributesEnd()) && (primaryKeyValuesIter != primaryKeyValues.end()); ++keyAttributesIter)
		{
			const std::string& columnName = *keyAttributesIter;

			if (keyAttributesIter != pEntity->keyAttributesBegin())
			{
				whereClauseStringStream << " AND ";
			}
			whereClauseStringStream << columnName << " = '" << *primaryKeyValuesIter << "'";
			primaryKeyValuesIter++;
		}

		sqlStatementStringStream << "SELECT * FROM " << pEntity->getName() << " " << whereClauseStringStream.str(); 

		result = sqlite3_exec(db, sqlStatementStringStream.str().c_str(), sqliteCallback, reinterpret_cast<void*>(pEntity), &pErrMsg);
		if (result != SQLITE_OK)
		{
			// An error occurred during execution of the SQL statement
			LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::commitEntry(): error during exec of SQL statement: " << pErrMsg);
			sqlite3_free(pErrMsg);

			return result;
		}

		return SQLITE_OK;
	}

	void SQLiteGameLogTask::receiveGameLogMessage(const Poco::AutoPtr<GameLogMessage>& pMessage)
	{
		sqlite3 *db;
		int result;
		// Get the path to the database
		std::string pathToDB = Config::getSingletonPtr()->getString(SQLITE_DB_PATH_KEY, DEFAULT_SQLITE_DB_PATH);

		// Check that the message is not NULL, if it is, log a warning and return.
		if (pMessage.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "SQLiteGameLogTask::receiveGameLogMessage(): received message is NULL, ignoring...");
			return;
		}

		if ((pMessage->getMessageType() == GameLogMessage::GLM_COMMIT_END) || (pMessage->getMessageType() == GameLogMessage::GLM_UPDATE_END))
		{
			if (pMessage->getMessageType() == GameLogMessage::GLM_COMMIT_END)
			{
				SQLiteGameLogManager::getSingleton().commitCompleted();
			}
			else
			{
				SQLiteGameLogManager::getSingleton().updateCompleted();
			}
		}
		else
		{
			// Open a connection
			result = sqlite3_open(pathToDB.c_str(), &db);
			if (result != SQLITE_OK)
			{
				LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::receiveGameLogMessage(): error connecting to SQLite db: " << sqlite3_errmsg(db));
				sqlite3_close(db);

				return;
			}

			// Process the message
			try
			{
				switch (pMessage->getMessageType())
				{
					case GameLogMessage::GLM_COMMIT_ENTITY:
						commitEntity(db, pMessage->getGameLogEntity());
						static_cast<SQLiteGameLogEntity*>(pMessage->getGameLogEntity())->commitCompleted();
						break;
					case GameLogMessage::GLM_UPDATE_ENTITY:
						updateEntity(db, pMessage->getGameLogEntity());
						static_cast<SQLiteGameLogEntity*>(pMessage->getGameLogEntity())->updateCompleted();
						break;
					case GameLogMessage::GLM_READ_ENTITY:
						readEntity(db, pMessage->getEntityName());
						SQLiteGameLogManager::getSingleton().readCompleted(pMessage->getActionID());
						break;
					case GameLogMessage::GLM_COMMIT_ENTRY:
						commitEntry(db, pMessage->getGameLogEntity(), pMessage->getGameLogEntityEntry());
						break;
					case GameLogMessage::GLM_UPDATE_ENTRY:
						updateEntry(db, pMessage->getGameLogEntity(), pMessage->getGameLogEntityEntry());
						break;
					case GameLogMessage::GLM_READ_ENTRY:
						readEntry(db, pMessage->getGameLogEntity(), pMessage->getEntryPrimaryKey());
						static_cast<SQLiteGameLogEntity*>(pMessage->getGameLogEntity())->readCompleted(pMessage->getActionID());
						break;
					case GameLogMessage::GLM_COMMIT_END:
					case GameLogMessage::GLM_UPDATE_END:
					case GameLogMessage::GLM_UNKNOWN:
					default:
						LOG(EngineLog::LM_WARNING, "SQLiteGameLogTask::receiveGameLogMessage(): tried to handle unknown/unsupported message type: " << pMessage->getMessageType());
						break;
				} // switch
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_ERROR, "SQLiteGameLogTask::receiveGameLogMessage(): caught exception while processing message: " << e.getMsg());
			}

			// Close the connection
			sqlite3_close(db);
		}
	}

} // Myoushu


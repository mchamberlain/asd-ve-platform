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
 * @file SQLiteGameLogTask.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_SQLITE_GAME_LOG_TASK_H
#define MYOUSHU_SQLITE_GAME_LOG_TASK_H

#include <string>
#include <list>

#include "sqlite3.h"

#include "Poco/AutoPtr.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Task.h"
#include "Exception.h"
#include "SQLiteGameLogEntity.h"
#include "GameLogMessage.h"

namespace Myoushu
{

	/**
	 * This Task manages reads and writes to a SQLite database for the GameLog system. See SQLiteGameLogManager.
	 */
	class MYOUSHU_API SQLiteGameLogTask : public NamedObject<SQLiteGameLogTask>, public Task
	{
		public:
			/** The key used to fetch the path to the SQLite database, stored in the Config singleton. */
			static const std::string SQLITE_DB_PATH_KEY;

			/** The default path to the sqlite database. */
			static const std::string DEFAULT_SQLITE_DB_PATH;

			/**
			 * Constructor.
			 * @param priority The priority of the Task.
			 * @param name The name of the Task.
			 * @param executionInterval The amount of time, in microseconds, between executions of this Task. 
			 *							To execute in every frame use 0. Defaults to 0. To execute twice
			 *							a second use 500000 for instance.
			 * @param iterationLimit If the task misses its executionInterval, iterationLimit controls how many
			 *						 extra executions of the Task will be performed to catch up. Task that are
			 *						 slow and computationally expensive should not set this limit higher than one
			 *						 since it will slow the engine down if it cannot consistently run the task at
			 *						 its intervals. Higher iterationLimits are meant for lighter
			 *						 but important tasks, like game logic updates.
			 */
			SQLiteGameLogTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			SQLiteGameLogTask();

			/** Destructor. */
			~SQLiteGameLogTask();

			CLASS_NAME_FUNCTIONS(SQLiteGameLogTask);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method should sets the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Sets state to TS_KILLED.
			 */
			void kill();

			/** Get the maximum number of messages that will be processed per call to execute(). */
			unsigned int getMaxNumberOfMessagesPerIteration() const;

			/** Set the maximum number of messages that will be processed per call to execute(). */
			void setMaxNumberOfMessagesPerIteration(unsigned int maxNumberOfMessagesPerIteration);

			/**
			 * This function is called when some instance sends a GameLogMessage. The message is processed and
			 * data is sent or fetched from the underlying SQLite database.
			 * @param pMessage The GameLogMessage that was sent.
			 */
			void receiveGameLogMessage(const Poco::AutoPtr<GameLogMessage>& pMessage);

		protected:
			/** Read/write mutex for mMaxNumberOfMessagesPerIteration */
			mutable Poco::RWLock mMaxNumberOfMessagesPerIterationRWLock;
			/** This field defines the maximum number of messages that will processed per call to execute. */
			unsigned int mMaxNumberOfMessagesPerIteration;

			int checkIfTableExists(sqlite3 *db, const std::string& name);

			int checkIfRowExists(sqlite3 *db, const std::string& tableName, const std::string& whereClause);

			int commitEntity(sqlite3 *db, const GameLogEntity *pEntity) throw (Exception);

			int commitEntry(sqlite3 *db, const GameLogEntity *pEntity, const GameLogEntityEntry *pEntry) throw (Exception);

			int updateEntity(sqlite3 *db, GameLogEntity *pEntity) throw (Exception);

			int updateEntry(sqlite3 *db, GameLogEntity *pEntity, GameLogEntityEntry *pEntry) throw (Exception);

			int readEntity(sqlite3 *db, const std::string& entityName) throw (Exception);

			int readEntry(sqlite3 *db, GameLogEntity *pEntity, std::list<std::string> primaryKeyValues) throw (Exception);
	};

	/**
	 * This function is called by sqlite for the results of a query. It is called once for
	 * for every row in the table of results.
	 * @param pGameLogEntity The GameLogEntity instance to add the row to as an entry.
	 * @param argc The number of columns in this row.
	 * @param argv An array of strings for the value in each column.
	 * @param colNames An array of column names.
	 */
	int sqliteCallback(void *pGameLogEntity, int argc, char **argv, char **colNames);

	int sqliteTableInfoCallback(/*std::list<std::pair<std::string, bool> >*/void *pList, int argc, char **argv, char **colNames);

	//inlines
	inline unsigned int SQLiteGameLogTask::getMaxNumberOfMessagesPerIteration() const
	{
		Poco::ScopedRWLock lock(mMaxNumberOfMessagesPerIterationRWLock, false);

		return mMaxNumberOfMessagesPerIteration;
	}

	inline void SQLiteGameLogTask::setMaxNumberOfMessagesPerIteration(unsigned int maxNumberOfMessagesPerIteration)
	{
		Poco::ScopedRWLock lock(mMaxNumberOfMessagesPerIterationRWLock, true);

		mMaxNumberOfMessagesPerIteration = maxNumberOfMessagesPerIteration;
	}

} // Myoushu

#endif

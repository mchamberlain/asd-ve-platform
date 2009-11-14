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

/*
 * @file SQLiteGameLogEntity.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include <sstream>

#include "SQLiteGameLogEntity.h"
#include "ObjectPool.h"
#include "GameLogMessage.h"
#include "NotificationManager.h"

namespace Myoushu
{
	CLASS_NAME(SQLiteGameLogEntity, "Myoushu::SQLiteGameLogEntity");

	SQLiteGameLogEntity::SQLiteGameLogEntity(const std::string& name) : GameLogEntity(name), mLastAssignedReadID(0), mCommitPending(false)
		, mUpdatePending(false)
	{
	}

	SQLiteGameLogEntity::SQLiteGameLogEntity(const std::string& name, const GameLogEntityEntry::AttributeNamesVector& attributeNames)
		: GameLogEntity(name, attributeNames), mLastAssignedReadID(0), mCommitPending(false), mUpdatePending(false)
	{
	}

	SQLiteGameLogEntity::~SQLiteGameLogEntity()
	{
	}

	memUInt SQLiteGameLogEntity::readEntry(const std::list<std::string>& primaryKey)
	{
		memUInt readID;
		std::map<std::string, memUInt>::const_iterator iter;
		GameLogMessage *pMessage;
		std::stringstream sStr;
		std::list<std::string>::const_iterator keyIter;
		std::string primaryKeyStr;

		for (keyIter = primaryKey.begin(); keyIter != primaryKey.end(); ++keyIter)
		{
			sStr << (*keyIter);
		}

		primaryKeyStr = sStr.str();

		Poco::ScopedRWLock lock(mRWLock, true);

		// Check if there is already a pending read request for this primaryKey. If there is, return the read ID
		// associated with it. If there is not yet a pending read request, add it and return the new read ID.
		iter = mPendingNameToReadID.find(primaryKeyStr);
		if (iter != mPendingNameToReadID.end())
		{
			// The read request already exists
			return iter->second;
		}

		// A read request for this entity primaryKey does not already exist
		readID = mLastAssignedReadID + 1;
		mPendingNameToReadID.insert(std::pair<std::string, memUInt>(primaryKeyStr, readID));
		mPendingReadIDToName.insert(std::pair<memUInt, std::string>(readID, primaryKeyStr));

		mLastAssignedReadID++;

		// Send a message to read this entry
		pMessage = ObjectPool<GameLogMessage>::getSingletonPtr()->get(true);
		pMessage->setMessageType(GameLogMessage::GLM_READ_ENTRY);
		pMessage->setGameLogEntity(this);
		pMessage->setEntryPrimaryKey(primaryKey);
		pMessage->setActionID(readID);
		NotificationManager::getSingletonPtr()->queueNotification(pMessage);

		return readID;
	}

	bool SQLiteGameLogEntity::checkRead(memUInt readID)
	{
		std::map<memUInt, std::string>::const_iterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		iter = mPendingReadIDToName.find(readID);
		if (iter == mPendingReadIDToName.end())
		{
			// Pending read ID not found, read is either complete or invalid ID
			return true;
		}

		// Read is still pending
		return false;
	}

	void SQLiteGameLogEntity::readCompleted(memUInt readID)
	{
		std::map<memUInt, std::string>::iterator iter;
		std::string primaryKey;

		Poco::ScopedRWLock lock(mRWLock, true);

		iter = mPendingReadIDToName.find(readID);
		if (iter == mPendingReadIDToName.end())
		{
			// Pending read ID not found, read is either complete or invalid ID
			return;
		}

		// Remove read ID
		primaryKey = iter->second;

		mPendingReadIDToName.erase(iter);
		mPendingNameToReadID.erase(primaryKey);
	}

	void SQLiteGameLogEntity::commit()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Set the mCommitPending flag to true
		mCommitPending = true;

		// Create and send the message
		GameLogMessage *pMessage;
		pMessage = ObjectPool<GameLogMessage>::getSingleton().get(true);

		pMessage->setMessageType(GameLogMessage::GLM_COMMIT_ENTITY);
		pMessage->setGameLogEntity(this);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	bool SQLiteGameLogEntity::checkCommit()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mCommitPending;
	}

	void SQLiteGameLogEntity::commitCompleted()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mCommitPending = false;
	}

	void SQLiteGameLogEntity::update(bool overwrite)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Set the mCommitPending flag to true
		mCommitPending = true;

		// Create and send the message
		GameLogMessage *pMessage;
		pMessage = ObjectPool<GameLogMessage>::getSingleton().get(true);

		pMessage->setMessageType(GameLogMessage::GLM_UPDATE_ENTITY);
		pMessage->setGameLogEntity(this);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	bool SQLiteGameLogEntity::checkUpdate()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mUpdatePending;
	}

	void SQLiteGameLogEntity::updateCompleted()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mUpdatePending = false;
	}

} // namespace Myoushu

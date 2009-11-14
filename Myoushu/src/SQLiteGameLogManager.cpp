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
 * @file SQLiteGameLogManager.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "SQLiteGameLogManager.h"
#include "SQLiteGameLogEntity.h"
#include "ObjectPool.h"
#include "GameLogMessage.h"
#include "NotificationManager.h"

namespace Myoushu
{
	SQLiteGameLogManager::SQLiteGameLogManager() : mLastAssignedReadID(0), mCommitPending(false)
		, mUpdatePending(false)
	{
	}

	SQLiteGameLogManager::~SQLiteGameLogManager()
	{
	}

	GameLogEntity* SQLiteGameLogManager::make(const std::string& name)
	{
		SQLiteGameLogEntity *pEntity;
		std::string newName;

		newName = ensureUniqueName(name);
		if (newName != name)
		{
			// An entity with the same name already exists, return it
			return static_cast<GameLogEntity*>(findByName(name));
		}

		// Create a new entity
		pEntity = new SQLiteGameLogEntity(name);

		// Add it to the factory
		add(pEntity);

		return pEntity;
	}

	GameLogEntity* SQLiteGameLogManager::make(const std::string& className, const std::string& name) throw (Exception)
	{
		if (className == NamedObject<SQLiteGameLogEntity>::getStaticClassName())
		{
			return make(name);
		}

		return NULL;
	}

	GameLogEntity* SQLiteGameLogManager::makeEntity(const std::string& name, std::vector<std::string> attributeNames)
	{
		SQLiteGameLogEntity *pEntity;
		std::string newName;

		newName = ensureUniqueName(name);
		if (newName != name)
		{
			// An entity with the same name already exists. Check whether the attributes and match. If it does, return
			// the existing entity. If it does not, create a new entity with the modified name
			pEntity = static_cast<SQLiteGameLogEntity*>(findByName(name));
			if (pEntity->getAttributeNames() == attributeNames)
			{
				// Match, return the existing entity
				return pEntity;
			}
		}
		// Create a new entity and return it
		pEntity = new SQLiteGameLogEntity(newName, attributeNames);

		// Add it to the factory.
		add(pEntity);

		return pEntity;
	}

	memUInt SQLiteGameLogManager::readEntity(const std::string& name)
	{
		memUInt readID;
		std::map<std::string, memUInt>::const_iterator iter;
		GameLogMessage *pMessage;

		Poco::ScopedRWLock lock(mRWLock, true);

		// Check if there is already a pending read request for this name. If there is, return the read ID
		// associated with it. If there is not yet a pending read request, add it and return the new read ID.
		iter = mPendingNameToReadID.find(name);
		if (iter != mPendingNameToReadID.end())
		{
			// The read request already exists
			return iter->second;
		}

		// A read request for this entity name does not already exist
		readID = mLastAssignedReadID + 1;
		mPendingNameToReadID.insert(std::pair<std::string, memUInt>(name, readID));
		mPendingReadIDToName.insert(std::pair<memUInt, std::string>(readID, name));

		mLastAssignedReadID++;

		// Send a message to read this entry
		pMessage = ObjectPool<GameLogMessage>::getSingletonPtr()->get(true);
		pMessage->setMessageType(GameLogMessage::GLM_READ_ENTITY);
		pMessage->setEntityName(name);
		pMessage->setActionID(readID);
		NotificationManager::getSingletonPtr()->queueNotification(pMessage);

		return readID;
	}

	bool SQLiteGameLogManager::checkRead(memUInt readID) const
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

	void SQLiteGameLogManager::readCompleted(memUInt readID)
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

	void SQLiteGameLogManager::commit()
	{
		Iterator iter;
		GameLogMessage *pMessage;

		Poco::ScopedRWLock lock(mRWLock, false);

		// Set the mCommitPending flag to true
		mCommitPending = true;

		for (iter = begin(); iter != end(); ++iter)
		{
			GameLogEntity *pEntity = iter->second;

			// Call commit on the entity
			if (!pEntity->checkCommit())
			{
				pEntity->commit();
			}
		}

		// Now that messages has been sent to commit all changed entities, we need to
		// put a message in the queue that indicates that all relevant entities have been
		// processed
		pMessage = ObjectPool<GameLogMessage>::getSingleton().get(true);
		pMessage->setMessageType(GameLogMessage::GLM_COMMIT_END);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	bool SQLiteGameLogManager::checkCommit()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mCommitPending;
	}

	void SQLiteGameLogManager::commitCompleted()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mCommitPending = false;
	}

	void SQLiteGameLogManager::update()
	{
		Iterator iter;
		GameLogMessage *pMessage;

		Poco::ScopedRWLock lock(mRWLock, false);

		// Set the mUpdatePending flag to true
		mUpdatePending = true;

		for (iter = begin(); iter != end(); ++iter)
		{
			GameLogEntity *pEntity = iter->second;

			// Call update on the entity
			if (!pEntity->checkUpdate())
			{
				pEntity->update();
			}
		}

		// Now that messages has been sent to update all changed entities, we need to
		// put a message in the queue that indicates that all relevant entities have been
		// processed
		pMessage = ObjectPool<GameLogMessage>::getSingleton().get(true);
		pMessage->setMessageType(GameLogMessage::GLM_UPDATE_END);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	bool SQLiteGameLogManager::checkUpdate()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mUpdatePending;
	}

	void SQLiteGameLogManager::updateCompleted()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mUpdatePending = false;
	}

} // namespace Myoushu

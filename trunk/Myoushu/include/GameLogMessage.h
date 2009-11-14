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
 * @file GameLogMessage.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_GAME_LOG_MESSAGE_H
#define MYOUSHU_GAME_LOG_MESSAGE_H

#include <list>
#include <string>

#include "Poco/RWLock.h"

#include "Message.h"
#include "NamedObject.h"
#include "GameLogEntity.h"

namespace Myoushu
{
	/**
	 * A message about events related to the data capturing system in the engine.
	 */
	class MYOUSHU_API GameLogMessage : public Message, public NamedObject<GameLogMessage>
	{
		public:
			/** Enumeration of message types for the activity log system. */
			enum GameLogMessageType
			{
				/** Unknown message type. */
				GLM_UNKNOWN = 0,
				/** Commit changes to an entity secondary storage. */
				GLM_COMMIT_ENTITY,
				/** Reload entity data from secondary storage into memory. */
				GLM_UPDATE_ENTITY,
				/** Read a specific entity from secondary storage into memory. */
				GLM_READ_ENTITY,
				/** Commit changes to an entry secondary storage. */
				GLM_COMMIT_ENTRY,
				/** Reload entry data from secondary storage into memory. */
				GLM_UPDATE_ENTRY,
				/** Read a specific entry from secondary storage into memory. */
				GLM_READ_ENTRY,
				/** This message indicates the last entity has been committed. */
				GLM_COMMIT_END,
				/** This message indicates the last entity has been updated. */
				GLM_UPDATE_END
			};

			/** Nullary constructor. */
			GameLogMessage();

			/**
			 * Constructor.
			 * @param messageType The type of this message.
			 * @param pEntity The GameLogEntity to be influenced, depending on the message type.
			 * @param entityName In situations where pEntity is NULL or unavailable, the name of the entity
			 *					 can be used in conjunction with the GameLogManager.
			 */
			GameLogMessage(GameLogMessageType messageType, GameLogEntity *pEntity = NULL, const std::string& entityName = "");

			/** Destructor */
			virtual ~GameLogMessage();

			CLASS_NAME_FUNCTIONS(GameLogMessage);

			/** Gets the mMessageType field, the type of this message. */
			GameLogMessageType getMessageType() const;

			/** Sets the type of this message, the mMessageType field. */
			void setMessageType(GameLogMessageType messageType);

			/** Gets the GameLogEntity, if any, associated with this message. */
			GameLogEntity* getGameLogEntity() const;

			/** Sets the GameLogEntity that is to be associated with this message. */
			void setGameLogEntity(GameLogEntity *pEntity);

			/** Gets the GameLogEntityEntry, if any, associated with this message. */
			GameLogEntityEntry* getGameLogEntityEntry() const;

			/** Sets the GameLogEntityEntry that is to be associated with this message. */
			void setGameLogEntityEntry(GameLogEntityEntry *pEntity);

			/**
			 * Gets the name of the entity. In situations where mpEntity is NULL or unavailable,
			 * mEntityName can be used in conjunction with the GameLogManager.
			 */
			std::string getEntityName() const;

			/**
			 * Sets the name of the entity. In situations where mpEntity is NULL or unavailable,
			 * mEntityName can be used in conjunction with the GameLogManager.
			 */
			void setEntityName(const std::string& entityName);

			/**
			 * Gets the primary key of the entry. In situations where mpEntry is NULL or unavailable,
			 * mEntryPrimaryKey can be used in conjunction with the mpEntity and GameLogManager.
			 */
			std::list<std::string> getEntryPrimaryKey() const;

			/**
			 * Sets the primary key of the entry. In situations where mpEntry is NULL or unavailable,
			 * mEntryPrimaryKey can be used in conjunction with the mpEntry and GameLogManager.
			 */
			void setEntryPrimaryKey(const std::list<std::string>& entryPrimaryKey);

			/** 
			 * Get an ID associated with the action contained in this message. For instance, a read
			 * request on a GameLogEntityEntry will return an ID that users can use to check whether
			 * a read has completed. So this ID can then be used to notify a Task, for instance,
			 * that the action has completed.
			 */
			memUInt getActionID() const;

			/** 
			 * Set an ID associated with the action contained in this message. For instance, a read
			 * request on a GameLogEntityEntry will return an ID that users can use to check whether
			 * a read has completed. So this ID can then be used to notify a Task, for instance,
			 * that the action has completed.
			 */
			void setActionID(memUInt actionID);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual GameLogMessage* clone() const;

			/** Clone this instance into message. */
			GameLogMessage& operator=(const GameLogMessage& message);

			/** 
			 * Clears or resets the fields of the Message instance. This method resets the mCreator field to the local IP. 
			 * It is crucial that classes that override the clear() function call Message::clear() in their version of clear().
			 */
			virtual void clear();

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialised data.
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception);

			/**
			 * Populates this instance with the serialized description read from the specified buffer.
			 * @param pMem The buffer to read the instance description from.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the data read (in bytes).
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The message type. */
			GameLogMessageType mMessageType;
			/** The entity that is influenced by the action specified in the message type. */
			GameLogEntity *mpEntity;
			/** The entry that is influenced by the action specified in the message type. */
			GameLogEntityEntry *mpEntry;
			/**
			 * The name of the entity. In situations where mpEntity is NULL or unavailable,
			 * mEntityName can be used in conjunction with the GameLogManager.
			 */
			std::string mEntityName;
			/**
			 * The primary key of the entry. In situations where mpEntry is NULL or unavailable,
			 * mEntryPrimaryKey can be used in conjunction with mpEntry and GameLogManager.
			 */
			std::list<std::string> mEntryPrimaryKey;
			/** 
			 * An ID associated with the action contained in this message. For instance, a read
			 * request on a GameLogEntityEntry will return an ID that users can use to check whether
			 * a read has completed. So this ID can then be used to notify a Task, for instance,
			 * that the action has completed.
			 */
			memUInt mActionID;

	}; // class GameLogMessage

	// inlines
	inline GameLogMessage::GameLogMessageType GameLogMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mMessageType;
	}

	inline void GameLogMessage::setMessageType(GameLogMessage::GameLogMessageType messageType)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mMessageType = messageType;
	}

	inline GameLogEntity* GameLogMessage::getGameLogEntity() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mpEntity;
	}

	inline void GameLogMessage::setGameLogEntity(GameLogEntity *pEntity)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpEntity = pEntity;
	}

	inline GameLogEntityEntry* GameLogMessage::getGameLogEntityEntry() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mpEntry;
	}

	inline void GameLogMessage::setGameLogEntityEntry(GameLogEntityEntry *pEntry)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpEntry = pEntry;
	}

	inline std::string GameLogMessage::getEntityName() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntityName;
	}

	inline void GameLogMessage::setEntityName(const std::string& entityName)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mEntityName = entityName;
	}

	inline std::list<std::string> GameLogMessage::getEntryPrimaryKey() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntryPrimaryKey;
	}

	inline void GameLogMessage::setEntryPrimaryKey(const std::list<std::string>& entryPrimaryKey)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mEntryPrimaryKey = entryPrimaryKey;
	}

	inline memUInt GameLogMessage::getActionID() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mActionID;
	}

	inline void GameLogMessage::setActionID(memUInt actionID)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mActionID = actionID;
	}

} // namespace Myoushu

#endif

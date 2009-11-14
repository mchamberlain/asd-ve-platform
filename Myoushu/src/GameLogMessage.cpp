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
 * @file GameLogMessage.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "GameLogMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(GameLogMessage, "Myoushu::GameLogMessage");

	GameLogMessage::GameLogMessage() : mMessageType(GLM_UNKNOWN), mpEntity(NULL), mEntityName(""), mActionID(0)
	{
	}

	GameLogMessage::GameLogMessage(GameLogMessageType messageType, GameLogEntity *pEntity, const std::string& entityName)
		: mMessageType(messageType), mpEntity(pEntity), mEntityName(entityName)
	{
	}

	GameLogMessage::~GameLogMessage()
	{
	}

	GameLogMessage* GameLogMessage::clone() const
	{
		GameLogMessage *newMessage;

		newMessage = ObjectPool<GameLogMessage>::getSingleton().get(true);
		(*newMessage) = (*this);

		return newMessage;
	}

	GameLogMessage& GameLogMessage::operator=(const GameLogMessage& message)
	{
		Message::operator =(message);

		Poco::ScopedRWLock lock(mRWLock, true);

		mMessageType = message.getMessageType();
		mpEntity = message.getGameLogEntity();
		mpEntry = message.getGameLogEntityEntry();
		mEntityName = message.getEntityName();
		mEntryPrimaryKey = message.getEntryPrimaryKey();

		return *this;
	}

	void GameLogMessage::clear()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mMessageType = GLM_UNKNOWN;
		mpEntity = NULL;
		mpEntry = NULL;
		mEntityName = "";
		mEntryPrimaryKey.clear();
	}

	memUInt GameLogMessage::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		return 0;
	}

	memUInt GameLogMessage::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		return 0;
	}

} // namespace Myoushu

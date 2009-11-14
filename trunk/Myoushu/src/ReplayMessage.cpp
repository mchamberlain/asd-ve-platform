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
 * @file ReplayMessage.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "ReplayMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(ReplayMessage, "Myoushu::ReplayMessage");

	ReplayMessage::ReplayMessage(ReplayMessageType messageType, const std::string& replayName) : mMessageType(messageType), mReplayName(replayName), mpReplay(NULL)
	{
	}

	ReplayMessage::ReplayMessage() : mMessageType(RM_UNKNOWN), mReplayName(""), mpReplay(NULL)
	{
	}

	ReplayMessage::~ReplayMessage()
	{
	}

	void ReplayMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(mRWLock, true);

		// Set all member variables to their zero values
		mMessageType = RM_UNKNOWN;
		mReplayName = "";
		mpReplay = NULL;
	}

	ReplayMessage* ReplayMessage::clone() const
	{
		ReplayMessage *replayMessage;

		Poco::ScopedRWLock lock(mRWLock, false);

		replayMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		(*replayMessage) = (*this);

		return replayMessage;
	}

	ReplayMessage& ReplayMessage::operator=(const ReplayMessage& message)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		Message::operator=(message);

		mMessageType = message.getMessageType();
		mReplayName = message.getReplayName();
		mpReplay = const_cast<Replay*>(message.getReplay());

		return *this;
	}

} // Myoushu

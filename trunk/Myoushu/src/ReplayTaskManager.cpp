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
 * @file ReplayTaskManager.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "ReplayTaskManager.h"
#include "ReplayFactory.h"
#include "ReplayMessage.h"
#include "ObjectPool.h"
#include "NotificationManager.h"
#include "Constants.h"

namespace Myoushu
{
	ReplayTaskManager::ReplayTaskManager()
	{
	}

	ReplayTaskManager::~ReplayTaskManager()
	{
	}

	void ReplayTaskManager::play(const std::string& replayName, const std::string& group) throw (Exception)
	{
		Replay *pReplay;
		ReplayMessage *pMessage;

		// First check if a replay with the same name exists in the factory, if so use it, otherwise
		// create a new one
		pReplay = ReplayFactory::getSingleton().findByName(replayName);
		if (pReplay == NULL)
		{
			pReplay = ReplayFactory::getSingleton().make(replayName, false);
		}

		// open the replay for reading, so that it is ready for playback
		if (group == "")
		{
			pReplay->openForPlayback(Constants::RG_REPLAYS);
		}
		else
		{
			pReplay->openForPlayback(group);
		}

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_START_PLAYBACK);
		pMessage->setReplayName(replayName);
		pMessage->setReplay(pReplay);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	void ReplayTaskManager::play(Replay *pReplay) throw (Exception)
	{
		ReplayMessage *pMessage;

		// Ensure that pReplay is not NULL
		if (pReplay == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ReplayTaskManager::play(): pReplay is NULL!");
		}

		pReplay->openForPlayback("");

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_START_PLAYBACK);
		pMessage->setReplayName(pReplay->getName());
		pMessage->setReplay(pReplay);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	void ReplayTaskManager::record(const std::string& replayName, const std::string& group, bool overwrite) throw (Exception)
	{
		Replay *pReplay;
		ReplayMessage *pMessage;

		pReplay = ReplayFactory::getSingleton().make(replayName, !overwrite);

		if (pReplay == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ReplayTaskManager::record(): Couldn't find/create Replay instance.");
		}

		// open the replay for writing, so that it is ready for recording
		if (group == "")
		{
			pReplay->openForWriting(Constants::RG_REPLAYS, overwrite);
		}
		else
		{
			pReplay->openForWriting(group, overwrite);
		}

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_START_RECORDING);
		pMessage->setReplayName(replayName);
		pMessage->setReplay(pReplay);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	void ReplayTaskManager::record(Replay *pReplay, bool overwrite) throw (Exception)
	{
		ReplayMessage *pMessage;

		// Ensure that pReplay is not NULL
		if (pReplay == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ReplayTaskManager::record(): pReplay is NULL!");
		}

		pReplay->openForWriting(Constants::RG_REPLAYS, overwrite);

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_START_RECORDING);
		pMessage->setReplayName(pReplay->getName());
		pMessage->setReplay(pReplay);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	void ReplayTaskManager::pause()
	{
		ReplayMessage *pMessage;

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_PAUSE);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

	void ReplayTaskManager::stop()
	{
		ReplayMessage *pMessage;

		pMessage = ObjectPool<ReplayMessage>::getSingleton().get(true);
		pMessage->setMessageType(ReplayMessage::RM_STOP);

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

} // namespace

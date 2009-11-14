/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morn� Chamberlain & Stellenbosch University

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
 * @file DefaultNetworkTransmitBehaviour.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "DefaultNetworkTransmitBehaviour.h"
#include "NotificationManager.h"
#include "EngineLog.h"

namespace Myoushu
{
	DefaultNetworkTransmitBehaviour::DefaultNetworkTransmitBehaviour()
	{
	}

	DefaultNetworkTransmitBehaviour::~DefaultNetworkTransmitBehaviour()
	{
		// Unregister the handler for ScriptMessages
		NotificationManager::getSingleton().removeObserver(this, &DefaultNetworkTransmitBehaviour::receiveNetworkMessage);

		// Destroy the message queue for this task
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void DefaultNetworkTransmitBehaviour::init()
	{
		// Register the receiveNetworkMessage function to receive NetworkMessages sent by the engine.
		NotificationManager::getSingleton().addObserver(this, &DefaultNetworkTransmitBehaviour::receiveNetworkMessage);
	}

	void DefaultNetworkTransmitBehaviour::update()
	{
		// Receive any notifications queued for this Task.
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void DefaultNetworkTransmitBehaviour::receiveNetworkMessage(const Poco::AutoPtr<NetworkMessage>& message)
	{
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "DefaultNetworKTransmitBehaviour::receiveNetworkMessage(): message is NULL.");
			return;
		}

		mMessagesToTransmit.push_back(message);
	}

} // namespace Myoushu
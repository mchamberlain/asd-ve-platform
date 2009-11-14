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
 * @file DefaultNetworkListenBehaviour.cpp
 * @author ME Chamberlain
 * @date November 2008
 */

#include <string>

#include "Poco/AutoPtr.h"

#include "DefaultNetworkListenBehaviour.h"
#include "NetworkMessage.h"
#include "ObjectPool.h"
#include "EngineLog.h"
#include "NetworkMessageCallbackBase.h"

namespace Myoushu
{
	CLASS_NAME(DefaultNetworkListenBehaviour, "Myoushu::DefaultNetworkListenBehaviour");

	DefaultNetworkListenBehaviour::DefaultNetworkListenBehaviour()
	{
	}

	DefaultNetworkListenBehaviour::~DefaultNetworkListenBehaviour()
	{
	}

	void DefaultNetworkListenBehaviour::processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length)
	{
		Poco::AutoPtr<NetworkMessage> message;
		NetworkMessageCallbackBase *callback;
		std::string type;

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->populateInstance(buffer, length);

		switch (message->getType())
		{
			case NetworkMessage::NM_UNKNOWN:
				type = "unknown";
				break;
			case NetworkMessage::NM_CONNECT:
				type = "connect";
				break;
			case NetworkMessage::NM_DISCONNECT:
				type = "disconnect";
				break;
			case NetworkMessage::NM_ACK_CONNECT:
				type = "acknowledge connect";
				break;
			case NetworkMessage::NM_ACK:
				type = "ack";
				break;
			case NetworkMessage::NM_PING:
				type = "ping";
				break;
			case NetworkMessage::NM_ENCAPSULATED_MESSAGE:
				type = "encapsulated message";
				break;
			case NetworkMessage::NM_CREATE_OBJECT:
				type = "create object\nname = " + message->getObjectName() + "\nclass name = " + message->getObjectClassName();
				break;
			case NetworkMessage::NM_UPDATE_OBJECT:
				type = "update object\nname = " + message->getObjectName() + "\nclass name = " + message->getObjectClassName();
				break;
			case NetworkMessage::NM_DESTROY_OBJECT:
				type = "delete object\nname = " + message->getObjectName();
				break;
			default:
				type = "unsupported";
				break;
		}

		LOG_DEBUG(EngineLog::LM_INFO_ENGINE, "Received message over network, type: " << type);

		// Call any associated callbacks
		callback = mNetworkMessageCallbacks[message->getType()].get();
		if (callback != NULL)
		{
			callback->executeCallback(message.get());
		}
	}

} // namespace Myoushu

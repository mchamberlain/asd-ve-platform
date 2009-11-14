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
 * @file P2PNetworkTransmitBehaviour.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "P2PNetworkTransmitBehaviour.h"
#include "ObjectPool.h"
#include "NetworkManager.h"

namespace Myoushu
{
	P2PNetworkTransmitBehaviour::P2PNetworkTransmitBehaviour()
	{
		// Disallow the NO_ACTION input action from being transmitted
		addDisallowedInputAction(InputMessage::NO_ACTION);
		// Disallow the built-in console action from being transmitted
		addDisallowedInputAction("console");
	}

	P2PNetworkTransmitBehaviour::~P2PNetworkTransmitBehaviour()
	{
		// Unregister the handlers
		NotificationManager::getSingleton().removeObserver(this, &P2PNetworkTransmitBehaviour::receiveNetworkMessage);
		NotificationManager::getSingleton().removeObserver(this, &P2PNetworkTransmitBehaviour::receiveInputMessage);

		// Destroy the message queue for this task
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void P2PNetworkTransmitBehaviour::init()
	{
		// Register the receiveNetworkMessage function to receive NetworkMessages sent by the engine.
		NotificationManager::getSingleton().addObserver(this, &P2PNetworkTransmitBehaviour::receiveNetworkMessage);
		// Register the receiveInputMessage function to receive InputMessages sent by the engine.
		NotificationManager::getSingleton().addObserver(this, &P2PNetworkTransmitBehaviour::receiveInputMessage);
	}

	void P2PNetworkTransmitBehaviour::update()
	{
		clearListOfMessagesToTransmit();

		// Receive any notifications queued for this Task.
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void P2PNetworkTransmitBehaviour::receiveNetworkMessage(const Poco::AutoPtr<NetworkMessage>& message)
	{
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "P2PNetworkTransmitBehaviour::receiveNetworkMessage(): message is NULL.");
			return;
		}

		// Do not transmit messages that did not originate on this host
		if (message->getCreator() != NetworkManager::getSingleton().getLocalIP())
		{
			return;
		}

		// If an instance name for an attached object is given in the message, append the IP address of this host to
		// the name, so that names stay unique and can be associated with the proper hosts on every system.
		if (message->getObjectName().length() > 0)
		{
			NetworkMessage *msg;

			msg = const_cast<NetworkMessage*>(message.get());
			msg->setObjectName(message->getObjectName() + "_" + NetworkManager::getSingleton().getLocalIP().toString());
		}

		mMessagesToTransmit.push_back(message);
	}

	void P2PNetworkTransmitBehaviour::receiveInputMessage(const Poco::AutoPtr<InputMessage>& message)
	{
		InputMessage *pInputMessage;
		NetworkMessage *pNetworkMessage;
		NetworkManager::ConnectedHostsMapConstIterator iter;

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "P2PNetworKTransmitBehaviour::receiveInputMessage(): message is NULL.");
			return;
		}

		// Check whether there are any currently connected hosts to forward this message to
		// If there are none, then just exit the function
		if (NetworkManager::getSingleton().getNumberOfConnectedHosts() == 0)
		{
			return;
		}

		// Do not transmit messages that did not originate on this host
		if (message->getCreator() != NetworkManager::getSingleton().getLocalIP())
		{
			return;
		}

		// Do not transmit InputMessages with an inputAction that is disallowed for transmission
		if (isDisallowedInputAction(message->getInputAction()))
		{
			return;
		}

		// Get an empty NetworkMessage instance from the NetworkMessage ObjectPool
		pNetworkMessage = ObjectPool<NetworkMessage>::getSingleton().get(true);
		// Clone the InputMessage that is to be encapsulated in the NetworkMessage
		pInputMessage = message->clone();

		pNetworkMessage->setType(NetworkMessage::NM_ENCAPSULATED_MESSAGE);
		pNetworkMessage->setSource(NetworkManager::getSingleton().getLocalIP());
		pNetworkMessage->setEncapsulatedMessage(pInputMessage);

		iter = NetworkManager::getSingleton().getConncetedHostsIteratorAndLock();
		try
		{
			pNetworkMessage->setDestination(iter->second.getIPAddress());
			// Queue the NetworkMessage
			mMessagesToTransmit.push_back(pNetworkMessage);

			// We have already queued the message to the first host, now start from the second
			for (++iter; iter != NetworkManager::getSingleton().getConncetedHostsEndIterator(); ++iter)
			{
				const HostRecord& hostRecord = iter->second;

				pNetworkMessage = pNetworkMessage->clone();
				pNetworkMessage->setDestination(hostRecord.getIPAddress());
				pNetworkMessage->setEncapsulatedMessage(pInputMessage->clone());
				// Queue the NetworkMessage
				mMessagesToTransmit.push_back(pNetworkMessage);
			}
			NetworkManager::getSingleton().releaseConnectedHostsIteratorAndLock(iter);
		}
		catch (Exception &e)
		{
			NetworkManager::getSingleton().releaseConnectedHostsIteratorAndLock(iter);
			LOG(EngineLog::LM_ERROR, "P2PNetworkTransmitBehaviour::receiveInputMessage(): exception while queueing network messages for transmission: " << e.what());
		}
		catch (Poco::Exception &pe)
		{
			NetworkManager::getSingleton().releaseConnectedHostsIteratorAndLock(iter);
			LOG(EngineLog::LM_ERROR, "P2PNetworkTransmitBehaviour::receiveInputMessage(): exception while queueing network messages for transmission: " << pe.message());
		}
		catch (...)
		{
			NetworkManager::getSingleton().releaseConnectedHostsIteratorAndLock(iter);
			LOG(EngineLog::LM_ERROR, "P2PNetworkTransmitBehaviour::receiveInputMessage(): exception while queueing network messages for transmission.");
		}
	}

} // namespace Myoushu

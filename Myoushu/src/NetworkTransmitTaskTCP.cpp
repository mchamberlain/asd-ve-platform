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
 * @file NetworkTransmitTaskTCP.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "Poco/Net/StreamSocket.h"

#include "NetworkTransmitTaskTCP.h"
#include "NetworkMessage.h"
#include "NotificationManager.h"
#include "Constants.h"
#include "EngineLog.h"
#include "DefaultNetworkTransmitBehaviour.h"
#include "NetworkManager.h"

namespace Myoushu
{
	CLASS_NAME(NetworkTransmitTaskTCP, "Myoushu::NetworkTransmitTaskTCP");

	NetworkTransmitTaskTCP::NetworkTransmitTaskTCP(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit)
		: NetworkTransmitTask(priority, name, executionInterval, iterationLimit)
	{
		state = TS_CREATED;
	}

	NetworkTransmitTaskTCP::NetworkTransmitTaskTCP() : NetworkTransmitTask()
	{
		state = TS_CREATED;
	}

	NetworkTransmitTaskTCP::~NetworkTransmitTaskTCP()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());
	}

	void NetworkTransmitTaskTCP::init() throw (Exception)
	{
		NetworkTransmitTask::init();
	}

	void NetworkTransmitTaskTCP::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void NetworkTransmitTaskTCP::execute(unsigned long timeDelta)
	{
		memUInt dataSize;
		std::list<Poco::AutoPtr<NetworkMessage> >::const_iterator iter;

		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}

		// Construct the list of NetworkMessages to transmit
		pBehaviour->update();

		const std::list<Poco::AutoPtr<NetworkMessage> >& networkMessageQueue = pBehaviour->getMessagesToTransmit();
		rwLock.unlock();

		for (iter = networkMessageQueue.begin(); iter != networkMessageQueue.end(); ++iter)
		{
			const Poco::AutoPtr<NetworkMessage>& message = *iter;

			// Ensure that the message is not NULL
			if (message.get() == NULL)
			{
				LOG(EngineLog::LM_WARNING, "NetworkTransmitTaskTCP::execute(): message is NULL.");
				return;
			}

			// Serialize the message into pSendBuffer
			dataSize = 0;
			try
			{
				dataSize = message->serialize(pSendBuffer, Constants::NETWORK_TRANSMIT_BUFFER_SIZE, Serializable::ST_NETWORK);
			}
			catch (Exception& e)
			{
				LOG(EngineLog::LM_ERROR, "NetworkTransmitTaskTCP::execute(): error serialising message for transmission: " << e.what());
			}

			// Transmit the serialised message to the specified host.
			if (dataSize != 0)
			{
				try
				{
					HostRecord record;
					Poco::Net::StreamSocket socket;

					if (NetworkManager::getSingleton().getConnectedHost(message->getDestination().toString(), record))
					{
						socket = record.getSocket();
					}
					else
					{
						socket.connect(Poco::Net::SocketAddress(message->getDestination(), Constants::NETWORK_LISTEN_PORT));
						socket.setKeepAlive(true);
						socket.setBlocking(false);
						// Add the host to the list of connected hosts in the network manager
						record = NetworkManager::getSingleton().createHostRecord(message->getDestination().toString());
						record.setSocket(socket);
						NetworkManager::getSingleton().addConnectedHost(record);
					}
					// Do not send with invalid sockets
					if ((socket.impl() != NULL) && (socket.impl()->sockfd() != POCO_INVALID_SOCKET))
					{
						socket.setKeepAlive(true);
						socket.sendBytes(pSendBuffer, dataSize);
					}
				}
				catch (Poco::Exception& e)
				{
					LOG(EngineLog::LM_ERROR, "NetworkTransmitTaskTCP::execute(): error transmitting message: " << e.message());
				}
			}
		}

		Poco::ScopedRWLock lock(rwLock, false);

		pBehaviour->clearListOfMessagesToTransmit();
	}

	void NetworkTransmitTaskTCP::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);
		state = TS_KILLED;
	}

} // namespace Myoushu

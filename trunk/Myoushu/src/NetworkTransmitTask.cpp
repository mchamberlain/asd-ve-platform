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
 * @file NetworkTransmitTask.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "NetworkTransmitTask.h"
#include "NetworkMessage.h"
#include "NotificationManager.h"
#include "Constants.h"
#include "EngineLog.h"
#include "DefaultNetworkTransmitBehaviour.h"

namespace Myoushu
{
	CLASS_NAME(NetworkTransmitTask, "Myoushu::NetworkTransmitTask");

	NetworkTransmitTask::NetworkTransmitTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit)
		: Task(name, priority, executionInterval, iterationLimit), pBehaviour(new DefaultNetworkTransmitBehaviour()), pSendBuffer(NULL)
	{
		state = TS_CREATED;
	}

	NetworkTransmitTask::NetworkTransmitTask() : Task("NetworkTransmitTask", 0), pBehaviour(new DefaultNetworkTransmitBehaviour()), pSendBuffer(NULL)
	{
		state = TS_CREATED;
	}

	NetworkTransmitTask::~NetworkTransmitTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		if (pSendBuffer != NULL)
		{
			delete [] pSendBuffer;
			pSendBuffer = NULL;
		}

		pBehaviour = NULL;
	}

	void NetworkTransmitTask::init() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Initializing " << getName() << ".");

		Poco::ScopedRWLock lock(rwLock, true);

		pSendBuffer = new char[Constants::NETWORK_TRANSMIT_BUFFER_SIZE];
		state = TS_INITIALIZED;
	}

	void NetworkTransmitTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void NetworkTransmitTask::execute(unsigned long timeDelta)
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
				LOG(EngineLog::LM_WARNING, "NetworkTransmitTask::execute(): message is NULL.");
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
				LOG(EngineLog::LM_ERROR, "NetworkTransmitTask::execute(): error serialising message for transmission: " << e.what());
			}

			// Transmit the serialised message to the specified host.
			if (dataSize != 0)
			{
				try
				{
					mTransmitSocket.sendTo(pSendBuffer, dataSize, Poco::Net::SocketAddress(message->getDestination(), Constants::NETWORK_LISTEN_PORT));
				}
				catch (Poco::Exception& e)
				{
					LOG(EngineLog::LM_ERROR, "NetworkTransmitTask::execute(): error transmitting message: " << e.message());
				}
			}
		}

		Poco::ScopedRWLock lock(rwLock, false);

		pBehaviour->clearListOfMessagesToTransmit();
	}

	void NetworkTransmitTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);
		state = TS_KILLED;
	}

	void NetworkTransmitTask::setNetworkTransmitBehaviour(NetworkTransmitBehaviour *pBehaviour) throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (pBehaviour == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkTransmitTask::setNetworkTransmitBehaviour(): pBehaviour is NULL.");
		}

		// Initialize the new behaviour before we remove the old one, we do not want to miss any messages in the cross-over
		pBehaviour->init();

		// Destory the existing behaviour
		if (this->pBehaviour.get() != NULL)
		{
			this->pBehaviour = NULL;
		}

		// and assign the new one
		this->pBehaviour = pBehaviour;
	}

} // namespace Myoushu

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
 * @file NetworkListenTask.cpp
 * @author ME Chamberlain
 * @date November 2008
 */

#include "NetworkListenTask.h"
#include "Constants.h"
#include "EngineLog.h"
#include "DefaultNetworkListenBehaviour.h"

namespace Myoushu
{
	CLASS_NAME(NetworkListenTask, "Myoushu::NetworkListenTask");

	NetworkListenTask::NetworkListenTask(const std::string& name, int priority, unsigned long executionInterval, unsigned int iterationLimit)
		: ConcurrentTask(name, priority, executionInterval, iterationLimit), mListenSocket(), mListenBehaviour(new DefaultNetworkListenBehaviour())
	{
		state = TS_CREATED;
	}

	NetworkListenTask::~NetworkListenTask()
	{
		kill();
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());
	}

	void NetworkListenTask::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing NetworkListenTask...");
		// Setup the socket address to receive messages from any host on port Constants::NETWORK_LISTEN_PORT
		Poco::Net::SocketAddress listenSocketAddress("0.0.0.0", Constants::NETWORK_LISTEN_PORT);
		mListenSocket.setBlocking(false);
		// Bind the socket
		mListenSocket.bind(listenSocketAddress);
		
		state = TS_INITIALIZED;
	}

	void NetworkListenTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void NetworkListenTask::execute(unsigned long timeDelta)
	{
		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}

		rwLock.unlock();
	}

	void NetworkListenTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Close the socket
		mListenSocket.close();

		state = TS_KILLED;
	}

	void NetworkListenTask::run()
	{
		Poco::Net::SocketAddress incomingAddress;
		TaskState lState;
		char* buffer;
		int receivedSize;

		// Create the receive buffer
		buffer = new char[Constants::NETWORK_RECEIVE_BUFFER_SIZE];

		// A loop that receives network messages. The loop checks the state of this task in
		// a thread safe manner, and terminates if the the state is TS_KILLED. If the state is TS_SUSPEND
		// the loop does not receive any messages.
		for (lState = getState(); lState != TS_KILLED; lState = getState())
		{
			if (lState == TS_SUSPENDED)
			{
				this->sleep(1);

				// Immediately continue to the next iteration if the the task is suspended
				continue;
			}

			try
			{
				// Listen for incoming messages
				receivedSize = mListenSocket.receiveFrom(buffer, Constants::NETWORK_RECEIVE_BUFFER_SIZE, incomingAddress);

				// If we received a message, send it to our NetworkListenBehaviour instance for processing
				if (receivedSize > 0)
				{
					LOG_DEBUG(EngineLog::LM_INFO_ENGINE, "NetworkListenTask::run(): Received message from: " << incomingAddress.toString());

					// Lock for reading mListenBehaviour
					Poco::ScopedRWLock lock(rwLock, false);

					if (mListenBehaviour != NULL)
					{
						mListenBehaviour->processReceivedMessage(incomingAddress.host(), buffer, receivedSize);
					}
					else
					{
						LOG(EngineLog::LM_WARNING, "NetworkListenTask::run(): Received message dropped: there is no NetworkListenBehaviour instance available to process the message.");
					}
				}
			}
			catch (Exception& e)
			{
				LOG(EngineLog::LM_ERROR, "NetworkListenTask::run(): caught Exception: " << e.getMsg());
			}
			catch (Poco::TimeoutException& e)
			{
				// ignore the TimeoutException, it is thrown often in non-blocking mode
			}
			catch (Poco::Exception& e)
			{
				LOG(EngineLog::LM_ERROR, "NetworkListenTask::run(): caught Poco::Exception: " << e.displayText());
			}

			this->sleep(1);
		}

		// Free the receive buffer
		delete[] buffer;
	}

} // namespace Myoushu

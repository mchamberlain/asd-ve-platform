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
 * @file NetworkListenTaskTCP.cpp
 * @author ME Chamberlain
 * @date November 2008
 */

#include "NetworkListenTaskTCP.h"
#include "Constants.h"
#include "EngineLog.h"
#include "NetworkManager.h"

namespace Myoushu
{
	CLASS_NAME(NetworkListenTaskTCP, "Myoushu::NetworkListenTaskTCP");

	NetworkListenTaskTCP::NetworkListenTaskTCP(const std::string& name, int priority, unsigned long executionInterval, unsigned int iterationLimit)
		: NetworkListenTask(name, priority, executionInterval, iterationLimit), mServerSocket()
	{
		state = TS_CREATED;
	}

	NetworkListenTaskTCP::~NetworkListenTaskTCP()
	{
		kill();
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());
	}

	void NetworkListenTaskTCP::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing NetworkListenTaskTCP...");
		// Setup the socket address to receive messages from any host on port Constants::NETWORK_LISTEN_PORT
		Poco::Net::SocketAddress listenSocketAddress("0.0.0.0", Constants::NETWORK_LISTEN_PORT);
		// Bind the socket
		mServerSocket.bind(listenSocketAddress);
		mServerSocket.setBlocking(false);
		mServerSocket.listen();
		
		state = TS_INITIALIZED;
	}

	void NetworkListenTaskTCP::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void NetworkListenTaskTCP::execute(unsigned long timeDelta)
	{
		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}

		rwLock.unlock();
	}

	void NetworkListenTaskTCP::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Close the socket
		mListenSocket.close();

		state = TS_KILLED;
	}

	void NetworkListenTaskTCP::receiveFromSocket(Poco::Net::StreamSocket& socket, char *buffer)
	{
		int receivedSize;

		try
		{
			// Listen for incoming messages
			receivedSize = socket.receiveBytes(buffer, Constants::NETWORK_RECEIVE_BUFFER_SIZE);

			// If we received a message, send it to our NetworkListenBehaviour instance for processing
			if (receivedSize > 0)
			{
				LOG_DEBUG(EngineLog::LM_INFO_ENGINE, "NetworkListenTaskTCP::run(): Received message from: " << socket.peerAddress().host().toString());

				// Lock for reading mListenBehaviour
				Poco::ScopedRWLock lock(rwLock, false);

				if (mListenBehaviour != NULL)
				{
					mListenBehaviour->processReceivedMessage(socket.peerAddress().host(), buffer, receivedSize);
				}
				else
				{
					LOG(EngineLog::LM_WARNING, "NetworkListenTaskTCP::run(): Received message dropped: there is no NetworkListenBehaviour instance available to process the message.");
				}
			}
		}
		catch (Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "NetworkListenTaskTCP::receiveFromSocket(): caught Exception: " << e.getMsg());
		}
		catch (Poco::TimeoutException& e)
		{
			// ignore the TimeoutException, it is thrown often in non-blocking mode
		}
		catch (Poco::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "NetworkListenTaskTCP::receiveFromSocket(): caught Poco::Exception: " << e.displayText());
		}
	}

	void NetworkListenTaskTCP::run()
	{
		Poco::Net::SocketAddress incomingAddress;
		TaskState lState;
		char* buffer;
		NetworkManager *pNetMan;
		std::list<HostRecord> connectedHosts;
		std::list<HostRecord>::iterator iter;

		pNetMan = NetworkManager::getSingletonPtr();

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

			Poco::Net::StreamSocket socket;
			// Get a completed connection if there are any
			try
			{
				HostRecord record;

				socket = mServerSocket.acceptConnection(incomingAddress);
				socket.setBlocking(false);
				socket.setKeepAlive(true);

				if (pNetMan->getConnectedHost(incomingAddress.toString(), record))
				{
					record.setSocket(socket);
				}
				else
				{
					record = pNetMan->createHostRecord(incomingAddress.host().toString());
					record.setSocket(socket);
					pNetMan->addConnectedHost(record);
				}
			}
			catch (Poco::IOException &e)
			{
			}
				
			// Loop over all connected hosts to try and receive messages
			pNetMan->getConnectedHosts(connectedHosts);
			try
			{
				for (iter = connectedHosts.begin(); iter != connectedHosts.end(); ++iter)
				{
					HostRecord &record = *iter;
					Poco::Net::StreamSocket rcvSocket = record.getSocket();

					// Do not receive from invalid sockets
					if ((rcvSocket.impl() == NULL) || (rcvSocket.impl()->sockfd() == POCO_INVALID_SOCKET))
					{
						continue;
					}

					receiveFromSocket(rcvSocket, buffer);
				}
			}
			catch (Poco::Exception &pe)
			{
				LOG(EngineLog::LM_ERROR, "NetworkListenTaskTCP::run(): Exception in listen loop: " << pe.message());
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_ERROR, "NetworkListenTaskTCP::run(): Exception in listen loop: " << e.what());
			}
			catch (...)
			{
				LOG(EngineLog::LM_ERROR, "NetworkListenTaskTCP::run(): Exception in listen loop.");
			}

			this->sleep(1);
		}

		// Free the receive buffer
		delete[] buffer;
	}

} // namespace Myoushu

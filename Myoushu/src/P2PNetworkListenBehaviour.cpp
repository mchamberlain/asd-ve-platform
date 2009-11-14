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
 * @file P2PNetworkListenBehaviour.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "Poco/AutoPtr.h"

#include "P2PNetworkListenBehaviour.h"
#include "ObjectPool.h"
#include "NetworkManager.h"
#include "EngineLog.h"
#include "NotificationManager.h"
#include "NamedObjectFactory.h"
#include "NamedObjectInstanceCreatorManager.h"
#include "ObjectPool.h"
#include "InputMessage.h"

namespace Myoushu
{
	CLASS_NAME(P2PNetworkListenBehaviour, "Myoushu::P2PNetworkListenBehaviour");

	P2PNetworkListenBehaviour::P2PNetworkListenBehaviour()
	{
	}

	P2PNetworkListenBehaviour::~P2PNetworkListenBehaviour()
	{
	}

	void P2PNetworkListenBehaviour::processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length)
	{
		Poco::AutoPtr<NetworkMessage> message;
		NetworkManager *pNetworkManager;
		NetworkMessage *newMessage;
		NetworkMessageCallbackBase *pCallback;
		bool callbackResult;
		memUInt readSize;
		memUInt totalReadSize;

		// Ignore empty buffer
		if (length <= 0)
		{
			return;
		}

		pNetworkManager = NetworkManager::getSingletonPtr();
		message = ObjectPool<NetworkMessage>::getSingleton().get(true);

		totalReadSize = 0;
		do
		{
			message->clear();
			try
			{
				readSize = message->populateInstance(buffer + (totalReadSize / sizeof(char)), length - totalReadSize);
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_ERROR, "P2PNetworkListenBehaviour::processReceivedMessage(): error while processing message: " << e.what());
				return;
			}

			// Get the associated callback, if any
			pCallback = mNetworkMessageCallbacks[message->getType()].get();
			callbackResult = true;

			switch (message->getType())
			{
				case NetworkMessage::NM_CONNECT:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): User from " << source.toString() << " connected.");

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}

					if (callbackResult)
					{
						// Allow the connection
						newMessage = ObjectPool<NetworkMessage>::getSingleton().get(true);
						newMessage->setType(NetworkMessage::NM_ACK_CONNECT);
						newMessage->setDestination(source);
						pNetworkManager->sendNetworkMessage(source, newMessage);

						// Add the host to the list of connected hosts in the network manager
						pNetworkManager->addConnectedHost(pNetworkManager->createHostRecord(source.toString()));
					}
					break;
				case NetworkMessage::NM_DISCONNECT:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): User from " << source.toString() << " disconnected.");

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}

					if (callbackResult)
					{
						// Remove the user from the list of connected hosts
						pNetworkManager->removeConnectedHost(source.toString());
					}
					break;
				case NetworkMessage::NM_ACK_CONNECT:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Server at " << source.toString() << " acknowledges our connect request.");

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}

					if (callbackResult)
					{
						// Add the host to the list of connected hosts in the network manager
						pNetworkManager->addConnectedHost(pNetworkManager->createHostRecord(source.toString()));
					}
					break;
				case NetworkMessage::NM_ACK:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Received acknowledgement from " << source.toString() << ".");

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}
					break;
				case NetworkMessage::NM_PING:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Received ping from " << source.toString() << ". Sending pong...");
					pNetworkManager->sendPong(source);

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}
					break;
				case NetworkMessage::NM_PONG:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Received pong from " << source.toString() << ".");

					// Execute the associated callback, if any
					if (pCallback != NULL)
					{
						callbackResult = pCallback->executeCallback(message.get());
					}
					break;
				case NetworkMessage::NM_ENCAPSULATED_MESSAGE:
					LOG_DEBUG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Received message with encapsulated engine message from " << source.toString());
					try
					{
						processEncapsulatedMessage(message);
					}
					catch (Exception& e)
					{
						LOG(EngineLog::LM_ERROR, e.getMsg());
						return;
					}
					break;
				case NetworkMessage::NM_CREATE_OBJECT:
					LOG(EngineLog::LM_INFO_ENGINE, "P2PNetworkListenBehaviour::processReceivedMessage(): Received create object (instance: " << message->getObjectName() << ", class: " << message->getObjectClassName() << " from " << source.toString() << ".");
					try
					{
						readSize += processCreateObjectMessage(message, buffer + totalReadSize + readSize, length - totalReadSize - readSize);
					}
					catch (Exception& e)
					{
						LOG(EngineLog::LM_ERROR, e.getMsg());
						return;
					}
					break;
				case NetworkMessage::NM_UPDATE_OBJECT:
					try
					{
						readSize += processUpdateObjectMessage(message, buffer + totalReadSize + readSize, length - totalReadSize - readSize);
					}
					catch (Exception& e)
					{
						LOG(EngineLog::LM_ERROR, e.getMsg());
						return;
					}
					break;
				case NetworkMessage::NM_DESTROY_OBJECT:
					try
					{
						processDestroyObjectMessage(message);
					}
					catch (Exception& e)
					{
						LOG(EngineLog::LM_ERROR, e.getMsg());
						return;
					}
					break;
				case NetworkMessage::NM_UNKNOWN:
				default:
					LOG(EngineLog::LM_WARNING, "P2PNetworkListenBehaviour::processReceivedMessage(): received an unknown network message from: " << source.toString());
					return;
					break;
			}
			totalReadSize += readSize;
		} while (totalReadSize < length);
	}

	void P2PNetworkListenBehaviour::processEncapsulatedMessage(NetworkMessage *message) const throw (Exception)
	{
		Message *encapsulatedMessage;
		NetworkMessageCallbackBase *pCallback;
		bool callbackResult;

		if ((message == NULL) || (message->getEncapsulatedMessage() == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processEncapsulatedMessage(): message or encapsulated message is NULL.");
		}

		encapsulatedMessage = message->getEncapsulatedMessage()->clone();

		callbackResult = true;
		pCallback = const_cast<NetworkMessageCallbackBase *>(mNetworkMessageCallbacks[message->getType()].get());
		if (pCallback != NULL)
		{
			callbackResult = pCallback->executeCallback(message);
		}
		
		if (callbackResult)
		{
			// Send the message via the NotificationManager to the rest of the engine
			NotificationManager::getSingleton().queueNotification(encapsulatedMessage);
		}
	}

	int P2PNetworkListenBehaviour::processCreateObjectMessage(NetworkMessage *message, char *buffer, int length) const throw (Exception)
	{
		NamedObjectFactoryBase *objectFactory;
		NamedInstance *instance;
		NetworkMessageCallbackBase *pCallback;
		bool callbackResult;

		objectFactory = NULL;
		instance = NULL;

		if ((message == NULL) || (buffer == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processCreateObjectMessage(): message or buffer is NULL.");
		}

		callbackResult = true;
		pCallback = const_cast<NetworkMessageCallbackBase *>(mNetworkMessageCallbacks[message->getType()].get());
		if (pCallback != NULL)
		{
			callbackResult = pCallback->executeCallback(message);
		}
		
		if (!callbackResult)
		{
			return 0;
		}

		// Get the object factory that constructs objects of the specified type
		objectFactory = NamedObjectFactoryBase::getObjectFactoryFromClassName(message->getObjectClassName());
		if (objectFactory == NULL)
		{
			// If an object factory could not be found, try creating the object using the NamedObjectInstanceCreatorManager
			instance = static_cast<NamedInstance*>(NamedObjectInstanceCreatorManager::getSingleton().createInstance(message->getObjectClassName()));

			if (instance == NULL)
			{
				// Failed to create the object, throw an exception
				throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processCreateObjectMessage(): no object factory could be found and NamedObjectInstanceCreatorManager failed to create an instance for objects of type: " + message->getObjectClassName());
			}
		}
		else
		{
			// Create the object using its designated object factory
			instance = objectFactory->make(message->getObjectClassName(), message->getObjectName());

			if (instance == NULL)
			{
				// Failed to create the object, throw an exception
				throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processCreateObjectMessage(): The object factory failed to create an instance of type: " + message->getObjectClassName());
			}
		}

		// Populate the instance from the buffer
		return instance->populateInstance(buffer, length);
	}

	int P2PNetworkListenBehaviour::processUpdateObjectMessage(NetworkMessage *message, char *buffer, int length) const throw (Exception)
	{
		NamedObjectFactoryBase *objectFactory;
		NamedInstance *instance;		
		NetworkMessageCallbackBase *pCallback;
		bool callbackResult;

		objectFactory = NULL;
		instance = NULL;

		if ((message == NULL) || (buffer == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processUpdateObjectMessage(): message or buffer is NULL.");
		}

		callbackResult = true;
		pCallback = const_cast<NetworkMessageCallbackBase *>(mNetworkMessageCallbacks[message->getType()].get());
		if (pCallback != NULL)
		{
			callbackResult = pCallback->executeCallback(message);
		}
		
		if (!callbackResult)
		{
			return 0;
		}

		// Get the object factory that constructs objects of the specified type
		objectFactory = NamedObjectFactoryBase::getObjectFactoryFromClassName(message->getObjectClassName());
		if (objectFactory == NULL)
		{
			// Failed to create the object, throw an exception
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processUpdateObjectMessage(): no object factory could be found for objects of type: " + message->getObjectClassName());
		}
		else
		{
			// Get the object using its designated object factory
			instance = objectFactory->findByName(message->getObjectName());
		}

		if (instance == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processUpdateObjectMessage(): Couldn't find object with name: " + message->getObjectName() + " in object factory.");
		}

		// Populate the instance from the buffer
		return instance->populateInstance(buffer, length, Serializable::ST_NETWORK_UPDATE);
	}

	void P2PNetworkListenBehaviour::processDestroyObjectMessage(NetworkMessage *message) const throw (Exception)
	{
		NamedObjectFactoryBase *objectFactory;
		NamedInstance *instance;		
		NetworkMessageCallbackBase *pCallback;
		bool callbackResult;

		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processDestroyObjectMessage(): message or buffer is NULL.");
		}

		callbackResult = true;
		pCallback = const_cast<NetworkMessageCallbackBase *>(mNetworkMessageCallbacks[message->getType()].get());
		if (pCallback != NULL)
		{
			callbackResult = pCallback->executeCallback(message);
		}
		
		if (!callbackResult)
		{
			return;
		}

		// Get the object factory that constructs objects of the specified type
		objectFactory = NamedObjectFactoryBase::getObjectFactoryFromClassName(message->getObjectClassName());
		if (objectFactory == NULL)
		{
			// Failed to create the object, throw an exception
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processDestroyObjectMessage(): no object factory could be found for objects of type: " + message->getObjectClassName());
		}
		else
		{
			// Get the object using its designated object factory
			instance = objectFactory->findByName(message->getObjectName());
		}

		if (instance == NULL)
		{
			// Failed to create the object, throw an exception
			throw Exception(Exception::E_NULL_POINTER, "P2PNetworkListenBehaviour::processDestroyObjectMessage(): Couldn't find object with name: " + message->getObjectName() + " in object factory.");
		}

		// Destroy the object
		objectFactory->removeByName(message->getObjectName());
		delete instance;
	}

} // namespace Myoushu

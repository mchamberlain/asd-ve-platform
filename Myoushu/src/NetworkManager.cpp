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
 * @file NetworkManager.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "NetworkManager.h"
#include "NotificationManager.h"
#include "ObjectPool.h"
#include "NetworkListenTask.h"
#include "NetworkTransmitTask.h"
#include "ServerNetworkListenBehaviour.h"
#include "ClientNetworkListenBehaviour.h"

namespace Myoushu
{
	NetworkManager::NetworkManager()
	{
	}

	NetworkManager::~NetworkManager()
	{
	}

	void NetworkManager::sendNetworkMessage(Poco::Net::IPAddress destination, NetworkMessage *message) const throw (Exception)
	{
		// Ensure that message is not NULL
		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::sendNetworkMessage(): message is NULL.");
		}

		message->setDestination(destination);
		message->setSource(getLocalIP());
		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::sendNetworkMessage(const std::string& destination, NetworkMessage *message) const throw (Exception)
	{
		sendNetworkMessage(Poco::Net::IPAddress(destination), message);
	}

	void NetworkManager::sendNetworkMessageToAllConnectedHosts(NetworkMessage *message) const throw (Exception)
	{
		ConnectedHostsMapConstIterator iter;
		ConnectedHostsMapConstIterator endIter;

		// Ensure that message is not NULL
		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::sendNetworkMessage(): message is NULL.");
		}

		Poco::ScopedRWLock lock(mConnectedHostsRWLock, true);

		iter = mConnectedHosts.begin();
		endIter = mConnectedHosts.end();
		if (iter != endIter)
		{
			message->setSource(getLocalIP());
			message->setDestination(Poco::Net::IPAddress(iter->first));

			// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
			NotificationManager::getSingleton().queueNotification(message);
			++iter;
			for (; iter != endIter; ++iter)
			{
				NetworkMessage *newMessage;

				newMessage = message->clone();
				newMessage->setDestination(Poco::Net::IPAddress(iter->first));
				// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
				NotificationManager::getSingleton().queueNotification(newMessage);
			}
		}
	}

	void NetworkManager::sendPing(Poco::Net::IPAddress destination) const
	{
		NetworkMessage *message;

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->setType(NetworkMessage::NM_PING);
		message->setDestination(destination);
		message->setSource(getLocalIP());

		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::sendPing(const std::string& destination) const
	{
		sendPing(Poco::Net::IPAddress(destination));
	}

	void NetworkManager::sendPong(Poco::Net::IPAddress destination) const
	{
		NetworkMessage *message;

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->setType(NetworkMessage::NM_PONG);
		message->setDestination(destination);
		message->setSource(getLocalIP());

		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::sendPong(const std::string& destination) const
	{
		sendPong(Poco::Net::IPAddress(destination));
	}

	void NetworkManager::sendCreateObjectMessage(const std::string& destination, const std::string& instanceName, const std::string& className, Serializable *objectToCreate) const throw (Exception)
	{
		NetworkMessage *message;

		// Check that objectToCreate is not NULL
		if (objectToCreate == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::sendCreateObjectMessage(): objectToCreate is NULL!");
		}

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->setType(NetworkMessage::NM_CREATE_OBJECT);
		message->setDestination(Poco::Net::IPAddress(destination));
		message->setSource(getLocalIP());
		message->setObjectName(instanceName);
		message->setObjectClassName(className);
		message->setAttachedObject(objectToCreate);

		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::sendUpdateObjectMessage(const std::string& destination, const std::string& instanceName, const std::string& className, Serializable *objectToUpdate) const throw (Exception)
	{
		NetworkMessage *message;

		// Check that objectToCreate is not NULL
		if (objectToUpdate == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::sendUpdateObjectMessage(): objectToUpdate is NULL!");
		}

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->setType(NetworkMessage::NM_UPDATE_OBJECT);
		message->setDestination(Poco::Net::IPAddress(destination));
		message->setSource(getLocalIP());
		message->setObjectName(instanceName);
		message->setObjectClassName(className);
		message->setAttachedObject(objectToUpdate);

		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::sendDestroyObjectMessage(const std::string& destination, const std::string& name) const
	{
		NetworkMessage *message;

		// Check that objectToCreate is not NULL
		if (name.length() == 0)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "NetworkManager::sendDestroyObjectMessage(): The name of the object is empty!");
		}

		message = ObjectPool<NetworkMessage>::getSingleton().get(true);
		message->setType(NetworkMessage::NM_DESTROY_OBJECT);
		message->setDestination(Poco::Net::IPAddress(destination));
		message->setSource(getLocalIP());
		message->setObjectName(name);

		// Send the network message via the NotificationManager. It will be delivered to the NetworkTransmitTask for transmission.
		NotificationManager::getSingleton().queueNotification(message);
	}

	void NetworkManager::setNetworkListenBehaviour(NetworkListenBehaviour *pBehaviour) const throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that pBehaviour is not NULL
		if (pBehaviour == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The given behaviour is NULL!");
		}

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		pNetworkListenTask->setNetworkListenBehaviour(pBehaviour);
	}

	void NetworkManager::setClientNetworkListenBehaviour() const throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		pNetworkListenTask->setNetworkListenBehaviour(new ClientNetworkListenBehaviour());
	}

	void NetworkManager::setServerNetworkListenBehaviour() const throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		pNetworkListenTask->setNetworkListenBehaviour(new ServerNetworkListenBehaviour());
	}

	void NetworkManager::setP2PNetworkListenBehaviour() const throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		pNetworkListenTask->setNetworkListenBehaviour(new P2PNetworkListenBehaviour());
	}

	void NetworkManager::setP2PNetworkTransmitBehaviour() const throw (Exception)
	{
		NetworkTransmitTask *pNetworkTransmitTask;

		// Check that the NetworkTransmitTask instance exists
		pNetworkTransmitTask = NetworkTransmitTask::getSingletonPtr();
		if (pNetworkTransmitTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkTransmitBehaviour(): The NetworkTransmitTask does not exist!");
		}

		pNetworkTransmitTask->setNetworkTransmitBehaviour(new P2PNetworkTransmitBehaviour());
	}

	void NetworkManager::setNetworkTransmitBehaviour(NetworkTransmitBehaviour *pBehaviour) const throw (Exception)
	{
		NetworkTransmitTask *pNetworkTransmitTask;

		// Check that pBehaviour is not NULL
		if (pBehaviour == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkTransmitBehaviour(): The given behaviour is NULL!");
		}

		// Check that the NetworkTransmitTask instance exists
		pNetworkTransmitTask = NetworkTransmitTask::getSingletonPtr();
		if (pNetworkTransmitTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkTransmitBehaviour(): The NetworkTransmitTask does not exist!");
		}

		pNetworkTransmitTask->setNetworkTransmitBehaviour(pBehaviour);
	}

	const NetworkListenBehaviour* NetworkManager::getNetworkListenBehaviour() const throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		return pNetworkListenTask->getNetworkListenBehaviour();
	}

	const NetworkTransmitBehaviour* NetworkManager::getNetworkTransmitBehaviour() const throw (Exception)
	{
		NetworkTransmitTask *pNetworkTransmitTask;

		// Check that the NetworkTransmitTask instance exists
		pNetworkTransmitTask = NetworkTransmitTask::getSingletonPtr();
		if (pNetworkTransmitTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkTransmitBehaviour(): The NetworkTransmitTask does not exist!");
		}

		return pNetworkTransmitTask->getNetworkTransmitBehaviour();
	}

	NetworkListenBehaviour* NetworkManager::getNetworkListenBehaviour() throw (Exception)
	{
		NetworkListenTask *pNetworkListenTask;

		// Check that the NetworkListenTask instance exists
		pNetworkListenTask = NetworkListenTask::getSingletonPtr();
		if (pNetworkListenTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkListenBehaviour(): The NetworkListenTask does not exist!");
		}

		return pNetworkListenTask->getNetworkListenBehaviour();
	}

	NetworkTransmitBehaviour* NetworkManager::getNetworkTransmitBehaviour() throw (Exception)
	{
		NetworkTransmitTask *pNetworkTransmitTask;

		// Check that the NetworkTransmitTask instance exists
		pNetworkTransmitTask = NetworkTransmitTask::getSingletonPtr();
		if (pNetworkTransmitTask == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkManager::setNetworkTransmitBehaviour(): The NetworkTransmitTask does not exist!");
		}

		return pNetworkTransmitTask->getNetworkTransmitBehaviour();
	}

	Poco::Net::IPAddress NetworkManager::getHostIP(const std::string& hostName) const throw (Exception)
	{
		const Poco::Net::HostEntry &host = Poco::Net::DNS::hostByName(hostName);

		if (host.addresses().size() > 0)
		{
			return host.addresses()[0];
		}

		throw Exception(Exception::E_UNKNOWN_HOST, "NetworkManager::getHostIP(): host " + hostName + " could not be resolved.");
	}

	HostRecord NetworkManager::createHostRecord(const std::string& ipAddress) const
	{
		Poco::ScopedRWLock lock(mConnectedHostsRWLock, false);
		ConnectedHostsMap::const_iterator iter;

		iter = mConnectedHosts.find(ipAddress);
		if (iter != mConnectedHosts.end())
		{
			return iter->second;
		}

		//const Poco::Net::HostEntry &host = Poco::Net::DNS::hostByAddress(Poco::Net::IPAddress::parse(ipAddress));

		HostRecord hostRecord(Poco::Net::IPAddress(ipAddress), ipAddress);

		return hostRecord;		
	}

	void NetworkManager::addConnectedHost(const HostRecord& hostRecord)
	{
		Poco::ScopedRWLock lock(mConnectedHostsRWLock, true);
		ConnectedHostsMap::iterator iter;

		iter = mConnectedHosts.find(hostRecord.getIPAddress().toString());
		if (iter != mConnectedHosts.end())
		{
			LOG(EngineLog::LM_WARNING, "NetworkManager::addConnectedHost(): host record already exists, not adding.");
			return;
		}
		LOG(EngineLog::LM_WARNING, "NetworkManager::addConnectedHost(): adding " << hostRecord.getIPAddress().toString() << ".");
		mConnectedHosts.insert(std::pair<std::string, HostRecord>(hostRecord.getIPAddress().toString(), hostRecord));
	}

	bool NetworkManager::removeConnectedHost(const std::string& ipAddress)
	{
		ConnectedHostsMapIterator iter;

		Poco::ScopedRWLock lock(mConnectedHostsRWLock, true);

		iter = mConnectedHosts.find(ipAddress);

		if (iter == mConnectedHosts.end())
		{
			return false;
		}

		mConnectedHosts.erase(iter);

		return true;
	}

	void NetworkManager::removeAllConnectedHosts()
	{
		Poco::ScopedRWLock lock(mConnectedHostsRWLock, true);

		mConnectedHosts.clear();
	}

	bool NetworkManager::getConnectedHost(const std::string& ipAddress, HostRecord& hostRecord) const
	{
		ConnectedHostsMapConstIterator iter;

		Poco::ScopedRWLock lock(mConnectedHostsRWLock, false);

		iter = mConnectedHosts.find(ipAddress);

		if (iter == mConnectedHosts.end())
		{
			return false;
		}

		hostRecord = iter->second;

		return true;
	}

	void NetworkManager::getConnectedHosts(std::list<HostRecord>& connectedHosts) const
	{
		ConnectedHostsMapConstIterator iter;

		Poco::ScopedRWLock lock(mConnectedHostsRWLock, false);

		connectedHosts.clear();
		for (iter = mConnectedHosts.begin(); iter != mConnectedHosts.end(); ++iter)
		{
			connectedHosts.push_back(iter->second);
		}
	}

} // namespace Myoushu

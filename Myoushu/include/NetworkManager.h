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
 * @file NetworkManager.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef MYOUSHU_NETWORK_MANAGER
#define MYOUSHU_NETWORK_MANAGER

#include <map>

#include "Poco/RWLock.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/DNS.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Singleton.h"
#include "NetworkMessage.h"
#include "NetworkListenBehaviour.h"
#include "NetworkTransmitBehaviour.h"
#include "P2PNetworkListenBehaviour.h"
#include "P2PNetworkTransmitBehaviour.h"
#include "Exception.h"
#include "HostRecord.h"

namespace Myoushu
{
	/**
	 * Manager classes for the networking system in the engine. Controls the NetworkListen and NetworkTransmitTasks and can be used
	 * to set the current NetworkListenBehaviour or NetworkTransmitBehaviour classes.
	 */
	class MYOUSHU_API NetworkManager : public Ogre::Singleton<NetworkManager>
	{
		public:
			/** Type definition of a map of ip address strings to HostRecords. */
			typedef std::map<std::string, HostRecord> ConnectedHostsMap;
			/** Type definition of the iterator over a map of ip address strings to HostRecords. */
			typedef std::map<std::string, HostRecord>::iterator ConnectedHostsMapIterator;
			/** Type definition of the const_iterator over a map of ip address strings to HostRecords. */
			typedef std::map<std::string, HostRecord>::const_iterator ConnectedHostsMapConstIterator;

			/** Constructor */
			NetworkManager();

			/** Destructor */
			virtual ~NetworkManager();

			/**
			 * Sends the given NetworkMessage to the specified host.
			 * @param destination The IP Address of the host to send the message to.
			 * @param message The NetworkMessage instance to send, must not be NULL.
			 */
			void sendNetworkMessage(Poco::Net::IPAddress destination, NetworkMessage *message) const throw (Exception);

			/**
			 * Sends the given NetworkMessage to the specified host.
			 * @param destination The IP Address of the host to send the message to.
			 * @param message The NetworkMessage instance to send, must not be NULL.
			 */
			void sendNetworkMessage(const std::string& destination, NetworkMessage *message) const throw (Exception);

			/**
			 * Sends the given NetworkMessage to all connected hosts.
			 * @param message The NetworkMessage instance to send, must not be NULL.
			 */
			void sendNetworkMessageToAllConnectedHosts(NetworkMessage *message) const throw (Exception);

			/** Sends a ping NetworkMessage to the specified host. */
			void sendPing(Poco::Net::IPAddress destination) const;

			/** Sends a ping NetworkMessage to the specified host. */
			void sendPing(const std::string& destination) const;

			/** Sends a pong (response to a ping) NetworkMessage to the specified host. */
			void sendPong(Poco::Net::IPAddress destination) const;

			/** Sends a poing (response to a ping) NetworkMessage to the specified host. */
			void sendPong(const std::string& destination) const;

			/**
			 * Sends a message to a host instructing it to create the included object.
			 * @param destination The address or hostname of the host to send this message to.
			 * @param instanceName The name of the objectToCreate instance.
			 * @param className The class name of the objectToCreate instance.
			 * @param objectToCreate A pointer to the instance to be recreated on the host specified in destination.
			 * @throws Exception::E_NULL_POINTER if objectToCreate is NULL.
			 */
			void sendCreateObjectMessage(const std::string& destination, const std::string& instanceName, const std::string& className, Serializable *objectToCreate) const throw (Exception);

			/**
			 * Sends a message to a host instructing it to update the included object in its state.
			 * @param destination The address or hostname of the host to send this message to.
			 * @param instanceName The name of the objectToUpdate instance.
			 * @param className The class name of the objectToUpdate instance.
			 * @param objectToUpdate A pointer to the instance to be updated on the host specified in destination.
			 * @throws Exception::E_NULL_POINTER if objectToUpfate is NULL.
			 */
			void sendUpdateObjectMessage(const std::string& destination, const std::string& instanceName, const std::string& className, Serializable *objectToUpdate) const throw (Exception);

			/**
			 * Sends a message to a host instructing it to delete the included object in its state.
			 * @param destination The address or hostname of the host to send this message to.
			 * @param name The name of the instance to be deleted.
			 */
			void sendDestroyObjectMessage(const std::string& destination, const std::string& name) const;

			/** 
			 * Changes the behaviour of the NetworkListenTask to the specified behaviour.
			 * The NetworkListenTask will take ownership of the behaviour, so users should never
			 * manually free pBehaviour.
			 * @param pBehaviour The new NetworkListenBehaviour to use in the NetworkListenTask.
			 * @throws Exception::E_NULL_POINTER if the NetworkListenTask does not exist.
			 */
			void setNetworkListenBehaviour(NetworkListenBehaviour *pBehaviour) const  throw (Exception);

			/** 
			 * Changes the behaviour of the NetworkTransmitTask to the specified behaviour.
			 * The NetworkTransmitTask will take ownership of the behaviour, so users should never
			 * manually free pBehaviour.
			 * @param pBehaviour The new NetworkTransmitBehaviour to use in the NetworkTransmitTask.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			void setNetworkTransmitBehaviour(NetworkTransmitBehaviour *pBehaviour) const  throw (Exception);

			/** 
			 * Sets the NetworkListenBehaviour of the NetworkListenTask to the default ClientNetworkListenBehaviour.
			 * @throws Exception::E_NULL_POINTER if the NetworkListenTask does not exist.
			 */
			void setClientNetworkListenBehaviour() const throw (Exception);

			/** 
			 * Sets the NetworkListenBehaviour of the NetworkListenTask to the default ServerNetworkListenBehaviour.
			 * @throws Exception::E_NULL_POINTER if the NetworkListenTask does not exist.
			 */
			void setServerNetworkListenBehaviour() const throw (Exception);

			/** 
			 * Sets the NetworkListenBehaviour of the NetworkListenTask to the default P2PNetworkListenBehaviour.
			 * @throws Exception::E_NULL_POINTER if the NetworkListenTask does not exist.
			 */
			void setP2PNetworkListenBehaviour() const throw (Exception);

			/** 
			 * Sets the NetworkTransmitBehaviour of the NetworkTransmitTask to the default P2PNetworkTransmitBehaviour.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			void setP2PNetworkTransmitBehaviour() const throw (Exception);

			/** 
			 * Gets the currently set NetworkListenBehaviour instance.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			const NetworkListenBehaviour* getNetworkListenBehaviour() const throw (Exception);

			/** 
			 * Gets the currently set NetworkTransmitBehaviour instance.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			const NetworkTransmitBehaviour* getNetworkTransmitBehaviour() const throw (Exception);

			/**
			 * Gets the currently set NetworkListenBehaviour instance.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			NetworkListenBehaviour* getNetworkListenBehaviour() throw (Exception);

			/**
			 * Gets the currently set NetworkTransmitBehaviour instance.
			 * @throws Exception::E_NULL_POINTER if the NetworkTransmitTask does not exist.
			 */
			NetworkTransmitBehaviour* getNetworkTransmitBehaviour() throw (Exception);

			/** Gets the IP of the local host. */
			Poco::Net::IPAddress getLocalIP() const;

			/** 
			 * Gets the IP of the specified host name. 
			 * @throws Exception::E_UNKOWN_HOST if the specified hostName cannot be resolved.
			 */
			Poco::Net::IPAddress getHostIP(const std::string& hostName) const throw (Exception);

			/** Creates and returns a HostRecord from the specified ipAddress. */
			HostRecord createHostRecord(const std::string& ipAddress) const;

			/** Adds a host to the list of hosts that are connected to the same game as this host. */
			void addConnectedHost(const HostRecord& hostRecord);

			/** 
			 * Removes a host from the list of hosts that are connected to the same game as this host. 
			 * @param ipAddress of the host to remove.
			 * @return true if the host record was found and removed, false otherwise.
			 */
			bool removeConnectedHost(const std::string& ipAddress);

			/** Removes all connected hosts from the list of connected hosts. */
			void removeAllConnectedHosts();

			/** 
			 * Gets the HostRecord of a connected host via its IP address.
			 * @param ipAddress The IP address of the host to get the record for.
			 * @return true if the HostRecord could be found, false otherwise.
			 */
			bool getConnectedHost(const std::string& ipAddress, HostRecord& hostRecord) const;

			/**
			 * Get a list of all of the HostRecord instances of the connected hosts.
			 * @param connectedHosts Reference to a std::list to populate with all the connected hosts.
			 */
			void getConnectedHosts(std::list<HostRecord>& connectedHosts) const;

			/** Returns true if the host with the specified IP is in the list of connected hosts maintained by the NetworkManager. */
			bool isConnectedHost(const std::string& ipAddress) const;

			/** Gets the number of currently connected hosts. */
			unsigned int getNumberOfConnectedHosts() const;

			/**
			 * Gets the begin constant iterator over the map of connected hosts. Also gets a read lock
			 * on the map. The lock must be released with a call to releaseConnectedHostsIteratorAndLock() when
			 * finished with the iterator.
			 */
			ConnectedHostsMapConstIterator getConncetedHostsIteratorAndLock() const;

			/** Gets the end constant iterator over the map of connected hosts. */
			ConnectedHostsMapConstIterator getConncetedHostsEndIterator() const;

			/** Releases the read lock and iterator previously received from getConnectedHostsIteratorAndLock(). */
			void releaseConnectedHostsIteratorAndLock(ConnectedHostsMapConstIterator& iter) const;

		protected:
			/** Read/write mutex for thread safety on the mConnectedHosts map. */
			mutable Poco::RWLock mConnectedHostsRWLock;
			/** Map of IP addresses to hosts that are connected to the same game as this host. */
			ConnectedHostsMap mConnectedHosts;
	};

	// inlines
	inline Poco::Net::IPAddress NetworkManager::getLocalIP() const
	{
		const Poco::Net::HostEntry &thisHost = Poco::Net::DNS::thisHost();

		return thisHost.addresses()[0];
	}

	inline bool NetworkManager::isConnectedHost(const std::string& ipAddress) const
	{
		Poco::ScopedRWLock lock(mConnectedHostsRWLock, false);

		return (mConnectedHosts.find(ipAddress) != mConnectedHosts.end());
	}

	inline unsigned int NetworkManager::getNumberOfConnectedHosts() const
	{
		Poco::ScopedRWLock lock(mConnectedHostsRWLock, false);

		return mConnectedHosts.size();
	}

	inline NetworkManager::ConnectedHostsMapConstIterator NetworkManager::getConncetedHostsIteratorAndLock() const
	{
		mConnectedHostsRWLock.readLock();

		return mConnectedHosts.begin();
	}

	inline NetworkManager::ConnectedHostsMapConstIterator NetworkManager::getConncetedHostsEndIterator() const
	{
		return mConnectedHosts.end();
	}

	inline void NetworkManager::releaseConnectedHostsIteratorAndLock(NetworkManager::ConnectedHostsMapConstIterator& iter) const
	{
		mConnectedHostsRWLock.unlock();
	}

} // namespace Myoushu

#endif

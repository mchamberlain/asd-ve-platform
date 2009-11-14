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
 * @file NetworkListenBehaviour.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_NETWORK_LISTEN_BEHAVIOUR_H
#define MYOUSHU_NETWORK_LISTEN_BEHAVIOUR_H

#include "Poco/RWLock.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "NamedObject.h"
#include "NetworkMessageCallbackBase.h"
#include "NetworkMessageCallback.h"
#include "NetworkMessage.h"
#include "ActionStringClassCallback.h"

namespace Myoushu
{
	/**
	 * An abstract class that defines a function that must be implemented by subclasses. The function should
	 * process a message received over the network. Different subclass implementations can then exist for server
	 * (ServerNetworkListenBehaviour) and for clients (ClientNetworkListenBehaviour).
	 */
	class MYOUSHU_API NetworkListenBehaviour : public NamedObject<NetworkListenBehaviour>, public Poco::RefCountedObject
	{
		public:
			/** Nullary Constructor. */
			NetworkListenBehaviour();

			CLASS_NAME_FUNCTIONS(NetworkListenBehaviour);

			/**
			 * This method must process a message that was received over the network.
			 * @param source The host from which the message was received.
			 * @param buffer A character array containing the bytes of the message.
			 * @param length The length of the message in bytes, thus the length of the buffer array.
			 */
			virtual void processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length) = 0;

			/**
			 * Sets the callback for the specified NetworkMessageType.
			 * @param messageType The NetworkMessageType to set the callback for.
			 * @param pCallback The NetworkMessageCallbackBase instance to use as callback.
			 */
			void setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackBase *pCallback);

			/**
			 * Sets the callback for the specified NetworkMessageType.
			 * @param messageType The NetworkMessageType to set the callback for.
			 * @param pCallback The global function to use as callback.
			 */
			void setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackGlobalFunction pCallback);

			/**
			 * Sets the callback for the specified NetworkMessageType.
			 * @param messageType The NetworkMessageType to set the callback for.
			 * @param pCallback The LuaFunctor to use as callback.
			 */
			void setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackLuaFunctor *pCallback);

			/**
			 * Sets the callback for the specified NetworkMessageType.
			 * @param messageType The NetworkMessageType to set the callback for.
			 * @param callback The Lua function name to use as callback.
			 */
			void setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, const std::string& callback);

			/**
			 * Sets the callback for the specified NetworkMessageType.
			 * @param messageType The NetworkMessageType to set the callback for.
			 * @param pInstance The class instance containing the function to call.
			 * @param pCallback Pointer to the class function to use as callback.
			 */
			template<class C>
			void setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, C *pInstance, typename ActionStringClassCallback<bool, C, NetworkMessage>::ActionStringClassCallbackFunction pCallback);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** List of callbacks for all possible network message types. */
			Poco::AutoPtr<NetworkMessageCallbackBase> mNetworkMessageCallbacks[NetworkMessage::NM_UNKNOWN + 1];
	};

	// template implementations
	template<class C>
	inline void NetworkListenBehaviour::setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, C *pInstance, typename ActionStringClassCallback<bool, C, NetworkMessage>::ActionStringClassCallbackFunction pCallback)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNetworkMessageCallbacks[messageType] = new ActionStringClassCallback<bool, C, NetworkMessage>("", pInstance, pCallback);
	}

	// inlines
	inline void NetworkListenBehaviour::setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackBase *pCallback)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNetworkMessageCallbacks[messageType] = pCallback;
	}

	inline void NetworkListenBehaviour::setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackGlobalFunction pCallback)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNetworkMessageCallbacks[messageType] = new NetworkMessageCallback("", pCallback);
	}

	inline void NetworkListenBehaviour::setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, NetworkMessageCallbackLuaFunctor *pCallback)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNetworkMessageCallbacks[messageType] = new NetworkMessageCallback("", pCallback);
	}

	inline void NetworkListenBehaviour::setNetworkMessageCallback(NetworkMessage::NetworkMessageType messageType, const std::string& callback)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNetworkMessageCallbacks[messageType] = new NetworkMessageCallback("", callback);
	}
} // namespace Myoushu

#endif

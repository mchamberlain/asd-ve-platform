/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morn� Chamberlain & Stellenbosch University

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
 * @file P2PNetworkTransmitBehaviour.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_P2P_NETWORK_TRANSMIT_BEHAVIOUR
#define MYOUSHU_P2P_NETWORK_TRANSMIT_BEHAVIOUR

#include <set>

#include "NetworkTransmitBehaviour.h"
#include "NetworkMessage.h"
#include "InputMessage.h"

namespace Myoushu
{
	/**
	 * This class implements the NetworkTransmitBehaviour for a peer-to-peer based networking model.
	 */
	class MYOUSHU_API P2PNetworkTransmitBehaviour : public NetworkTransmitBehaviour
	{
		public:
			/** Nullary Constructor. */
			P2PNetworkTransmitBehaviour();

			/** Destructor */
			virtual ~P2PNetworkTransmitBehaviour();

			/**
			 * Initializes the behaviour. Typically this function would register the behaviour to receive various types of
			 * engine messages, including NetworkMessages.
			 */
			virtual void init();

			/**
			 * Process any queued (from the NotificationManager) messages, including NetworkMessages, and any other relevant logic and
			 * create a list of NetworkMessages that should be transmitted over the network.
			 */
			virtual void update();

			/** 
			 * This method is called for every NetworkMessage that is sent via the NotificationManager.
			 * The message queue is processed in the update() function.
			 * Relevant messages are queued and the NetworkTransmitTask transmits them.
			 * @param message The NetworkMessage that was sent.
			 */
			void receiveNetworkMessage(const Poco::AutoPtr<NetworkMessage>& message);

			/** 
			 * This method is called for every InputMessage that is sent via the NotificationManager.
			 * The message queue is processed in the update() function.
			 * Relevant messages are encapsulated in NetworkMessage which are then queued for transmission by the NetworkTransmitTask.
			 * @param message The NetworkMessage that was sent.
			 */
			void receiveInputMessage(const Poco::AutoPtr<InputMessage>& message);

			/** Adds an input action string to the list of input actions that are not to be propogated accross the network. */
			void addDisallowedInputAction(const std::string& inputActionStr);

			/** Removes an input action string from the list of input actions that are not to be propogated accross the network. */
			void removeDisallowedInputAction(const std::string& inputActionStr);

			/** Returns true if the specified input action string is in the list of input actions that are not propogated accross the network. */
			bool isDisallowedInputAction(const std::string& inputActionStr) const;

		protected:
			/** Read/write lock on mDisallowedInputActionSet */
			mutable Poco::RWLock mDisallowedInputActionSetRWLock;
			/** Set of input actions that should not be propogated accross the network. */
			std::set<std::string> mDisallowedInputActionSet;
	};

	inline void P2PNetworkTransmitBehaviour::addDisallowedInputAction(const std::string& inputActionStr)
	{
		Poco::ScopedRWLock lock(mDisallowedInputActionSetRWLock, true);

		mDisallowedInputActionSet.insert(inputActionStr);
	}

	inline void P2PNetworkTransmitBehaviour::removeDisallowedInputAction(const std::string& inputActionStr)
	{
		Poco::ScopedRWLock lock(mDisallowedInputActionSetRWLock, true);

		mDisallowedInputActionSet.erase(inputActionStr);
	}

	inline bool P2PNetworkTransmitBehaviour::isDisallowedInputAction(const std::string& inputActionStr) const
	{
		Poco::ScopedRWLock lock(mDisallowedInputActionSetRWLock, false);

		return (mDisallowedInputActionSet.find(inputActionStr) != mDisallowedInputActionSet.end());
	}

} // namespace Myoushu

#endif

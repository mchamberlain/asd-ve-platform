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
 * @file DefaultNetworkTransmitBehaviour.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_DEFAULT_NETWORK_TRANSMIT_BEHAVIOUR
#define MYOUSHU_DEFAULT_NETWORK_TRANSMIT_BEHAVIOUR

#include "NetworkTransmitBehaviour.h"

namespace Myoushu
{
	/**
	 * Default implementation of the NetworkTransmitBehaviour class. Mostly a stub implementation, does not really do anything.
	 */
	class MYOUSHU_API DefaultNetworkTransmitBehaviour : public NetworkTransmitBehaviour
	{
		public:
			/** Nullary Constructor. */
			DefaultNetworkTransmitBehaviour();

			/** Destructor */
			virtual ~DefaultNetworkTransmitBehaviour();

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
	};

} // namespace Myoushu

#endif

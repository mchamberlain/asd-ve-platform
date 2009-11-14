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
 * @file P2PNetworkListenBehaviour.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef MYOUSHU_P2P_NETWORK_LISTEN_BEHAVIOUR_H
#define MYOUSHU_P2P_NETWORK_LISTEN_BEHAVIOUR_H

#include "NetworkListenBehaviour.h"
#include "NetworkMessage.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class implements the NetworkListenBehaviour for a peer-to-peer based networking model.
	 */
	class MYOUSHU_API P2PNetworkListenBehaviour : public NetworkListenBehaviour, public NamedObject<P2PNetworkListenBehaviour>
	{
		public:
			/** Constructor */
			P2PNetworkListenBehaviour();

			/** Destructor */
			virtual ~P2PNetworkListenBehaviour();

			CLASS_NAME_FUNCTIONS(P2PNetworkListenBehaviour);

			/**
			 * This method must process a message that was received over the network.
			 * @param source The host from which the message was received.
			 * @param buffer A character array containing the bytes of the message.
			 * @param length The length of the message in bytes, thus the length of the buffer array.
			 */
			virtual void processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length);

		protected:
			/**
			 * Processes a received NetworkMessage instance that contains an encapsulated engine message. This
			 * method is called by processReceivedMessage when appropriate.
			 * @param message The NetworkMessage instance that was received, that contains an encapsulated engine message.
			 */
			void processEncapsulatedMessage(NetworkMessage *message) const throw (Exception);

			/**
			 * Processes a received NetworkMessage instance that is to create an object on this host. This method
			 * is called by processReceivedMessage.
			 * @param message The NetworkMessage instance that was received, that contains the create object message.
			 * @param buffer The remainder of the receive buffer starting just after the end of the NetworkMessage. This buffer
			 *				 will contain a serialized representation of the object to be created.
			 * @param length The size of the buffer.
			 * @return The number of bytes that were read from buffer.
			 */
			int processCreateObjectMessage(NetworkMessage *message, char *buffer, int length) const throw (Exception);

			/**
			 * Processes a received NetworkMessage instance that is to update an object on this host. This method
			 * is called by processReceivedMessage.
			 * @param message The NetworkMessage instance that was received, that contains the update object message.
			 * @param buffer The remainder of the receive buffer starting just after the end of the NetworkMessage. This buffer
			 *				 will contain a serialized representation of the updates that must be applied to the object.
			 * @param length The size of the buffer.
			 * @return The number of bytes that were read from buffer.
			 */
			int processUpdateObjectMessage(NetworkMessage *message, char *buffer, int length) const throw (Exception);

			/**
			 * Process a received NetworkMessage instance with a destroy object message. This method is called by
			 * processReceivedMessage.
			 * @param message the NetworkMessage instance that was received that contains the destroy object message.
			 */
			void processDestroyObjectMessage(NetworkMessage *message) const throw (Exception);

	};
} // namespace Myoushu

#endif

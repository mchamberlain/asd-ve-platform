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
 * @file DefaultNetworkListenBehaviour.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_DEFAULT_NETWORK_LISTEN_BEHAVIOUR_H
#define MYOUSHU_DEFAULT_NETWORK_LISTEN_BEHAVIOUR_H

#include "Platform.h"
#include "NetworkListenBehaviour.h"

namespace Myoushu
{
	/**
	 * An implementation of NetworkListenBehaviour. This method processes the generic part of messages sent between
	 * hosts. Subclasses of this class (ServerNetworkListenBehaviour and ClientNetworkListenBehaviour) implements full
	 * processing for messages received over the network.
	 */
	class MYOUSHU_API DefaultNetworkListenBehaviour : public NetworkListenBehaviour, public NamedObject<DefaultNetworkListenBehaviour>
	{
		public:
			/** Constructor. */
			DefaultNetworkListenBehaviour();

			/** Destructor */
			virtual ~DefaultNetworkListenBehaviour();

			CLASS_NAME_FUNCTIONS(DefaultNetworkListenBehaviour);

			/**
			 * This method processes a message that was received over the network. It handles the data that is
			 * common between any messages sent over the network by this engine.
			 * @param source The host from which the message was received.
			 * @param buffer A character array containing the bytes of the message.
			 * @param length The length of the message in bytes, thus the length of the buffer array.
			 */
			virtual void processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length);
	};
} // namespace Myoushu

#endif

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
 * @file ServerNetworkListenBehaviour.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_SERVER_NETWORK_LISTEN_BEHAVIOUR_H
#define MYOUSHU_SERVER_NETWORK_LISTEN_BEHAVIOUR_H

#include "Platform.h"
#include "DefaultNetworkListenBehaviour.h"

namespace Myoushu
{
	/**
	 * An implementation of NetworkListenBehaviour and extension of DefaultNetworkListenBehaviour. 
	 * This class provides methods to process received messages as the server of a networked game session.
	 */
	class MYOUSHU_API ServerNetworkListenBehaviour : public DefaultNetworkListenBehaviour, public NamedObject<ServerNetworkListenBehaviour>
	{
		public:
			/** Constructor. */
			ServerNetworkListenBehaviour();

			/** Destructor */
			virtual ~ServerNetworkListenBehaviour();

			CLASS_NAME_FUNCTIONS(ServerNetworkListenBehaviour);

			/**
			 * This method processes a message that was received over the network. It processes and responds
			 * to received messages as the server of a networked game session.
			 * @param source The host from which the message was received.
			 * @param buffer A character array containing the bytes of the message.
			 * @param length The length of the message in bytes, thus the length of the buffer array.
			 */
			virtual void processReceivedMessage(Poco::Net::IPAddress source, char *buffer, int length);
	};
} // namespace Myoushu

#endif

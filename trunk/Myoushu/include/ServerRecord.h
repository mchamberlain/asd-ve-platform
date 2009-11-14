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
 * @file ServerRecord.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_SERVER_RECORD_H
#define MYOUSHU_SERVER_RECORD_H

#include "Platform.h"
#include "HostRecord.h"

namespace Myoushu
{
	class MYOUSHU_API ServerRecord : public HostRecord, public NamedObject<ServerRecord>
	{
		public:
			/**
			 * Constructor. Populate the ServerRecord instance from a Poco::Net::HostEntry instance.
			 * @param hostEntry The Poco::Net::HostEntry instance to get the IP address and host name of the
			 *					server from.
			 */
			ServerRecord(const Poco::Net::HostEntry &hostEntry);

			/**
			 * Constructor. Sets the mIPAddress and name fields in this record to the specified values.
			 * @param ipAddress The IPAddress of the server.
			 * @param name The host name of the server.
			 */
			ServerRecord(const Poco::Net::IPAddress &ipAddress, const std::string &name);

			/** Destructor */
			virtual ~ServerRecord();

			CLASS_NAME_FUNCTIONS(ServerRecord);
	};

} // namespace Myoushu

#endif

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
 * @file HostRecord.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_HOST_RECORD_H
#define MYOUSHU_HOST_RECORD_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/HostEntry.h"

#include "Platform.h"
#include "NamedObject.h"
#include "NamedInstance.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * This class is used to store information about a host that is connected with the local host
	 * in a network session.
	 */
	class MYOUSHU_API HostRecord : public NamedObject<HostRecord>, public NamedInstance
	{
		public:
			/**
			 * Constructor. Populate the HostRecord instance from a Poco::Net::HostEntry instance.
			 * @param hostEntry The Poco::Net::HostEntry instance to get the IP address and host name of the
			 *					host from.
			 */
			HostRecord(const Poco::Net::HostEntry &hostEntry);

			/**
			 * Constructor. Sets the mIPAddress and name fields in this record to the specified values.
			 * @param ipAddress The IPAddress of the host.
			 * @param name The host name of the host.
			 */
			HostRecord(const Poco::Net::IPAddress &ipAddress, const std::string &name);

			/** Copy Constructor */
			HostRecord(const HostRecord& hostRecord);

			/** Nullary constructor, the name is set to "" and the IP address to "0.0.0.0". */
			HostRecord();

			/** Destructor */
			virtual ~HostRecord();

			CLASS_NAME_FUNCTIONS(HostRecord);

			/** Gets the host name of the host represented by this record. */
			std::string getHostName() const;

			/** Gets the IP address of the host represented by this record. */
			Poco::Net::IPAddress getIPAddress() const;

			/** Gets a pointer to the Poco::Socket instance currently used for communication with this host. */
			Poco::Net::StreamSocket getSocket();

			/** Gets a pointer to the Poco::Socket instance currently used for communication with this host. */
			Poco::Net::StreamSocket getSocket() const;

			/** Sets the Poco::Socket instance currently used for communication with this host. */
			void setSocket(Poco::Net::StreamSocket socket);

			/** Equality operator. */
			bool operator==(const HostRecord& rhs) const;

			/** Assignment operator. */
			HostRecord& operator=(const HostRecord& rhs);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The IP Address for the host represented by this record. */
			Poco::Net::IPAddress mIPAddress;
			/** 
			 * The Socket used for communication to this host. This can be NULL when
			 * using a connection-less protocol.
			 */
			Poco::Net::StreamSocket mSocket;
	};

	// inlines
	inline std::string HostRecord::getHostName() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return getName();
	}

	inline Poco::Net::IPAddress HostRecord::getIPAddress() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mIPAddress;
	}

	inline Poco::Net::StreamSocket HostRecord::getSocket()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSocket;
	}

	inline Poco::Net::StreamSocket HostRecord::getSocket() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSocket;
	}

	inline void HostRecord::setSocket(Poco::Net::StreamSocket socket)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mSocket = socket;
	}

} // namespace Myoushu

#endif

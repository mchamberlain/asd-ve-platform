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
 * @file HostRecord.cpp
 * @author ME Chamberlain
 * @date November 2008
 */

#include "HostRecord.h"

namespace Myoushu
{
	CLASS_NAME(HostRecord, "Myoushu::HostRecord");

	HostRecord::HostRecord(const Poco::Net::HostEntry &hostEntry) : NamedInstance(hostEntry.name()), mIPAddress(hostEntry.addresses().front()), mSocket()
	{
	}

	HostRecord::HostRecord(const Poco::Net::IPAddress &ipAddress, const std::string &name) : NamedInstance(name), mIPAddress(ipAddress), mSocket()
	{
	}

	HostRecord::HostRecord(const HostRecord& hostRecord) : NamedInstance(hostRecord.getHostName()), mIPAddress(hostRecord.getIPAddress()), mSocket(hostRecord.getSocket())
	{
	}

	HostRecord::HostRecord() : NamedInstance("")
	{
	}

	HostRecord::~HostRecord()
	{
	}

	bool HostRecord::operator==(const HostRecord& rhs) const
	{
		return ((mIPAddress == rhs.getIPAddress()) && (getHostName() == rhs.getHostName()));
	}

	HostRecord& HostRecord::operator=(const HostRecord& rhs)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mIPAddress = rhs.getIPAddress();
		setName(rhs.getHostName());
		mSocket = rhs.getSocket();

		return *this;
	}

} // namespace Myoushu

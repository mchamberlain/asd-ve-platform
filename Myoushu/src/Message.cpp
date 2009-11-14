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
 * @file Message.h
 * @author ME Chamberlain
 * @date April 2008
 */

#include "Message.h"
#include "NetworkManager.h"

namespace Myoushu
{
	CLASS_NAME(Message, "Myoushu::Message");

	Message::Message() : Poco::Notification(new PoolObjectReferenceCounter()), mCreator(NetworkManager::getSingleton().getLocalIP())
	{
	}

	Message::~Message()
	{
	}

	Message& Message::operator=(const Message& message)
	{
		// Clone the mCreator field
		mCreator = message.getCreator();

		return *this;
	}

	void Message::clear()
	{
		mCreator = NetworkManager::getSingleton().getLocalIP();
	}

	memUInt Message::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		memUInt pBuf;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Message::serialize(): pMem is NULL!");
		}

		writtenSize = 0;
		totalSize = 0;
		pBuf = reinterpret_cast<memUInt>(pMem);

		writtenSize = writeString(mCreator.toString(), reinterpret_cast<void*>(pBuf));
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Message::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt Message::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		memUInt pBuf;
		std::string addr;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Message::populateInstance(): pMem is NULL!");
		}

		readSize = 0;
		totalSize = 0;
		pBuf = reinterpret_cast<memUInt>(pMem);

		readSize = readString(addr, reinterpret_cast<void*>(pBuf));
		setCreator(addr);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Message::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // Myoushu

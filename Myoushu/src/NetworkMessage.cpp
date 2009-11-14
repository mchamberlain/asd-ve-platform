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
 * @file NetworkMessage.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "NetworkMessage.h"
#include "ObjectPool.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(NetworkMessage, "Myoushu::NetworkMessage");

	NetworkMessage::NetworkMessage() : mType(NM_UNKNOWN), mEncapsulatedMessage(NULL), mObjectName(""), mObjectClassName(""), pAttachedObject(NULL)
	{
	}

	NetworkMessage::NetworkMessage(NetworkMessageType type) : mType(type), mEncapsulatedMessage(NULL), mObjectName(""), mObjectClassName(""), pAttachedObject(NULL)
	{
	}

	NetworkMessage::~NetworkMessage()
	{
	}

	void NetworkMessage::clear()
	{
		Message::clear();

		mType = NM_UNKNOWN;
		mEncapsulatedMessage = NULL;
		mSource = Poco::Net::IPAddress::parse("0.0.0.0");
		mDestination = Poco::Net::IPAddress::parse("0.0.0.0");
		mObjectName = "";
		mObjectClassName = "";
		pAttachedObject = NULL;
	}

	void NetworkMessage::clone(NetworkMessage *dest) const throw (Exception)
	{
		Message *destMessage;

		// Ensure that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkMessage::clone(): dest is NULL.");
		}

		Poco::ScopedRWLock lock(rwLock, false);

		destMessage = static_cast<Message*>(dest);
		(*destMessage) = *this;

		dest->setType(mType);
		//dest->setEncapsulatedMessage(mEncapsulatedMessage);
		dest->setSource(mSource);
		dest->setDestination(mDestination);
		dest->setObjectName(mObjectName);
		dest->setObjectClassName(mObjectClassName);
		dest->setAttachedObject(pAttachedObject);
	}

	NetworkMessage* NetworkMessage::clone() const
	{
		NetworkMessage *newMsg;

		//newMsg = new NetworkMessage();
		newMsg = ObjectPool<NetworkMessage>::getSingleton().get(true);
		clone(newMsg);

		return newMsg;
	}

	NetworkMessage& NetworkMessage::operator=(const NetworkMessage& message)
	{
		Message::operator=(message);

		message.clone(this);

		return *this;
	}

	memUInt NetworkMessage::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		char *pBuf;
		memUInt totalSize;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkMessage::serialize(): pMem is NULL!");
		}

		writtenSize = 0;
		totalSize = 0;
		pBuf = static_cast<char*>(pMem);

		// Serialize the instance into the buffer pMem.

		// Call Message's serialize
		writtenSize = Message::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, false);

		writtenSize = writePrimitiveType(mType, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		writtenSize = writeString(mDestination.toString(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		writtenSize = writeString(mSource.toString(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		// First write the class name of the encapsulated message to indicate what class it is. Also if mEncapsulatedMessage is NULL
		// we write the empty string "" to indicate the NULL value.
		if (mEncapsulatedMessage.get() != NULL)
		{
			writtenSize = writeString(mEncapsulatedMessage->getClassName(), pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
			}

			writtenSize = mEncapsulatedMessage->serialize(pBuf, size - (totalSize), sTarget);
		}
		else
		{
			writtenSize = writeString("", pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		// Write mObjectName
		writtenSize = writeString(mObjectName, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		// Write mObjectClassName
		writtenSize = writeString(mObjectClassName, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
		}

		// Serialize the attached object if applicable
		if (pAttachedObject != NULL)
		{
			if (mType == NM_UPDATE_OBJECT)
			{
				writtenSize = pAttachedObject->serialize(pBuf, size - totalSize, ST_NETWORK_UPDATE);
			}
			else
			{
				writtenSize = pAttachedObject->serialize(pBuf, size - totalSize, sTarget);
			}
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::serialize(): buffer too small.");
			}
		}

		return totalSize;
	}

	memUInt NetworkMessage::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		std::string className;
		std::string addr;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NetworkMessage::populateInstance(): pMem is NULL!");
		}

		readSize = 0;
		totalSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// Populate the instance from the buffer pMem.

		// Call Message's populateInstance
		readSize = Message::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, true);

		readSize = readPrimitiveType(mType, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}

		readSize = readString(addr, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}
		mDestination = Poco::Net::IPAddress::parse(addr);

		readSize = readString(addr, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}
		mSource = Poco::Net::IPAddress::parse(addr);

		readSize = readString(className, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}

		if (className.length() > 0)
		{
			// Get the object pool that creates message instances of the specified class name
			ObjectPoolBase *pool;
			pool = ObjectPoolBase::getObjectPoolFromClassName(className);

			if (pool == NULL)
			{
				// Log an error, we do not support the message type
				LOG(EngineLog::LM_ERROR, "NetworkMessage::populateInstance(): cannot instantiate class of type: " << className);
			}
			else
			{
				mEncapsulatedMessage = STATIC_CAST_PTR(Message*, PoolObject*, pool->get(true));
				if (mEncapsulatedMessage.get() == NULL)
				{
					LOG(EngineLog::LM_ERROR, "NetworkMessage::populateInstance(): failed to instantiate class of type: " << className);
				}
				else
				{
					// populate the encapsulated message from the buffer
					readSize = mEncapsulatedMessage->populateInstance(pBuf, size - totalSize, sTarget);
					pBuf += readSize;
					totalSize += readSize;
				}
			}
		}
		else
		{
			mEncapsulatedMessage = NULL;
		}

		// Read mObjectName
		readSize = readString(mObjectName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}

		// Read mObjectClassName
		readSize = readString(mObjectClassName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NetworkMessage::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // namespace Myoushu

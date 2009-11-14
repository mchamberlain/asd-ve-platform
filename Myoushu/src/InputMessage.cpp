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
 * @file InputMessage.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "InputMessage.h"
#include "NetworkManager.h"
#include "ObjectPool.h"

namespace Myoushu
{

	CLASS_NAME(InputMessage, "Myoushu::InputMessage");

	const std::string InputMessage::NO_ACTION = "None";

	InputMessage::InputMessage(InputDevice *inputDevice) : InputDeviceMessage(inputDevice), inputAction(NO_ACTION)
	{
	}

	InputMessage::InputMessage(InputDevice *inputDevice, DeviceAction deviceAction, const std::string& inputAction, InputDevice::InputDeviceType deviceType,
		const int deviceState[DEVICE_STATE_LENGTH], const Ogre::Vector3& actionVector, const std::string inputIdentifiers[MAX_NUMBER_OF_INPUT_IDENTIFIERS]) throw (Exception)
														 : InputDeviceMessage(inputDevice, deviceAction, deviceType, deviceState, actionVector, inputIdentifiers), inputAction(inputAction)
	{
	}

	InputMessage::~InputMessage()
	{
	}


	void InputMessage::clear()
	{
		InputDeviceMessage::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Initialize everything to their zero values
		inputAction = NO_ACTION;
	}

	InputMessage& InputMessage::operator=(const InputMessage& message)
	{
		message.clone(this);

		return *this;
	}

	InputMessage& InputMessage::operator=(const InputDeviceMessage& message)
	{
		message.clone(static_cast<InputDeviceMessage*>(this));

		return *this;
	}

	void InputMessage::clone(InputMessage *dest) const throw (Exception)
	{
		unsigned int i;
		InputDeviceMessage *destMessage;

		Poco::ScopedRWLock lock(rwLock, false);

		// Check that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputMessage::clone(): dest is NULL.");
		}

		destMessage = static_cast<InputDeviceMessage*>(dest);
		(*destMessage) = *this;

		dest->setInputAction(inputAction);
	}

	InputMessage* InputMessage::clone() const
	{
		InputMessage *newMsg;

		Poco::ScopedRWLock lock(rwLock, false);

		//newMsg = new InputMessage(inputDevice);
		newMsg = ObjectPool<InputMessage>::getSingleton().get(true);
		clone(newMsg);

		return newMsg;
	}

	memUInt InputMessage::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		char *pBuf;
		memUInt totalSize;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputMessage::serialize(): pMem is NULL!");
		}

		writtenSize = 0;
		totalSize = 0;
		pBuf = static_cast<char*>(pMem);

		// Serialize the instance into the buffer pMem.

		// Call InputDeviceMessage's serialize
		writtenSize = InputDeviceMessage::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputMessage::serialize(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, false);

		// If the serialization is for network transmission (sTarget == ST_NETWORK) then we append the local IP to the inputAction to ensure
		// that it is unique on the target host and identifiable as belonging to this host
		if (sTarget == ST_NETWORK)
		{
			writtenSize = writeString(inputAction + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
		}
		else
		{
			writtenSize = writeString(inputAction, pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputMessage::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt InputMessage::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char* pBuf;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputMessage::populateInstance(): pMem is NULL!");
		}

		readSize = 0;
		totalSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// Populate the instance from the buffer pMem.

		// Call InputDeviceMessage's populateInstance
		readSize = InputDeviceMessage::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputMessage::populateInstance(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, true);

		readSize = readString(inputAction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputMessage::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // Myoushu

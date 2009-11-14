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
 * @file InputDeviceMessage.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "InputDeviceMessage.h"
#include "InputDevice.h"
#include "Exception.h"
#include "ObjectPool.h"
#include "NetworkManager.h"

namespace Myoushu
{

	CLASS_NAME(InputDeviceMessage, "Myoushu::InputDeviceMessage");

	const unsigned int InputDeviceMessage::DS_BUTTON_INDEX = 0;
	const unsigned int InputDeviceMessage::DS_BUTTONS_STATE_INDEX = 1;
	const unsigned int InputDeviceMessage::DS_X_INDEX = 2;
	const unsigned int InputDeviceMessage::DS_Y_INDEX = 3;
	const unsigned int InputDeviceMessage::DS_Z_INDEX = 4;
	const unsigned int InputDeviceMessage::DS_X_REL_INDEX = 5;
	const unsigned int InputDeviceMessage::DS_Y_REL_INDEX = 6;
	const unsigned int InputDeviceMessage::DS_Z_REL_INDEX = 7;

	InputDeviceMessage::InputDeviceMessage(InputDevice *inputDevice) : inputDevice(inputDevice)
	{
		unsigned int i;

		Poco::ScopedRWLock lock(rwLock, true);

		// Initialize everything to their zero values
		deviceAction = DA_PRESS;
		deviceType = InputDevice::IDT_KEYBOARD;

		// Initialize the deviceState array
		for (i = 0; i < DEVICE_STATE_LENGTH; i++)
		{
			deviceState[i] = 0;
		}

		actionVector = Ogre::Vector3::ZERO;

		// Initialize the inputIdentifiers array
		for (i = 0; i < MAX_NUMBER_OF_INPUT_IDENTIFIERS; i++)
		{
			inputIdentifiers[i] = "";
		}
	}

	InputDeviceMessage::InputDeviceMessage(InputDevice *inputDevice, DeviceAction deviceAction, InputDevice::InputDeviceType deviceType,
		const int deviceState[DEVICE_STATE_LENGTH], const Ogre::Vector3& actionVector, const std::string inputIdentifiers[MAX_NUMBER_OF_INPUT_IDENTIFIERS]) throw (Exception)
														 : inputDevice(inputDevice), deviceAction(deviceAction), deviceType(deviceType)
	{
		unsigned int i;

		Poco::ScopedRWLock lock(rwLock, true);

		if (deviceState == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceMessage::InputDeviceMessage(): deviceState is NULL.");
		}

		// Copy the deviceState array
		for (i = 0; i < DEVICE_STATE_LENGTH; i++)
		{
			this->deviceState[i] = deviceState[i];
		}

		// Copy the actionVector
		this->actionVector = actionVector;

		// Copy the inputIdentifiers array
		for (i = 0; i < MAX_NUMBER_OF_INPUT_IDENTIFIERS; i++)
		{
			this->inputIdentifiers[i] = inputIdentifiers[i];
		}
	}

	InputDeviceMessage::~InputDeviceMessage()
	{
	}

	Ogre::Real InputDeviceMessage::getActionVector(unsigned int index) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (index >= 3)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "InputDeviceMessage::getActionVector(): index out of bounds.");
		}

		return actionVector[index];
	}

	int InputDeviceMessage::getDeviceState(unsigned int index) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (index >= DEVICE_STATE_LENGTH)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "InputDeviceMessage::setDeviceState(): index out of bounds.");
		}

		return deviceState[index];
	}

	void InputDeviceMessage::setDeviceState(unsigned int index, int value) throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (index >= DEVICE_STATE_LENGTH)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "InputDeviceMessage::setDeviceState(): index out of bounds.");
		}

		deviceState[index] = value;
	}

	void InputDeviceMessage::setActionVector(unsigned int index, Ogre::Real value) throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (index >= DEVICE_STATE_LENGTH)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "InputDeviceMessage::setActionVector(): index out of bounds.");
		}

		actionVector[index] = value;
	}

	void InputDeviceMessage::clear()
	{
		unsigned int i;

		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Initialize everything to their zero values
		inputDevice = NULL;
		deviceAction = DA_PRESS;
		deviceType = InputDevice::IDT_KEYBOARD;

		// Initialize the deviceState array
		for (i = 0; i < DEVICE_STATE_LENGTH; i++)
		{
			deviceState[i] = 0;
		}

		actionVector = Ogre::Vector3::ZERO;

		// Initialize the inputIdentifiers array
		for (i = 0; i < MAX_NUMBER_OF_INPUT_IDENTIFIERS; i++)
		{
			inputIdentifiers[i] = "";
		}
	}

	InputDeviceMessage& InputDeviceMessage::operator=(const InputDeviceMessage& message)
	{
		message.clone(this);

		return *this;
	}

	void InputDeviceMessage::clone(InputDeviceMessage *dest) const throw (Exception)
	{
		unsigned int i;
		Message *destMessage;

		Poco::ScopedRWLock lock(rwLock, false);

		// Check that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceMessage::clone(): dest is NULL.");
		}

		destMessage = static_cast<Message*>(dest);
		(*destMessage) = *this;

		dest->setInputDevice(inputDevice);
		dest->setDeviceAction(deviceAction);
		dest->setDeviceType(deviceType);

		for (i = 0; i < DEVICE_STATE_LENGTH; i++)
		{
			dest->setDeviceState(i, deviceState[i]);
		}

		dest->setActionVector(actionVector);

		for (i = 0; i < MAX_NUMBER_OF_INPUT_IDENTIFIERS; i++)
		{
			dest->setInputIdentifier(i, inputIdentifiers[i]);
		}
	}

	InputDeviceMessage* InputDeviceMessage::clone() const
	{
		InputDeviceMessage *newMsg;

		Poco::ScopedRWLock lock(rwLock, false);

		//newMsg = new InputDeviceMessage(inputDevice);
		newMsg = ObjectPool<InputDeviceMessage>::getSingleton().get(true);
		newMsg->setInputDevice(inputDevice);
		clone(newMsg);

		return newMsg;
	}

	memUInt InputDeviceMessage::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		char *pBuf;
		memUInt totalSize;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceMessage::serialize(): pMem is NULL!");
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
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, false);

		writtenSize = writePrimitiveType(deviceAction, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(deviceType, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveTypeArray(deviceState, DEVICE_STATE_LENGTH, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		writtenSize = writeOgreVector3(actionVector, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		writtenSize = writeStringArray(inputIdentifiers, MAX_NUMBER_OF_INPUT_IDENTIFIERS, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt InputDeviceMessage::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char* pBuf;

		// Ensure that pMem is not NULL
		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceMessage::populateInstance(): pMem is NULL!");
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
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		Poco::ScopedRWLock lock(rwLock, true);

		// Set the input device to NULL
		inputDevice = NULL;

		readSize = readPrimitiveType(deviceAction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(deviceType, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveTypeArray(deviceState, DEVICE_STATE_LENGTH, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (readSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		readSize = readOgreVector3(actionVector, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		readSize = readStringArray(inputIdentifiers, MAX_NUMBER_OF_INPUT_IDENTIFIERS, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "InputDeviceMessage::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // Myoushu

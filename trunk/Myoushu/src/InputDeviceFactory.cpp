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
 * @file InputDeviceFactory.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <list>
#include <iostream>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"
#include "OIS.h"

#include "Platform.h"
#include "InputDeviceFactory.h"
#include "Exception.h"
#include "KeyboardOISInputDevice.h"
#include "MouseOISInputDevice.h"

//template<>
//Myoushu::InputDeviceFactory* Ogre::Singleton<Myoushu::InputDeviceFactory>::ms_Singleton = NULL;

namespace Myoushu
{
	InputDeviceFactory::InputDeviceFactory()
	{
	}

	InputDeviceFactory::~InputDeviceFactory()
	{
		// Clear the devices list. Since we use Poco::AutoPtr the instances will automatically be freed
		devices.clear();
	}

	Poco::AutoPtr<KeyboardOISInputDevice> InputDeviceFactory::make(OIS::Keyboard *oisKeyboard, const std::string& name) throw (Exception)
	{
		Poco::AutoPtr<KeyboardOISInputDevice> newDevice;
		DevicesIterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		if (oisKeyboard == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceFactory::make(): oisKeyboard is NULL.");
		}

		newDevice = NULL;
		// Search for a conflicting or existing device
		for (iter = devices.begin(); ((iter != devices.end()) && (newDevice.get() == NULL)); ++iter)
		{
			if ((*iter)->getName() == name)
			{
				newDevice = (*iter).cast<KeyboardOISInputDevice>();
				// Check if it is the same device, if not throw an exception otherwise return the found instance
				if ((newDevice.get() == NULL) || (newDevice->getOISDevice() != oisKeyboard))
				{
					throw Exception(Exception::E_INVALID_PARAMETERS, "InputDeviceFactory::make(): Device with same name but different OIS::Object already exists.");
				}
			}
		}

		// No existing device found, create a new one
		if (newDevice.get() == NULL)
		{
			newDevice = new KeyboardOISInputDevice(name, oisKeyboard);
			devices.push_back(newDevice);
		}

		return newDevice;
	}

	Poco::AutoPtr<MouseOISInputDevice> InputDeviceFactory::make(OIS::Mouse *oisMouse, const std::string& name) throw (Exception)
	{
		Poco::AutoPtr<MouseOISInputDevice> newDevice;
		DevicesIterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		if (oisMouse == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputDeviceFactory::make(): oisMouse is NULL.");
		}

		newDevice = NULL;
		// Search for a conflicting or existing device
		for (iter = devices.begin(); ((iter != devices.end()) && (newDevice.get() == NULL)); ++iter)
		{
			if ((*iter)->getName() == name)
			{
				newDevice = (*iter).cast<MouseOISInputDevice>();
				// Check if it is the same device, if not throw an exception otherwise return the found instance
				if ((newDevice.get() == NULL) || (newDevice->getOISDevice() != oisMouse))
				{
					throw Exception(Exception::E_INVALID_PARAMETERS, "InputDeviceFactory::make(): Device with same name but different OIS::Object already exists.");
				}
			}
		}

		// No existing device found, create a new one
		if (newDevice.get() == NULL)
		{
			newDevice = new MouseOISInputDevice(name, oisMouse);
			devices.push_back(newDevice);
		}

		return newDevice;
	}

	const Poco::AutoPtr<InputDevice> InputDeviceFactory::getInputDevice(const std::string& name) const
	{
		DevicesConstIterator iter;

		for (iter = devices.begin(); iter != devices.end(); ++iter)
		{
			if ((*iter)->getName() == name)
			{
				return *iter;
			}
		}

		return NULL;
	}
} // Myoushu

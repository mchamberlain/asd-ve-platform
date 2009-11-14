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
 * @file InputDeviceFactory.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_DEVICE_FACTORY_H
#define INPUT_DEVICE_FACTORY_H

#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"
#include "OIS.h"

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "KeyboardOISInputDevice.h"
#include "MouseOISInputDevice.h"

namespace Myoushu
{
	/**
	 * A factory that creates various InputDevice instances through its make methods.
	 */
	class MYOUSHU_API InputDeviceFactory : public Ogre::Singleton<InputDeviceFactory>
	{
		public:
			/**
			 * std::list InputDevice iterator
			 */
			typedef std::list<Poco::AutoPtr<InputDevice> >::iterator DevicesIterator;
			typedef std::list<Poco::AutoPtr<InputDevice> >::const_iterator DevicesConstIterator;

			/**
			 * Nullary Constructor.
			 */
			InputDeviceFactory();

			/**
			 * Destructor
			 */
			~InputDeviceFactory();

			/**
			 * Create a new KeyboardInputDevice with the given parameters. If a device with the same
			 * parameters already exist the existing one is returned and a new instance is not created.
			 * @param oisKeyboard A pointer to the OIS::Keyboard instance associated with the device.
			 * @param name The name of the device. This is used to identify the device/instance.
			 * @return A KeyboardInputDevice instance.
			 * @throw Exception::E_NULL_POINTER If oisKeyboard is NULL.
			 * @throw Exception::E_INVALID_PARAMETERS If a device with the same name already exists but the oisKeyboard instance differs.
			 */
			Poco::AutoPtr<KeyboardOISInputDevice> make(OIS::Keyboard *oisKeyboard, const std::string& name) throw (Exception);

			/**
			 * Create a new MouseInputDevice with the given parameters. If a device with the same
			 * parameters already exist the existing one is returned and a new instance is not created.
			 * @param oisMouse A pointer to the OIS::Mouse instance associated with the device.
			 * @param name The name of the device. This is used to identify the device/instance.
			 * @return A MouseInputDevice instance.
			 * @throw Exception::E_NULL_POINTER If oisMouse is NULL.
			 * @throw Exception::E_INVALID_PARAMETERS If a device with the same name already exists but the oisMouse instance differs.
			 */
			Poco::AutoPtr<MouseOISInputDevice> make(OIS::Mouse *oisMouse, const std::string& name) throw (Exception);

			/**
			 * Gets a constant pointer to the specified input device.
			 * @param name The name of the device instance.
			 * @return The InputDevice or NULL if no device was found.
			 */
			const Poco::AutoPtr<InputDevice> getInputDevice(const std::string& name) const;

			/**
			 * Get the DevicesIterator that points to the first element in the list.
			 * @return DevicesIterator that points to the first element in the list.
			 */
			inline DevicesIterator getDevicesIteratorBegin()
			{
				return devices.begin();
			}

			/**
			 * Get the DevicesIterator that points just past the last element in the list.
			 * @return DevicesIterator that points just past the last element in the list.
			 */
			inline DevicesIterator getDevicesIteratorEnd()
			{
				return devices.end();
			}

			/**
			 * Get the DevicesConstIterator that points to the first element in the list.
			 * @return DevicesConstIterator that points to the first element in the list.
			 */
			inline DevicesConstIterator getDevicesConstIteratorBegin() const
			{
				return devices.begin();
			}

			/**
			 * Get the DevicesConstIterator that points just past the last element in the list.
			 * @return DevicesConstIterator that points just past the last element in the list.
			 */
			inline DevicesConstIterator getDevicesConstIteratorEnd() const
			{
				return devices.end();
			}

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** List of InputDevices */
			std::list<Poco::AutoPtr<InputDevice> > devices;
	};
} // Myoushu

#endif

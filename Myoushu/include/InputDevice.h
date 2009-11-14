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
 * @file InputDevice.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class serves as a base class for a generic input device system.
	 * Input devices can be any device that gives input to in game entities,
	 * like keyboards and mice, or an AI system.
	 */
	class MYOUSHU_API InputDevice : public Poco::RefCountedObject
	{
		public:
			/** A List of input device types, like keyboard, mouse etc. */
			enum InputDeviceType
			{
				/** Indicates a device is a keyboard. */
				IDT_KEYBOARD,
				/** Indicates a device is a mouse. */
				IDT_MOUSE,
				/** Indicates a device is a gamepad. */
				IDT_GAMEPAD,
				/** Indicates an unknown devce */
				IDT_UNKNOWN
			};

			/**
			 * Constructor.
			 * @param name The name of this instance.
			 * @param deviceType The device type.
			 */
			InputDevice(const std::string& name, InputDeviceType deviceType) : name(name), deviceType(deviceType)
			{
			}

			/**
			 * Destructor
			 */
			~InputDevice()
			{
			}

			/**
			 * This method should update the device and create and queue InputMessages based on the
			 * state of the device.
			 */
			virtual void capture() = 0;

			/**
			 * Returns the input event string for an input event. It returns a string of the format
			 * input.devicename.inputIdentifier.
			 * @param inputIdentifier The input identifier. This is a simple string identifying the key, 
			 *						  button or axis on the device. Classes should define constants 
			 *						  containing these strings. These are not the actual key codes, 
			 *						  input device classes maintain maps between these input identifier
			 *						  strings and the actual key/button/axis codes.
			 * @throws Exception::E_NO_SUCH_ELEMENT if inputIdentifier is invalid.
			 */
			virtual std::string getInputEventString(const std::string& inputIdentifier) const throw (Exception) = 0;

			/**
			 * Returns the input code for an input identifier. For example, on a keyboard the input
			 * identifier could be the character 'a' and the input code could be the ASCII code
			 * for 'a' namely 97.
			 * @param inputIdentifier The input identifier string for the key/button/axis on the device.
			 * @return The device key/button/axis code associated with the input identifier.
			 * @throws Exception::E_NO_SUCH_ELEMENT if inputIdentifier is invalid.
			 */
			virtual int getInputCodeFromInputIdentifier(const std::string& inputIdentifier) const throw (Exception) = 0;

			/**
			 * Returns the input identifier for an input code. For example, on a keyboard the input code
			 * for 'a' could be the ASCII code 97, and the input identifier would be 'a'.
			 * @param inputCode The input code for the input identifier that should be returned.
			 * @return The input identifier that maps to the specified input code.
			 * @throws Exception::E_INVALID_PARAMETERS if inputCode is invalid.
			 */
			virtual std::string getInputIdentifierFromInputCode(int inputCode) const throw (Exception) = 0; 

			/**
			 * Get the InputDeviceType of this device.
			 * @return The InputDeviceType of this device.
			 */
			inline InputDeviceType getDeviceType() const
			{
				return deviceType;
			}

			/**
			 * Gets the name of the InputDevice.
			 * @return The name of the InputDevice.
			 */
			inline const std::string& getName() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return name;
			}

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The name of the device */
			std::string name;
			/** The device type. */
			InputDeviceType deviceType;

		private:
			/**
			 * Nullary Constructor.
			 */
			InputDevice() : deviceType(IDT_KEYBOARD)
			{
			}
	};
} // Myoushu

#endif

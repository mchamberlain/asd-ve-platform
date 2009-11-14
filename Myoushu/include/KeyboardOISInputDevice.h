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
 * @file KeyboardOISInputDevice.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef KEYBOARD_OIS_INPUT_DEVICE_H
#define KEYBOARD_OIS_INPUT_DEVICE_H

#define NUMBER_OF_KEY_INPUT_IDENTIFIERS 238

#include <string>
#include <map>

#include "OIS.h"

#include "Platform.h"
#include "OISInputDevice.h"
#include "KeyboardInputDevice.h"

namespace Myoushu
{
	/**
	 * This class manages keyboard input using OIS.
	 */
	class MYOUSHU_API KeyboardOISInputDevice : public OISInputDevice<OIS::Keyboard>, public KeyboardInputDevice, public OIS::KeyListener
	{
		public:
			/** Redefine the key codes. All input codes are contained in the KeyCode enumeration. */
			typedef OIS::KeyCode KeyCode;

			/** The base name of KeyboardOISInputDevices */
			static const std::string INPUT_DEVICE_NAME;

			/**
			 * Constructor.
			 * @param name The instance name.
			 * @param oisKeyboard The OIS::Keyboard instance associated with this device.
			 */
			KeyboardOISInputDevice(const std::string& name, OIS::Keyboard *oisKeyboard);

			/**
			 * Destructor
			 */
			~KeyboardOISInputDevice();

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
			std::string getInputEventString(const std::string& inputIdentifier) const throw (Exception);

			/**
			 * Returns the input code for an input identifier. For example, on a keyboard the input
			 * identifier could be the character 'a' and the input code could be the ASCII code
			 * for 'a' namely 97.
			 * @param inputIdentifier The input identifier string for the key/button/axis on the device.
			 * @return The device key/button/axis code associated with the input identifier.
			 * @throws Exception::E_NO_SUCH_ELEMENT if inputIdentifier is invalid.
			 */
			int getInputCodeFromInputIdentifier(const std::string& inputIdentifier) const throw (Exception);

			/**
			 * Returns the input identifier for an input code. For example, on a keyboard the input code
			 * for 'a' could be the ASCII code 97, and the input identifier would be 'a'.
			 * @param inputCode The input code for the input identifier that should be returned.
			 * @return The input identifier that maps to the specified input code.
			 * @throws Exception::E_INVALID_PARAMETER if inputCode is less than zero or too large.
			 */
			std::string getInputIdentifierFromInputCode(int inputCode) const throw (Exception); 

			/**
			 * Calls the capture method of the OIS::Object associated with this device. This will update
			 * the device and call any event callbacks that have been registered.
			 */
			inline void capture()
			{
				((OISInputDevice<OIS::Keyboard>*) this)->capture();
			}

			/**
			 * The event handler for key presses.
			 * @param arg The OIS::KeyEvent describing the key press.
			 */
			bool keyPressed(const OIS::KeyEvent &arg);

			/**
			 * The event handler for key releases.
			 * @param arg The OIS::KeyEvent describing the key release.
			 */
			bool keyReleased(const OIS::KeyEvent &arg);

		private:
			/** 
			 * Keyboard input identifiers array. Using KeyCode::* as 
			 * an index one can find the corresponding keyboard input 
			 * identifier for a keyboard input code. 
			 */
			std::string keyInputIdentifiers[NUMBER_OF_KEY_INPUT_IDENTIFIERS];

	};
} // Myoushu

#endif

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
 * @file MouseOISInputDevice.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <sstream>
#include <string>

#include "OIS.h"

#include "MouseOISInputDevice.h"
#include "NotificationManager.h"
#include "InputDeviceMessage.h"
#include "Config.h"
#include "ObjectPool.h"

namespace Myoushu
{
	const std::string MouseOISInputDevice::INPUT_DEVICE_NAME = "mouse";

	MouseOISInputDevice::MouseOISInputDevice(const std::string& name, OIS::Mouse *oisMouse) : OISInputDevice<OIS::Mouse>(oisMouse), MouseInputDevice(name)
	{
		unsigned int i;

		i = 0;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_X_AXIS;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_Y_AXIS;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_WHEEL;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_0;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_1;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_2;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_3;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_4;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_5;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_6;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_7;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_8;
		mouseInputIdentifiers[i++] = MouseInputDevice::MI_BUTTON_9;
	}

	MouseOISInputDevice::~MouseOISInputDevice()
	{
	}


	std::string MouseOISInputDevice::getInputEventString(const std::string& inputIdentifier) const throw (Exception)
	{
		std::ostringstream stream;

		// Create the key definition
		stream << Config::INPUT_PREFIX << "." << name << "." << inputIdentifier;

		return stream.str();
	}

	int MouseOISInputDevice::getInputCodeFromInputIdentifier(const std::string& inputIdentifier) const throw (Exception)
	{
		// Search through the array of input identifiers, the index is the key input code.
		for (unsigned int i = 0; i < NUMBER_OF_MOUSE_INPUT_IDENTIFIERS; i++)
		{
			if (mouseInputIdentifiers[i] == inputIdentifier)
			{
				return i;
			}
		}

		// If the mouse input identifier was not found throw an exception
		throw Exception(Exception::E_NO_SUCH_ELEMENT, "MouseOISInputDevice::getInputCodeFromInputIdentifier(): no such inputIdentifier.");

		return -1;
	}

	std::string MouseOISInputDevice::getInputIdentifierFromInputCode(int inputCode) const throw (Exception)
	{
		// Ensure that a valid input code is given, through an exception if it is not.
		if ((inputCode < 0) || (inputCode >= NUMBER_OF_MOUSE_INPUT_IDENTIFIERS))
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "MouseOISInputDevice::getInputIdentifierFromInputCode(): inputCode is invalid.");
		}

		return mouseInputIdentifiers[inputCode];
	}

	bool MouseOISInputDevice::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
	{
		InputDeviceMessage *message;
		Ogre::Real mouseSensitivity = Config::getSingleton().getDouble(Config::INPUT_MOUSE_SENSITIVITY);

		Poco::ScopedRWLock lock(rwLock, false);

		// Create an InputDeviceMessage instance to encapsulate the event
		//message = new InputDeviceMessage(this);
		message = ObjectPool<InputDeviceMessage>::getSingleton().get(true);

		message->setInputDevice(this);
		message->setDeviceType(this->deviceType);
		message->setDeviceAction(InputDeviceMessage::DA_PRESS);
		message->setDeviceState(InputDeviceMessage::DS_BUTTON_INDEX, (int) id);
		message->setDeviceState(InputDeviceMessage::DS_BUTTONS_STATE_INDEX, arg.state.buttons);
		message->setDeviceState(InputDeviceMessage::DS_X_INDEX, arg.state.X.abs);
		message->setDeviceState(InputDeviceMessage::DS_Y_INDEX, arg.state.Y.abs);
		message->setDeviceState(InputDeviceMessage::DS_Z_INDEX, arg.state.Z.abs);
		message->setDeviceState(InputDeviceMessage::DS_X_REL_INDEX, mouseSensitivity * arg.state.X.rel);
		message->setDeviceState(InputDeviceMessage::DS_Y_REL_INDEX, mouseSensitivity * arg.state.Y.rel);
		message->setDeviceState(InputDeviceMessage::DS_Z_REL_INDEX, mouseSensitivity * arg.state.Z.rel);

		// Try and set the input identifier string, log a warning if it is unknown.
		try
		{
			message->setInputIdentifier(0, getInputIdentifierFromInputCode((int) id + MC_BUTTON0));
		}
		catch (Exception &e)
		{
			LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
		}

		// Send the message.
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

	bool MouseOISInputDevice::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
	{
		InputDeviceMessage *message;
		Ogre::Real mouseSensitivity = Config::getSingleton().getDouble(Config::INPUT_MOUSE_SENSITIVITY);

		Poco::ScopedRWLock lock(rwLock, false);

		// Create an InputDeviceMessage instance to encapsulate the event
		//message = new InputDeviceMessage(this);
		message = ObjectPool<InputDeviceMessage>::getSingleton().get(true);

		message->setInputDevice(this);
		message->setDeviceType(this->deviceType);
		message->setDeviceAction(InputDeviceMessage::DA_RELEASE);
		message->setDeviceState(InputDeviceMessage::DS_BUTTON_INDEX, (int) id);
		message->setDeviceState(InputDeviceMessage::DS_BUTTONS_STATE_INDEX, arg.state.buttons);
		message->setDeviceState(InputDeviceMessage::DS_X_INDEX, arg.state.X.abs);
		message->setDeviceState(InputDeviceMessage::DS_Y_INDEX, arg.state.Y.abs);
		message->setDeviceState(InputDeviceMessage::DS_Z_INDEX, arg.state.Z.abs);
		message->setDeviceState(InputDeviceMessage::DS_X_REL_INDEX, mouseSensitivity * arg.state.X.rel);
		message->setDeviceState(InputDeviceMessage::DS_Y_REL_INDEX, mouseSensitivity * arg.state.Y.rel);
		message->setDeviceState(InputDeviceMessage::DS_Z_REL_INDEX, mouseSensitivity * arg.state.Z.rel);

		// Try and set the input identifier string, log a warning if it is unknown.
		try
		{
			message->setInputIdentifier(0, getInputIdentifierFromInputCode((int) id + MC_BUTTON0));
		}
		catch (Exception &e)
		{
			LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
		}

		// Send the message.
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

	bool MouseOISInputDevice::mouseMoved(const OIS::MouseEvent &arg)
	{
		InputDeviceMessage *message;
		Ogre::Real mouseSensitivity = Config::getSingleton().getDouble(Config::INPUT_MOUSE_SENSITIVITY);
		unsigned int i;

		Poco::ScopedRWLock lock(rwLock, false);

		// Create an InputDeviceMessage instance to encapsulate the event
		//message = new InputDeviceMessage(this);
		message = ObjectPool<InputDeviceMessage>::getSingleton().get(true);

		message->setInputDevice(this);
		message->setDeviceType(this->deviceType);
		message->setDeviceAction(InputDeviceMessage::DA_MOVE);
		message->setDeviceState(InputDeviceMessage::DS_BUTTONS_STATE_INDEX, arg.state.buttons);
		message->setDeviceState(InputDeviceMessage::DS_X_INDEX, arg.state.X.abs);
		message->setDeviceState(InputDeviceMessage::DS_Y_INDEX, arg.state.Y.abs);
		message->setDeviceState(InputDeviceMessage::DS_Z_INDEX, arg.state.Z.abs);
		message->setDeviceState(InputDeviceMessage::DS_X_REL_INDEX, mouseSensitivity * arg.state.X.rel);
		message->setDeviceState(InputDeviceMessage::DS_Y_REL_INDEX, mouseSensitivity * arg.state.Y.rel);
		message->setDeviceState(InputDeviceMessage::DS_Z_REL_INDEX, mouseSensitivity * arg.state.Z.rel);

		i = 0;
		// Check if the mouse moved on the X axis
		if (arg.state.X.rel != 0)
		{
			// Try and set the input identifier string, log a warning if it is unknown.
			try
			{
				message->setInputIdentifier(i, getInputIdentifierFromInputCode(MC_AXIS_X));
				i++;
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
			}
		}

		// Check if the mouse moved on the Y axis
		if (arg.state.Y.rel != 0)
		{
			// Try and set the input identifier string, log a warning if it is unknown.
			try
			{
				message->setInputIdentifier(i, getInputIdentifierFromInputCode(MC_AXIS_Y));
				i++;
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
			}
		}

		// Check if the mouse moved on the Z axis
		if (arg.state.Z.rel != 0)
		{
			// Try and set the input identifier string, log a warning if it is unknown.
			try
			{
				message->setInputIdentifier(i, getInputIdentifierFromInputCode(MC_WHEEL));
				i++;
			}
			catch (Exception &e)
			{
				LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
			}
		}

		// Send the message.
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

} // Myoushu

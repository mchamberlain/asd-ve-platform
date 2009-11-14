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
 * @file KeyboardOISInputDevice.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <sstream>
#include <string>
#include <iostream>

#include "KeyboardOISInputDevice.h"
#include "NotificationManager.h"
#include "InputDeviceMessage.h"
#include "Config.h"
#include "ObjectPool.h"

namespace Myoushu
{

	const std::string KeyboardOISInputDevice::INPUT_DEVICE_NAME = "keyboard";

	KeyboardOISInputDevice::KeyboardOISInputDevice(const std::string& name, OIS::Keyboard* oisKeyboard) : OISInputDevice<OIS::Keyboard>(oisKeyboard), KeyboardInputDevice(name)
	{
    unsigned int i;

    i = 0;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_UNASSIGNED;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_ESCAPE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_1;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_2;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_3;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_4;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_5;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_6;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_7;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_8;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_9;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_0;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MINUS;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_EQUALS;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_BACK;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_TAB;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_Q;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_W;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_E;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_R;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_T;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_Y;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_U;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_I;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_O;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_P;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LBRACKET;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RBRACKET;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RETURN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LCONTROL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_A;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_S;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_D;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_G;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_H;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_J;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_K;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_L;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SEMICOLON;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_APOSTROPHE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_GRAVE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LSHIFT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_BACKSLASH;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_Z;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_X;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_C;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_V;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_B;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_N;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_M;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_COMMA;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PERIOD;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SLASH;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RSHIFT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MULTIPLY;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LMENU;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SPACE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_CAPITAL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F1;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F2;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F3;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F4;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F5;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F6;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F7;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F8;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F9;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F10;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMLOCK;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SCROLL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD7;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD8;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD9;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SUBTRACT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD4;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD5;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD6;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_ADD;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD1;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD2;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD3;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPAD0;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_DECIMAL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_OEM_102;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F11;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F12;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F13;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F14;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_F15;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_KANA;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_ABNT_C1;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_CONVERT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NOCONVERT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_YEN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_ABNT_C2;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPADEQUALS;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PREVTRACK;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_AT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_COLON;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_UNDERLINE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_KANJI;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_STOP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_AX;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_UNLABELED;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NEXTTRACK;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPADENTER;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RCONTROL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MUTE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_CALCULATOR;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PLAYPAUSE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MEDIASTOP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_VOLUMEDOWN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_VOLUMEUP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBHOME;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_NUMPADCOMMA;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_DIVIDE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SYSRQ;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RMENU;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PAUSE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_HOME;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_UP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PGUP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LEFT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RIGHT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_END;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_DOWN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_PGDOWN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_INSERT;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_DELETE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_LWIN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_RWIN;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_APPS;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_POWER;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_SLEEP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WAKE;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBSEARCH;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBFAVORITES;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBREFRESH;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBSTOP;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBFORWARD;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_WEBBACK;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MYCOMPUTER;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MAIL;
		keyInputIdentifiers[i++] = KeyboardInputDevice::KI_MEDIASELECT;

	}

	KeyboardOISInputDevice::~KeyboardOISInputDevice()
	{
	}

	std::string KeyboardOISInputDevice::getInputEventString(const std::string& inputIdentifier) const throw (Exception)
	{
		std::ostringstream stream;

		// Create the key definition
		stream << Config::INPUT_PREFIX << "." << name << "." << inputIdentifier;

		return stream.str();
	}

	int KeyboardOISInputDevice::getInputCodeFromInputIdentifier(const std::string& inputIdentifier) const throw (Exception)
	{
		// Search through the array of input identifiers, the index is the key input code.
		for (unsigned int i = 0; i < NUMBER_OF_KEY_INPUT_IDENTIFIERS; i++)
		{
			if (keyInputIdentifiers[i] == inputIdentifier)
			{
				return i;
			}
		}

		// If the key identifier was not found throw an exception
		throw Exception(Exception::E_NO_SUCH_ELEMENT, "KeyboardOISInputDevice::getInputCodeFromInputIdentifier(): no such inputIdentifier.");

		return -1;
	}

	std::string KeyboardOISInputDevice::getInputIdentifierFromInputCode(int inputCode) const throw (Exception)
	{
		// Ensure that a valid input code is given, through an exception if it is not.
		if ((inputCode < 0) || (inputCode >= NUMBER_OF_KEY_INPUT_IDENTIFIERS))
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "KeyboardOISInputDevice::getInputIdentifierFromInputCode(): inputCode is invalid.");
		}

		return keyInputIdentifiers[inputCode];
	}

	bool KeyboardOISInputDevice::keyPressed(const OIS::KeyEvent &arg)
	{
		InputDeviceMessage *message;

		// Create an InputDeviceMessage instance to encapsulate the event
		//message = new InputDeviceMessage(this);
		message = ObjectPool<InputDeviceMessage>::getSingleton().get(true);
		message->setInputDevice(this);
		message->setDeviceType(this->deviceType);
		message->setDeviceAction(InputDeviceMessage::DA_PRESS);
		message->setDeviceState(InputDeviceMessage::DS_BUTTON_INDEX, (int) arg.key);

		// Try and set the input identifier string, log a warning if it is unknown.
		try
		{
			message->setInputIdentifier(0, getInputIdentifierFromInputCode((int) arg.key));
		}
		catch (Exception &e)
		{
			LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
		}

		// Send the message.
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

	bool KeyboardOISInputDevice::keyReleased(const OIS::KeyEvent &arg)
	{
		InputDeviceMessage *message;

		// Create an InputDeviceMessage instance to encapsulate the event
		//message = new InputDeviceMessage(this);
		message = ObjectPool<InputDeviceMessage>::getSingleton().get(true);
		message->setInputDevice(this);
		message->setDeviceType(this->deviceType);
		message->setDeviceAction(InputDeviceMessage::DA_RELEASE);
		message->setDeviceState(InputDeviceMessage::DS_BUTTON_INDEX, (int) arg.key);

		// Try and set the input identifier string, log a warning if it is unknown.
		try
		{
			message->setInputIdentifier(0, getInputIdentifierFromInputCode((int) arg.key));
		}
		catch (Exception &e)
		{
			LOG(EngineLog::LM_WARNING, "No input identifier defined for key code: " << e.what());
		}

		// Send the message.
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

} // Myoushu

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
 * @file KeyboardInputDevice.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef KEYBOARD_INPUT_DEVICE_H
#define KEYBOARD_INPUT_DEVICE_H

#include <string>

#include "OIS.h"

#include "Platform.h"
#include "HumanInputDevice.h"

namespace Myoushu
{
	/**
	 * The base class for keyboards.
	 */
	class MYOUSHU_API KeyboardInputDevice : public HumanInputDevice
	{
		public:
			/** Key identifiers taken from OIS */
			static const std::string KI_UNASSIGNED;
			static const std::string KI_ESCAPE;
			static const std::string KI_1;
			static const std::string KI_2;
			static const std::string KI_3;
			static const std::string KI_4;
			static const std::string KI_5;
			static const std::string KI_6;
			static const std::string KI_7;
			static const std::string KI_8;
			static const std::string KI_9;
			static const std::string KI_0;
			static const std::string KI_MINUS;    // - on main keyboard
			static const std::string KI_EQUALS;
			static const std::string KI_BACK;    // backspace
			static const std::string KI_TAB;
			static const std::string KI_Q;
			static const std::string KI_W;
			static const std::string KI_E;
			static const std::string KI_R;
			static const std::string KI_T;
			static const std::string KI_Y;
			static const std::string KI_U;
			static const std::string KI_I;
			static const std::string KI_O;
			static const std::string KI_P;
			static const std::string KI_LBRACKET;
			static const std::string KI_RBRACKET;
			static const std::string KI_RETURN;    // Enter on main keyboard
			static const std::string KI_LCONTROL;
			static const std::string KI_A;
			static const std::string KI_S;
			static const std::string KI_D;
			static const std::string KI_F;
			static const std::string KI_G;
			static const std::string KI_H;
			static const std::string KI_J;
			static const std::string KI_K;
			static const std::string KI_L;
			static const std::string KI_SEMICOLON;
			static const std::string KI_APOSTROPHE;
			static const std::string KI_GRAVE;    // accent
			static const std::string KI_LSHIFT;
			static const std::string KI_BACKSLASH;
			static const std::string KI_Z;
			static const std::string KI_X;
			static const std::string KI_C;
			static const std::string KI_V;
			static const std::string KI_B;
			static const std::string KI_N;
			static const std::string KI_M;
			static const std::string KI_COMMA;
			static const std::string KI_PERIOD;    // . on main keyboard
			static const std::string KI_SLASH;    // / on main keyboard
			static const std::string KI_RSHIFT;
			static const std::string KI_MULTIPLY;    // * on numeric keypad
			static const std::string KI_LMENU;    // left Alt
			static const std::string KI_SPACE;
			static const std::string KI_CAPITAL;
			static const std::string KI_F1;
			static const std::string KI_F2;
			static const std::string KI_F3;
			static const std::string KI_F4;
			static const std::string KI_F5;
			static const std::string KI_F6;
			static const std::string KI_F7;
			static const std::string KI_F8;
			static const std::string KI_F9;
			static const std::string KI_F10;
			static const std::string KI_NUMLOCK;
			static const std::string KI_SCROLL;    // Scroll Lock
			static const std::string KI_NUMPAD7;
			static const std::string KI_NUMPAD8;
			static const std::string KI_NUMPAD9;
			static const std::string KI_SUBTRACT;    // - on numeric keypad
			static const std::string KI_NUMPAD4;
			static const std::string KI_NUMPAD5;
			static const std::string KI_NUMPAD6;
			static const std::string KI_ADD;    // + on numeric keypad
			static const std::string KI_NUMPAD1;
			static const std::string KI_NUMPAD2;
			static const std::string KI_NUMPAD3;
			static const std::string KI_NUMPAD0;
			static const std::string KI_DECIMAL;    // . on numeric keypad
			static const std::string KI_OEM_102;    // < > | on UK/Germany keyboards
			static const std::string KI_F11;
			static const std::string KI_F12;
			static const std::string KI_F13;    //                     (NEC PC98)
			static const std::string KI_F14;    //                     (NEC PC98)
			static const std::string KI_F15;    //                     (NEC PC98)
			static const std::string KI_KANA;    // (Japanese keyboard)
			static const std::string KI_ABNT_C1;    // / ? on Portugese (Brazilian) keyboards
			static const std::string KI_CONVERT;    // (Japanese keyboard)
			static const std::string KI_NOCONVERT;    // (Japanese keyboard)
			static const std::string KI_YEN;    // (Japanese keyboard)
			static const std::string KI_ABNT_C2;    // Numpad . on Portugese (Brazilian) keyboards
			static const std::string KI_NUMPADEQUALS;    // = on numeric keypad (NEC PC98)
			static const std::string KI_PREVTRACK;    // Previous Track (static const std::string KI_CIRCUMFLEX on Japanese keyboard)
			static const std::string KI_AT;    //                     (NEC PC98)
			static const std::string KI_COLON;    //                     (NEC PC98)
			static const std::string KI_UNDERLINE;    //                     (NEC PC98)
			static const std::string KI_KANJI;    // (Japanese keyboard)
			static const std::string KI_STOP;    //                     (NEC PC98)
			static const std::string KI_AX;    //                     (Japan AX)
			static const std::string KI_UNLABELED;    //                        (J3100)
			static const std::string KI_NEXTTRACK;    // Next Track
			static const std::string KI_NUMPADENTER;    // Enter on numeric keypad
			static const std::string KI_RCONTROL;
			static const std::string KI_MUTE;    // Mute
			static const std::string KI_CALCULATOR;    // Calculator
			static const std::string KI_PLAYPAUSE;    // Play / Pause
			static const std::string KI_MEDIASTOP;    // Media Stop
			static const std::string KI_VOLUMEDOWN;    // Volume -
			static const std::string KI_VOLUMEUP;    // Volume +
			static const std::string KI_WEBHOME;    // Web home
			static const std::string KI_NUMPADCOMMA; // on numeric keypad (NEC PC98)
			static const std::string KI_DIVIDE;    // / on numeric keypad
			static const std::string KI_SYSRQ;
			static const std::string KI_RMENU;    // right Alt
			static const std::string KI_PAUSE;    // Pause
			static const std::string KI_HOME;    // Home on arrow keypad
			static const std::string KI_UP;    // UpArrow on arrow keypad
			static const std::string KI_PGUP;    // PgUp on arrow keypad
			static const std::string KI_LEFT;    // LeftArrow on arrow keypad
			static const std::string KI_RIGHT;    // RightArrow on arrow keypad
			static const std::string KI_END;    // End on arrow keypad
			static const std::string KI_DOWN;    // DownArrow on arrow keypad
			static const std::string KI_PGDOWN;    // PgDn on arrow keypad
			static const std::string KI_INSERT;    // Insert on arrow keypad
			static const std::string KI_DELETE;    // Delete on arrow keypad
			static const std::string KI_LWIN;    // Left Windows key
			static const std::string KI_RWIN;    // Right Windows key
			static const std::string KI_APPS;    // AppMenu key
			static const std::string KI_POWER;    // System Power
			static const std::string KI_SLEEP;    // System Sleep
			static const std::string KI_WAKE;    // System Wake
			static const std::string KI_WEBSEARCH;    // Web Search
			static const std::string KI_WEBFAVORITES;    // Web Favorites
			static const std::string KI_WEBREFRESH;    // Web Refresh
			static const std::string KI_WEBSTOP;    // Web Stop
			static const std::string KI_WEBFORWARD;    // Web Forward
			static const std::string KI_WEBBACK;    // Web Back
			static const std::string KI_MYCOMPUTER;    // My Computer
			static const std::string KI_MAIL;    // Mail
			static const std::string KI_MEDIASELECT;     // Media Select

			/**
			 * Constructor.
			 * @param name The instance name.
			 */
			KeyboardInputDevice(const std::string& name);

			/**
			 * Destructor
			 */
			~KeyboardInputDevice();

		private:
			/** Nullary Constructor */
			KeyboardInputDevice() : HumanInputDevice("KeyboardInputDevice", InputDevice::IDT_KEYBOARD)
			{
			}

	};
} // Myoushu

#endif

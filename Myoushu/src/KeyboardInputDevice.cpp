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
 * @file KeyboardInputDevice.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>

#include "KeyboardInputDevice.h"
#include "NotificationManager.h"

namespace Myoushu
{
	const std::string KeyboardInputDevice::KI_UNASSIGNED = "UNASSIGNED";
	const std::string KeyboardInputDevice::KI_ESCAPE = "ESCAPE";
	const std::string KeyboardInputDevice::KI_1 = "1";
	const std::string KeyboardInputDevice::KI_2 = "2";
	const std::string KeyboardInputDevice::KI_3 = "3";
	const std::string KeyboardInputDevice::KI_4 = "4";
	const std::string KeyboardInputDevice::KI_5 = "5";
	const std::string KeyboardInputDevice::KI_6 = "6";
	const std::string KeyboardInputDevice::KI_7 = "7";
	const std::string KeyboardInputDevice::KI_8 = "8";
	const std::string KeyboardInputDevice::KI_9 = "9";
	const std::string KeyboardInputDevice::KI_0 = "0";
	const std::string KeyboardInputDevice::KI_MINUS = "MINUS";    
	const std::string KeyboardInputDevice::KI_EQUALS = "EQUALS";
	const std::string KeyboardInputDevice::KI_BACK = "BACK";    
	const std::string KeyboardInputDevice::KI_TAB = "TAB";
	const std::string KeyboardInputDevice::KI_Q = "Q";
	const std::string KeyboardInputDevice::KI_W = "W";
	const std::string KeyboardInputDevice::KI_E = "E";
	const std::string KeyboardInputDevice::KI_R = "R";
	const std::string KeyboardInputDevice::KI_T = "T";
	const std::string KeyboardInputDevice::KI_Y = "Y";
	const std::string KeyboardInputDevice::KI_U = "U";
	const std::string KeyboardInputDevice::KI_I = "I";
	const std::string KeyboardInputDevice::KI_O = "O";
	const std::string KeyboardInputDevice::KI_P = "P";
	const std::string KeyboardInputDevice::KI_LBRACKET = "LBRACKET";
	const std::string KeyboardInputDevice::KI_RBRACKET = "RBRACKET";
	const std::string KeyboardInputDevice::KI_RETURN = "RETURN";    
	const std::string KeyboardInputDevice::KI_LCONTROL = "LCONTROL";
	const std::string KeyboardInputDevice::KI_A = "A";
	const std::string KeyboardInputDevice::KI_S = "S";
	const std::string KeyboardInputDevice::KI_D = "D";
	const std::string KeyboardInputDevice::KI_F = "F";
	const std::string KeyboardInputDevice::KI_G = "G";
	const std::string KeyboardInputDevice::KI_H = "H";
	const std::string KeyboardInputDevice::KI_J = "J";
	const std::string KeyboardInputDevice::KI_K = "K";
	const std::string KeyboardInputDevice::KI_L = "L";
	const std::string KeyboardInputDevice::KI_SEMICOLON = "SEMICOLON";
	const std::string KeyboardInputDevice::KI_APOSTROPHE = "APOSTROPHE";
	const std::string KeyboardInputDevice::KI_GRAVE = "GRAVE";    
	const std::string KeyboardInputDevice::KI_LSHIFT = "LSHIFT";
	const std::string KeyboardInputDevice::KI_BACKSLASH = "BACKSLASH";
	const std::string KeyboardInputDevice::KI_Z = "Z";
	const std::string KeyboardInputDevice::KI_X = "X";
	const std::string KeyboardInputDevice::KI_C = "C";
	const std::string KeyboardInputDevice::KI_V = "V";
	const std::string KeyboardInputDevice::KI_B = "B";
	const std::string KeyboardInputDevice::KI_N = "N";
	const std::string KeyboardInputDevice::KI_M = "M";
	const std::string KeyboardInputDevice::KI_COMMA = "COMMA";
	const std::string KeyboardInputDevice::KI_PERIOD = "PERIOD";    
	const std::string KeyboardInputDevice::KI_SLASH = "SLASH";    
	const std::string KeyboardInputDevice::KI_RSHIFT = "RSHIFT";
	const std::string KeyboardInputDevice::KI_MULTIPLY = "MULTIPLY";    
	const std::string KeyboardInputDevice::KI_LMENU = "LMENU";    
	const std::string KeyboardInputDevice::KI_SPACE = "SPACE";
	const std::string KeyboardInputDevice::KI_CAPITAL = "CAPITAL";
	const std::string KeyboardInputDevice::KI_F1 = "F1";
	const std::string KeyboardInputDevice::KI_F2 = "F2";
	const std::string KeyboardInputDevice::KI_F3 = "F3";
	const std::string KeyboardInputDevice::KI_F4 = "F4";
	const std::string KeyboardInputDevice::KI_F5 = "F5";
	const std::string KeyboardInputDevice::KI_F6 = "F6";
	const std::string KeyboardInputDevice::KI_F7 = "F7";
	const std::string KeyboardInputDevice::KI_F8 = "F8";
	const std::string KeyboardInputDevice::KI_F9 = "F9";
	const std::string KeyboardInputDevice::KI_F10 = "F10";
	const std::string KeyboardInputDevice::KI_NUMLOCK = "NUMLOCK";
	const std::string KeyboardInputDevice::KI_SCROLL = "SCROLL";    
	const std::string KeyboardInputDevice::KI_NUMPAD7 = "NUMPAD7";
	const std::string KeyboardInputDevice::KI_NUMPAD8 = "NUMPAD8";
	const std::string KeyboardInputDevice::KI_NUMPAD9 = "NUMPAD9";
	const std::string KeyboardInputDevice::KI_SUBTRACT = "SUBTRACT";    
	const std::string KeyboardInputDevice::KI_NUMPAD4 = "NUMPAD4";
	const std::string KeyboardInputDevice::KI_NUMPAD5 = "NUMPAD5";
	const std::string KeyboardInputDevice::KI_NUMPAD6 = "NUMPAD6";
	const std::string KeyboardInputDevice::KI_ADD = "ADD";    
	const std::string KeyboardInputDevice::KI_NUMPAD1 = "NUMPAD1";
	const std::string KeyboardInputDevice::KI_NUMPAD2 = "NUMPAD2";
	const std::string KeyboardInputDevice::KI_NUMPAD3 = "NUMPAD3";
	const std::string KeyboardInputDevice::KI_NUMPAD0 = "NUMPAD0";
	const std::string KeyboardInputDevice::KI_DECIMAL = "DECIMAL";    
	const std::string KeyboardInputDevice::KI_OEM_102 = "OEM_102";    
	const std::string KeyboardInputDevice::KI_F11 = "F11";
	const std::string KeyboardInputDevice::KI_F12 = "F12";
	const std::string KeyboardInputDevice::KI_F13 = "F13";    
	const std::string KeyboardInputDevice::KI_F14 = "F14";    
	const std::string KeyboardInputDevice::KI_F15 = "F15";    
	const std::string KeyboardInputDevice::KI_KANA = "KANA";    
	const std::string KeyboardInputDevice::KI_ABNT_C1 = "ABNT_C1";    
	const std::string KeyboardInputDevice::KI_CONVERT = "CONVERT";    
	const std::string KeyboardInputDevice::KI_NOCONVERT = "NOCONVERT";    
	const std::string KeyboardInputDevice::KI_YEN = "YEN";    
	const std::string KeyboardInputDevice::KI_ABNT_C2 = "ABNT_C2";    
	const std::string KeyboardInputDevice::KI_NUMPADEQUALS = "NUMPADEQUALS";    
	const std::string KeyboardInputDevice::KI_PREVTRACK = "PREVTRACK";    
	const std::string KeyboardInputDevice::KI_AT = "AT";    
	const std::string KeyboardInputDevice::KI_COLON = "COLON";    
	const std::string KeyboardInputDevice::KI_UNDERLINE = "UNDERLINE";    
	const std::string KeyboardInputDevice::KI_KANJI = "KANJI";    
	const std::string KeyboardInputDevice::KI_STOP = "STOP";    
	const std::string KeyboardInputDevice::KI_AX = "AX";    
	const std::string KeyboardInputDevice::KI_UNLABELED = "UNLABELED";    
	const std::string KeyboardInputDevice::KI_NEXTTRACK = "NEXTTRACK";    
	const std::string KeyboardInputDevice::KI_NUMPADENTER = "NUMPADENTER";    
	const std::string KeyboardInputDevice::KI_RCONTROL = "RCONTROL";
	const std::string KeyboardInputDevice::KI_MUTE = "MUTE";    
	const std::string KeyboardInputDevice::KI_CALCULATOR = "CALCULATOR";    
	const std::string KeyboardInputDevice::KI_PLAYPAUSE = "PLAYPAUSE";    
	const std::string KeyboardInputDevice::KI_MEDIASTOP = "MEDIASTOP";    
	const std::string KeyboardInputDevice::KI_VOLUMEDOWN = "VOLUMEDOWN";    
	const std::string KeyboardInputDevice::KI_VOLUMEUP = "VOLUMEUP";    
	const std::string KeyboardInputDevice::KI_WEBHOME = "WEBHOME";    
	const std::string KeyboardInputDevice::KI_NUMPADCOMMA = "NUMPADCOMMA"; 
	const std::string KeyboardInputDevice::KI_DIVIDE = "DIVIDE";    
	const std::string KeyboardInputDevice::KI_SYSRQ = "SYSRQ";
	const std::string KeyboardInputDevice::KI_RMENU = "RMENU";    
	const std::string KeyboardInputDevice::KI_PAUSE = "PAUSE";    
	const std::string KeyboardInputDevice::KI_HOME = "HOME";    
	const std::string KeyboardInputDevice::KI_UP = "UP";    
	const std::string KeyboardInputDevice::KI_PGUP = "PGUP";    
	const std::string KeyboardInputDevice::KI_LEFT = "LEFT";    
	const std::string KeyboardInputDevice::KI_RIGHT = "RIGHT";    
	const std::string KeyboardInputDevice::KI_END = "END";    
	const std::string KeyboardInputDevice::KI_DOWN = "DOWN";    
	const std::string KeyboardInputDevice::KI_PGDOWN = "PGDOWN";    
	const std::string KeyboardInputDevice::KI_INSERT = "INSERT";    
	const std::string KeyboardInputDevice::KI_DELETE = "DELETE";    
	const std::string KeyboardInputDevice::KI_LWIN = "LWIN";    
	const std::string KeyboardInputDevice::KI_RWIN = "RWIN";    
	const std::string KeyboardInputDevice::KI_APPS = "APPS";    
	const std::string KeyboardInputDevice::KI_POWER = "POWER";    
	const std::string KeyboardInputDevice::KI_SLEEP = "SLEEP";    
	const std::string KeyboardInputDevice::KI_WAKE = "WAKE";    
	const std::string KeyboardInputDevice::KI_WEBSEARCH = "WEBSEARCH";    
	const std::string KeyboardInputDevice::KI_WEBFAVORITES = "WEBFAVORITES";    
	const std::string KeyboardInputDevice::KI_WEBREFRESH = "WEBREFRESH";    
	const std::string KeyboardInputDevice::KI_WEBSTOP = "WEBSTOP";    
	const std::string KeyboardInputDevice::KI_WEBFORWARD = "WEBFORWARD";    
	const std::string KeyboardInputDevice::KI_WEBBACK = "WEBBACK";    
	const std::string KeyboardInputDevice::KI_MYCOMPUTER = "MYCOMPUTER";    
	const std::string KeyboardInputDevice::KI_MAIL = "MAIL";    
	const std::string KeyboardInputDevice::KI_MEDIASELECT = "MEDIASELECT";     

	KeyboardInputDevice::KeyboardInputDevice(const std::string& name) : HumanInputDevice(name, InputDevice::IDT_KEYBOARD)
	{
	}

	KeyboardInputDevice::~KeyboardInputDevice()
	{
	}

} // Myoushu


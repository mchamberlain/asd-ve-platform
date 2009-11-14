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
 * @file MouseInputDevice.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>

#include "OIS.h"

#include "MouseInputDevice.h"
#include "NotificationManager.h"

namespace Myoushu
{
	
	const std::string MouseInputDevice::MI_X_AXIS = "X-AXIS";
	const std::string MouseInputDevice::MI_Y_AXIS = "Y-AXIS";
	const std::string MouseInputDevice::MI_WHEEL = "WHEEL";
	const std::string MouseInputDevice::MI_BUTTON = "BUTTON";
	const std::string MouseInputDevice::MI_BUTTON_0 = "BUTTON0";
	const std::string MouseInputDevice::MI_BUTTON_1 = "BUTTON1";
	const std::string MouseInputDevice::MI_BUTTON_2 = "BUTTON2";
	const std::string MouseInputDevice::MI_BUTTON_3 = "BUTTON3";
	const std::string MouseInputDevice::MI_BUTTON_4 = "BUTTON4";
	const std::string MouseInputDevice::MI_BUTTON_5 = "BUTTON5";
	const std::string MouseInputDevice::MI_BUTTON_6 = "BUTTON6";
	const std::string MouseInputDevice::MI_BUTTON_7 = "BUTTON7";
	const std::string MouseInputDevice::MI_BUTTON_8 = "BUTTON8";
	const std::string MouseInputDevice::MI_BUTTON_9 = "BUTTON9";

	MouseInputDevice::MouseInputDevice(const std::string& name) : HumanInputDevice(name, InputDevice::IDT_MOUSE)
	{
	}

	MouseInputDevice::~MouseInputDevice()
	{
	}

} // Myoushu

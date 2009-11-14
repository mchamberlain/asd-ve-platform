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
 * @file MouseInputDevice.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef MOUSE_INPUT_DEVICE_H
#define MOUSE_INPUT_DEVICE_H

#include <string>

#include "Platform.h"
#include "HumanInputDevice.h"

namespace Myoushu
{
	/**
	 * This class manages mouse input using OIS.
	 */
	class MYOUSHU_API MouseInputDevice : public HumanInputDevice
	{
		public:
			/** String identifier for the x axis. */
			static const std::string MI_X_AXIS;
			/** String identifier for the y axis. */
			static const std::string MI_Y_AXIS;
			/** String identifier for the z axis, mouse wheel. */
			static const std::string MI_WHEEL;
			/** String identifier for a button, a number must be appended for a specific button. */
			static const std::string MI_BUTTON;
			/** String identifier for button 0 on the mouse. */
			static const std::string MI_BUTTON_0;
			/** String identifier for button 1 on the mouse. */
			static const std::string MI_BUTTON_1;
			/** String identifier for button 2 on the mouse. */
			static const std::string MI_BUTTON_2;
			/** String identifier for button 3 on the mouse. */
			static const std::string MI_BUTTON_3;
			/** String identifier for button 4 on the mouse. */
			static const std::string MI_BUTTON_4;
			/** String identifier for button 5 on the mouse. */
			static const std::string MI_BUTTON_5;
			/** String identifier for button 6 on the mouse. */
			static const std::string MI_BUTTON_6;
			/** String identifier for button 7 on the mouse. */
			static const std::string MI_BUTTON_7;
			/** String identifier for button 8 on the mouse. */
			static const std::string MI_BUTTON_8;
			/** String identifier for button 9 on the mouse. */
			static const std::string MI_BUTTON_9;

			/**
			 * Constructor.
			 * @param name The name of the instance.
			 */
			MouseInputDevice(const std::string& name);

			/**
			 * Destructor
			 */
			~MouseInputDevice();

	};
} // Myoushu

#endif

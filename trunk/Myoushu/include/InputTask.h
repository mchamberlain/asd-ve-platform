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
 * @file InputTask.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_TASK_H
#define INPUT_TASK_H

#include <string>
#include <list>

#include "Poco/AutoPtr.h"
#include "OIS.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Task.h"
#include "InputDevice.h"
#include "InputDeviceMessage.h"
#include "InputMessage.h"

namespace Myoushu
{
	/**
	 * This Task manages all input related system in the engine.
	 */
	class MYOUSHU_API InputTask : public NamedObject<InputTask>, public Task
	{
		public:
			/** The default mouse sensitivity. */
			static const Ogre::Real DEFAULT_MOUSE_SENSITIVITY;

			/**
			 * Constructor.
			 * @param priority The priority of the Task.
			 * @param name The name of the Task.
			 * @param executionInterval The amount of time, in microseconds, between executions of this Task. 
			 *							To execute in every frame use 0. Defaults to 0. To execute twice
			 *							a second use 500000 for instance.
			 * @param iterationLimit If the task misses its executionInterval, iterationLimit controls how many
			 *						 extra executions of the Task will be performed to catch up. Task that are
			 *						 slow and computationally expensive should not set this limit higher than one
			 *						 since it will slow the engine down if it cannot consistently run the task at
			 *						 its intervals. Higher iterationLimits are meant for lighter
			 *						 but important tasks, like game logic updates.
			 */
			InputTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			InputTask();

			/** Destructor */
			~InputTask();

			CLASS_NAME_FUNCTIONS(InputTask);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method sets the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Sets state to TS_KILLED.
			 */
			void kill();

			/**
			 * Receive a InputDeviceMessage.
			 * @param message The InputDeviceMessage.
			 */
			void receiveInputDeviceMessage(const Poco::AutoPtr<InputDeviceMessage>& message);
		protected:
			/** The OIS::InputManager instance */
			OIS::InputManager *inputManager;
	};
} // Myoushu

#endif

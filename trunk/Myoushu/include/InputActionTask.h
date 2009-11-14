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
 * @file InputActionTask.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_ACTION_TASK_H
#define INPUT_ACTION_TASK_H

#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Task.h"
#include "InputMessage.h"

namespace Myoushu
{
	/**
	 * The InputActionTask receives InputMessages and calls the callbacks associated with the
	 * inputAction of the InputMessage through the InputActionManager. 
	 */
	class MYOUSHU_API InputActionTask : public Task, public NamedObject<InputActionTask>
	{
		public:
			/**
			 * Nullary Constructor. The priority and executionIntervals are initialized to 0.
			 */
			InputActionTask();

			/** InputActionTask constructor.
			 * @param priority The Task's priority, used to determine execution order in the Kernel.
			 * @param name The name of the instance.
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
			InputActionTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/** Task Destructor. */
			virtual ~InputActionTask();

			CLASS_NAME_FUNCTIONS(InputActionTask);

			/**
			 * Initializes the task.
			 */
			virtual void init() throw (Exception);

			/**
			 * Suspend the Task. This method should set the TaskState to TS_SUSPENDED.
			 */
			virtual void suspend();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			virtual void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Should set state to TS_KILLED.
			 */
			virtual void kill();

			/**
			 * Receive a InputMessage. Calls any callback functions associated with the input action
			 * of the message though the InputActionManager.
			 * @param message The InputMessage.
			 */
			void receiveInputMessage(const Poco::AutoPtr<InputMessage>& message);
	};

} // Myoushu

#endif

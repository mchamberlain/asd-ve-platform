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
 * @file ScriptTask.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef SCRIPT_TASK_H
#define SCRIPT_TASK_H

#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Task.h"
#include "NamedObject.h"
#include "LuaParser.h"
#include "ScriptMessage.h"

namespace Myoushu
{
	/**
	 * This task runs the Script system in the engine. It is Lua based. The task receives ScriptMessage instances
	 * and reacts to them (executes a script or function for instance).
	 */
	class MYOUSHU_API ScriptTask : public Task, public NamedObject<ScriptTask>
	{
		public:
			/** Nullary Constructor */
			ScriptTask();

			/**
			 * Constructor.
			 * @param priority The priority of the Task. Smaller is higher.
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
			ScriptTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/** Destructor */
			~ScriptTask();

			CLASS_NAME_FUNCTIONS(ScriptTask);

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
			 * Kill the task. Should set state to TS_KILLED.
			 */
			void kill();

			/**
			 * Message handler function for ScriptMessages. This method will take appropriate action (execute a script
			 * for example) based on the message received.
			 * @param message A ScriptMessage instance.
			 */
			void receiveScriptMessage(const Poco::AutoPtr<ScriptMessage>& message);

		private:
			/** A pointer to the LuaParser to use to execute scripts. */
			LuaParser *luaParser;
	};
} // Myoushu

#endif

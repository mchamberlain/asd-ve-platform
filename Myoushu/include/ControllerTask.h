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
 * @file ControllerTask.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef CONTROLLER_TASK_H
#define CONTROLLER_TASK_H

#include <map>

#include "Ogre.h"
#include "Poco/AutoPtr.h"

#include "Task.h"
#include "NamedObject.h"
#include "Controller.h"
#include "ControllerTaskMessage.h"

namespace Myoushu
{
	/**
	 * The ControllerTask manages and updates Controller instances. Everytime the ControllerTask is executed by the Kernel it calls the update() function of each of the
	 * Controllers that it is managing.
	 */
	class MYOUSHU_API ControllerTask : public NamedObject<ControllerTask>, public Task
	{
		public:
			/** Type definition of the map of controller names to controllers. */
			typedef std::map<Ogre::String, Controller*> ControllersMap;
			/** Type definition for the iterator over the ControllersMap. */
			typedef ControllersMap::iterator ControllersMapIterator;
			/** Type definition for the const iterator over ControllersMap. */
			typedef ControllersMap::const_iterator ControllersMapConstIterator;

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
			ControllerTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			ControllerTask();

			/** Destructor. */
			~ControllerTask();

			CLASS_NAME_FUNCTIONS(ControllerTask);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method should sets the TaskState to TS_SUSPENDED.
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
			 * Handles a ControllerTaskMessage. This is generally used to add or remave a controller to/from this task.
			 * @param message The ControllerTaskMessage instance.
			 */
			void receiveControllerTaskMessage(const Poco::AutoPtr<ControllerTaskMessage>& message);

		protected:
			/** List of Controllers that will be updated by this Task. */
			ControllersMap controllers;			
	};

} // Myoushu

#endif

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
 * @file PhysicsTask.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef PHYSICSTASK_H
#define PHYSICSTASK_H

#include "NxOgre.h"

#include "Task.h"
#include "TimerTaskMessage.h"
#include "NotificationManager.h"

namespace Myoushu
{
	/**
	 * This Task manages collision detection and physics for all GameObjects that are registered for collision detection and physics. We use
	 * NxOgre (www.nxogre.org) and the NVIDIA PhysX SDK (www.nvidia.com).
	 */
	class MYOUSHU_API PhysicsTask : public Task, public NamedObject<PhysicsTask>
	{
		public:
			/**
			 * Constructor
			 * @param priority The priority of the task. Lower values means higher priorities.
			 * @param name The instance name of the Task.
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
			PhysicsTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

 			/** Nullary Constructor */
			PhysicsTask();

			/** Destructor */
			~PhysicsTask();
			
			CLASS_NAME_FUNCTIONS(PhysicsTask);

			/**
			 * Initializes the task, NxOgre and the PhysX SDK.
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
			 * Getter for the NxOgre::World instance.
			 * @return the NxOgre::World instance.
			 */
			inline NxOgre::World* getWorld()
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return world;
			}

			/** Receive and process the timer update message. */
			void receiveTimerTaskMessage(const Poco::AutoPtr<TimerTaskMessage>& message);

		protected:
			/** Represents the physics universe that will contain all of the physics enabled scenes, containing objects */
			NxOgre::World *world;
			/** 
			 * The NxOgre::PhysXDriver instance created by NxOgre::World constructor. We use this instance to control the
			 * physics simulation.
			 */
			NxOgre::PhysXDriver *physXDriver;
			/** The time since the last step. This variable is updated in the receiveTimerTaskMessage function. */
			float timeSinceLastStep;
	};
} // Myoushu

#endif
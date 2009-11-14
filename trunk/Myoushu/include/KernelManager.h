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
 * @file KernelManager.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef KERNEL_MANAGER_H
#define KERNEL_MANAGER_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Task.h"
#include "CallbackTask.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * A singleton that manages the Kernel. Users can use the KernelManager to add and remove tasks, set the
	 * state of the task or stop the engine.
	 */
	class MYOUSHU_API KernelManager : public Ogre::Singleton<KernelManager>
	{
		public:
			/** Nullary Constructor */
			KernelManager();

			/** Destructor */
			virtual ~KernelManager();

			/**
			 * This method sends a message to the Kernel telling it to terminate as soon as possible.
			 * All tasks will be removed from the kernel.
			 */
			void stopKernel();

			/** Adds the given Task instance to the Kernel's task pool.
			 * @param task The Task instance to add.
			 * @throws Exception if task is NULL.
			 */
			void addTask(Task *task) throw (Exception);

			/**
			 * Suspend the specified Task instance.
			 * @param task The Task instance to suspend.
			 * @throws Exception if task is NULL.
			 */
			void suspendTask(Task *task) throw (Exception);

			/**
			 * Suspend the Task instance with the specified name.
			 * @param name The name of the Task instance to suspend.
			 * @return The Task that was suspended.
			 */
			void suspendTask(const std::string& name);

			/**
			 * Remove the specified Task instance.
			 * @param task The Task instance to remove.
			 * @throws Exception if task is NULL.
			 */
			void removeTask(Task *task) throw (Exception);

			/**
			 * Kill and Remove the Task instance with the specified name.
			 * @param name The name of the Task instance to remove.
			 * @return The Task that was killed and removed.
			 */
			void removeTask(const std::string& name);

			/** Initialize all Tasks in the Kernel. */
			void initAllTasks();

			/* Convenience function to creates a CallbackTask instance and add it to the kernel. It is not initialised. The Kernel takes ownership
			 * of the created CallbackTask instance.
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
			CallbackTask* createCallbackTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
	};

	// inlines
	inline CallbackTask* KernelManager::createCallbackTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit)
	{
		CallbackTask *pTask = new CallbackTask(priority, name, executionInterval, iterationLimit);

		addTask(pTask);

		return pTask;
	}
} // Myoushu

#endif


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
 * @file Kernel.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Task.h"
#include "ConcurrentTask.h"
#include "Exception.h"
#include "KernelMessage.h"

namespace Myoushu
{
	/**
	 * The Kernel executes and manages Tasks and ConcurrentTasks. It executes Tasks in a serial, round robin fashion.
	 */

	class MYOUSHU_API Kernel : public Ogre::Singleton<Kernel>
	{
		public:
			/** Iterator for a std::list of Tasks. */
			typedef std::list<Poco::AutoPtr<Task> >::iterator TaskPoolIter;

			/** Constructor */
			Kernel();

			/** Destructor
			 * Kills any active tasks in the task pool and removes
			 * all tasks from the task pool.
			 */
			virtual ~Kernel();

			/** Adds the given Task instance to the Kernel's task pool.
			 * @param task The Task instance to add.
			 * @throws Exception if task is NULL.
			 */
			void addTask(Poco::AutoPtr<Task> task) throw (Exception);

			/**
			 * Suspend the specified Task instance.
			 * @param task The Task instance to suspend.
			 * @throws Exception if task is NULL.
			 */
			void suspendTask(Poco::AutoPtr<Task> task) throw (Exception);

			/**
			 * Suspend the Task instance with the specified name.
			 * @param name The name of the Task instance to suspend.
			 * @return The Task that was suspended.
			 */
			Poco::AutoPtr<Task> suspendTask(const std::string& name);

			/**
			 * Remove the specified Task instance.
			 * @param task The Task instance to remove.
			 * @throws Exception if task is NULL.
			 */
			void removeTask(Poco::AutoPtr<Task> task) throw (Exception);

			/**
			 * Kill and Remove the Task instance with the specified name.
			 * @param name The name of the Task instance to remove.
			 * @return The Task that was killed and removed.
			 */
			Poco::AutoPtr<Task> removeTask(const std::string& name);

			/**
			 * Execute one iteration of all of the Tasks in a Round Robin fashion.
			 * The order in which the Tasks are executed are determined
			 * by their priorities. This method sets executing to true
			 * and continues to execute until the Kernel receives the
			 * Kernel::KM_SHUTDOWN message.
			 */
			void execute();

			/**
			 * Calls the init() methods of all of the tasks in the task pool.
			 */
			void initAllTasks();

			/**
			 * Starts all of the concurrent tasks in their own threads.
			 */
			void startConcurrentTasks();

			/**
			 * This method shouldn't be called by users, it gets called
			 * by the Poco Notification system.
			 * @param message The message that was sent to this observer.
			 */
			void receiveMessage(const Poco::AutoPtr<KernelMessage>& message);

			/**
			 * Gets the value of executing. Executing is true while the execute() function is
			 * running.
			 * @return The value of executing.
			 */
			inline bool isExecuting() const
			{
				Poco::ScopedRWLock lock(rwLockExecuting, false);

				return executing;
			}

			/**
			 * Setter for the executing flag.
			 * @param executing The new value for the executing flag.
			 */
			inline void setExecuting(bool executing)
			{
				Poco::ScopedRWLock lock(rwLockExecuting, true);

				this->executing = executing;
			}

			/** Returns the value of taskPoolChanged in a thread safe manner. */
			inline bool isTaskPoolChanged() const
			{
				Poco::ScopedRWLock lock(rwLockTaskPoolChanged, false);

				return taskPoolChanged;
			}

			/**
			 * Sets the value of taskPoolChanged.
			 * @param changed The new value for taskPoolChanged.
 			 */
			inline void setTaskPoolChanged(bool changed)
			{
				Poco::ScopedRWLock lock(rwLockTaskPoolChanged, true);

				taskPoolChanged = changed;
			}

		protected:
			/** read write mutex for thread safety. This lock is used to obtain
			 * mutal exclusion on all variables in the class except the ones that have
			 * their own locks defined below. */
			mutable Poco::RWLock rwLock;
			/** read write mutex for the execute varibale */
			mutable Poco::RWLock rwLockExecuting;
			/** read write mutex for the taskPoolChanged boolean */
			mutable Poco::RWLock rwLockTaskPoolChanged;
			/** read write lock on the executeTaskList */
			mutable Poco::RWLock rwLockExecuteTaskList;
			/** true if execute is running */
			bool executing;
			/** List of Tasks */
			std::list<Poco::AutoPtr<Task> > taskPool;
			/** Boolean indicating if the taskPool has changed since the last kernel execution run. */
			bool taskPoolChanged;
			/** List of Tasks to execute. */
			std::list<Poco::AutoPtr<Task> > executeTaskList;

			/** Kills all running tasks. Called when the kernel stops executing. */
			void killAllTasks();

	};
} // Myoushu

#endif

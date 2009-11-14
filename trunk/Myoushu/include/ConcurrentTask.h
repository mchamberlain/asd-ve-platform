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
 * @file ConcurrentTask.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef CONCURRENTTASK_H
#define CONCURRENTTASK_H

#include <string>

#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "Task.h"
#include "NamedObject.h"

namespace Myoushu
{
	/**
	 * An extension of Task, a ConcurrentTask runs concurrently with the Kernel in its own thread.
	 * It still has an execute function that is still called by the Kernel during the Kernel's
	 * execution of the serial Tasks.
	 */

	class MYOUSHU_API ConcurrentTask : public NamedObject<ConcurrentTask>, public Task, public Poco::Runnable, public Poco::Thread
	{
		public:
			/** Constructor.
			 * @param name The name of the instance.
			 * @param priority The priority of the task in the Kernel.
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
			ConcurrentTask(const std::string& name, int priority, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Destructor.
			 */
			~ConcurrentTask();

			CLASS_NAME_FUNCTIONS(ConcurrentTask);

			/** Gets the name of this Task. Implemented here to avoid conflict with Task and Poco::Thread. */
			std::string getName() const;

			/**
			 * This is the main execution area of the thread. The current execution of the
			 * thread takes place in the function.
			 */
			 virtual void run() = 0;
	};

	// inlines
	inline std::string ConcurrentTask::getName() const
	{
		return Task::getName();
	}
} // Myoushu

#endif

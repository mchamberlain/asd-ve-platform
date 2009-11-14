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
 * @file Task.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef TASK_H
#define TASK_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"
#include "NamedInstance.h"

namespace Myoushu
{
	/**
	 * A serial Task that is executed by the Kernel. This abstract class should be extended by other classes to
	 * create various tasks that engine needs, like a VideoTask for redering for instance.
	 */

	class MYOUSHU_API Task : public NamedObject<Task>, public NamedInstance, public Poco::RefCountedObject
	{
		public:
			/** The state of the Task. */
			enum TaskState {
				/** The Task was just created. */
				TS_CREATED,
				/** The Task has been initialized. */
				TS_INITIALIZED,
				/** The Task is running. */
				TS_RUNNING,
				/** The Task is suspended. */
				TS_SUSPENDED,
				/** The Task has been killed. */
				TS_KILLED
			};

			/**
			 * Nullary Constructor. The priority and executionIntervals are initialized to 0.
			 */
			Task();

			/** Task constructor.
			 * @param priority The Task's priority, used to determine execution order in the Kernel.
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
			Task(int priority, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/** Task constructor.
			 * @param name The name of the instance.
			 * @param priority The Task's priority, used to determine execution order in the Kernel.
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
			Task(const std::string& name, int priority, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/** Task Destructor. */
			virtual ~Task();

			CLASS_NAME_FUNCTIONS(Task);

			/** Get the Task's priority.
			 * @return The Task's Priority.
			 */
			int getPriority() const;

			/** 
			 * Gets the amount of time, in microseconds, between executions of this Task.
			 * To execute in every frame use 0. Defaults to 0. To execute twice
			 * a second use 500000 for instance.
			 */
			unsigned long getExecutionInterval() const;

			/**
			 * Getter for the iterationLimit. If the task misses its executionInterval, iterationLimit controls how many
			 * extra executions of the Task will be performed to catch up. Task that are
			 * slow and computationally expensive should not set this limit higher than one
			 * since it will slow the engine down if it cannot consistently run the task at
			 * its intervals. Higher iterationLimits are meant for lighter
			 * but important tasks, like game logic updates.
			 * @return the iterationLimit
			 */
			unsigned int getIterationLimit() const;

			/** Get the current task state.
			 * @return The TaskState value of the Task.
			 */
			TaskState getState() const;

			/** Get the time (in microseconds) at which this Task was last executed.
			 * @return The time (in microseconds) at which this Task was last executed.
			 */
			unsigned long getTimeLastExecuted() const;

			/** Set the time (in microseconds) at which this Task was last executed.
			 * @param timeStap The time (in microseconds) at which this Task was last executed.
			 */
			void setTimeLastExecuted(unsigned long timeStamp);

			/**
			 * Set the Task's current TaskState.
			 * @param state The new TaskState of the class.
			 */
			void setState(TaskState state);

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
			virtual void execute(unsigned long timeDelta) = 0;

			/**
			 * Kill the task. Should set state to TS_KILLED.
			 */
			virtual void kill();

		protected:
			/** Read write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** The state of the task, running, stopped etc.*/
			TaskState state;
			/** Last execute time stamp */
			unsigned long timeLastExecuted;

		private:
			/** The task's priority, used to determine execution order in the Kernel. */
			int priority;
			/** The amount of time, in mcroseconds, between executions of this Task. 
			 *	To execute in every frame use 0.
			 */
			unsigned long executionInterval;
			/*
			 * If the task misses its executionInterval, iterationLimit controls how many
			 * extra executions of the Task will be performed to catch up. Task that are
			 * slow and computationally expensive should not set this limit higher than one
			 * since it will slow the engine down if it cannot consistently run the task at
			 * its intervals. Higher iterationLimits are meant for lighter
			 * but important tasks, like game logic updates.
			 */
			unsigned int iterationLimit;
	};

	// inlines
	inline int Task::getPriority() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return priority;
	}

	inline unsigned long Task::getExecutionInterval() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return executionInterval;
	}

	inline unsigned int Task::getIterationLimit() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return iterationLimit;
	}

	inline Task::TaskState Task::getState() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return state;
	}

	inline void Task::setState(TaskState state)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->state = state;
	}

	inline unsigned long Task::getTimeLastExecuted() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return timeLastExecuted;
	}

	inline void Task::setTimeLastExecuted(unsigned long timeStamp)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		timeLastExecuted = timeStamp;
	}

} // Myoushu

#endif

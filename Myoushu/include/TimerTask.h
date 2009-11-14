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
 * @file TimerTask.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef TIMER_TASK_H
#define TIMER_TASK_H

#include <string>

#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "NamedObject.h"
#include "Task.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class manages a timer and sends messages to other Tasks about the time that has
	 * passed since the last execution phase. (Time between frames basically)
	 */

	class MYOUSHU_API TimerTask : public NamedObject<TimerTask>, public Task, public Ogre::Singleton<TimerTask>
	{
		public:
			/** Constructor.
			 * @param priority The priority of the task.
			 * @param name The name of the instance.
			 */
			TimerTask(int priority, const std::string& name);

			/**
			 * Nullary Constructor.
			 */
			TimerTask();

			/** Destructor */
			~TimerTask();

			CLASS_NAME_FUNCTIONS(TimerTask);

			/**
			 * Set the state of the task.
			 * @param state The new state of the task (TS_RUNNING, TS_SUSPENDED etc.)
			 */
			void setState(TaskState state);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method should set the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Kill the task. Should set state to TS_KILLED.
			 */
			void kill();

			/**
			 * Reset the absTime and other stats keeping variables, but does not
			 * reset the internal timer that calculates frame deltas, so this will stay consistent.
			 */
			void resetStats();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Gets the time delta (time since last frame) in microseconds.
			 * @return The time delta (time since last frame) in microseconds.
			 */
			unsigned long getDelta();

			/**
			 * Gets the absolute time since engine start in microseconds.
			 * @return The absolute time since engine start in microseconds.
			 */
			unsigned long getAbsTime();

			/** Gets the total number of iterations (times execute() has been called). */
			unsigned long getIterationCnt();

			/** Gets the smallest time delta in milliseconds. */
			unsigned long getSmallestTimeDelta();

			/** Gets the largest time delta in milliseconds. */
			unsigned long getLargestTimeDelta();

			/** Gets the absolute running time in milliseconds. */
			unsigned long getAbsTimeMillis();

		private:
			/** The Timer */
			Ogre::Timer timer;
			/** The time delta in microseconds */
			unsigned long delta;
			/** The absolute time since the start of the TimerTask in microseconds */
			unsigned long absTime;
			///** Since absolute time is measured in milliseconds, this variable accumulates
			// * frame deltas (in microseconds) up to 1000 before adding it to the absolute time.
			// */
			//unsigned long incrementalDelta;
			/** The total number of iterations (times execute() has been called). */
			unsigned long mIterationCnt;
			/** The smallest time delta in milliseconds. */
			unsigned long mSmallestTimeDelta;
			/** The largest time delta in milliseconds. */
			unsigned long mLargestTimeDelta;
			/** The absolute running time in milliseconds. */
			unsigned long mAbsTimeMillis;
	};

	// inlines
	inline unsigned long TimerTask::getDelta()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return delta;
	}

	inline unsigned long TimerTask::getAbsTime()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return absTime;
	}

	inline unsigned long TimerTask::getIterationCnt()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mIterationCnt;
	}

	inline unsigned long TimerTask::getSmallestTimeDelta()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSmallestTimeDelta;
	}

	inline unsigned long TimerTask::getLargestTimeDelta()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mLargestTimeDelta;
	}

	inline unsigned long TimerTask::getAbsTimeMillis()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mAbsTimeMillis;
	}

} // Myoushu

#endif


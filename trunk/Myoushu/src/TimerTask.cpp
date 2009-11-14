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
 * @file TimerTask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>
#include <iostream>

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "TimerTask.h"
#include "TimerTaskMessage.h"
#include "NotificationManager.h"
#include "Task.h"
#include "Exception.h"
#include "EngineLog.h"
#include "ObjectPool.h"

//template<>
//Myoushu::TimerTask* Ogre::Singleton<Myoushu::TimerTask>::ms_Singleton = NULL;

namespace Myoushu
{
	CLASS_NAME(TimerTask, "Myoushu::TimerTask");

	TimerTask::TimerTask(int priority, const std::string& name) : Task(name, priority), delta(0), absTime(0)
		/*, incrementalDelta(0)*/, mIterationCnt(0), mSmallestTimeDelta(0), mLargestTimeDelta(0), mAbsTimeMillis(0)
	{
	}

	TimerTask::TimerTask() : Task(0), delta(0), absTime(0) //, incrementalDelta(0)
		, mIterationCnt(0), mSmallestTimeDelta(0), mLargestTimeDelta(0), mAbsTimeMillis(0)
	{
	}

	TimerTask::~TimerTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());
	}

	void TimerTask::setState(TaskState state)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if ((state == TS_RUNNING) && (this->state == TS_RUNNING))
		{
			delta = 0;
			absTime = 0;
			mIterationCnt = 0;
			mSmallestTimeDelta = 0;
			mLargestTimeDelta = 0;
			mAbsTimeMillis = 0;
			timer.reset();
		}

		this->state = state;
	}

	void TimerTask::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing TimerTask.");

		delta = 0;
		absTime = 0;
		mIterationCnt = 0;
		mSmallestTimeDelta = 0;
		mLargestTimeDelta = 0;
		mAbsTimeMillis = 0;
		timer.reset();

		state = TS_INITIALIZED;
	}

	void TimerTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void TimerTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void TimerTask::resetStats()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		absTime = 0;
		//incrementalDelta = 0;
		mIterationCnt = 0;
		mSmallestTimeDelta = 0;
		mLargestTimeDelta = 0;
		mAbsTimeMillis = 0;
	}

	void TimerTask::execute(unsigned long timeDelta)
	{
		TimerTaskMessage *message;
		//unsigned long step;

		Poco::ScopedRWLock lock(rwLock, true);

		if (state != TS_RUNNING)
		{
			delta = 0;
			absTime = 0;
			//incrementalDelta = 0;
			mIterationCnt = 0;
			mSmallestTimeDelta = 0;
			mLargestTimeDelta = 0;
			mAbsTimeMillis = 0;
			timer.reset();

			state = TS_RUNNING;
		}
		else
		{
			unsigned long deltaMillis;

			mIterationCnt++;

			// Get the time that passed since the Task last executed
			delta = timer.getMicroseconds();
			deltaMillis = delta / 1000;
			absTime += delta;
			mAbsTimeMillis += deltaMillis;

			if ((mAbsTimeMillis == deltaMillis) && (deltaMillis > 0))
			{
				// First frame, set max and min to current delta
				mSmallestTimeDelta = deltaMillis;
				mLargestTimeDelta = deltaMillis;
			}
			else if (deltaMillis > 0)
			{
				if (mSmallestTimeDelta > deltaMillis)
				{
					mSmallestTimeDelta = deltaMillis;
				}
				if (mLargestTimeDelta < deltaMillis)
				{
					mLargestTimeDelta = deltaMillis;
				}
			}

			//// Since absolute time is recored in milliseconds, only increase it after a full
			//// millisecond has passed, but keep track of the exact time
			//incrementalDelta += delta;
			//if (incrementalDelta >= 1000ul)
			//{
			//	step = incrementalDelta / 1000ul;
			//	incrementalDelta -= 1000ul * step;
			//	absTime += step;
			//}

			timer.reset();
		}

		// Populate and send the message
		message = ObjectPool<TimerTaskMessage>::getSingletonPtr()->get(true);
		message->setMessageType(TimerTaskMessage::TM_UPDATE);
		message->setDelta(delta);
		message->setAbsTime(absTime);

		NotificationManager::getSingleton().queueNotification(message);
	}

} // Myoushu

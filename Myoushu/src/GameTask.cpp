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
 * @file GameTask.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>

#include "Constants.h"
#include "GameTask.h"
#include "NotificationManager.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(GameTask, "Myoushu::GameTask");

	GameTask::GameTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
	{
		state = TS_CREATED;
	}

	GameTask::GameTask() : Task("GameTask", 0)
	{
		state = TS_CREATED;
	}

	GameTask::~GameTask()
	{
		// Destroy the message queue for this task
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void GameTask::init() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Initializing GameTask.");

		Poco::ScopedRWLock lock(rwLock, true);
		state = TS_INITIALIZED;
	}

	void GameTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void GameTask::execute(unsigned long timeDelta)
	{
		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}

		rwLock.unlock();

		// Receive any notifications queued for this Task.
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void GameTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);
		state = TS_KILLED;
	}


} // Myoushu


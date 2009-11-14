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
 * @file Task.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>

#include "Poco/RWLock.h"

#include "Task.h"
#include "Exception.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(Task, "Myoushu::Task");

	Task::Task() : NamedInstance("Task"), state(TS_CREATED), timeLastExecuted(-1.0), priority(0), executionInterval(0.0)
	{
	}

	Task::Task(int priority, unsigned long executionInterval, unsigned int iterationLimit) : NamedInstance("Task"), state(TS_CREATED)
		, timeLastExecuted(-1.0), priority(priority), executionInterval(executionInterval), iterationLimit(iterationLimit)
	{
	}

	Task::Task(const std::string& name, int priority, unsigned long executionInterval, unsigned int iterationLimit) : NamedInstance(name), state(TS_CREATED)
		, timeLastExecuted(-1.0), priority(priority), executionInterval(executionInterval), iterationLimit(iterationLimit)
	{
	}

	Task::~Task()
	{
	}

	void Task::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_INITIALIZED;
	}

	void Task::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void Task::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

} // Myoushu


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
 * @file CallbackTask.h
 * @author ME Chamberlain
 * @date March 2009
 */

#include "CallbackTask.h"

namespace Myoushu
{
	CLASS_NAME(CallbackTask, "Myoushu::CallbackTask");

	CallbackTask::CallbackTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit)
		: Task(name, priority, executionInterval, iterationLimit), mpInitFunctor(NULL), mpSuspendFunctor(NULL), mpExecuteFunctor(NULL)
		, mpKillFunctor(NULL)

	{
		setState(TS_CREATED);
	}

	CallbackTask::CallbackTask() : Task(), mpInitFunctor(NULL), mpSuspendFunctor(NULL), mpExecuteFunctor(NULL), mpKillFunctor(NULL)
	{
		setState(TS_CREATED);
	}

	CallbackTask::~CallbackTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Destroying CallbackTask.");
	}

	void CallbackTask::init() throw (Exception)
	{
		FunctorBase *f;

		setState(TS_INITIALIZED);

		f = getInitCallback();
		if (f != NULL)
		{
			(*f)();
		}
	}

	void CallbackTask::suspend()
	{
		FunctorBase *f;

		setState(TS_SUSPENDED);

		f = getSuspendCallback();
		if (f != NULL)
		{
			(*f)();
		}
	}

	void CallbackTask::execute(unsigned long timeDelta)
	{
		Value val;
		FunctorBase *f;
		
		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		f = getExecuteCallback();
		if (f != NULL)
		{
			val.set(timeDelta);
			if (f->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				static_cast<LuaExecuteCallbackFunction*>(f)->setParameter1(timeDelta);
			}
			else
			{
				f->setParameter(0, val);
			}
			(*f)();
		}
	}

	void CallbackTask::kill()
	{
		FunctorBase *f;

		setState(TS_KILLED);

		f = getKillCallback();

		if (f != NULL)
		{
			(*f)();
		}
	}

} // Myoushu

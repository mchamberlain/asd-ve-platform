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

#ifndef CALLBACK_TASK_H
#define CALLBACK_TASK_H

#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Task.h"
#include "NamedObject.h"
#include "TimerTaskMessage.h"
#include "FunctorBase.h"
#include "LuaFunctor.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * A Task implementation that can be used in scripts. Every function, init(), suspend(), execute() and kill() have an associated
	 * FunctorBase instance. This Task executes the appropriate Functor in each of its functions. Thus this class can be used to link the
	 * Task with a scripted version and then insert it into the Kernel.
	 */
	class MYOUSHU_API CallbackTask : public Task, public NamedObject<CallbackTask>
	{
		public:
			/** Type definition for a Lua callback function for zero parameter functions (init(), suspend(), kill()). */
			typedef LuaFunctor<void, 0> LuaCallbackFunction;
			/** Type definition for a Lua callback function for single unsinged int parameter functions (execute(timeDelta)). */
			typedef LuaFunctor<void, 1, unsigned int> LuaExecuteCallbackFunction;

			/**
			 * Constructor.
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
			CallbackTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			CallbackTask();

			/** Destructor */
			~CallbackTask();

			CLASS_NAME_FUNCTIONS(CallbackTask);

			/**
			 * Initializes the task.
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

			/** Sets the callback for the init() function. */
			void setInitCallback(FunctorBase *pFunctor);
			
			/** Sets the callback for the init() function. */
			void setInitCallback(const std::string& luaFunctionName);

			/** Sets the callback for the suspend() function. */
			void setSuspendCallback(FunctorBase *pFunctor);
			
			/** Sets the callback for the suspend() function. */
			void setSuspendCallback(const std::string& luaFunctionName);

			/** Sets the callback for the execute() function. */
			void setExecuteCallback(FunctorBase *pFunctor);
			
			/** Sets the callback for the execute() function. */
			void setExecuteCallback(const std::string& luaFunctionName);

			/** Sets the callback for the kill() function. */
			void setKillCallback(FunctorBase *pFunctor);
			
			/** Sets the callback for the kill() function. */
			void setKillCallback(const std::string& luaFunctionName);

			/** Gets the callback for the init() function. */
			FunctorBase* getInitCallback();

			/** Gets the callback for the suspend() function. */
			FunctorBase* getSuspendCallback();

			/** Sets the callback for the execute() function. */
			FunctorBase* getExecuteCallback();

			/** Sets the callback for the kill() function. */
			FunctorBase* getKillCallback();

		protected:
			/** Functor for the init() function. */
			Poco::AutoPtr<FunctorBase> mpInitFunctor;
			/** Functor for the suspend() function. */
			Poco::AutoPtr<FunctorBase> mpSuspendFunctor;
			/** Functor for the execute() function. */
			Poco::AutoPtr<FunctorBase> mpExecuteFunctor;
			/** Functor for the kill() function. */
			Poco::AutoPtr<FunctorBase> mpKillFunctor;
	};

	inline void CallbackTask::setInitCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpInitFunctor = pFunctor;
	}
	
	inline void CallbackTask::setInitCallback(const std::string& luaFunctionName)
	{
		LuaFunctorBase *pLuaFunctorBase;

		Poco::ScopedRWLock lock(rwLock, true);

		pLuaFunctorBase = new LuaCallbackFunction(luaFunctionName);
		pLuaFunctorBase->setQueue(false);
		mpInitFunctor = pLuaFunctorBase;
	}

	inline void CallbackTask::setSuspendCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpSuspendFunctor = pFunctor;
	}
	
	inline void CallbackTask::setSuspendCallback(const std::string& luaFunctionName)
	{
		LuaFunctorBase *pLuaFunctorBase;

		Poco::ScopedRWLock lock(rwLock, true);

		pLuaFunctorBase = new LuaCallbackFunction(luaFunctionName);
		pLuaFunctorBase->setQueue(false);
		mpSuspendFunctor = pLuaFunctorBase;
	}

	inline void CallbackTask::setExecuteCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpExecuteFunctor = pFunctor;
	}
	
	inline void CallbackTask::setExecuteCallback(const std::string& luaFunctionName)
	{
		LuaFunctorBase *pLuaFunctorBase;

		Poco::ScopedRWLock lock(rwLock, true);

		pLuaFunctorBase = new LuaExecuteCallbackFunction(luaFunctionName, "unsigned int");
		pLuaFunctorBase->setQueue(false);
		mpExecuteFunctor = pLuaFunctorBase;
	}

	inline void CallbackTask::setKillCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpKillFunctor = pFunctor;
	}
	
	inline void CallbackTask::setKillCallback(const std::string& luaFunctionName)
	{
		LuaFunctorBase *pLuaFunctorBase;

		Poco::ScopedRWLock lock(rwLock, true);

		pLuaFunctorBase = new LuaCallbackFunction(luaFunctionName);
		pLuaFunctorBase->setQueue(false);
		mpKillFunctor = pLuaFunctorBase;
	}

	inline FunctorBase* CallbackTask::getInitCallback()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpInitFunctor;
	}

	inline FunctorBase* CallbackTask::getSuspendCallback()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpSuspendFunctor;
	}

	inline FunctorBase* CallbackTask::getExecuteCallback()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpExecuteFunctor;
	}

	inline FunctorBase* CallbackTask::getKillCallback()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpKillFunctor;
	}

} // Myoushu

#endif

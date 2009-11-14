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
 * @file ScriptTask.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>

#include "Poco/RWLock.h"

#include "ScriptTask.h"
#include "ScriptManager.h"
#include "ScriptMessage.h"
#include "NotificationManager.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(ScriptTask, "Myoushu::ScriptTask");

	ScriptTask::ScriptTask() : Task(0)
	{
		state = TS_CREATED;
	}

	ScriptTask::ScriptTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
	{
		state = TS_CREATED;
	}

	ScriptTask::~ScriptTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());
	}

	void ScriptTask::init() throw (Exception)
	{
		ScriptManager *scriptManager;

		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing ScriptTask.");

		// Ensure that the ScriptManager Singleton exists
		scriptManager = ScriptManager::getSingletonPtr();
		if (scriptManager == NULL)
		{
			scriptManager = new ScriptManager();
		}

		// Get a pointer to the LuaParser
		luaParser = &(scriptManager->getDefaultLuaParser());

		// Register a handler for ScripMessages
		NotificationManager::getSingleton().addObserver(this, &ScriptTask::receiveScriptMessage);

		state = TS_INITIALIZED;
	}

	void ScriptTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void ScriptTask::execute(unsigned long timeDelta)
	{
		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		// Tell the NotificationManager to deliver all queued messages for this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void ScriptTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Unregister the handler for ScriptMessages
		NotificationManager::getSingleton().removeObserver(this, &ScriptTask::receiveScriptMessage);

		// Remove any queues and NotificationCenters created for this Task
		NotificationManager::getSingleton().removeQueue((memUInt) this);

		state = TS_KILLED;
	}

	void ScriptTask::receiveScriptMessage(const Poco::AutoPtr<ScriptMessage>& message)
	{
		LuaFunctorBase *luaFunctor;
		Poco::ScopedRWLock lock(rwLock, false);

		// Check that the message is not NULL
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "ScriptTask::receiveScriptMessage(): message is NULL.");

			return;
		}

		switch (message->getMessageType())
		{
			case ScriptMessage::SM_EXECUTE:
				// Check that there is a LuaParser instance set up
				if (luaParser == NULL)
				{
					LOG(EngineLog::LM_ERROR, "ScriptTask::receiveScriptMessage(): No LuaParser available.");

					return;
				}

				try
				{
					// Execute the script
					luaParser->execute(message->getScript());
				}
				catch (Exception& e)
				{
					LOG(EngineLog::LM_ERROR, "Error executing LUA script: " << e.what());
				}
				catch (std::exception& e)
				{
					LOG(EngineLog::LM_ERROR, "Error executing LUA script: " << e.what());
				}
				catch (...)
				{
					LOG(EngineLog::LM_ERROR, "Error while executing LUA script.");
				}
			break;
			case ScriptMessage::SM_EXECUTE_LUA_FUNCTOR:
				// Check that there is a LuaParser instance set up
				if (luaParser == NULL)
				{
					LOG(EngineLog::LM_ERROR, "ScriptTask::receiveScriptMessage(): No LuaParser available.");

					return;
				}

				try
				{
					// Execute the function
					luaFunctor = const_cast<LuaFunctorBase*>(message->getLuaFunctor());
					if (luaFunctor == NULL)
					{
						LOG(EngineLog::LM_ERROR, "ScriptTask::receiveScriptMessage(): Invalid Lua Functor.");

						return;
					}

					luaParser->getLuaStateLock(true);
					(*luaFunctor)(luaParser->getLuaState());
					luaParser->releaseLuaStateLock();
				}
				catch (Exception& e)
				{
					luaParser->releaseLuaStateLock();
					LOG(EngineLog::LM_ERROR, "Error executing LUA script (" << luaFunctor->getFunctionName() << "): " << e.what());
				}
				catch (std::exception& e)
				{
					luaParser->releaseLuaStateLock();
					LOG(EngineLog::LM_ERROR, "Error executing LUA script (" << luaFunctor->getFunctionName() << "): " << e.what());
				}
				catch (...)
				{
					luaParser->releaseLuaStateLock();
					LOG(EngineLog::LM_ERROR, "Error while executing LUA script (" << luaFunctor->getFunctionName() << "(.");
				}
			break;
			case ScriptMessage::SM_SLEEP:
				// todo
			break;
			case ScriptMessage::SM_UNKNOWN:
			default:
				LOG(EngineLog::LM_WARNING, "ScriptTask::receiveScriptMessage(): unknown message type.");
			break;
		}
	}
} // Myoushu

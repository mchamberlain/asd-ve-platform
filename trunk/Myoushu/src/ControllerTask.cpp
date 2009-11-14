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
 * @file ControllerTask.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "ControllerTask.h"
#include "EngineLog.h"
#include "NotificationManager.h"

namespace Myoushu
{
	CLASS_NAME(ControllerTask, "Myoushu::ControllerTask");

	ControllerTask::ControllerTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) 
		: Task(name, priority, executionInterval, iterationLimit)
	{
	}

	ControllerTask::ControllerTask() : Task(0)
	{
	}

	ControllerTask::~ControllerTask()
	{
		// Remove any message queues associated with this instance
		NotificationManager::getSingleton().removeQueue((memUInt) this);

		controllers.clear();
	}

	void ControllerTask::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Add an observer for AnimationTaskMessages to this instance
		NotificationManager::getSingleton().addObserver(this, &ControllerTask::receiveControllerTaskMessage);

		state = TS_INITIALIZED;
	}

	void ControllerTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Remove message observer
		NotificationManager::getSingleton().removeObserver(this, &ControllerTask::receiveControllerTaskMessage);

		state = TS_SUSPENDED;
	}

	void ControllerTask::execute(unsigned long timeDelta)
	{
		ControllersMapIterator iter;

		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}
		rwLock.unlock();

		// Dispatch all waiting messages of this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

		// Get a read lock
		Poco::ScopedRWLock lock(rwLock, false);

		// Call the update function in all Controllers registered with this Task
		for (iter = controllers.begin(); iter != controllers.end(); ++iter)
		{
			Controller *controller = iter->second;

			controller->update(timeDelta);
		}
	}

	void ControllerTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void ControllerTask::receiveControllerTaskMessage(const Poco::AutoPtr<ControllerTaskMessage>& message)
	{
		Controller *controller;
		ControllersMapIterator iter;

		// Check that the message is not NULL
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "ControllerTask::receiveControllerTaskMessage(): message is NULL!");
			return;
		}

		controller = const_cast<Controller *>(message->getController());

		switch (message->getMessageType())
		{
			case ControllerTaskMessage::CTM_ADD:
				// Add the Controller to the Controllers managed by this Task
				if (controller != NULL)
				{
					Poco::ScopedRWLock lock(rwLock, true);
					controllers[controller->getName()] = controller;
				}
				else
				{
					LOG(EngineLog::LM_WARNING, "ControllerTask::receiveControllerTaskMessage(): attempted to add NULL Controller.");
				}
				break;

			case ControllerTaskMessage::CTM_REMOVE:
				// Remove the Controller from this Task
				if (controller != NULL)
				{
					Poco::ScopedRWLock lock(rwLock, true);
					
					iter = controllers.find(controller->getName());
					if (iter != controllers.end())
					{
						controllers.erase(iter);
					}
					else
					{
						LOG(EngineLog::LM_WARNING, "ControllerTask::receiveControllerTaskMessage(): failed to remove controller: " << controller->getName() << ", no such controller.");
					}
				}
				else
				{
					LOG(EngineLog::LM_WARNING, "ControllerTask::receiveControllerTaskMessage(): attempted to add NULL Controller.");
				}
				break;
			
			case ControllerTaskMessage::CTM_UNKNOWN:
			default:
				LOG(EngineLog::LM_WARNING, "ControllerTask::receiveControllerTaskMessage(): unknown message received.");
				break;
		}
	}

} // Myoushu

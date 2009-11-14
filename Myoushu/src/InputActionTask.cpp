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
 * @file InputActionTask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "InputActionTask.h"
#include "Constants.h"
#include "Config.h"
#include "InputActionCallbackBase.h"
#include "InputActionManager.h"
#include "Console.h"

namespace Myoushu
{
	CLASS_NAME(InputActionTask, "Myoushu::InputActionTask");

	InputActionTask::InputActionTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
	{
		state = TS_CREATED;
	}

	InputActionTask::InputActionTask() : Task("InputActionTask", 0)
	{
		state = TS_CREATED;
	}

	InputActionTask::~InputActionTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		// Remove message queue
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void InputActionTask::init() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Initializing InputActionTask.");

		// Register the InputActionTask message handler functions
		NotificationManager::getSingleton().addObserver<InputActionTask, InputMessage>(this, &InputActionTask::receiveInputMessage);

		setState(TS_INITIALIZED);
	}

	void InputActionTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		setState(TS_SUSPENDED);
	}

	void InputActionTask::execute(unsigned long timeDelta)
	{
		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		// Receive any messages that have been queued for this Task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void InputActionTask::kill()
	{
		// Unregister the InputDeviceMessage observer in this task
		NotificationManager::getSingleton().removeObserver<InputActionTask, InputMessage>(this, &InputActionTask::receiveInputMessage);

		setState(TS_KILLED);
	}

	void InputActionTask::receiveInputMessage(const Poco::AutoPtr<InputMessage>& message)
	{
		std::list<InputActionCallbackBase*> callbackList;
		std::list<InputActionCallbackBase*>::iterator iter;

		// if message is NULL, log a warning and exit the function
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "InputActionTask::receiveInputMessage(): received a NULL input message.");

			return;
		}

		// Skip messages with blank actions
		if (message->getInputAction() == InputMessage::NO_ACTION)
		{
			return;
		}

		Poco::AutoPtr<InputMessage> inputMessage = message->clone();

		if ((inputMessage->getDeviceAction() == InputDeviceMessage::DA_RELEASE) && (inputMessage->getInputAction() == Constants::INPUT_ACTION_CONSOLE))
		{
			// Show the GUI
			Console::getSingleton().toggleVisible();
		}
		else if ((inputMessage->getInputDevice() == NULL) || (InputActionManager::getSingleton().isCallbacksForActionEnabled(inputMessage->getInputAction())))
		{
			// Get the list of callbacks for this input action
			InputActionManager::getSingleton().getInputActionCallbacks(inputMessage->getInputAction(), callbackList);
			// Call them one by one
			for (iter = callbackList.begin(); iter != callbackList.end(); ++iter)
			{
				(*iter)->executeCallback(inputMessage);
			}
		}
	}

} // Myoushu

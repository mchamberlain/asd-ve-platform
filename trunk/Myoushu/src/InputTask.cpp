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
 * @file InputTask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>
#include <sstream>
#include <iostream>

#include "OIS.h"
#include "Ogre.h"

#include "InputTask.h"
#include "Constants.h"
#include "EngineLog.h"
#include "InputDeviceFactory.h"
#include "NotificationManager.h"
#include "Config.h"
#include "InputActionCallbackBase.h"
#include "InputActionManager.h"
#include "Constants.h"
#include "Console.h"

namespace Myoushu
{
	CLASS_NAME(InputTask, "Myoushu::InputTask");

	const Ogre::Real InputTask::DEFAULT_MOUSE_SENSITIVITY = 1.0;

	InputTask::InputTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
	{
		state = TS_CREATED;
	}

	InputTask::InputTask() : Task("InputTask", 0)
	{
		state = TS_CREATED;
	}

	InputTask::~InputTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		// Remove message queue
		NotificationManager::getSingleton().removeQueue((memUInt) this);

		// Destroy the InputDevieFactory
		if (InputDeviceFactory::getSingletonPtr())
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying InputDeviceFactory");
			delete InputDeviceFactory::getSingletonPtr();
		}

		if (inputManager)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying OIS InputManager");
			OIS::InputManager::destroyInputSystem(inputManager);
		}
	}

	void InputTask::init() throw (Exception)
	{
		InputDeviceFactory *inputDeviceFactory;
		OIS::ParamList pl;
		Ogre::RenderWindow *window;
		std::ostringstream windowHndStr;
		size_t windowHnd;
		unsigned int oisVersion;
		std::ostringstream devName;

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing InputTask.");

		windowHnd = 0;
		window = (Ogre::RenderWindow*) Ogre::Root::getSingleton().getRenderTarget(Constants::MAIN_RENDER_TARGET);

		// Get the window handle
		window->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;

		try {
			// Create the InputDeviceFactory
			LOG(EngineLog::LM_INFO_ENGINE, "Creating InputDeviceFactory");
			inputDeviceFactory = new InputDeviceFactory();

			// Create the input manager
			pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

			LOG(EngineLog::LM_INFO_ENGINE, "Initializing OIS");
			inputManager = OIS::InputManager::createInputSystem(pl);

			// Log OIS startup and version info
			oisVersion = inputManager->getVersionNumber();
			LOG(EngineLog::LM_INFO_ENGINE, "OIS Version: " << (oisVersion >> 16 ) << "." << ((oisVersion >> 8) & 0x000000FF) << "." << (oisVersion & 0x000000FF)
				<< "\n\tRelease Name: " << inputManager->getVersionName()
				<< "\n\tPlatform: " << inputManager->inputSystemName()
				<< "\n\tNumber of Mice: " << inputManager->getNumberOfDevices(OIS::OISMouse)
				<< "\n\tNumber of Keyboards: " << inputManager->getNumberOfDevices(OIS::OISKeyboard)
				<< "\n\tNumber of Joys/Pads = " << inputManager->getNumberOfDevices(OIS::OISJoyStick));

			// Set default settings
			Config& config = Config::getSingleton();
			if (config.hasProperty(Config::INPUT_MOUSE_SENSITIVITY) == false)
			{
				config.setDouble(Config::INPUT_MOUSE_SENSITIVITY, DEFAULT_MOUSE_SENSITIVITY);
			}

			// Iterate through the detected devices and create OISInputDevice instances for them
			for (int i = 0; i < inputManager->getNumberOfDevices(OIS::OISKeyboard); i++)
			{
				OIS::Keyboard *keyboard = dynamic_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));

				devName.str("");
				devName << KeyboardOISInputDevice::INPUT_DEVICE_NAME << i;

				LOG(EngineLog::LM_INFO_ENGINE, "Creating KeyboardOISInputDevice: " << keyboard->vendor());
				keyboard->setEventCallback(inputDeviceFactory->make(keyboard, devName.str()));
			}

			for (int i = 0; i < inputManager->getNumberOfDevices(OIS::OISMouse); i++)
			{
				// Create the mouse
				OIS::Mouse *mouse = dynamic_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

				// Set the width and height to the current resolution
				mouse->getMouseState().width = Config::getSingleton().getInt(Config::VID_WIDTH);
				mouse->getMouseState().height = Config::getSingleton().getInt(Config::VID_HEIGHT);

				devName.str("");
				devName << MouseOISInputDevice::INPUT_DEVICE_NAME << i;

				LOG(EngineLog::LM_INFO_ENGINE, "Creating MouseOISInputDevice: " << mouse->vendor());
				mouse->setEventCallback(inputDeviceFactory->make(mouse, devName.str()));
			}

			// Register the InputTask message handler functions
			NotificationManager::getSingleton().addObserver<InputTask, InputDeviceMessage>(this, &InputTask::receiveInputDeviceMessage);

			state = TS_INITIALIZED;
		}
		catch (OIS::Exception& e)
		{
			throw Exception(Exception::E_OIS_EXCEPTION, e.eText);
		}
		catch (Exception& e)
		{
			throw e;
		}


	}

	void InputTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void InputTask::execute(unsigned long timeDelta)
	{
		InputDeviceFactory::DevicesIterator iter;
		InputDeviceFactory *inputDeviceFactory;

		rwLock.writeLock();
		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}
		rwLock.unlock();

		inputDeviceFactory = InputDeviceFactory::getSingletonPtr();

		// Loop through the InputDevices and update them
		for (iter = inputDeviceFactory->getDevicesIteratorBegin(); iter != inputDeviceFactory->getDevicesIteratorEnd(); ++iter)
		{
			(*iter)->capture();
		}

		// Receive any messages that have been queued for this Task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);
	}

	void InputTask::kill()
	{
		// Unregister the InputDeviceMessage observer in this task
		NotificationManager::getSingleton().removeObserver<InputTask, InputDeviceMessage>(this, &InputTask::receiveInputDeviceMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void InputTask::receiveInputDeviceMessage(const Poco::AutoPtr<InputDeviceMessage>& message)
	{
		unsigned int actionCnt;
		std::ostringstream sStream;

		// If inputMessage is NULL, log a warning and exit the function
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "InputTask::receiveInputDeviceMessage(): received a NULL input message.");

			return;
		}

		// Get an InputMessage instance
		Poco::AutoPtr<InputMessage> inputMessage = ObjectPool<InputMessage>::getSingleton().get(true);
		// Populate it with the content from the InputDeviceMessage
		message->clone(inputMessage);

		actionCnt = 0;
		if (inputMessage->getInputDevice() != NULL)
		{
			// Get the InputDevice instance that spawned the InputDeviceMessage
			const InputDevice *inputDevice = inputMessage->getInputDevice();

			// Loop through the array of input identifier strings and fetch a binding from the config singleton
			for (unsigned int i = 0; i < MAX_NUMBER_OF_INPUT_IDENTIFIERS; i++)
			{
				const std::string& inputIdentifier = inputMessage->getInputIdentifier(i);
				
				// If the input identifier is blank we have reached the end of the array, break out of the loop
				if (inputIdentifier.length() == 0)
				{
					break;
				}

				// Construct the configuration string for the key/button/axis binding
				sStream.str("");
				sStream << Config::INPUT_PREFIX << "." << inputDevice->getName() << "." << inputIdentifier;

				// Fetch the bound action from the config system
				inputMessage->setInputAction(Config::getSingleton().getString(sStream.str(), InputMessage::NO_ACTION));

				// If action is disabled, leave the action field on NO_ACTION
				if (InputActionManager::getSingleton().isCallbacksForActionEnabled(inputMessage->getInputAction()) == false)
				{
					inputMessage->setInputAction(InputMessage::NO_ACTION);
				}

				// Send the InputMessage with the internal communication system
				if (inputMessage->getInputAction() != InputMessage::NO_ACTION)
				{
					NotificationManager::getSingleton().queueNotification(inputMessage->clone());
					actionCnt++;
				}
			}

		}
		if (actionCnt == 0)
		{
			// If no actions exist for this message send it anyway
			NotificationManager::getSingleton().queueNotification(inputMessage->clone());
		}

	}

} // Myoushu

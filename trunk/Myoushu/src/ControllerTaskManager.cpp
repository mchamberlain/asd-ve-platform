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
 * @file ControllerTaskManager.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "ControllerTaskManager.h"
#include "ControllerTaskMessage.h"
#include "ObjectPool.h"
#include "ControllerFactory.h"
#include "NotificationManager.h"

namespace Myoushu
{
	ControllerTaskManager::ControllerTaskManager()
	{
	}

	ControllerTaskManager::~ControllerTaskManager()
	{
	}

	void ControllerTaskManager::addController(Controller *controller) throw (Exception)
	{
		ControllerTaskMessage *message;

		// Ensure that controller is not NULL. If it is NULL, throw an exception
		if (controller == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ControllerTaskManager::addController(): controller is NULL");
		}

		// Get a message instance from the object pool
		message = ObjectPool<ControllerTaskMessage>::getSingleton().get(true);

		// Populate the message
		message->setMessageType(ControllerTaskMessage::CTM_ADD);
		message->setController(controller);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	bool ControllerTaskManager::addController(const Ogre::String& name)
	{
		ControllerTaskMessage *message;
		Controller *controller;

		// Find the Controller instance by name
		controller = ControllerFactory::getSingleton().find(name);

		// If the Controller instance could not be found, return false
		if (controller == NULL)
		{
			return false;
		}

		// Get a message instance from the object pool
		message = ObjectPool<ControllerTaskMessage>::getSingleton().get(true);

		// Populate the message
		message->setMessageType(ControllerTaskMessage::CTM_ADD);
		message->setController(controller);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

	void ControllerTaskManager::removeController(Controller *controller) throw (Exception)
	{
		ControllerTaskMessage *message;

		// Ensure that controller is not NULL. If it is NULL, throw an exception
		if (controller == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ControllerTaskManager::removeController(): controller is NULL");
		}

		// Get a message instance from the object pool
		message = ObjectPool<ControllerTaskMessage>::getSingleton().get(true);

		// Populate the message
		message->setMessageType(ControllerTaskMessage::CTM_REMOVE);
		message->setController(controller);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	bool ControllerTaskManager::removeController(const Ogre::String& name)
	{
		ControllerTaskMessage *message;
		Controller *controller;

		// Find the Controller instance by name
		controller = ControllerFactory::getSingleton().find(name);

		// If the Controller instance could not be found, return false
		if (controller == NULL)
		{
			return false;
		}

		// Get a message instance from the object pool
		message = ObjectPool<ControllerTaskMessage>::getSingleton().get(true);

		// Populate the message
		message->setMessageType(ControllerTaskMessage::CTM_REMOVE);
		message->setController(controller);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);

		return true;
	}

} // namespace Myoushu

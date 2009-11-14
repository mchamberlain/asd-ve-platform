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
 * @file KernelManager.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "KernelManager.h"
#include "NotificationManager.h"
#include "KernelMessage.h"
#include "ObjectPool.h"

//template<>
//Myoushu::KernelManager* Ogre::Singleton<Myoushu::KernelManager>::ms_Singleton = NULL;

namespace Myoushu
{
	KernelManager::KernelManager()
	{
	}

	KernelManager::~KernelManager()
	{
	}

	void KernelManager::stopKernel()
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		//message = new KernelMessage(KernelMessage::KM_SHUTDOWN);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_SHUTDOWN);

		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::addTask(Task *task) throw (Exception)
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Check that task is not NULL, if it is throw an exception
		if (task == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KernelManager::addTask(): task is NULL!");
		}

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_ADD_TASK, task);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_ADD_TASK);
		message->setTask(task);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::suspendTask(Task *task) throw (Exception)
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Check that task is not NULL, if it is throw an exception
		if (task == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KernelManager::suspendTask(): task is NULL!");
		}

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_SUSPEND_TASK, task);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_SUSPEND_TASK);
		message->setTask(task);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::suspendTask(const std::string& name)
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_SUSPEND_TASK, NULL, name);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_SUSPEND_TASK);
		message->setTaskName(name);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::removeTask(Task *task) throw (Exception)
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Check that task is not NULL, if it is throw an exception
		if (task == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KernelManager::removeTask(): task is NULL!");
		}

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_REMOVE_TASK, task);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_REMOVE_TASK);
		message->setTask(task);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::removeTask(const std::string& name)
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_REMOVE_TASK, NULL, name);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_REMOVE_TASK);
		message->setTaskName(name);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void KernelManager::initAllTasks()
	{
		KernelMessage *message;

		Poco::ScopedRWLock lock(rwLock, false);

		// Create the message
		//message = new KernelMessage(KernelMessage::KM_INIT_ALL_TASKS);
		message = ObjectPool<KernelMessage>::getSingleton().get(true);
		message->setMessageType(KernelMessage::KM_INIT_ALL_TASKS);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

} // Myoushu




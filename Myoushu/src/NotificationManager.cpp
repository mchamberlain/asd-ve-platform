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
 * @file NotificationManager.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <iostream>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Poco/Notification.h"
#include "Poco/NotificationQueue.h"
#include "Poco/AbstractObserver.h"
#include "Poco/NObserver.h"
#include "Ogre.h"

#include "NotificationManager.h"
#include "NotificationCenter.h"
#include "Message.h"

//template<>
//Myoushu::NotificationManager* Ogre::Singleton<Myoushu::NotificationManager>::ms_Singleton = NULL;

namespace Myoushu
{
	NotificationManager::NotificationManager() : objectQueueMapChanged(true)
	{
	}

	NotificationManager::~NotificationManager()
	{
	}

	void NotificationManager::sendNotification(Message *message) throw (Exception)
	{
		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::sendNotification(): message is NULL.");
		}

		NotificationCenter::defaultCenter().postNotification(message);
	}

	void NotificationManager::queueNotification(Message* message) throw (Exception)
	{
		MessageQueueMapIterator iter;
		std::pair<MessageQueueMapIterator, MessageQueueMapIterator> range;
		Poco::AutoPtr<Message> msgPtr;

		Poco::ScopedRWLock lock(rwLockMessageQueueMap, false);

		// Check that message is not NULL
		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::queueNotification(): message is NULL.");
		}

		msgPtr = message;

		// Get all the queues that exist for the message type
		range = messageQueueMap.equal_range(msgPtr->getClassName());

		// Enqueue the messages in all of the relevant queues
		for (iter = range.first; iter != range.second; ++iter)
		{
			iter->second->enqueueMessage(msgPtr);
		}
	}

	void NotificationManager::queueUrgentNotification(Message* message) throw (Exception)
	{
		MessageQueueMapIterator iter;
		std::pair<MessageQueueMapIterator, MessageQueueMapIterator> range;
		Poco::AutoPtr<Message> msgPtr;

		Poco::ScopedRWLock lock(rwLockMessageQueueMap, false);

		// Check that message is not NULL
		if (message == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::queueUrgentNotification(): message is NULL.");
		}

		msgPtr = message;

		// Get all the queues that exist for the message type
		range == messageQueueMap.equal_range(msgPtr->getClassName());

		// Enqueue the messages in all of the relevant queues
		for (iter = range.first; iter != range.second; ++iter)
		{
			iter->second->enqueueMessage(msgPtr, true);
		}
	}

	void NotificationManager::dispatchQueuedNotifications()
	{
		ObjectQueueMapIterator iter;

		if (isObjectQueueMapChanged())
		{
			// If objectQueueMap has changed, update objectQueueMapClone
			Poco::ScopedRWLock lockObjectQueueMap(rwLockObjectQueueMap, false);
			Poco::ScopedRWLock lockObjectQueueMapClone(rwLockObjectQueueMapClone, true);

			objectQueueMapClone.clear();
			objectQueueMapClone = objectQueueMap;

			setObjectQueueMapChanged(false);
		}

		Poco::ScopedRWLock lockObjectQueueMapClone(rwLockObjectQueueMapClone, false);

		// Dispatch all messages in all queues
		for (iter = objectQueueMapClone.begin(); iter != objectQueueMapClone.end(); ++iter)
		{
			MessageQueue *queue;
			NotificationCenter *center;

			// Get the NotificationCenter and the queue
			center = iter->second.first.get();
			queue = iter->second.second.get();

			// Dispatch all messages in the queue using the NotificationCenter associated with it
			queue->dispatch(*center);
		}
	}

	void NotificationManager::dispatchQueuedNotifications(memUInt object, unsigned int maxNumberToDispatch)
	{
		ObjectQueueMapIterator iter;

		rwLockObjectQueueMap.readLock();

		// Find the queue
		iter = objectQueueMap.find(object);

		if (iter != objectQueueMap.end())
		{
			MessageQueue *queue;
			NotificationCenter *center;

			// Get the NotificationCenter and the queue
			center = iter->second.first.get();
			queue = iter->second.second.get();

			// Release the lock
			rwLockObjectQueueMap.unlock();

			// Dispatch all (or maxNumberToDispatch) messages in the queue using the NotificationCenter associated with it
			queue->dispatch(*center, maxNumberToDispatch);
		}
		else
		{
			// Release the lock
			rwLockObjectQueueMap.unlock();
		}
	}

	bool NotificationManager::removeQueue(memUInt object) throw (Exception)
	{
		ObjectQueueMapIterator objectQueueMapIter;
		MessageQueueMapIterator messageQueueMapIter;
		Poco::AutoPtr<MessageQueue> queue;

		Poco::ScopedRWLock lockObjectQueueMap(rwLockObjectQueueMap, true);
		Poco::ScopedRWLock lockMessageQueueMap(rwLockMessageQueueMap, true);

		if (object == (memUInt) NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::removeQueue(): object is null.");
		}

		// Find the queue for the object.
		objectQueueMapIter = objectQueueMap.find(object);
		// Return false if no queue was found
		if (objectQueueMapIter == objectQueueMap.end())
		{
			return false;
		}
		queue = objectQueueMapIter->second.second;

		// Remove all of the associated entries from messageQueueMap
		for (messageQueueMapIter = messageQueueMap.begin(); messageQueueMapIter != messageQueueMap.end();)
		{
			if (messageQueueMapIter->second == queue)
			{
				messageQueueMap.erase(messageQueueMapIter++);
			}
			else
			{
				messageQueueMapIter++;
			}
		}

		objectQueueMap.erase(objectQueueMapIter);

		setObjectQueueMapChanged(true);

		return true;
	}

	void NotificationManager::removeObserverObject(memUInt object) throw (Exception)
	{
		NotificationObserverForFunctorMap::iterator iter;
		NotificationObserverForFunctor *pObserver;
		std::list<std::string> messageTypeList;

		Poco::ScopedRWLock lock(rwLockNotificationObserverForFunctorMap, true);

		// Find the NotificationObserverForFunctor instance associated with object
		iter = mNotificationObserverForFunctorMap.find(object);
		if (iter == mNotificationObserverForFunctorMap.end())
		{
			// No instance associated with object is found, just exit the function
			return;
		}

		pObserver = iter->second;
		if (pObserver->numMappedFunctors() > 0)
		{
			// Error: there are still observers for Functors in NotificationObserverForFunctor. These
			// must be removed with removeObserverFunctor<T>(object) before the NotificationObserverForFunctor
			// instance can be removed and destroyed.
			throw Exception(Exception::E_GENERAL_EXCEPTION, "NotificationManager::removeObserverObject(): there are still observers for Functors in NotificationObserverForFunctor. These must be removed with removeObserverFunctor<T>(object) before the NotificationObserverForFunctor instance can be removed and destroyed.");
		}

		// Remove any messages queues associated with object
		removeQueue(object);
		// Remove the NotificationObserverForFunctor - object mapping (this will destroy the 
		// NotificationObserverForFunctor instnace.
		mNotificationObserverForFunctorMap.erase(iter);
	}

} // Myoushu

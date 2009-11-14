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
 * @file NotificationManager.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <map>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Poco/Notification.h"
#include "Poco/AbstractObserver.h"
#include "Poco/NObserver.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "NotificationCenter.h"
#include "Message.h"
#include "Exception.h"
#include "NamedObject.h"
#include "MessageQueue.h"
#include "NotificationObserverForFunctor.h"

namespace Myoushu
{
	/**
	 * This class is uses the Poco::NotificationManager class to send messages between observers in the engine. The
	 * Kernel, for instance, observers KernelMessages and a Task in the engine can send the Kernel a message using
	 * the functions defined in the class.
	 *
	 * Synchronous and asynchronous message delivery is supported.
	 */

	class MYOUSHU_API NotificationManager : public Ogre::Singleton<NotificationManager>
	{
		public:
			/** Map of objects to MessageQueues */
			typedef std::map<memUInt, std::pair<Poco::AutoPtr<NotificationCenter>, Poco::AutoPtr<MessageQueue> > > ObjectQueueMap;
			/** Multi map of message types to MessageQueues */
			typedef std::multimap<std::string, Poco::AutoPtr<MessageQueue> > MessageQueueMultiMap;
			/** Iterator for the map of message types to MessageQueues. */
			typedef MessageQueueMultiMap::iterator MessageQueueMapIterator;
			/** Iterator for the map of objects to MessageQueues. */
			typedef ObjectQueueMap::iterator ObjectQueueMapIterator;
			/** A type definition of a multimap of the addresses to instances of NotificationObserverForFunctors created to allow for message delivery via Functors. */
			typedef std::map<memUInt, Poco::AutoPtr<NotificationObserverForFunctor> > NotificationObserverForFunctorMap;
			/** Type definition of an entry in a NotificationObserverForFunctorMap. */
			typedef NotificationObserverForFunctorMap::value_type NotificationObserverForFunctorMapEntry;

			/** Constructor. */
			NotificationManager();

			/** Destructor */
			~NotificationManager();

			/**
			 * Sends the notification to all receivers immediately.
			 * @param message The message to send (an instance of Poco::Notification).
			 *                The NotificationManager does not take ownership of the message, the caller of this function
			 *								must free the message after the function ends.
			 * @throw Exception::E_NULL_POINTER if message is NULL.
			 */
			void sendNotification(Message *message) throw (Exception);

			/**
			 * Queues a notification to be sent by the next call to
			 * dispatchQueuedNotifications. The NotificationManager takes ownership of the message and will free it
			 * when appropriate.
			 * @param message The message to queue.
			 * @throw Exception::E_NULL_POINTER if message is NULL.
			 */
			void queueNotification(Message* message) throw (Exception);

			/**
			 * Queues an urgent notification, by adding it to the front of the queue,
			 * to be sent by the next call to dispatchQueuedNotifications. The NotificationManager takes ownership of the message and will free it
			 * when appropriate.
			 * @param message The message to queue.
			 * @throw Exception::E_NULL_POINTER if message is NULL.
			 */
			void queueUrgentNotification(Message* message) throw (Exception);

			/**
			 * Dispatches all queued notifications.
			 */
			void dispatchQueuedNotifications();

			/**
			 * Dispatches all queued notifications relevant to a specific object.
			 * @param object The address of the object for which all queued messages must be
			 * dispatched.
			 * @param maxNumberToDispatch The maximum number of queued messages to dispatch. This can be
			 *							  used to limit the number of messages that will actually be
			 *							  processed from the queue. If this is set to 0 (the default)
			 *							  all messages from the queue will be processed. Messages not dispached
			 *							  stay in the queue and will be the first to be dispatched in
			 *							  subsequent calls.
			 */
			void dispatchQueuedNotifications(memUInt object, unsigned int maxNumberToDispatch = 0);

			/**
			 * Adds an object and its handler function as an observer to a notification type.
			 * @param object The object that receives notifications.
			 * @param handler The function of the object that will be called when notification of class N arrive.
			 * @param createQueue Should a dedicated queue be created for this object. This is used in asyncrhonous
			 * communication. Only one queue per object is created, so if an object registers observers for multiple message
			 * types, all of the messages go into one queue. If a queue for the object already exists, this parameter has
			 * no effect.
			 */
			template <class C, class N>
			void addObserver(C *object, void (C::*handler)(const Poco::AutoPtr<N>&), bool createQueue = true) throw (Exception);

			/**
			 * Adds an object and its handler function as an observer to a notification type. A Functor is used as handler in this case. This
			 * function should typically only be used to allow for delivery of messages to functions defined in script languages used with the
			 * engine, such as Lua, Python or Java.
			 * @param object The address of the NotificationObserverForFunctor instance that will be used in conjunction with the specified
			 *				 Functor to handle delivery to the functor. If this value is 0 a NotificationObserverForFunctor instance is created, 
			 *				 and its address is returned by this function. This function takes ownership of the NotificationObserverForFunctor
			 *				 instance. Typically this function will be called once with object = 0 so that a NotificationObserverForFunctor instance
			 *				 is created and returned. After that this function can be called again for other functors, with different types T, using the
			 *				 object address returned earlier by this function. So typically the NotificationObserverForFunctor instance would replace the
			 *				 the class C in the addObserver<C, N>() function.
			 * @param pFunctor The FunctorBase instance that wraps the function to call when a message of type T arrives.
			 * @param createQueue Should a dedicated queue be created for this object. This is used in asyncrhonous
			 * communication. Only one queue per object is created, so if an object registers observers for multiple message
			 * types, all of the messages go into one queue. If a queue for the object already exists, this parameter has
			 * no effect.
			 * @return The newly created NotificationObserverForFunctor instance address, or 0 if there was a problem.
			 * @throws Exception::E_NULL_POINTER if pFunctor is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if object is not 0 but an existing NotificationObserverForFunctor instance
			 *										associated with object does not exist.
			 */
			template<class T>
			memUInt addObserverFunctor(FunctorBase *pFunctor, memUInt object = 0, bool createQueue = true) throw (Exception);

			/**
			 * Removes an obverser object from the NotificationManager. No queues are deleted, the queues for
			 * objects are only destroyed in the destructor of this class, or by calling removeQueue(C *object).
			 * @param object The object that receives notifications.
			 * @param handler The function of the object that will be called when notification of class N arrive.
			 */
			template <class C, class N>
			void removeObserver(C *object, void (C::*handler)(const Poco::AutoPtr<N>&)) throw (Exception);

			/**
			 * Removes an obverser object from the NotificationManager that was previously added with addObserverFunctor. No queues are deleted, the queues for
			 * objects are only destroyed in the destructor of this class, or by calling removeQueue(memUInt object).
			 * @param object The object that receives notifications.
			 * @param handler The function of the object that will be called when notification of class N arrive.
			 * @throws Exception::E_INVALID_PARAMETERS if object is 0.
			 * @throws Exception::E_NO_SUCH_ELEMENT if object is not 0 but an existing NotificationObserverForFunctor instance
			 *										associated with object does not exist.
			 */
			template<class T>
			void removeObserverFunctor(memUInt object);

			/**
			 * Removes a NotificationObserverForFunctor instance created earlier by
			 * addObserverFunctor(). IMPORTANT: All handlers added with addObserverFunctor() for this
			 * value of object must first be removed by removeObserverFunctor() before this function is called.
			 * This function also removes any message queues associated with object.
			 * @param object The address associated with the NotificationObserverForFunctor instance to remove,
			 *				 created earlier by addObserverFunctor<T>().
			 */
			void removeObserverObject(memUInt object);

			/**
			 * Remove a queue associated with the specified object.
			 * @param object The object for which the associated queue will be removed.
			 * @return true if a queue was destroyed, false if no appropriate queue was found.
			 * @throw Exception if object is NULL.
			 */
			bool removeQueue(memUInt object) throw (Exception);

			/**
			 * Getter for the objectQueueMapChanged field.
			 * @return objectQueueMapChanged
			 */
			bool isObjectQueueMapChanged() const;

			/**
			 * Setter for objectQueueMapChanged field.
			 * @param changed The new value for objectQueueMapChanged.
			 */
			void setObjectQueueMapChanged(bool changed);

		protected:
			/** Read write mutex on the objectQueueMap */
			mutable Poco::RWLock rwLockObjectQueueMap;
			/** Read write mutex on the messageQueueMap. */
			mutable Poco::RWLock rwLockMessageQueueMap;
			/** Read write mutex on the objectQueueMapClone. */
			mutable Poco::RWLock rwLockObjectQueueMapClone;
			/** Read write mutex on the objectQueueMapChanged flag. */
			mutable Poco::RWLock rwLockObjectQueueMapChanged;
			/** Read/write mutex on the mNotificationObserverForFunctorMap. */
			mutable Poco::RWLock rwLockNotificationObserverForFunctorMap;
			/** A map to store the MessageQueues and NotificationCenters mapped to objects. */
			ObjectQueueMap objectQueueMap;
			/** A map to store the MessageQueues mapped to message types */
			MessageQueueMultiMap messageQueueMap;
			/**
			 * A clone of objectQueueMap, used while dispatching messages, so that other threads can queue new messages, create new queues
			 * etc. while message dispatcing is in progress.
			 */
			ObjectQueueMap objectQueueMapClone;
			/** A map of the the addresses to instances of NotificationObserverForFunctors created to allow for message delivery via Functors. */
			NotificationObserverForFunctorMap mNotificationObserverForFunctorMap;
			/** Flag indicating whether the objectQueueMap has been changed since its last clone. */
			bool objectQueueMapChanged;

	};

	// template definitions
	template <class C, class N>
	void NotificationManager::addObserver(C *object, void (C::*handler)(const Poco::AutoPtr<N>&), bool createQueue) throw (Exception)
	{
		Poco::AutoPtr<NotificationCenter> center;
		Poco::AutoPtr<MessageQueue> queue;

		if ((object == NULL) || (handler == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::addObserver(): object or handler is null.");
		}

		// Create the observer and add it to the default notification center
		Poco::NObserver<C, N> obs(*object, handler);
		NotificationCenter::defaultCenter().addObserver(obs);

		// Create a NotificationQueue and a NotificationCenter for the object it createQueue is true
		if (createQueue)
		{
			Poco::ScopedRWLock lockObjectQueueMap(rwLockObjectQueueMap, true);
			Poco::ScopedRWLock lockMessageQueueMap(rwLockMessageQueueMap, true);

			// Check whether the object already has a queue and center, if it doesn't create it otherwise just
			// fetch it
			if (objectQueueMap.count((memUInt) object) == 0)
			{
				std::pair<memUInt, std::pair<Poco::AutoPtr<NotificationCenter>, Poco::AutoPtr<MessageQueue> > > entry;

				center = new NotificationCenter();
				queue = new MessageQueue();

				entry.first = (memUInt) object;
				entry.second = std::make_pair(center, queue);
				objectQueueMap.insert(entry);

				setObjectQueueMapChanged(true);
			}
			else
			{
				std::pair<Poco::AutoPtr<NotificationCenter>, Poco::AutoPtr<MessageQueue> > entry;

				entry = objectQueueMap[(memUInt) object];
				center = entry.first;
				queue = entry.second;
			}

			std::pair<std::string, Poco::AutoPtr<MessageQueue> > entry;

			// Map the message type to the NotificationQueue of the handler object
			entry.first = NamedObject<N>::getStaticClassName();
			entry.second = queue;
			messageQueueMap.insert(entry);

			// Register the observer created earlier with the dedicated NotificationCenter of the handler object
			center->addObserver(obs);
		}
	}

	template<class T>
	memUInt NotificationManager::addObserverFunctor(FunctorBase *pFunctor, memUInt object, bool createQueue) throw (Exception)
	{
		NotificationObserverForFunctor *pObserver;

		// Check whether we should create a new instance of NotificationObserverForFunctor, or fetch one
		// from the map
		if (object == 0)
		{
			Poco::ScopedRWLock lock(rwLockNotificationObserverForFunctorMap, true);

			// Create new instance
			pObserver = new NotificationObserverForFunctor();
			object = reinterpret_cast<memUInt>(pObserver);
			// insert it into the map
			mNotificationObserverForFunctorMap.insert(NotificationObserverForFunctorMapEntry(object, pObserver));
		}
		else
		{
			Poco::ScopedRWLock lock(rwLockNotificationObserverForFunctorMap, false);

			// Fetch instance from map
			NotificationObserverForFunctorMap::iterator iter;
			iter = mNotificationObserverForFunctorMap.find(object);
			if (iter == mNotificationObserverForFunctorMap.end())
			{
				// No such entry in the map, throw an exception
				throw Exception(Exception::E_NO_SUCH_ELEMENT, "NotificationManager::addObserverFunctor(): the supplied object argument is invalid.");
			}
			pObserver = iter->second;
		}

		// Check that pObserver is not NULL
		if (pObserver == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::addObserverFunctor(): pObserver is NULL.");
		}

		// Add pFunctor as the handler for type T to pObserver
		pObserver->addFunctor(NamedObject<T>::getStaticClassName(), pFunctor);

		// Call the existing addObserver function so that messages are sent to pObserver. It acts as a proxy
		// and will call pFunctor for every message of type T it receives.
		addObserver<NotificationObserverForFunctor, T>(pObserver, &NotificationObserverForFunctor::handler<T>, createQueue);

		return reinterpret_cast<memUInt>(pObserver);
	}

	template <class C, class N>
	void NotificationManager::removeObserver(C *object, void (C::*handler)(const Poco::AutoPtr<N>&)) throw (Exception)
	{
		ObjectQueueMapIterator iter;

		Poco::ScopedRWLock lock(rwLockObjectQueueMap, true);

		if ((object == NULL) || (handler == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::removeObserver(): object or handler is null.");
		}

		// Remove the observer from the default center
		Poco::NObserver<C, N> obs(*object, handler);
		NotificationCenter::defaultCenter().removeObserver(obs);

		// Check wether the object has a dedicated NotificationCenter and queue and remove the observer
		// from that center as well
		iter = objectQueueMap.find((memUInt) object);

		if (iter != objectQueueMap.end())
		{
			std::pair<MessageQueueMultiMap::iterator, MessageQueueMultiMap::iterator> range;
			MessageQueueMultiMap::iterator messageQueueMapIter;

			NotificationCenter *center = iter->second.first.get();
			MessageQueue *queue = iter->second.second.get();

			// Remove the observer from the NotificationCenter of object
			center->removeObserver(obs);

			Poco::ScopedRWLock lock2(rwLockMessageQueueMap, true);
			
			// Remove the mapping between the message type and the queue, we allow only one hanlder per message type in a class instance
			range = messageQueueMap.equal_range(NamedObject<N>::getStaticClassName());
			messageQueueMapIter = range.first;
			for (messageQueueMapIter = range.first; messageQueueMapIter != range.second; ++messageQueueMapIter)
			{
				if (messageQueueMapIter->second == queue)
				{
					messageQueueMap.erase(messageQueueMapIter);
					break;
				}
			}
		}
	}

	template<class T>
	void NotificationManager::removeObserverFunctor(memUInt object)
	{
		NotificationObserverForFunctorMap::iterator iter;
		NotificationObserverForFunctor *pObserver;

		// If object is 0, throw an exception. Otherwise fetch the NotificationObserverForFunctor instance
		// from the map
		if (object == 0)
		{
			// object must not be NULL
			throw Exception(Exception::E_INVALID_PARAMETERS, "NotificationManager::removeObserverFunctor(): the supplied object argument is invalid (0).");
		}
		else
		{
			Poco::ScopedRWLock lock(rwLockNotificationObserverForFunctorMap, false);

			// Fetch instance from map
			iter = mNotificationObserverForFunctorMap.find(object);
			if (iter == mNotificationObserverForFunctorMap.end())
			{
				// No such entry in the map, throw an exception
				throw Exception(Exception::E_NO_SUCH_ELEMENT, "NotificationManager::removeObserverFunctor(): the supplied object argument is invalid.");
			}
			pObserver = iter->second;
		}

		// Check that pObserver is not NULL
		if (pObserver == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationManager::addObserverFunctor(): pObserver is NULL.");
		}

		// Remove the proxy observer for message type T and this NotificationObserverForFunctor instance
		removeObserver<NotificationObserverForFunctor, T>(pObserver, &NotificationObserverForFunctor::handler<T>);

		// Remove the Functor associated with message type T from the NotificationObserverForFunctor instance
		pObserver->removeFunctor(NamedObject<T>::getStaticClassName());
	}

	// inlines
	inline bool NotificationManager::isObjectQueueMapChanged() const
	{
		Poco::ScopedRWLock lock(rwLockObjectQueueMapChanged, false);

		return objectQueueMapChanged;
	}

	inline void NotificationManager::setObjectQueueMapChanged(bool changed)
	{
		Poco::ScopedRWLock lock(rwLockObjectQueueMapChanged, true);

		objectQueueMapChanged = changed;
	}

} // Myoushu

#endif

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
 * @file MessageQueue.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef MYOUSHU_MESSAGE_QUEUE_H
#define MYOUSHU_MESSAGE_QUEUE_H

#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

#include "NotificationCenter.h"
#include "Platform.h"
#include "Message.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * A queue of Messages. Very similar to Poco::NotificationQueue, except that this queue uses
	 * Poco::AutoPtrs to ease memory management.
	 */
	class MYOUSHU_API MessageQueue : public Poco::RefCountedObject
	{
		public:
			/** An iterator over the message list */
			typedef std::list<Poco::AutoPtr<Message> >::iterator MessagesIterator;

			/** Nullary Consturctor. */
			MessageQueue();

			/** Destructor */
			virtual ~MessageQueue();

			/**
			 * Add a message to the queue. If urgent is true the message is added to the head of
			 * the queue, otherwise it is added to the tail.
			 * @param message The message to add to the queue.
			 * @param urgent Indicates if the message is urgent. Urgent messages are added to the front
			 * 							 of the queue.
			 * @throw Exception::E_NULL_POINTER if message is NULL.
			 */
			void enqueueMessage(Poco::AutoPtr<Message>& message, bool urgent = false) throw (Exception);

			/**
			 * Dispatch all of the messages in the queue using the specified NotificationCenter.
			 * @param center The NotificationCenter to use when dispatching the messages in the queue.
			 * @param maxNumberToDispatch The maximum number of queued messages to dispatch. This can be
			 *							  used to limit the number of messages that will actually be
			 *							  processed from the queue. If this is set to 0 (the default)
			 *							  all messages from the queue will be processed. Messages not dispached
			 *							  stay in the queue and will be the first to be dispatched in
			 *							  subsequent calls.
			 */
			void dispatch(NotificationCenter& center, unsigned int maxNumberToDispatch = 0);

		protected:
			/** Read/write mutex for thread safety on the queuedMessages. */
			mutable Poco::RWLock queuedMessagesRWLock;
			/** Read/write mutex for thread safety on the dispatchQueue. */
			mutable Poco::RWLock dispatchQueueRWLock;
			/** Queue of messages waiting to be dispatched. */
			std::list<Poco::AutoPtr<Message> > queuedMessages;
			/** Queue of messages being dispatched */
			std::list<Poco::AutoPtr<Message> > dispatchQueue;
	};
} // Myoushu

#endif

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
 * @file MessageQueue.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>
#include <algorithm>
#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "MessageQueue.h"
#include "Message.h"
#include "Exception.h"
#include "EngineLog.h"

namespace Myoushu
{
	MessageQueue::MessageQueue()
	{
	}

	MessageQueue::~MessageQueue()
	{
		Poco::ScopedRWLock queuedMessagesLock(queuedMessagesRWLock, true);
		Poco::ScopedRWLock dispatchQueueLock(dispatchQueueRWLock, true);

		queuedMessages.clear();
		dispatchQueue.clear();
	}

	void MessageQueue::enqueueMessage(Poco::AutoPtr<Message>& message, bool urgent) throw (Exception)
	{
		Poco::ScopedRWLock lock(queuedMessagesRWLock, true);

		if (message.get() == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MessageQueue::queueMessage(): message is NULL.");
		}

		if (!urgent)
		{
			queuedMessages.push_back(message);
		}
		else
		{
			queuedMessages.push_front(message);
		}
	}

	void MessageQueue::dispatch(NotificationCenter& center, unsigned int maxNumberToDispatch)
	{
		MessagesIterator iter;
		unsigned int dispatchCount;

		Poco::ScopedRWLock lock(dispatchQueueRWLock, true);

		dispatchCount = 0;

		// First copy the messages from the queuedMessages queue to the dispatchQueue
		queuedMessagesRWLock.writeLock();
		iter = queuedMessages.begin();
		while ((iter != queuedMessages.end()) && ((maxNumberToDispatch == 0) || (dispatchCount < maxNumberToDispatch)))
		{
			// Insert message into dispatch queue
			dispatchQueue.push_back(*iter);

			// Remove message from queued messages queue
			iter = queuedMessages.erase(iter);

			dispatchCount++;
		}
		queuedMessages.clear();
		queuedMessagesRWLock.unlock();

		// Dispatch the messages
		for (iter = dispatchQueue.begin(); iter != dispatchQueue.end(); )
		{

			// Call duplicate on the Message instance, since Poco doesn't expect the object to be shared
			(*iter)->duplicate();

			// Send the message
			center.postNotification(*iter);

			// Remove the message from the list
			iter = dispatchQueue.erase(iter);
		}
		dispatchQueue.clear();
	}

} // Myoushu


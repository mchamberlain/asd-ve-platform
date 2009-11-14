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
 * @file TimerTaskMessage.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "TimerTaskMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(TimerTaskMessage, "Myoushu::TimerTaskMessage");

	TimerTaskMessage::TimerTaskMessage() : Message(), type(TM_UNKNOWN), absTime(0), delta(0)
	{
	}

	TimerTaskMessage::TimerTaskMessage(TimerTaskMessageType type, unsigned long delta, unsigned int absTime) : type(type), absTime(absTime), delta(delta)
	{
	}

	TimerTaskMessage::~TimerTaskMessage()
	{
	}

	void TimerTaskMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Set all of the member variables to their zero values
		type = TM_UNKNOWN;
		absTime = 0;
		delta = 0;
	}

	void TimerTaskMessage::clone(TimerTaskMessage *dest) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		// Check that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "TimerTaskMessage::clone(): dest is NULL.");
		}

		dest->setMessageType(type);
		dest->setAbsTime(absTime);
		dest->setDelta(delta);
	}

	TimerTaskMessage* TimerTaskMessage::clone() const
	{
		TimerTaskMessage *newMsg;

		Poco::ScopedRWLock lock(rwLock, false);

		newMsg = ObjectPool<TimerTaskMessage>::getSingletonPtr()->get(true);
		clone(newMsg);

		return newMsg;
	}

	TimerTaskMessage& TimerTaskMessage::operator=(const TimerTaskMessage& rhs)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		Message::operator=(rhs);

		rhs.clone(this);

		return *this;
	}

} // Myoushu

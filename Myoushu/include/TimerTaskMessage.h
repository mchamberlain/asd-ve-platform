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
 * @file TimerTaskMessage.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef TIMER_TASK_MESSAGE_H
#define TIMER_TASK_MESSAGE_H

#include "Poco/Notification.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Cloneable.h"

namespace Myoushu
{
	/**
	 * This class encapsulates message sent by TimerTask.
	 */

	class MYOUSHU_API TimerTaskMessage : public NamedObject<TimerTaskMessage>, public Message
	{
		public:
			/** Message about the timer. */
			enum TimerTaskMessageType
			{
				/**
				 * The TimerTask sends update messages to notify the system of the time that has passed
				 * since the last update. Typically this happens at the start of each Kernel execute loop.
				 */
				TM_UPDATE,
				/** Unkown message type */
				TM_UNKNOWN
			};

			/**
			 * Nullary constructor.
			 */
			 TimerTaskMessage();

			/**
			 * Constructor. Creates a TimerTaskMessage.
			 * @param type The message type.
			 * @param delta The time difference since the previous frame in microseconds
			 * @param absTime The absolute time passed since start of the timer task in milliseconds.
			 */
			TimerTaskMessage(TimerTaskMessageType type, unsigned long delta, unsigned int absTime);

			/** Destructor */
			~TimerTaskMessage();

			CLASS_NAME_FUNCTIONS(TimerTaskMessage);

			/**
			 * Gets the message type.
			 * @return The message type.
			 */
			inline TimerTaskMessageType getMessageType() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return type;
			}

			/**
			 * Sets the message type.
			 * @param type The message type.
			 */
			inline void setMessageType(TimerTaskMessageType type)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->type = type;
			}

			/**
			 * Gets the absolute time since the start of the Timer Task in milliseconds.
			 * @return the absolute time since the start of the Timer Task in milliseconds.
			 */
			inline unsigned int getAbsTime() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return absTime;
			}

			/**
			 * Sets the absolute time since the start of the Timer Task in milliseconds.
			 * @param absTime The absolute time since the start of the Timer Task in milliseconds.
			 */
			inline void setAbsTime(unsigned int absTime)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->absTime = absTime;
			}

			/**
			 * Gets the time that passed since the previous frame in microseconds.
			 * @return The time that passed since the previous frame in microseconds.
			 */
			inline unsigned long getDelta() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return delta;
			}

			/**
			 * Sets the time that passed since the previous frame in microseconds.
			 * @param delta The time that passed since the previous frame in microseconds.
			 */
			inline void setDelta(unsigned long delta)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->delta = delta;
			}

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(TimerTaskMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			TimerTaskMessage* clone() const;

			/**
			 * Equality operator.
			 * @param rhs The instance of TimerTaskMessage to test against.
			 * @return true if this instance and rhs represent the same message.
			 */
			inline bool operator==(const TimerTaskMessage& rhs) const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return ((type == rhs.getMessageType()) && (absTime == rhs.getAbsTime()) && (delta == rhs.getDelta()));
			}

			/**
			 * The assignment operator. Makes this message a duplicate of the given message.
			 * @param rhs The message to copy values from to this instance.
			 */
			TimerTaskMessage& operator=(const TimerTaskMessage& rhs);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** The message type */
			TimerTaskMessageType type;
			/** Absolute time passed since start of timer task */
			unsigned int absTime;
			/** Time difference since previous frame */
			unsigned long delta;
	};
} // Myoushu

#endif

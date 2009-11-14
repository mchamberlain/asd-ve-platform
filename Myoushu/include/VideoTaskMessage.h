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
 * @file VideoTaskMessage.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef VIDEO_TASK_MESSAGE_H
#define VIDEO_TASK_MESSAGE_H

#include "Poco/RWLock.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Cloneable.h"

namespace Myoushu
{
	/**
	 * This class encapsulates message sent/received by VideoTaskManager/VideoTask.
	 */
	class MYOUSHU_API VideoTaskMessage : public NamedObject<VideoTaskMessage>, public Message
	{
		public:
			/** Message about the timer. */
			enum VideoTaskMessageType
			{
				/** Unkown message type */
				VM_UNKNOWN = 0,
				/** Message type indicating that frame rate stats should be displayed on screen. */
				VM_SHOW_FPS,
				/** Message type indicating that frame rate stats should not be displayed on screen. */
				VM_HIDE_FPS
			};

			/**
			 * Nullary constructor.
			 */
			 VideoTaskMessage();

			/**
			 * Constructor. Creates a VideoTaskMessage.
			 * @param type The message type.
			 */
			VideoTaskMessage(VideoTaskMessageType type);

			/** Destructor */
			~VideoTaskMessage();

			CLASS_NAME_FUNCTIONS(VideoTaskMessage);

			/**
			 * Gets the message type.
			 * @return The message type.
			 */
			VideoTaskMessageType getMessageType() const;

			/**
			 * Sets the message type.
			 * @param type The message type.
			 */
			void setMessageType(VideoTaskMessageType type);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			VideoTaskMessage* clone() const;

			/**
			 * Equality operator.
			 * @param rhs The instance of VideoTaskMessage to test against.
			 * @return true if this instance and rhs represent the same message.
			 */
			bool operator==(const VideoTaskMessage& rhs) const;

			/**
			 * The assignment operator. Makes this message a duplicate of the given message.
			 * @param rhs The message to copy values from to this instance.
			 */
			VideoTaskMessage& operator=(const VideoTaskMessage& rhs);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** The message type */
			VideoTaskMessageType type;
	};

	// inlines
	inline VideoTaskMessage::VideoTaskMessageType VideoTaskMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return type;
	}

	inline void VideoTaskMessage::setMessageType(VideoTaskMessage::VideoTaskMessageType type)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->type = type;
	}

	inline bool VideoTaskMessage::operator==(const VideoTaskMessage& rhs) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return (type == rhs.getMessageType());
	}

} // Myoushu

#endif

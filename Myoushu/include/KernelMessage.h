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
 * @file KernelMessage.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef KERNEL_MESSAGE_H
#define KERNEL_MESSAGE_H

#include <string>

#include "Poco/Notification.h"
#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Message.h"
#include "Exception.h"
#include "Cloneable.h"
#include "Task.h"

namespace Myoushu
{
	/** This class encapsulates a message that can be sent to the Kernel by any system within the engine.
	 */

	class MYOUSHU_API KernelMessage : public NamedObject<KernelMessage>, public Message
	{
		public:
			/** The varous message types that can be sent to the Kernel. */
			enum KernelMessageType
			{
				/** The Kernel should shut down as soon as possible. */
				KM_SHUTDOWN = 1,
				/** Add a Task to the Kernel. */
				KM_ADD_TASK,
				/** Remove a Task from the Kernel. */
				KM_REMOVE_TASK,
				/** Suspend a Task */
				KM_SUSPEND_TASK,
				/** Initialize all the Tasks in the Kernel's Task list */
				KM_INIT_ALL_TASKS,
				/** Unkown message type */
				KM_UNKNOWN
			};

			/**
			 * Nullary constructor.
			 */
			 KernelMessage();

			/**
			 * Constructor. Creates a KernelMessage.
			 * @param type The message type.
			 */
			KernelMessage(KernelMessageType type, Task *task = NULL, const std::string& taskName = "");

			/** Destructor */
			~KernelMessage();

			CLASS_NAME_FUNCTIONS(KernelMessage);

			/**
			 * Gets the message type.
			 * @return The message type.
			 */
			inline KernelMessageType getMessageType() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return type;
			}

			/**
			 * Sets the message type.
			 * @param type The message type.
			 */
			inline void setMessageType(KernelMessageType type)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->type = type;
			}

			/**
			 * Gets the Task associated with the KernelMessage, if it was specified.
			 * @return The Task instance associated with KernelMessage.
			 */
			inline Task* getTask()
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return task;
			}

			/**
			 * Set the Task associated with the KernelMessage.
			 * @param task The Task instance associated with the KernelMessage.
			 */
			inline void setTask(Task *task)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->task = task;
			}

			/**
			 * Get the name of the Task instance associated with the message.
			 * @return The name of the Task instance associated with the message.
			 */
			inline std::string getTaskName() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return taskName;
			}

			/**
			 * Set the name of the Task instance associated with the KernelMessage.
			 * @param taskName The name of the Task instance assocaited with the message.
			 */
			inline void setTaskName(const std::string& taskName)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->taskName = taskName;
			}

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(KernelMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			KernelMessage* clone() const;

			/**
			 * Assignment operator. Copies the specified message data into this instance.
			 * @param message The Message instance to copy from.
			 */
			KernelMessage& operator=(const KernelMessage& message);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** The message type */
			KernelMessageType type;
			/** A Task */
			Task *task;
			/** Task name */
			std::string taskName;
	};
} // Myoushu

#endif


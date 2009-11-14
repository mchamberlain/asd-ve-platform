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
 * @file ControllerTaskMessage.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef CONTROLLER_TASK_MESSAGE_H
#define CONTROLLER_TASK_MESSAGE_H

#include "Poco/RWLock.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Controller.h"

namespace Myoushu
{
	/**
	 * This Message class encapsulates message sent to the ControllerTask to register or unregister controllers.
	 */
	class MYOUSHU_API ControllerTaskMessage : public Message, public NamedObject<ControllerTaskMessage>
	{
		public:
			/** An enumeration that defines the different message types. */
			enum ControllerTaskMessageType
			{
				/** Add a Controller to the ControllerTask. */
				CTM_ADD,
				/** Remove a Controller from the ControllerTask. */
				CTM_REMOVE,
				/** An unknown message type. */
				CTM_UNKNOWN
			};

			/**
			 * Nullary Constructor.
			 */
			ControllerTaskMessage();

			/**
			 * Constructor.
			 * @param messageType The type of this message.
			 * @param controller The Controller instance this message is about.
			 */
			ControllerTaskMessage(ControllerTaskMessageType messageType, Controller *controller);

			/**
			 * Destructor.
			 */
			virtual ~ControllerTaskMessage();

			CLASS_NAME_FUNCTIONS(ControllerTaskMessage);

			/** Setter for the message type. */
			void setMessageType(ControllerTaskMessageType messageType);

			/** Getter for the message type. */
			ControllerTaskMessageType getMessageType() const;

			/** Setter of the Controller instance that this message is about. */
			void setController(Controller *controller);

			/** Getter for the Controller instance that this message is about. */
			const Controller* getController() const;

			/** Getter for the Controller instance that this message is about. */
			Controller* getController();

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones this message.
			 * @return A cloned instance of this message.
			 */
			ControllerTaskMessage* clone() const;

			/**
			 * Assignment operator. Assigns the values from rhs to this instance.
			 * @param rhs The ControllerTaskMessage instance to assign values from.
			 */
			ControllerTaskMessage& operator=(const ControllerTaskMessage &rhs);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The message type or action. */
			ControllerTaskMessageType messageType;
			/** The Controller this message is about. */
			Controller *controller;
	};

	// inlines
	inline void ControllerTaskMessage::setMessageType(ControllerTaskMessageType messageType)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->messageType = messageType;
	}

	inline ControllerTaskMessage::ControllerTaskMessageType ControllerTaskMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return messageType;
	}

	inline void ControllerTaskMessage::setController(Controller *controller)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->controller = controller;
	}

	inline const Controller* ControllerTaskMessage::getController() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return controller;
	}

	inline Controller* ControllerTaskMessage::getController()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return controller;
	}

} // Myoushu

#endif

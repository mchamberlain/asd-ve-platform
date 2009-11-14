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
 * @file ControllerTaskMessage.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "ControllerTaskMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(ControllerTaskMessage, "Myoushu::ControllerTaskMessage");

	ControllerTaskMessage::ControllerTaskMessage() : messageType(CTM_UNKNOWN), controller(NULL)
	{
	}

	ControllerTaskMessage::ControllerTaskMessage(ControllerTaskMessageType messageType, Controller *controller) : messageType(messageType), controller(controller)
	{
	}

	ControllerTaskMessage::~ControllerTaskMessage()
	{
	}

	void ControllerTaskMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		messageType = CTM_UNKNOWN;
		controller = NULL;
	}

	ControllerTaskMessage* ControllerTaskMessage::clone() const
	{
		ControllerTaskMessage *newMessage;

		Poco::ScopedRWLock lock(rwLock, false);

		// Get an instance from the ObjectPool
		newMessage = ObjectPool<ControllerTaskMessage>::getSingleton().get(true);

		*newMessage = *this;

		return newMessage;
	}

	ControllerTaskMessage& ControllerTaskMessage::operator=(const ControllerTaskMessage &rhs)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		Message::operator=(rhs);

		messageType = rhs.getMessageType();
		controller = const_cast<Controller *>(rhs.getController());

		return *this;
	}

} // Myoushu

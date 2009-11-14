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
 * @file KernelMessage.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "KernelMessage.h"
#include "Exception.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(KernelMessage, "Myoushu::KernelMessage");

	KernelMessage::KernelMessage() : type(KM_UNKNOWN), task(NULL), taskName("")
	{
	}

	KernelMessage::KernelMessage(KernelMessageType type, Task *task, const std::string& taskName) : type(type), task(task), taskName(taskName)
	{
	}

	KernelMessage::~KernelMessage()
	{
	}

	void KernelMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Set all member variables to their zero values
		type = KM_UNKNOWN;
		task = NULL;
		taskName = "";
	}

	void KernelMessage::clone(KernelMessage *dest) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		// Check that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KernelMessage::clone(): dest is NULL.");
		}

		dest->setMessageType(type);
		dest->setTask(task);
		dest->setTaskName(taskName);
	}

	KernelMessage* KernelMessage::clone() const
	{
		KernelMessage *newMsg;

		Poco::ScopedRWLock lock(rwLock, false);

		//newMsg = new KernelMessage();
		newMsg = ObjectPool<KernelMessage>::getSingleton().get(true);
		clone(newMsg);

		return newMsg;
	}

	KernelMessage& KernelMessage::operator=(const KernelMessage& message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		Message::operator=(message);

		message.clone(this);

		return *this;
	}

} // Myoushu

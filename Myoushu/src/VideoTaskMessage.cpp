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
 * @file VideoTaskMessage.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "VideoTaskMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(VideoTaskMessage, "Myoushu::VideoTaskMessage");

	VideoTaskMessage::VideoTaskMessage() : Message(), type(VM_UNKNOWN)
	{
	}

	VideoTaskMessage::VideoTaskMessage(VideoTaskMessageType type) : type(type)
	{
	}

	VideoTaskMessage::~VideoTaskMessage()
	{
	}

	void VideoTaskMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Set all of the member variables to their zero values
		type = VM_UNKNOWN;
	}

	VideoTaskMessage* VideoTaskMessage::clone() const
	{
		VideoTaskMessage *newMsg;

		Poco::ScopedRWLock lock(rwLock, false);

		newMsg = ObjectPool<VideoTaskMessage>::getSingletonPtr()->get(true);
		(*newMsg) = (*this);

		return newMsg;
	}

	VideoTaskMessage& VideoTaskMessage::operator=(const VideoTaskMessage& rhs)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		Message::operator=(rhs);

		type = rhs.getMessageType();

		return *this;
	}

} // Myoushu

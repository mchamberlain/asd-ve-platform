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
 * @file GUIMessage.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "GUIMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(GUIMessage, "Myoushu::GUIMessage");

	GUIMessage::GUIMessage()
	{
	}

	GUIMessage::~GUIMessage()
	{
	}

	void GUIMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Clear all of the member variables
		messageType = GM_UNKNOWN;
		visible = false;
		message = "";
		resourceGroup = "";
		mPosition = Ogre::Vector2::ZERO;
		mSize = Ogre::Vector2::ZERO;
		mRelative = false;
		mWidgetType = "";
		mWidgetName = "";
	}

	GUIMessage* GUIMessage::clone() const
	{
		GUIMessage *newMessage;

		Poco::ScopedRWLock lock(rwLock, false);

		//newMessage = new GUIMessage();
		newMessage = ObjectPool<GUIMessage>::getSingleton().get(true);

		*newMessage = *this;

		return newMessage;
	}

	GUIMessage& GUIMessage::operator=(const GUIMessage &rhs)
	{
		Message::operator=(rhs);

		messageType = rhs.getMessageType();
		visible = rhs.isVisible();
		message = rhs.getMessage();
		resourceGroup = rhs.getResourceGroup();
		mPosition = rhs.getPosition();
		mSize = rhs.getSize();
		mRelative = rhs.getRelative();
		mWidgetType = rhs.getWidgetType();
		mWidgetName = rhs.getWidgetName();

		return *this;
	}

} // Myoushu

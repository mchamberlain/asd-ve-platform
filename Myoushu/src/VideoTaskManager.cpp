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
 * @file VideoTaskManager.cpp
 * @author ME Chamberlain
 * @date March 2009
 */

#include "VideoTaskManager.h"
#include "VideoTaskMessage.h"
#include "NotificationManager.h"
#include "ObjectPool.h"

namespace Myoushu
{
	VideoTaskManager::VideoTaskManager()
	{
	}

	VideoTaskManager::~VideoTaskManager()
	{
	}

	Ogre::RenderWindow* VideoTaskManager::getRenderWindow(const Ogre::String& name)
	{
		Ogre::RenderTarget *pRenderTarget;

		try
		{
			pRenderTarget = Ogre::Root::getSingleton().getRenderTarget(name);
		}
		catch (Ogre::Exception& e)
		{
			return NULL;
		}

		if (pRenderTarget == NULL)
		{
			return NULL;
		}

		return dynamic_cast<Ogre::RenderWindow*>(pRenderTarget);
	}

	void VideoTaskManager::showFPS(bool show)
	{
		VideoTaskMessage *pMessage;

		pMessage = ObjectPool<VideoTaskMessage>::getSingleton().get(true);
		if (show)
		{
			pMessage->setMessageType(VideoTaskMessage::VM_SHOW_FPS);
		}
		else
		{
			pMessage->setMessageType(VideoTaskMessage::VM_HIDE_FPS);
		}

		NotificationManager::getSingleton().queueNotification(pMessage);
	}

} // namespace

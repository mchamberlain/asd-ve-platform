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
 * @file AnimationManager.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "AnimationManager.h"
#include "AnimationTaskMessage.h"
#include "ObjectPool.h"
#include "NotificationManager.h"

namespace Myoushu
{
	AnimationManager::AnimationManager()
	{
	}

	AnimationManager::~AnimationManager()
	{
	}

	void AnimationManager::playAnimation(Ogre::AnimationState *animation, bool loop, bool restart, bool playCounter, FunctorBase *pStartCallback, FunctorBase *pStopCallback) throw (Exception)
	{
		AnimationTaskMessage *message;

		// Create and populate the message
		message = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		message->setMessageType(AnimationTaskMessage::AM_ENABLE);
		message->setAnimation(animation);
		message->setLoop(loop);
		message->setRestart(restart);
		message->setPlayCounter(playCounter);
		message->setStartCallback(pStartCallback);
		message->setStopCallback(pStopCallback);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void AnimationManager::playAnimationLuaCallback(Ogre::AnimationState *animation, bool loop, bool restart, bool playCounter, const std::string& luaStartCallback, const std::string& luaStopCallback) throw (Exception)
	{
		AnimationLuaCallback *pStart;
		AnimationLuaCallback *pStop;

		pStart = NULL;
		pStop = NULL;
		if (luaStartCallback != "")
		{
			pStart = new AnimationLuaCallback(luaStartCallback, "Ogre::AnimationState*", "bool");
		}
		if (luaStopCallback != "")
		{
			pStop = new AnimationLuaCallback(luaStopCallback, "Ogre::AnimationState*", "bool");
		}

		playAnimation(animation, loop, restart, playCounter, pStart, pStop);
	}

	void AnimationManager::playAnimation(const Ogre::String& name, Scene *scene, bool loop, bool restart, bool playCounter, FunctorBase *pStartCallback, FunctorBase *pStopCallback) throw (Exception)
	{
		AnimationTaskMessage *message;

		// Create and populate the message
		message = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		message->setMessageType(AnimationTaskMessage::AM_ENABLE);
		message->setAnimation(name, scene);
		message->setLoop(loop);
		message->setRestart(restart);
		message->setPlayCounter(playCounter);
		message->setStartCallback(pStartCallback);
		message->setStopCallback(pStopCallback);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void AnimationManager::playAnimationLuaCallback(const Ogre::String& name, Scene *scene, bool loop, bool restart, bool playCounter, const std::string& luaStartCallback, const std::string& luaStopCallback) throw (Exception)
	{
		AnimationLuaCallback *pStart;
		AnimationLuaCallback *pStop;

		pStart = NULL;
		pStop = NULL;
		if (luaStartCallback != "")
		{
			pStart = new AnimationLuaCallback(luaStartCallback, "Ogre::AnimationState*", "bool");
		}
		if (luaStopCallback != "")
		{
			pStop = new AnimationLuaCallback(luaStopCallback, "Ogre::AnimationState*", "bool");
		}

		playAnimation(name, scene, loop, restart, playCounter, pStart, pStop);
	}

	void AnimationManager::stopAnimation(Ogre::AnimationState *animation, bool playCounter) throw (Exception)
	{
		AnimationTaskMessage *message;

		// Create and populate the message
		message = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		message->setMessageType(AnimationTaskMessage::AM_DISABLE);
		message->setAnimation(animation);
		message->setPlayCounter(playCounter);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void AnimationManager::stopAnimation(const Ogre::String& name, Scene *scene, bool playCounter) throw (Exception)
	{
		AnimationTaskMessage *message;

		// Create and populate the message
		message = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		message->setMessageType(AnimationTaskMessage::AM_DISABLE);
		message->setAnimation(name, scene);
		message->setPlayCounter(playCounter);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void AnimationManager::stopAllAnimations()
	{
		AnimationTaskMessage *message;

		// Create and populate the message
		message = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		message->setMessageType(AnimationTaskMessage::AM_DISABLE_ALL);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

} // namespace Myoushu
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
 * @file AnimationTaskMessage.h
 * @author ME Chamberlain
 * @date July 2008
 */

#include "AnimationTaskMessage.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(AnimationTaskMessage, "Myoushu::AnimationTaskMessage");

	AnimationTaskMessage::AnimationTaskMessage() : messageType(AM_ENABLE), animation(NULL), name(""), loop(false), restart(false), playCounter(false), mpStartCallback(NULL), mpStopCallback(NULL)
	{
	}

	AnimationTaskMessage::AnimationTaskMessage(AnimationTaskMessageType messageType, Ogre::AnimationState *animation
		, bool loop, bool restart, bool playCounter) throw (Exception) : messageType(messageType), animation(animation)
		, loop(loop), restart(restart), playCounter(playCounter), mpStartCallback(NULL), mpStopCallback(NULL)
	{
		if (animation == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "AnimationTaskMessage(): animation is null.");
		}
	}

	AnimationTaskMessage::AnimationTaskMessage(AnimationTaskMessageType messageType, Scene *scene, const std::string& name, bool loop
		, bool restart, bool playCounter) throw (Exception) : messageType(messageType), loop(loop), restart(restart), playCounter(playCounter), mpStartCallback(NULL), mpStopCallback(NULL)
	{
		setAnimation(name, scene);
	}

	void AnimationTaskMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		messageType = AM_ENABLE;
		animation = NULL;
		name = "";
		loop = false;
		restart = false;
		playCounter = false;
		mpStartCallback = NULL;
		mpStopCallback = NULL;
	}

	void AnimationTaskMessage::setAnimation(const Ogre::String& name, Scene *scene) throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Check that scene is not NULL
		if (scene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "AnimaitonTaskMessage(): scene is NULL.");
		}

		// Try to get the animation from the scene
		animation = scene->getAnimationState(name);

		// If the animation could not be found, throw an exception
		if (animation == NULL)
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "No animation with the specified name exists in the scene.");
		}
	}

	AnimationTaskMessage* AnimationTaskMessage::clone() const
	{
		AnimationTaskMessage *newInstance;

		// Get/create new instance from pool
		newInstance = ObjectPool<AnimationTaskMessage>::getSingleton().get(true);

		// Set the new instance data equal to this instance
		*newInstance = *this;

		return newInstance;
	}

	bool AnimationTaskMessage::operator==(const AnimationTaskMessage &rhs) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return ((rhs.getMessageType() == messageType) && (rhs.getAnimation() == animation)
			&& (rhs.isLoop() == loop) && (rhs.isRestart() == restart) && (rhs.isPlayCounter() == playCounter)
			&& (rhs.getStartCallback() == mpStartCallback) && (rhs.getStopCallback() == mpStopCallback));
	}

	AnimationTaskMessage& AnimationTaskMessage::operator=(const AnimationTaskMessage &rhs)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		Message::operator=(rhs);

		messageType = rhs.getMessageType();
		animation = rhs.getAnimation();
		loop = rhs.isLoop();
		restart = rhs.isRestart();
		playCounter = rhs.isPlayCounter();
		mpStartCallback = rhs.getStartCallback();
		mpStopCallback = rhs.getStopCallback();

		return *this;
	}

} // namespace Myoushu

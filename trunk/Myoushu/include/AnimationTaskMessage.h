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

#ifndef ANIMATION_TASK_MESSAGE_H
#define ANIMATION_TASK_MESSAGE_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Exception.h"
#include "Scene.h"
#include "FunctorBase.h"

namespace Myoushu
{
	/**
	 * Message class for notifying the AnimationTask about new animations to play, or
	 * animations to stop playing.
	 */
	class MYOUSHU_API AnimationTaskMessage : public Message, public NamedObject<AnimationTaskMessage>
	{
		public:
			/** Various message types */
			enum AnimationTaskMessageType
			{
				/** Enable an animation to play from the next frame. */
				AM_ENABLE,
				/** Disable a playing animation */
				AM_DISABLE,
				/** Disable all playing animations */
				AM_DISABLE_ALL
			};

			/** Nullary Constructor */
			AnimationTaskMessage();

			/**
			 * Constructor. Create an AnimationTaskMessage with the specified paramters.
			 * @param messageType The type of this message, AM_ENABLE or AM_DISABLE.
			 * @param animation Pointer to the Ogre::Animation related to this message.
			 * @param loop If true the animation will be looped. Only used with AM_ENABLE.
			 * @param restart If true the animation will be played from the beginnig, and
			 *				  not from where it stopped previously. Only used with AM_ENABLE.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation.
			 *					  When the playCounter flag is used with the stop action, the play counter determines
			 *					  when to stop playing an animation.
			 * @throws Exception::E_NULL_POINTER if animation is NULL.
			 */
			AnimationTaskMessage(AnimationTaskMessageType messageType, Ogre::AnimationState *animation, bool loop = false, bool restart = false, bool playCounter = false) throw (Exception);

			/**
			 * Constructor. Create an AnimationTaskMessage with the specified parameters.
			 * @param messageType The type of this message, AM_ENABLE or AM_DISABLE.
			 * @param scene The Scene instance containing the animation.
			 * @param name The name of the animation to apply this message to.
			 * @param loop If true the animation will be looped. Only used with AM_ENABLE.
			 * @param restart If true the animation will be played from the beginnig, and
			 *				  not from where it stopped previously. Only used with AM_ENABLE.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation.
			 *					  When the playCounter flag is used with the stop action, the play counter determines
			 *					  when to stop playing an animation.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the specified animation could not be found.
			 */
			AnimationTaskMessage(AnimationTaskMessageType messageType, Scene *scene, const std::string& name, bool loop = false, bool restart = false, bool playCounter = false) throw (Exception);

			CLASS_NAME_FUNCTIONS(AnimationTaskMessage);

			/** Clear this message. */
			void clear();

			/**
			 * Set the type of this message.
			 * @param messageType The type of the message AM_ENABLE, AM_DISABLE.
			 */
			void setMessageType(AnimationTaskMessageType messageType);

			/** 
			 * Get the type of this message.
			 * @return The type of this message.
			 */
			AnimationTaskMessageType getMessageType() const;

			/**
			 * Set the animation to apply the message on.
			 * @param animation Pointer to the animation.
			 */
			void setAnimation(Ogre::AnimationState *animation);

			/**
			 * Set the animation from its name and the scene that contains it.
			 * @param name The name of the animation.
			 * @param scene The Scene instance that contains the animation.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the specified animation could not be found.
			 */
			void setAnimation(const Ogre::String& name, Scene *scene) throw (Exception);

			/**
			 * Get the animation associated with this message.
			 * @return Pointer to the animation to apply this message on.
			 */
			Ogre::AnimationState* getAnimation() const;

			/**
			 * Set whether the animation should loop.
			 * @param loop Flag for whether the animation should loop.
			 */
			void setLoop(bool loop);

			/**
			 * Getter for the loop flag.
			 * @return The value of the loop flag.
			 */
			bool isLoop() const;

			/**
			 * Setter for the restart flag, indicating wheter the animation
			 * should be restarted or played for where it stopped previously.
			 * @param restart restart flag.
			 */
			void setRestart(bool restart);

			/**
			 * Getter for the restart flag.
			 * @return The restart flag.
			 */
			bool isRestart() const;

			/**
			 * Setter for the play counter flag. 
			 * @param playCounter The Flag indicates whether a play counter should be used to control playing
			 *					  and stopping of the animation. This is useful to use when multiple actions use the same animation.
			 *					  Each play operation increases the play counter, stop actions decrease the counter. If the counter
			 *					  is less than or equal to zero the animation stops playing.
			 */
			void setPlayCounter(bool playCounter);

			/**
			 * Getter for the play counter flag.
			 * @return The Flag indicates whether a play counter should be used to control playing
			 *		   and stopping of the animation. This is useful to use when multiple actions use the same animation.
			 *		   Each play operation increases the play counter, stop actions decrease the counter. If the counter
			 * 		   is less than or equal to zero the animation stops playing.
			 */
			bool isPlayCounter() const;

			/**
			 * Create a clone of this message.
			 */
			AnimationTaskMessage* clone() const;

			/** 
			 * Sets the mpStartCallback field. This is the callback that will be called when
			 * the animation starts playing.
			 */
			void setStartCallback(FunctorBase *pFunctor);

			/** 
			 * Sets the mpStopCallback field. This is the callback that will be called when
			 * the animation stops playing.
			 */
			void setStopCallback(FunctorBase *pFunctor);

			/** 
			 * Gets the mpStartCallback field. This is the callback that will be called when
			 * the animation starts playing.
			 */
			FunctorBase* getStartCallback() const;

			/** 
			 * Gets the mpStopCallback field. This is the callback that will be called when
			 * the animation stops playing.
			 */
			FunctorBase* getStopCallback() const;

			/**
			 * Test this instance and the specified instance for equality.
			 * @param rhs The instance to test for equality with this one.
			 */
			bool operator==(const AnimationTaskMessage &rhs) const;

			/**
			 * Sets this instance equal to the specified one.
			 * @param rhs The instance to set this one equal to.
			 * @return this instance
			 */
			AnimationTaskMessage& operator=(const AnimationTaskMessage &rhs);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The type of this message. */
			AnimationTaskMessageType messageType;
			/** Pointer to the animation to apply this message on. */
			Ogre::AnimationState *animation;
			/** The name of the animation to apply this message on. */
			std::string name;
			/** Flag indicating whether the animation should loop. */
			bool loop;
			/** Flag indicating whether the animation should be played from the start. */
			bool restart;
			/** Flag indicating whether a play counter should be used to control playing
			 * and stopping of the animation. This is useful to use when multiple actions use the same animation.
			 * Each play operation increases the play counter, stop actions decrease the counter. If the counter
			 * is less than or equal to zero the animation stops playing.
			 */
			bool playCounter;
			/** Functor to call when the animation starts. If its NULL nothing is called. */
			FunctorBase *mpStartCallback;
			/** Functor to call when the animation stops. If its NULL nothing is called. */
			FunctorBase *mpStopCallback;

	};

	// inlines

	inline void AnimationTaskMessage::setMessageType(AnimationTaskMessage::AnimationTaskMessageType messageType)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->messageType = messageType;
	}

	inline AnimationTaskMessage::AnimationTaskMessageType AnimationTaskMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return messageType;
	}

	inline void AnimationTaskMessage::setAnimation(Ogre::AnimationState *animation)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->animation = animation;
	}

	inline Ogre::AnimationState* AnimationTaskMessage::getAnimation() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return animation;
	}

	inline void AnimationTaskMessage::setLoop(bool loop)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->loop = loop;
	}

	inline bool AnimationTaskMessage::isLoop() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return loop;
	}

	inline void AnimationTaskMessage::setRestart(bool restart)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->restart = restart;
	}

	inline bool AnimationTaskMessage::isRestart() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return restart;
	}

	inline void AnimationTaskMessage::setPlayCounter(bool playCounter)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->playCounter = playCounter;
	}

	inline bool AnimationTaskMessage::isPlayCounter() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return playCounter;
	}

	inline void AnimationTaskMessage::setStartCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpStartCallback = pFunctor;
	}

	inline void AnimationTaskMessage::setStopCallback(FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpStopCallback = pFunctor;
	}

	inline FunctorBase* AnimationTaskMessage::getStartCallback() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return const_cast<FunctorBase*>(mpStartCallback);
	}

	inline FunctorBase* AnimationTaskMessage::getStopCallback() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return const_cast<FunctorBase*>(mpStopCallback);
	}

} // namespace Myoushu

#endif


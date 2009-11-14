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
 * @file AnimationManager.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "Scene.h"
#include "FunctorBase.h"
#include "LuaFunctor.h"

namespace Myoushu
{
	/** 
	 * This class is used to manage animations. Mainly it is used to enable or disable
	 * playing of scene node animations.
	 */
	class MYOUSHU_API AnimationManager : public Ogre::Singleton<AnimationManager>
	{
		public:
			typedef LuaFunctor<void, 2, Ogre::AnimationState*, bool> AnimationLuaCallback;

			/** Nullary Constructor */
			AnimationManager();

			/** Destructor */
			virtual ~AnimationManager();

			/**
			 * Send a message to the AnimationTask to play the specified animation.
			 * @param animation The animation to play.
			 * @param loop Flag indicating whether the animation should be looped.
			 * @param restart Flag indicating whether the animation should be restarted, or
			 *				  from where it was previously.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation.
			 *					  The playCounter flag can be used in the stopAnimation function as well, to determine
			 *					  when to stop playing an animation.
			 * @param pStartCallback A FunctorBase instance (see AnimationCallback and AnimationClassCallback) that wraps a function to call when the animation starts playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @param pStopCallback A FunctorBase instance (see AnimationCallback and AnimationClassCallback) that wraps a function to call when the animation stops playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @throws Exception::E_NULL_POINTER if animation is NULL.
			 */
			void playAnimation(Ogre::AnimationState *animation, bool loop = false, bool restart = false, bool playCounter = false, FunctorBase *pStartCallback = NULL, FunctorBase *pStopCallback = NULL) throw (Exception);

			/**
			 * Send a message to the AnimationTask to play the specified animation.
			 * @param animation The animation to play.
			 * @param loop Flag indicating whether the animation should be looped.
			 * @param restart Flag indicating whether the animation should be restarted, or
			 *				  from where it was previously.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation.
			 *					  The playCounter flag can be used in the stopAnimation function as well, to determine
			 *					  when to stop playing an animation.
			 * @param luaStartCallback The name of a Lua function to call when the animation starts playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @param luaStopCallback The name of a Lua function to call when the animation stops playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @throws Exception::E_NULL_POINTER if animation is NULL.
			 */
			void playAnimationLuaCallback(Ogre::AnimationState *animation, bool loop = false, bool restart = false, bool playCounter = false, const std::string& luaStartCallback = "", const std::string& luaStopCallback = "") throw (Exception);

			/**
			 * Send a message to the AnimationTask to play the specified animation.
			 * @param name The name of the animation to play.
			 * @param scene The Scene containing the animation.
			 * @param loop Flag indicating whether the animation should be looped.
			 * @param restart Flag indicating whether the animation should be restarted, or
			 *				  from where it was previously.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation
			 *					  The playCounter flag can be used in the stopAnimation function as well, to determine
			 *					  when to stop playing an animation.
			 * @param pStartCallback A FunctorBase instance (see AnimationCallback and AnimationClassCallback) that wraps a function to call when the animation starts playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @param pStopCallback A FunctorBase instance (see AnimationCallback and AnimationClassCallback) that wraps a function to call when the animation stops playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the animation could not be found.
			 */
			void playAnimation(const Ogre::String& name, Scene *scene, bool loop = false, bool restart = false, bool playCounter = false, FunctorBase *pStartCallback = NULL, FunctorBase *pStopCallback = NULL) throw (Exception);

			/**
			 * Send a message to the AnimationTask to play the specified animation.
			 * @param name The name of the animation to play.
			 * @param scene The Scene containing the animation.
			 * @param loop Flag indicating whether the animation should be looped.
			 * @param restart Flag indicating whether the animation should be restarted, or
			 *				  from where it was previously.
			 * @param playCounter If true, if the animation is already playing this action
			 *					  will not restart it, it will only increase a play counter on the animation
			 *					  The playCounter flag can be used in the stopAnimation function as well, to determine
			 *					  when to stop playing an animation.
			 * @param luaStartCallback The name of a Lua function to call when the animation starts playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @param luaStopCallback The name of a Lua function to call when the animation stops playing.
			 *						 If NULL no function is called. Defaults to NULL.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the animation could not be found.
			 */
			void playAnimationLuaCallback(const Ogre::String& name, Scene *scene, bool loop = false, bool restart = false, bool playCounter = false, const std::string& luaStartCallback = "", const std::string& luaStopCallback = "") throw (Exception);

			/**
			 * Send a message to the AnimationTask to stop playing the specified animation.
			 * @param animation The animation to stop playing.
			 * @param playCounter If true, if the animation is playing this action
			 *					  will only stop it if its playcount is 0 or less, if the 
			 *					  playCounter flag was true when the animation was played.
			 * @throws Exception::E_NULL_POINTER if animation is NULL.
			 */
			void stopAnimation(Ogre::AnimationState *animation, bool playCounter = false) throw (Exception);

			/**
			 * Send a message to the AnimationTask to stop playing the specified animation.
			 * @param name The name of the animation to play.
			 * @param scene The Scene containing the animation.
			 * @param playCounter If true, if the animation is playing this action
			 *					  will only stop it if its playcount is 0 or less, if the 
			 *					  playCounter flag was true when the animation was played.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the animation could not be found.
			 */
			void stopAnimation(const Ogre::String& name, Scene *scene, bool playCounter = false) throw (Exception);

			/** Send a message to the AnimationTask to stop playing all currently playing animations. */
			void stopAllAnimations();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
	};
} // namespace Myoushu

#endif


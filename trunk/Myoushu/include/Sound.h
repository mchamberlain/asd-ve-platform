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
 * @file Sound.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef SOUND_H
#define SOUND_H

#include <string>

#include "Poco/RefCountedObject.h"

#include "Ogre.h"

#include "Platform.h"
#include "NamedInstance.h"
#include "NamedObject.h"
#include "FunctorBase.h"
#include "LuaFunctor.h"

namespace Myoushu
{
	/** The base class for all sound implementations. */
	class MYOUSHU_API Sound : public NamedInstance, public Poco::RefCountedObject, public NamedObject<Sound>
	{
		public:
			/** A LuaFunctor taking 1 Sound* parameter used for Lua based Finsihed/Loop Sound callbacks. */
			typedef LuaFunctor<void, 1, Sound*> SoundCallbackLuaFunctor;

			/**
			 * Constructor.
			 * @param name The unique name of this Sound instance.
			 */
			Sound(const std::string& name = "Sound");

			/** Destructor. */
			virtual ~Sound();

			CLASS_NAME_FUNCTIONS(Sound);

			/** Play the sound */
			virtual void play() = 0;

			/** Pause the sound */
			virtual void pause() = 0;

			/** Stop the sound */
			virtual void stop() = 0;

			/**
			 * Gets the Ogre::MovableObject instance pointer for this sound. This is to be
			 * used for positioning sounds in the world, by placing sounds in Ogre::SceneNodes.
			 * If the sound implementation does not support/require positional sound, this function
			 * should return null, otherwise it should return an Ogre::MovableObject instance pointer
			 * that can be placed in a SceneNode.
			 */
			virtual Ogre::MovableObject* getMovableObject() = 0;

			/** Set whether the sound should loop */
			virtual void setLoop(bool loop) = 0;

			/** 
			 * Check if the sound is playing.
			 * @return true if the sound is playing.
			 */
			virtual bool isPlaying() = 0;

			/** 
			 * Check if the sound is paused.
			 * @return true if the sound is paused.
			 */
			virtual bool isPaused() = 0;

			/** 
			 * Check if the sound is stopped.
			 * @return true if the sound is stopped.
			 */
			virtual bool isStopped() = 0;

			/** Sets the volume of playback. */
			virtual void setVolume(Ogre::Real volume) = 0;

			/** Gets the volume of the playback. */
			virtual Ogre::Real getVolume() = 0;

			/** Sets the pitch of playback. */
			virtual void setPitch(Ogre::Real pitch) = 0;

			/** Gets the volume of the playback. */
			virtual Ogre::Real getPitch() = 0;

			/** Gets the length of the audio. */
			virtual Ogre::Real getAudioLength() = 0;

			/**
			 * Sets a callback function to be called when this sound finishes its playback.
			 * @param luaFunctionName The Lua function name to execute. The function will receive a pointer
			 *						  to this Sound instance as only parameter.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setFinishedCallback(const std::string luaFunctionName, bool enabled = true) = 0;

			/**
			 * Sets a callback function to be called when this sound finishes its playback.
			 * @param pFunctor Pointer to a functor instance to execute as callback. This
			 *				   instance takes ownership of the functor and will destroy it when appropriate.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setFinishedCallback(FunctorBase* pFunctor, bool enabled = true) = 0;

			/** Enables or disables the finished callback for this Sound instance. */
			virtual void setFinishedCallbackEnabled(bool enabled) = 0;

			/**
			 * Sets a callback function to be called when this sound finsihes one iteration of its playback loop.
			 * @param luaFunctionName The Lua function name to execute. The function will receive a pointer
			 *						  to this Sound instance as only parameter.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setLoopCallback(const std::string luaFunctionName, bool enabled = true) = 0;

			/**
			 * Sets a callback function to be called when this sound finsihes one iteration of its playback loop.
			 * @param pFunctor Pointer to a functor instance to execute as callback. This
			 *				   instance takes ownership of the functor and will destroy it when appropriate.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setLoopCallback(FunctorBase* pFunctor, bool enabled = true) = 0;

			/** Enables or disables the loop callback for this Sound instance. */
			virtual void setLoopCallbackEnabled(bool enabled) = 0;

	}; // class Sound

} // namespace Myoushu

#endif

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
 * @file MyoushuMyoushuOgreOggStaticSound.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_OGRE_OGG_STATIC_SOUND_H
#define MYOUSHU_OGRE_OGG_STATIC_SOUND_H

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "OgreOggStaticSound.h"

#include "StaticSound.h"
#include "Exception.h"
#include "NamedObject.h"

#include "MyoushuOgreOggSoundPlatform.h"

namespace Myoushu
{
	/** 
	 * An implementation of the StaticSound interface using the MyoushuOgreOggStaticSound class from the OgreOggSound
	 * plugin for OGRE.
	 */
	class MYOUSHU_OGRE_OGG_SOUND_API MyoushuOgreOggStaticSound : public StaticSound, public NamedObject<MyoushuOgreOggStaticSound>
	{
		public:
			/**
			 * Constructor.
			 * @param name The unique name of this Sound instance.
			 * @param pOgreOggStreamSound The underlying OgreOggSound::OgreOggStreamSound instance used by this instance. Must not
			 *							  be NULL.
			 * @throws Exception::E_NULL_POINTER if pOgreOggStreamSound is NULL.
			 */
			MyoushuOgreOggStaticSound(const std::string& name, OgreOggSound::OgreOggStaticSound *pOgreOggStaticSound) throw (Exception);

			/** Destructor */
			virtual ~MyoushuOgreOggStaticSound();

			CLASS_NAME_FUNCTIONS(MyoushuOgreOggStaticSound);

			/**
			 * Opens an audio file and starts to read it into memory.
			 * @param pDataStream The stream to read the audio data from.
			 */
			virtual void open(Ogre::DataStreamPtr pDataStream);

			/**
			 * Opens an audio file and starts to read it into memory using
			 * a shared buffer.
			 * @param fileName The audio file path.
			 * @param pBuffer The shared memory buffer.
			 */
			virtual void open(const std::string& fileName, memUInt pBuffer);

			/** Play the sound */
			virtual void play();

			/** Pause the sound */
			virtual void pause();

			/** Stop the sound */
			virtual void stop();

			/**
			 * Gets the Ogre::MovableObject instance pointer for this sound. This is to be
			 * used for positioning sounds in the world, by placing sounds in Ogre::SceneNodes.
			 * If the sound implementation does not support/require positional sound, this function
			 * should return null, otherwise it should return an Ogre::MovableObject instance pointer
			 * that can be placed in a SceneNode.
			 */
			virtual Ogre::MovableObject* getMovableObject();

			/** Set whether the sound should loop */
			virtual void setLoop(bool loop);

			/** 
			 * Check if the sound is playing.
			 * @return true if the sound is playing.
			 */
			virtual bool isPlaying();

			/** 
			 * Check if the sound is paused.
			 * @return true if the sound is paused.
			 */
			virtual bool isPaused();

			/** 
			 * Check if the sound is stopped.
			 * @return true if the sound is stopped.
			 */
			virtual bool isStopped();

			/** Sets the volume of playback. */
			virtual void setVolume(Ogre::Real volume);

			/** Gets the volume of the playback. */
			virtual Ogre::Real getVolume();

			/** Sets the pitch of playback. */
			virtual void setPitch(Ogre::Real pitch);

			/** Gets the volume of the playback. */
			virtual Ogre::Real getPitch();

			/** Gets the length of the audio. */
			virtual Ogre::Real getAudioLength();

			/**
			 * Sets a callback function to be called when this sound finishes its playback.
			 * @param luaFunctionName The Lua function name to execute. The function will receive a pointer
			 *						  to this Sound instance as only parameter.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setFinishedCallback(const std::string luaFunctionName, bool enabled = true);

			/**
			 * Sets a callback function to be called when this sound finishes its playback.
			 * @param pFunctor Pointer to a functor instance to execute as callback. This
			 *				   instance takes ownership of the functor and will destroy it when appropriate.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setFinishedCallback(FunctorBase* pFunctor, bool enabled = true);

			/** Enables or disables the finished callback for this Sound instance. */
			virtual void setFinishedCallbackEnabled(bool enabled);

			/**
			 * Sets a callback function to be called when this sound finsihes one iteration of its playback loop.
			 * @param luaFunctionName The Lua function name to execute. The function will receive a pointer
			 *						  to this Sound instance as only parameter.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setLoopCallback(const std::string luaFunctionName, bool enabled = true);

			/**
			 * Sets a callback function to be called when this sound finsihes one iteration of its playback loop.
			 * @param pFunctor Pointer to a functor instance to execute as callback. This
			 *				   instance takes ownership of the functor and will destroy it when appropriate.
			 * @param enabled A flag indicating whether this callback is enabled.
			 */
			virtual void setLoopCallback(FunctorBase* pFunctor, bool enabled = true);

			/** Enables or disables the loop callback for this Sound instance. */
			virtual void setLoopCallbackEnabled(bool enabled);

		protected:
			/** Read/write mutex for thread safety. */
			Poco::RWLock mRWLock;
			/** The underlying OgreOggSound::OgreStaticSound instance to use. */
			OgreOggSound::OgreOggStaticSound *mpOgreOggStaticSound;
			/** The pitch. OgreOggStreamSound does not provide a getPitch function. */
			Ogre::Real mPitch;
			/** The finsihed callback FunctorBase auto ptr. */
			Poco::AutoPtr<FunctorBase> mpFinishedCallback;
			/** The loop callback FunctorBase auto ptr. */
			Poco::AutoPtr<FunctorBase> mpLoopCallback;

		private:
			/** 
			 * Method use to catch finished callbacks from the OgreOggSound::OgreOggISound instance and then
			 * call our associated finsihed callback.
			 */
			void catchOgreOggSoundFinishedCallback(OgreOggSound::OgreOggISound *sound);

			/** 
			 * Method use to catch loop callbacks from the OgreOggSound::OgreOggISound instance and then
			 * call our associated loop callback.
			 */
			void catchOgreOggSoundLoopCallback(OgreOggSound::OgreOggISound *sound);

	}; // class MyoushuOgreOggStaticSound

} // namespace Myoushu

#endif

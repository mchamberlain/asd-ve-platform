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
 * @file MyoushuOgreOggMyoushuOgreOggSoundManager.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_OGRE_OGG_SOUND_MANAGER_H
#define MYOUSHU_OGRE_OGG_SOUND_MANAGER_H

#include "OgreOggSound.h"

#include "SoundManager.h"
#include "Singleton.h"
#include "Exception.h"

#include "MyoushuOgreOggSoundPlatform.h"

namespace Myoushu
{
	/**
	 * The MyoushuOgreOggSoundManager class. It implements the SoundManager interface to provide sound management
	 * via the OgreOggSound plugin for Ogre.
	 */
	class MYOUSHU_OGRE_OGG_SOUND_API MyoushuOgreOggSoundManager : public SoundManager, public Ogre::Singleton<MyoushuOgreOggSoundManager>
	{
		public:
			/** Constructor */
			MyoushuOgreOggSoundManager();

			/** Destructor */
			virtual ~MyoushuOgreOggSoundManager();

			/**
			 * Sets the master volume of all sound.
			 * @param vol The new master volume.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void setMasterVolume(float vol) throw (Exception);

			/** 
			 * Gets the current master volume.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual float getMasterVolume() throw (Exception);

			/** 
			 * Starts to play a sound. 
			 * @param sName The name of the sound to play.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void playSound(const std::string &sName) throw (Exception);

			/** 
			 * Pauses the playback of a sound. 
			 * @param sName The name of the sound to pause.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void pauseSound(const std::string &sName) throw (Exception);

			/** 
			 * Stops the playback of a sound. 
			 * @param sName The name of the sound to pause.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void stopSound(const std::string &sName) throw (Exception);

			/** 
			 * Stops the playback of all currently playing sounds. 
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void stopAllSounds() throw (Exception);

			/** 
			 * Pauses the playback of all currently playing sounds. 
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void pauseAllSounds() throw (Exception);

			/** 
			 * Resumes the playback of all previously paused sounds. 
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual void resumeAllPausedSounds() throw (Exception);

			/** 
			 * Gets the listener that acts as the ears of the user. This listener is not created by the user, it
			 * is automatically created by the audio subsystem or the MyoushuOgreOggSoundManager. Users can attach this listener
			 * Ogre::SceneNodes.
			 * @return The Ogre::MovableObject instance pointer that acts as the listener (the user's ears) for 
			 *		   audio playback.
			 * @throw Exception::E_NULL_POINTER if the underlying OgreOggSound::OgreOggSoundManager instance
			 *									does not exist.
			 */
			virtual Ogre::MovableObject* getListener() throw (Exception);

		protected:
			/**
			 * Gets the OgreOggSound::OgreOggSoundManager instance. If the instance does not
			 * exist an exception is thrown.
			 * @return The OgreOggSound::OgreOggSoundManager instance.
			 * @throws Exception::E_NULL_POINTER if the OgreOggSound::OgreOggSoundManager instance does not exist.
			 */
			OgreOggSound::OgreOggSoundManager* getOgreOggSoundManager() throw (Exception);

	}; // class MyoushuOgreOggSoundManager
} // namespace Myoushu

#endif

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
 * @file SoundManager.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef MYOUSHU_SOUND_MANAGER_H
#define MYOUSHU_SOUND_MANAGER_H

#include "Platform.h"

namespace Myoushu
{
	/**
	 * The SoundManager interface. An interface that allows one to play, stop and pause sounds as well as set the
	 * the current listener of sounds.
	 */
	class MYOUSHU_API SoundManager 
	{
		public:
			/**
			 * Sets the master volume of all sound.
			 * @param vol The new master volume.
			 */
			virtual void setMasterVolume(float vol) = 0;

			/** Gets the current master volume. */
			virtual float getMasterVolume() = 0;

			/** 
			 * Starts to play a sound. 
			 * @param sName The name of the sound to play.
			 */
			virtual void playSound(const std::string &sName) = 0;

			/** 
			 * Pauses the playback of a sound. 
			 * @param sName The name of the sound to pause.
			 */
			virtual void pauseSound(const std::string &sName) = 0;

			/** 
			 * Stops the playback of a sound. 
			 * @param sName The name of the sound to pause.
			 */
			virtual void stopSound(const std::string &sName) = 0;

			/** Stops the playback of all currently playing sounds. */
			virtual void stopAllSounds() = 0;

			/** Pauses the playback of all currently playing sounds. */
			virtual void pauseAllSounds() = 0;

			/** Resumes the playback of all previously paused sounds. */
			virtual void resumeAllPausedSounds() = 0;

			/** 
			 * Gets the listener that acts as the ears of the user. This listener is not created by the user, it
			 * is automatically created by the audio subsystem or the SoundManager. Users can attach this listener
			 * Ogre::SceneNodes.
			 * @return The Ogre::MovableObject instance pointer that acts as the listener (the user's ears) for 
			 *		   audio playback.
			 */
			virtual Ogre::MovableObject* getListener() = 0;

	}; // class SoundManager
} // namespace Myoushu

#endif

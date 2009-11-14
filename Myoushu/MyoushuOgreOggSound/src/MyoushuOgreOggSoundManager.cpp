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
 * @file MyoushuOgreSoundManager.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "OgreOggSoundManager.h"

#include "MyoushuOgreOggSoundManager.h"

namespace Myoushu
{
	MyoushuOgreOggSoundManager::MyoushuOgreOggSoundManager()
	{
	}

	MyoushuOgreOggSoundManager::~MyoushuOgreOggSoundManager()
	{
	}

	void MyoushuOgreOggSoundManager::setMasterVolume(float vol) throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->setMasterVolume(vol);
	}

	float MyoushuOgreOggSoundManager::getMasterVolume() throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		return pSoundManager->getMasterVolume();
	}

	void MyoushuOgreOggSoundManager::playSound(const std::string &sName) throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->playSound(sName);
	}

	void MyoushuOgreOggSoundManager::pauseSound(const std::string &sName) throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->pauseSound(sName);
	}

	void MyoushuOgreOggSoundManager::stopSound(const std::string &sName) throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->stopSound(sName);
	}

	void MyoushuOgreOggSoundManager::stopAllSounds() throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->stopAllSounds();
	}

	void MyoushuOgreOggSoundManager::pauseAllSounds() throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->pauseAllSounds();
	}

	void MyoushuOgreOggSoundManager::resumeAllPausedSounds() throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		pSoundManager->resumeAllPausedSounds();
	}

	Ogre::MovableObject* MyoushuOgreOggSoundManager::getListener() throw (Exception)
	{
		// Get the OgreOggSoundManager instnace, throws an Exception::E_NULL_POINTER if the
		// OgreOggSoundManager does not exist.
		OgreOggSound::OgreOggSoundManager *pSoundManager = getOgreOggSoundManager();

		return pSoundManager->getListener();
	}

	OgreOggSound::OgreOggSoundManager* MyoushuOgreOggSoundManager::getOgreOggSoundManager() throw (Exception)
	{
		OgreOggSound::OgreOggSoundManager *pSoundManager;

		pSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (pSoundManager == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MyoushuOgreOggSoundManager::getOgreOggSoundManager(): The OgreOggSound::OgreOggSoundManager does not exist!");
		}

		return pSoundManager;
	}

} // namespace Myoushu

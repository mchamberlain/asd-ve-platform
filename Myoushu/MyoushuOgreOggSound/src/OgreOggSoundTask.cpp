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
 * @file OgreOggSoundTask.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "Ogre.h"

#include "Constants.h"
#include "EngineLog.h"
#include "TimerTask.h"

#include "OgreOggSoundTask.h"

namespace Myoushu
{
	CLASS_NAME(OgreOggSoundTask, "OgreOggSoundTask");

	OgreOggSoundTask::OgreOggSoundTask(const std::string& name, int priority, unsigned long executionInterval
		, unsigned int iterationLimit) : ConcurrentTask(name, priority, executionInterval, iterationLimit), mpOgreOggSoundManager(NULL)
	{
	}

	OgreOggSoundTask::~OgreOggSoundTask()
	{
		if (mpOgreOggSoundManager != NULL)
		{
			delete mpOgreOggSoundManager;
			mpOgreOggSoundManager = NULL;
		}
	}

	void OgreOggSoundTask::init() throw (Exception)
	{
		Ogre::StringVector deviceList;

		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initialising OgreOggSound Task...");

		// Create the OgreOggSoundManager instance (if it doesn't exist already, it shouldn't...)
		LOG(EngineLog::LM_INFO_ENGINE, "Creating OgreOggSoundManager instance...");
		mpOgreOggSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (mpOgreOggSoundManager == NULL)
		{
			mpOgreOggSoundManager = new OgreOggSound::OgreOggSoundManager();
		}

		// Initialise the default audio device
		LOG(EngineLog::LM_INFO_ENGINE, "Initialising Audio Devices...");
		// try to init devices. OgreOggSound throws either Ogre exceptions or std::strings as exceptions...
		try
		{
			mpOgreOggSoundManager->init();
		}
		catch (Ogre::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Error initialising OgreOggSoundTask: " << e.what());
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}
		catch (std::string& e)
		{
			LOG(EngineLog::LM_ERROR, "Error initialising OgreOggSoundTask: " << e);
			throw Exception(Exception::E_UNKNOWN_ERROR, e);
		}

		state = TS_INITIALIZED;
	}

	void OgreOggSoundTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void OgreOggSoundTask::execute(unsigned long timeDelta)
	{
		TaskState tState = getState();
		if (tState == TS_SUSPENDED)
		{
			return;
		}
		else if (tState != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		//Poco::ScopedRWLock lock(rwLock, false);
		//mpOgreOggSoundManager->update(static_cast<Ogre::Real>(timeDelta / MICROSECONDS_IN_SECOND));
	}

	void OgreOggSoundTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpOgreOggSoundManager->stopAllSounds();

		state = TS_KILLED;
	}

	void OgreOggSoundTask::run()
	{
		TaskState lState;
		unsigned long timeStamp;

		timeStamp = TimerTask::getSingletonPtr()->getAbsTime();

		try
		{

			// A loop that updates streamed sounds. The loop checks the state of this task in
			// a thread safe manner, and terminates if the the state is TS_KILLED. If the state is TS_SUSPEND
			// the loop skips an iteration.
			for (lState = getState(); lState != TS_KILLED; lState = getState())
			{
				if (lState == TS_SUSPENDED)
				{
					this->yield();

					// Immediately continue to the next iteration if the the task is suspended
					continue;
				}
				else
				{
					//Poco::ScopedRWLock lock(rwLock, false);
					//unsigned long currentTime;
					
					// A little hack here to update the audio in a separate thread. We should look into OgreOggSound's
					// builtin threaded options with Boost.
					//currentTime = TimerTask::getSingletonPtr()->getAbsTime();
					//mpOgreOggSoundManager->update(static_cast<Ogre::Real>((currentTime - timeStamp) / MICROSECONDS_IN_SECOND));
					//timeStamp = currentTime;
					mpOgreOggSoundManager->processQueuedSounds();
					mpOgreOggSoundManager->updateBuffers();

					this->yield();
				}
			}
		}
		catch (Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "OgreOggSoundTask::run(): caught Exception: " << e.getMsg());
		}
		catch (Ogre::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "OgreOggSoundTask::run(): caught Ogre::Exception: " << e.what());
		}
		catch (Poco::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "OgreOggSoundTask::run(): caught Poco::Exception: " << e.displayText());
		}
		catch (std::exception& e)
		{
			LOG(EngineLog::LM_ERROR, "OgreOggSoundTask::run(): caught std::exception: " << e.what());
		}
		catch (...)
		{
			LOG(EngineLog::LM_ERROR, "OgreOggSoundTask::run(): caught unknown exception.");
		}
	}

} // Myoushu


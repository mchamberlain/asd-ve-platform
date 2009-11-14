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
 * @file MyoushuOgreOggSoundPlugin.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "SoundPluginManager.h"
#include "EngineLog.h"
#include "KernelManager.h"
#include "Constants.h"

#include "MyoushuOgreOggSoundPlugin.h"
#include "MyoushuOgreOggSoundFactory.h"
#include "MyoushuOgreOggSoundManager.h"
#include "MyoushuOgreOggStaticSound.h"
#include "MyoushuOgreOggStreamSound.h"
#include "OgreOggSoundTask.h"

namespace Myoushu
{
	void MyoushuOgreOggSoundPlugin::install()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		// Create the MyoushuOgreOggSoundFactory singleton
		LOG(EngineLog::LM_INFO_ENGINE, "[MyoushuOgreOggSound]: Creating MyoushuOgreOggSoundFactory singleton...");
		mpFactory = new MyoushuOgreOggSoundFactory();
	}

	void MyoushuOgreOggSoundPlugin::initialise()
	{
		OgreOggSoundTask *pTask;

		Poco::ScopedRWLock lock(mRWLock, false);

		// Create and add OgreOggSoundTask to kernel
		pTask = new OgreOggSoundTask(Constants::AUDIO_TASK_NAME, Constants::AUDIO_TASK_PRIORITY, Constants::AUDIO_TASK_EXECUTION_INTERVAL, Constants::AUDIO_TASK_ITERATION_LIMIT);
		pTask->init();
		KernelManager::getSingleton().addTask(pTask);
		// Since it is a concurrent task, we have to start it
		pTask->start(*pTask);

		// Register the MyoushuOgreOggSoundFactory singleton with the SoundPluginManager of the engine
		SoundPluginManager::getSingleton().registerSoundFactory(mpFactory, NamedObject<MyoushuOgreOggStaticSound>::getStaticClassName());
		SoundPluginManager::getSingleton().registerSoundFactory(mpFactory, NamedObject<MyoushuOgreOggStreamSound>::getStaticClassName());
	}

	void MyoushuOgreOggSoundPlugin::shutdown()
	{
		// Unregister the MyoushuOgreOggSoundFactory singleton with the SoundPluginManager of the engine
		SoundPluginManager::getSingleton().unregisterSoundFactory(NamedObject<MyoushuOgreOggStaticSound>::getStaticClassName());
		SoundPluginManager::getSingleton().unregisterSoundFactory(NamedObject<MyoushuOgreOggStreamSound>::getStaticClassName());
	}

	void MyoushuOgreOggSoundPlugin::uninstall()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		// Destroy the MyoushuOgreOggSoundFactory singleton
		if (mpFactory != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "[MyoushuOgreOggSound]: Destroying MyoushuOgreOggSoundFactory singleton...");
			delete mpFactory;
			mpFactory = NULL;
		}
	}

} // namespace Myoushu

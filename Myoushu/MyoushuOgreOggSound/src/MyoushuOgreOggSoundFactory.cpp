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
 * @file MyoushuOgreOggSoundFactory.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "OgreOggSoundManager.h"

#include "MyoushuOgreOggSoundFactory.h"
#include "EngineLog.h"

namespace Myoushu
{
	MyoushuOgreOggSoundFactory::MyoushuOgreOggSoundFactory()
	{
	}

	MyoushuOgreOggSoundFactory::~MyoushuOgreOggSoundFactory()
	{
	}

	MyoushuOgreOggStaticSound* MyoushuOgreOggSoundFactory::make(const std::string& name)
	{
		return makeStaticSound(name, "");
	}

	Sound* MyoushuOgreOggSoundFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		if (className == NamedObject<MyoushuOgreOggStaticSound>::getStaticClassName())
		{
			return makeStaticSound(name, "");
		}
		else if (className == NamedObject<MyoushuOgreOggStreamSound>::getStaticClassName())
		{
			return makeStreamSound(name, "");
		}
		else
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "MyoushuOgreOggSoundFactory::make(): class " + className + " unsupported.");
		}
	}

	MyoushuOgreOggStaticSound* MyoushuOgreOggSoundFactory::makeStaticSound(const std::string& name, const std::string& filePath, bool loop, bool preBuffer)
	{
		OgreOggSound::OgreOggSoundManager *pSoundManager;
		OgreOggSound::OgreOggStaticSound *pOgreOggStaticSound;
		MyoushuOgreOggStaticSound *pStaticSound;
		std::string uName;

		// Get the OgreOggSoundManager instance so that we can create sounds
		// TODO: possible concurrency issues here
		pSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (pSoundManager == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggSoundFactory: Cannot create sound instance: OgreOggSoundManager is NULL.");
			return NULL;
		}

		uName = ensureUniqueName(name);
		// Create the underlying OgreOggISound instance
		pOgreOggStaticSound = static_cast<OgreOggSound::OgreOggStaticSound*>(pSoundManager->createSound(uName, filePath, false, loop, preBuffer));

		// Create the MyoushuOgreOggStaticSound instance and add it to this factory
		pStaticSound = new MyoushuOgreOggStaticSound(uName, pOgreOggStaticSound);
		add(pStaticSound);

		return pStaticSound;
	}

	MyoushuOgreOggStreamSound* MyoushuOgreOggSoundFactory::makeStreamSound(const std::string& name, const std::string& filePath, bool loop, bool preBuffer)
	{
		OgreOggSound::OgreOggSoundManager *pSoundManager;
		OgreOggSound::OgreOggStreamSound *pOgreOggStreamSound;
		MyoushuOgreOggStreamSound *pStreamSound;
		std::string uName;

		// Get the OgreOggSoundManager instance so that we can create sounds
		// TODO: possible concurrency issues here
		pSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (pSoundManager == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggSoundFactory: Cannot create sound instance: OgreOggSoundManager is NULL.");
			return NULL;
		}

		uName = ensureUniqueName(name);
		// Create the underlying OgreOggISound instance
		pOgreOggStreamSound = static_cast<OgreOggSound::OgreOggStreamSound*>(pSoundManager->createSound(uName, filePath, true, loop, preBuffer));

		// Create the MyoushuOgreOggStaticSound instance and add it to this factory
		pStreamSound = new MyoushuOgreOggStreamSound(uName, pOgreOggStreamSound);
		add(pStreamSound);

		return pStreamSound;
	}

	void MyoushuOgreOggSoundFactory::destroyInstance(Sound* pInstance) throw (Exception)
	{
		OgreOggSound::OgreOggSoundManager *pSoundManager;
		OgreOggSound::OgreOggISound *pOgreOggSound;
		bool objectInFactory;

		pSoundManager = NULL;
		pOgreOggSound = NULL;

		// If gameObject is NULL, throw an exception
		if (pInstance == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MyoushuOgreOggSoundFactory::destroyInstance():pInstance is NULL.");
		}

		pOgreOggSound = static_cast<OgreOggSound::OgreOggISound*>(pInstance->getMovableObject());

		// Remove the object from the factory, if it is in the factory.
		objectInFactory = remove(pInstance);

		// Get the OgreOggSoundManager instance so that we can create sounds
		// TODO: possible concurrency issues here
		pSoundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
		if (pSoundManager == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggSoundFactory: Cannot create sound instance: OgreOggSoundManager is NULL.");
		}
		else
		{
			// Destroy the underlying OgreOggISound instance
			pSoundManager->destroySound(pOgreOggSound->getName());
		}
	}

	void MyoushuOgreOggSoundFactory::destroyAll()
	{
		Iterator iter;

		iter = begin();
		while (iter != end())
		{
			Sound* pSound = iter->second;

			pSound->stop();
			destroyInstance(pSound);

			iter = begin();
		}

	}


} // namespace Myoushu

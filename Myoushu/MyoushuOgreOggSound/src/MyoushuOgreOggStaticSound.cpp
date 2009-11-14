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
 * @file OgreOggStaticSound.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "MyoushuOgreOggStaticSound.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(MyoushuOgreOggStaticSound, "Myoushu::MyoushuOgreOggStaticSound");

	MyoushuOgreOggStaticSound::MyoushuOgreOggStaticSound(const std::string& name, OgreOggSound::OgreOggStaticSound *pOgreOggStaticSound) throw (Exception)
		: StaticSound(name), mpOgreOggStaticSound(pOgreOggStaticSound), mPitch(0), mpFinishedCallback(NULL), mpLoopCallback(NULL)
	{
		// Check that pOgreOggStaticSound is not NULL
		if (pOgreOggStaticSound == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MyoushuOgreOggStaticSound::MyoushuOgreOggStaticSound(): pOgreOggStaticSound is NULL.");
		}
	}

	MyoushuOgreOggStaticSound::~MyoushuOgreOggStaticSound()
	{
	}

	void MyoushuOgreOggStaticSound::open(Ogre::DataStreamPtr pDataStream)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::open(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->open(pDataStream);
	}

	void MyoushuOgreOggStaticSound::open(const std::string& fileName, memUInt pBuffer)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::open(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->open(fileName, pBuffer);
	}

	void MyoushuOgreOggStaticSound::play()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::play(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->play();
	}

	void MyoushuOgreOggStaticSound::pause()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::pause(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->pause();
	}

	void MyoushuOgreOggStaticSound::stop()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::stop(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->stop();
	}

	Ogre::MovableObject* MyoushuOgreOggStaticSound::getMovableObject()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		return static_cast<Ogre::MovableObject*>(mpOgreOggStaticSound);
	}

	void MyoushuOgreOggStaticSound::setLoop(bool loop)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::loop(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->loop(loop);
	}

	bool MyoushuOgreOggStaticSound::isPlaying()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::isPlaying(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStaticSound->isPlaying();
	}

	bool MyoushuOgreOggStaticSound::isPaused()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::isPaused(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStaticSound->isPaused();
	}

	bool MyoushuOgreOggStaticSound::isStopped()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::isStopped(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStaticSound->isStopped();
	}

	void MyoushuOgreOggStaticSound::setVolume(Ogre::Real volume)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setVolume(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->setVolume(volume);
	}

	Ogre::Real MyoushuOgreOggStaticSound::getVolume()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::getVolume(): mpOgreOggSound is NULL.");

			return 0;
		}

		return mpOgreOggStaticSound->getVolume();
	}

	void MyoushuOgreOggStaticSound::setPitch(Ogre::Real pitch)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, true);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setPitch(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->setPitch(pitch);
		mPitch = pitch;
	}

	Ogre::Real MyoushuOgreOggStaticSound::getPitch()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		return mPitch;
	}

	Ogre::Real MyoushuOgreOggStaticSound::getAudioLength()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::getAudioLength(): mpOgreOggSound is NULL.");

			return 0;
		}

		return mpOgreOggStaticSound->getAudioLength();
	}

	void MyoushuOgreOggStaticSound::setFinishedCallback(const std::string luaFunctionName, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setFinishedCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpFinishedCallback = new SoundCallbackLuaFunctor(luaFunctionName, NamedObject<Sound>::getStaticClassName() + "*");
		mpOgreOggStaticSound->setFinishedCallback(this, &MyoushuOgreOggStaticSound::catchOgreOggSoundFinishedCallback, enabled);
	}

	void MyoushuOgreOggStaticSound::setFinishedCallback(FunctorBase* pFunctor, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setFinishedCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpFinishedCallback = pFunctor;
		mpOgreOggStaticSound->setFinishedCallback(this, &MyoushuOgreOggStaticSound::catchOgreOggSoundFinishedCallback, enabled);
	}

	void MyoushuOgreOggStaticSound::setFinishedCallbackEnabled(bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setFinishedCallbackEnabled(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->setFinishedCallbackEnabled(enabled);
	}

	void MyoushuOgreOggStaticSound::setLoopCallback(const std::string luaFunctionName, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setLoopCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpLoopCallback = new SoundCallbackLuaFunctor(luaFunctionName, NamedObject<Sound>::getStaticClassName() + "*");
		mpOgreOggStaticSound->setLoopCallback(this, &MyoushuOgreOggStaticSound::catchOgreOggSoundLoopCallback, enabled);
	}

	void MyoushuOgreOggStaticSound::setLoopCallback(FunctorBase* pFunctor, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setLoopCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpLoopCallback = pFunctor;
		mpOgreOggStaticSound->setLoopCallback(this, &MyoushuOgreOggStaticSound::catchOgreOggSoundLoopCallback, enabled);
	}

	void MyoushuOgreOggStaticSound::setLoopCallbackEnabled(bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStaticSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStaticSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStaticSound::setLoopCallbackEnabled(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStaticSound->setLoopCallbackEnabled(enabled);
	}

	void MyoushuOgreOggStaticSound::catchOgreOggSoundFinishedCallback(OgreOggSound::OgreOggISound *sound)
	{
		Value v;

		Poco::ScopedRWLock lock(mRWLock, false);

		// If a finished callback has been defined, call it
		if (mpFinishedCallback.get() != NULL)
		{
			if (mpFinishedCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				SoundCallbackLuaFunctor *pFunctor = static_cast<SoundCallbackLuaFunctor*>(mpFinishedCallback.get());

				pFunctor->setParameter1(this);
			}
			else
			{
				v.set(reinterpret_cast<void*>(this));
				mpFinishedCallback->setParameter(0, v);
			}
			(*mpFinishedCallback)();
		}
	}

	void MyoushuOgreOggStaticSound::catchOgreOggSoundLoopCallback(OgreOggSound::OgreOggISound *sound)
	{
		Value v;

		Poco::ScopedRWLock lock(mRWLock, false);

		// If a finished callback has been defined, call it
		if (mpLoopCallback.get() != NULL)
		{
			if (mpLoopCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				SoundCallbackLuaFunctor *pFunctor = static_cast<SoundCallbackLuaFunctor*>(mpLoopCallback.get());

				pFunctor->setParameter1(this);
			}
			else
			{
				v.set(reinterpret_cast<void*>(this));
				mpLoopCallback->setParameter(0, v);
			}
			(*mpLoopCallback)();
		}
	}

} // namespace Myoushu

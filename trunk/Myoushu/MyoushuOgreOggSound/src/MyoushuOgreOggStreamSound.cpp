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
 * @file OgreOggStreamSound.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "MyoushuOgreOggStreamSound.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(MyoushuOgreOggStreamSound, "Myoushu::MyoushuOgreOggStreamSound");

	MyoushuOgreOggStreamSound::MyoushuOgreOggStreamSound(const std::string& name, OgreOggSound::OgreOggStreamSound *pOgreOggStreamSound) throw (Exception)
		: StreamSound(name), mpOgreOggStreamSound(pOgreOggStreamSound), mPitch(0), mpFinishedCallback(NULL), mpLoopCallback(NULL)
	{
		// Check that pOgreOggStreamSound is not NULL
		if (pOgreOggStreamSound == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MyoushuOgreOggStreamSound::MyoushuOgreOggStreamSound(): pOgreOggStreamSound is NULL.");
		}
	}

	MyoushuOgreOggStreamSound::~MyoushuOgreOggStreamSound()
	{
	}

	void MyoushuOgreOggStreamSound::open(Ogre::DataStreamPtr pDataStream)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::open(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->open(pDataStream);
	}

	void MyoushuOgreOggStreamSound::play()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::play(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->play();
	}

	void MyoushuOgreOggStreamSound::pause()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::pause(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->pause();
	}

	void MyoushuOgreOggStreamSound::stop()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::stop(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->stop();
	}

	Ogre::MovableObject* MyoushuOgreOggStreamSound::getMovableObject()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		return static_cast<Ogre::MovableObject*>(mpOgreOggStreamSound);
	}

	void MyoushuOgreOggStreamSound::setLoop(bool loop)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::loop(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->loop(loop);
	}

	bool MyoushuOgreOggStreamSound::isPlaying()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::isPlaying(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStreamSound->isPlaying();
	}

	bool MyoushuOgreOggStreamSound::isPaused()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::isPaused(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStreamSound->isPaused();
	}

	bool MyoushuOgreOggStreamSound::isStopped()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::isStopped(): mpOgreOggSound is NULL.");

			return false;
		}

		return mpOgreOggStreamSound->isStopped();
	}

	void MyoushuOgreOggStreamSound::setVolume(Ogre::Real volume)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setVolume(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->setVolume(volume);
	}

	Ogre::Real MyoushuOgreOggStreamSound::getVolume()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::getVolume(): mpOgreOggSound is NULL.");

			return 0;
		}

		return mpOgreOggStreamSound->getVolume();
	}

	void MyoushuOgreOggStreamSound::setPitch(Ogre::Real pitch)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, true);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setPitch(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->setPitch(pitch);
		mPitch = pitch;
	}

	Ogre::Real MyoushuOgreOggStreamSound::getPitch()
	{
		// Get a read lock
		Poco::ScopedRWLock lock(mRWLock, false);

		return mPitch;
	}

	Ogre::Real MyoushuOgreOggStreamSound::getAudioLength()
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::getAudioLength(): mpOgreOggSound is NULL.");

			return 0;
		}

		return mpOgreOggStreamSound->getAudioLength();
	}

	void MyoushuOgreOggStreamSound::setFinishedCallback(const std::string luaFunctionName, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setFinishedCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpFinishedCallback = new SoundCallbackLuaFunctor(luaFunctionName, NamedObject<Sound>::getStaticClassName() + "*");
		mpOgreOggStreamSound->setFinishedCallback(this, &MyoushuOgreOggStreamSound::catchOgreOggSoundFinishedCallback, enabled);
	}

	void MyoushuOgreOggStreamSound::setFinishedCallback(FunctorBase* pFunctor, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setFinishedCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpFinishedCallback = pFunctor;
		mpOgreOggStreamSound->setFinishedCallback(this, &MyoushuOgreOggStreamSound::catchOgreOggSoundFinishedCallback, enabled);
	}

	void MyoushuOgreOggStreamSound::setFinishedCallbackEnabled(bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setFinishedCallbackEnabled(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->setFinishedCallbackEnabled(enabled);
	}

	void MyoushuOgreOggStreamSound::setLoopCallback(const std::string luaFunctionName, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setLoopCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpLoopCallback = new SoundCallbackLuaFunctor(luaFunctionName, NamedObject<Sound>::getStaticClassName() + "*");
		mpOgreOggStreamSound->setLoopCallback(this, &MyoushuOgreOggStreamSound::catchOgreOggSoundLoopCallback, enabled);
	}

	void MyoushuOgreOggStreamSound::setLoopCallback(FunctorBase* pFunctor, bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setLoopCallback(): mpOgreOggSound is NULL.");

			return;
		}

		mpLoopCallback = pFunctor;
		mpOgreOggStreamSound->setLoopCallback(this, &MyoushuOgreOggStreamSound::catchOgreOggSoundLoopCallback, enabled);
	}

	void MyoushuOgreOggStreamSound::setLoopCallbackEnabled(bool enabled)
	{
		// Get a read lock and called the corresponding function from mpOgreOggStreamSound
		Poco::ScopedRWLock lock(mRWLock, false);

		if (mpOgreOggStreamSound == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyoushuOgreOggStreamSound::setLoopCallbackEnabled(): mpOgreOggSound is NULL.");

			return;
		}

		mpOgreOggStreamSound->setLoopCallbackEnabled(enabled);
	}

	void MyoushuOgreOggStreamSound::catchOgreOggSoundFinishedCallback(OgreOggSound::OgreOggISound *sound)
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

	void MyoushuOgreOggStreamSound::catchOgreOggSoundLoopCallback(OgreOggSound::OgreOggISound *sound)
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

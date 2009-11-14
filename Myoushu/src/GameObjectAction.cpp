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
 * @file GameObjectAction.cpp
 * @author ME Chamberlain
 * @date October 2008
 */

#include "GameObjectAction.h"
#include "GameObject.h"
#include "NetworkManager.h"
#include "GameObjectFactory.h"

namespace Myoushu
{
	CLASS_NAME(GameObjectAction, "Myoushu::GameObjectAction");

	GameObjectAction::GameObjectAction() : NamedInstance(""), mGameObject(NULL), mToggleAction(false), mpStartCallback(NULL), mpStopCallback(NULL)
	{
	}

	GameObjectAction::GameObjectAction(const Ogre::String& name, GameObject *gameObject, bool toggleAction) throw (Exception) 
		: NamedInstance(name), mGameObject(gameObject), mToggleAction(toggleAction), mpStartCallback(NULL), mpStopCallback(NULL)
	{
	}

	GameObjectAction::~GameObjectAction()
	{
	}

	void GameObjectAction::setStartCallback(GameObjectActionCallbackBase *startCallback) throw (Exception)
	{
		// Check that startCallback is not NULL
		if (startCallback == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStartCallback(): startCallback is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStartCallback = startCallback;
	}

	void GameObjectAction::setStartCallback(GameObjectActionCallbackGlobalFunction functionPtr) throw (Exception)
	{
		// Check that startCallback is not NULL
		if (functionPtr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStartCallback(): functionPtr is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStartCallback = new GameObjectActionCallback(getName() + "_start", functionPtr);
	}

	void GameObjectAction::setStartCallback(const Ogre::String& luaFunction)
	{
		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStartCallback = new GameObjectActionCallback(getName() + "_start", luaFunction);
	}

	void GameObjectAction::setStartCallback(GameObjectActionCallbackLuaFunctor *luaFunction) throw (Exception)
	{
		// Check that luaFunction is not NULL
		if (luaFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStartCallback(): luaFunction is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStartCallback = new GameObjectActionCallback(getName() + "_start", luaFunction);
	}

	void GameObjectAction::setStopCallback(GameObjectActionCallbackBase *stopCallback) throw (Exception)
	{
		// Check that stopCallback is not NULL
		if (stopCallback == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStopCallback(): stopCallback is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStopCallback = stopCallback;
	}

	void GameObjectAction::setStopCallback(GameObjectActionCallbackGlobalFunction functionPtr) throw (Exception)
	{
		// Check that stopCallback is not NULL
		if (functionPtr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStopCallback(): functionPtr is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStopCallback = new GameObjectActionCallback(getName() + "_stop", functionPtr);
	}

	void GameObjectAction::setStopCallback(const Ogre::String& luaFunction)
	{
		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStopCallback = new GameObjectActionCallback(getName() + "_stop", luaFunction);
	}

	void GameObjectAction::setStopCallback(GameObjectActionCallbackLuaFunctor *luaFunction) throw (Exception)
	{
		// Check that luaFunction is not NULL
		if (luaFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::setStopCallback(): luaFunction is NULL!");
		}

		// Get a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mpStopCallback = new GameObjectActionCallback(getName() + "_stop", luaFunction);
	}

	void GameObjectAction::startAction()
	{
		// If a start callback has been set, call it
		if (mpStartCallback)
		{
			mpStartCallback->executeCallback(this);
		}
	}

	void GameObjectAction::stopAction()
	{
		// If this is a toggle action exit the function. Toggle actions do not use stop action callbacks.
		if (mToggleAction)
		{
			return;
		}

		// If a stop callback has been set, call it
		if (mpStopCallback)
		{
			mpStopCallback->executeCallback(this);
		}
	}

	memUInt GameObjectAction::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		char* pBuf;
		memUInt writtenSize;
		memUInt totalSize;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::serialize(): pMem is NULL.");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// Serialize the fields of this instance
		// At the moment we ignore the callback function pointers

		// Write the name field
		writtenSize = writeString(getName(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAtion::serialize(): buffer too small.");
		}

		// Write the name of the GameObject that this action belongs too
		if (mGameObject != NULL)
		{
			if (sTarget == ST_NETWORK)
			{
				writtenSize = writeString(mGameObject->getName() + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
			}
			else
			{
				writtenSize = writeString(mGameObject->getName(), pBuf);
			}
		}
		else
		{
			writtenSize = writeString("", pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAction::serialize(): buffer too small.");
		}

		// Write the toggleAction field
		writtenSize = writePrimitiveType(mToggleAction, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAtion::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt GameObjectAction::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		const char *pBuf;
		memUInt readSize;
		memUInt totalSize;
		std::string gameObjectName;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectAction::populateInstance(): pMem is NULL.");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// Read the fields of this instance
		// At the moment we ignore the callback function pointers

		// Read the name field
		readSize = readString(this->instanceName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAtion::populateInstance(): buffer too small.");
		}

		// Read the name of the GameObject that this action belongs too
		readSize = readString(gameObjectName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAction::populateInstance(): buffer too small.");
		}
		mGameObject = dynamic_cast<GameObject*>(GameObjectFactory::getSingleton().findByName(gameObjectName));

		// Read the toggleAction field
		readSize = readPrimitiveType(mToggleAction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObjectAtion::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // namespace Myoushu

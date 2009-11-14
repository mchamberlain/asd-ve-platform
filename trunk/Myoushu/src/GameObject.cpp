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
 * @file GameObject.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "GameObject.h"
#include "EngineLog.h"
#include "NamedObjectInstanceCreatorManager.h"

namespace Myoushu
{
	CLASS_NAME(GameObject, "Myoushu::GameObject");

	GameObject::GameObject(const Ogre::String& name) : NamedInstance(name), mLocalUpVector(0, 1, 0), mLocalForwardVector(0, 0, -1)
	{
	}

	GameObject::GameObject() : NamedInstance("GameObject"), mLocalUpVector(0, 1, 0), mLocalForwardVector(0, 0, -1)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::addAction(GameObjectAction *action) throw (Exception)
	{
		if (action == NULL)
		{
			LOG(EngineLog::LM_ERROR, "GameObject::addAction(): action is NULL.");
			throw Exception(Exception::E_NULL_POINTER, "GameObject::addAction(): action is NULL.");
		}

		// Insert the action into the map, replacing any existing action with the same name
		actionMap[action->getName()] = action;
	}

	GameObjectAction* GameObject::getAction(const Ogre::String& actionName)
	{
		ActionMapIterator iter;

		// Get the action from the map
		iter = actionMap.find(actionName);
		if (iter == actionMap.end())
		{
			// If an action with the specified name could not be found, return NULL
			return NULL;
		}

		// Return the GameObjectAction instance
		return iter->second.get();
	}

	bool GameObject::startAction(const Ogre::String& actionName)
	{
		ActionMapIterator iter;
		GameObjectAction *action;

		// Ignore blank actions
		if (actionName == "") 
		{
			return false;
		}

		iter = actionMap.find(actionName);
		if (iter == actionMap.end())
		{
			LOG(EngineLog::LM_WARNING, "GameObject::startAction(): No such action defined: " << actionName);
			return false;
		}

		// Get the GameObjectAction instance
		action = iter->second.get();
		// Check that it is not NULL, and call the startAction() method
		if (action)
		{
			action->startAction();
		}

		return true;
	}

	bool GameObject::stopAction(const Ogre::String& actionName)
	{
		ActionMapIterator iter;
		GameObjectAction *action;

		action = NULL;
		iter = actionMap.find(actionName);
		if (iter == actionMap.end())
		{
			LOG(EngineLog::LM_WARNING, "GameObject::startAction(): No such action defined: " << actionName);
			return false;
		}

		// Get the GameObjectAction instance
		action = iter->second.get();
		// Check that it is not NULL, and call the stopAction() method
		if (action)
		{
			action->stopAction();
		}

		return true;
	}

	memUInt GameObject::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;
		ActionMapConstIterator iter;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObject::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// First write the number of map entries, then iterate over the map and serialize the key-value pairs.
		writtenSize = writePrimitiveType(actionMap.size(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::serialize(): buffer too small.");
		}

		// Serialize the actionMap
		for (iter = actionMap.begin(); iter != actionMap.end(); ++iter)
		{
			const GameObjectAction *action = iter->second;

			// Write the key as a string
			writtenSize = writeString(iter->first, pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::serialize(): buffer too small.");
			}

			// Serialize the GameObjectAction instance
			// First write the class name of the game object action
			writtenSize = writeString(action->getClassName(), pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;

			writtenSize = action->serialize(pBuf, size - totalSize, sTarget);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::serialize(): buffer too small.");
			}
		}

		// Serialize the key value properties of the GameObject
		writtenSize = mProperties.serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;

		// mLocalUpVector
		writtenSize = writeOgreVector3(mLocalUpVector, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::serialize(): buffer too small.");
		}

		// mLocalForwardVector
		writtenSize = writeOgreVector3(mLocalForwardVector, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt GameObject::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		unsigned int numActionMapEntries;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObject::populateInstance(): buffer is NULL.");
		}

		totalSize = 0;
		readSize = 0;
		numActionMapEntries = 0;
		pBuf = static_cast<const char*>(pMem);

		// First read the number of map entries, then iterate over the map and serialize the key-value pairs.
		readSize = readPrimitiveType(numActionMapEntries, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
		}

		// Clear the actionMap of any exisiting entries
		actionMap.clear();
		for (unsigned int i = 0; i < numActionMapEntries; i++)
		{
			std::string key;
			std::string gameObjectActionClassName;
			GameObjectAction *action;

			// Read the key as a string
			readSize = readString(key, pBuf);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
			}

			// Read the GameObjectAction instance
			// First read the class name of the game object action
			readSize = readString(gameObjectActionClassName, pBuf);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
			}

			// Create a GameObjectAction instance
			action = dynamic_cast<Myoushu::GameObjectAction *>(NamedObjectInstanceCreatorManager::getSingleton().createInstance(gameObjectActionClassName));

			if (action == NULL)
			{
				throw Exception(Exception::E_NULL_POINTER, "GameObject::populateInstance(): Could not create the appropriate GameObjectAction instance: " + gameObjectActionClassName);
			}

			readSize = action->populateInstance(pBuf, size - totalSize, sTarget);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
			}

			// Add the entry to the action map
			actionMap.insert(ActionMapEntry(key, action));
		}

		// Read the key value properties of the GameObject
		readSize = mProperties.populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;

		// mLocalUpVector
		readSize = readOgreVector3(mLocalUpVector, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
		}

		// mLocalForwardVector
		readSize = readOgreVector3(mLocalForwardVector, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameObject::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // Myoushu

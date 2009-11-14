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
 * @file GameActorObject.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "GameActorObject.h"

namespace Myoushu
{
	CLASS_NAME(GameActorObject, "Myoushu::GameActorObject");

	GameActorObject::GameActorObject(const Ogre::String& name, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
		: GameObject(name), Actor(name, scene, collisionShape, initialPose, actorParams)
	{
		// Ensure that scene is not NULL
		if (scene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameActorObject(): scene is NULL.");
		}
	}

	GameActorObject::~GameActorObject()
	{
	}

	Ogre::Vector3 GameActorObject::getGlobalUpVector()
	{
		Ogre::Quaternion orientation = getGlobalOrientation();

		return orientation * getLocalUpVector();
	}

	memUInt GameActorObject::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameActorObject::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// Call the serialize method of the Actor parent instance
		writtenSize = Actor::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameActorObject::serialize(): buffer is too small!");
		}

		// Call the serialize method of the GameObject parent instance
		writtenSize = GameObject::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameActorObject::serialize(): buffer is too small!");
		}

		return totalSize;
	}

	memUInt GameActorObject::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameActorObject::populateInstance(): buffer is NULL.");
		}

		totalSize = 0;
		readSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// Call the serialize method of the Actor parent instance
		readSize = Actor::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameActorObject::populateInstance(): buffer is too small!");
		}

		// Call the serialize method of the GameObject parent instance
		readSize = GameObject::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameActorObject::populateInstance(): buffer is too small!");
		}

		return totalSize;
	}

} // Myoushu

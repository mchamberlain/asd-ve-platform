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
 * @file ActorCharacterActorCharacterCollisionCallback.cpp
 * @author ME Chamberlain
 * @date March 2009
 */

#include "ActorCharacterCollisionCallback.h"

namespace Myoushu
{

	ActorCharacterCollisionCallback::ActorCharacterCollisionCallback(ActorCharacterCollisionCallbackGlobalFunction pFunction)
		: mpFunction(pFunction), mpCharacter(NULL), mpActor(NULL), mCollisionProperties()
	{
	}

	ActorCharacterCollisionCallback::~ActorCharacterCollisionCallback()
	{
	}

	void ActorCharacterCollisionCallback::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Ensure that the index is in [0, 2], if not throw an exception
		if (index > 2)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "ActorCharacterCollisionCallback::setParameter(): index out of bounds");
		}

		// Acquire a write lock on the data members of this instace
		Poco::ScopedRWLock lock(mRWLock, true);

		switch (index)
		{
			case 0:
				if (v.getType() == Value::VT_NAMED_INSTANCE)
				{
					mpCharacter = reinterpret_cast<GameCharacterObject*>(v.getValue().mNamedInstance);
				}
				else if (v.getType() == Value::VT_VOID_PTR)
				{
					mpCharacter = reinterpret_cast<GameCharacterObject*>(v.getValue().mVoidPtr);
				}
				else
				{
					// throw an exception if Value is of an unsupported type
					throw Exception(Exception::E_INVALID_PARAMETERS, "ActorCharacterCollisionCallback::setParameter(): The type of the value in v, for parameter 0, must be either void* or NamedInstance*.");
				}
				break;
			case 1:
				if (v.getType() == Value::VT_NAMED_INSTANCE)
				{
					mpActor = reinterpret_cast<GameActorObject*>(v.getValue().mNamedInstance);
				}
				else if (v.getType() == Value::VT_VOID_PTR)
				{
					mpActor = reinterpret_cast<GameActorObject*>(v.getValue().mVoidPtr);
				}
				else
				{
					// throw an exception if Value is of an unsupported type
					throw Exception(Exception::E_INVALID_PARAMETERS, "ActorCharacterCollisionCallback::setParameter(): The type of the value in v, for parameter 1, must be either void* or NamedInstance*.");
				}
				break;
			case 2:
				if (v.getType() == Value::VT_VOID_PTR)
				{
					CollisionManager::CollisionProperties *pCProps;

					pCProps = NULL;
					pCProps = reinterpret_cast<CollisionManager::CollisionProperties*>(v.getValue().mVoidPtr);
					if (pCProps != NULL)
					{
						mCollisionProperties = (*pCProps);
					}
					else
					{
						mCollisionProperties.mWorldPosition = Ogre::Vector3::ZERO;
						mCollisionProperties.mWorldNormal = Ogre::Vector3::ZERO;
						mCollisionProperties.mDirection = Ogre::Vector3::ZERO;
						mCollisionProperties.mLength = 0;
					}
				}
				else
				{
					// throw an exception if Value is of an unsupported type
					throw Exception(Exception::E_INVALID_PARAMETERS, "ActorCharacterCollisionCallback::setParameter(): The type of the value in v, for parameter 2, must be void*.");
				}
				break;
		}
			
	}

	void ActorCharacterCollisionCallback::setParameters(GameCharacterObject* pCharacter, GameActorObject *pActor, const CollisionManager::CollisionProperties& collisionProperties)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpCharacter = pCharacter;
		mpActor = pActor;
		mCollisionProperties = collisionProperties;
	}

	void ActorCharacterCollisionCallback::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ActorCharacterCollisionCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(*mpFunction)(mpCharacter, mpActor, mCollisionProperties);
	}

} // namespace Myoushu

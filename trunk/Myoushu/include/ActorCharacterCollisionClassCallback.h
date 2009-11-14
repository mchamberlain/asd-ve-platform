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
 * @file ActorCharacterCollisionClassCallback.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef MYOUSHU_ACTOR_CHARACTER_COLLISION_CLASS_CALLBACK_H
#define MYOUSHU_ACTOR_CHARACTER_COLLISION_CLASS_CALLBACK_H

#include "Ogre.h"

#include "FunctorBase.h"
#include "GameCharacterObject.h"
#include "GameActorObject.h"
#include "CollisionManager.h"

namespace Myoushu
{
	/**
	 * A callback class used by the CollisionManager for collisions between GameObjectActors and GameObjectCharacters.
	 */
	template <class C>
	class ActorCharacterCollisionClassCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking a GameCharacterObject pointer, GameActorObject pointer and CollisionProperties as parameters. */
			typedef void (C::*ActorCharacterCollisionClassCallbackFunction)(GameCharacterObject*, GameActorObject*, CollisionManager::CollisionProperties);

			/** Constructor */
			ActorCharacterCollisionClassCallback(C* pClassInstance, ActorCharacterCollisionClassCallbackFunction pFunction);

			/** Destructor */
			virtual ~ActorCharacterCollisionClassCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. For parameter index 2, the CollisionProperties struct, 
			 * use a void *. This function will make an internal copy of the struct.
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** 
			 * Sets the parameters for the callback function call: the the GameCharacterObject and GameActorObject that is involved in a collision
			 * and the CollisionProperties struct that contains some extra information about the collision.
			 */
			void setParameters(GameCharacterObject* pFirstActor, GameActorObject *pSecondActor, const CollisionManager::CollisionProperties& collisionProperties);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual ActorCharacterCollisionClassCallback<C>* clone() const;

			/**
			 * Execute the function wrapped by this functor.
			 */
			virtual void operator()() throw (Exception);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock mRWLock;
			/** Class instance that contains the function to be called */
			C* mpClassInstance;
			/** Pointer to the function to execute */
			ActorCharacterCollisionClassCallbackFunction mpFunction;
			/** The character involved in the collision */
			GameCharacterObject *mpCharacter;
			/** The actor involved in the collision */
			GameActorObject *mpActor;
			/** CollisionProperties struct containing some extra information about the collision. */
			CollisionManager::CollisionProperties mCollisionProperties;
			
	}; // class ActorCharacterCollisionClassCallback

	// template implementation

	template <class C>
	ActorCharacterCollisionClassCallback<C>::ActorCharacterCollisionClassCallback(C* pClassInstance, ActorCharacterCollisionClassCallbackFunction pFunction) : mpClassInstance(pClassInstance), mpFunction(pFunction)
	{
	}

	template <class C>
	ActorCharacterCollisionClassCallback<C>::~ActorCharacterCollisionClassCallback()
	{
	}

	template <class C>
	void ActorCharacterCollisionClassCallback<C>::setParameter(unsigned int index, Value v) throw (Exception)
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

	template <class C>
	void ActorCharacterCollisionClassCallback<C>::setParameters(GameCharacterObject* pCharacter, GameActorObject *pActor, const CollisionManager::CollisionProperties& collisionProperties)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpCharacter = pCharacter;
		mpActor = pActor;
		mCollisionProperties = collisionProperties;
	}

	template <class C>
	inline ActorCharacterCollisionClassCallback<C>* ActorCharacterCollisionClassCallback<C>::clone() const
	{
		ActorCharacterCollisionClassCallback<C>* newInstance;

		Poco::ScopedRWLock lock(mRWLock, false);

		newInstance = new ActorCharacterCollisionClassCallback<C>(mpClassInstance, mpFunction);
		newInstance->setParameters(mpCharacter, mpActor, mCollisionProperties);

		return newInstance;
	}

	template <class C>
	void ActorCharacterCollisionClassCallback<C>::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ActorCharacterCollisionCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(mpClassInstance->*mpFunction)(mpCharacter, mpActor, mCollisionProperties);
	}

} // namespace Myoushu

#endif

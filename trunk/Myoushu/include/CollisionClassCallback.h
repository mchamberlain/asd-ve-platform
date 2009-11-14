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
 * @file CollisionClassCallback.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef MYOUSHU_COLLISION_CLASS_CALLBACK_H
#define MYOUSHU_COLLISION_CLASS_CALLBACK_H

#include "FunctorBase.h"
#include "GameActorObject.h"

namespace Myoushu
{
	/**
	 * A callback used for notification about collisions between objects in the virtual world.
	 */
	template <class C>
	class CollisionClassCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking two GameActorObject pointers as parameters. */
			typedef void (C::*CollisionClassCallbackFunction)(GameActorObject*, GameActorObject*);

			/** Constructor */
			CollisionClassCallback(C* pClassInstance, CollisionClassCallbackFunction pFunction);

			/** Destructor */
			virtual ~CollisionClassCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** Sets the parameters for the callback function call: the two GameActorObjects that is involved in a collision. */
			void setParameters(GameActorObject* pFirstActor, GameActorObject *pSecondActor);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual CollisionClassCallback<C>* clone() const;

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
			CollisionClassCallbackFunction mpFunction;
			/** One of the actors involved in the collision */
			GameActorObject *mpFirstActor;
			/** The other actor involved in the collision */
			GameActorObject *mpSecondActor;
			
	}; // class CollisionClassCallback

	// template implementation

	template <class C>
	CollisionClassCallback<C>::CollisionClassCallback(C* pClassInstance, CollisionClassCallbackFunction pFunction) : mpClassInstance(pClassInstance), mpFunction(pFunction)
	{
	}

	template <class C>
	CollisionClassCallback<C>::~CollisionClassCallback()
	{
	}

	template <class C>
	void CollisionClassCallback<C>::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Check that index is either 0 or 1
		if (index > 1)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "CollisionCallback::setParameter(): index > 1");
		}

		// Check that the type of v is either void* or NamedInstance*
		if ((v.getType() != Value::VT_VOID_PTR) && (v.getType() != Value::VT_NAMED_INSTANCE)) 
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "CollisionCallback::setParameter(): The type of the value in v must be either void* or NamedInstance*.");
		}

		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		// Set the appropriate parameter. If index == 0, set pFirstActor. We cast from either void* or NamedInstance*, depending on the type 
		// stored in Value.
		if (v.getType() == Value::VT_VOID_PTR)
		{
			if (index == 0)
			{
				mpFirstActor = reinterpret_cast<GameActorObject*>(v.getValue().mVoidPtr);
			}
			else
			{
				mpSecondActor = reinterpret_cast<GameActorObject*>(v.getValue().mVoidPtr);
			}
		}
		else
		{
			if (index == 0)
			{
				mpFirstActor = static_cast<GameActorObject*>(v.getValue().mNamedInstance);
			}
			else
			{
				mpSecondActor = static_cast<GameActorObject*>(v.getValue().mNamedInstance);
			}
		}
	}

	template <class C>
	void CollisionClassCallback<C>::setParameters(GameActorObject* pFirstActor, GameActorObject *pSecondActor)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		mpFirstActor = pFirstActor;
		mpSecondActor = pSecondActor;
	}

	template <class C>
	inline CollisionClassCallback<C>* CollisionClassCallback<C>::clone() const
	{
		CollisionClassCallback<C>* newInstance;

		Poco::ScopedRWLock lock(mRWLock, false);

		newInstance = new CollisionClassCallback<C>(mpClassInstance, mpFunction);
		newInstance->setParameters(mpFirstActor, mpSecondActor);

		return newInstance;
	}

	template <class C>
	void CollisionClassCallback<C>::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(mpClassInstance->*mpFunction)(mpFirstActor, mpSecondActor);
	}

} // namespace Myoushu

#endif

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
 * @file AnimationClassCallback.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef MYOUSHU_ANIMATION_CLASS_CALLBACK_H
#define MYOUSHU_ANIMATION_CLASS_CALLBACK_H

#include "Ogre.h"

#include "FunctorBase.h"

namespace Myoushu
{
	/**
	 * A callback class used to call a function when an animation ends or loops.
	 */
	template <class C>
	class AnimationClassCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking two GameActorObject pointers as parameters. */
			typedef void (C::*AnimationClassCallbackFunction)(Ogre::AnimationState*, bool);

			/** Constructor */
			AnimationClassCallback(C* pClassInstance, AnimationClassCallbackFunction pFunction);

			/** Destructor */
			virtual ~AnimationClassCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** Sets the parameters for the callback function call: the two GameActorObjects that is involved in a animation. */
			void setParameters(Ogre::AnimationState *pAState, bool loop);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual AnimationClassCallback<C>* clone() const;

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
			AnimationClassCallbackFunction mpFunction;
			/** The Ogre::AnimationState for the animation. */
			Ogre::AnimationState *mpAState;
			/** The loop flag (inidicates whether the animation will loop. */
			bool mLoop;
			
	}; // class AnimationClassCallback

	// template implementation

	template <class C>
	AnimationClassCallback<C>::AnimationClassCallback(C* pClassInstance, AnimationClassCallbackFunction pFunction) : mpClassInstance(pClassInstance), mpFunction(pFunction), mpAState(NULL), mLoop(false)
	{
	}

	template <class C>
	AnimationClassCallback<C>::~AnimationClassCallback()
	{
	}

	template <class C>
	void AnimationClassCallback<C>::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Chec		// Check that index is either 0 or 1
		if (index > 1)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "AnimationCallback::setParameter(): index > 1");
		}

		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		// Set the appropriate parameter. If index == 0, set mpAState, if index == 1 mLoop. We cast from void* for mpAState.
		if (index == 0)
		{
			// Check that the type of v is void*
			if (v.getType() != Value::VT_VOID_PTR)
			{
				throw Exception(Exception::E_INVALID_PARAMETERS, "AnimationCallback::setParameter(): The type of the value in v must be either void*.");
			}
			mpAState = reinterpret_cast<Ogre::AnimationState*>(v.getValue().mVoidPtr);
		}
		else
		{
			// Check that the type of v is bool or integral
			if ((v.getType() != Value::VT_CHAR) && (v.getType() != Value::VT_INT) 
				&& (v.getType() != Value::VT_LONG) && (v.getType() != Value::VT_SHORT) && (v.getType() != Value::VT_UCHAR) 
				&& (v.getType() != Value::VT_UINT) && (v.getType() != Value::VT_ULONG) && (v.getType() != Value::VT_USHORT))
			{
				throw Exception(Exception::E_INVALID_PARAMETERS, "AnimationCallback::setParameter(): The type of the value in v must be bool or integral.");
			}

			mFlag = static_cast<bool>(v.getValue().mULong);
		}
	}

	template <class C>
	void AnimationClassCallback<C>::setParameters(Ogre::AnimationState *pAState, bool loop)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		mpAState = pAState;
		mLoop = loop;
	}

	template <class C>
	inline AnimationClassCallback<C>* AnimationClassCallback<C>::clone() const
	{
		AnimationClassCallback<C>* newInstance;

		Poco::ScopedRWLock lock(mRWLock, false);

		newInstance = new AnimationClassCallback<C>(mpClassInstance, mpFunction);
		newInstance->setParameters(mpAState, mLoop);

		return newInstance;
	}

	template <class C>
	void AnimationClassCallback<C>::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "AnimationCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(mpClassInstance->*mpFunction)(mpAState, mLoop);
	}

} // namespace Myoushu

#endif

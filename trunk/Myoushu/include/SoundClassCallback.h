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
 * @file SoundClassCallback.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_COLLISION_CLASS_CALLBACK_H
#define MYOUSHU_COLLISION_CLASS_CALLBACK_H

#include "FunctorBase.h"
#include "Sound.h"

namespace Myoushu
{
	/**
	 * A callback class used by Sound instances to call a function when the sound ends or is looped.
	 */
	template <class C>
	class SoundClassCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking a Sound pointer as parameter. */
			typedef void (C::*SoundClassCallbackFunction)(Sound*);

			/** Constructor */
			SoundClassCallback(C* pClassInstance, SoundClassCallbackFunction pFunction);

			/** Destructor */
			virtual ~SoundClassCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** Sets the parameters for the callback function call: the Sound instance involved in the callback. */
			void setParameters(Sound *pSound);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual SoundClassCallback<C>* clone() const;

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
			SoundClassCallbackFunction mpFunction;
			/** The Sound instance involved in the callback. */
			Sound *mpSound;
			
	}; // class SoundClassCallback

	// template implementation

	template <class C>
	SoundClassCallback<C>::SoundClassCallback(C* pClassInstance, SoundClassCallbackFunction pFunction) : mpClassInstance(pClassInstance), mpFunction(pFunction)
	{
	}

	template <class C>
	SoundClassCallback<C>::~SoundClassCallback()
	{
	}

	template <class C>
	void SoundClassCallback<C>::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Check that index is 0
		if (index > 0)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "SoundClassCallback::setParameter(): index > 0");
		}

		// Check that the type of v is either void* or NamedInstance*
		if ((v.getType() != Value::VT_VOID_PTR) && (v.getType() != Value::VT_NAMED_INSTANCE)) 
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "SoundClassCallback::setParameter(): The type of the value in v must be either void* or NamedInstance*.");
		}

		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		// Set the appropriate parameter. If index == 0, set pFirstActor. We cast from either void* or NamedInstance*, depending on the type 
		// stored in Value.
		if (v.getType() == Value::VT_VOID_PTR)
		{
			mpSound = reinterpret_cast<Sound*>(v.getValue().mVoidPtr);
		}
		else
		{
			mpSound = static_cast<Sound*>(v.getValue().mNamedInstance);
		}
	}

	template <class C>
	void SoundClassCallback<C>::setParameters(Sound *pSound)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		mpSound = pSound;
	}

	template <class C>
	inline SoundClassCallback<C>* SoundClassCallback<C>::clone() const
	{
		SoundClassCallback<C>* newInstance;

		Poco::ScopedRWLock lock(mRWLock, false);

		newInstance = new SoundClassCallback<C>(mpClassInstance, mpFunction);
		newInstance->setParameters(mpSound);

		return newInstance;
	}

	template <class C>
	void SoundClassCallback<C>::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SoundClassCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(mpClassInstance->*mpFunction)(mpSound);
	}

} // namespace Myoushu

#endif

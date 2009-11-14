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
 * @file AnimationCallback.cpp
 * @author ME Chamberlain
 * @date March 2009
 */

#include "AnimationCallback.h"

namespace Myoushu
{
	AnimationCallback::AnimationCallback(AnimationCallbackGlobalFunction pFunction) : mpFunction(pFunction), mpAState(NULL), mLoop(false)
	{
	}

	AnimationCallback::~AnimationCallback()
	{
	}

	void AnimationCallback::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Check that index is either 0 or 1
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

			mLoop = static_cast<bool>(v.getValue().mULong);
		}
	}

	void AnimationCallback::setParameters(Ogre::AnimationState *pAState, bool loop)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		mpAState = pAState;
		mLoop = loop;
	}

	void AnimationCallback::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "AnimationCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(*mpFunction)(mpAState, mLoop);
	}

} // namespace Myoushu

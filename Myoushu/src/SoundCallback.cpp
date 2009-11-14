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
 * @file SoundCallback.cpp
 * @author ME Chamberlain
 * @date April 2009
 */

#include "SoundCallback.h"

namespace Myoushu
{
	SoundCallback::SoundCallback(SoundCallbackGlobalFunction pFunction) : mpFunction(pFunction), mpSound(NULL)
	{
	}

	SoundCallback::~SoundCallback()
	{
	}

	void SoundCallback::setParameter(unsigned int index, Value v) throw (Exception)
	{
		// Check that index is 0
		if (index > 0)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "SoundCallback::setParameter(): index > 0");
		}

		// Check that the type of v is either void* or NamedInstance*
		if ((v.getType() != Value::VT_VOID_PTR) && (v.getType() != Value::VT_NAMED_INSTANCE)) 
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "SoundCallback::setParameter(): The type of the value in v must be either void* or NamedInstance*.");
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

	void SoundCallback::setParameters(Sound *pSound)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);
	
		mpSound = pSound;
	}

	void SoundCallback::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SoundCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(*mpFunction)(mpSound);
	}

} // namespace Myoushu

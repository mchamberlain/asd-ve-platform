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
 * @file CollisionCallback.cpp
 * @author ME Chamberlain
 * @date March 2009
 */

#include "CollisionCallback.h"

namespace Myoushu
{
	CollisionCallback::CollisionCallback(CollisionCallbackGlobalFunction pFunction) : mpFunction(pFunction), mpFirstActor(NULL), mpSecondActor(NULL)
	{
	}

	CollisionCallback::~CollisionCallback()
	{
	}

	void CollisionCallback::setParameter(unsigned int index, Value v) throw (Exception)
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

	void CollisionCallback::setParameters(GameActorObject* pFirstActor, GameActorObject *pSecondActor)
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(mRWLock, true);

		mpFirstActor = pFirstActor;
		mpSecondActor = pSecondActor;
	}

	void CollisionCallback::operator()() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that mpFunction is not NULL
		if (mpFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionCallback::operator()(): mpFunction is NULL!");
		}

		// Execute the function
		(*mpFunction)(mpFirstActor, mpSecondActor);
	}

} // namespace Myoushu

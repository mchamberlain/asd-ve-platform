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
 * @file PoolObjectReferenceCounter.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "PoolObjectReferenceCounter.h"
#include "Exception.h"
#include "PoolObject.h"

namespace Myoushu
{
	PoolObjectReferenceCounter::PoolObjectReferenceCounter() : rc(1)
	{
	}

	PoolObjectReferenceCounter::PoolObjectReferenceCounter(const PoolObjectReferenceCounter& object)
	{
		(*this) = object;
	}

	void PoolObjectReferenceCounter::duplicate() const
	{
		Poco::ScopedRWLock lock(rwLock, true);

		rc++;
	}

	void PoolObjectReferenceCounter::release() const
	{
		PoolObject *pObject;
		int tempRC;

		rwLock.writeLock();
		tempRC = --rc;
		rwLock.unlock();

		// If the reference count is zero, free the object
		if (tempRC == 0)
		{
			// Technically this is unsafe, a dynamic_cast is safe but slower.
//			pObject = const_cast<PoolObject*>(reinterpret_cast<const PoolObject*>(this->_refCountedObject));
			//pObject = const_cast<PoolObject*>(STATIC_CAST_PTR(const PoolObject*, const PoolObjectReferenceCounter*, this->_refCountedObject));
			pObject = const_cast<PoolObject*>(dynamic_cast<const PoolObject*>(this->_refCountedObject));
			if (pObject != NULL)
			{
				// Increase the reference count by one when the object is returned to the pool, as it is not actually destroyed,
				// the object must be in the same state as it would be if new is called when it is residing in the object pool
				rwLock.writeLock();
				rc++;
				rwLock.unlock();

				pObject->returnToPool(true);
			}
		}
		
	}

	int PoolObjectReferenceCounter::referenceCount() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return rc;
	}

	PoolObjectReferenceCounter::~PoolObjectReferenceCounter()
	{
	}

	PoolObjectReferenceCounter& PoolObjectReferenceCounter::operator =(const PoolObjectReferenceCounter& object)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		rc = object.referenceCount();

		return *this;
	}

} // Myoushu

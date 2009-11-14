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
 * @file PoolObjectReferenceCounter.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef POOL_OBJECT_REFERENCE_COUNTER_H
#define POOL_OBJECT_REFERENCE_COUNTER_H

#include "Poco/RWLock.h"
#include "Poco/ReferenceCounterBase.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"

namespace Myoushu
{
	/**
	 * A reference counter used for PoolObjects. When a PoolObject is reference counted and its reference count
	 * reaches zero, it should not be destroyed but instead returned to its pool.
	 */
	class MYOUSHU_API PoolObjectReferenceCounter : public Poco::ReferenceCounterBase
	{
		public:
			/**
			 * Constructor.
			 * @param poolObject If True when the reference count reaches zero, the PoolObject::returnToPool()
			 *					 function will be called on this object, instead of just a normal delete operation.
			 */
			PoolObjectReferenceCounter();

			/** Increment the refernce count. */
			void duplicate() const;

			/** Decrement the reference count, and destroy the object if the reference count is 0. */
			void release() const;

			/** Returns the reference count */
			int referenceCount() const;

		protected:
			/** Destructor */
			virtual ~PoolObjectReferenceCounter();

		private:
			/** Read/write mutex */
			mutable Poco::RWLock rwLock;
			/** Reference count */
			mutable int rc;

			/**
			 * Copy constructor.
			 * @param object The instance to copy from.
			 */
			PoolObjectReferenceCounter(const PoolObjectReferenceCounter& object);

			/**
			 * Sets this instance equal to the specified one.
			 * @param object The instance to copy from.
			 */
			PoolObjectReferenceCounter& operator =(const PoolObjectReferenceCounter& object);
	};

} // Myoushu

#endif

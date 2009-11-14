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
 * @file PoolObject.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef POOL_OBJECT_H
#define POOL_OBJECT_H

#include "Poco/RWLock.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"

namespace Myoushu
{
	// Forward declaration of ObjectPoolBase
	class MYOUSHU_API ObjectPoolBase;

	/** 
	 * This abstract class serves as an interface for classes that can be created/managed by an ObjectPool instance.
	 * The ObjectPool stores instances of classes, and instead of reallocating memory on the heap for a new instance
	 * each time one is required, one of the preallocated classes from an ObjectPool can be returned to save time
	 * and reduce memory fragmentation. PoolObject instances must implement the {@code clear()} function to blank
	 * a class before it is fetched from an ObjectPool. Also PoolObject instances must have a nullary (zero parameter)
	 * constructor.
	 *
	 * The new and delete operators have been overloaded allowing the programmer to specify during the new operation if
	 * an ObjectPool should be used, and which ObjectPool should be used. The delete operator will return an instance
	 * to the ObjectPool it came from, or free it if it didn't come from an ObjectPool.
	 */
	class MYOUSHU_API PoolObject : public NamedObject<PoolObject>
	{
		public:
			/** Nullary Constructor */
			PoolObject();

			/** 
			 * Constructor 
			 * @param pool The ObjectPool instance this object belongs to.
			 */
			PoolObject(ObjectPoolBase *pool);

			/** Destructor */
			virtual ~PoolObject();

			CLASS_NAME_FUNCTIONS(PoolObject);

			/** Clears the memeber variables of the instance. */
			virtual void clear() = 0;

			/**
			 * This function tries to add the instance to the appropriate ObjectPool singleton 
			 * if it was fetched from an ObjectPool, if that fails (the pool is 
			 * full for example, or it this instance isn't managed by an ObjectPool) the instance is destroyed
			 * if autoDelete is true.
			 * @param autoDelete If true the instance will be deleted if it cannot be returned to an ObjectPool.
			 *					 Defaults to false.
			 */
			void returnToPool(bool autoDelete = false);

		protected:
			/** 
			 * Declare ObjectPoolBase as a friend class, giving it access to this class'
			 * private member variables.
			 */
			friend class ObjectPoolBase;

			/**
			 * Setter for the pool field. Sets the ObjectPoolBase instance
			 * used to create/manage this PoolObject instance.
			 * @param pool The ObjectPoolBase instance.
			 */
			inline void setObjectPool(ObjectPoolBase *pool)
			{
				Poco::ScopedRWLock lock(rwLockPool, true);

				this->pool = pool;
			}

			/**
			 * Getter for the pool field in the PoolObject class.
			 * @return The ObjectPoolBase instance used to create/manage this PoolObject.
			 */
			inline ObjectPoolBase* getObjectPool()
			{
				Poco::ScopedRWLock lock(rwLockPool, false);

				return pool;
			}

			/**
			 * Getter for the pool field in the PoolObject class. This method does not
			 * acquire a lock before reading pool. This is useful in overloaded delete
			 * operators, where the lock could've been destroyed already.
			 * @return The ObjectPoolBase instance used to create/manager this PoolObject.
			 */
			inline ObjectPoolBase* getObjectPoolNoLock()
			{
				return pool;
			}

		private:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLockPool;
			/** 
			 * ObjectPool to return the object to when it is destroyed, or that 
			 * is containing it at the moment 
			 */
			ObjectPoolBase *pool;

	};
} // Myoushu

#endif

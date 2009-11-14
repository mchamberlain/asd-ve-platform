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
 * @file ObjectPool.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H

#include <map>
#include <vector>

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "ObjectPoolBase.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class stores a pool of allocated, but empty objects. Any class that needs to be stored
	 * in a ObjectPool instance needs to inherit from PoolObject. The new and delete functions
	 * of the class is overridden in PoolObject to first look for an available instance in
	 * a specified ObjectPool and return that instance, instead of allocating a new one. The
	 * delete instance inserts an instance that would have been freed into the ObjectPool instead
	 * of actually freeing it, the instance can then be reused later. This saves memory allocation
	 * and freeing time, as well as helping to limit memory fragmentation.
	 *
	 * A limit on the pool size can be specified.
	 */
	template <typename T>
	class ObjectPool : public ObjectPoolBase, public Ogre::Singleton<ObjectPool<T> >
	{
		public:
			/** std::map::iterator over the map of managed instances. */
			typedef typename std::map<memUInt, T*>::iterator ManagedInstancesIterator;
			/** std::map::const_iterator over the map of managed instances. */
			typedef typename std::map<memUInt, T*>::const_iterator ManagedInstancesConstIterator;

			/** 
			 * Constructor.
			 * @param maxNumberOfObjects Specifies the maximum number of objects that
			 *							 can be in the pool at any given time. If
			 *							 the value is zero, the pool size defaults to 10.
			 */
			ObjectPool(unsigned int maxNumberOfObjects = 10) : maxNumberOfObjects(maxNumberOfObjects), curPoolSize(0)
			{
				if (maxNumberOfObjects = 0)
				{
					this->maxNumberOfObjects = 10;
				}
				pool = new T*[this->maxNumberOfObjects];

				// Register this object pool by the class name of the objects it creates
				ObjectPoolBase::registerObjectPool(NamedObject<T>::getStaticClassName(), this);
			}

			/** Destructor */
			virtual ~ObjectPool()
			{
				ManagedInstancesIterator managedInstancesIter;
				T *object;
				unsigned int i;

				// Unregister this object pool by the class name of the objects it creates
				ObjectPoolBase::unregisterObjectPool(NamedObject<T>::getStaticClassName());

				// Remove the reference to this object pool from any pool objects that are not currently in the pool,
				// in other words the map of managed instances
				for (managedInstancesIter = managedInstances.begin(); managedInstancesIter != managedInstances.end(); ++managedInstancesIter)
				{
					object = managedInstancesIter->second;
					this->clearObjectPoolOnPoolObject(*object);
				}
				managedInstances.clear();

				if (pool != NULL)
				{
					// Loop through the pool and delete any objects in it and remove them from the pool
					for (i = 0; i < curPoolSize; i++)
					{
						object = pool[i];
						delete object;
					}
					delete [] pool;
				}
			}

			/**
			 * Adds an object to the pool.
			 * @param object The object to add to the pool
			 * @param autoDelete If true, object will be automatically deleted if
			 *					 the pool is full, and NULL will be returned. Defaults
			 *					 to false.
			 * @return NULL if the object was successfully added to the pool (or if 
			 *				autoDelete is true and the object was deleted),
			 *				otherwise object is returned indicating that pool is full.
			 * @throws Exception::E_NULL_POINTER if object is NULL.
			 */
			PoolObject* add(PoolObject *object, bool autoDelete = false) throw (Exception)
			{
				T* instance;

				instance = NULL;

				// Check that object is not NULL
				if (object == NULL)
				{
					throw Exception(Exception::E_NULL_POINTER, "ObjectPool::add(): object is NULL.");
				}

				Poco::ScopedRWLock lock(rwLock, true);

				if ((maxNumberOfObjects > 0) && (curPoolSize >= maxNumberOfObjects))
				{
					// Pool is full, cannot add object
					if (!autoDelete)
					{
						// If autoDelete is false, return the object
						return object;
					}
					else
					{
						// Remove the object from the map of managedInstances
						managedInstances.erase(reinterpret_cast<memUInt>(object));

						// If autoDelete is true, delete the object
						delete object;

						return NULL;
					}
				}

				instance = STATIC_CAST_PTR(T*, PoolObject*, object);
				// Set the ObjectPool in the object
				this->setObjectPoolOnPoolObject(*object);
				// Remove the object from the map of managedInstances
				managedInstances.erase(reinterpret_cast<memUInt>(object));
				// Add the object to the back of the pool
				pool[curPoolSize] = instance;
				curPoolSize++;

				return NULL;
			}

			/**
			 * Get an object from the pool.
			 * @param autoCreate If true, if the pool is empty the function
			 *					 automatically creates a new instance of T
			 *					 and returns it (for this to work class T must 
			 *					 have a nullary cosntructor). Defaults to false.
			 * @return NULL if the pool is empty, otherwise an object
			 *		   is removed from the pool, the clear() on it is 
			 *		   called the pool and returned. If autoCreate is true, NULL won't
			 *		   be returned if the pool is empty, a new instance will be created
			 *		   and returned (for this to work class T must have a nullary constructor).
			 */
			T* get(bool autoCreate = false)
			{
				T *object;
				PoolObject *poolObject;

				Poco::ScopedRWLock lock(rwLock, true);

				// Return NULL if the pool is empty.
				if (curPoolSize == 0)
				{
					if (!autoCreate)
					{
						return NULL;
					}

					// If autoCreate is true, create a new instance of class T and return it.
					object = new T();
					poolObject = STATIC_CAST_PTR(PoolObject*, T*, object);
					this->setObjectPoolOnPoolObject(*poolObject);
					// Add the instance to the map of instances managed by this pool
					managedInstances.insert(std::pair<memUInt, T*>(reinterpret_cast<memUInt>(poolObject), object));

					return object;
				}

				// Remove and return the last object in the pool
				object = pool[curPoolSize - 1];
				pool[curPoolSize - 1] = NULL;
				curPoolSize--;
				// Add the instance to the map of instances managed by this pool
				managedInstances.insert(std::pair<memUInt, T*>(reinterpret_cast<memUInt>(object), object));

				// Clear the object
				object->clear();
				this->setObjectPoolOnPoolObject(*STATIC_CAST_PTR(PoolObject*, T*, object));

				return object;
			}

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** Maximum number of objects that can be in the pool at any one time. */
			unsigned int maxNumberOfObjects;
			/** The object pool. */
			T** pool;
			/** Number of items in pool */
			unsigned int curPoolSize;
			/** Map of instances that came from this pool and still hold a reference to be returned to this pool. */
			std::map<memUInt, T*> managedInstances;
	};
} // Myoushu

#endif

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
 * @file ObjectPoolBase.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef OBJECT_POOL_BASE_H
#define OBJECT_POOL_BASE_H

#include <map>

#include "Poco/RWLock.h"

#include "Platform.h"
#include "Exception.h"
#include "PoolObject.h"

namespace Myoushu
{
	/**
	 * This class serves as the base class for the ObjectPool class. It provides pure virtual functions
	 * that are implemented by ObjectPool.
	 */
	class MYOUSHU_API ObjectPoolBase
	{
		public:
			/** Nullary Constructor */
			ObjectPoolBase();

			/** Destructor */
			virtual ~ObjectPoolBase();

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
			virtual PoolObject* add(PoolObject *object, bool autoDelete = false) throw (Exception) = 0;

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
			virtual PoolObject* get(bool autoCreate = false) = 0;

			/**
			 * Sets this instance as the ObjectPool creator/manager of the specified
			 * poolObject.
			 * @param poolObject Reference to the PoolObject.
			 */
			void setObjectPoolOnPoolObject(PoolObject& poolObject);

			/**
			 * Sets ObjectPool creator/manager of the specified poolObject to NULL.
			 * @param poolObject Reference to the PoolObject.
			 */
			void clearObjectPoolOnPoolObject(PoolObject& poolObject);

			/** 
			 * This method registers an object pool. Object pools are mapped to the classnames of the
			 * objects that they create.
			 * @param className The class name of the objects that the object pool creates.
			 * @param objectPool Pointer to the ObjectPoolBase instance that should be registered.
			 */
			static void registerObjectPool(const std::string& className, ObjectPoolBase *objectPool);

			/** 
			 * This method unregisters an object pool. An Object pool that was mapped to the classn ame of the
			 * objects that it creates, will be unmapped.
			 * @param className The class name of the objects that the object pool creates.
			 * @return The ObjectPoolBase instance that was mapped to the specified class name, or NULL if
			 *		   there was no mapping for the specified class name.
			 */
			static ObjectPoolBase* unregisterObjectPool(const std::string& className);

			/**
			 * Gets a registered ObjectPoolBase instance from the class name of the objects it creates.
			 * @param className The class name of the objects that the pool creates.
			 * @return The ObjectPoolBase instance mapped to the specified class name, or NULL if the class
			 *		   name has no ObjectPoolBase mapping.
			 */
			static ObjectPoolBase* getObjectPoolFromClassName(const std::string& className);

		private:
			/** A map of class names to ObjectPoolBase instances that can create instances of those classes. */
			static std::map<std::string, ObjectPoolBase*> msClassNamePoolMap;
			/** A read/write mutex for msClassNamePoolMap */
			static Poco::RWLock msClassNamePoolMapLock;
	};

	// inlines
	inline void ObjectPoolBase::setObjectPoolOnPoolObject(PoolObject& poolObject)
	{
		poolObject.setObjectPool(this);
	}

	inline void ObjectPoolBase::clearObjectPoolOnPoolObject(PoolObject& poolObject)
	{
		poolObject.setObjectPool(NULL);
	}

} // Myoushu

#endif

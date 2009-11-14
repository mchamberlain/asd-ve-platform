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
 * @file ObjectFactory.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <list>
#include <algorithm>

#include "Poco/AutoPtr.h"
#include "Poco/RWLock.h"

#include "Platform.h"

namespace Myoushu
{
	/** An object factory class to be extended by classes which are object factories. All objects are stored with Poco::AutoPtrs, that
	 * means any object stored in the object factory must extend RefCountedObject.
	 */
	template<typename OBJ_TYPE>
	class ObjectFactory 
	{
		public:
			/** std::list::const_iterator type for the std::list used to store objects in this factory. */
			typedef typename std::list<Poco::AutoPtr<OBJ_TYPE> >::const_iterator ConstIterator;
			/** std::list::iterator type for the std::list used to store objects in this factory. */
			typedef typename std::list<Poco::AutoPtr<OBJ_TYPE> >::iterator Iterator;

			/** The constructor */
			ObjectFactory() 
			{
			}

			/** The destructor */
			virtual ~ObjectFactory() 
			{
				Poco::ScopedRWLock lock(rwLock, true);

				objects.clear();
			}

			/** Returns the beginning of the objects list
			 * @return The iterator for the beginning
			 */
			inline ConstIterator begin() const 
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return objects.begin();
			}

			/** Returns the ending of the objects list
			 * @return The iterator for the ending
			 */
			inline ConstIterator end() const 
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return objects.end();
			}

			/** Returns the beginning of the objects list
			 * @return The iterator for the beginning
			 */
			inline Iterator begin()
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return objects.begin();
			}

			/** Returns the ending of the objects list
			 * @return The iterator for the ending
			 */
			inline Iterator end()
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return objects.end();
			}

			/** Adds an object to this factory. The factory takes ownership of the pointer.
			 * @param obj The object to add
			 */
			void add(OBJ_TYPE *obj) 
			{
				Poco::ScopedRWLock lock(rwLock, true);

				// If obj is NULL, don't add it to the list
				if (obj == NULL) {
					return;
				}

				objects.push_back(obj);
			}

			/** Removes an object from the object factory
			 * @param obj The object to remove
			 * @return If the object could be removed
			 */
			bool remove(OBJ_TYPE *obj) 
			{
				Iterator objIt;

				Poco::ScopedRWLock lock(rwLock, true);

				objIt = std::find(objects.begin(), objects.end(), obj);

				if (objIt != objects.end()) 
				{
					objects.erase(objIt);
					return true;
				}

				return false;
			}

			/** Clears the object factory */
			void clear() 
			{
				Poco::ScopedRWLock lock(rwLock, true);

				objects.clear();
			}

			/** 
			 * Acquire a read lock on the list. This function should only be used in conjunction with the begin()
			 * and end() functions.
			 */
			inline void acquireReadLock()
			{
				rwLock.readLock();
			}

			/** Release a previously acquired read lock. */
			inline void releaseLock()
			{
				rwLock.unlock();
			}

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;

		private:
			/** List of objects created by and stored in this factory. */
			std::list<Poco::AutoPtr<OBJ_TYPE> > objects;
	};
} // Myoushu

#endif

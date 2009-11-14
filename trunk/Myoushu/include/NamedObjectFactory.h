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
 * @file NamedObjectFactory.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef NAMED_OBJECTFACTORY_H
#define NAMED_OBJECTFACTORY_H

#include <map>
#include <sstream>

#include "Poco/AutoPtr.h"
#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "NamedObjectFactoryBase.h"

namespace Myoushu
{
	/** An object factory class to be extended by classes which are object factories. All objects are stored with Poco::AutoPtrs, that
	 * means any object stored in the object factory must extend RefCountedObject. Objects created with this factory and factories extending
	 * from it must have unique names and implement a getName() function.
	 */
	template<typename OBJ_TYPE>
	class NamedObjectFactory : public NamedObjectFactoryBase
	{
		public:
			/** std::map::const_iterator type for the std::map used to store objects in this factory. */
			typedef typename std::map<Ogre::String, Poco::AutoPtr<OBJ_TYPE> >::const_iterator ConstIterator;
			/** std::map::iterator type for the std::map used to store objects in this factory. */
			typedef typename std::map<Ogre::String, Poco::AutoPtr<OBJ_TYPE> >::iterator Iterator;

			/** The constructor */
			NamedObjectFactory() 
			{
				// Register this factory with the class name of the objects that it creates instances of
				NamedObjectFactoryBase::registerObjectFactory(NamedObject<OBJ_TYPE>::getStaticClassName(), this);
			}

			/** The destructor */
			virtual ~NamedObjectFactory() 
			{
				Poco::ScopedRWLock lock(rwLock, true);

				objects.clear();

				// Unregister the mapping of the this factory to its class name
				NamedObjectFactory::unregisterObjectFactory(NamedObject<OBJ_TYPE>::getStaticClassName());
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

				objects[obj->getName()] = obj;
			}

			/** Removes an object from the object factory
			 * @param obj The object to remove
			 * @return If the object could be removed
			 */
			bool remove(OBJ_TYPE *obj) 
			{
				Iterator objIt;

				Poco::ScopedRWLock lock(rwLock, true);

				objIt = objects.find(obj->getName());

				if (objIt != objects.end()) 
				{
					objects.erase(objIt);
					return true;
				}

				return false;
			}

			/** Removes an object from the object factory
			 * @param name The instance name (NamedInstance) of the object to remove
			 * @return True if the object could be removed
			 */
			virtual bool removeByName(const Ogre::String& name);

			/**
			 * Find an object in this factory by name.
			 * @param name The name of the object to find.
			 * @return A pointer to the instance with the specified name,
			 *		   or NULL if no such instance could be found in this factory.
			 */
			OBJ_TYPE* find(const Ogre::String& name)
			{
				Iterator objIt;

				Poco::ScopedRWLock lock(rwLock, false);

				objIt = objects.find(name);

				// return NULL if the no object with the specified name could be found
				if (objIt == objects.end())
				{
					return NULL;
				}

				return objIt->second;
			}

			/**
			 * Find an object in this factory by name.
			 * @param name The name of the object to find.
			 * @return A pointer to the instance with the specified name,
			 *		   or NULL if no such instance could be found in this factory.
			 */
			virtual NamedInstance* findByName(const Ogre::String& name);

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

			/**
			 * Ensure that the specified name is unique in this factory. If it is not a number is appended to it to
			 * make it unique. For example if the factory contains an object name 'Rock' and this function is
			 * called with the name 'Rock' it will return 'Rock1'.
			 * @param name The name to ensure uniqueness for.
			 */
			Ogre::String ensureUniqueName(const Ogre::String& name)
			{
				ConstIterator iter;
				std::ostringstream oStr;
				unsigned int number;
				unsigned int smallestNoMatch;
				unsigned int largestMatch;
				bool unique;

				Poco::ScopedRWLock lock(rwLock, false);

				iter = objects.find(name);

				if (iter == objects.end())
				{
					// No object with this name in the factory, we can use it as is
					return name;
				}
				else
				{
					// An object with the specified name already exists, we have to rename
					// the new object to name# where # is some number
					// We use a binary search method to find the a number to use to keep the naming
					// sequential, i.e. "Rock0", "Rock1" etc.
					unique = false;
					number = objects.size();
					smallestNoMatch = number + 1;
					largestMatch = -1;
					while (!unique)
					{
						oStr.str("");
						oStr << name << number;
						// Search for an object with the specified name and the current number concatenated
						iter = objects.find(oStr.str());

						if (iter == objects.end())
						{
							// If no object with such a name is found change the upper bound of our search
							// range to the current number
							smallestNoMatch = number;
						}
						else
						{
							// If a match was found at the current value of number, change
							// the lower bound of our search area to number
							largestMatch = number;
						}
						// Get the middle of the interval between the largest match and smallest mismatch
						number = largestMatch + (smallestNoMatch - largestMatch) / 2;

						// If the difference between the largest match and smallest mismatch is one then
						// we have found the maximum number and we can append number + 1 to the name for the
						// object
						if (smallestNoMatch - largestMatch == 1)
						{
							unique = true;
							number++;
						}
					}
					// Return the new name for the object
					oStr.str("");
					oStr << name << number;

					return oStr.str();
				}
			}

		private:
			/** List of objects created by and stored in this factory. */
			std::map<Ogre::String, Poco::AutoPtr<OBJ_TYPE> > objects;
	};

	// inlines
	template<typename OBJ_TYPE>
	inline bool NamedObjectFactory<OBJ_TYPE>::removeByName(const Ogre::String& name)
	{
		OBJ_TYPE *obj;

		obj = STATIC_CAST_PTR(OBJ_TYPE*, NamedInstance*, findByName(name));

		if (obj == NULL)
		{
			return false;
		}

		return remove(obj);
	}

	template<typename OBJ_TYPE>
	inline NamedInstance* NamedObjectFactory<OBJ_TYPE>::findByName(const Ogre::String& name)
	{
		return find(name);
	}

} // Myoushu

#endif

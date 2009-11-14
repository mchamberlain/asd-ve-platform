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
 * @file NamedObjectFactorybase.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef NAMED_OBJECTFACTORY_BASE_H
#define NAMED_OBJECTFACTORY_BASE_H

#include <string>
#include <map>

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "NamedInstance.h"
#include "Exception.h"

namespace Myoushu
{
	class MYOUSHU_API NamedObjectFactoryBase
	{
		public:
			/** Constructor */
			NamedObjectFactoryBase();

			/** Destructor */
			virtual ~NamedObjectFactoryBase();

			/**
			 * Find an object in this factory by name.
			 * @param name The name of the object to find.
			 * @return A pointer to the instance with the specified name,
			 *		   or NULL if no such instance could be found in this factory.
			 */
			virtual NamedInstance* findByName(const Ogre::String& name) = 0;

			/** Removes an object from the object factory
			 * @param name The instance name (NamedInstance) of the object to remove
			 * @return True if the object could be removed
			 */
			virtual bool removeByName(const Ogre::String& name) = 0;

			/** 
			 * Create an instance using with specified name. Extending classes can change
			 * the return type of this function to an appropriate type.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 */
			virtual NamedInstance* make(const std::string& name) = 0;

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual NamedInstance* make(const std::string& className, const std::string& name) throw (Exception) = 0;

			/** 
			 * This method registers an object factory. Object factories are mapped to the classnames of the
			 * objects that they create.
			 * @param className The class name of the objects that the object factory creates.
			 * @param objectPool Pointer to the ObjectPoolBase instance that should be registered.
			 */
			static void registerObjectFactory(const std::string& className, NamedObjectFactoryBase *pFactory);

			/** 
			 * This method unregisters an object factory. An Object factory that was mapped to the classn ame of the
			 * objects that it creates, will be unmapped.
			 * @param className The class name of the objects that the object factory creates.
			 * @return The ObjectPoolBase instance that was mapped to the specified class name, or NULL if
			 *		   there was no mapping for the specified class name.
			 */
			static NamedObjectFactoryBase* unregisterObjectFactory(const std::string& className);

			/**
			 * Gets a registered NamedObjectFactoryBase instance from the class name of the objects it creates.
			 * @param className The class name of the objects that the factory creates.
			 * @return The NamedObjectFactoryBase instance mapped to the specified class name, or NULL if the class
			 *		   name has no NamedObjectFactoryBase mapping.
			 */
			static NamedObjectFactoryBase* getObjectFactoryFromClassName(const std::string& className);

		private:
			/** A map of class names to object factories that create instances of the classes. */
			static std::map<std::string, NamedObjectFactoryBase*> msClassNameFactoryMap;
			/** A read/write mutex used to control access to msClassNameFactoryMap */
			static Poco::RWLock msClassNameFactoryMapLock;

	};
} // namespace Myoushu

#endif

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
 * @file NamedObjectInstanceCreatorManager.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef NAMED_OBJECT_MANAGER_H
#define NAMED_OBJECT_MANAGER_H

#include <string>
#include <map>

#include "Poco/RWLock.h"

#include "Singleton.h"
#include "NamedObject.h"
#include "Exception.h"
#include "NamedObjectBase.h"

namespace Myoushu
{
	/**
	 * This singleton serves as a class that can create instances of classes that extend NamedObject<T>. Users can supply a string with the class
	 * name and the manager will create such an instance.
	 */
	class MYOUSHU_API NamedObjectInstanceCreatorManager : public Ogre::Singleton<NamedObjectInstanceCreatorManager>
	{
		public:
			/** A type definition of a global function pointer or a static member function pointer. */
			typedef NamedObjectBase* (*tStaticFPtr)();

			/** Constructor. */
			NamedObjectInstanceCreatorManager();

			/** Destructor. */
			virtual ~NamedObjectInstanceCreatorManager();

			/** Overridden version of Ogre::Singleton<T>::getSingleton(). This version instantiates the class if it does not exist. */
			static NamedObjectInstanceCreatorManager& getSingleton();

			/** Creates a new instance of the class with the specified class name.
			 * @param className The class name of the class to create an instance of.
			 * @return The newly created instance or NULL if an instance could not be created.
			 * @throws Exception::E_NO_SUCH_ELEMENT if the specified className does not have an
			 *		   an associated creator function associated with it and could thus not be created.
			 */
			NamedObjectBase* createInstance(const std::string& className) const throw (Exception);

			/**
			 * Map a function pointer to a function that creates an instance with the specified class name.
			 * @param className The class name of the class in question.
			 * @param creatorFPtr Pointer to the creator function for the class of the specified class name.
			 */
			void registerClassCreatorFunction(const std::string& className, tStaticFPtr creatorFPtr) throw (Exception);

			/**
			 * Removing the mapping from the class name of a class to the function that creates instances of it.
			 * @param className The name of the class in question.
			 */
			void unregisterClassCreatorFunction(const std::string& className) throw (Exception);

		private:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** Map of class names to the create function in NamedObject<class> that creates a new instance of such a class using
			 * the nullary constructor of the class.
			 */
			std::map<std::string, tStaticFPtr> mClassNameCreateFunctionMap;
	};
	//inlines

	inline NamedObjectInstanceCreatorManager& NamedObjectInstanceCreatorManager::getSingleton()
	{
		if (Ogre::Singleton<NamedObjectInstanceCreatorManager>::ms_Singleton == NULL)
		{
			new NamedObjectInstanceCreatorManager();
		}

		return Ogre::Singleton<NamedObjectInstanceCreatorManager>::getSingleton();
	}

} // namespace Myoushu

#endif

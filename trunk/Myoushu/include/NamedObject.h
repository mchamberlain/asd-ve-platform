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
 * @file NamedObject.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef NAMED_OBJECT_H
#define NAMED_OBJECT_H

#include <string>

#include "Platform.h"
#include "NamedObjectBase.h"

/**
 * A macro to define the class name of a class.
 * @param class The class name without quotes (for example CLASS_NAME(Test, "Test"))
 * @param name A string containing th class name of the class.
 */
#define CLASS_NAME(class, name) \
	template<> \
	const std::string Myoushu::NamedObject<class >::className = name;

	/**
	 * Defines the getClassName() function that gets the class name.
	 * @param class The class that this function should be generated for. (without quotes).
	 */
#define CLASS_NAME_FUNCTIONS(class) \
	inline virtual std::string getClassName() const \
	{ \
		return Myoushu::NamedObject<class >::getStaticClassName(); \
	} \
	\
	inline virtual class* castPtr(void *p) \
	{ \
		return reinterpret_cast<class*>(p); \
	}

namespace Myoushu
{
	/**
	 * An interface for classes that need to store explicit class names. Classes that are
	 * derived from NamedObject have to put CLASS_NAME(class, name) in their cpp files and CLASS_NAME_FUNCTIONS(class)
	 * in the class definition.
	 */
	template <class C>
	class NamedObject : public NamedObjectBase
	{
		public:
			/**
			 * Nullary Constructor.
			 */
			NamedObject();

			/**
			 * Destructor.
			 */
			virtual ~NamedObject();

			/**
			 * Gets the class name.
			 * @return A const reference to the class name string.
			 */
			static const std::string& getStaticClassName();

			/** Casts a void pointer into a pointer of type T. No safety checks are performed. */
			static C* staticCastPtr(void *p);

		protected:
			/** The class name */
			static const std::string className;
	};

	// implementation
	template<class C>
	NamedObject<C>::NamedObject()
	{
	}

	template<class C>
	NamedObject<C>::~NamedObject()
	{
	}

	template<class C>
	inline const std::string& NamedObject<C>::getStaticClassName()
	{
		return className;
	}

	template<class C>
	inline C* NamedObject<C>::staticCastPtr(void *p)
	{
		return reinterpret_cast<C*>(p);
	}

} // Myoushu

#endif

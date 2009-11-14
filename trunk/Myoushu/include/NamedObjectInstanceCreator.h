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
 * @file NamedObjectInstanceCreator.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef NAMED_OBJECT_INSTANCE_CREATOR_H
#define NAMED_OBJECT_INSTANCE_CREATOR_H

#include <string>

#include "Platform.h"
#include "NamedObject.h"
#include "NamedObjectInstanceCreatorManager.h"

/**
 * A macro that registers the specified class' instance creation method from its class name string.
 * @param class The class type
 */
#define REGISTER_INSTANCE_CREATOR(class) \
	NamedObjectInstanceCreatorManager::getSingleton().registerClassCreatorFunction(NamedObject<class>::getStaticClassName(), reinterpret_cast<NamedObjectBase* (*)()>(&NamedObjectInstanceCreator<class>::createInstance));

namespace Myoushu
{
	/**
	 * A class that allows the creation of instances from class name strings. Class that extend this class cannot be abstract.
	 * C must inherit from NamedObject<C>.
	 */
	template <class C>
	class NamedObjectInstanceCreator : public NamedObject<C>
	{
		public:
			/**
			 * Nullary Constructor.
			 */
			NamedObjectInstanceCreator();

			/**
			 * Destructor.
			 */
			virtual ~NamedObjectInstanceCreator();

			/** Creates an instance of C using the default nullary constructor. */
			static C* createInstance();
	};

	// implementation
	template<class C>
	NamedObjectInstanceCreator<C>::NamedObjectInstanceCreator()
	{
	}

	template<class C>
	NamedObjectInstanceCreator<C>::~NamedObjectInstanceCreator()
	{
	}

	template<class C>
	inline C* NamedObjectInstanceCreator<C>::createInstance()
	{
		return new C();
	}

} // Myoushu

#endif

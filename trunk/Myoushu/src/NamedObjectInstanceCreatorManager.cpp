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
 * @file NamedObjectInstanceCreatorManager.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "NamedObjectInstanceCreatorManager.h"

namespace Myoushu
{
	NamedObjectInstanceCreatorManager::NamedObjectInstanceCreatorManager()
	{
	}

	NamedObjectInstanceCreatorManager::~NamedObjectInstanceCreatorManager()
	{
	}

	NamedObjectBase* NamedObjectInstanceCreatorManager::createInstance(const std::string& className) const throw (Exception)
	{
		std::map<std::string, tStaticFPtr>::const_iterator iter;
		tStaticFPtr fPtr;

		iter = mClassNameCreateFunctionMap.find(className);
		if (iter == mClassNameCreateFunctionMap.end())
		{
			// No creator found for the specified class name, throw an exception
			throw Exception(Exception::E_INVALID_PARAMETERS, "NamedObjectInstanceCreatorManager::createInstance(): the specified class name, " + className + " does not have an associated creator function.");
		}

		// Invoke the creator function
		fPtr = iter->second;
		return (*fPtr)();
	}

	void NamedObjectInstanceCreatorManager::registerClassCreatorFunction(const std::string& className, tStaticFPtr creatorFPtr) throw (Exception)
	{
		// Ignore empty class names
		if (className.length() == 0)
		{
			return;
		}

		// Check that the function pointer is not NULL
		if (creatorFPtr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NamedObjectInstanceCreatorManager::registerClassCreatorFunction(): creatorFPtr is NULL.");
		}

		mClassNameCreateFunctionMap[className] = creatorFPtr;
	}

	void NamedObjectInstanceCreatorManager::unregisterClassCreatorFunction(const std::string& className) throw (Exception)
	{
		std::map<std::string, tStaticFPtr>::iterator iter;

		// Ignore empty class names
		if (className.length() == 0)
		{
			return;
		}

		iter = mClassNameCreateFunctionMap.find(className);
		if (iter == mClassNameCreateFunctionMap.end())
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "NamedObjectInstanceCreatorManager::unregisterClassCreatorFunction(): no function pointer mapping for class " + className);
		}

		mClassNameCreateFunctionMap.erase(iter);
	}

} // namespace Myoushu

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
 * @file ObjectPoolBase.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "ObjectPoolBase.h"

namespace Myoushu
{
	// static member initialization

	std::map<std::string, ObjectPoolBase*> ObjectPoolBase::msClassNamePoolMap;

	Poco::RWLock ObjectPoolBase::msClassNamePoolMapLock;

	// end - static member initialization

	ObjectPoolBase::ObjectPoolBase()
	{
	}

	ObjectPoolBase::~ObjectPoolBase()
	{
	}

	void ObjectPoolBase::registerObjectPool(const std::string& className, ObjectPoolBase *objectPool)
	{
		Poco::ScopedRWLock lock(msClassNamePoolMapLock, true);

		msClassNamePoolMap[className] = objectPool;
	}

	ObjectPoolBase* ObjectPoolBase::unregisterObjectPool(const std::string& className)
	{
		std::map<std::string, ObjectPoolBase*>::iterator iter;
		ObjectPoolBase *pool;

		Poco::ScopedRWLock lock(msClassNamePoolMapLock, true);

		iter = msClassNamePoolMap.find(className);
		if (iter == msClassNamePoolMap.end())
		{
			return NULL;
		}

		pool = iter->second;
		msClassNamePoolMap.erase(iter);

		return pool;
	}

	ObjectPoolBase* ObjectPoolBase::getObjectPoolFromClassName(const std::string& className)
	{
		std::map<std::string, ObjectPoolBase*>::iterator iter;

		Poco::ScopedRWLock lock(msClassNamePoolMapLock, false);

		iter = msClassNamePoolMap.find(className);
		if (iter == msClassNamePoolMap.end())
		{
			return NULL;
		}

		return iter->second;
	}
} // Myoushu

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
 * @file NamedObjectFactoryBase.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "NamedObjectFactoryBase.h"

namespace Myoushu
{
	// static member initialization

	std::map<std::string, NamedObjectFactoryBase*> NamedObjectFactoryBase::msClassNameFactoryMap;

	Poco::RWLock NamedObjectFactoryBase::msClassNameFactoryMapLock;

	// end - static member initialization

	NamedObjectFactoryBase::NamedObjectFactoryBase()
	{
	}

	NamedObjectFactoryBase::~NamedObjectFactoryBase()
	{
	}

	void NamedObjectFactoryBase::registerObjectFactory(const std::string& className, NamedObjectFactoryBase *pFactory)
	{
		Poco::ScopedRWLock lock(msClassNameFactoryMapLock, true);

		msClassNameFactoryMap[className] = pFactory;
	}

	NamedObjectFactoryBase* NamedObjectFactoryBase::unregisterObjectFactory(const std::string& className)
	{
		std::map<std::string, NamedObjectFactoryBase*>::iterator iter;
		NamedObjectFactoryBase *factory;

		Poco::ScopedRWLock lock(msClassNameFactoryMapLock, true);

		iter = msClassNameFactoryMap.find(className);
		if (iter == msClassNameFactoryMap.end())
		{
			return NULL;
		}

		factory = iter->second;
		msClassNameFactoryMap.erase(iter);

		return factory;
	}

	NamedObjectFactoryBase* NamedObjectFactoryBase::getObjectFactoryFromClassName(const std::string& className)
	{
		std::map<std::string, NamedObjectFactoryBase*>::iterator iter;

		Poco::ScopedRWLock lock(msClassNameFactoryMapLock, false);

		iter = msClassNameFactoryMap.find(className);
		if (iter == msClassNameFactoryMap.end())
		{
			return NULL;
		}

		return iter->second;
	}

} // namespace Myoushu

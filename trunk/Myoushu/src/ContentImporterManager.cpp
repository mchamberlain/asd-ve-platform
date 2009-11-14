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
 * @file ContentImporterManager.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "ContentImporterManager.h"

namespace Myoushu
{
	ContentImporterManager::ContentImporterManager()
	{
	}

	ContentImporterManager::~ContentImporterManager()
	{
	}

	ContentImporter* ContentImporterManager::make(const std::string& className, const std::string& instanceName)
	{
		ContentImporterFactory *pFactory;

		// Get the object factory that has been registered to create instances of the specified class name
		pFactory = static_cast<ContentImporterFactory*>(NamedObjectFactoryBase::getObjectFactoryFromClassName(className));

		// If pFactory is NULL, there is no factory for this class name, return NULL
		if (pFactory == NULL)
		{
			return NULL;
		}

		// Create an instance using the factory
		return pFactory->make(className, instanceName);
	}

	bool ContentImporterManager::destroy(ContentImporter *pInstance)
	{
		ContentImporterFactory *pFactory;

		// Get the object factory that has been registered to create and destroy instances of the specified class name
		pFactory = static_cast<ContentImporterFactory*>(NamedObjectFactoryBase::getObjectFactoryFromClassName(pInstance->getClassName()));

		// If pFactory is NULL, there is no factory for this class name, return NULL
		if (pFactory == NULL)
		{
			return false;
		}

		return pFactory->removeByName(pInstance->getName());
	}

} // namespace Myoushu

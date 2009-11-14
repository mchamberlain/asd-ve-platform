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
 * @file ContentImporterManager.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_CONTENT_IMPORTER_MANAGER_H
#define MYOUSHU_CONTENT_IMPORTER_MANAGER_H

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "ContentImporterFactory.h"

namespace Myoushu
{
	/**
	 * The ContentImporterManager manages various ContentImporterFactory and ContentImporter implementations that could be added to the engine through plug-ins.
	 */
	class MYOUSHU_API ContentImporterManager : public Ogre::Singleton<ContentImporterManager>
	{
		public:
			/** Constructor. */
			ContentImporterManager();

			/** Destructor. */
			virtual ~ContentImporterManager();

			/**
			 * Register a ContentImporterFactory instance with the class name of the ContentImporter instances it
			 * creates.
			 * @param pContentImporterFactory The ContentImporterFactory instance to register, must not be NULL.
			 * @param className The class name of the ContentImporter derived class it creates.
			 * @throws Exception::E_NULL_POINTER if pContentImporterFactory is NULL.
			 */
			void registerContentImporterFactory(ContentImporterFactory *pContentImporterFactory, const std::string& className) throw (Exception);

			/**
			 * Unregister a previously registered ContentImporterFactory instance for a class name.
			 * @param className The class name to unregister the ContentImporterFactory instance for.
			 * @return The unregistered ContentImporterFactory instance or NULL if no instance associated with
			 *		   className could be found.
			 */
			ContentImporterFactory* unregisterContentImporterFactory(const std::string& className);

			/**
			 * Creates a new ContentImporter derived instance of className with the specified instanceName.
			 * @param className The class name of the instance to create (the factory that was registered with
			 *					registerContentImporterFactory() will be used).
			 * @param instanceName The name of the newly created ContentImporter instance.
			 * @return The newly created ContentImporter instance of NULL if the instance could not be created 
			 * (generally this will happen if no factory has been registered for the specified className).
			 */
			ContentImporter* make(const std::string& className, const std::string& instanceName);

			/**
			 * Destroys the specified instance.
			 * @param pInstance The instance to destroy.
			 * @return True if the instance was successfully destroyed, false if the factory that created
			 *		   the instance could not be found, and which case the instance is not destroyed.
			 */
			bool destroy(ContentImporter *pInstance);

	}; // class ContentImporterManager

	// inlines
	inline void ContentImporterManager::registerContentImporterFactory(ContentImporterFactory *pContentImporterFactory, const std::string& className) throw (Exception)
	{
		// Check that pContentImporterFactory is not NULL
		if (pContentImporterFactory == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ContentImporterManager::registerContentImporterFactory(): pContentImporterFactory is NULL.");
		}

		// Register the ContentImporterFactory with the static methods in NamedObjectFactoryBase
		NamedObjectFactoryBase::registerObjectFactory(className, pContentImporterFactory);
	}

	inline ContentImporterFactory* ContentImporterManager::unregisterContentImporterFactory(const std::string& className)
	{
		// Unregister the ContentImporterFactory with the static methods in NamedObjectFactoryBase
		return static_cast<ContentImporterFactory*>(NamedObjectFactoryBase::unregisterObjectFactory(className));
	}

} // namespace Myoushu

#endif

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
 * @file FunctorManager.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_FUNCTOR_MANAGER_H
#define MYOUSHU_FUNCTOR_MANAGER_H

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "FunctorFactory.h"

namespace Myoushu
{
	/**
	 * Manages FunctorFactory and Functor implementations provided by plug-ins.
	 */
	class MYOUSHU_API FunctorManager : public Ogre::Singleton<FunctorManager>
	{
		public:
			/** Constructor. */
			FunctorManager();

			/** Destructor. */
			virtual ~FunctorManager();

			/**
			 * Register a FunctorFactory instance with the class name of the FunctorBase instances it
			 * creates.
			 * @param pFunctorFactory The FunctorFactory instance to register, must not be NULL.
			 * @param className The class name of the FunctorBase derived class it creates.
			 * @throws Exception::E_NULL_POINTER if pFunctorFactory is NULL.
			 */
			void registerFunctorFactory(FunctorFactory *pFunctorFactory, const std::string& className) throw (Exception);

			/**
			 * Unregister a previously registered FunctorFactory instance for a class name.
			 * @param className The class name to unregister the FunctorFactory instance for.
			 * @return The unregistered FunctorFactory instance or NULL if no instance associated with
			 *		   className could be found.
			 */
			FunctorFactory* unregisterFunctorFactory(const std::string& className);

			/**
			 * Creates a new FunctorBase derived instance of className with the specified instanceName.
			 * @param className The class name of the instance to create (the factory that was registered with
			 *					registerFunctorFactory() will be used).
			 * @param instanceName The name of the newly created FunctorBase instance.
			 * @return The newly created FunctorBase instance of NULL if the instance could not be created 
			 * (generally this will happen if no factory has been registered for the specified className).
			 */
			FunctorBase* make(const std::string& className, const std::string& instanceName);

			/**
			 * Destroys the specified instance.
			 * @param pInstance The instance to destroy.
			 * @return True if the instance was successfully destroyed, false if the factory that created
			 *		   the instance could not be found, and which case the instance is not destroyed.
			 */
			bool destroy(FunctorBase *pInstance);

	}; // class FunctorManager

	// inlines
	inline void FunctorManager::registerFunctorFactory(FunctorFactory *pFunctorFactory, const std::string& className) throw (Exception)
	{
		// Check that pFunctorFactory is not NULL
		if (pFunctorFactory == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "FunctorManager::registerFunctorFactory(): pFunctorFactory is NULL.");
		}

		// Register the FunctorFactory with the static methods in NamedObjectFactoryBase
		NamedObjectFactoryBase::registerObjectFactory(className, pFunctorFactory);
	}

	inline FunctorFactory* FunctorManager::unregisterFunctorFactory(const std::string& className)
	{
		// Unregister the FunctorFactory with the static methods in NamedObjectFactoryBase
		return static_cast<FunctorFactory*>(NamedObjectFactoryBase::unregisterObjectFactory(className));
	}

} // namespace Myoushu

#endif

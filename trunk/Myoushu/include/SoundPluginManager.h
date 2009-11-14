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
 * @file SoundPluginManager.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_SOUND_PLUGIN_MANAGER_H
#define MYOUSHU_SOUND_PLUGIN_MANAGER_H

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "SoundFactory.h"
#include "SoundManager.h"

namespace Myoushu
{
	/**
	 * Manages the factories and managers of the sound plug-ins active in the engine.
	 */
	class MYOUSHU_API SoundPluginManager : public Ogre::Singleton<SoundPluginManager>
	{
		public:
			/** Constructor. */
			SoundPluginManager();

			/** Destructor. */
			virtual ~SoundPluginManager();

			/**
			 * Register a SoundFactory instance with the class name of the Sound instances it
			 * creates.
			 * @param pSoundFactory The SoundFactory instance to register, must not be NULL.
			 * @param className The class name of the Sound derived class it creates.
			 * @throws Exception::E_NULL_POINTER if pSoundFactory is NULL.
			 */
			void registerSoundFactory(SoundFactory *pSoundFactory, const std::string& className) throw (Exception);

			/**
			 * Unregister a previously registered SoundFactory instance for a class name.
			 * @param className The class name to unregister the SoundFactory instance for.
			 * @return The unregistered SoundFactory instance or NULL if no instance associated with
			 *		   className could be found.
			 */
			SoundFactory* unregisterSoundFactory(const std::string& className);

			/** Gets the SoundFactory instance that creates instance of className. Returns NULL if no such factory is registered. */
			SoundFactory* getFactoryFor(const std::string& className);

			/**
			 * Creates a new Sound derived instance of className with the specified instanceName.
			 * @param className The class name of the instance to create (the factory that was registered with
			 *					registerSoundFactory() will be used).
			 * @param instanceName The name of the newly created Sound instance.
			 * @return The newly created Sound instance of NULL if the instance could not be created 
			 * (generally this will happen if no factory has been registered for the specified className).
			 */
			Sound* make(const std::string& className, const std::string& instanceName);

			/**
			 * Destroys the specified instance.
			 * @param pInstance The instance to destroy.
			 * @return True if the instance was successfully destroyed, false if the factory that created
			 *		   the instance could not be found, and which case the instance is not destroyed.
			 */
			bool destroy(Sound *pInstance);

	}; // class SoundManager

	// inlines
	inline void SoundPluginManager::registerSoundFactory(SoundFactory *pSoundFactory, const std::string& className) throw (Exception)
	{
		// Check that pSoundFactory is not NULL
		if (pSoundFactory == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SoundManager::registerSoundFactory(): pSoundFactory is NULL.");
		}

		// Register the SoundFactory with the static methods in NamedObjectFactoryBase
		NamedObjectFactoryBase::registerObjectFactory(className, pSoundFactory);
	}

	inline SoundFactory* SoundPluginManager::getFactoryFor(const std::string& className)
	{
		return static_cast<SoundFactory*>(NamedObjectFactoryBase::getObjectFactoryFromClassName(className));
	}


	inline SoundFactory* SoundPluginManager::unregisterSoundFactory(const std::string& className)
	{
		// Unregister the SoundFactory with the static methods in NamedObjectFactoryBase
		return static_cast<SoundFactory*>(NamedObjectFactoryBase::unregisterObjectFactory(className));
	}

} // namespace Myoushu

#endif

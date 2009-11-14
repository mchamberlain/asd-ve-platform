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
 * @file SceneFactory.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include "Ogre.h"
#include "NxOgre.h"

#include "Singleton.h"
#include "NamedObjectFactory.h"
#include "Scene.h"

namespace Myoushu
{
	/**
	 * This class manages the creation and destruction of Myoushu::Scene instances.
	 */
	class MYOUSHU_API SceneFactory : public NamedObjectFactory<Scene>, public Ogre::Singleton<SceneFactory>
	{
		public:
			/** Nullary Constructor */
			SceneFactory();

			/**
			 * Constructor.
			 * @param world The NxOgre::World instance to use when creating NxOgre::Scene instances.
			 */
			SceneFactory(NxOgre::World *world);

			/**
			 * Set the NxOgre::World instance to use.
			 * @param The NxOgre::World instance to use, cannot be NULL.
			 * @throws Exception::E_NULL_POINTER if world is NULL.
			 */
			inline void setWorld(NxOgre::World *world) throw (Exception)
			{
				// Ensure that world is not NULL
				if (world == NULL)
				{
					throw Exception(Exception::E_NULL_POINTER, "SceneFactory::setWorld(): world is NULL.");
				}

				Poco::ScopedRWLock lock(rwLock, false);

				this->world = world;
			}

			/**
			 * Getter for the NxOgre::World instance.
			 * @return The NxOgre::World instance.
			 */
			inline NxOgre::World* getWorld()
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return world;
			}

			/**
			 * Creates a new Myoushu::Scene instance. The scene is created with a GENERIC Ogre SceneManager
			 * and with the default physics options.
			 * @param name The name for the scene.
			 */
			virtual Scene* make(const std::string& name) throw (Exception);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual Scene* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Wrap the two specified instances.
			 * @param nxScene The NxOgre::Scene to wrap.
			 * @param sceneManager The Ogre::SceneManager instance to wrap.
			 */
			Scene* make(NxOgre::Scene *nxScene, Ogre::SceneManager *sceneManager) throw (Exception);

			/**
			 * Create a NxOgre::Scene and use an existing Ogre::SceneManager.
			 * @param name The name that the instances should have.
			 * @param sceneTypeName The type of Ogre::SceneManager to create.
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 * @param sceneManager The existing Ogre::SceneManager instance to use.
			 */
			Scene* make(const Ogre::String& name, NxOgre::SceneParams& sceneParams, Ogre::SceneManager *sceneManager) throw (Exception);

			/**
			 * Create NxOgre::Scene and Ogre::SceneManager instances with the
			 * specified parameters.
			 * @param name The name that the instances should have.
			 * @param sceneTypeName The type of Ogre::SceneManager to create.
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 */
			Scene* make(const Ogre::String& name, const Ogre::String& sceneTypeName, NxOgre::SceneParams& sceneParams) throw (Exception);

			/**
			 * Create NxOgre::Scene and Ogre::SceneManager instances with the
			 * specified parameters.
			 * @param name The name that the instances should have.
			 * @param sceneTypeMask A type mask indicating the type of Ogre::SceneManager to create.
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 */
			Scene* make(const Ogre::String& name, Ogre::SceneTypeMask sceneTypeMask, NxOgre::SceneParams& sceneParams) throw (Exception);

			/**
			 * Destroy the specified Scene instance and remove it from the factory.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			void destroy(Scene *scene) throw (Exception);

		protected:
			/** The NxOgre::World instance to use when creating NxOgre::Scene instances. */
			NxOgre::World *world;
	};

} // Myoushu

#endif

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
 * @file SceneFactory.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "SceneFactory.h"

//template<>
//Myoushu::SceneFactory* Ogre::Singleton<Myoushu::SceneFactory>::ms_Singleton = NULL;

namespace Myoushu
{
	SceneFactory::SceneFactory() : world(NULL)
	{
	}

	SceneFactory::SceneFactory(NxOgre::World *world) : world(world)
	{
	}

	Scene* SceneFactory::make(const std::string& name) throw (Exception)
	{
		NxOgre::SceneParams sceneParams;
		Scene *newScene;

		sceneParams.setToDefault();
		newScene = new Scene(ensureUniqueName(name), Ogre::ST_GENERIC, world, sceneParams);

		add(newScene);

		return newScene;
	}

	Scene* SceneFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		NxOgre::SceneParams sceneParams;

		sceneParams.setToDefault();

		if (className == NamedObject<Scene>::getStaticClassName())
		{
			return make(name, Ogre::ST_GENERIC, sceneParams);
		}
		else
		{
			throw Exception(Exception::E_NULL_POINTER, "SceneFactory::make(): " + className + " cannot be instantiated by this factory.");
		}

		return NULL;
	}

	Scene* SceneFactory::make(NxOgre::Scene *nxScene, Ogre::SceneManager *sceneManager) throw (Exception)
	{
		Scene *newScene;

		newScene = new Scene(nxScene, sceneManager);

		add(newScene);

		return newScene;
	}

	Scene* SceneFactory::make(const Ogre::String& name, NxOgre::SceneParams& sceneParams, Ogre::SceneManager *sceneManager) throw (Exception)
	{
		Scene *newScene;

		newScene = new Scene(ensureUniqueName(name), world, sceneParams, sceneManager);

		add(newScene);

		return newScene;
	}

	Scene* SceneFactory::make(const Ogre::String& name, const Ogre::String& sceneTypeName, NxOgre::SceneParams& sceneParams) throw (Exception)
	{
		Scene *newScene;

		newScene = new Scene(ensureUniqueName(name), sceneTypeName, world, sceneParams);

		add(newScene);

		return newScene;
	}

	Scene* SceneFactory::make(const Ogre::String& name, Ogre::SceneTypeMask sceneTypeMask, NxOgre::SceneParams& sceneParams) throw (Exception)
	{
		Scene *newScene;

		newScene = new Scene(ensureUniqueName(name), sceneTypeMask, world, sceneParams);

		add(newScene);
		
		return newScene;
	}

	void SceneFactory::destroy(Scene *scene) throw (Exception)
	{
		bool sceneInFactory;

		// scene mustn't be NULL, throw an exception if it is.
		if (scene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "SceneFactory::destory(): scene is NULL");
		}

		// If the Scene instance is in the factory remove it.
		sceneInFactory = remove(scene);

		// If the Scene instance was in the factory, delete it.
		if (sceneInFactory)
		{
			delete scene;
		}
	}

} // Myoushu

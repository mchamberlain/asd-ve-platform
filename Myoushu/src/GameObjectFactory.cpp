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
 * @file GameObjectFactory.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include <sstream>

#include "GameObjectFactory.h"
#include "SceneFactory.h"

//template<> Myoushu::GameObjectFactory* Ogre::Singleton<Myoushu::GameObjectFactory>::ms_Singleton = NULL;

namespace Myoushu
{
	GameObjectFactory::GameObjectFactory()
	{
		// Register this object factory as the creator of GameObject, GameActorObject, GameBodyObject and GameCharacterObject
		registerObjectFactory(NamedObject<GameObject>::getStaticClassName(), this);
		registerObjectFactory(NamedObject<GameActorObject>::getStaticClassName(), this);
		registerObjectFactory(NamedObject<GameBodyObject>::getStaticClassName(), this);
		registerObjectFactory(NamedObject<GameCharacterObject>::getStaticClassName(), this);
	}

	GameObjectFactory::~GameObjectFactory()
	{
	}

	GameObject* GameObjectFactory::make(const std::string& name)
	{
		GameObject *newGameObject;

		newGameObject = new GameObject(ensureUniqueName(name));

		add(newGameObject);

		return newGameObject;
	}

	GameObject* GameObjectFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		Scene *pDefaultScene;

		pDefaultScene = SceneFactory::getSingleton().find(Constants::DEFAULT_SCENE_MANAGER);
		if (pDefaultScene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectFactory::make(): Default scene manager does not exist.");
		}

		if (className == NamedObject<GameObject>::getStaticClassName())
		{
			return make(name);
		}
		else if (className == NamedObject<GameActorObject>::getStaticClassName())
		{
			return makeActor(name, pDefaultScene, NULL);
		}
		else if (className == NamedObject<GameBodyObject>::getStaticClassName())
		{
			return makeBody(name, "", pDefaultScene, NULL);
		}
		else if (className == NamedObject<GameCharacterObject>::getStaticClassName())
		{
			GameCharacterObject *character;
			NxOgre::CharacterParams params;

			Ogre::String uName = ensureUniqueName(name);
			params.setToDefault();

			character = new GameCharacterObject(uName, pDefaultScene, NULL, params);

			add(character);

			return character;
		}
		else
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectFactory::make(): " + className + " cannot be instantiated by this factory.");
		}

		return NULL;
	}

	GameActorObject* GameObjectFactory::makeActor(const Ogre::String& name, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameActorObject *newGameActorObject;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		newGameActorObject = new GameActorObject(ensureUniqueName(name), scene, collisionShape, initialPose, actorParams);

		add(newGameActorObject);

		return newGameActorObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, const Ogre::String& meshName, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), meshName, scene, collisionShape, initialPose, actorParams);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		NxOgre::ActorParams params;
		GameBodyObject *newGameBodyObject;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		params = actorParams;
		params.mNodeName = sceneNode->getName();
		params.mNodeScale = sceneNode->_getDerivedScale();
		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), meshName, sceneNode, scene, collisionShape, params);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		NxOgre::ActorParams params;
		GameBodyObject *newGameBodyObject;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		params = actorParams;
		params.mNodeName = sceneNode->getName();
		params.mNodeScale = sceneNode->_getDerivedScale();
		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), sceneNode, entity, scene, collisionShape, params);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, Ogre::Entity *entity, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), entity, scene, collisionShape, initialPose, actorParams);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	NxOgre::ConvexShape* GameObjectFactory::getConvexShapeFromFile(const Ogre::String& fileName, const Ogre::String& resourceGroup, const NxOgre::ShapeParams shapeParams)
	{
		NxOgre::ConvexShape *pCollisionShape;
		Ogre::FileInfoListPtr pFileInfoList;
		Ogre::FileInfoList::const_iterator fileInfoIter;

		// Get the full path for the specified collision shape file from Ogre's resource management system
		pCollisionShape = NULL;
		pFileInfoList = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(resourceGroup, fileName, false);
		if (!pFileInfoList.isNull())
		{
			for (fileInfoIter = pFileInfoList->begin(); ((pCollisionShape == NULL) && (fileInfoIter != pFileInfoList->end())); ++fileInfoIter)
			{
				const Ogre::FileInfo& fileInfo = *fileInfoIter;

				if ((fileInfo.filename == fileName) && (fileInfo.archive != NULL))
				{
					pCollisionShape = new NxOgre::ConvexShape(fileInfo.archive->getName() + "\\" + fileInfo.path + fileInfo.filename, shapeParams);
				}
			}
		}

		return pCollisionShape;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, const Ogre::String& meshName, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;
		NxOgre::ConvexShape *pCollisionShape;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		// Get the convex collision mesh from file
		pCollisionShape = getConvexShapeFromFile(collisionShapeFileName, Constants::RG_COLLISION_MESH, shapeParams);
		// If the file could not be found, throw an exception
		if (pCollisionShape == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " << collisionShapeFileName);
			throw Exception(Exception::E_FILE_NOT_FOUND, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " + collisionShapeFileName);
		}

		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), meshName, scene, pCollisionShape, initialPose, actorParams);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;
		NxOgre::ConvexShape *pCollisionShape;
		NxOgre::ActorParams params;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		// Get the convex collision mesh from file
		pCollisionShape = getConvexShapeFromFile(collisionShapeFileName, Constants::RG_COLLISION_MESH, shapeParams);
		// If the file could not be found, throw an exception
		if (pCollisionShape == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " << collisionShapeFileName);
			throw Exception(Exception::E_FILE_NOT_FOUND, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " + collisionShapeFileName);
		}

		params = actorParams;
		params.mNodeName = sceneNode->getName();
		params.mNodeScale = sceneNode->_getDerivedScale();
		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), meshName, sceneNode, scene, pCollisionShape, params);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;
		NxOgre::ConvexShape *pCollisionShape;
		NxOgre::ActorParams params;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		// Get the convex collision mesh from file
		pCollisionShape = getConvexShapeFromFile(collisionShapeFileName, Constants::RG_COLLISION_MESH, shapeParams);
		// If the file could not be found, throw an exception
		if (pCollisionShape == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " << collisionShapeFileName);
			throw Exception(Exception::E_FILE_NOT_FOUND, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " + collisionShapeFileName);
		}

		params = actorParams;
		params.mNodeName = sceneNode->getName();
		params.mNodeScale = sceneNode->_getDerivedScale();
		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), sceneNode, entity, scene, pCollisionShape, params);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameBodyObject* GameObjectFactory::makeBody(const Ogre::String& name, Ogre::Entity *entity, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams, const NxOgre::Pose& initialPose, const NxOgre::ActorParams& actorParams) throw (Exception)
	{
		GameBodyObject *newGameBodyObject;
		NxOgre::ConvexShape *pCollisionShape;

		if (!ensureActorGroupExists(scene, actorParams.mGroupAsIndex, actorParams.mGroupAsName))
		{
			LOG(EngineLog::LM_WARNING, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " << collisionShapeFileName);
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "GameObjectFactory: the specified actor group does not exist and could not be created.");
		}

		// Get the convex collision mesh from file
		pCollisionShape = getConvexShapeFromFile(collisionShapeFileName, Constants::RG_COLLISION_MESH, shapeParams);
		// If the file could not be found, throw an exception
		if (pCollisionShape == NULL)
		{
			throw Exception(Exception::E_FILE_NOT_FOUND, "GameObjectFactory::makeBody(): Cannot find the specified collisionShapeFileName: " + collisionShapeFileName);
		}

		newGameBodyObject = new GameBodyObject(ensureUniqueName(name), entity, scene, pCollisionShape, initialPose, actorParams);

		add(newGameBodyObject);

		return newGameBodyObject;
	}

	GameCharacterObject* GameObjectFactory::makeCharacter(const Ogre::String& name, const Ogre::String& meshName, const Ogre::String& skeletonMeshName, Scene* scene, const NxOgre::Pose& pose, const NxOgre::CharacterParams& params) throw (Exception)
	{
		GameCharacterObject *character;

		if (scene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectFactory::makeCharacter(): scene is NULL.");
		}

		Ogre::String uName = ensureUniqueName(name);

		character = new GameCharacterObject(uName, scene, scene->createCharacter(uName, pose, params), params);
		if (character->getNxController() == NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "NxController NULL");
			// Error creating physics aspect of the character, destroy it and return NULL
			delete character;

			return NULL;
		}

		if (meshName != "")
		{
			character->attachMesh(meshName);
		}
		if (skeletonMeshName != "")
		{
			character->attachSkeletonMesh(skeletonMeshName);
		}

		add(character);

		return character;
	}

	void GameObjectFactory::destroy(GameObject *gameObject) throw (Exception)
	{
		Iterator iter;
		bool objectInFactory;

		// If gameObject is NULL, throw an exception
		if (gameObject == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectFactory::destroy(): gameObject is NULL.");
		}

		// Remove the object from the factory, if it is in the factory.
		objectInFactory = remove(gameObject);

		// Delete the object if it was in the factory.
		//if (objectInFactory)
		//{
		//	delete gameObject;
		//}
		// Memory managed by Poco::AutoPtr
	}

	bool GameObjectFactory::ensureActorGroupExists(Scene *pScene, NxActorGroup actorGroupID, const Ogre::String& actorGroupName) const
	{
		if ((pScene == NULL) || ((actorGroupName.length() == 0) && (actorGroupID == 0)))
		{
			return true;
		}

		// Only consider actorGroupID if actorGroupName is ""
		if (actorGroupName.length() > 0)
		{
			if (pScene->getActorGroup(actorGroupName) == NULL)
			{
				// Group does not exist, create it
				pScene->createActorGroup(actorGroupName);
			}
		}
		else
		{
			if (pScene->getActorGroupsByIndex()->get(actorGroupID) == NULL)
			{
				return false;
			}
		}

		return true;
	}

	void GameObjectFactory::destroyAllFromScene(Scene *pScene) throw (Exception)
	{
		Iterator iter;
		Iterator endIter;
		std::list<GameObject*> objectsToRemove;
		std::list<GameObject*>::iterator removeIter;

		if (pScene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameObjectFactory::destroyAllFromScene(): pScene is NULL!");
		}

		iter = begin();
		endIter = end();

		{
			Poco::ScopedRWLock lock(rwLock, false);

			// Loop through all GameObjects and check if their parent scenes match pScene
			// If it does, put the GameObject in the objectsToRemove list
			for (; iter != endIter; ++iter)
			{
				GameObject *pGameObject;
				Scene *pParentScene;
				
				pGameObject = iter->second;
				pParentScene = pGameObject->getScene();
				if ((pParentScene != NULL) && (pParentScene == pScene))
				{
					// The GameObject is in pScene, put it in the remove list
					objectsToRemove.push_back(pGameObject);
				}
			}
		}

		// If the remove list is empty, exit the function
		if (objectsToRemove.empty())
		{
			return;
		}
		// otherwise remove all GameObjects in the remove list
		for (removeIter = objectsToRemove.begin(); removeIter != objectsToRemove.end(); )
		{
			destroy(*removeIter);
			// Erase the current element from the list and returns the position of the next element
			removeIter = objectsToRemove.erase(removeIter);
		}
	}

} // Myoushu
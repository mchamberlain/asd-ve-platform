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
 * @file Scene.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "Scene.h"
#include "GlobalLocks.h"
#include "GameObjectFactory.h"

namespace Myoushu
{

	CLASS_NAME(Scene, "Myoushu::Scene");

	Scene::Scene(NxOgre::Scene *nxScene, Ogre::SceneManager *sceneManager) throw (Exception) : NamedInstance("")
	{
		// If either nxScene or sceneManager is NULL, throw an exception
		if ((nxScene == NULL) || (sceneManager == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "Scene::Scene(): nxScene or sceneManager is NULL.");
		}

		// Set the nxScene and sceneManager values
		this->nxScene = nxScene;
		this->sceneManager = sceneManager;
		this->nxSceneCreated = false;
		this->sceneManagerCreated = false;
		this->world = NULL;

		// Set the instance name
		this->instanceName = nxScene->getName();
	}

	Scene::Scene(const Ogre::String& name, NxOgre::World *world, NxOgre::SceneParams& sceneParams, Ogre::SceneManager *sceneManager) throw (Exception) : NamedInstance(name)
	{
		// Ensure that world and sceneManager is not NULL
		if ((world == NULL) || (sceneManager == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "Scene::Scene(): world or sceneManager is NULL.");
		}

		this->world = world;

		// Set the Ogre::SceneManager
		this->sceneManager = sceneManager;

		try
		{
			GlobalLocks::rwLockNxOgre.writeLock();
			nxScene = world->createScene(name, sceneManager, sceneParams);
			GlobalLocks::rwLockNxOgre.unlock();
		}
		catch (...)
		{
			GlobalLocks::rwLockNxOgre.unlock();
			throw Exception(Exception::E_GENERAL_EXCEPTION, "Scene::Scene(): Error while creating NxOgre::Scene instance.");
		}

		this->nxSceneCreated = true;
		this->sceneManagerCreated = false;
	}

	Scene::Scene(const Ogre::String& name, const Ogre::String& sceneTypeName, NxOgre::World *world, NxOgre::SceneParams& sceneParams) throw (Exception) : NamedInstance(name)
	{
		Ogre::Root *ogreRootPtr;

		ogreRootPtr = Ogre::Root::getSingletonPtr();

		// Ensure that world and the Ogre::Root is not NULL
		if ((world == NULL) || (ogreRootPtr == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "Scene::Scene(): world or ogreRootPtr is NULL");
		}

		this->world = world;

		// Create the Ogre::SceneManager instance
		try
		{
			GlobalLocks::rwLockOgreRoot.writeLock();
			sceneManager = ogreRootPtr->createSceneManager(sceneTypeName, name);
			GlobalLocks::rwLockOgreRoot.unlock();
		}
		catch (Ogre::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}

		try
		{
			GlobalLocks::rwLockNxOgre.writeLock();
			nxScene = world->createScene(name, sceneManager, sceneParams);
			GlobalLocks::rwLockNxOgre.unlock();
		}
		catch (...)
		{
			GlobalLocks::rwLockNxOgre.unlock();
			throw Exception(Exception::E_GENERAL_EXCEPTION, "Scene::Scene(): Error while creating NxOgre::Scene instance.");
		}

		this->nxSceneCreated = true;
		this->sceneManagerCreated = true;
	}

	Scene::Scene(const Ogre::String& name, Ogre::SceneTypeMask sceneTypeMask, NxOgre::World *world, NxOgre::SceneParams& sceneParams) throw (Exception) : NamedInstance(name)
	{
		Ogre::Root *ogreRootPtr;

		ogreRootPtr = Ogre::Root::getSingletonPtr();

		// Ensure that world and the Ogre::Root is not NULL
		if ((world == NULL) || (ogreRootPtr == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "Scene::Scene(): world or ogreRootPtr is NULL");
		}

		this->world = world;

		// Create the Ogre::SceneManager instance
		try
		{
			GlobalLocks::rwLockOgreRoot.writeLock();
			sceneManager = ogreRootPtr->createSceneManager(sceneTypeMask, name);
			GlobalLocks::rwLockOgreRoot.unlock();
		}
		catch (Ogre::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}

		try
		{
			GlobalLocks::rwLockNxOgre.writeLock();
			nxScene = world->createScene(name, sceneManager, sceneParams);
			GlobalLocks::rwLockNxOgre.unlock();
		}
		catch (...)
		{
			GlobalLocks::rwLockNxOgre.unlock();
			throw Exception(Exception::E_GENERAL_EXCEPTION, "Scene::Scene(): Error while creating NxOgre::Scene instance.");
		}

		this->nxSceneCreated = true;
		this->sceneManagerCreated = true;
	}

	Scene::~Scene()
	{
		Ogre::Root *ogreRootPtr;

		// If nxScene was created in the constructor, destroy it.
		if ((nxScene) && (nxSceneCreated))
		{
			if (world)
			{
				try
				{
					GlobalLocks::rwLockNxOgre.writeLock();
					world->destroyScene(nxScene->getName());
					GlobalLocks::rwLockNxOgre.unlock();
				}
				catch (...)
				{
					GlobalLocks::rwLockNxOgre.unlock();
					//throw Exception(Exception::E_GENERAL_EXCEPTION, "Scene::~Scene(): error while destroying NxOgre::Scene.");
				}
			}
			else
			{
				delete nxScene;
			}
		}

		// If sceneManager was created in the constructor, destroy it.
		if ((sceneManager) && (sceneManagerCreated))
		{
			ogreRootPtr = Ogre::Root::getSingletonPtr();
			// If the Ogre::Root is available use it to destroy the SceneManager, otherwise just use the destructor
			if (ogreRootPtr)
			{
				try
				{
					GlobalLocks::rwLockOgreRoot.writeLock();
					ogreRootPtr->destroySceneManager(sceneManager);
					GlobalLocks::rwLockOgreRoot.unlock();
				}
				catch (Ogre::Exception& e)
				{
					GlobalLocks::rwLockOgreRoot.unlock();
					//throw Exception(Exception::E_OGRE_EXCEPTION, e.what())
				}
			}
			else
			{
				delete sceneManager;
			}
		}
	}

	std::list<GameObject*> Scene::getGameObjectsFromRaycast(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::Real range, NxOgre::RayCaster::ActorFilter filter)
	{
		// Get a read lock on the NxOgre scene
		Poco::ScopedRWLock lock(rwLockNxScene, false);

		// Create a RayCaster object to do the actual ray casting
		NxOgre::RayCaster rayCaster(position, direction, range, NxOgre::RayCaster::RCT_ALL, nxScene);
		std::list<GameObject*> gameObjectList;

		// Cast the ray, checking for intersections against the collision shapes of the actors
		rayCaster.castShape(filter);

		if (rayCaster.mReport.count() > 0) 
		{
			// Loop through the actors that intersect the ray, find their GameObject instances and add it to the list
			GameObjectFactory &gameObjectFactory = GameObjectFactory::getSingleton();
			for (NxOgre::RayCastHit hit = rayCaster.mReport._begin(); !rayCaster.mReport._atEnd(); hit = rayCaster.mReport._next()) 
			{
				GameObject *pGameObject = NULL;

				// Try to find the GameObject instance of mActor
				if (hit.mActor != NULL)
				{
					pGameObject = gameObjectFactory.find(hit.mActor->getName());
				}
				else if (hit.mCharacter != NULL)
				{
					pGameObject = gameObjectFactory.find(hit.mCharacter->getName());
				}

				if (pGameObject == NULL)
				{
					// If the GameObject instance could not be found, log a warning
					LOG(EngineLog::LM_WARNING, "Scene::getGameObjectsFromRaycast(): NxActor '" << hit.mActor->getName() << "' does not exist as a GameObject...");
				}
				else
				{
					// Add the GameObject instance to the back of the list
					gameObjectList.push_back(pGameObject);
				}
			}
		}

		// Return the list of GameObjects that intersect the ray
		return gameObjectList;
	}

	GameObject* Scene::getClosestGameObjectFromRaycast(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::Real range, NxOgre::RayCaster::ActorFilter filter)
	{
		// Get a read lock on the NxOgre scene
		Poco::ScopedRWLock lock(rwLockNxScene, false);

		// Create a RayCaster object to do the actual ray casting
		NxOgre::RayCaster rayCaster(position, direction, range, NxOgre::RayCaster::RCT_CLOSEST, nxScene);
		GameObject* pGameObject = NULL;

		// Cast the ray, checking for intersections against the collision shapes of the actors
		rayCaster.castShape(filter);

		if (rayCaster.getClosestActor() != NULL)
		{
			pGameObject = GameObjectFactory::getSingleton().find(rayCaster.getClosestActor()->getName());
		}
		else if (rayCaster.getClosestCharacter() != NULL)
		{
			pGameObject = GameObjectFactory::getSingleton().find(rayCaster.getClosestCharacter()->getName());
		}

		return pGameObject;
	}

	void Scene::getGameObjectsInCameraView(Ogre::Camera& camera, std::list<GameObject*> &gameObjectList)
	{
		// Get a read lock on the Ogre SceneManager
		Poco::ScopedRWLock lock(rwLockSceneManager, false);

		// Get the camera frustum plane bounded volume
		std::vector<Ogre::PlaneBoundedVolume> planeBoundedVolumeList;
		planeBoundedVolumeList.push_back(camera.getCameraToViewportBoxVolume(0, 0, 1, 1, true));
		// Create the Ogre SceneQuery instance
		Ogre::PlaneBoundedVolumeListSceneQuery *pQuery = sceneManager->createPlaneBoundedVolumeQuery( planeBoundedVolumeList );


		Ogre::SceneQueryResult result = pQuery->execute();
		
		// Run through the results of the query and look-up the GameObjects from the GameObjectFactory by name
		GameObjectFactory& gameObjectFactory = GameObjectFactory::getSingleton();
		Ogre::SceneQueryResultMovableList::iterator iter;
		for (iter = result.movables.begin(); iter != result.movables.end(); ++iter)
		{
			Ogre::MovableObject *pMovableObject = *iter;

			GameObject *pGameObject = gameObjectFactory.find(pMovableObject->getName());
			if (pGameObject)
			{
				gameObjectList.push_back(pGameObject);
			}
		}

		sceneManager->destroyQuery(pQuery);
	}

	//********** OGRE::SCENEMANAGER METHODS ***********//

	const Ogre::String& Scene::getTypeName(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getTypeName();
	}

	
	Ogre::Camera* Scene::createCamera(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createCamera(name);
	}

	
	Ogre::Camera* Scene::getCamera(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getCamera(name);
	}

	
	bool Scene::hasCamera(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasCamera(name);
	}

	
	void Scene::destroyCamera(Ogre::Camera *cam)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyCamera(cam);
	}

	
	void Scene::destroyCamera(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyCamera(name);
	}

	
	void Scene::destroyAllCameras(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllCameras();
	}

	
	Ogre::Light* Scene::createLight(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createLight(name);
	}

	
	Ogre::Light* Scene::getLight(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getLight(name);
	}

	
	bool Scene::hasLight(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasLight(name);
	}

	
	void Scene::destroyLight(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyLight(name);
	}

	
	void Scene::destroyLight(Ogre::Light* light)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyLight(light);
	}
	
	void Scene::destroyAllLights(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllLights();
	}

	
	void Scene::_notifyLightsDirty(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		sceneManager->_notifyLightsDirty();
	}

	
	Ogre::ulong Scene::_getLightsDirtyCounter(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->_getLightsDirtyCounter();
	}

	
	const Ogre::LightList& Scene::_getLightsAffectingFrustum(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->_getLightsAffectingFrustum();
	}

	
	void Scene::_populateLightList(const Ogre::Vector3& position, Ogre::Real radius, Ogre::LightList& destList)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_populateLightList(position, radius, destList);
	}


	
	Ogre::SceneNode* Scene::createSceneNode(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createSceneNode();
	}

	
	Ogre::SceneNode* Scene::createSceneNode(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createSceneNode(name);
	}

	
	void Scene::destroySceneNode(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroySceneNode(name);
	}

	
	Ogre::SceneNode* Scene::getRootSceneNode(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getRootSceneNode();
	}

	
	Ogre::SceneNode* Scene::getSceneNode(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSceneNode(name);
	}

	
	bool Scene::hasSceneNode(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasSceneNode(name);
	}


	
	Ogre::Entity* Scene::createEntity(const Ogre::String& entityName, const Ogre::String& meshName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createEntity(entityName, meshName);
	}

	
	Ogre::Entity* Scene::createEntity(const Ogre::String& entityName, Ogre::SceneManager::PrefabType ptype)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createEntity(entityName, ptype);
	}
	
	Ogre::Entity* Scene::getEntity(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->getEntity(name);
	}
	
	bool Scene::hasEntity(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasEntity(name);
	}

	
	void Scene::destroyEntity(Ogre::Entity* ent)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyEntity(ent);
	}

	
	void Scene::destroyEntity(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyEntity(name);
	}

	
	void Scene::destroyAllEntities(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllEntities();
	}

	
	Ogre::ManualObject* Scene::createManualObject(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createManualObject(name);
	}
	
	Ogre::ManualObject* Scene::getManualObject(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getManualObject(name);
	}
	
	bool Scene::hasManualObject(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasManualObject(name);
	}

	
	void Scene::destroyManualObject(Ogre::ManualObject* obj)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyManualObject(obj);
	}
	
	void Scene::destroyManualObject(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyManualObject(name);
	}
	
	void Scene::destroyAllManualObjects(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllManualObjects();
	}
	
	Ogre::BillboardChain* Scene::createBillboardChain(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createBillboardChain(name);
	}
	
	Ogre::BillboardChain* Scene::getBillboardChain(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getBillboardChain(name);
	}
	
	bool Scene::hasBillboardChain(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasBillboardChain(name);
	}

	
	void Scene::destroyBillboardChain(Ogre::BillboardChain* obj)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyBillboardChain(obj);
	}
	
	void Scene::destroyBillboardChain(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyBillboardChain(name);
	}
	
	void Scene::destroyAllBillboardChains(void)		
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllBillboardChains();
	}
	
	Ogre::RibbonTrail* Scene::createRibbonTrail(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createRibbonTrail(name);
	}
	
	Ogre::RibbonTrail* Scene::getRibbonTrail(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getRibbonTrail(name);
	}
	
	bool Scene::hasRibbonTrail(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasRibbonTrail(name);
	}

	
	void Scene::destroyRibbonTrail(Ogre::RibbonTrail* obj)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyRibbonTrail(obj);
	}
	
	void Scene::destroyRibbonTrail(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyRibbonTrail(name);
	}
	
	void Scene::destroyAllRibbonTrails(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllRibbonTrails();
	}

	
	Ogre::ParticleSystem* Scene::createParticleSystem(const Ogre::String& name,	const Ogre::String& templateName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createParticleSystem(name, templateName);
	}
	
	Ogre::ParticleSystem* Scene::createParticleSystem(const Ogre::String& name, size_t quota, const Ogre::String& resourceGroup)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createParticleSystem(name, quota, resourceGroup);
	}
	
	Ogre::ParticleSystem* Scene::getParticleSystem(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getParticleSystem(name);
	}
	
	bool Scene::hasParticleSystem(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasParticleSystem(name);
	}

	
	void Scene::destroyParticleSystem(Ogre::ParticleSystem* obj)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyParticleSystem(obj);
	}
	
	void Scene::destroyParticleSystem(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyParticleSystem(name);
	}
	
	void Scene::destroyAllParticleSystems(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllParticleSystems();
	}

	
	void Scene::clearScene(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		// First destroy all GameObjects belonging to this scene via the GameObjectFactory
		GameObjectFactory::getSingleton().destroyAllFromScene(this);

		LOG(EngineLog::LM_INFO_ENGINE, "b OGRE scene clear");
		if (sceneManager != NULL)
		{
			sceneManager->clearScene();
		}
		LOG(EngineLog::LM_INFO_ENGINE, "a OGRE scene clear");
	}

	
	void Scene::setAmbientLight(const Ogre::ColourValue& colour)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setAmbientLight(colour);
	}

	
	const Ogre::ColourValue& Scene::getAmbientLight(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getAmbientLight();
	}

	
	void Scene::setWorldGeometry(const Ogre::String& filename)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setWorldGeometry(filename);
	}

	
	void Scene::setWorldGeometry(Ogre::DataStreamPtr& stream, const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setWorldGeometry(stream, typeName);
	}

	
	size_t Scene::estimateWorldGeometry(const Ogre::String& filename)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->estimateWorldGeometry(filename);
	}

			
	size_t Scene::estimateWorldGeometry(Ogre::DataStreamPtr& stream, const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->estimateWorldGeometry(stream, typeName);
	}
	
	Ogre::ViewPoint Scene::getSuggestedViewpoint(bool random)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSuggestedViewpoint(random);
	}

	
	bool Scene::setOption( const Ogre::String& strKey, const void* pValue )
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->setOption(strKey, pValue);
	}

	
	bool Scene::getOption( const Ogre::String& strKey, void* pDestValue )
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->getOption(strKey, pDestValue);
	}

	
	bool Scene::hasOption( const Ogre::String& strKey ) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasOption(strKey);
	}
	
	bool Scene::getOptionValues( const Ogre::String& strKey, Ogre::StringVector& refValueList )
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->getOptionValues(strKey, refValueList);
	}

	
	bool Scene::getOptionKeys( Ogre::StringVector& refKeys )
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getOptionKeys(refKeys);
	}

	
	void Scene::_updateSceneGraph(Ogre::Camera* cam)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_updateSceneGraph(cam);
	}

	
	void Scene::_findVisibleObjects(Ogre::Camera* cam, Ogre::VisibleObjectsBoundsInfo* visibleBounds, bool onlyShadowCasters)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		sceneManager->_findVisibleObjects(cam, visibleBounds, onlyShadowCasters);
	}

	
	void Scene::_applySceneAnimations(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_applySceneAnimations();
	}

	
	void Scene::_renderVisibleObjects(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_renderVisibleObjects();
	}

	
	void Scene::_renderScene(Ogre::Camera* camera, Ogre::Viewport* vp, bool includeOverlays)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_renderScene(camera, vp, includeOverlays);
	}

	
	void Scene::_queueSkiesForRendering(Ogre::Camera* cam)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_queueSkiesForRendering(cam);
	}



	
	void Scene::_setDestinationRenderSystem(Ogre::RenderSystem* sys)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_setDestinationRenderSystem(sys);
	}

	void Scene::setSkyPlane(bool enable, const Ogre::Plane& plane, const Ogre::String& materialName, Ogre::Real scale,
		Ogre::Real tiling, bool drawFirst, Ogre::Real bow, int xsegments, int ysegments, const Ogre::String& groupName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setSkyPlane(enable, plane, materialName, scale, tiling, drawFirst, bow, xsegments, ysegments, groupName);
	}

	Ogre::SceneNode* Scene::getSkyPlaneNode(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyPlaneNode();
	}

	const Ogre::SceneManager::SkyPlaneGenParameters& Scene::getSkyPlaneGenParameters(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyPlaneGenParameters();
	}

	void Scene::setSkyBox(bool enable, const Ogre::String& materialName, Ogre::Real distance, bool drawFirst, const Ogre::Quaternion& orientation,
		const Ogre::String& groupName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setSkyBox(enable, materialName, distance, drawFirst, orientation, groupName);
	}

	
	bool Scene::isSkyBoxEnabled(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isSkyBoxEnabled();
	}

	
	Ogre::SceneNode* Scene::getSkyBoxNode(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyBoxNode();
	}

	
	const Ogre::SceneManager::SkyBoxGenParameters& Scene::getSkyBoxGenParameters(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyBoxGenParameters();
	}

	void Scene::setSkyDome(bool enable, const Ogre::String& materialName, Ogre::Real curvature, Ogre::Real tiling, Ogre::Real distance, bool drawFirst,
		const Ogre::Quaternion& orientation, int xsegments, int ysegments, int ysegments_keep, const Ogre::String& groupName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setSkyDome(enable, materialName, curvature, tiling, distance, drawFirst, orientation, xsegments, ysegments, ysegments_keep, groupName);
	}

	
	bool Scene::isSkyDomeEnabled(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isSkyDomeEnabled();
	}

	
	Ogre::SceneNode* Scene::getSkyDomeNode(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyDomeNode();
	}

	
	const Ogre::SceneManager::SkyDomeGenParameters& Scene::getSkyDomeGenParameters(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSkyDomeGenParameters();
	}

	
	void Scene::setFog(Ogre::FogMode mode, const Ogre::ColourValue& colour,	Ogre::Real expDensity, Ogre::Real linearStart, Ogre::Real linearEnd)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setFog(mode, colour, expDensity, linearStart, linearEnd);
	}

	
	Ogre::FogMode Scene::getFogMode(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFogMode();
	}

	
	const Ogre::ColourValue& Scene::getFogColour(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFogColour();
	}

	
	Ogre::Real Scene::getFogStart(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFogStart();
	}

	
	Ogre::Real Scene::getFogEnd(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFogEnd();
	}

	
	Ogre::Real Scene::getFogDensity(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFogDensity();
	}


	
	Ogre::BillboardSet* Scene::createBillboardSet(const Ogre::String& name, unsigned int poolSize)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createBillboardSet(name, poolSize);
	}

	
	Ogre::BillboardSet* Scene::getBillboardSet(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getBillboardSet(name);
	}
	
	bool Scene::hasBillboardSet(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasBillboardSet(name);
	}

	
	void Scene::destroyBillboardSet(Ogre::BillboardSet* set)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyBillboardSet(set);
	}

	
	void Scene::destroyBillboardSet(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyBillboardSet(name);
	}

	
	void Scene::destroyAllBillboardSets(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllBillboardSets();
	}

	
	void Scene::setDisplaySceneNodes(bool display)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setDisplaySceneNodes(display);
	}
	
	bool Scene::getDisplaySceneNodes(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getDisplaySceneNodes();
	}

	Ogre::Animation* Scene::createAnimation(const Ogre::String& name, Ogre::Real length)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createAnimation(name, length);
	}

	
	Ogre::Animation* Scene::getAnimation(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getAnimation(name);
	}
	
	bool Scene::hasAnimation(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasAnimation(name);
	}

	
	void Scene::destroyAnimation(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAnimation(name);
	}

	
	void Scene::destroyAllAnimations(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllAnimations();
	}

	Ogre::AnimationState* Scene::createAnimationState(const Ogre::String& animName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createAnimationState(animName);
	}

	
	Ogre::AnimationState* Scene::getAnimationState(const Ogre::String& animName) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getAnimationState(animName);
	}
	
	bool Scene::hasAnimationState(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasAnimationState(name);
	}

	
	void Scene::destroyAnimationState(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAnimationState(name);
	}

	
	void Scene::destroyAllAnimationStates(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllAnimationStates();
	}

	
	void Scene::manualRender(Ogre::RenderOperation* rend, Ogre::Pass* pass, Ogre::Viewport* vp, 
		const Ogre::Matrix4& worldMatrix, const Ogre::Matrix4& viewMatrix, const Ogre::Matrix4& projMatrix, 
		bool doBeginEndFrame) 
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->manualRender(rend, pass, vp, worldMatrix, viewMatrix, projMatrix, doBeginEndFrame);
	}

	
	Ogre::RenderQueue* Scene::getRenderQueue(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getRenderQueue();
	}

	
	void Scene::addRenderQueueListener(Ogre::RenderQueueListener* newListener)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->addRenderQueueListener(newListener);
	}

	
	void Scene::removeRenderQueueListener(Ogre::RenderQueueListener* delListener)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->removeRenderQueueListener(delListener);
	}

	
	void Scene::addSpecialCaseRenderQueue(Ogre::uint8 qid)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->addSpecialCaseRenderQueue(qid);
	}
	
	void Scene::removeSpecialCaseRenderQueue(Ogre::uint8 qid)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->removeSpecialCaseRenderQueue(qid);
	}
	
	void Scene::clearSpecialCaseRenderQueues(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->clearSpecialCaseRenderQueues();
	}
	
	void Scene::setSpecialCaseRenderQueueMode(Ogre::SceneManager::SpecialCaseRenderQueueMode mode)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setSpecialCaseRenderQueueMode(mode);
	}
	
	Ogre::SceneManager::SpecialCaseRenderQueueMode Scene::getSpecialCaseRenderQueueMode(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getSpecialCaseRenderQueueMode();
	}
	
	bool Scene::isRenderQueueToBeProcessed(Ogre::uint8 qid)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isRenderQueueToBeProcessed(qid);
	}

	void Scene::setWorldGeometryRenderQueue(Ogre::uint8 qid)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setWorldGeometryRenderQueue(qid);
	}

	Ogre::uint8 Scene::getWorldGeometryRenderQueue(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getWorldGeometryRenderQueue();
	}

	
	void Scene::showBoundingBoxes(bool bShow)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->showBoundingBoxes(bShow);
	}

	
	bool Scene::getShowBoundingBoxes() const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShowBoundingBoxes();
	}

	
	void Scene::_notifyAutotrackingSceneNode(Ogre::SceneNode* node, bool autoTrack)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_notifyAutotrackingSceneNode(node, autoTrack);
	}

    
	
	Ogre::AxisAlignedBoxSceneQuery* Scene::createAABBQuery(const Ogre::AxisAlignedBox& box, unsigned long mask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createAABBQuery(box, mask);
	}
	
	Ogre::SphereSceneQuery* Scene::createSphereQuery(const Ogre::Sphere& sphere, unsigned long mask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createSphereQuery(sphere, mask);
	}
	
	Ogre::PlaneBoundedVolumeListSceneQuery* Scene::createPlaneBoundedVolumeQuery(const Ogre::PlaneBoundedVolumeList& volumes, unsigned long mask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createPlaneBoundedVolumeQuery(volumes, mask);
	}


	
	Ogre::RaySceneQuery* Scene::createRayQuery(const Ogre::Ray& ray, unsigned long mask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createRayQuery(ray, mask);
	}

	
	Ogre::IntersectionSceneQuery* Scene::createIntersectionQuery(unsigned long mask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createIntersectionQuery(mask);
	}

	
	void Scene::destroyQuery(Ogre::SceneQuery* query)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyQuery(query);
	}

	Ogre::SceneManager::CameraIterator Scene::getCameraIterator(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getCameraIterator();
	}

	
	Ogre::SceneManager::AnimationIterator Scene::getAnimationIterator(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getAnimationIterator();
	}

	
	Ogre::AnimationStateIterator Scene::getAnimationStateIterator(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getAnimationStateIterator();
	}

	void Scene::setShadowTechnique(Ogre::ShadowTechnique technique)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTechnique(technique);
	}
    
	
	Ogre::ShadowTechnique Scene::getShadowTechnique(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowTechnique();
	}

	void Scene::setShowDebugShadows(bool debug)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShowDebugShadows(debug);
	}
	
	bool Scene::getShowDebugShadows(void ) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShowDebugShadows();
	}

	
	void Scene::setShadowColour(const Ogre::ColourValue& colour)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowColour(colour);
	}
	
	const Ogre::ColourValue& Scene::getShadowColour(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowColour();
	}
	
	void Scene::setShadowDirectionalLightExtrusionDistance(Ogre::Real dist)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowDirectionalLightExtrusionDistance(dist);
	}
	
	Ogre::Real Scene::getShadowDirectionalLightExtrusionDistance(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowDirectionalLightExtrusionDistance();
	}
	
	void Scene::setShadowFarDistance(Ogre::Real distance)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowFarDistance(distance);
	}
	
	Ogre::Real Scene::getShadowFarDistance(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowFarDistance();
	}

	void Scene::setShadowIndexBufferSize(size_t size)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowIndexBufferSize(size);
	}

	size_t Scene::getShadowIndexBufferSize(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowIndexBufferSize();
	}

	
	void Scene::setShadowTextureSize(unsigned short size)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureSize(size);
	}

	
	void Scene::setShadowTextureConfig(size_t shadowIndex, unsigned short width, 
		unsigned short height, Ogre::PixelFormat format)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureConfig(shadowIndex, width, height, format);
	}
	
	void Scene::setShadowTextureConfig(size_t shadowIndex, const Ogre::ShadowTextureConfig& config)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureConfig(shadowIndex, config);
	}

	
	Ogre::ConstShadowTextureConfigIterator Scene::getShadowTextureConfigIterator() const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowTextureConfigIterator();
	}

	
	void Scene::setShadowTexturePixelFormat(Ogre::PixelFormat fmt)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTexturePixelFormat(fmt);
	}
	
	void Scene::setShadowTextureCount(size_t count)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureCount(count);
	}

	size_t Scene::getShadowTextureCount(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowTextureCount();
	}

	
	void Scene::setShadowTextureSettings(unsigned short size, unsigned short count, Ogre::PixelFormat fmt)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureSettings(size, count, fmt);
	}

	
	const Ogre::TexturePtr& Scene::getShadowTexture(size_t shadowIndex)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowTexture(shadowIndex);
	}

	void Scene::setShadowDirLightTextureOffset(Ogre::Real offset)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowDirLightTextureOffset(offset);
	}

	
	Ogre::Real Scene::getShadowDirLightTextureOffset(void)  const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowDirLightTextureOffset();
	}

	
	void Scene::setShadowTextureFadeStart(Ogre::Real fadeStart)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureFadeStart(fadeStart);
	}

	
	void Scene::setShadowTextureFadeEnd(Ogre::Real fadeEnd)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureFadeEnd(fadeEnd);
	}

	
	void Scene::setShadowTextureSelfShadow(bool selfShadow)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureSelfShadow(selfShadow);
	}

	bool Scene::getShadowTextureSelfShadow(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowTextureSelfShadow();
	}

	
	void Scene::setShadowTextureCasterMaterial(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureCasterMaterial(name);
	}
	
	void Scene::setShadowTextureReceiverMaterial(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowTextureReceiverMaterial(name);
	}

	
	void Scene::setShadowCasterRenderBackFaces(bool bf)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowCasterRenderBackFaces(bf);
	}

	
	bool Scene::getShadowCasterRenderBackFaces() const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowCasterRenderBackFaces();
	}

	
	void Scene::setShadowCameraSetup(const Ogre::ShadowCameraSetupPtr& shadowSetup)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowCameraSetup(shadowSetup);
	}

	
	const Ogre::ShadowCameraSetupPtr& Scene::getShadowCameraSetup() const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowCameraSetup();
	}

	void Scene::setShadowUseInfiniteFarPlane(bool enable)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setShadowUseInfiniteFarPlane(enable);
	}

	
	bool Scene::isShadowTechniqueStencilBased(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueStencilBased();
	}
	
	bool Scene::isShadowTechniqueTextureBased(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueTextureBased();
	}
	
	bool Scene::isShadowTechniqueModulative(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueModulative();
	}
	
	bool Scene::isShadowTechniqueAdditive(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueAdditive();
	}
	
	bool Scene::isShadowTechniqueIntegrated(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueIntegrated();
	}
	
	bool Scene::isShadowTechniqueInUse(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->isShadowTechniqueInUse();
	}

	
	void Scene::addListener(Ogre::SceneManager::Listener* l)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->addListener(l);
	}
	
	void Scene::removeListener(Ogre::SceneManager::Listener* l)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->removeListener(l);
	}

	
	Ogre::StaticGeometry* Scene::createStaticGeometry(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createStaticGeometry(name);
	}
	
	Ogre::StaticGeometry* Scene::getStaticGeometry(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getStaticGeometry(name);
	}
	
	bool Scene::hasStaticGeometry(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasStaticGeometry(name);
	}
	
	void Scene::destroyStaticGeometry(Ogre::StaticGeometry* geom)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyStaticGeometry(geom);
	}
	
	void Scene::destroyStaticGeometry(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyStaticGeometry(name);
	}
	
	void Scene::destroyAllStaticGeometry(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllStaticGeometry();
	}

	
	Ogre::InstancedGeometry* Scene::createInstancedGeometry(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createInstancedGeometry(name);
	}
	
	Ogre::InstancedGeometry* Scene::getInstancedGeometry(const Ogre::String& name) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getInstancedGeometry(name);
	}
	
	void Scene::destroyInstancedGeometry(Ogre::InstancedGeometry* geom)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyInstancedGeometry(geom);
	}
	
	void Scene::destroyInstancedGeometry(const Ogre::String& name)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyInstancedGeometry(name);
	}
	
	void Scene::destroyAllInstancedGeometry(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllInstancedGeometry();
	}


	Ogre::MovableObject* Scene::createMovableObject(const Ogre::String& name, const Ogre::String& typeName, const Ogre::NameValuePairList* params)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->createMovableObject(name, typeName, params);
	}
	
	void Scene::destroyMovableObject(const Ogre::String& name, const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyMovableObject(name, typeName);
	}
	
	void Scene::destroyMovableObject(Ogre::MovableObject* m)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyMovableObject(m);
	}
	
	void Scene::destroyAllMovableObjectsByType(const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllMovableObjectsByType(typeName);
	}
	
	void Scene::destroyAllMovableObjects(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->destroyAllMovableObjects();
	}
	
	Ogre::MovableObject* Scene::getMovableObject(const Ogre::String& name, const Ogre::String& typeName) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getMovableObject(name, typeName);
	}
	
	bool Scene::hasMovableObject(const Ogre::String& name, const Ogre::String& typeName) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->hasMovableObject(name, typeName);
	}
	
	Ogre::SceneManager::MovableObjectIterator Scene::getMovableObjectIterator(const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getMovableObjectIterator(typeName);
	}
	
	void Scene::injectMovableObject(Ogre::MovableObject* m)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->injectMovableObject(m);
	}
	
	void Scene::extractMovableObject(const Ogre::String& name, const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->extractMovableObject(name, typeName);
	}
	
	void Scene::extractMovableObject(Ogre::MovableObject* m)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->extractMovableObject(m);
	}
	
	void Scene::extractAllMovableObjectsByType(const Ogre::String& typeName)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->extractAllMovableObjectsByType(typeName);
	}

	
	void Scene::setVisibilityMask(Ogre::uint32 vmask)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setVisibilityMask(vmask);
	}

	
	Ogre::uint32 Scene::getVisibilityMask(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getVisibilityMask();
	}

	
	Ogre::uint32 Scene::_getCombinedVisibilityMask(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->_getCombinedVisibilityMask();
	}

	
	void Scene::setFindVisibleObjects(bool find)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->setFindVisibleObjects(find);
	}

	
	bool Scene::getFindVisibleObjects(void)
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getFindVisibleObjects();
	}

	void Scene::_injectRenderWithPass(Ogre::Pass *pass, Ogre::Renderable *rend, bool shadowDerivation)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_injectRenderWithPass(pass, rend, shadowDerivation);
	}

	void Scene::_suppressRenderStateChanges(bool suppress)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_suppressRenderStateChanges(suppress);
	}
	
	
	bool Scene::_areRenderStateChangesSuppressed(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->_areRenderStateChangesSuppressed();
	}

	
	const Ogre::Pass* Scene::_setPass(const Ogre::Pass* pass, bool evenIfSuppressed, bool shadowDerivation)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		return sceneManager->_setPass(pass, evenIfSuppressed, shadowDerivation);
	}


	
	void Scene::_suppressShadows(bool suppress)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_suppressShadows(suppress);
	}

	
	bool Scene::_areShadowsSuppressed(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->_areShadowsSuppressed();
	}

	
	void Scene::_renderQueueGroupObjects(Ogre::RenderQueueGroup* group, Ogre::QueuedRenderableCollection::OrganisationMode om)
	{
		Poco::ScopedRWLock(rwLockSceneManager, true);

		sceneManager->_renderQueueGroupObjects(group, om);
	}

	
//	void Scene::setQueuedRenderableVisitor(SceneMgrQueuedRenderableVisitor* visitor)
//	{
//		Poco::ScopedRWLock(rwLockSceneManager, true);
//
//		sceneManager->setQueuedRenderableVisitor(visitor);
//	}
//
//	
//	SceneMgrQueuedRenderableVisitor* Scene::getQueuedRenderableVisitor(void) const
//	{
//		Poco::ScopedRWLock(rwLockSceneManager, false);
//
//		return sceneManager->getQueuedRenderableVisitor();
//	}


	
	Ogre::RenderSystem* Scene::getDestinationRenderSystem()
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getDestinationRenderSystem();
	}

	
	Ogre::Viewport* Scene::getCurrentViewport(void) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getCurrentViewport();
	}

	
	const Ogre::VisibleObjectsBoundsInfo& Scene::getVisibleObjectsBoundsInfo(const Ogre::Camera* cam) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getVisibleObjectsBoundsInfo(cam);
	}

	
	const Ogre::VisibleObjectsBoundsInfo& Scene::getShadowCasterBoundsInfo(const Ogre::Light* light) const
	{
		Poco::ScopedRWLock(rwLockSceneManager, false);

		return sceneManager->getShadowCasterBoundsInfo(light);
	}

	//********** END:  OGRE::SCENEMANAGER METHODS ***********//

	//********** NXOGRE::SCENE METHODS ************//

	NxScene*  Scene::getNxScene()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNxScene();
	}

	
	NxOgre::World*  Scene::getWorld()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getWorld();
	}


	void  Scene::setSceneController(NxOgre::SceneController* sceneController)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->setSceneController(sceneController);
	}

	void Scene::simulate(NxReal dt)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->simulate(dt);
	}

	void Scene::render(NxReal dt)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->render(dt);
	}

	//NxOgre::Blueprints::SceneBlueprint  Scene::save()
	//{
	//	Poco::ScopedRWLock lock(rwLock, false);

	//	return nxScene->save();
	//}

//	NxSimulationType Scene::getSimType() const
//	{
//		Poco::ScopedRWLock lock(rwLock, false);
//
//		return nxScene->getSimType();
//	}

	void  Scene::setGravity(const Ogre::Vector3& gravity)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->setGravity(gravity);
	}


	Ogre::Vector3  Scene::getGravity() const
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getGravity();
	}


	NxOgre::Actor*  Scene::createActor(const NxOgre::NxString& identifier, NxOgre::ShapeBlueprint* shape, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createActor(identifier, shape, pose, actorParams);
	}

	void  Scene::batchCreateActors(const NxOgre::NxString& identifierPattern, NxU32 nbActors, NxOgre::ShapeBlueprint* shape, const NxOgre::Pose& poseOrigin, const NxOgre::Pose& poseDifference, NxOgre::Scene::BatchActionTimeFrame batchActionTimeFrame, NxOgre::ActorParams actorParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->batchCreateActors(identifierPattern, nbActors, shape, poseOrigin, poseDifference, batchActionTimeFrame, actorParams);
	}


	void  Scene::destroyActor(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyActor(identifier);
	}

	void  Scene::batchDestroyActor(const NxOgre::NxString& identifier, NxOgre::Scene::BatchActionTimeFrame timeFrame)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->batchDestroyActor(identifier, timeFrame);
	}
	
	//void  Scene::batchDestroyActors(const NxOgre::NxString& identifierPattern, NxU32 nbActors, NxOgre::Scene::BatchActionTimeFrame timeFrame)
	//{
	//	Poco::ScopedRWLock(rwLockNxScene, true);

	//	nxScene->batchDestroyActors(identifierPattern, nbActors, timeFrame);
	//}
	
	void  Scene::batchDestroyActors(NxOgre::Actors actors, NxOgre::Scene::BatchActionTimeFrame timeFrame)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->batchDestroyActors(actors, timeFrame);
	}

	NxOgre::Actor*  Scene::getActor(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->getActor(name);
	}
	
	NxOgre::Actors*  Scene::getActors()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActors();
	}

	NxOgre::Actors  Scene::getActorsFromIdentifier(NxOgre::NxStringOperator stringOperator, const NxOgre::NxString& identifierPattern)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->getActorsFromIdentifier(stringOperator, identifierPattern);
	}
	
	NxOgre::Actors  Scene::getActorsFromFrame(NxOgre::NxComparisonOperator comparisonOperator, NxU32 frame)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorsFromFrame(comparisonOperator, frame);
	}

	NxOgre::Actors&  Scene::getActorsFromRegion(NxOgre::SimpleShape* shape, NxShapesType type)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorsFromRegion(shape, type);
	}
	
	NxOgre::Actors&  Scene::getActorsFromLastRegion(NxShapesType type)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorsFromLastRegion(type);
	}

	NxOgre::Actors  Scene::getActorsFromRaycast(Ogre::Vector3 position, Ogre::Vector3 normal, NxReal range)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorsFromRaycast(position, normal, range);
	}

	NxU32  Scene::getNbActors() const
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbActors();
	}

	NxOgre::Body*  Scene::createBody(const NxOgre::NxString& meshIdentifier, NxOgre::ShapeBlueprint* shape, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createBody(meshIdentifier, shape, pose, actorParams);
	}
	
	void  Scene::batchCreateBodies(const NxOgre::NxString& identifierPattern, const NxOgre::NxString& visualData, NxU32 nbActors, NxOgre::ShapeBlueprint* shape, const NxOgre::Pose& poseOrigin, const NxOgre::Pose& poseDifference, NxOgre::Scene::BatchActionTimeFrame timeFrame, NxOgre::ActorParams actorParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->batchCreateBodies(identifierPattern, visualData, nbActors, shape, poseOrigin, poseDifference, timeFrame, actorParams);
	}
	
	void  Scene::destroyBody(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyBody(name);
	}
		
	NxOgre::Trigger*  Scene::createTrigger(const NxOgre::NxString& identifier, NxOgre::ShapeBlueprint* shape, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createTrigger(identifier, shape, pose, actorParams);
	}

	void  Scene::destroyTrigger(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyTrigger(name);
	}

	NxOgre::Trigger* Scene::getTrigger(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxScene->getTrigger(name);
	}

	NxOgre::Triggers* Scene::getTriggers()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxScene->getTriggers();
	}

	NxU32  Scene::getNbTriggers()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbTriggers();
	}

	NxOgre::SphericalJoint*  Scene::createSphericalJoint(NxOgre::Actor* actor, NxOgre::Actor* actor2, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createSphericalJoint(actor, actor2, anchor, jointParams);
	}


	
	NxOgre::SphericalJoint*  Scene::createSphericalJoint(NxOgre::Actor* actor, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createSphericalJoint(actor, anchor, jointParams);
	}


	
	NxOgre::RevoluteJoint*  Scene::createRevoluteJoint(NxOgre::Actor* actor, NxOgre::Actor* actor2, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createRevoluteJoint(actor, actor2, axis, anchor, jointParams);
	}


	
	NxOgre::RevoluteJoint*  Scene::createRevoluteJoint(NxOgre::Actor* actor, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createRevoluteJoint(actor, axis, anchor, jointParams);
	}


	
	NxOgre::PrismaticJoint*  Scene::createPrismaticJoint(NxOgre::Actor* actor, NxOgre::Actor* actor2, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createPrismaticJoint(actor, actor2, axis, anchor, jointParams);
	}
	
	
	
	NxOgre::PrismaticJoint*  Scene::createPrismaticJoint(NxOgre::Actor* actor, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createPrismaticJoint(actor, axis, anchor, jointParams);
	}


	
	NxOgre::CylindricalJoint*  Scene::createCylindricalJoint(NxOgre::Actor* actor, NxOgre::Actor* actor2, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createCylindricalJoint(actor, actor2, axis, anchor, jointParams);
	}


	
	NxOgre::CylindricalJoint*  Scene::createCylindricalJoint(NxOgre::Actor* actor, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createCylindricalJoint(actor, axis, anchor, jointParams);
	}


	
	NxOgre::FixedJoint*  Scene::createFixedJoint(NxOgre::Actor* actor, NxOgre::Actor* actor2, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createFixedJoint(actor, actor2, jointParams);
	}


	
	NxOgre::FixedJoint*  Scene::createFixedJoint(NxOgre::Actor* actor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createFixedJoint(actor, jointParams);
	}


	
	void Scene::releaseJoint(NxOgre::Joint* joint)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->releaseJoint(joint);
	}

	
	void Scene::releaseJoint(NxOgre::NxJointID id)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->releaseJoint(id);
	}

#if (NX_USE_CHARACTER_API == 1)
	
	NxOgre::Character*  Scene::createCharacter(const NxOgre::NxString &identifier, NxOgre::Pose pose, NxOgre::CharacterParams params)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createCharacter(identifier, pose, params);
	}

	void  Scene::destroyCharacter(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyCharacter(identifier);
	}
#endif

	
	NxOgre::Material*  Scene::createMaterial(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createMaterial(identifier);
	}

	
	void  Scene::destroyMaterial(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->destroyMaterial(identifier);
	}

	
	NxOgre::Material*  Scene::getMaterial(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getMaterial(identifier);
	}

	
	NxOgre::Material*  Scene::getMaterial(NxMaterialIndex index)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getMaterial(index);
	}

	
	NxOgre::MaterialList*  Scene::getMaterials()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getMaterials();
	}

	
	NxU32  Scene::getNbMaterials()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbMaterials();
	}

	
	NxMaterialIndex  Scene::getMaterialIndex(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getMaterialIndex(identifier);
	}

	
	//void  Scene::addMaterialPair(Ogre::Material* material, NxOgre::Material* material2)
	//{
	//	Poco::ScopedRWLock(rwLockNxScene, true);

	//	nxScene->addMaterialPair(material, material2);
	//}

	//
	//void  Scene::addMaterialPair(const NxOgre::NxString& ogre, const NxOgre::NxString& nxogre)
	//{
	//	Poco::ScopedRWLock(rwLockNxScene, true);

	//	nxScene->addMaterialPair(ogre, nxogre);
	//}

	//
	//void  Scene::addMaterialPairsFromFile(const NxOgre::NxString& ogre, const NxOgre::NxString& nxogre)
	//{
	//	Poco::ScopedRWLock(rwLockNxScene, true);

	//	nxScene->addMaterialPairsFromFile(ogre, nxogre);
	//}

	NxOgre::ActorGroup*  Scene::createActorGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createActorGroup(name);
	}

	
	void  Scene::destroyActorGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyActorGroup(name);
	}

	
	NxU32  Scene::getNbActorGroups() const
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbActorGroups();
	}

	
	NxOgre::ActorGroups*  Scene::getActorGroups()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorGroups();
	}

	
	NxOgre::ActorGroupsByIndex*  Scene::getActorGroupsByIndex()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorGroupsByIndex();
	}

	
	NxOgre::ActorGroup*  Scene::getActorGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getActorGroup(name);
	}

	
	NxOgre::ShapeGroup*  Scene::createShapeGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createShapeGroup(name);
	}

	
	void  Scene::destroyShapeGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyShapeGroup(name);
	}

	NxU32  Scene::getNbShapeGroups() const
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbShapeGroups();
	}

	NxOgre::ShapeGroups*  Scene::getShapeGroups()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getShapeGroups();
	}

	NxOgre::ShapeGroupsByIndex*  Scene::getShapeGroupsByIndex()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getShapeGroupsByIndex();
	}

	NxOgre::ShapeGroup*  Scene::getShapeGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getShapeGroup(name);
	}

#if (NX_SDK_VERSION_NUMBER >= 272) 

	NxOgre::DominanceGroup*  Scene::createDominanceGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->createDominanceGroup(name);
	}

	void  Scene::setDominanceGroupPair(const NxOgre::NxString& AGroup, const NxOgre::NxString& BGroup, NxReal ADominance, NxReal BDominance)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->setDominanceGroupPair(AGroup, BGroup, ADominance, BDominance);
	}

	void  Scene::setDominanceGroupPair(NxOgre::DominanceGroup* AGroup, NxOgre::DominanceGroup* BGroup, NxReal ADominance, NxReal BDominance)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->setDominanceGroupPair(AGroup, BGroup, ADominance, BDominance);
	}

	
	void  Scene::destroyDominanceGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyDominanceGroup(name);
	}

	
	NxU32  Scene::getNbDominanceGroups() const
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbDominanceGroups();
	}

	
	NxOgre::DominanceGroups*  Scene::getDominanceGroups()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getDominanceGroups();
	}

	
	NxOgre::DominanceGroupsByIndex*  Scene::getDominanceGroupsByIndex()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getDominanceGroupsByIndex();
	}

	
	NxOgre::DominanceGroup*  Scene::getDominanceGroup(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getDominanceGroup(name);
	}

#endif

	
	void  Scene::addFloor()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		nxScene->addFloor();
	}

	void  Scene::addFloor(float y)
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		nxScene->createActor("Ground", new NxOgre::GroundShape(), Ogre::Vector3(0, y, 0), "static:yes");
	}

	void Scene::setStaticGeometry(Ogre::StaticGeometry* geom)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->setStaticGeometry(geom);
	}

	Ogre::StaticGeometry* Scene::getStaticGeometry()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxScene->getStaticGeometry();
	}

	void Scene::removeStaticGeometry()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->removeStaticGeometry();
	}

#if (NX_USE_FLUID_API == 1)

	//NxOgre::Fluid*	createFluid(const NxOgre::Pose& pose, NxOgre::FluidParams fluidParams)
	//{
	//	Poco::ScopedRWLock lock(rwLock, true);

	//	return nxScene->createFluid(pose, fluidParams);
	//}

	//void	destroyFluid(const NxOgre::NxString& name)
	//{
	//	Poco::ScopedRWLock lock(rwLock, true);

	//	nxScene->destroyFluid(name);
	//}

	//NxU32	getNbFluids()	const
	//{
	//	Poco::ScopedRWLock lock(rwLock, false);

	//	return nxScene->getNbFluids();
	//}

	//NxOgre::Fluids*	getFluids()
	//{
	//	Poco::ScopedRWLock lock(rwLock, false);

	//	return nxScene->getFluids();
	//}

#endif

#if (NX_USE_CLOTH_API == 1)

	
	NxOgre::Actor*  Scene::createDeformableActor(const NxOgre::NxString& meshName, NxOgre::ShapeBlueprint* roughShape, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams, NxOgre::ClothParams clothParams, NxReal impulseThreshold, NxReal penetrationDepth)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createDeformableActor(meshName, roughShape, pose, actorParams, clothParams, impulseThreshold, penetrationDepth);
	}

	
	NxOgre::Cloth*  Scene::createCloth(const NxOgre::NxString& identifier, const NxOgre::Pose& pose, NxOgre::ClothParams clothParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createCloth(identifier, pose, clothParams);
	}

	
	NxOgre::Cloth*  Scene::createCloth(const NxOgre::NxString& identifier, const NxOgre::NxString& meshName, const NxOgre::Pose& pose, NxOgre::ClothParams clothParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createCloth(identifier, meshName, pose, clothParams);
	}

	void  Scene::destroyCloth(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyCloth(name);
	}

	
	NxOgre::Cloths*  Scene::getCloths()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getCloths();
	}

	
	NxU32  Scene::getNbCloths()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbCloths();
	}

#endif

#if (NX_USE_SOFTBODY_API == 1)

	
	NxOgre::SoftBody*  Scene::createSoftBody(const NxOgre::NxString& TetAndMeshFilePrefix, const NxOgre::Pose& pose, NxOgre::SoftBodyParams softBodyParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createSoftBody(TetAndMeshFilePrefix, pose, softBodyParams);
	}

	
	NxOgre::SoftBody*  Scene::createSoftBody(NxReal width, NxReal height, NxReal r, const NxOgre::Pose& pose, NxOgre::SoftBodyParams softBodyParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createSoftBody(width, height, r, pose, softBodyParams);
	}

	
	void  Scene::destroySoftBody(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroySoftBody(identifier);
	}

	
	NxU32  Scene::getNbSoftBodies()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbSoftBodies();
	}

	
	NxOgre::SoftBodies*  Scene::getSoftBodies()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getSoftBodies();
	}
#endif


#if (NX_USE_FORCEFIELD_API == 1)

	
	NxOgre::ForceField*  Scene::createForceField(const NxOgre::NxString& identifier, const NxOgre::Pose& pose, NxOgre::ShapeBlueprint* actorShape, NxOgre::ActorParams actorParams, NxOgre::ForceFieldParams forceFieldParams)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		return nxScene->createForceField(identifier, pose, actorShape, actorParams, forceFieldParams);
	}

	
	void  Scene::destroyForceField(const NxOgre::NxString& identifier)
	{
		Poco::ScopedRWLock(rwLockNxScene, true);

		nxScene->destroyForceField(identifier);
	}

	
	NxU32  Scene::getNbForceFields()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getNbForceFields();
	}

	
	NxOgre::ForceFields*  Scene::getForceFields()
	{
		Poco::ScopedRWLock(rwLockNxScene, false);

		return nxScene->getForceFields();
	}
#endif

	
	void		Scene::_registerHelper(const NxOgre::NxString& name, NxOgre::Helper* helper)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->_registerHelper(name, helper);
	}

	void		Scene::_unregisterHelper(const NxOgre::NxString& name)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxScene->_unregisterHelper(name);
	}

	void		Scene::idle()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		nxScene->idle();
	}

	//********** END:  NXOGRE::SCENE METHODS ************//

} // Myoushu
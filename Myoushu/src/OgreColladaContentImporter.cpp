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
 * @file OgreColladaContentImporter.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "GlobalLocks.h"
#include "OgreColladaContentImporter.h"
#include "GameObjectFactory.h"
#include "EngineLog.h"

namespace Myoushu
{
	OgreColladaContentImporter::OgreColladaContentImporter(Scene *scene) : ContentImporter(scene)
	{
		GlobalLocks::rwLockOgreRoot.readLock();

		ogreColladaImporter = OgreCollada::CreateImpExp(Ogre::Root::getSingletonPtr(), scene->getOgreSceneManager());
		ogreColladaImporter->setResourceNotificationListener(this);

		GlobalLocks::rwLockOgreRoot.unlock();
	}

	OgreColladaContentImporter::~OgreColladaContentImporter()
	{
		if (ogreColladaImporter)
		{
			delete ogreColladaImporter;
			ogreColladaImporter = NULL;
		}
	}

	void OgreColladaContentImporter::importContent(const std::string& path) throw (Exception)
	{
		// Check that scene is not null
		if (scene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "OgreColladaContentImporter::importContent(): scene is NULL!");
		}

		// Clear the lists of previously loaded scene nodes, entities etc.
		clearLists();

		Poco::ScopedRWLock lock(rwLock, true);

		ogreColladaImporter->setSceneManager(scene->getOgreSceneManager());

		if (!ogreColladaImporter->importCollada(path.c_str()))
		{
			throw Exception(Exception::E_FILE_NOT_FOUND, "OgreColladaContentImporter::importContent(): path is invalid.");
		}
	}

	void OgreColladaContentImporter::clearLists()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		sceneNodes.clear();
		entities.clear();
		cameras.clear();
		lights.clear();
		resources.clear();
	}

	void OgreColladaContentImporter::sceneNodeCreated(Ogre::SceneNode* pNode, FCDSceneNode* pFColladaSceneNode)
	{
		NxOgre::ActorParams actorParams;
		NxOgre::ShapeParams shapeParams;
		Ogre::Vector3 boxSize;
		Ogre::Vector3 scale;
		Ogre::Entity *pEntity;
		std::list<Ogre::Entity*> entityList;
		std::list<Ogre::Entity*>::iterator entityListIter;
		NxVec3 row;

		pEntity = NULL;
		Ogre::SceneNode::ObjectIterator  iter = pNode->getAttachedObjectIterator();

		while (iter.hasMoreElements())
		{
			pEntity = dynamic_cast<Ogre::Entity*>(iter.getNext());

			if (pEntity != NULL)
			{
				entityList.push_back(pEntity);
			}
		}

		shapeParams.setToDefault();
		//scale = pNode->_getDerivedScale();
		//shapeParams.mMeshScale = NxVec3(scale.x, scale.y, scale.z);
		for (entityListIter = entityList.begin(); entityListIter != entityList.end(); ++entityListIter)
		{

			pEntity = *entityListIter;
			boxSize = pEntity->getBoundingBox().getSize();

			pNode->detachObject(pEntity);
			actorParams.setToDefault();
			actorParams.mMass = 0.0f;
			actorParams.mBodyFlags |= NX_BF_KINEMATIC;

			GameObjectFactory::getSingleton().makeBody(pEntity->getName(), pNode, pEntity, scene
				,new NxOgre::CubeShape(boxSize.x, boxSize.y, boxSize.z, shapeParams), actorParams);
		}

		sceneNodes.push_back(pNode);
	}

	void OgreColladaContentImporter::entityCreated(Ogre::Entity* pEntity, FCDSceneNode* pFColladaParentNode)
	{
		// Apparently setNormaliseNormals is now automatic and default (Ogre 1.6)
		// pEntity->setNormaliseNormals(true);
		entities.push_back(pEntity);
	}

	void OgreColladaContentImporter::cameraCreated(Ogre::Camera* pCam, FCDCamera* pFColladaCamera)
	{
		cameras.push_back(pCam);
	}

	void OgreColladaContentImporter::lightCreated(Ogre::Light* pLight, FCDLight* pFColladaLight)
	{
		lights.push_back(pLight);
	}

	void OgreColladaContentImporter::resourceCreated(Ogre::Resource* pResource, FCDEntity* pFColladaObject)
	{
		resources.push_back(pResource);
	}

	void OgreColladaContentImporter::getDefaultTexture(Ogre::Image& rImage)
	{
	}

} //namespace Myoushu
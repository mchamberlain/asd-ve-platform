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
 * @file MyoushuDotSceneEntityElementProcessor.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "NxOgre.h"
#include "Ogre.h"

#include "Scene.h"
#include "GameObjectFactory.h"

#include "MyoushuDotSceneEntityElementProcessor.h"
#include "MyoushuDotSceneUserDataElementProcessor.h"
#include "EngineLog.h"

namespace Myoushu
{
	MyoushuDotSceneEntityElementProcessor::MyoushuDotSceneEntityElementProcessor() : mpEntity(NULL)
	{
	}

	MyoushuDotSceneEntityElementProcessor::~MyoushuDotSceneEntityElementProcessor()
	{
	}
	
	void* MyoushuDotSceneEntityElementProcessor::parseElementImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode)
	{
		// Clear the key value properties
		// The entity element is the parent of the userData element. We have to clear the userData that
		// was parsed for the previous entity, otherwise if there are no userData in this entity element
		// it could reuse the data from the previous element, which would be wrong
		// Get the key value properties passed through user data
		KeyValueProperties &keyValueProperties = static_cast<MyoushuDotSceneUserDataElementProcessor*>(getElementProcessor("userData"))->getKeyValueProperties();
		keyValueProperties.clear();

		mpEntity = reinterpret_cast<Ogre::Entity*>(Ogre::EntityElementProcessor::parseElementImpl(parent, currentNode));

		return mpEntity;
	}

	NxOgre::ShapeBlueprint* MyoushuDotSceneEntityElementProcessor::createCollisionShape(const KeyValueProperties* pKeyValProps, const Ogre::Vector3& boundingBoxSize, const NxOgre::ShapeParams& shapeParams)
	{
		NxOgre::ShapeBlueprint *pCollisionShape;
		Ogre::Vector3 scale;
		std::string collisionShapeProperty;
		const Value *pVal;

		// Get the collisionShape key value. If the key does not exist, default it to "cube"
		pVal = pKeyValProps->get("collisionShape");
		if (pVal != NULL)
		{
			collisionShapeProperty = pVal->getString();
		}
		else
		{
			collisionShapeProperty = "cube";
		}

		// Check which type of shape should be used for collision geometry
		if (collisionShapeProperty == "sphere")
		{
			// Check if a radius is specified
			pVal = pKeyValProps->get("collisionSphereRadius");
			if (pVal != NULL)
			{
				pVal->get(scale.x);
			}
			else
			{
				// Make the radius half the largest of the dimensions of the bounding box
				if ((boundingBoxSize.x >= boundingBoxSize.y) && (boundingBoxSize.y >= boundingBoxSize.z))
				{
					scale.x = boundingBoxSize.x / 2;
				}
				else if ((boundingBoxSize.y >= boundingBoxSize.x) && (boundingBoxSize.x >= boundingBoxSize.z))
				{
					scale.x = boundingBoxSize.y / 2;
				}
				else
				{
					scale.x = boundingBoxSize.z / 2;
				}
			}

			pCollisionShape = new NxOgre::SphereShape(scale.x, shapeParams);
		}
		else if (collisionShapeProperty == "capsule")
		{
			// Check if a radius is specified
			pVal = pKeyValProps->get("collisionCapsuleRadius");
			if (pVal != NULL)
			{
				pVal->get(scale.x);
			}
			else
			{
				// Make the radius the largest among the bounding box size in the x and z directions
				if (boundingBoxSize.x >= boundingBoxSize.z)
				{
					scale.x = boundingBoxSize.x;
				}
				else
				{
					scale.x = boundingBoxSize.z;
				}
			}

			// Check if a height is specified
			pVal = pKeyValProps->get("collisionCapsuleHeight");
			if (pVal != NULL)
			{
				pVal->get(scale.y);
			}
			else
			{
				// Make the height the bounding box size in the y direction
				scale.y = boundingBoxSize.y;
			}

			pCollisionShape = new NxOgre::CapsuleShape(scale.x, scale.y, shapeParams);
		}
		else if (collisionShapeProperty == "convex")
		{
			Ogre::FileInfoListPtr pFileInfoList;
			Ogre::FileInfoList::const_iterator fileInfoIter;
			std::string convexShapeFile;
			bool found;

			// Check if a height is specified
			pVal = pKeyValProps->get("collisionConvexFile");
			if (pVal != NULL)
			{
				convexShapeFile = pVal->getString();

				// Get the full path for the specified collision shape file from Ogre's resource management system
				found = false;
				pFileInfoList = Ogre::ResourceGroupManager::getSingleton().findResourceFileInfo(Constants::RG_COLLISION_MESH, convexShapeFile, false);
				if (!pFileInfoList.isNull())
				{
					for (fileInfoIter = pFileInfoList->begin(); ((!found) && (fileInfoIter != pFileInfoList->end())); ++fileInfoIter)
					{
						const Ogre::FileInfo& fileInfo = *fileInfoIter;

						if ((fileInfo.filename == convexShapeFile) && (fileInfo.archive != NULL))
						{
							found = true;
							convexShapeFile = fileInfo.archive->getName() + "\\" + fileInfo.path + fileInfo.filename;
						}
					}
				}
			}

			// If we found the file in the resource manager
			if (found)
			{
				pCollisionShape = new NxOgre::ConvexShape(convexShapeFile, shapeParams);
			}
		}

		if ((collisionShapeProperty == "cube") || (pCollisionShape == NULL)) // Default to cube
		{
			// Check if a scale is specified
			pVal = pKeyValProps->get("collisionCubeScaleX");
			if (pVal != NULL)
			{
				pVal->get(scale.x);
			}
			else
			{
				scale.x = boundingBoxSize.x;
			}
			pVal = pKeyValProps->get("collisionCubeScaleY");
			if (pVal != NULL)
			{
				pVal->get(scale.y);
			}
			else
			{
				scale.y = boundingBoxSize.y;
			}
			pVal = pKeyValProps->get("collisionCubeScaleZ");
			if (pVal != NULL)
			{
				pVal->get(scale.z);
			}
			else
			{
				scale.z = boundingBoxSize.z;
			}

			pCollisionShape = new NxOgre::CubeShape(scale.x, scale.y, scale.z, shapeParams);
		}

		return pCollisionShape;
	}

	void MyoushuDotSceneEntityElementProcessor::parseElementEndImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode)
	{
		NxOgre::ActorParams actorParams;
		NxOgre::ShapeParams shapeParams;
		NxOgre::ShapeBlueprint *pCollisionShape;
		Ogre::Vector3 boxSize;
		Ogre::Vector3 scale;
		Ogre::Entity *pEntity;
		Ogre::SceneNode *pSceneNode;
		Scene *pScene;
		KeyValueProperties::KeyValueMapIterator iter;
		Value *pVal;
		GameBodyObject *pGameObject;

		pCollisionShape = NULL;

		pEntity = mpEntity;

		if (pEntity == NULL)
		{
			return;
		}

		// Get the key value properties passed through user data
		KeyValueProperties &keyValueProperties = static_cast<MyoushuDotSceneUserDataElementProcessor*>(getElementProcessor("userData"))->getKeyValueProperties();

		// Create a GameObject for the Ogre::Entity that was loaded from the .scene file
		pSceneNode = static_cast<Ogre::SceneNode*>(parent->getParsedNode());
		shapeParams.setToDefault();

		actorParams.setToDefault();
		// set up some actor parameters from user data
		// mass
		pVal = keyValueProperties.get("mass");
		if (pVal != NULL)
		{
			pVal->get(actorParams.mMass);
		}
		else
		{
			actorParams.mMass = 0.0f;
		}
		// flag indicating if the object is kinematic
		pVal = keyValueProperties.get("kinematic");
		if ((pVal != NULL) && (pVal->getValue().mUChar != 0))
		{
			actorParams.mBodyFlags |= NX_BF_KINEMATIC;
		}

		boxSize = pEntity->getBoundingBox().getSize();

		// Get the Myoushu::Scene that we should load objects into, from the common properties
		pScene = reinterpret_cast<Scene*>(mTreeBuilder->getCommonParameter("Scene"));
		if (pSceneNode != NULL)
		{
			const Ogre::Vector3& scale = pSceneNode->getScale();

			boxSize.x *= scale.x;
			boxSize.y *= scale.y;
			boxSize.z *= scale.z;

			// Get the collision shape
			pCollisionShape = createCollisionShape(&keyValueProperties, boxSize, shapeParams);

			actorParams.mNodeName = pSceneNode->getName();

			pGameObject = GameObjectFactory::getSingleton().makeBody(pEntity->getName(), pSceneNode, pEntity, pScene, pCollisionShape, actorParams);
		}
		else
		{
			// Get the collision shape
			pCollisionShape = createCollisionShape(&keyValueProperties, boxSize, shapeParams);
			pGameObject = GameObjectFactory::getSingleton().makeBody(pEntity->getName(), pEntity, pScene, pCollisionShape, NxOgre::Pose(), actorParams);
		}

		// Check whether the collisionResponse property is specified
		pVal = keyValueProperties.get("collisionResponse");
		if ((pVal != NULL) && (pVal->getValue().mUChar == 0))
		{
			// If the collisionResponse property is false we disable collision response for this body
			pGameObject->disableCollisionResponse();
		}

		// Copy the user data from keyValueProperties into the internal KeyValueProperties instance of pGameObject
		for (iter = keyValueProperties.getBeginIterator(); iter != keyValueProperties.getEndIterator(); ++iter)
		{
			pGameObject->getProperties().insert(iter->first, new Value(*(iter->second)));
		}
	}

} // namespace Myoushu


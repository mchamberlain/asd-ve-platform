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
 * @file MyoushuDotSceneEntityElementProcessor.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_DOTSCENE_ENTITY_ELEMENT_PROCESSOR_H
#define MYOUSHU_DOTSCENE_ENTITY_ELEMENT_PROCESSOR_H

#include "dotSceneXmlNodeProcessors.h"

#include "KeyValueProperties.h"

#include "MyoushuDotScenePlatform.h"

namespace Myoushu
{
	/**
	 * This class is an extension of Ogre::dsi::EntityElementProcessor. The Ogre::dsi::EntityElementProcessor processes
	 * an Ogre::Entity from a .scene file and adds it so a scene. This extension ensures that a corresponding Myoushu::GameObject
	 * is created to encapsulate the Ogre::Entity.
	 */
	class MYOUSHU_DOTSCENE_API MyoushuDotSceneEntityElementProcessor : public Ogre::EntityElementProcessor
	{
		public:
			/** Nullary constructor. */
			MyoushuDotSceneEntityElementProcessor();

			/** Destructor. */
			virtual ~MyoushuDotSceneEntityElementProcessor();

			/** Parse an Ogre::Entity from the XML based .scene file. */
			virtual void* parseElementImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode);

			/** Parse an Ogre::Entity from the XML based .scene file. */
			virtual void parseElementEndImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode);

		protected:
			/** Entity parsed with the last call to parseElementImpl */
			Ogre::Entity *mpEntity;

			/** 
			 * Creates an NxOgre::ShapeBlueprint collision shape based on the specified properties and bounding box size.
			 * The key-value properties must include an entry "collisionShape" that is one of (cube, sphere, capsule, convex).
			 * The key-value properties can then contain additional keys that describe the properties of the collision shape,
			 * such as collisionCubeScale{X,Y,Z}, collisionSphereRadius etc.
			 * @param collisionShapeProperty The value of the "collisionShape" key in the key-value map.
			 * @param keyValProps The key-value properties of the object to create a collision shape for.
			 * @param pSceneNode Pointer to the Ogre::SceneNode that will contain the entity with this collisionshape.
			 * @param pEntity The entity for which the collision shape is being created.
			 * @param boundingBoxSize The size of the bouding box of the entity.
			 * @param shapeParams An NxOgre::ShapeParams instance for any extra parameters that should be applied
			 *					  to the shape when it is created.
			 */
			NxOgre::ShapeBlueprint* createCollisionShape(const KeyValueProperties* pKeyValProps, const Ogre::SceneNode* pSceneNode, const Ogre::Entity *pEntity, const Ogre::Vector3& boundingBoxSize, const NxOgre::ShapeParams& shapeParams = NxOgre::ShapeParams());
	};
} // namespace Myoushu

#endif


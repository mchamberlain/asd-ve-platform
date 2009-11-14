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
 * @file GameBodyObject.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "GameBodyObject.h"

namespace Myoushu
{
	CLASS_NAME(GameBodyObject, "Myoushu::GameBodyObject");

	GameBodyObject::GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Scene* scene) throw (Exception)
		: GameActorObject(name, scene, NULL)
	{
		createBody(meshName);
	}

	GameBodyObject::GameBodyObject(const Ogre::String& name, Ogre::Entity *entity, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, const NxOgre::Pose& pose, NxOgre::ActorParams params) throw (Exception)
		: GameActorObject(name, scene, firstShapeDescription, pose, params)
	{

		// Get the scene node for the actor, if it exists. Otherwise create one.
		if (params.mNodeName.length() == 0) 
		{
			mNode = mOwner->getSceneManager()->createSceneNode();
		}
		else if (!mOwner->getSceneManager()->hasSceneNode(params.mNodeName)) 
		{
			mNode = mOwner->getSceneManager()->createSceneNode(params.mNodeName);
		}

		mEntity = entity;
		mNode->attachObject(mEntity);

		if (params.mNodeScale != Ogre::Vector3(1,1,1)) 
		{
			mNode->scale(params.mNodeScale);
		}

		// Set the position and orientation of the node
		if (mNode)
		{
			mNode->setPosition(pose);
			mNode->setOrientation(pose);
		}

		// Add the scene node to the scene if it is not already in the scene.
		if (mNode->getParent() == NULL)
		{
			mOwner->getSceneManager()->getRootSceneNode()->addChild(mNode);
		}

		// Update the previous position and orientation of this body. This is
		// used to update the actor in case the scene node of this object is moved
		// by something other than physics reactions.
		prevGlobalPosition = mNode->_getDerivedPosition();
		prevGlobalOrientation = mNode->_getDerivedOrientation();
	}

	GameBodyObject::GameBodyObject(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, NxOgre::ActorParams params) throw (Exception)
		: GameActorObject(name, scene, firstShapeDescription, NxOgre::Pose(sceneNode->_getDerivedPosition(), sceneNode->_getDerivedOrientation()), params)
	{
		if ((sceneNode == NULL) || (entity == NULL))
		{
			throw Exception(Exception::E_NULL_POINTER, "Body::Body(): sceneNode or entity is NULL.");
		}

		// Set the scene node and entity for this body.
		mNode = sceneNode;
		mEntity = entity;
		// Attach the entity to the scene node
		// First we have to check that the entity is not already attached to some scene node, if it is we detach it first
		if (mEntity->getParentSceneNode() != NULL)
		{
			mEntity->detatchFromParent();
		}
		mNode->attachObject(mEntity);

		// Update the previous position and orientation of this body. This is
		// used to update the actor in case the scene node of this object is moved
		// by something other than physics reactions.
		prevGlobalPosition = mNode->_getDerivedPosition();
		prevGlobalOrientation = mNode->_getDerivedOrientation();
	}

	GameBodyObject::GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, NxOgre::ActorParams params) throw (Exception)
		: GameActorObject(name, scene, firstShapeDescription, NxOgre::Pose(sceneNode->getPosition(), sceneNode->getOrientation()), params)
	{
		if (sceneNode == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Body::Body(): sceneNode is NULL.");
		}

		// Set the scene node
		mNode = sceneNode;

		// If the node is not yet in the scene, add it to the scene.
		if (mNode->getParent() == NULL)
		{
			mOwner->getSceneManager()->getRootSceneNode()->addChild(mNode);
		}

		// Create the entity for this body.
		mEntity = mOwner->getSceneManager()->createEntity(name, meshName);
		mEntity->setCastShadows(params.mNodeShadows);

		// Attach the entity to the scene node.
		mNode->attachObject(mEntity);

		// Update the previous position and orientation of this body. This is
		// used to update the actor in case the scene node of this object is moved
		// by something other than physics reactions.
		prevGlobalPosition = mNode->_getDerivedPosition();
		prevGlobalOrientation = mNode->_getDerivedOrientation();
	}

	GameBodyObject::GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Scene* scene, NxOgre::ShapeBlueprint* blueprint, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams) throw (Exception)
		: GameActorObject(name, scene, blueprint, pose, actorParams)
	{
		// Check if an exisiting node was specified. If one was specified use it,
		// if not create a new one.
		if (actorParams.mNodeName.length() == 0) 
		{
			mNode = mOwner->getSceneManager()->createSceneNode();
		}
		else if (!mOwner->getSceneManager()->hasSceneNode(actorParams.mNodeName)) 
		{
			mNode = mOwner->getSceneManager()->createSceneNode(actorParams.mNodeName);
		}

		// Create the entity for this body.
		mEntity = mOwner->getSceneManager()->createEntity(name, meshName);
		mEntity->setCastShadows(actorParams.mNodeShadows);
		// Attach the entity to the scene node.
		mNode->attachObject(mEntity);

		// Set the scale of the node.
		if (actorParams.mNodeScale != Ogre::Vector3(1,1,1)) 
		{
			mNode->scale(actorParams.mNodeScale);
		}

		// Set the position and orientation of the node.
		if (mNode)
		{
			mNode->setPosition(pose);
			mNode->setOrientation(pose);
		}

		// If the node is not in the scene, add it to the scene.
		if (mNode->getParent() == NULL)
		{
			mOwner->getSceneManager()->getRootSceneNode()->addChild(mNode);
		}

		// Update the previous position and orientation of this body. This is
		// used to update the actor in case the scene node of this object is moved
		// by something other than physics reactions.
		prevGlobalPosition = mNode->_getDerivedPosition();
		prevGlobalOrientation = mNode->_getDerivedOrientation();
	}

	GameBodyObject::~GameBodyObject()
	{
		if (mNode == NULL)
		{
			return;
		}
		
		mNode->detachObject(mEntity);
		mOwner->getSceneManager()->destroyEntity(mEntity);
		mEntity = NULL;

		if ((mNode->numAttachedObjects() == 0) && (mNode->numChildren() == 0))
		{
			mOwner->getSceneManager()->destroySceneNode(mNode->getName());
			mNode = NULL;
		}
	}

	void GameBodyObject::createBody(const NxOgre::NxString& meshName)
	{
		// Get the scene node for the actor.
		mNode = mOwner->getSceneManager()->createSceneNode();

		// Add the scene node to the scene
		mOwner->getSceneManager()->getRootSceneNode()->addChild(mNode);
		
		// Create an entity for the body
		mEntity = mOwner->getSceneManager()->createEntity(this->getName(), meshName);
		mNode->attachObject(mEntity);

		// Update the previous position and orientation of this body. This is
		// used to update the actor in case the scene node of this object is moved
		// by something other than physics reactions.
		prevGlobalPosition = mNode->_getDerivedPosition();
		prevGlobalOrientation = mNode->_getDerivedOrientation();
	}

	void GameBodyObject::simulate(float dT)
	{
		// Check if the scene node has been changed, other than by the physics system,
		// and update the physics transforms accordingly
		if (mNode != NULL)
		{
			if (prevGlobalPosition != mNode->_getDerivedPosition())
			{
				setGlobalPosition(mNode->_getDerivedPosition());
			}
			if (prevGlobalOrientation != mNode->_getDerivedOrientation())
			{
				setGlobalOrientation(mNode->_getDerivedOrientation());
			}
		}
		shapeSimulate(dT);
	}

	//////////////////////////////////////////////////////////

	void GameBodyObject::render(float) 
	{
	#if (NX_UNSTABLE_USE_SCENE_ACTIVE_TRANSFORM == 1)

		NxMat34 nm = mActor->getGlobalPose();
		NxVec3 nv(nm.t);
		NxQuat nq(nm.M);
		if (mNode != NULL)
		{
			mNode->setPosition(nv.x, nv.y, nv.z);
			mNode->setOrientation(nq.w,nq.x,nq.y,nq.z);
		}
		shapeRender(0);
	#else
		if ((mActor != NULL) && (mNode != NULL))
		{
			mNode->setPosition(getGlobalPosition());
			mNode->setOrientation(getGlobalOrientation());
			shapeRender(dT);
		}	
	#endif

		// Update the prevGlobalTransform value
		if (mNode != NULL)
		{
			prevGlobalPosition = mNode->_getDerivedPosition();
			prevGlobalOrientation = mNode->_getDerivedOrientation();
		}
	}

	//////////////////////////////////////////////////////////

	void GameBodyObject::setNode(Ogre::SceneNode* node)
	{
		mNode = node;
	}

	//////////////////////////////////////////////////////////

	void GameBodyObject::setEntity(Ogre::Entity* entity) 
	{
		mEntity = entity;
	}

	//////////////////////////////////////////////////////////
	//
	// Based of the work from http://www.ogre3d.org/wiki/index.php/DumpingNodeTree
	//

	void GameBodyObject::DumpNodes(NxOgre::StringPairList &l, Ogre::Node *n, int level, int nid) 
	{

		Ogre::SceneNode::ObjectIterator object_it = ((Ogre::SceneNode *)n)->getAttachedObjectIterator();
		Ogre::Node::ChildNodeIterator node_it = n->getChildIterator();
		
		Ogre::MovableObject *m;
		Ogre::Entity *e;

		if (level != 0) 
		{
			l.insert(
				"Node" + 
				Ogre::StringConverter::toString(nid) + 
				"-Position", 
				Ogre::StringConverter::toString(n->getPosition()));
		}
		
		int i=0;
		while(object_it.hasMoreElements()) 
		{
			
			m = object_it.getNext();
			
			if (m->getMovableType() == "Entity") 
			{
				e = static_cast<Ogre::Entity*>(m);
				NxOgre::NxString entitySuffix = "";
				
				
				if (i > 0)
				{
					entitySuffix = Ogre::StringConverter::toString(i);
				}
					
				if (level == 0) 
				{
					l.insert("Entity" + entitySuffix, e->getMesh()->getName());
				}
				
				else 
				{
					l.insert(
							"Node" + 
							Ogre::StringConverter::toString(nid) +
							"-Entity" +
							entitySuffix,
							e->getMesh()->getName()
						);
				}
			}
			i++;
		}

		while(node_it.hasMoreElements()) 
		{
			DumpNodes(l, node_it.getNext(), level + 1, nid++);
		}

	}

	//////////////////////////////////////////////////////////

	NxOgre::StringPairList GameBodyObject::saveCustom()
	{
		
		NxOgre::StringPairList l;
		l.insert("ActorType", "Body");

		if (mNode == 0)
		{
			return l;
		}

		if (mNode->numChildren() > 0) 
		{
			DumpNodes(l, mNode, 0, 1);
		}
		else 
		{
			Ogre::Entity* entity = static_cast<Ogre::Entity*>(mNode->getAttachedObject(0));
			l.insert("Entity", entity->getMesh()->getName());
		}
		
		return l;
	}

	//////////////////////////////////////////////////////////

	void GameBodyObject::restoreCustom(NxOgre::StringPairList spl) 
	{

		mNode = mOwner->getSceneManager()->getRootSceneNode()->createChildSceneNode();

		for (NxOgre::StringPairList::StringPair sp = spl.begin();spl.hasNext();) 
		{
			sp = spl.next();
	/*
			std::stringstream ss;
			ss << sp.first;
			ss << " => ";
			ss << sp.second;
			ss << std::endl;

			NxDebug(ss.str());
	*/
			NxOgre::NxString key = sp.first;
			Ogre::StringUtil::toLowerCase(key);

			if (key == "entity" || key == "node") 
			{

				Ogre::Entity* entity = mOwner->getSceneManager()->createEntity(
					mName + "-" + sp.second + "-" + Ogre::StringConverter::toString(mNode->numAttachedObjects()), 
					sp.second
				);

				mNode->attachObject(entity);

			}

			if (key == "node-scale") 
			{
				mNode->setScale(Ogre::StringConverter::parseVector3(sp.second));
			}

		}

		// Assign first Attached Object that is an entity to mEntity

		Ogre::SceneNode::ObjectIterator object_it = mNode->getAttachedObjectIterator();
		Ogre::MovableObject *m;
		while(object_it.hasMoreElements()) 
		{
			m = object_it.getNext();
			if (m->getMovableType() == "Entity")
			{
				mEntity = (Ogre::Entity*) m;
				break;
			}
		}

		mNode->setPosition(getGlobalPosition());
		mNode->setOrientation(getGlobalOrientation());

	}

	//////////////////////////////////////////////////////////

	void GameBodyObject::disableVisualisation() 
	{

		if (mNode->getParent() != NULL) 
		{
			mNode->getParent()->removeChild(mNode);
		}

	}

	memUInt GameBodyObject::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameBodyObject::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// Call the serialize method of the GameObject parent instance
		writtenSize = GameActorObject::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameBodyObject::serialize(): buffer is too small!");
		}

		return totalSize;
	}

	memUInt GameBodyObject::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameBodyObject::populateInstance(): buffer is NULL.");
		}

		totalSize = 0;
		readSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// Call the serialize method of the GameObject parent instance
		readSize = GameActorObject::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameBodyObject::populateInstance(): buffer is too small!");
		}

		return totalSize;
	}

} // Myoushu
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
 * @file GameObject.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef GAMEBODYOBJECT_H
#define GAMEBODYOBJECT_H

#include "Ogre.h"

#include "GameActorObject.h"
#include "Exception.h"

namespace Myoushu
{
	/** This class serves as the base class for physics enabled objects that are also visible. */
	class MYOUSHU_API GameBodyObject : public GameActorObject, public NamedObject<GameBodyObject>
	{
		public:
			/**
			 * Constructor.
			 * @param name The name of the body.
			 * @param meshName The Ogre .mesh file to load for the body, must end in .mesh.
			 * @param scene The scene that will own the body.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Scene* scene) throw (Exception);

			/**
			 * Constructor.
			 * @param name The name of the body.
			 * @param entity An existing Ogre::Entity to use as visiual representation for the body.
			 * @param scene The scene to add the body to.
			 * @param firstShapeDescription Shape for the collision geometry of the body.
			 * @param pose The body's initial pose: position and orientation.
			 * @param actorParams Various parameters for the Actor part of the body,
			 *					  this includes velocity, mass, density etc.
			 * @throws Exception::E_NULL_POINTER if any pointer is NULL.
			 */
			GameBodyObject(const Ogre::String& name, Ogre::Entity *entity, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, const NxOgre::Pose& pose, NxOgre::ActorParams params) throw (Exception);

			/**
			 * Constructor.
			 * @param name The name of the body.
			 * @param sceneNode An existing Ogre::SceneNode to use with the Actor instance for this body.
			 * @param entity An existing Ogre::Entity to use as visiual representation for the body.
			 * @param scene The scene to add the body to.
			 * @param firstShapeDescription Shape for the collision geometry of the body.
			 * @param actorParams Various parameters for the Actor part of the body,
			 *					  this includes velocity, mass, density etc.
			 * @throws Exception::E_NULL_POINTER if any pointer is NULL.
			 */
			GameBodyObject(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, NxOgre::ActorParams params) throw (Exception);

			/**
			 * Constructor.
			 * @param name The name of the body.
			 * @param meshName The Ogre .mesh file to load for the body, must end in .mesh.
			 * @param sceneNode An existing Ogre::SceneNode to use with the Actor instance for this body.
			 * @param scene The scene to add the body to.
			 * @param firstShapeDescription Shape for the collision geometry of the body.
			 * @param actorParams Various parameters for the Actor part of the body,
			 *					  this includes velocity, mass, density etc.
			 * @throws Exception::E_NULL_POINTER if any pointer is NULL.
			 */
			GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene* scene, NxOgre::ShapeBlueprint *firstShapeDescription, NxOgre::ActorParams params) throw (Exception);

			/**
			 * Constructor.
			 * @param name The name of the body.
			 * @param meshName The Ogre .mesh file to load for the body, must end in .mesh.
			 * @param scene The Scene that will own the body.
			 * @param blueprint The Shape used for collision detection.
			 * @param pose The body's initial pose: position and orientation.
			 * @param actorParams Various parameters for the Actor part of the body,
			 *					  this includes velocity, mass, density etc.
			 */
			GameBodyObject(const Ogre::String& name, const Ogre::String& meshName, Scene* scene, NxOgre::ShapeBlueprint* blueprint, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams = NxOgre::ActorParams()) throw (Exception);

			/** Destructor */
			virtual ~GameBodyObject();

			CLASS_NAME_FUNCTIONS(GameBodyObject);

			/**
			 * Creates a scene node for the body and attaches the body and the associated mesh to it.
			 * @param meshName The name of the mesh to use for this body.
			 */
			void createBody(const NxOgre::NxString& meshName);

			/** Returns true if the body has visualisation. */
			virtual bool hasVisualisation() const;

			/** Getter for the Ogre::SceneNode containing this body. */
			Ogre::SceneNode* getNode();

			/** Getter for the Ogre::Entity representing the visualisation of the body. */
			Ogre::Entity* getEntity();

			/** Sets the Ogre::SceneNode that contains this body (managed by the Actor instance). */
			void setNode(Ogre::SceneNode* node);

			/** Sets the Ogre::Entity that is the visualisation of this body. */
			void setEntity(Ogre::Entity* entity);

			/**
			 * Simulates physics on this body for the time delta specified. This will update
			 * the scene nodes position and orientation based on the physical interactions in the world.
			 * @param dt The time that has passed since the previous simulation, in seconds.
			 */
			void simulate(float dt);

			/**
			 * Renders the body to the scene node.
			 * @param dt The time that has passed since the previous render call, in seconds.
			 */
			void render(float dt);

			/** Save custom data.*/
			NxOgre::StringPairList saveCustom();

			/** Restore custom data */
			void restoreCustom(NxOgre::StringPairList stringPairList);

			/** Disables visualisation of this body. */
			void disableVisualisation();

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialized data (in bytes).
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception);

			/**
			 * Populates this instance with the serialized description read from the specified buffer.
			 * @param pMem The buffer to read the instance description from.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the data read (in bytes).
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception);

		protected:
			/** The SceneNode containing this body */
			Ogre::SceneNode *mNode;
			/** The Entity that visually represents this body. */
			Ogre::Entity *mEntity;
			/** The previously rendered global transformation of the body, used to 
			 * check if the body's transformation was changed via scene nodes, and update
			 * the PhysX controlled transformation of the body.
			 */
			Ogre::Vector3 prevGlobalPosition;
			Ogre::Quaternion prevGlobalOrientation;

			void DumpNodes(NxOgre::StringPairList &l, Ogre::Node *n, int level,int nid);
	};

    // inlines
    inline bool GameBodyObject::hasVisualisation() const
    {
	    return true;
    }

    inline Ogre::SceneNode* GameBodyObject::getNode()
    {
		Poco::ScopedRWLock lock(rwLock, false);

		return mNode;
    }

    inline Ogre::Entity* GameBodyObject::getEntity()
    {
		Poco::ScopedRWLock lock(rwLock, false);

		return mEntity;
    }

} // Myoushu

#endif

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
 * @file GameActorObject.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef GAME_ACTOR_OBJECT_H
#define GAME_ACTOR_OBJECT_H

#include "Actor.h"
#include "GameObject.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * The base class for all static and dynamic objects in the game, for instance, tables, chairs or character avatars. It extends from 
	 * the Actor class for collision detection and physics.
	 */
	class MYOUSHU_API GameActorObject : public GameObject, public Actor, public NamedObject<GameActorObject>
	{
		public:
			/**
			 * Constructor. Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param initialPose The initial pose of the object. This is basically the initial position and orientation of the object.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameActorObject(const Ogre::String& name, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/** Destructor */			 
			~GameActorObject();

			CLASS_NAME_FUNCTIONS(GameActorObject);

			/** Gets the name of this instance. Override getName() to resolve ambiguity issues from Actor and NamedInstance. */
			std::string getName() const;

			/** Gets the Scene instance that contains this GameActorObject. */
			virtual Scene* getScene();

			/** Gets the current up vector of this actor. */
			virtual Ogre::Vector3 getGlobalUpVector();

			/** Disables response and reporting of collions for this actor. */
			void disableCollisionDetection();

			/** Enables collision detection for this actor. */
			void enableCollisionDetection();

			/** Disables collision response for this actor, but still reports collisions. */
			void disableCollisionResponse();

			/** Enables collision response for this actor. */
			void enableCollisionResponse();

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
	};

	// inlines
	inline std::string GameActorObject::getName() const
	{
		return NamedInstance::getName();
	}

	inline Scene* GameActorObject::getScene()
	{
		return Actor::getScene();
	}

	inline void GameActorObject::disableCollisionDetection()
	{
		Actor::raiseActorFlag(NX_AF_DISABLE_COLLISION);
	}

	inline void GameActorObject::enableCollisionDetection()
	{
		Actor::clearActorFlag(NX_AF_DISABLE_COLLISION);
	}

	inline void GameActorObject::disableCollisionResponse()
	{
		Actor::raiseActorFlag(NX_AF_DISABLE_RESPONSE);
	}

	inline void GameActorObject::enableCollisionResponse()
	{
		Actor::clearActorFlag(NX_AF_DISABLE_RESPONSE);
	}

} // Myoushu

#endif

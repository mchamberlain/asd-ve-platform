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
 * @file GameCharacterObject.h
 * @author ME Chamberlain
 * @date August 2008
 */

#ifndef MYOUSHU_GAME_CHARACTER_OBJECT_H
#define MYOUSHU_GAME_CHARACTER_OBJECT_H

#include "Poco/RWLock.h"
#include "NxOgre.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameCharacterObjectAction.h"

namespace Myoushu
{
	class MYOUSHU_API GameCharacterObject : public GameObject, public NamedObject<GameCharacterObject>
	{
		public:
			/**
			 * Construcor. Creates a GameCharacterObject from an existing NxOgre::Character instance.
			 * @param name The unique name for this GameCharacterObject instance.
			 * @param scene The scene to create this character in.
			 * @param nxOgreCharacter The NxOgre::Character instance to create this GameCharacterObject instace from.
			 * @param params Parameters to create this character with, and with which nxOgreCharacter was created.
			 * @throws Exception::E_NULL_POINTER if character is NULL.
			 */
			GameCharacterObject(const Ogre::String& name, Scene* scene, NxOgre::Character* nxOgreCharacter, NxOgre::CharacterParams params) throw (Exception);

			/**
			 * Constructor.
			 * @param name The unique name for this GameCharacterObject instance.
			 * @param scene The scene to create this character in.
			 * @param characterController The NxOgre::CharacterController instance that controls this character.
			 * @param pose The initial position and orientation to create this character with.
			 * @param params Parameters to create this character with.
			 */
			GameCharacterObject(const Ogre::String& name, Scene* scene, NxOgre::CharacterController* characterController
				, NxOgre::Pose pose, NxOgre::CharacterParams params);

			/** Destructor. */
			~GameCharacterObject();

			CLASS_NAME_FUNCTIONS(GameCharacterObject);

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

			/**
			 * Creates a new GameCharacterObjectAction and adds it to this GameCharacterObject. The instance is owned by this
			 * GameCharacterObject instance and will be destroyed by it when appropriate.
			 * @param name The name of the action.
			 * @param character The GameCharacterObject instance this action is bound to.
			 * @param toggleAction Flag indicating whether this is a toggle action. Toggle actions only use action start 
			 *					   callbacks (no stop callbacks) and the animation is toggled on or off every time the 
			 *					   action is started.
			 * @param animationName The name of the character animation to play, if any.
			 * @param animBehaviour The manner in which to play the animation, loop, once, only one frame.
			 * @param restartAnimation Flag indicating whether the animation should be restarted when the action is started.
			 * @param playCounter If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 *					  increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 *					  if the counter is zero. This is useful in situations where there are multiple actions that play the
			 *					  same animation.
			 */
			GameCharacterObjectAction* addAction(const Ogre::String& name, bool toggleAction = false, const Ogre::String& animationName = ""
				, GameCharacterObjectAction::AnimationBehaviour animBehaviour = GameCharacterObjectAction::AM_LOOP, bool restartAnimation = false, bool playCounter = false) throw (Exception);

			/** Creates an Ogre::SceneNode for this character. */
			void createNode();

			/**
			 * Attaches a mesh to this character.
			 * @param meshName The name of the mesh. Will be loaded via Ogre's resource manager.
			 */
			void attachMesh(const Ogre::String& meshName);

			/**
			 * Attach a skeleton mesh to this character.
			 * @param meshName The name of the mesh. Will be loaded via Ogre's resource manager.
			 */
			void attachSkeletonMesh(const Ogre::String& meshName);

			/**
			 * Set the bones that represent the feet of this character.
			 * @param leftBone The name of the bone representing the left foot of the character.
			 * @param rightBone the name of the bone representing the right foot of the character.
			 */
			void bindFeet(const Ogre::String& leftBone, const Ogre::String& rightBone);

			/** Unbound bones that were previously bound to the feet of the character. */
			void unBindFeet();

			/** Gets the current up vector of this character. */
			virtual Ogre::Vector3 getGlobalUpVector();

			/** Gets the current world forward vector for this character. */
			virtual Ogre::Vector3 getGlobalForwardVector();

			/**
			 * Get the global (world) position of the character.
			 * @return An Ogre::Vector3 containing the world position of the character.
			 */
			Ogre::Vector3 getGlobalPosition() const;

			/**
			 * Get the global orientation of the character.
			 * @return An Ogre::Quaternion containing the global orientation of the character.
			 */
			Ogre::Quaternion getGlobalOrientation() const;
			
			/** 
			 * Run physics a simulation step on this character.
			 * @param dt The time that has passed since the previous simulation step.
			 */
			void simulate(float dt);

			/**
			 * Apply the results of the physics simulation to the character and relevant
			 * nodes in the scene.
			 * @param dt The time that has passed since the previous simulation step.
			 */
			void render(float dt);

			/**
			 * Play an animation bound the character.
			 * @param animationName The name of the animation to play.
			 * @param restart If true the animation is played from the beginning.
			 * @param loop If true the animation is looped.
			 * @param playCounter If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 *					  increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 *					  if the counter is zero. This is useful in situations where there are multiple actions that play the
			 *					  same animation.
			 */
			void playAnimation(const Ogre::String& animationName, bool restart = true, bool loop = true, bool playCounter = false);

			/**
			 * Stop playing an animation of the character.
			 * @param animationName the name of the animation.
			 * @param playCounter If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 *					  increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 *					  if the counter is zero. This is useful in situations where there are multiple actions that play the
			 *					  same animation.
			 */
			void stopAnimation(const Ogre::String& animationName, bool playCounter = false);

			/**
			 * Set the direction the character is facing in.
			 * @param direction The direction the character is facing in, set in radians.
			 */
			void setDirection(const Ogre::Radian& direction);

			/**
			 * Set the direction the character is facing in.
			 * @param direction An Ogre::Quaternion representing the new direction the
			 *					character must face in.
			 */
			void setDirection(const Ogre::Quaternion& direction);

			/**
			 * Set the next movement direction.
			 * @param direction An NxVec3 instance containing the new movement direction.
			 */
			void setMovementDirection(const Ogre::Vector3& direction);

			/**
			 * Set the NxOgre::CharacterMovementVectorController instance that controls the movement of this
			 * character.
			 * @param movementVectorController The NxOgre::CharacterMovementVectorController instance that controls the movement of this
			 *								   character.
			 */
			void setMovementVectorController(NxOgre::CharacterMovementVectorController* movementVectorController);

			/**
			 * Set the position of the character in the world.
			 * @param position The position to set.
			 */
			void setPosition(const Ogre::Vector3& position);

			/**
			 * Get the name of this GameCharacterObject instance.
			 * @return The name of this GameCharacterObject instance.
			 */
			Ogre::String getName() const;

			/**
			 * Get the Ogre::SceneNode that contains the entity that represents this character.
			 * @return The Ogre::SceneNode that contains the entity that represents this character.
			 */
			Ogre::SceneNode* getNode();

			/**
			 * Get the Ogre::SceneNode that contains the entity that represents this character.
			 * @return The Ogre::SceneNode that contains the entity that represents this character.
			 */
			const Ogre::SceneNode* getNode() const;

			/**
			 * Get the Ogre::Entity instance that visually represents this character.
			 * @return The Ogre::Entity instance that visually represents this character.
			 */
 			Ogre::Entity* getEntity();

			/**
			 * Get the Scene instance that this character belongs to.
			 * @return The Scene instance that this character belongs to.
			 */
			Scene* getScene();

			/**
			 * Get the raw NxController instance that controls this character.
			 * @return The raw NxController instance that controls this character.
			 */
			NxController* getNxController();
		
			/**
			 * Gets the mass of this character.
			 * @return The mass of this character.
			 */
			NxReal getMass();

		protected:
			/** The NxOgre::Character instance that is wrapped by this class. */
			NxOgre::Character *nxOgreCharacter;
			/** The Scene instance that contains this character instance. */
			Scene *scene;
			/** A copy of the character parameters used when the NxOgre::Character instance was created. */
			NxOgre::CharacterParams mCharacterParams;

			/**
			 * Sets the fields in the mCharacterParams field to the values from the specified instance of NxOgre::CharacterParams.
			 * @param params The NxOgre::CharacterParams instance to backup.
			 */
			void backupCharacterParams(const NxOgre::CharacterParams& params);
	};

	// inlines
	inline Ogre::Vector3 GameCharacterObject::getGlobalForwardVector()
	{
		return (getNode()->_getDerivedOrientation() * getLocalForwardVector());
	}

} // Myoushu

#endif

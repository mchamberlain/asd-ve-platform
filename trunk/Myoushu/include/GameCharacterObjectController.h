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
 * @file GameCharacterObjectController.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef MYOUSHU_GAME_CHARACTER_OBJECT_CONTROLLER_H
#define MYOUSHU_GAME_CHARACTER_OBJECT_CONTROLLER_H

#include <map>
#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Ogre.h"
#include "NxOgre.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"
#include "MoveableObjectController.h"
#include "InputMessage.h"
#include "GameCharacterObject.h"
#include "GameCharacterObjectControllerBinding.h"

namespace Myoushu
{
	/**
	 * A Controller for controlling a GameCharacterObject. Supports basic movement and orientation changes. The controller actions are bound to input action strings.
	 */
	class MYOUSHU_API GameCharacterObjectController : public MoveableObjectController, public NxOgre::CharacterMovementVectorController, public NamedObjectInstanceCreator<GameCharacterObjectController>
	{
		public:
			/** Map of input actions to GameCharacterObjectControllerBinding instances */
			typedef std::multimap<Ogre::String, Poco::AutoPtr<GameCharacterObjectControllerBinding> > InputActionBindingsMap;
			/** Entry in the map of input actions to GameCharacterObjectControllerBinding instances */
			typedef std::pair<Ogre::String, Poco::AutoPtr<GameCharacterObjectControllerBinding> > InputActionBindingsMapEntry;
			/** A pair of lower bound and upper bound iterators from the InputActionBindingsMap */
			typedef std::pair<InputActionBindingsMap::iterator, InputActionBindingsMap::iterator> InputActionBindingsMapRange;

			/** Nullary Constructor. Should only be used in conjunction with Serializable::populateInstance(). */
			GameCharacterObjectController();

			/**
			 * Constructor.
			 * @param name The name of this Controller.
			 * @param character The GameCharacterObject that will be controlled by this instance.
			 * @throws Exception::E_NULL_POINTER if character is NULL.
			 */
			GameCharacterObjectController(const Ogre::String& name, GameCharacterObject* character) throw (Exception);

			/**
			 * Constructor.
			 * @param name The name of this Controller.
			 * @param character The GameCharacterObject that will be controlled by this instance.
			 * @param maxMovementSpeed the maximum movement speed of the object, in 1.0 graphics units per second.
			 * @param movementAcceleration the movement acceleration of the object, in 1.0 graphics units per second per second.
			 * @param maxRotationSpeed the maximum rotation speed of the object, in radians per second.
			 * @param rotationAcceleration the rotation acceleration for the object, in radians per second per second.
			 * @throws Exception::E_NULL_POINTER if character is NULL.
			 */
			GameCharacterObjectController(const Ogre::String& name, GameCharacterObject* character, Ogre::Real maxMovementSpeed
				, Ogre::Real movementAcceleration, Ogre::Real maxRotationSpeed, Ogre::Real rotationAcceleration) throw (Exception);

			/** Destructor */
			virtual ~GameCharacterObjectController();

			CLASS_NAME_FUNCTIONS(GameCharacterObjectController);

			/** 
			 * Stops any current movement of the controlled object by this controller. Does not affect any future movement, basically
			 * this functions sets all velocities to zero.
			 */
			virtual void stop();

			/**
			 * Binds an input action to a movement direction and character action.
			 * @param inputAction The input action to bind to a movement direction and character action.
			 * @param characterAction The character action to perform. This is bound in the GameCharacterObject instance to
			 *						  an animation for instance.
			 * @param direction The direction the character should move in.
			 * @param rotationAxis
			 * @param deviceAxis
			 * @param once If true the characterAction will only be performed once. If false and the underlying device 
			 *			   action has press and release actions the character action will be performed from the press
			 *			   until the release action.
			 */
			void bind(const Ogre::String& inputAction, const Ogre::String& characterAction, const Ogre::Vector3& direction
				, const Ogre::Vector3& rotationAxis = Ogre::Vector3::ZERO, int deviceAxis = -1, bool once = false);

			/**
			 * Binds an input action to a character action.
			 * @param inputAction The input action to bind to a character action.
			 * @param characterAction The character action to perform. This is bound in the GameCharacterObject instance to
			 *						  an animation for instance.
			 * @param once If true the characterAction will only be performed once. If false and the underlying device 
			 *			   action has press and release actions the character action will be performed from the press
			 *			   until the release action.
			 */
			void bind(const Ogre::String& inputAction, const Ogre::String& characterAction, bool once = true);

			/**
			 * Process an input action that has been bound to the character managed by this instance.
			 * @param message The InputMessage instance that fired the inputAction.
			 */
			virtual void processInputAction(InputMessage *message);

			/**
			 * Overridden from NxOgre::CharacterMovementVectorCharacter. This method moves a character based on a given
			 * movement vector and time delta.
			 * @param out The vector to write the change in position in.
			 * @param moveVector The vector to move the character by relative to its local coordinate system with Y+ as the up
			 *					 direction.
			 * @param direction The direction the character is facing in in the world.
			 * @param t The time that has passed since the last update.
			 * @param character The NxOgre::Character instance of the character that is moved.
			 */
			void move(NxVec3 &out, NxVec3 &moveVector, NxQuat &direction, NxVec3 &g, float t, NxOgre::Character* character);

			/**
			 * Update method called periodically by the ControllerTask if this Controller is active.
			 * @param timeDelta The time since the last call of this function.
			 */
			virtual void update(unsigned long timeDelta);

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
			/** The GameCharacterObject instance that will be controlled by this instance. */
			GameCharacterObject *character;
			/** Vector that stores the current movement direction of the character. */
			Ogre::Vector3 movementDirection;
			/** This vector is subtracted from the movement direction vector at the end of the update phase. It is
			 * used to cancel the effect of once off actions after the first update.
			 */
			Ogre::Vector3 negationVector;
			/** Persistant list of axes to rotate the character around in the next update() call. */
			std::list<Ogre::Vector3> rotationAxisList;
			/** 
			 * List of axes to rotate the character around in the next update() call, only once, with a potential delta value. This
			 * is useful for when a device axis is bound to rotating the character.
			 */
			std::list<std::pair<Ogre::Vector3, int> > onceOffRotationAxisList;
			/** A map of action identifiers to a map of axis identifiers to their previous positions. */
			std::map<std::string, std::map<int, int> > previousAxisPositions;
			/** List of actions to start in the next update */
			std::list<Ogre::String> actionsToStart;
			/** List of actions to stop in the next update */
			std::list<Ogre::String> actionsToStop;
			/** Multi map of input actions to bindings for this controller. */
			InputActionBindingsMap inputActionBindings;
	};
} // Myoushu

#endif

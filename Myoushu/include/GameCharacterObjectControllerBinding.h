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
 * @file GameCharacterObjectControllerBinding.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef MYOUSHU_GAME_CHARACTER_OBJECT_CONTROLLER_BINDING_H
#define MYOUSHU_GAME_CHARACTER_OBJECT_CONTROLLER_BINDING_H

#include "Poco/RefCountedObject.h"
#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * This class represents a binding between an input action string and the effect it should have on a GameCharacterObject. It is used
	 * in the GameCharacterObjectController class.
	 */
	class MYOUSHU_API GameCharacterObjectControllerBinding : public Poco::RefCountedObject, public Serializable
	{
		public:
			/** Nullary Constructor. */
			GameCharacterObjectControllerBinding();

			/**
			 * Constructor. Initialises the fields of this instance to the specified parameters.
			 * @param inputAction The input action name for this binding.
			 * @param characterAction The character action associated with this binding.
			 * @param direction The direction associated with this binding.
			 * @param rotationAxis An axis to rotate the controlled character around. The axis (0,0,0) means no rotation.
			 * @param deviceAxis The device axis to use. If < 0 the device action is assumed to be a simple button press. Otherwise a valid
			 *					 axis index, such as InputMessage::DS_X_INDEX must be specified.
			 * @param once Boolean flag indicating whether this action should be executed once or continiously between
			 *			   press and release events.
			 */
			GameCharacterObjectControllerBinding(const Ogre::String& inputAction, const Ogre::String& characterAction
				, const Ogre::Vector3& direction = Ogre::Vector3::ZERO, const Ogre::Vector3& rotationAxis = Ogre::Vector3::ZERO
				, int deviceAxis = -1, bool once = false);

			/** Destructor */
			virtual ~GameCharacterObjectControllerBinding();

			/** Sets the input action for this binding */
			void setInputAction(const Ogre::String& inputAction);

			/** Gets the input action for this binding */
			Ogre::String getInputAction() const;

			/** Sets the direction for this binding. */
			void setDirection(const Ogre::Vector3& direction);

			/** Gets the direction for this binding */
			Ogre::Vector3 getDirection() const;

			/** Sets the character action for this binding. */
			void setCharacterAction(const Ogre::String& characterAction);

			/** Gets the character action for this binding. */
			Ogre::String getCharacterAction() const;

			/** Sets the axis to rotate the controlled character around. The axis (0,0,0) means no rotation. */
			void setRotationAxis(const Ogre::Vector3& rotationAxis);

			/** Gets the axis to rotate the controlled character around. The axis (0,0,0) means no rotation. */
			Ogre::Vector3 getRotationAxis() const;

			/** 
			 * Sets the device axis to use. If < 0 the device action is assumed to be a simple button press. Otherwise a valid
			 * axis index, such as InputMessage::DS_X_INDEX must be specified.
			 */
			void setDeviceAxis(int deviceAxis);

			/** 
			 * Gets the device axis to use. If < 0 the device action is assumed to be a simple button press. Otherwise a valid
			 * axis index, such as InputMessage::DS_X_INDEX must be specified.
			 */
			int getDeviceAxis() const;

			/**
			 * Sets the once flag that indicates whether this action should be executed only
			 * once when the action is fired, or continously between press and release actions.
			 */
			void setOnce(bool once);

			/** 
			 * Gets the once flag that indicates whether this action should be executed only
			 * once when the action is fired, or continously between press and release actions. 
			 */
			bool isOnce() const;

			bool operator==(const GameCharacterObjectControllerBinding& rhs) const;

			GameCharacterObjectControllerBinding& operator=(const GameCharacterObjectControllerBinding& rhs);

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
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The name of the input action for this binding. */
			Ogre::String inputAction;
			/** The character action associated with this binding. */
			Ogre::String characterAction;
			/** The direction that is associated with this binding, if any. */
			Ogre::Vector3 direction;
			/** An axis to rotate the controlled character around. The axis (0,0,0) means no rotation. */
			Ogre::Vector3 rotationAxis;
			/** 
			 * The device axis to use. If < 0 the device action is assumed to be a simple button press. Otherwise a valid
			 * axis index, such as InputMessage::DS_X_INDEX must be specified.
			 */
			int deviceAxis;
			/** Flag indicating if this is a once off or continious action. */
			bool once;
	};

	// inlines
	inline void GameCharacterObjectControllerBinding::setInputAction(const Ogre::String& inputAction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->inputAction = inputAction;
	}

	inline Ogre::String GameCharacterObjectControllerBinding::getInputAction() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return inputAction;
	}

	inline void GameCharacterObjectControllerBinding::setDirection(const Ogre::Vector3& direction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->direction = direction;
	}

	inline Ogre::Vector3 GameCharacterObjectControllerBinding::getDirection() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return direction;
	}

	inline void GameCharacterObjectControllerBinding::setCharacterAction(const Ogre::String& characterAction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->characterAction = characterAction;
	}

	inline Ogre::String GameCharacterObjectControllerBinding::getCharacterAction() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return characterAction;
	}

	inline void GameCharacterObjectControllerBinding::setRotationAxis(const Ogre::Vector3& rotationAxis)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->rotationAxis = rotationAxis;
	}

	inline Ogre::Vector3 GameCharacterObjectControllerBinding::getRotationAxis() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return rotationAxis;
	}

	inline void GameCharacterObjectControllerBinding::setDeviceAxis(int deviceAxis)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->deviceAxis = deviceAxis;
	}

	inline int GameCharacterObjectControllerBinding::getDeviceAxis() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return deviceAxis;
	}

	inline void GameCharacterObjectControllerBinding::setOnce(bool once)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->once = once;
	}

	inline bool GameCharacterObjectControllerBinding::isOnce() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return once;
	}

	inline bool GameCharacterObjectControllerBinding::operator==(const GameCharacterObjectControllerBinding& rhs) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return ((inputAction == rhs.getInputAction()) && (characterAction == rhs.getCharacterAction()) 
			&& (direction == rhs.getDirection()) && (once == rhs.isOnce()));
	}

} // namespace Myoushu

#endif

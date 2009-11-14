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
 * @file MoveableObjectController.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef MYOUSHU_MOVEABLE_OBJECT_CONTROLLER_H
#define MYOUSHU_MOVEABLE_OBJECT_CONTROLLER_H

#include "Ogre.h"

#include "Platform.h"
#include "Controller.h"

namespace Myoushu
{
	/**
	 * A class that provides some data members for movement and rotations speeds. Used as a base class of more advanced controller classes,
	 * such as GameCharacterObjectController and CameraWithGameObjectController.
	 */
	class MYOUSHU_API MoveableObjectController : public Controller
	{
		public:
			/**
			 * Constructor. All speed and acceleration values default to 1.
			 * @param name The name/id of this controller.
			 * @param maxMovementSpeed the maximum movement speed of the object, in 1.0 graphics units per second.
			 * @param movementAcceleration the movement acceleration of the object, in 1.0 graphics units per second per second.
			 * @param maxRotationSpeed the maximum rotation speed of the object, in radians per second.
			 * @param rotationAcceleration the rotation acceleration for the object, in radians per second per second.
			 */
			MoveableObjectController(const Ogre::String& name, Ogre::Real maxMovementSpeed = 1, Ogre::Real movementAcceleration = 1, Ogre::Real maxRotationSpeed = 1
				, Ogre::Real rotationAcceleration = 1);

			/** Gets current the movement speed of the object, in 1.0 graphics units per second. */
			Ogre::Real getMovementSpeed() const;

			/** Sets current the maximum movement speed of the object, in 1.0 graphics units per second. */
			void setMaxMovementSpeed(Ogre::Real maxMovementSpeed);

			/** Gets current the maximum movement speed of the object, in 1.0 graphics units per second. */
			Ogre::Real getMaxMovementSpeed() const;

			/** Gets the movement acceleration of the object, in 1.0 graphics units per second per second. */
			Ogre::Real getMovementAcceleration() const;

			/** Sets the movement acceleration of the object, in 1.0 graphics units per second per second. */
			void setMovementAcceleration(Ogre::Real movementAcceleration);

			/** Gets the current rotation speed of the object, in radians per second. */
			Ogre::Real getRotationSpeed() const;

			/** Sets the maximum rotation speed of the object, in radians per second. */
			void setMaxRotationSpeed(Ogre::Real maxRotationSpeed);

			/** Gets the maximum rotation speed of the object, in radians per second. */
			Ogre::Real getMaxRotationSpeed() const;

			/** Sets the rotation acceleration for the object, in radians per second per second. */
			void setRotationAcceleration(Ogre::Real rotationAcceleration);

			/** Gets the rotation acceleration for the object, in radians per second per second. */
			Ogre::Real getRotationAcceleration() const;

			/** 
			 * This function sets the max speeds and accelerations of otherController to be the same as this instance's.
			 * It will ensure that movement and rotation speed of this controller and otherController are equal across
			 * calls to update().
			 * @param otherController The other MoveableObjectController to link this instance with. If NULL the existing link is removed.
			 */
			void linkSpeedsWith(MoveableObjectController* otherController);

			/** 
			 * Stops any current movement of the controlled object by this controller. Does not affect any future movement, basically
			 * this functions sets all velocities to zero.
			 */
			virtual void stop();

			/**
			 * This method is called by the ControllerTask.
			 * @param timeDelta The time that has passed since the previous
			 *					update in mircoseconds.
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
			/** The current movement speed of the object, in 1.0 graphics units per second. */
			Ogre::Real mMovementSpeed;
			/** The maximum movement speed of the object, in 1.0 graphics units per second. */
			Ogre::Real mMaxMovementSpeed;
			/** The movement acceleration of the object, in 1.0 graphics units per second per second. */
			Ogre::Real mMovementAcceleration;
			/** The current rotation speed of the object, in radians per second. */
			Ogre::Real mRotationSpeed;
			/** The maximum rotation speed of the object, in radians per second. */
			Ogre::Real mMaxRotationSpeed;
			/** The rotation acceleration of the object, in radians per second per second. */
			Ogre::Real mRotationAcceleration;
			/** 
			 * A controller that has its max speeds and accelerations set to be the same as this instance's.
			 * It is ensured that the movement and rotation speed of this controller and mpLinkedController are equal across
			 * calls to update().
			 */
			MoveableObjectController *mpLinkedController;

			/** Sets the current movement speed of the object being controlled by the controller, in 1.0 world units per second. */
			void setMovementSpeed(Ogre::Real movementSpeed);

			/** Sets the current rotation speed of the object being controller by the controller, in 1.0 radians per second. */
			void setRotationSpeed(Ogre::Real rotationSpeed);

			/** Updates the speeds and accelerations of mpLinkedController, if it is not NULL, to match that of this controller. */
			void updateLinkedController();

	}; // class MoveableObjectController

	// inlines

	inline void MoveableObjectController::setMovementSpeed(Ogre::Real movementSpeed)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		movementSpeed = mMovementSpeed;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setMovementSpeed(movementSpeed);
		}
	}

	inline Ogre::Real MoveableObjectController::getMovementSpeed() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMovementSpeed;
	}

	inline void MoveableObjectController::setMaxMovementSpeed(Ogre::Real maxMovementSpeed)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMaxMovementSpeed = maxMovementSpeed;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setMaxMovementSpeed(maxMovementSpeed);
		}
	}

	inline Ogre::Real MoveableObjectController::getMaxMovementSpeed() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMaxMovementSpeed;
	}

	inline Ogre::Real MoveableObjectController::getMovementAcceleration() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMovementAcceleration;
	}

	inline void MoveableObjectController::setMovementAcceleration(Ogre::Real movementAcceleration)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMovementAcceleration = movementAcceleration;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setMovementAcceleration(movementAcceleration);
		}
	}

	inline void MoveableObjectController::setRotationSpeed(Ogre::Real rotationSpeed)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mRotationSpeed = rotationSpeed;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setRotationSpeed(rotationSpeed);
		}
	}

	inline Ogre::Real MoveableObjectController::getRotationSpeed() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mRotationSpeed;
	}

	inline void MoveableObjectController::setMaxRotationSpeed(Ogre::Real maxRotationSpeed)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMaxRotationSpeed = maxRotationSpeed;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setMaxRotationSpeed(maxRotationSpeed);
		}
	}

	inline Ogre::Real MoveableObjectController::getMaxRotationSpeed() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMaxRotationSpeed;
	}

	inline void MoveableObjectController::setRotationAcceleration(Ogre::Real rotationAcceleration)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mRotationAcceleration = rotationAcceleration;
		if (mpLinkedController != NULL)
		{
			mpLinkedController->setRotationAcceleration(rotationAcceleration);
		}
	}

	inline Ogre::Real MoveableObjectController::getRotationAcceleration() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mRotationAcceleration;
	}

} // namespace Myoushu

#endif

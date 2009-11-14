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
 * @file CameraWithGameObjectController.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_CAMERA_WITH_GAME_OBJECT_CONTROLLER_H
#define MYOUSHU_CAMERA_WITH_GAME_OBJECT_CONTROLLER_H

#include <string>
#include <list>
#include <map>

#include "Poco/AutoPtr.h"

#include "Ogre.h"

#include "Platform.h"
#include "MoveableObjectController.h"
#include "GameObject.h"
#include "InputMessage.h"

namespace Myoushu
{
	/**
	 * A controller for controlling a third or first person camera associated with some GameObject.
	 */
	class MYOUSHU_API CameraWithGameObjectController : public MoveableObjectController, public NamedObject<CameraWithGameObjectController>
	{
		public:
			/** Enumerations of CameraActions, such as yaw and pitch. */
			enum CameraAction
			{
				/** An unknown camera action. */
				CA_UNKNOWN = 0,
				/** Pitch the camera */
				CA_PITCH,
				/** Yaw the camera */
				CA_YAW,
				/** Roll the camera */
				CA_ROLL
			};

			/** 
			 * Type definition for an Action entry: CameraAction the action that should be applied to the camera. The int
			 * defines whether the input associated with this action comes from an axis on a device or a non-axis. If the value
			 * is less than zero it is non-axis, 0 or greater should be an axis index that could be used with an InputMessage,
			 * such as InputMessage::DS_X_INDEX.
			 */
			typedef std::pair<CameraAction, int> ActionEntry;
			/** Type definition of a multimap of input action strings to camera actions. */
			typedef std::multimap<std::string, ActionEntry> InputActionToCameraActionMap;
			/** Type defintion of an iterator over InputActionToCameraActionMap. */
			typedef InputActionToCameraActionMap::iterator InputActionToCameraActionMapIterator;
			/** Type defintion of an const_iterator over InputActionToCameraActionMap. */
			typedef InputActionToCameraActionMap::const_iterator InputActionToCameraActionMapConstIterator;
			/** Type defintion of an entry in InputActionToCameraActionMap. */
			typedef std::pair<std::string, ActionEntry> InputActionToCameraActionMapEntry;

			/**
			 * Constructor.
			 * @param name The name of this Controller.
			 */
			CameraWithGameObjectController(const std::string& name, Ogre::Camera *pCamera, GameObject *pGameObject);

			/** Destructor */
			virtual ~CameraWithGameObjectController();

			CLASS_NAME_FUNCTIONS(CameraWithGameObjectController);

			/** Gets the Ogre::Camera instance that is controlled by this Controller. */
			const Ogre::Camera* getCamera() const;

			/** Gets the Ogre::Camera instance that is controlled by this Controller. */
			Ogre::Camera* getCamera();

			/** Sets the Ogre::Camera instance that is controlled by this Controller. */
			void setCamera(Ogre::Camera *pCamera);

			/** Gets the GameObject instance that is followed by the camera. */
			GameObject* getGameObject();

			/** Gets the GameObject instance that is followed by the camera. */
			const GameObject* getGameObject() const;

			/** Sets the GameObject instance that is followed by the camera. */
			void setGameObject(GameObject *pGameObject);

			/** Gets the point to look at relative to the center of mpGameObject. */
			Ogre::Vector3 getOffsetFromGameObjectCenter() const;

			/** Sets the point to look at relative to the center of mpGameObject. */
			void setOffsetFromGameObjectCenter(const Ogre::Vector3& offsetFromGameObjectCenter);

			/** Gets the distance to maintain from the camera. */
			Ogre::Real getDistanceFromObject() const;

			/** Sets the distance to maintain from the camera. */
			void setDistanceFromObject(Ogre::Real distanceFromObject);

			/** 
			 * Gets the minimum allowed angle between the camera direction and the game object
			 * up vector.
			 */
			Ogre::Radian getMinAngleBetweenCamDirectionGameObjectUp() const;

			/** 
			 * Sets the minimum allowed angle between the camera direction and the game object
			 * up vector.
			 */
			void setMinAngleBetweenCamDirectionGameObjectUp(Ogre::Radian angle);

			/** 
			 * Gets the maximum allowed angle between the camera direction and the game object
			 * up vector.
			 */
			Ogre::Radian getMaxAngleBetweenCamDirectionGameObjectUp() const;

			/** 
			 * Sets the maximum allowed angle between the camera direction and the game object
			 * up vector.
			 */
			void setMaxAngleBetweenCamDirectionGameObjectUp(Ogre::Radian angle);

			/**
			 * This method is called by the ControllerTask.
			 * @param timeDelta The time that has passed since the previous
			 *					update in mircoseconds.
			 */
			virtual void update(unsigned long timeDelta);

			/**
			 * Binds the specified action string to this controller. InputMessages containing the specified
			 * input action string will be delivered to this controller.
			 * @param cameraAction The CameraAction to associate the input action string with.
			 * @param inputActionStr The input action string to bind to this controller.
			 * @param axis Defines whether the input associated with this action comes from an axis on a device or a non-axis. If the value
			 * is less than zero it is a non-axis, 0 or greater should be an axis index that could be used with an InputMessage,
			 * such as InputMessage::DS_X_INDEX.
			 */
			void bind(CameraAction cameraAction, const std::string& inputActionStr, int axis = -1);

			/**
			 * Unbind an input action string that was previously bound to a CameraAction.
			 * @param inputActionStr The input action string to unbind.
			 * @return true if the action was successfully unbound, false if the action was not previously bound and thus not unbound.
			 */
			bool unBind(const std::string& inputActionStr);

			/** Processes an InputMessage containing one of the input action strings that have been associated with camera actions. */
			void processInputAction(InputMessage *message);

		protected:
			/** The Ogre::Camera to be controlled by this controller. */
			Ogre::Camera *mpCamera;
			/** The GameActorObject that will be followed by the camera */
			GameObject *mpGameObject;
			/** The point to look at relative to the center of mpGameObject. */
			Ogre::Vector3 mOffsetFromGameObjectCenter;
			/** The distance to maintain from the camera. */
			Ogre::Real mDistanceFromObject;
			/** The previous position of the game object. */
			Ogre::Vector3 mPreviousGameObjectPosition;
			/** Map of input action strings to camera actions. */
			InputActionToCameraActionMap mInputActionToCameraActionMap;
			/** Queue of actions to perform in next call to update() */
			std::list<std::pair<ActionEntry, Poco::AutoPtr<InputMessage> > > mQueueOfActionsToPerform;
			/** A map of input device names to their axes' respective previous positions */
			std::map<std::string, std::map<int, int> > mPrevAxisPositions;
			/** Minimum allowed angle between camera direction and game object up vector. */
			Ogre::Radian mMinAngleBetweenCamDirectionGameObjectUp;
			/** Maximum allowed angle between camera direction and game object up vector. */
			Ogre::Radian mMaxAngleBetweenCamDirectionGameObjectUp;
	};

	inline const Ogre::Camera* CameraWithGameObjectController::getCamera() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpCamera;
	}

	inline Ogre::Camera* CameraWithGameObjectController::getCamera()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpCamera;
	}

	inline void CameraWithGameObjectController::setCamera(Ogre::Camera *pCamera)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpCamera = pCamera;
	}

	inline GameObject* CameraWithGameObjectController::getGameObject()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpGameObject;
	}

	inline const GameObject* CameraWithGameObjectController::getGameObject() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpGameObject;
	}

	inline Ogre::Vector3 CameraWithGameObjectController::getOffsetFromGameObjectCenter() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mOffsetFromGameObjectCenter;
	}

	inline void CameraWithGameObjectController::setOffsetFromGameObjectCenter(const Ogre::Vector3& offsetFromGameObjectCenter)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mOffsetFromGameObjectCenter = offsetFromGameObjectCenter;
	}

	inline Ogre::Real CameraWithGameObjectController::getDistanceFromObject() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mDistanceFromObject;
	}

	inline void CameraWithGameObjectController::setDistanceFromObject(Ogre::Real distanceFromObject)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mDistanceFromObject = distanceFromObject;
	}

	inline Ogre::Radian CameraWithGameObjectController::getMinAngleBetweenCamDirectionGameObjectUp() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMinAngleBetweenCamDirectionGameObjectUp;
	}

	inline void CameraWithGameObjectController::setMinAngleBetweenCamDirectionGameObjectUp(Ogre::Radian angle)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMinAngleBetweenCamDirectionGameObjectUp = angle;
	}

	inline Ogre::Radian CameraWithGameObjectController::getMaxAngleBetweenCamDirectionGameObjectUp() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMaxAngleBetweenCamDirectionGameObjectUp;
	}

	inline void CameraWithGameObjectController::setMaxAngleBetweenCamDirectionGameObjectUp(Ogre::Radian angle)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMaxAngleBetweenCamDirectionGameObjectUp = angle;
	}

} // namespace Myoushu

#endif

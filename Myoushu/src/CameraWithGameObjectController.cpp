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
 * @file CameraWithGameObjectController.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "CameraWithGameObjectController.h"
#include "InputActionManager.h"
#include "EngineLog.h"
#include "GameActorObject.h"
#include "GameCharacterObject.h"

namespace Myoushu
{
	CLASS_NAME(CameraWithGameObjectController, "Myoushu::CameraWithGameObjectController");

	CameraWithGameObjectController::CameraWithGameObjectController(const std::string& name, Ogre::Camera *pCamera, GameObject *pGameObject) 
		: MoveableObjectController(name, 20.0f, 20.0f, 0.25f, 0.25f), mpCamera(pCamera), mpGameObject(pGameObject)
		, mOffsetFromGameObjectCenter(Ogre::Vector3::ZERO), mDistanceFromObject(30.0f), mMinAngleBetweenCamDirectionGameObjectUp(0.0)
		, mMaxAngleBetweenCamDirectionGameObjectUp(Ogre::Math::PI)
	{
		GameActorObject *pGameActor;
		GameCharacterObject *pGameCharacter;

		pGameActor = dynamic_cast<GameActorObject*>(pGameObject);
		pGameCharacter = dynamic_cast<GameCharacterObject*>(pGameObject);
		mPreviousGameObjectPosition = Ogre::Vector3::ZERO;
		if (pGameActor != NULL)
		{
			mPreviousGameObjectPosition = pGameActor->getGlobalPosition() + mOffsetFromGameObjectCenter;

			// Set the initial camera orientation
			pCamera->setDirection(pGameActor->getGlobalForwardVector());
		}
		else if (pGameCharacter != NULL)
		{
			mPreviousGameObjectPosition = pGameCharacter->getGlobalPosition() + mOffsetFromGameObjectCenter;

			// Set the initial camera orientation
			pCamera->setDirection(pGameCharacter->getGlobalForwardVector());
		}
	}

	CameraWithGameObjectController::~CameraWithGameObjectController()
	{
	}

	void CameraWithGameObjectController::setGameObject(GameObject *pGameObject)
	{
		GameActorObject *pGameActor;
		GameCharacterObject *pGameCharacter;

		Poco::ScopedRWLock lock(rwLock, true);

		mpGameObject = pGameObject;

		pGameActor = dynamic_cast<GameActorObject*>(mpGameObject);
		pGameCharacter = dynamic_cast<GameCharacterObject*>(mpGameObject);
		mPreviousGameObjectPosition = Ogre::Vector3::ZERO;
		if (pGameActor != NULL)
		{
			mPreviousGameObjectPosition = pGameActor->getGlobalPosition() + mOffsetFromGameObjectCenter;

			// Set the initial camera orientation
			mpCamera->setDirection(pGameActor->getGlobalForwardVector());
		}
		else if (pGameCharacter != NULL)
		{
			mPreviousGameObjectPosition = pGameCharacter->getGlobalPosition() + mOffsetFromGameObjectCenter;

			// Set the initial camera orientation
			mpCamera->setDirection(pGameCharacter->getGlobalForwardVector());
		}
	}

	void CameraWithGameObjectController::update(unsigned long timeDelta)
	{
		GameActorObject *pGameActor;
		GameCharacterObject *pGameCharacter;
		std::list<std::pair<ActionEntry, Poco::AutoPtr<InputMessage> > >::const_iterator iter;
		std::map<std::string, std::map<int, int> >::iterator prevPosIter;
		std::map<int, int>::iterator axisIter;
		Ogre::Vector3 cameraPosition;
		Ogre::Quaternion cameraOrientation;
		Ogre::Vector3 cameraUp;
		Ogre::Vector3 cameraRight;
		Ogre::Vector3 cameraDirection;
		Ogre::Vector3 gameObjectPosition;
		Ogre::Quaternion gameObjectOrientation;
		Ogre::Vector3 moveDirection;
		Ogre::Matrix3 rotationMatrix;
		Ogre::Vector3 objectDisplacement;
		Ogre::Real distance;
		Ogre::Real moveDistance;
		Ogre::Real deltaTimeInSeconds;
		bool didRotate;

		//mRotationSpeed = 0.01;

		MoveableObjectController::update(timeDelta);

		pGameActor = dynamic_cast<GameActorObject*>(mpGameObject);
		pGameCharacter = dynamic_cast<GameCharacterObject*>(mpGameObject);
		gameObjectPosition = Ogre::Vector3::ZERO;
		rotationMatrix = Ogre::Matrix3::IDENTITY;
		if (pGameActor != NULL)
		{
			gameObjectPosition = pGameActor->getGlobalPosition();
			gameObjectOrientation = pGameActor->getGlobalOrientation();
			gameObjectOrientation.ToRotationMatrix(rotationMatrix);
		}
		else if (pGameCharacter != NULL)
		{
			gameObjectPosition = pGameCharacter->getGlobalPosition();
			gameObjectOrientation = pGameCharacter->getGlobalOrientation();
			gameObjectOrientation.ToRotationMatrix(rotationMatrix);
		}
		gameObjectPosition += rotationMatrix * mOffsetFromGameObjectCenter;

		cameraPosition = mpCamera->getDerivedPosition();
		cameraOrientation = mpCamera->getDerivedOrientation();
		cameraDirection = mpCamera->getDerivedDirection();
		cameraUp = mpCamera->getDerivedUp();
		cameraRight = mpCamera->getDerivedRight();
		deltaTimeInSeconds = static_cast<Ogre::Real>(timeDelta) / MICROSECONDS_IN_SECOND;

		// if mDistanceFromObject is zero, we lock the camera to always be at the gameObjectPosition + offset
		if (mDistanceFromObject != 0)
		{
			// Get the distance between the camera and the tracked object
			distance = cameraPosition.distance(gameObjectPosition);
			// The direction the camera should move in
			// The camera must move in the direction the object is moving in, but it must also move toward the object if it is farther
			// away than mDistanceFromObject
			// Thus we check whether the object is moving and construct a displacement vector for its movement
			// we also construct a vector for moving the camera toward the object
			// If the distance between the camera and object is not mDistanceFromObject we add the two vectors together to form
			// the resultant camera displacement vector, otherwise we just use the objectDisplacement vector
			objectDisplacement = gameObjectPosition - mPreviousGameObjectPosition;
			moveDirection = Ogre::Vector3::ZERO;
			if (objectDisplacement.length() < mMovementAcceleration * 0.001f)
			{
				objectDisplacement = Ogre::Vector3::ZERO;
				moveDirection = gameObjectPosition - cameraPosition;
			}
			else
			{
				moveDirection = objectDisplacement;
			}
			// Normalise the camera displacement vector
			moveDirection.normalise();
			// Move the camera
			if ((distance - mDistanceFromObject > mMovementAcceleration * 0.1f) || (objectDisplacement == Ogre::Vector3::ZERO))
			{
				// Here we are accelerating or decelerating, but we are moving closer to the object
				// This case is also used when we have to take the object displacement into account
				if ((mMovementSpeed == 0) || (mMovementSpeed / mMovementAcceleration < objectDisplacement.length() / mMovementSpeed) || (mMovementSpeed / mMovementAcceleration < (distance - mDistanceFromObject) / mMovementSpeed))
				{
					moveDistance = mMovementSpeed * deltaTimeInSeconds + 0.5f * mMovementAcceleration * deltaTimeInSeconds * deltaTimeInSeconds;
					mMovementSpeed += mMovementAcceleration * deltaTimeInSeconds;
				}
				else
				{
					moveDistance = mMovementSpeed * deltaTimeInSeconds - 0.5f * mMovementAcceleration * deltaTimeInSeconds * deltaTimeInSeconds;
					mMovementSpeed -= mMovementAcceleration * deltaTimeInSeconds;
				}
			}
			else if (distance - mDistanceFromObject < -mMovementAcceleration * 0.1f)
			{
				// Accelerate or decelerate, moving away from the object
				if ((mMovementSpeed == 0) || (mMovementSpeed / -mMovementAcceleration < (distance - mDistanceFromObject) / mMovementSpeed))
				{
					moveDistance = mMovementSpeed * deltaTimeInSeconds - 0.5f * mMovementAcceleration * deltaTimeInSeconds * deltaTimeInSeconds;
					mMovementSpeed += -mMovementAcceleration * deltaTimeInSeconds;
				}
				else
				{
					moveDistance = mMovementSpeed * deltaTimeInSeconds + 0.5f * mMovementAcceleration * deltaTimeInSeconds * deltaTimeInSeconds;
					mMovementSpeed -= -mMovementAcceleration * deltaTimeInSeconds;
				}
			}
			else
			{
				mMovementSpeed = 0.0f;
				moveDistance = 0.0f;
			}

			// Ensure that the camera does not exceed its maximum speed
			if (mMovementSpeed > mMaxMovementSpeed)
			{
				mMovementSpeed = mMaxMovementSpeed;
			}
			else if (mMovementSpeed < -mMaxMovementSpeed)
			{
				mMovementSpeed = -mMaxMovementSpeed;
			}

			// Move the camera closer to the object
			cameraPosition += moveDirection * moveDistance;
		}
		else
		{
			cameraPosition = gameObjectPosition;
		}

		didRotate = false;
		// Process the queue of actions and transform the camera as appropriate
		for (iter = mQueueOfActionsToPerform.begin(); iter != mQueueOfActionsToPerform.end(); ++iter)
		{
			// Get the CameraAction and the associated InputMessage that was received 
			ActionEntry actionEntry = iter->first;
			const InputMessage* message = iter->second;
			CameraAction cameraAction = actionEntry.first;
			int axis = actionEntry.second;
			Ogre::Real delta;

			delta = mRotationSpeed * deltaTimeInSeconds + 0.5f * mRotationAcceleration * deltaTimeInSeconds * deltaTimeInSeconds;

			if ((axis >= 0) && (message->getDeviceAction() == InputMessage::DA_MOVE))
			{
				prevPosIter = mPrevAxisPositions.find(message->getInputIdentifier(0));
				if (prevPosIter != mPrevAxisPositions.end())
				{
					axisIter = prevPosIter->second.find(axis);
					if (axisIter != prevPosIter->second.end())
					{
						//delta = static_cast<Ogre::Real>((-axisIter->second + message->getDeviceState(static_cast<unsigned int>(axis))));
						delta = static_cast<Ogre::Real>((message->getDeviceState(static_cast<unsigned int>(axis)))) * mMaxRotationSpeed / 628;
					}
				}
			}
			else
			{
				continue;
			}

			switch (cameraAction)
			{
				case CA_PITCH:
					{
						Ogre::Vector3 tempCameraDirection;
						Ogre::Real angle;

						// Rotate the camera with the position of the GameObject as origin, around the camera's right direction
						Ogre::Quaternion(Ogre::Radian(-delta), cameraRight).ToRotationMatrix(rotationMatrix);
						tempCameraDirection = rotationMatrix * cameraDirection;
						if (pGameActor != NULL)
						{
							angle = tempCameraDirection.angleBetween(pGameActor->getGlobalUpVector()).valueDegrees();
						}
						else if (pGameCharacter != NULL)
						{
							angle = tempCameraDirection.angleBetween(pGameCharacter->getGlobalUpVector()).valueDegrees();
						}

						if ((angle >= mMinAngleBetweenCamDirectionGameObjectUp.valueDegrees()) && (angle <= mMaxAngleBetweenCamDirectionGameObjectUp.valueDegrees()))
						{
							cameraDirection = tempCameraDirection;
							cameraPosition -= gameObjectPosition;
							cameraPosition = rotationMatrix * cameraPosition;
							cameraPosition += gameObjectPosition;
						}
						didRotate = true;
					}
					break;
				case CA_YAW:
					// Rotate the camera with the position of the GameObject as origin, around the camera's up direction
					cameraPosition -= gameObjectPosition;
					// Do not use the camera up here
					Ogre::Quaternion(Ogre::Radian(-delta), mpGameObject->getGlobalUpVector().normalisedCopy()).ToRotationMatrix(rotationMatrix);
					cameraPosition = rotationMatrix * cameraPosition;
					cameraDirection = rotationMatrix * cameraDirection;
					cameraPosition += gameObjectPosition;
					didRotate = true;
					break;
				case CA_ROLL:
					break;
				default:
					// log a warning
					LOG(EngineLog::LM_WARNING, "CameraWithGameObjectController::update(): unknown CameraAction");
			}
		}

		// If the camera is rotating we have to update the rotation speed by using the rotation acceleration and the time delta
		// If we are no longer receiving commands to rotate we must decelerate the rotation of the camera
		// We always ensure the rotation speed does not go above the maximum set rotation speed
		if (didRotate)
		{
			mRotationSpeed += mRotationAcceleration * deltaTimeInSeconds;
			if (mRotationSpeed > mMaxRotationSpeed)
			{
				mRotationSpeed = mMaxRotationSpeed;
			}
		}
		else if (mRotationSpeed > 0)
		{
			mRotationSpeed -= mRotationAcceleration * deltaTimeInSeconds;
			if (mRotationSpeed < 0)
			{
				mRotationSpeed = 0;
			}
		}

		// Set the final position of the camera
		mpCamera->setPosition(cameraPosition);
		if (mDistanceFromObject == 0)
		{
			mpCamera->setDirection(cameraDirection);
		}
		else
		{
			mpCamera->lookAt(gameObjectPosition);
		}

		// Update the previous positions of the axes associated with the input devices to their current positions
		for (iter = mQueueOfActionsToPerform.begin(); iter != mQueueOfActionsToPerform.end(); ++iter)
		{
			ActionEntry actionEntry = iter->first;
			const InputMessage* message = iter->second;
			int axis = actionEntry.second;

			if ((axis >= 0) && (message->getDeviceAction() == InputMessage::DA_MOVE))
			{
				mPrevAxisPositions[message->getInputIdentifier(0)][axis] = message->getDeviceState(axis);
			}
		}

		mQueueOfActionsToPerform.clear();

		mPreviousGameObjectPosition = gameObjectPosition;
	}

	void CameraWithGameObjectController::bind(CameraAction cameraAction, const std::string& inputActionStr, int axis)
	{
		if (cameraAction == CA_UNKNOWN)
		{
			return;
		}

		Poco::ScopedRWLock lock(rwLock, false);

		// Add the entry to the map
		mInputActionToCameraActionMap.insert(InputActionToCameraActionMapEntry(inputActionStr, ActionEntry(cameraAction, axis)));

		// Set up the callback function in the InputActionManager
		InputActionManager::getSingleton().addInputActionCallback<CameraWithGameObjectController>(inputActionStr, this, &CameraWithGameObjectController::processInputAction);
	}

	bool CameraWithGameObjectController::unBind(const std::string& inputActionStr)
	{
		std::pair<InputActionToCameraActionMapIterator, InputActionToCameraActionMapIterator> range;

		if (mInputActionToCameraActionMap.erase(inputActionStr) == 0)
		{
			return false;
		}

		// TODO remove the input action from the InputActionManager
		
		return true;
	}

	void CameraWithGameObjectController::processInputAction(InputMessage *message)
	{
		std::pair<InputActionToCameraActionMapConstIterator, InputActionToCameraActionMapConstIterator> range;
		InputActionToCameraActionMapConstIterator iter;

		// If the message is NULL, log a warning and exit the function
		if (message == NULL)
		{
			LOG(EngineLog::LM_WARNING, "CameraWithGameObjectController::processInputAction(): message is NULL!");
			return;
		}

		Poco::ScopedRWLock lock(rwLock, false);

		range = mInputActionToCameraActionMap.equal_range(message->getInputAction());

		for (iter = range.first; iter != range.second; ++iter)
		{
			ActionEntry actionEntry = iter->second;
			
			// Enqueue the action to be performed during update
			mQueueOfActionsToPerform.push_back(std::pair<ActionEntry, InputMessage*>(actionEntry, message->clone()));
		}
	}

} // namespace Myoushu

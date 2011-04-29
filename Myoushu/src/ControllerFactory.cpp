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
 * @file ControllerFactory.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "ControllerFactory.h"
#include "ControllerTaskManager.h"

namespace Myoushu
{
	ControllerFactory::ControllerFactory()
	{
		// Register this object factory as the creator of GameCharacterObjectController
		registerObjectFactory(NamedObject<GameCharacterObjectController>::getStaticClassName(), this);
	}

	ControllerFactory::~ControllerFactory()
	{
	}

	GameCharacterObjectController* ControllerFactory::make(const std::string& name) throw (Exception)
	{
		GameCharacterObjectController *controller;

		controller = new GameCharacterObjectController(ensureUniqueName(name), NULL);

		add(controller);

		return controller;
	}

	Controller* ControllerFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		if (className == NamedObject<GameCharacterObjectController>::getStaticClassName())
		{
			return make(name);
		}
		else if (className == NamedObject<CameraWithGameObjectController>::getStaticClassName())
		{
			return make(name, NULL, NULL);
		}
		else
		{
			throw Exception(Exception::E_NULL_POINTER, "ControllerFactory::make(): " + className + " cannot be instantiated by this factory.");
		}

		return NULL;
	}

	GameCharacterObjectController* ControllerFactory::make(const Ogre::String& name, GameCharacterObject *character) throw (Exception)
	{
		GameCharacterObjectController *controller;

		controller = new GameCharacterObjectController(ensureUniqueName(name), character);

		add(controller);

		return controller;
	}

	CameraWithGameObjectController* ControllerFactory::make(const Ogre::String& name, Ogre::Camera *pCamera, GameObject *pGameObject) throw (Exception)
	{
		CameraWithGameObjectController *controller;

		controller = new CameraWithGameObjectController(ensureUniqueName(name), pCamera, pGameObject);

		add(controller);

		return controller;
	}

	void ControllerFactory::makeGameCharacterObjectCameraControllerPair(const Ogre::String& cameraControllerName, const Ogre::String& characterControllerName
		, GameCharacterObject *pCharacter, Ogre::Camera *pCamera, const Ogre::String& moveForwardAction, const Ogre::String& moveBackwardAction
		, const Ogre::String& strafeLeftAction, const Ogre::String& strafeRightAction, const Ogre::String& lookUpAction, const Ogre::String& lookDownAction
		, const Ogre::String& lookLeftAction, const Ogre::String& lookRightAction, const Ogre::String& forwardCharacterAction, const Ogre::String& backwardCharacterAction
		, const Ogre::String& strafeLeftCharacterAction, const Ogre::String& strafeRightCharacterAction, const Ogre::Vector3& cameraOffset, double cameraDistance
		, double maxMovementSpeed, double movementAcceleration, double maxRotationSpeed, double rotationAcceleration) throw (Exception)
	{
		Ogre::Vector3 moveDirection;
		Ogre::Quaternion quat;

		GameCharacterObjectController *pCharController;
		CameraWithGameObjectController *pCamController;

		// Create the GameCharacterObjectController and the CameraWithGameObjectController
		pCharController = make(characterControllerName, pCharacter);
		pCamController = make(cameraControllerName, pCamera, pCharacter);

		// Setup the camera controller using the given arguments
		pCamController->bind(Myoushu::CameraWithGameObjectController::CA_YAW, lookRightAction, Myoushu::InputMessage::DS_X_REL_INDEX);
		pCamController->bind(Myoushu::CameraWithGameObjectController::CA_PITCH, lookUpAction, Myoushu::InputMessage::DS_Y_REL_INDEX);
		pCamController->setOffsetFromGameObjectCenter(cameraOffset);
		pCamController->setDistanceFromObject(cameraDistance);
		pCamController->setMaxRotationSpeed(maxRotationSpeed);
		pCamController->setRotationAcceleration(rotationAcceleration);
		pCamController->setMaxMovementSpeed(maxMovementSpeed);
		pCamController->setMovementAcceleration(movementAcceleration);

		pCamController->setMinAngleBetweenCamDirectionGameObjectUp(Ogre::Radian(Ogre::Math::PI / 4.0));
		pCamController->setMaxAngleBetweenCamDirectionGameObjectUp(Ogre::Radian(3.0 * Ogre::Math::PI / 4.0));

		// Setup the character controller
		//moveDirection.x = 0;
		//moveDirection.y = 0;
		//moveDirection.z = -1;
		moveDirection = pCharacter->getLocalForwardVector();
		pCharController->bind(moveForwardAction, forwardCharacterAction, moveDirection);

		pCharController->bind(moveBackwardAction, backwardCharacterAction, -moveDirection);

		//moveDirection.x = -1;
		//moveDirection.z = 0;
		quat.FromAngleAxis(Ogre::Radian(Ogre::Math::PI / 2.0), pCharacter->getLocalUpVector());
		pCharController->bind(strafeLeftAction, strafeLeftCharacterAction, quat * moveDirection);

		//moveDirection.x = 1;
		//moveDirection.y = 0;
		pCharController->bind(strafeRightAction, strafeRightCharacterAction, quat * -moveDirection);
		//moveDirection.x = 0;
		//moveDirection.y = 1;
		moveDirection = pCharacter->getLocalUpVector();
		pCharController->bind(lookRightAction, "", Ogre::Vector3::ZERO, -moveDirection, Myoushu::InputMessage::DS_X_REL_INDEX, true);

		// Link the controllers
		pCamController->linkSpeedsWith(pCharController);

		// Add the controllers to the ControllerTask
		ControllerTaskManager& controllerTaskManager = ControllerTaskManager::getSingleton();

		controllerTaskManager.addController(pCamController);
		controllerTaskManager.addController(pCharController);
	}

	bool ControllerFactory::destroy(Controller *pController) throw (Exception)
	{
		bool removed;

		if (pController == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ControllerFactory::destroy(): pController is NULL.");
		}

		return remove(pController);
	}

	bool ControllerFactory::destroy(const std::string& name) throw (Exception)
	{
		Controller *pController = find(name);

		if (pController == NULL)
		{
			return false;
		}

		return remove(pController);
	}

} // Myoushu

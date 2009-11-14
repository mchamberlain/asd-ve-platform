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
 * @file ControllerFactory.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef CONTROLLER_FACTORY_H
#define CONTROLLER_FACTORY_H

#include "NamedObjectFactory.h"
#include "Controller.h"
#include "GameCharacterObjectController.h"
#include "CameraWithGameObjectController.h"
#include "Singleton.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * An ObjectFactory implementation for creating Controller instances.
	 */
	class MYOUSHU_API ControllerFactory : public NamedObjectFactory<Controller>, public Ogre::Singleton<ControllerFactory>
	{
		public:
			/** Nullary Constructor */
			ControllerFactory();

			/** Destructor */
			virtual ~ControllerFactory();

			/**
			 * Creates a GameCharacterObjectController instance without specifying a character to control.
			 * @param name The name to use for the Controller.
			 */
			virtual GameCharacterObjectController* make(const std::string& name) throw (Exception);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual Controller* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Creates a GameCharacterObjectController instance.
			 * @param name The name to use for the Controller.
			 * @param character The GameCharacterObject instance that will be controlled by the created Controller instance.
			 */
			GameCharacterObjectController* make(const Ogre::String& name, GameCharacterObject *character) throw (Exception);

			/**
			 * Creates a new CameraWithGameObjectController instance.
			 * @param name The unique name for this controller.
			 * @param pCamera The Ogre::Camera that will be controlled by this controller.
			 * @param pGameObject The GameObject instance that will be tracked by the camera.
			 */
			CameraWithGameObjectController* make(const Ogre::String& name, Ogre::Camera *pCamera, GameObject *pGameObject) throw (Exception);

			/**
			 * This function creates a GameCharacterObjectController and CameraWithGameObjectController pair for controlling a GameObjectCharacter and
			 * a first or third person camera. The controllers are added to the ControllerTask.
			 * @param cameraControllerName The name of the CameraWithGameObjectController that will be created.
			 * @param characterControllerName The name of the GameCharacterObjectController that will be create.
			 * @param pCharacter The GameCharacterObject to be controlled by these controllers.
			 * @param pCamera The Ogre::Camera instance to be controlled by the CameraWithGameObjectController that will be created.
			 * @param moveForwardAction The input action string that should cause the character to move forward.
			 * @param moveBackwardAction The input action string that should cause the character to move backward.
			 * @param strafeLeftAction The input action string that should cause the character to strafe left.
			 * @param strafeRightAction The input action string that should cause the character to strafe right.
			 * @param lookUpAction The input action string that should cause the camera to pitch up.
			 * @param lookDownAction The input action string that should cause the camera to pitch down.
			 * @param lookLeftAction The input action string that should cause the camera to yaw to the left.
			 * @param lookRightAction The input action string that should cause the camera to yaw to the right.
			 * @param forwardCharacterAction The character action to fire (for instance playing an animation) when the character is moving forward.
			 * @param backwardCharacterAction The character action to fire (for instance playing an animation) when the character is moving backward.
			 * @param strafeLeftCharacterAction The character action to fire (for instance playing an animation) when the character is strafing left.
			 * @param strafeRightCharacterAction The character action to fire (for instance playing an animation) when the character is strafing right.
			 * @param cameraOffset The vector is added to the center of the GameCharacterObject to determine the point at which the camera looks.
			 * @param cameraDistance The distance the camera should stay away from the point defined by cameraOffset.
			 * @param maxMovementSpeed The maximum speed the character/camera can move at.
			 * @param movementAcceleration The movement acceleration of the character/camera.
			 * @param maxRotationSpeed The maximum rotation speed of the character/camera.
			 * @param rotationAcceleration The rotation acceleration of the character/camera.
			 * @throws Exception::E_NULL_POINTER if pCharacter or pCamera is NULL.
			 */
			void makeGameCharacterObjectCameraControllerPair(const Ogre::String& cameraControllerName, const Ogre::String& characterControllerName
				, GameCharacterObject *pCharacter, Ogre::Camera *pCamera, const Ogre::String& moveForwardAction, const Ogre::String& moveBackwardAction
				, const Ogre::String& strafeLeftAction, const Ogre::String& strafeRightAction, const Ogre::String& lookUpAction, const Ogre::String& lookDownAction
				, const Ogre::String& lookLeftAction, const Ogre::String& lookRightAction, const Ogre::String& forwardCharacterAction = ""
				, const Ogre::String& backwardCharacterAction = "", const Ogre::String& strafeLeftCharacterAction = "", const Ogre::String& strafeRightCharacterAction = ""
				, const Ogre::Vector3& cameraOffset = Ogre::Vector3::ZERO, double cameraDistance = 0, double maxMovementSpeed = 20.0
				, double movementAcceleration = 20.0, double maxRotationSpeed = 0.15, double rotationAcceleration = 0.15) throw (Exception);

			/**
			 * Remove the specified controller from the factory and destroy it.
			 * @param pController Pointer to the Controller instance to destroy.
			 * @throws Exception::E_NULL_POINTER if pController is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if pController is not managed by this factory.
			 */
			bool destroy(Controller *pController) throw (Exception);

			/**
			 * Remove the specified controller from the factory and destroy it.
			 * @param name The name of the Controller instance to destroy.
			 * @throws Exception::E_NO_SUCH_ELEMENT if a Controller instance with the specified name could
			 *										be found.
			 */
			bool destroy(const std::string& name) throw (Exception);
	};
} // Myoushu

#endif

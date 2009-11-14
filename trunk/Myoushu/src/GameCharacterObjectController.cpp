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
 * @file GameCharacterObjectController.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include <algorithm>

#include "GameCharacterObjectController.h"
#include "Constants.h"
#include "InputActionManager.h"
#include "EngineLog.h"
#include "GameObjectFactory.h"
#include "NetworkManager.h"
#include "ControllerTaskManager.h"

namespace Myoushu
{
	CLASS_NAME(GameCharacterObjectController, "Myoushu::GameCharacterObjectController");

	GameCharacterObjectController::GameCharacterObjectController() : MoveableObjectController(""), character(NULL)
		, movementDirection(Ogre::Vector3::ZERO), negationVector(Ogre::Vector3::ZERO)
	{
	}

	GameCharacterObjectController::GameCharacterObjectController(const Ogre::String& name, GameCharacterObject* character) throw (Exception) 
		: MoveableObjectController(name), character(character), movementDirection(Ogre::Vector3::ZERO), negationVector(Ogre::Vector3::ZERO)
	{
		if (character != NULL)
		{
			character->setMovementVectorController(this);
		}
	}

	GameCharacterObjectController::GameCharacterObjectController(const Ogre::String& name, GameCharacterObject* character
		, Ogre::Real maxMovementSpeed, Ogre::Real movementAcceleration, Ogre::Real maxRotationSpeed
		, Ogre::Real rotationAcceleration) throw (Exception) : MoveableObjectController(name, maxMovementSpeed, movementAcceleration
		, maxRotationSpeed, rotationAcceleration), character(character), movementDirection(Ogre::Vector3::ZERO)
		, negationVector(Ogre::Vector3::ZERO)
	{
		if (character != NULL)
		{
			character->setMovementVectorController(this);
		}
	}
				
	GameCharacterObjectController::~GameCharacterObjectController()
	{
		inputActionBindings.clear();
	}

	void GameCharacterObjectController::stop()
	{
		MoveableObjectController::stop();

		Poco::ScopedRWLock lock(rwLock, false);

		movementDirection = Ogre::Vector3::ZERO;
		negationVector = Ogre::Vector3::ZERO;
	}

	void GameCharacterObjectController::bind(const Ogre::String& inputAction, const Ogre::String& characterAction
		, const Ogre::Vector3& direction, const Ogre::Vector3& rotationAxis, int deviceAxis, bool once)
	{
		GameCharacterObjectControllerBinding *binding;
		Ogre::Vector3 normDirection;
		InputActionBindingsMapRange range;
		InputActionBindingsMap::iterator iter;

		// First we need to check if there is a duplicate entry in the map. If there is we do not add the new entry, if there
		// is not one we add a new entry.
		range = inputActionBindings.equal_range(inputAction);

		normDirection = direction;
		normDirection.normalise();

		for (iter = range.first; iter != range.second; ++iter)
		{
			binding = iter->second;

			if ((binding->getCharacterAction() == characterAction) && (binding->getDirection() == normDirection) 
				&& (binding->isOnce() == once) && (binding->getRotationAxis() == rotationAxis) && (binding->getDeviceAxis() == deviceAxis))
			{
				// Match found, we do not create a new entry
				return;
			}
		}

		// No match found, create a new entry
		binding = new GameCharacterObjectControllerBinding(inputAction, characterAction, normDirection, rotationAxis, deviceAxis, once);
		// Register the callback for the input action
		InputActionManager::getSingleton().addInputActionCallback(inputAction, this, &GameCharacterObjectController::processInputAction);

		// Insert the entry into the multi map
		inputActionBindings.insert(InputActionBindingsMapEntry(inputAction, binding));
	}

	void GameCharacterObjectController::bind(const Ogre::String& inputAction, const Ogre::String& characterAction, bool once)
	{
		Ogre::Vector3 direction;

		direction = Ogre::Vector3::ZERO;
		bind(inputAction, characterAction, direction, Ogre::Vector3::ZERO, -1, once);
	}

	void GameCharacterObjectController::processInputAction(InputMessage *message)
	{
		GameCharacterObjectControllerBinding *binding;
		InputActionBindingsMapRange range;
		InputActionBindingsMap::iterator iter;
		std::list<Ogre::Vector3>::iterator rotationsIter;
		std::map<std::string, std::map<int, int> >::const_iterator previousAxisPositionIter;
		std::map<int, int>::const_iterator deviceAxisDeltaIter;
		int delta;

		// Log a warning if the message is NULL and return from the function
		if (message == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameCharacterObjectController::processInputAction(): message is NULL!");
			return;
		}

		if (!isEnabled())
		{
			return;
		}

		// Acquire a write lock on the data structures of this instance
		Poco::ScopedRWLock lock(rwLock, true);

		// Get any bindings defined for the current input action
		range = inputActionBindings.equal_range(message->getInputAction());

		for (iter = range.first; iter != range.second; ++iter)
		{
			binding = iter->second;
			delta = 1;
			if (message->getDeviceAction() == InputMessage::DA_PRESS)
			{
				movementDirection += binding->getDirection();
				actionsToStart.push_back(binding->getCharacterAction());

				if (binding->isOnce())
				{
					negationVector += binding->getDirection();
					if (binding->getRotationAxis() != Ogre::Vector3::ZERO)
					{
						onceOffRotationAxisList.push_back(std::pair<Ogre::Vector3, int>(binding->getRotationAxis(), 1));
					}
				}
				else
				{
					if (binding->getRotationAxis() != Ogre::Vector3::ZERO)
					{
						rotationAxisList.push_back(binding->getRotationAxis());
					}
				}
			}
			else if (message->getDeviceAction() == InputMessage::DA_RELEASE)
			{
				if (!binding->isOnce())
				{
					actionsToStop.push_back(binding->getCharacterAction());
					movementDirection -= binding->getDirection();

					// Find the persitant rotation and remove it
					if (binding->getRotationAxis() != Ogre::Vector3::ZERO)
					{
						rotationsIter = std::find(rotationAxisList.begin(), rotationAxisList.end(), binding->getRotationAxis());
						if (rotationsIter != rotationAxisList.end())
						{
							rotationAxisList.erase(rotationsIter);
						}
					}
				}
			}
			else if (message->getDeviceAction() == InputMessage::DA_MOVE)
			{
				movementDirection += binding->getDirection();
				actionsToStart.push_back(binding->getCharacterAction());

				if (binding->isOnce())
				{
					delta = 0;
					if (binding->getDeviceAxis() >= 0)
					{
						//previousAxisPositionIter = previousAxisPositions.find(message->getInputIdentifier(0));
						//if (previousAxisPositionIter != previousAxisPositions.end())
						//{
						//	deviceAxisDeltaIter = previousAxisPositionIter->second.find(binding->getDeviceAxis());
						//	if (deviceAxisDeltaIter != previousAxisPositionIter->second.end())
						//	{
						//		delta = message->getDeviceState(binding->getDeviceAxis()) - deviceAxisDeltaIter->second;
						//	}
						//}
						//// Update the previous axis positions
						//previousAxisPositions[message->getInputIdentifier(0)][binding->getDeviceAxis()] = message->getDeviceState(binding->getDeviceAxis());
						delta = message->getDeviceState(binding->getDeviceAxis());
					}
					negationVector += binding->getDirection();

					if ((binding->getRotationAxis() != Ogre::Vector3::ZERO) && (delta != 0))
					{
						onceOffRotationAxisList.push_back(std::pair<Ogre::Vector3, int>(binding->getRotationAxis(), delta));
					}
				}
			}
		}
	}

	void GameCharacterObjectController::move(NxVec3 &out, NxVec3 &moveVector, NxQuat &direction, NxVec3 &g, float t, NxOgre::Character* character)
	{
		// TODO: Non NX_Y directions.
		NxVec3 velocityDirection;
		
		if (!moveVector.isZero())
		{
			velocityDirection = direction.rot(moveVector);
			velocityDirection.normalize();
		}
		else
		{
			velocityDirection.zero();
		}

		//out = ((direction.rot(moveVector) * 1.5) + g) * t;
		out = velocityDirection * mMovementSpeed * t + 0.5 * (velocityDirection * mMovementAcceleration + g) * t * t;

		mMovementSpeed += mMovementAcceleration * t;
		if (mMovementSpeed > mMaxMovementSpeed)
		{
			mMovementSpeed = mMaxMovementSpeed;
		}

		if (moveVector.isZero())
		{
			mMovementSpeed = 0;
		}
	}

	void GameCharacterObjectController::update(unsigned long timeDelta)
	{
		std::list<Ogre::String>::const_iterator iter;
		std::list<std::pair<Ogre::Vector3, int> >::const_iterator onceOffRotationsIter;
		std::list<Ogre::Vector3>::const_iterator rotationsIter;
		Ogre::Real timeDeltaInSec;

		//mRotationSpeed = 0.01;

		if (!isEnabled())
		{
			return;
		}

		MoveableObjectController::update(timeDelta);

		// Do not run this update step if there is no associated character
		if (character == NULL)
		{
			return;
		}

		timeDeltaInSec = static_cast<Ogre::Real>(timeDelta) / static_cast<Ogre::Real>(MICROSECONDS_IN_SECOND);

		// Due to rounding errors we assume any vector with squared length less than 0.0000001 to be zero. */
		if (movementDirection.squaredLength() < 0.0000001)
		{
			movementDirection = Ogre::Vector3::ZERO;
		}

		// Set the movement direction for the character
		character->setMovementDirection(movementDirection);

		// Negate the once off or completed actions from the movementDirection
		movementDirection -= negationVector;
		// Clear the negation vector
		negationVector = Ogre::Vector3::ZERO;

		// Process once-off rotations
		Ogre::Matrix3 characterOrientation;
		character->getNode()->getOrientation().ToRotationMatrix(characterOrientation);

		for (onceOffRotationsIter = onceOffRotationAxisList.begin(); onceOffRotationsIter != onceOffRotationAxisList.end(); ++onceOffRotationsIter)
		{
			Ogre::Matrix3 rotation;
			
			Ogre::Quaternion(Ogre::Radian(static_cast<Ogre::Real>(onceOffRotationsIter->second) * mMaxRotationSpeed / 628.0), onceOffRotationsIter->first).ToRotationMatrix(rotation);
			characterOrientation = rotation * characterOrientation;
		}

		for (rotationsIter = rotationAxisList.begin(); rotationsIter != rotationAxisList.end(); ++rotationsIter)
		{
			Ogre::Matrix3 rotation;
			
			Ogre::Quaternion(Ogre::Radian(mRotationSpeed * timeDeltaInSec + 0.5f * mRotationAcceleration * timeDeltaInSec * timeDeltaInSec), *rotationsIter).ToRotationMatrix(rotation);
			characterOrientation = rotation * characterOrientation;
		}

		character->getNode()->setOrientation(characterOrientation);
		character->setDirection(Ogre::Quaternion(characterOrientation));

		if ((!onceOffRotationAxisList.empty()) || (!rotationAxisList.empty()))
		{
			mRotationSpeed += mRotationAcceleration * timeDeltaInSec;
			if (mRotationSpeed > mMaxRotationSpeed)
			{
				mRotationSpeed = mMaxRotationSpeed;
			}
		}
		else if (mRotationSpeed > 0)
		{
			mRotationSpeed -= mRotationAcceleration * timeDeltaInSec;
			if (mRotationSpeed < 0)
			{
				mRotationSpeed = 0;
			}
		}

		onceOffRotationAxisList.clear();

		// Start character actions
		for (iter = actionsToStart.begin(); iter != actionsToStart.end(); ++iter)
		{
			character->startAction(*iter);
		}
		actionsToStart.clear();
		// Stop some character actions
		for (iter = actionsToStop.begin(); iter != actionsToStop.end(); ++iter)
		{
			character->stopAction(*iter);
		}
		actionsToStop.clear();

	}

	memUInt GameCharacterObjectController::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;
		InputActionBindingsMap::const_iterator iter;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectController::serialize(): buffer is NULL!");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// First serialize using the parent class' method
		writtenSize = MoveableObjectController::serialize(pBuf, size, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;

		// Write the name of the character, when populating the GameObjectFactory can be used to get the correct pointer
		if (character != NULL)
		{
			if (sTarget == ST_NETWORK)
			{
				writtenSize = writeString(character->getName() + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
			}
			else
			{
				writtenSize = writeString(character->getName(), pBuf);
			}
		}
		else
		{
			writtenSize = writeString("", pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
		}

		writtenSize = writeOgreVector3(movementDirection, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
		}

		writtenSize = writeOgreVector3(negationVector, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
		}

		// We skip the actions to start and actions to stop -- should not be relevant for duplicating the object
		// Lastly we have to save the input action bindings map
		// Write the number of mappings that are in the map
		writtenSize = writePrimitiveType(inputActionBindings.size(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
		}

		// Iterate over the entries in the map and write out the strings and serialize the GameCharacterObjectControllerBinding instances
		for (iter = inputActionBindings.begin(); iter != inputActionBindings.end(); ++iter)
		{
			const GameCharacterObjectControllerBinding *binding = iter->second;

			// If the serialization is for network transmission (sTarget == ST_NETWORK) then we append the local IP to the inputAction to ensure
			// that it is unique on the target host and identifiable as belonging to this host
			if (sTarget == ST_NETWORK)
			{
				writtenSize = writeString(iter->first + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
			}
			else
			{
				writtenSize = writeString(iter->first, pBuf);
			}
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
			}

			writtenSize = binding->serialize(pBuf, size - totalSize, sTarget);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::serialize(): buffer is too small.");
			}
		}

		return totalSize;
	}

	memUInt GameCharacterObjectController::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		unsigned int numInputBindings;
		std::string characterName;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectController::populateInstance(): buffer is NULL!");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// First serialize using the parent class' method
		readSize = MoveableObjectController::populateInstance(pBuf, size, sTarget);
		pBuf += readSize;
		totalSize += readSize;

		// Read the name of the character, when populating the GameObjectFactory can be used to get the correct pointer
		readSize = readString(characterName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
		}
		// Get the GameCharacterObject instance from the object factory
		LOG(EngineLog::LM_INFO_ENGINE, "create character controller, before character " << characterName);
		character = dynamic_cast<GameCharacterObject *>(GameObjectFactory::getSingleton().findByName(characterName));
		if (character != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "create character controller, character name == " << character->getName());
			character->setMovementVectorController(this);
		}
		LOG(EngineLog::LM_INFO_ENGINE, "create character controller, after character");

		readSize = readOgreVector3(movementDirection, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
		}

		readSize = readOgreVector3(negationVector, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
		}

		// We skip the actions to start and actions to stop -- should not be relevant for duplicating the object
		// Lastly we have to save the input action bindings map
		// Read the number of mappings that are in the map
		readSize = readPrimitiveType(numInputBindings, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
		}

		// Iterate over the entries in the map and read out the strings and serialize the GameCharacterObjectControllerBinding instances
		for (unsigned int i = 0; i < numInputBindings; i++)
		{
			std::string inputActionStr;
			GameCharacterObjectControllerBinding *binding;

			inputActionStr = "";
			binding = NULL;

			readSize = readString(inputActionStr, pBuf);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
			}

			binding = new GameCharacterObjectControllerBinding();
			readSize = binding->populateInstance(pBuf, size - totalSize, sTarget);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectController::populateInstance(): buffer is too small.");
			}
			// Add the inputAction to the local InputActionManager
			// Register the callback for the input action
			InputActionManager::getSingleton().addInputActionCallback(inputActionStr, this, &GameCharacterObjectController::processInputAction);

			// Add the entry to the inputActionBindings map
			inputActionBindings.insert(InputActionBindingsMapEntry(inputActionStr, binding));
		}

		ControllerTaskManager::getSingleton().addController(this);

		return totalSize;
	}

} // Myoushu

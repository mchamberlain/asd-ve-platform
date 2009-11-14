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
 * @file GameCharacterObject.cpp
 * @author ME Chamberlain
 * @date August 2008
 */

#include "Ogre.h"

#include "GameCharacterObject.h"
#include "EngineLog.h"
#include "AnimationManager.h"

namespace Myoushu
{
	CLASS_NAME(GameCharacterObject, "Myoushu::GameCharacterObject");

	GameCharacterObject::GameCharacterObject(const Ogre::String& name, Scene *scene, NxOgre::Character *nxOgreCharacter, NxOgre::CharacterParams params) throw (Exception) 
		: GameObject(name), nxOgreCharacter(nxOgreCharacter), scene(scene)
	{
		backupCharacterParams(params);

		if ((scene == NULL) /*|| (nxOgreCharacter == NULL)*/)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObject::GameCharacterObject(): scene is NULL.");
		}
	}

	GameCharacterObject::GameCharacterObject(const Ogre::String& name, Scene* scene, NxOgre::CharacterController* characterController
		, NxOgre::Pose pose, NxOgre::CharacterParams params) : GameObject(name)
	{
		backupCharacterParams(params);

		nxOgreCharacter = new NxOgre::Character(name, scene->getNxOgreScene(), characterController, pose, params);
		this->scene = scene;
	}

	GameCharacterObject::~GameCharacterObject()
	{
		if (nxOgreCharacter != NULL)
		{
			if (scene != NULL)
			{
				this->scene->destroyCharacter(nxOgreCharacter->getName());
			}
		}
	}

	void GameCharacterObject::backupCharacterParams(const NxOgre::CharacterParams& params)
	{
		mCharacterParams.mType = params.mType;
		mCharacterParams.mDimensions = params.mDimensions;
		mCharacterParams.mUpAxis = params.mUpAxis;
		mCharacterParams.mSlopeLimit = params.mSlopeLimit;
		mCharacterParams.mStepOffset = params.mStepOffset;
		mCharacterParams.mSkinWidth = params.mSkinWidth;
		mCharacterParams.mActiveGroupsMask = params.mActiveGroupsMask;
		mCharacterParams.mSharpness = params.mSharpness;
		mCharacterParams.mGroupMask = params.mGroupMask;
	}

	memUInt GameCharacterObject::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObject::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// mCharacterParams
		writtenSize = writePrimitiveType(mCharacterParams.mType, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writeNxVec3(mCharacterParams.mDimensions, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mUpAxis, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mSlopeLimit, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mStepOffset, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mSkinWidth, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mActiveGroupsMask, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mSharpness, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		writtenSize = writePrimitiveType(mCharacterParams.mGroupMask, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// mesh name
		if ((nxOgreCharacter != NULL) && (nxOgreCharacter->getEntity() != NULL) && (nxOgreCharacter->getEntity()->getMesh().get() != NULL))
		{
			writtenSize = writeString(nxOgreCharacter->getEntity()->getMesh()->getName(), pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
		}
		else
		{
			writtenSize = writeString("", pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
		}
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// skeleton
		if ((nxOgreCharacter != NULL) && (nxOgreCharacter->getEntity() != NULL) && (nxOgreCharacter->getEntity()->getSkeleton() != NULL))
		{
			writtenSize = writeString(nxOgreCharacter->getEntity()->getSkeleton()->getName(), pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
		}
		else
		{
			writtenSize = writeString("", pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
		}
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// position
		writtenSize = writeOgreVector3(getGlobalPosition(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// orientation
		writtenSize = writeOgreQuaternion(getGlobalOrientation(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// scale
		if (getNode() != NULL)
		{
			writtenSize = writeOgreVector3(getNode()->getScale(), pBuf);
		}
		else
		{
			writtenSize = writeOgreVector3(Ogre::Vector3::ZERO, pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		// GameObject parent
		writtenSize = GameObject::serialize(pBuf, size - totalSize, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::serialize(): buffer is too small!");
		}

		return totalSize;
	}

	memUInt GameCharacterObject::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		std::string meshFile;
		std::string skeletonFile;
		Ogre::Vector3 position;
		Ogre::Vector3 scale;
		Ogre::Quaternion orientation;

		LOG(EngineLog::LM_INFO_ENGINE, "GameCharacterObject::populateInstance");

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObject::populateInstance(): buffer is NULL.");
		}

		totalSize = 0;
		readSize = 0;
		pBuf = static_cast<const char*>(pMem);

		readSize = readPrimitiveType(mCharacterParams.mType, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readNxVec3(mCharacterParams.mDimensions, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mUpAxis, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mSlopeLimit, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mStepOffset, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mSkinWidth, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mActiveGroupsMask, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mSharpness, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		readSize = readPrimitiveType(mCharacterParams.mGroupMask, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// mesh name
		readSize = readString(meshFile, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// skeleton
		readSize = readString(skeletonFile, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// position
		readSize = readOgreVector3(position, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// orientation
		readSize = readOgreQuaternion(orientation, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// scale
		readSize = readOgreVector3(scale, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		// GameObject parent
		readSize = GameObject::populateInstance(pBuf, size - totalSize, sTarget);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObject::populateInstance(): buffer is too small!");
		}

		LOG(EngineLog::LM_INFO_ENGINE, "GameCharacterObject::populateInstance name " << getName());

		if (sTarget != ST_NETWORK_UPDATE)
		{
			if (this->scene != NULL)
			{
				if (nxOgreCharacter != NULL)
				{
					this->scene->destroyCharacter(nxOgreCharacter->getName());
				}

				nxOgreCharacter = this->scene->createCharacter(this->getName(), NxOgre::Pose(position, orientation), mCharacterParams);
			}

			if (meshFile.length() > 0)
			{
				attachMesh(meshFile);
			}

			if (skeletonFile.length() > 0)
			{
				attachSkeletonMesh(skeletonFile);
			}
		}

		if (getNode() != NULL)
		{
			getNode()->setScale(scale);
		}

		if (sTarget == ST_NETWORK_UPDATE)
		{
			setPosition(position);
			setDirection(orientation);
		}

		return totalSize;
	}

	GameCharacterObjectAction* GameCharacterObject::addAction(const Ogre::String& name, bool toggleAction, const Ogre::String& animationName
		, GameCharacterObjectAction::AnimationBehaviour animBehaviour, bool restartAnimation, bool playCounter) throw (Exception)
	{
		// Create the GameCharacterObjectAction instance
		GameCharacterObjectAction *pAction = new GameCharacterObjectAction(name, this, toggleAction, animationName, animBehaviour, restartAnimation, playCounter);

		// Add it to this character instance
		GameObject::addAction(pAction);

		return pAction;
	}

	void GameCharacterObject::createNode()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		nxOgreCharacter->createNode();
	}

	void GameCharacterObject::attachMesh(const Ogre::String& meshName)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->attachMesh(meshName);
	}

	void GameCharacterObject::attachSkeletonMesh(const Ogre::String& meshName)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// not implemented by NxOgre
		//nxOgreCharacter->attachSkeletonMesh(meshName);


	}

	void GameCharacterObject::bindFeet(const Ogre::String& leftBone, const Ogre::String& rightBone)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->bindFeet(leftBone, rightBone);
	}

	void GameCharacterObject::unBindFeet()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->unBindFeet();
	}

	Ogre::Vector3 GameCharacterObject::getGlobalUpVector()
	{
		Ogre::Vector3 upVector;

		{
			Poco::ScopedRWLock lock(rwLock, false);

			switch (mCharacterParams.mUpAxis)
			{
				case NX_X:
					upVector = Ogre::Vector3::UNIT_X;
					break;
				case NX_Z:
					upVector = Ogre::Vector3::UNIT_Z;
					break;
				case NX_Y:
				default:
					upVector = Ogre::Vector3::UNIT_Y;
					break;
			}
		}

		return getGlobalOrientation() * upVector;
	}

	Ogre::Vector3 GameCharacterObject::getGlobalPosition() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return const_cast<NxOgre::Character*>(nxOgreCharacter)->getGlobalPosition();
	}

	Ogre::Quaternion GameCharacterObject::getGlobalOrientation() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return const_cast<NxOgre::Character*>(nxOgreCharacter)->getGlobalOrientation();
	}

	void GameCharacterObject::simulate(float dt)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->simulate(dt);	
	}

	void GameCharacterObject::render(float dt)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->render(dt);
	}

	void GameCharacterObject::playAnimation(const Ogre::String& animationName, bool restart, bool loop, bool playCounter)
	{
		Ogre::AnimationState *animation;
		std::map<Ogre::String, Ogre::AnimationState *>::iterator activeAnimationsIter;

		Poco::ScopedRWLock lock(rwLock, false);

		animation = nxOgreCharacter->getEntity()->getAnimationState(animationName);

		// if animation does not exist, log a warning and return
		if (animation == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameCharacterObject::playAnimation(): No such animation for this entity: " << animationName);
			return;
		}

		if (restart)
		{
			// Reset animation and set it as the current movement animation
			animation->setTimePosition(0);
		}
		animation->setLoop(loop);
		animation->setEnabled(true);

		// Play the animation
		AnimationManager::getSingleton().playAnimation(animation, loop, restart, playCounter);
	}

	void GameCharacterObject::stopAnimation(const Ogre::String& animationName, bool playCounter)
	{
		Ogre::AnimationState *animation;

		animation = nxOgreCharacter->getEntity()->getAnimationState(animationName);

		// if animation does not exist, log a warning
		if (animation == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GameCharacterObject::stopAnimation(): No such animation for this entity: " << animationName);
			return;
		}

		// Stop the animation
		AnimationManager::getSingleton().stopAnimation(animation, playCounter);
	}

	void GameCharacterObject::setDirection(const Ogre::Radian& direction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->setDirection(direction);
	}

	void GameCharacterObject::setDirection(const Ogre::Quaternion& direction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->setDirection(direction);
	}

	void GameCharacterObject::setMovementDirection(const Ogre::Vector3& direction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->setRawNextMovementDirection(NxVec3(direction.x, direction.y, direction.z));
	}

	void GameCharacterObject::setMovementVectorController(NxOgre::CharacterMovementVectorController* movementVectorController)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->setMovementVectorController(movementVectorController);
	}

	void GameCharacterObject::setPosition(const Ogre::Vector3& position)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		nxOgreCharacter->setPosition(position);
	}

	Ogre::String GameCharacterObject::getName() const
	{
		return NamedInstance::getName();
	}

	Ogre::SceneNode* GameCharacterObject::getNode()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return const_cast<NxOgre::Character*>(nxOgreCharacter)->getNode();
	}

	const Ogre::SceneNode* GameCharacterObject::getNode() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxOgreCharacter->getNode();
	}

	Ogre::Entity* GameCharacterObject::getEntity()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxOgreCharacter->getEntity();
	}

	Scene* GameCharacterObject::getScene()
	{
		Poco::ScopedRWLock lock(rwLock, false);
		
		return scene;
	}

	NxController* GameCharacterObject::getNxController()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxOgreCharacter->getNxController();
	}

	NxReal GameCharacterObject::getMass()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxOgreCharacter->getMass();
	}

} // Myoushu

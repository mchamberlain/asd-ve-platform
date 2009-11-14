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
 * @file Actor.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "Actor.h"

namespace Myoushu
{
	Actor::Actor(const NxOgre::NxString& Identifier, Scene* scene, bool isActorBased) : NxOgre::Actor(Identifier, scene->getNxOgreScene(), isActorBased), mpScene(scene)
	{
	}

	Actor::Actor(const NxOgre::NxString& Identifier, Scene* scene, NxOgre::ShapeBlueprint* blueprint, const NxOgre::Pose& pose, NxOgre::ActorParams actorParams) : NxOgre::Actor(Identifier, scene->getNxOgreScene(), blueprint, pose, actorParams), mpScene(scene)
	{
	}

	Actor::~Actor()
	{
	}

	memUInt Actor::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Actor::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// Serialize the actor parameters
		writtenSize = writePrimitiveType(mActorParams.mDensity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mActorFlags, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mGroupAsIndex, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeString(mActorParams.mGroupAsName, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeNxVec3(mActorParams.mMassSpaceInertia, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeNxVec3(mActorParams.mLinearVelocity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeNxVec3(mActorParams.mAngularVelocity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mWakeUpCounter, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mMass, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mLinearDamping, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mAngularDamping, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mMaxAngularVelocity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mBodyFlags, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mSleepLinearVelocity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mSleepAngularVelocity, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mCCDMotionThreshold, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mSolverIterationCount, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mBodyFlags, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mSleepEnergyThreshold, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mSleepDamping, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeOgreVector3(mActorParams.mNodeScale, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writeString(mActorParams.mNodeName, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		writtenSize = writePrimitiveType(mActorParams.mNodeShadows, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		// Serialize the position and orientation of the actor
		// position
		writtenSize = writeOgreVector3(getGlobalPosition(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}
		// orientation
		writtenSize = writeOgreQuaternion(getGlobalOrientation(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt Actor::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Actor::populateInstance(): buffer is NULL.");
		}

		totalSize = 0;
		readSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// Serialize the actor parameters
		readSize = readPrimitiveType(mActorParams.mDensity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mActorFlags, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mGroupAsIndex, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readString(mActorParams.mGroupAsName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readNxVec3(mActorParams.mMassSpaceInertia, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readNxVec3(mActorParams.mLinearVelocity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readNxVec3(mActorParams.mAngularVelocity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mWakeUpCounter, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mMass, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mLinearDamping, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mAngularDamping, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mMaxAngularVelocity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mBodyFlags, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mSleepLinearVelocity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mSleepAngularVelocity, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mCCDMotionThreshold, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mSolverIterationCount, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mBodyFlags, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mSleepEnergyThreshold, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mSleepDamping, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readOgreVector3(mActorParams.mNodeScale, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readString(mActorParams.mNodeName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		readSize = readPrimitiveType(mActorParams.mNodeShadows, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		// Serialize the position and orientation of the actor
		// position
		readSize = readOgreVector3(position, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}
		// orientation
		readSize = readOgreQuaternion(orientation, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Actor::populateInstance(): buffer too small.");
		}

		// create the underlying physics based actor
		_createActor(NULL, NxOgre::Pose(position, orientation), mActorParams);

		return totalSize;
	}

	//////////////////////////////////////////////////////////

	NxScene*	Actor::getNxScene()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getNxScene();
	}

	//////////////////////////////////////////////////////////

	void					Actor::simulate(float time)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::simulate(time);
	}

	void					Actor::render(float time)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::render(time);
	}

	void					Actor::shapeSimulate(float time)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::shapeSimulate(time);
	}

	void					Actor::shapeRender(float time)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::shapeRender(time);
	}

	NxOgre::Actor*							Actor::duplicate(const NxOgre::NxString& name, const NxOgre::Pose& p)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::duplicate(name, p);
	}

	//////////////////////////////////////////////////////////

	void							Actor::_createActor(NxOgre::ShapeBlueprint* blueprint,const NxOgre::Pose& pose,NxOgre::ActorParams params)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		// Back the actor params
		mActorParams.mDensity				= params.mDensity;
		mActorParams.mActorFlags			= params.mActorFlags;
		mActorParams.mGroupAsIndex			= params.mGroupAsIndex;
		mActorParams.mGroupAsName			= params.mGroupAsName;
	#if NX_SDK_VERSION_NUMBER >= 272 
		mActorParams.mDominanceGroupAsIndex	= params.mDominanceGroupAsIndex;
		mActorParams.mDominanceGroupAsName	= params.mDominanceGroupAsName;
	#endif
	#if NX_SDK_VERSION_NUMBER >= 260
		mActorParams.mCompartment			= params.mCompartment;
	#endif
		mActorParams.mMassLocalPose			= params.mMassLocalPose;
		mActorParams.mMassSpaceInertia		= params.mMassSpaceInertia;
		mActorParams.mLinearVelocity		= params.mLinearVelocity;
		mActorParams.mAngularVelocity		= params.mAngularVelocity;
		mActorParams.mWakeUpCounter			= params.mWakeUpCounter;
		mActorParams.mMass					= params.mMass;
		mActorParams.mLinearDamping			= params.mLinearDamping;
		mActorParams.mAngularDamping		= params.mAngularDamping;
		mActorParams.mMaxAngularVelocity	= params.mMaxAngularVelocity;
		mActorParams.mBodyFlags				= params.mBodyFlags;
		mActorParams.mSleepLinearVelocity	= params.mSleepLinearVelocity;
		mActorParams.mSleepAngularVelocity	= params.mSleepAngularVelocity;
		mActorParams.mCCDMotionThreshold	= params.mCCDMotionThreshold;
		mActorParams.mSolverIterationCount  = params.mSolverIterationCount;
		mActorParams.mBodyFlags				= params.mBodyFlags;
		mActorParams.mSleepEnergyThreshold	= params.mSleepEnergyThreshold;
		mActorParams.mSleepDamping			= params.mSleepDamping;

		mActorParams.mNodeScale				= params.mNodeScale;
		mActorParams.mNodeName				= params.mNodeName;
		mActorParams.mNodeShadows			= params.mNodeShadows;

		NxOgre::Actor::_createActor(blueprint, pose, params);
	}

	void							Actor::_destroyActor()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::_destroyActor();	
	}

	//////////////////////////////////////////////////////////

	void							Actor::setName(NxOgre::NxString name)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setName(name);
	}

	NxOgre::NxString						Actor::getName()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getName();
	}

	////////////////////////////////////////////////////////

	void							Actor::setGlobalPose(const NxOgre::Pose& pose)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGlobalPose(pose);
	}

	NxOgre::Pose							Actor::getGlobalPose()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getGlobalPose();
	}

	Ogre::Quaternion				Actor::getGlobalOrientation() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return STATIC_CAST_PTR(NxOgre::Actor*, Myoushu::Actor*, const_cast<Myoushu::Actor*>(this))->getGlobalOrientation();
	}
	void							Actor::setGlobalOrientation(const Ogre::Quaternion& quat)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGlobalOrientation(quat);
	}

	Ogre::Vector3					Actor::getGlobalPosition() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return STATIC_CAST_PTR(NxOgre::Actor*, Myoushu::Actor*, const_cast<Myoushu::Actor*>(this))->getGlobalPosition();
	}
	void							Actor::setGlobalPosition(const Ogre::Vector3& position)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGlobalPosition(position);
	}

	void							Actor::moveGlobalPose(const NxOgre::Pose& pose)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::moveGlobalPose(pose);	
	}
	void							Actor::moveGlobalPosition(const Ogre::Vector3& move)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::moveGlobalPosition(move);
	}
	void							Actor::moveGlobalOrientation(const Ogre::Quaternion& quat)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::moveGlobalOrientation(quat);
	}

	void							Actor::moveTowards(const NxOgre::Pose& pose, float force)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::moveTowards(pose, force);
	}

	//////////////////////////////////////////////////////////

	NxOgre::Shape*							Actor::addShape(NxOgre::ShapeBlueprint* blueprint)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::addShape(blueprint);
	}
	void							Actor::removeShape(NxOgre::Shape* shape)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::removeShape(shape);
	}
	void							Actor::removeShape(NxOgre::NxShapeIndex index)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::removeShape(index);
	}
	NxU32							Actor::getNbShapes() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getNbShapes();
	}
	NxOgre::CollisionModel*					Actor::getCollisionModel()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCollisionModel();
	}
	NxOgre::CollisionModel*					Actor::getDynamicCollisionModel()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getDynamicCollisionModel();
	}

	//////////////////////////////////////////////////////////

	void							Actor::setGroup(NxOgre::ActorGroup* actorGroup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGroup(actorGroup);
	}
	void							Actor::setGroup(const NxOgre::NxString& GroupIdentifier)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGroup(GroupIdentifier);
	}
	void							Actor::setGroup(NxActorGroup actorGroup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setGroup(actorGroup);
	}
	NxOgre::ActorGroup*						Actor::getGroup()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getGroup();
	}

	//////////////////////////////////////////////////////////

	void							Actor::raiseActorFlag(NxActorFlag flag)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::raiseActorFlag(flag);
	}
	void							Actor::clearActorFlag(NxActorFlag flag)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::clearActorFlag(flag);
	}
	bool							Actor::hasActorFlag(NxActorFlag flag)	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::hasActorFlag(flag);
	}
	bool							Actor::isDynamic()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::isDynamic();
	}

	//////////////////////////////////////////////////////////

	void							Actor::setCMassOffsetLocalPose(const NxOgre::Pose& pose)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetLocalPose(pose);
	}
	void							Actor::setCMassOffsetLocalPosition(const Ogre::Vector3& offsetPosition)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetLocalPosition(offsetPosition);
	}
	void							Actor::setCMassOffsetLocalOrientation(const NxMat33& orientation)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetLocalOrientation(orientation);
	}
	void							Actor::setCMassOffsetLocalOrientation(const Ogre::Matrix3& orientation)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetLocalOrientation(orientation);
	}
	void							Actor::setCMassOffsetGlobalPose(const NxOgre::Pose& pose)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetGlobalPose(pose);
	}
	void							Actor::setCMassOffsetGlobalPosition(const Ogre::Vector3& position)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetGlobalPosition(position);
	}
	void							Actor::setCMassOffsetGlobalOrientation(const NxMat33& orientation)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetGlobalOrientation(orientation);
	}
	void							Actor::setCMassOffsetGlobalOrientation(const Ogre::Matrix3& orientation)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassOffsetGlobalOrientation(orientation);
	}
	void							Actor::setCMassGlobalPose(const NxOgre::Pose& pose)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::setCMassGlobalPose(pose);
	}
	void							Actor::setCMassGlobalPosition(const Ogre::Vector3& position)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassGlobalPosition(position);
	}
	void							Actor::setCMassGlobalOrientation(const Ogre::Quaternion& orientation)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCMassGlobalOrientation(orientation);
	}

	NxOgre::Pose							Actor::getCMassLocalPose()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassLocalPose();
	}
	Ogre::Vector3 					Actor::getCMassLocalPosition()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassLocalPosition();
	}
	Ogre::Quaternion 				Actor::getCMassLocalOrientation() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassLocalOrientation();
	}
	NxOgre::Pose							Actor::getCMassGlobalPose() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassGlobalPose();
	}
	Ogre::Vector3 					Actor::getCMassGlobalPosition() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassGlobalPosition();
	}
	Ogre::Quaternion				Actor::getCMassGlobalOrientation()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCMassGlobalOrientation();
	}

	//////////////////////////////////////////////////////////

	void							Actor::setMass(NxReal mass)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setMass(mass);
	}
	NxReal							Actor::getMass() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getMass();
	}

	void							Actor::setMassSpaceInertiaTensor(const Ogre::Vector3& massSpaceIntertiaTensor)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setMassSpaceInertiaTensor(massSpaceIntertiaTensor);
	}
	Ogre::Vector3					Actor::getMassSpaceInertiaTensor()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getMassSpaceInertiaTensor();
	}
	Ogre::Matrix3					Actor::getGlobalInertiaTensor() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getGlobalInertiaTensor();
	}
	Ogre::Matrix3					Actor::getGlobalInertiaTensorInverse()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getGlobalInertiaTensorInverse();
	}

	void							Actor::updateMassFromShapeFromDensity(NxReal density)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::updateMassFromShapeFromDensity(density);
	}
	void							Actor::updateMassFromShapeAsMass(NxReal mass)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::updateMassFromShapeAsMass(mass);
	}

	//////////////////////////////////////////////////////////

	void							Actor::setLinearDamping(NxReal damping)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setLinearDamping(damping);
	}
	NxReal							Actor::getLinearDamping() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getLinearDamping();
	}

	void							Actor::setAngularDamping(NxReal damping)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setAngularDamping(damping);
	}
	NxReal							Actor::getAngularDamping() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

	return NxOgre::Actor::getAngularDamping();
	}

	//////////////////////////////////////////////////////////

	void							Actor::setLinearVelocity(const Ogre::Vector3& velocity)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setLinearVelocity(velocity);
	}
	void							Actor::setAngularVelocity(const Ogre::Vector3& velocity)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setAngularVelocity(velocity);
	}

	Ogre::Vector3					Actor::getLinearVelocity()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getLinearVelocity();
	}
	Ogre::Vector3					Actor::getAngularVelocity() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getAngularVelocity();
	}

	void							Actor::setMaxAngularVelocity(NxReal maxAngularVelocity)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setMaxAngularVelocity(maxAngularVelocity);
	}
	NxReal							Actor::getMaxAngularVelocity()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getMaxAngularVelocity();
	}


	//////////////////////////////////////////////////////////

	void							Actor::setCCDMotionThreshold(NxReal threshold)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setCCDMotionThreshold(threshold);
	}
	NxReal							Actor::getCCDMotionThreshold()	const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCCDMotionThreshold();	
	}

	//////////////////////////////////////////////////////////

	void							Actor::setLinearMomentum(const Ogre::Vector3& momentum)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setLinearMomentum(momentum);
	}
	void							Actor::setAngularMomentum(const Ogre::Vector3& momentum)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setAngularMomentum(momentum);
	}
	Ogre::Vector3					Actor::getLinearMomentum() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getLinearMomentum();
	}
	Ogre::Vector3					Actor::getAngularMomentum() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getAngularMomentum();
	}

	//////////////////////////////////////////////////////////

	void							Actor::addForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addForceAtPos(force, pos, mode, wakeup);
	}
	void							Actor::addForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addForceAtLocalPos(force, pos, mode, wakeup);
	}
	void							Actor::addLocalForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addLocalForceAtPos(force, pos, mode, wakeup);
	}
	void							Actor::addLocalForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addLocalForceAtLocalPos(force, pos, mode, wakeup);
	}
	void							Actor::addForce(const Ogre::Vector3& force, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addForce(force, mode, wakeup);
	}
	void							Actor::addLocalForce(const Ogre::Vector3& force, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addLocalForce(force, mode, wakeup);
	}
	void							Actor::addTorque(const Ogre::Vector3& torque, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addTorque(torque, mode, wakeup);
	}
	void							Actor::addLocalTorque(const Ogre::Vector3& torque, NxForceMode mode, bool wakeup)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::addLocalTorque(torque, mode, wakeup);
	}
	NxReal							Actor::computeKineticEnergy() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::computeKineticEnergy();
	}

	//////////////////////////////////////////////////////////

	Ogre::Vector3					Actor::getPointVelocity(const Ogre::Vector3& point) const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getPointVelocity(point);
	}
	Ogre::Vector3					Actor::getLocalPointVelocity(const Ogre::Vector3& point) const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getLocalPointVelocity(point);
	}

	//////////////////////////////////////////////////////////

	bool							Actor::isGroupSleeping() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::isGroupSleeping();
	}
	bool							Actor::isSleeping() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::isSleeping();	
	}
	NxReal							Actor::getSleepLinearVelocity() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getSleepLinearVelocity();
	}
	void							Actor::setSleepLinearVelocity(NxReal threshold)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setSleepLinearVelocity(threshold);
	}
	NxReal							Actor::getSleepAngularVelocity() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getSleepAngularVelocity();
	}
	void							Actor::setSleepAngularVelocity(NxReal threshold)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setSleepAngularVelocity(threshold);
	}
	NxReal							Actor::getSleepEnergyThreshold() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getSleepEnergyThreshold();
	}
	void							Actor::setSleepEnergyThreshold(NxReal threshold)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setSleepEnergyThreshold(threshold);
	}
	void							Actor::wakeUp(NxReal wakeCounterValue)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::wakeUp(wakeCounterValue);
	}
	void							Actor::putToSleep()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::putToSleep();
	}

	//////////////////////////////////////////////////////////

	void							Actor::raiseBodyFlag(NxBodyFlag flag)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::raiseBodyFlag(flag);
	}
	void							Actor::clearBodyFlag(NxBodyFlag flag)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		NxOgre::Actor::clearBodyFlag(flag);
	}
	bool							Actor::hasBodyFlag(NxBodyFlag flag) const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::hasBodyFlag(flag);
	}
	void							Actor::setSolverIterationCount(NxU32 iterCount)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::setSolverIterationCount(iterCount);
	}
	NxU32							Actor::getSolverIterationCount() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getSolverIterationCount();	
	}

	//////////////////////////////////////////////////////////

	#if NX_SUPPORT_SWEEP_API
	NxU32							Actor::linearSweep(const Ogre::Vector3& motion, NxU32 flags, void* userData, NxU32 nbShapeDescriptions, NxSweepQueryHit* ShapeDescriptions, NxUserEntityReport<NxSweepQueryHit>* callback, const NxSweepCache* sweepCache)
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::linearSweep(motion, flags, userData, nbShapeDescriptions, ShapeDescriptions, callback, sweepCache);
	}
	#endif

	//////////////////////////////////////////////////////////
	#if NX_SDK_VERSION_NUMBER >= 260
	NxOgre::Compartment*					Actor::getCompartment() const
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getCompartment();
	}
	#endif
	//////////////////////////////////////////////////////////

	void*							Actor::getNxActorUserData()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::getNxActorUserData();
	}

	NxOgre::FixedJoint*						Actor::joinWith(NxOgre::Actor* actor, NxOgre::JointParams jointParams)
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		return NxOgre::Actor::joinWith(actor, jointParams);
	}

	void							Actor::disable()
	{
		Poco::ScopedRWLock lock(mActorRWLock, true);

		NxOgre::Actor::disable();
	}

	NxOgre::StringPairList Actor::saveCustom()
	{
		Poco::ScopedRWLock lock(mActorRWLock, false);

		return NxOgre::Actor::saveCustom();
	}

} // Myoushu
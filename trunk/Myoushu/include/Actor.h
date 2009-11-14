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
 * @file Actor.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef ACTOR_H
#define ACTOR_H

#include "Poco/RWLock.h"
#include "Ogre.h"
#include "NxOgre.h"

#include "Platform.h"
#include "Scene.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * This file is basically a copy of the NxOgre::Actor header file. Every class method of NxOgre::Actor is overloaded and the original 
	 * called in a thread safe scope.
	 */
	class MYOUSHU_API Actor : public NxOgre::Actor, public Serializable
	{
		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock mActorRWLock;
			Scene *mpScene;
			NxOgre::ActorParams mActorParams;

		public:

			Actor(const NxOgre::NxString& Identifier, Scene*, bool isActorBased = true);
			Actor(const NxOgre::NxString& Identifier, Scene*, NxOgre::ShapeBlueprint*, const NxOgre::Pose&, NxOgre::ActorParams = NxOgre::ActorParams());
			virtual ~Actor();

			/** 
			 * Gets the name of the NxOgre::ActorGroup this Actor instance belongs to, if any.
			 * @return the name of the NxOgre::ActorGroup this Actor instance belongs to or "" if this Actor does
			 *         not belong to a group.
			 */
			std::string getGroupName() const;

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

			//////////////////////////////////////////////////////////

			Scene*		getScene()			{
												return mpScene;
											}

			NxScene*	getNxScene();

			//////////////////////////////////////////////////////////

			virtual bool					hasVisualisation() const {return false;}
			virtual void					simulate(float);
			virtual void					render(float);
			virtual void					shapeSimulate(float);
			virtual void					shapeRender(float);
			bool							isDead() { return (mActor == NULL); }


			/** Duplicate this actor
				
				@param	name	Name of the new Actor
				@param	pose	Position/Orientation of the new actor.

				@note
					This function is rather slow and inefficent when used repeatedly. Use a ActorBlueprint instead to
					keep a single blueprint of the actor and create as many as you want from that.

			 */
			NxOgre::Actor*							duplicate(const NxOgre::NxString& name, const NxOgre::Pose& p);

			//////////////////////////////////////////////////////////

			void							_createActor(NxOgre::ShapeBlueprint*,const NxOgre::Pose&,NxOgre::ActorParams params);
			void							_destroyActor();

			NxActor*						getNxActor(){return mActor;}

			//////////////////////////////////////////////////////////

			void							setName(NxOgre::NxString);
			NxOgre::NxString						getName();

			////////////////////////////////////////////////////////

			void							setGlobalPose(const NxOgre::Pose&);
			NxOgre::Pose							getGlobalPose();

			Ogre::Quaternion				getGlobalOrientation() const;
			void							setGlobalOrientation(const Ogre::Quaternion&);

			Ogre::Vector3					getGlobalPosition() const;
			void							setGlobalPosition(const Ogre::Vector3&);

			void							moveGlobalPose(const NxOgre::Pose&);
			void							moveGlobalPosition(const Ogre::Vector3&);
			void							moveGlobalOrientation(const Ogre::Quaternion&);

			void							moveTowards(const NxOgre::Pose&, float force = 10.0f);

			//////////////////////////////////////////////////////////

			NxOgre::Shape*							addShape(NxOgre::ShapeBlueprint*);
			void							removeShape(NxOgre::Shape*);
			void							removeShape(NxOgre::NxShapeIndex);
			NxU32							getNbShapes() const;
			NxOgre::CollisionModel*					getCollisionModel();
			NxOgre::CollisionModel*					getDynamicCollisionModel();

			//////////////////////////////////////////////////////////

			void							setGroup(NxOgre::ActorGroup*);
			void							setGroup(const NxOgre::NxString& GroupIdentifier);
			void							setGroup(NxActorGroup);
			NxOgre::ActorGroup*						getGroup()	const;

			//////////////////////////////////////////////////////////

			void							raiseActorFlag(NxActorFlag);
			void							clearActorFlag(NxActorFlag);
			bool							hasActorFlag(NxActorFlag)	const;
			bool							isDynamic()	const;

			//////////////////////////////////////////////////////////

			void							setCMassOffsetLocalPose(const NxOgre::Pose&);
			void							setCMassOffsetLocalPosition(const Ogre::Vector3&);
			void							setCMassOffsetLocalOrientation(const NxMat33&);
			void							setCMassOffsetLocalOrientation(const Ogre::Matrix3&);
			void							setCMassOffsetGlobalPose(const NxOgre::Pose&);
			void							setCMassOffsetGlobalPosition(const Ogre::Vector3&);
			void							setCMassOffsetGlobalOrientation(const NxMat33&);
			void							setCMassOffsetGlobalOrientation(const Ogre::Matrix3&);
			void							setCMassGlobalPose(const NxOgre::Pose&);
			void							setCMassGlobalPosition(const Ogre::Vector3&);
			void							setCMassGlobalOrientation(const Ogre::Quaternion&);

			NxOgre::Pose							getCMassLocalPose()	const;
			Ogre::Vector3 					getCMassLocalPosition()	const;
			Ogre::Quaternion 				getCMassLocalOrientation() const;
			NxOgre::Pose							getCMassGlobalPose() const;
			Ogre::Vector3 					getCMassGlobalPosition() const;
			Ogre::Quaternion				getCMassGlobalOrientation()	const;

			//////////////////////////////////////////////////////////

			void							setMass(NxReal);
			NxReal							getMass() const;

			void							setMassSpaceInertiaTensor(const Ogre::Vector3&);
			Ogre::Vector3					getMassSpaceInertiaTensor()	const;
			Ogre::Matrix3					getGlobalInertiaTensor() const;
			Ogre::Matrix3					getGlobalInertiaTensorInverse()	const;

			void							updateMassFromShapeFromDensity(NxReal);
			void							updateMassFromShapeAsMass(NxReal);

			//////////////////////////////////////////////////////////

			void							setLinearDamping(NxReal);
			NxReal							getLinearDamping() const;

			void							setAngularDamping(NxReal);
			NxReal							getAngularDamping() const;

			//////////////////////////////////////////////////////////

			void							setLinearVelocity(const Ogre::Vector3&);
			void							setAngularVelocity(const Ogre::Vector3&);

			Ogre::Vector3					getLinearVelocity()	const;
			Ogre::Vector3					getAngularVelocity() const;

			void							setMaxAngularVelocity(NxReal);
			NxReal							getMaxAngularVelocity()	const;


			//////////////////////////////////////////////////////////

			void							setCCDMotionThreshold(NxReal);
			NxReal							getCCDMotionThreshold()	const;

			//////////////////////////////////////////////////////////

			void							setLinearMomentum(const Ogre::Vector3&);
			void							setAngularMomentum(const Ogre::Vector3&);
			Ogre::Vector3					getLinearMomentum() const;
			Ogre::Vector3					getAngularMomentum() const;

			//////////////////////////////////////////////////////////

			void							addForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalForceAtPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalForceAtLocalPos(const Ogre::Vector3& force, const Ogre::Vector3& pos, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addForce(const Ogre::Vector3& force, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalForce(const Ogre::Vector3& force, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addTorque(const Ogre::Vector3& torque, NxForceMode mode = NX_FORCE, bool wakeup = true);
			void							addLocalTorque(const Ogre::Vector3& torque, NxForceMode mode = NX_FORCE, bool wakeup = true);
			NxReal							computeKineticEnergy() const;

			//////////////////////////////////////////////////////////

			Ogre::Vector3					getPointVelocity(const Ogre::Vector3& point) const;
			Ogre::Vector3					getLocalPointVelocity(const Ogre::Vector3& point) const;

			//////////////////////////////////////////////////////////

			bool							isGroupSleeping() const;
			bool							isSleeping() const;
    		NxReal							getSleepLinearVelocity() const;
    		void							setSleepLinearVelocity(NxReal threshold);
    		NxReal							getSleepAngularVelocity() const;
    		void							setSleepAngularVelocity(NxReal threshold);
			NxReal							getSleepEnergyThreshold() const;
			void							setSleepEnergyThreshold(NxReal threshold);
			void							wakeUp(NxReal wakeCounterValue=NX_SLEEP_INTERVAL);
			void							putToSleep();

			//////////////////////////////////////////////////////////

			void							raiseBodyFlag(NxBodyFlag);
			void							clearBodyFlag(NxBodyFlag);
			bool							hasBodyFlag(NxBodyFlag) const;
			void							setSolverIterationCount(NxU32);
			NxU32							getSolverIterationCount() const;

			//////////////////////////////////////////////////////////

#if NX_SUPPORT_SWEEP_API
			NxU32							linearSweep(const Ogre::Vector3& motion, NxU32 flags, void* userData, NxU32 nbShapeDescriptions, NxSweepQueryHit* ShapeDescriptions, NxUserEntityReport<NxSweepQueryHit>* callback, const NxSweepCache* sweepCache=NULL);
#endif

			//////////////////////////////////////////////////////////
#if NX_SDK_VERSION_NUMBER >= 260
			NxOgre::Compartment*					getCompartment() const;
#endif
			//////////////////////////////////////////////////////////

			void*							getNxActorUserData();

			/** joinWith

				Creates a fixedJoint with this actor and the referenced actor.

			*/
			NxOgre::FixedJoint*						joinWith(NxOgre::Actor*, NxOgre::JointParams);

			/** Disable

				Nearly kills the actor in the Scene. Disables collision, movement,
				rotation, reporting. If the Actor is subclassed the visualisation
				will be removed (or hidden). This is best used with a batch
				delete of Actors (just before a batch deletion is done) to hide
				the Actor from the screen, and just before it is deleted.

				If you want to undisable this actor, you will need to loose the 
				NX_AF_DISABLE_COLLISION, NX_AF_COLLISION_RESPONSE, NX_BF_FROZEN,
				flags. See the code in disable for more details.

			*/
			void							disable();
			virtual void					disableVisualisation() {}

			NxU32							getBirthFrame() {return mBirthFrame;}

			//////////////////////////////////////////////////////////

			virtual NxOgre::StringPairList			saveCustom();
			virtual void					restoreCustom(NxOgre::StringPairList)	{}

	};
	// inlines
	inline std::string Actor::getGroupName() const
	{
		NxOgre::ActorGroup* pGroup;

		pGroup = getGroup();

		if (pGroup == NULL)
		{
			return "";
		}

		return pGroup->getName();
	}

} // Myoushu



#endif

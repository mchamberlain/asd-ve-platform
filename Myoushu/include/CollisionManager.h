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
 * @file CollisionManager.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef MYOUSHU_COLLISION_MANAGER_H
#define MYOUSHU_COLLISION_MANAGER_H

#include <map>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Ogre.h"
#include "NxOgre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "Scene.h"
#include "FunctorBase.h"
#include "LuaFunctor.h"
#include "GameActorObject.h"
#include "GameCharacterObject.h"

namespace Myoushu
{
	/**
	 * The CollisionManager class allows one to set up monitoring and reporting (through callbacks) of collisions that occur between objects.
	 */
	class MYOUSHU_API CollisionManager : public NxOgre::GroupCallback::InheritedCallback, public NxOgre::CharacterHitReport, public Ogre::Singleton<CollisionManager>
	{
		public:
			/** Enumeration of the different situations in which collision callbacks should be called. */
			enum ContactPairFlag
			{
				/** Disable collision detection between a pair of objects */
				CP_IGNORE_PAIR								= NX_IGNORE_PAIR,
				/** Callback will be called when a pair of objects start to be in contact. */
				CP_NOTIFY_ON_START_TOUCH					= NX_NOTIFY_ON_START_TOUCH,
				/** Callback will be called when a pair of objects stops to be in contact. */
				CP_NOTIFY_ON_END_TOUCH						= NX_NOTIFY_ON_END_TOUCH,
				/** Callback will keep getting called while the pair is in contact */
				CP_NOTIFY_ON_TOUCH							= NX_NOTIFY_ON_TOUCH,
				/** Callbacks will be called for the situations in CP_NOTIFY_ON_START_TOUCH, CP_NOTIFY_ON_END_TOUCH and CP_NOTIFY_ON_TOUCH */
				CP_NOTIFY_ALL								= (CP_NOTIFY_ON_START_TOUCH | CP_NOTIFY_ON_END_TOUCH | CP_NOTIFY_ON_TOUCH)
			};

			/** A small struct that stores some properties about a actor-character collision, such as position, normal and direction of motion. */
			struct CollisionProperties
			{
				/** World position where contact took place. */
				Ogre::Vector3 mWorldPosition;
				/** The contact normal. */
				Ogre::Vector3 mWorldNormal;
				/** The direction of motion when the collision took place. */
				Ogre::Vector3 mDirection;
				/** The length of the motion. */
				Ogre::Real mLength;

				/** Assignment operator to ensure that struct assignments are handled properly. */
				CollisionProperties& operator=(const CollisionProperties& rhs);
			};

			/** Type definition of the basic std::map template used to map actor and group names to collision callbacks. */
			//typedef std::map<std::string, Poco::AutoPtr<FunctorBase> > CollisionCallbackMap;
			typedef std::map<std::string, FunctorBase* > CollisionCallbackMap;
			/** Type defitinion for an iterator over CollisionCallbackMap. */
			typedef CollisionCallbackMap::iterator CollisionCallbackMapIterator;
			/** Type defitinion for an const_iterator over CollisionCallbackMap. */
			typedef CollisionCallbackMap::const_iterator CollisionCallbackMapConstIterator;
			/** Type defitinion for an entry (key-value pair) in CollisionCallbackMap. */
			//typedef std::pair<std::string, Poco::AutoPtr<FunctorBase> > CollisionCallbackMapEntry;
			typedef std::pair<std::string, FunctorBase* > CollisionCallbackMapEntry;

			/** The LuaFunctor type used for Lua based actor-actor collision callbacks. */
			typedef LuaFunctor<void, 2, GameActorObject*, GameActorObject*> CollisionCallbackLuaFunctor;
			/** The LuaFunctor type used for Lua based character-actor collision callbacks. */
			typedef LuaFunctor<void, 3, GameCharacterObject*, GameActorObject*, CollisionProperties> CharacterActorCollisionCallbackLuaFunctor;

			/** Constructor */
			CollisionManager();

			/** Destructor */
			~CollisionManager();

			/** 
			 * Sets for which collision situations, between two groups, callbacks should be called. 
			 * @param pScene The scene the actor groups are registered in.
			 * @param firstGroupName The name of one of the groups.
			 * @param secondGroupName The name of the other group.
			 * @param contactPairFlag The flag that defines for which collision situations callbacks will be called.
			 * @param twoWay Defaults to false. If false only collisions of firstGroupName->secondGroupName are set, if true collisions in both directions are set.
			 * @throws Exception::E_NULL_POINTER if pScene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if any of the specified groups do not exist.
			 */
			void setActorGroupsCollidable(Myoushu::Scene* pScene, const Ogre::String& firstGroupName, const Ogre::String& secondGroupName, ContactPairFlag contactPairFlag, bool twoWay = false) throw (Exception);

			/** 
			 * Returns a flag (ContactPairFlag) indicating for which situations, for collision between objects from the two specified groups, collision callbacks will be called. 
			 * @param pScene The scene the actor groups are registered in.
			 * @param firstGroupName The name of one of the groups.
			 * @param secondGroupName The name of the other group.
			 * @return a flag (ContactPairFlag) indicating for which situations, for collision between objects from the two specified groups, collision callbacks will be called.
			 * @throws Exception::E_NULL_POINTER if pScene is NULL.
			 * @throws Exception::E_NO_SUCH_ELEMENT if any of the specified groups do not exist.
			 */
			ContactPairFlag getActorGroupsCollidable(Myoushu::Scene* pScene, const Ogre::String& firstGroupName, const Ogre::String& secondGroupName) throw (Exception);

			/** The underlying physics or collision detection system calls this method if two actors start to touch. */
			void onStartTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor);

			/** The underlying physics or collision detection system calls this method if two actors stop touching. */
			void onEndTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor);

			/** The underlying physics or collision detection system calls this method if two actors touch. */
			void onTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor);

			/** Called by PhysX for Actor-Character collisions. */
			virtual NxOgre::CharacterHitReport::Response onActor(NxOgre::Character*, NxOgre::Actor*, NxOgre::Shape*, NxOgre::ActorGroup*, const NxControllerShapeHit&);

			/** Called by PhysX for Actor-Character collisions. */
			virtual NxOgre::CharacterHitReport::Response onCharacterHit(NxOgre::Character*, NxOgre::Actor*, NxOgre::Shape*, NxOgre::ActorGroup*, const NxControllersHit&);

			/** 
			 * Sets the callback to call if any two collidable actors start to touch. 
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setGlobalStartTouchCallback(FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any two collidable actors start to touch. 
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setGlobalStartTouchCallback(const Ogre::String& luaFunctionName);

			/**
			 * Sets the callback to call if any two collidable actors stop touching. 
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setGlobalEndTouchCallback(FunctorBase* pCallback);

			/**
			 * Sets the callback to call if any two collidable actors stop touching. 
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setGlobalEndTouchCallback(const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if any two collidable actors collide. 
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setGlobalTouchCallback(FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any two collidable actors collide. 
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setGlobalTouchCallback(const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if any two collidable actors start to touch, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerGroupStartTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any two collidable actors start to touch, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerGroupStartTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if any two collidable actors stop touching, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerGroupEndTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any two collidable actors stop touching, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerGroupEndTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if any two collidable actors collide, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerGroupTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any two collidable actors collide, where one of the actors is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerGroupTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName);

			/**
			 * Sets the callback to call if the specified actor starts to collide with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorStartTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor starts to collide with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorStartTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback);

			/**
			 * Sets the callback to call if the specified actor starts to collide with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorStartTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor starts to collide with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorStartTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName);

			/**
			 * Sets the callback to call if the specified actor stops colliding with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorEndTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception);

			/**
			 * Sets the callback to call if the specified actor stops colliding with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorEndTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback);

			/**
			 * Sets the callback to call if the specified actor stops colliding with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorEndTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception);

			/**
			 * Sets the callback to call if the specified actor stops colliding with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorEndTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if the specified actor collides with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor collides with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if the specified actor collides with another actor. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor collides with another actor. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName);

			//======================================== Actor - Character collisions ========================================//

			/** Enable actor-character collision reporting. */
			void enableActorCharacterCollisionReporting(Scene *pScene);

			/** 
			 * Sets the callback to call if any actor collides with any character.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setGlobalActorCharacterCallback(FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if any actor collides with any character.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setGlobalActorCharacterCallback(const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if an actor collides with a character, where the actor is in the specified group. 
			 * @param groupName The name of the ActorGroup that the actor in the collision must belong to.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerGroupCharacterCallback(const Ogre::String& groupName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if an actor collides with a character, where the actor is in the specified group. 
			 * @param groupName The name of the ActorGroup that one of the actors in the collision must belong to.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerGroupCharacterCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if the specified actor collides with a character. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorCharacterCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor collides with a character. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerActorCharacterCallback(const Ogre::String& gameActorName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if the specified actor collides with a character. 
			 * @param pGameActor The Actor to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorCharacterCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception);

			/** 
			 * Sets the callback to call if the specified actor collides with a character. 
			 * @param gameActorName The name of the GameActorObject instance to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerActorCharacterCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName);

			/** 
			 * Sets the callback to call if the specified chracter collides with an actor. 
			 * @param pGameCharacter The Character to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerCharacterActorCallback(GameCharacterObject* pGameCharacter, FunctorBase* pCallback) throw (Exception);

			/** 
			 * Sets the callback to call if the specified character collides with an actor.
			 * @param gameCharacterName The name of the GameCharacterObject instance to register the collision callback for.
			 * @param pCallback A FunctorBase instance that wraps the function to be called.
			 */
			void setPerCharacterActorCallback(const Ogre::String& gameCharacterName, FunctorBase* pCallback);

			/** 
			 * Sets the callback to call if the specified chracter collides with an actor. 
			 * @param pGameCharacter The Character to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerCharacterActorCallback(GameCharacterObject* pGameCharacter, const Ogre::String& luaFunctionName) throw (Exception);

			/** 
			 * Sets the callback to call if the specified character collides with an actor.
			 * @param gameCharacterName The name of the GameCharacterObject instance to register the collision callback for.
			 * @param luaFunctionName The name of the Lua function to use as callback. The Lua function should
			 *						  expect two GameActorObject* parameters.
			 */
			void setPerCharacterActorCallback(const Ogre::String& gameCharacterName, const Ogre::String& luaFunctionName);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerActorStartCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerActorStopCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerActorCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerGroupStartCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerGroupStopCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerGroupCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockGlobalCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerActorCharacterCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerGroupCharacterCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockPerCharacterActorCallbacks;
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLockGlobalCharacterCallbacks;
			/** Map of actor names to callbacks to call when the actor starts to touch another actor. */
			CollisionCallbackMap mPerActorStartCallbacks;
			/** Map of actor names to callbacks to call when the actor stops touching another actor. */
			CollisionCallbackMap mPerActorStopCallbacks;
			/** Map of actor names to callbacks to call when the actor collides with another actor. */
			CollisionCallbackMap mPerActorCallbacks;
			/** Map of group names to callbacks to call when the an actor from the group starts to touch another actor. */
			CollisionCallbackMap mPerGroupStartCallbacks;
			/** Map of group names to callbacks to call when the an actor from the group stops touching another actor. */
			CollisionCallbackMap mPerGroupStopCallbacks;
			/** Map of group names to callbacks to call when the an actor from the group collides with another actor. */
			CollisionCallbackMap mPerGroupCallbacks;
			/** Callback to call if two actors start touching */
			FunctorBase *mpGlobalStartCallback;
			/** Callback to call if two actors stop touching */
			FunctorBase *mpGlobalStopCallback;
			/** Callback to call while two actors are colliding */
			FunctorBase *mpGlobalCallback;
			/** Map of actor names to callbacks to call when an actor collides with a character. */
			CollisionCallbackMap mPerActorCharacterCallbacks;
			/** Map of actor group names to callbacks to call when an actor collides with a character. */
			CollisionCallbackMap mPerGroupActorCharacterCallbacks;
			/** Map of character names to callbacks to call when an actor collides with the character. */
			CollisionCallbackMap mPerCharacterActorCallbacks;
			/** Callback to call when an actor collides with a character. */
			FunctorBase *mpGlobalActorCharacterCallback;

			/**
			 * Generic function that is called by onStartTouch, onEndTouch and onTouch to handle the calling of callback functions for the appropriate situation.
			 * @param globalRWLock The Poco::RWLock that controls access to pGlobalCallback.
			 * @param pGlobalCallback The callback to call for this touch situation. This should be mpGlobalStartCallback, mpGlobalStopCallback or mpGlobalCallback.
			 * @param perActorRWLock The Poco::RWLock that controls access to perActorCallbackMap
			 * @param perActorCallbackMap The map of per actor callbacks to use for this collision situation, should be one of mPerActorStartCallbacks, mPerActorStopCallbacks or mPerActorCallbacks.
			 * @param perGroupRWLock The Poco::RWLock that controls access to perGroupCallbackMap
			 * @param perGroupCallbackMap The map of per group callbacks to use for this collision situation, should be one of mPerGroupStartCallbacks, mPerGroupStopCallbacks or mPerGroupCallbacks.
			 * @param pFirstActor One of the actors involved in the collision.
			 * @param pSecondActor The ohter actor involved in the collision.
			 */
			void onTouchGeneric(Poco::RWLock& globalRWLock, FunctorBase* pGlobalCallback, Poco::RWLock& perActorRWLock
				, CollisionCallbackMap& perActorCallbackMap, Poco::RWLock& perGroupRWLock, CollisionCallbackMap& perGroupCallbackMap
				, GameActorObject* pFirstActor, GameActorObject* pSecondActor);

			/**
			 * Generic function that is called by onActor to handle the calling of callback functions for actor-character collisions.
			 * @param globalRWLock The Poco::RWLock that controls access to pGlobalCallback.
			 * @param pGlobalCallback The callback to call for this collision. This should be mpGlobalActorCharacterCallback.
			 * @param perActorRWLock The Poco::RWLock that controls access to perActorCallbackMap
			 * @param perActorCallbackMap The map of per actor callbacks to use for this collision, should be mPerActorCharacterCallbacks
			 * @param perGroupRWLock The Poco::RWLock that controls access to perGroupCallbackMap
			 * @param perGroupCallbackMap The map of per group callbacks to use for this collision, should be one of mPerGroupActorCharacterCallbacks.
			 * @param perCharacterActorRWLock The Poco::RWLock that controls access to perCharacterActorCallbackMap
			 * @param perCharacterActorCallbackMap The map of per character callbacks to use for this collision, should be mPerCharacterActorCallbacks
			 * @param pCharacter The character involved in the collision.
			 * @param pActor The actor involved in the collision.
			 * @param collisionProps Additional information about the collision.
			 */
			void characterActorGeneric(Poco::RWLock& globalRWLock, FunctorBase* pGlobalCallback, Poco::RWLock& perActorRWLock
				, CollisionCallbackMap& perActorCharacterCallbackMap, Poco::RWLock& perGroupRWLock
				, CollisionCallbackMap& perGroupCharacterCallbackMap, Poco::RWLock& perCharacterRWLock
				, CollisionCallbackMap& perCharacterActorCallbackMap, GameCharacterObject* pCharacter, GameActorObject* pActor
				, CollisionProperties collisionProps);

	}; // class CollisionManager

	// inlines
	inline CollisionManager::CollisionProperties& CollisionManager::CollisionProperties::operator=(const CollisionManager::CollisionProperties& rhs)
	{
		mWorldPosition = rhs.mWorldPosition;
		mWorldNormal = rhs.mWorldNormal;
		mDirection = rhs.mDirection;
		mLength = rhs.mLength;

		return *this;
	}

	inline void CollisionManager::setGlobalStartTouchCallback(const Ogre::String& luaFunctionName)
	{
		setGlobalStartTouchCallback(new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setGlobalEndTouchCallback(const Ogre::String& luaFunctionName)
	{
		setGlobalEndTouchCallback(new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setGlobalTouchCallback(const Ogre::String& luaFunctionName)
	{
		setGlobalTouchCallback(new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerGroupStartTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName)
	{
		setPerGroupStartTouchCallback(groupName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerGroupEndTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName)
	{
		setPerGroupEndTouchCallback(groupName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerGroupTouchCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName)
	{
		setPerGroupTouchCallback(groupName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorStartTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception)
	{
		setPerActorStartTouchCallback(pGameActor, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorStartTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName)
	{
		setPerActorStartTouchCallback(gameActorName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorEndTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception)
	{
		setPerActorEndTouchCallback(pGameActor, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorEndTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName)
	{
		setPerActorEndTouchCallback(gameActorName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorTouchCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception)
	{
		setPerActorTouchCallback(pGameActor, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setPerActorTouchCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName)
	{
		setPerActorTouchCallback(gameActorName, new CollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameActorObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*"));
	}

	inline void CollisionManager::setGlobalActorCharacterCallback(const Ogre::String& luaFunctionName)
	{
		setGlobalActorCharacterCallback(new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

	inline void CollisionManager::setPerGroupCharacterCallback(const Ogre::String& groupName, const Ogre::String& luaFunctionName)
	{
		setPerGroupCharacterCallback(groupName, new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

	inline void CollisionManager::setPerActorCharacterCallback(GameActorObject* pGameActor, const Ogre::String& luaFunctionName) throw (Exception)
	{
		setPerActorCharacterCallback(pGameActor, new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

	inline void CollisionManager::setPerActorCharacterCallback(const Ogre::String& gameActorName, const Ogre::String& luaFunctionName)
	{
		setPerActorCharacterCallback(gameActorName, new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

	inline void CollisionManager::setPerCharacterActorCallback(GameCharacterObject* pGameCharacter, const Ogre::String& luaFunctionName) throw (Exception)
	{
		setPerCharacterActorCallback(pGameCharacter, new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

	inline void CollisionManager::setPerCharacterActorCallback(const Ogre::String& gameCharacterName, const Ogre::String& luaFunctionName)
	{
		setPerCharacterActorCallback(gameCharacterName, new CharacterActorCollisionCallbackLuaFunctor(luaFunctionName, NamedObject<GameCharacterObject>::getStaticClassName() + "*", NamedObject<GameActorObject>::getStaticClassName() + "*", "Myoushu::CollisionManager::CollisionProperties"));
	}

} // namespace Myoushu

#endif

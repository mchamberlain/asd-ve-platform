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
 * @file CollisionManager.cpp
 * @author ME Chamberlain
 * @date March 2009
 */

#include "CollisionManager.h"
#include "GameObjectFactory.h"

namespace Myoushu
{
	CollisionManager::CollisionManager() : mpGlobalStartCallback(NULL), mpGlobalStopCallback(NULL), mpGlobalCallback(NULL), mpGlobalActorCharacterCallback(NULL)
	{
	}

	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::setActorGroupsCollidable(Scene* pScene, const Ogre::String& firstGroupName, const Ogre::String& secondGroupName, CollisionManager::ContactPairFlag contactPairFlag, bool twoWay) throw (Exception)
	{
		NxOgre::ActorGroup *pFirstGroup;
		NxOgre::ActorGroup *pSecondGroup;

		// Check that pScene is not NULL
		if (pScene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setActorGroupsCollidable(): pScene is NULL.");
		}

		pFirstGroup = NULL;
		pSecondGroup = NULL;

		// Get the NxOgre::ActorGroups by their names
		pFirstGroup = pScene->getActorGroup(firstGroupName);

		// If a group does not exist, create it but log a warning
		if (pFirstGroup == NULL)
		{
			//throw Exception(Exception::E_NO_SUCH_ELEMENT, "CollisionManager::setActorGroupsCollidable(): The group: " + firstGroupName + " does not exist.");
			pFirstGroup = pScene->createActorGroup(firstGroupName);
			LOG(EngineLog::LM_WARNING, "CollisionManager::setActorGroupsCollidable(): Group " << firstGroupName << " does not exist, it will be created.");
		}

		pSecondGroup = pScene->getActorGroup(secondGroupName);
		if (pSecondGroup == NULL)
		{
			//throw Exception(Exception::E_NO_SUCH_ELEMENT, "CollisionManager::setActorGroupsCollidable(): The group: " + secondGroupName + " does not exist.");
			pSecondGroup = pScene->createActorGroup(secondGroupName);
			LOG(EngineLog::LM_WARNING, "CollisionManager::setActorGroupsCollidable(): Group " << secondGroupName << " does not exist, it will be created.");
		}

		// Set the collision flags between the groups
		pFirstGroup->setCallback(this);
		if (twoWay)
		{
			pSecondGroup->setCallback(this);
		}
		pFirstGroup->setCollisionCallback(pSecondGroup, static_cast<NxContactPairFlag>(contactPairFlag), twoWay);
	}

	CollisionManager::ContactPairFlag CollisionManager::getActorGroupsCollidable(Scene* pScene, const Ogre::String& firstGroupName, const Ogre::String& secondGroupName) throw (Exception)
	{
		NxOgre::ActorGroup *pFirstGroup;
		NxOgre::ActorGroup *pSecondGroup;

		// Check that pScene is not NULL
		if (pScene == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setActorGroupsCollidable(): pScene is NULL.");
		}

		pFirstGroup = NULL;
		pSecondGroup = NULL;

		// Get the NxOgre::ActorGroups by their names
		pFirstGroup = pScene->getActorGroup(firstGroupName);
		pSecondGroup = pScene->getActorGroup(secondGroupName);

		// Check that both groups exist, if not throw an exception
		if (pFirstGroup == NULL)
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "CollisionManager::setActorGroupsCollidable(): The group: " + firstGroupName + " does not exist.");
		}

		if (pSecondGroup == NULL)
		{
			throw Exception(Exception::E_NO_SUCH_ELEMENT, "CollisionManager::setActorGroupsCollidable(): The group: " + secondGroupName + " does not exist.");
		}

		return static_cast<ContactPairFlag>(pScene->getNxScene()->getActorGroupPairFlags(pFirstGroup->getGroupID(), pSecondGroup->getGroupID()));
	}

	void CollisionManager::onTouchGeneric(Poco::RWLock& globalRWLock, FunctorBase* pGlobalCallback, Poco::RWLock& perActorRWLock
		, CollisionManager::CollisionCallbackMap& perActorCallbackMap, Poco::RWLock& perGroupRWLock, CollisionManager::CollisionCallbackMap& perGroupCallbackMap
		, GameActorObject* pFirstActor, GameActorObject* pSecondActor)
	{
		CollisionCallbackMapIterator iter;
		NxOgre::ActorGroup *pActorGroup;
		Value val;

		// Acquire a read lock on the global callbacks
		Poco::ScopedRWLock lockGlobal(globalRWLock, false);

		// set parameters and execute
		if (pGlobalCallback != NULL)
		{
			// set the parameters
			if (pGlobalCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CollisionCallbackLuaFunctor*>(pGlobalCallback);
				// parameters in LuaFunctor are set slightly differently
				pLuaFunctor->setParameter1(pFirstActor);
				pLuaFunctor->setParameter2(pSecondActor);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pFirstActor));
				pGlobalCallback->setParameter(0, val);
				val.set(reinterpret_cast<void*>(pSecondActor));
				pGlobalCallback->setParameter(1, val);
			}
			// execute the callback
			(*pGlobalCallback)();
		}

		// Acquire a read lock on the perActorCallbackMap
		Poco::ScopedRWLock lockPerActor(perActorRWLock, false);

		// Get the per actor start callback and call it, if it indeed exists
		iter = perActorCallbackMap.find(pFirstActor->getName());
		if (iter != perActorCallbackMap.end())
		{
			FunctorBase *pCallback = iter->second;

			// set parameters and execute
			if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CollisionCallbackLuaFunctor*>(pCallback);
				// parameters in LuaFunctor are set slightly differently
				pLuaFunctor->setParameter1(pFirstActor);
				pLuaFunctor->setParameter2(pSecondActor);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pFirstActor));
				pCallback->setParameter(0, val);
				val.set(reinterpret_cast<void*>(pSecondActor));
				pCallback->setParameter(1, val);
			}
			// execute the callback
			(*pCallback)();
		}

		// Get the per actor start callback for the second actor and call it, if it indeed exists
		iter = perActorCallbackMap.find(pSecondActor->getName());
		if (iter != perActorCallbackMap.end())
		{
			FunctorBase *pCallback = iter->second;

			// set parameters and execute
			if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CollisionCallbackLuaFunctor*>(pCallback);
				// parameters in LuaFunctor are set slightly differently
				pLuaFunctor->setParameter1(pFirstActor);
				pLuaFunctor->setParameter2(pSecondActor);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pFirstActor));
				pCallback->setParameter(1, val);
				val.set(reinterpret_cast<void*>(pSecondActor));
				pCallback->setParameter(0, val);
			}
			// execute the callback
			(*pCallback)();
		}

		// Acquire a read lock on the perGroupCallbackMap
		Poco::ScopedRWLock lockPerGroup(perGroupRWLock, false);

		// Get the per group start callback and call it, if it indeed exists
		pActorGroup = pFirstActor->getGroup();
		if (pActorGroup != NULL)
		{
			iter = perGroupCallbackMap.find(pActorGroup->getName());
			if (iter != perGroupCallbackMap.end())
			{
				FunctorBase *pCallback = iter->second;

				// set parameters and execute
				if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
				{
					CollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CollisionCallbackLuaFunctor*>(pCallback);
					// parameters in LuaFunctor are set slightly differently
					pLuaFunctor->setParameter1(pFirstActor);
					pLuaFunctor->setParameter2(pSecondActor);
				}
				else
				{
					val.set(reinterpret_cast<void*>(pFirstActor));
					pCallback->setParameter(0, val);
					val.set(reinterpret_cast<void*>(pSecondActor));
					pCallback->setParameter(1, val);
				}
				// execute the callback
				(*pCallback)();
			}
		}

		// Get the per group start callback for the second actor and call it, if it indeed exists
		pActorGroup = pSecondActor->getGroup();
		if (pActorGroup != NULL)
		{
			iter = perGroupCallbackMap.find(pActorGroup->getName());
			if (iter != perGroupCallbackMap.end())
			{
				FunctorBase *pCallback = iter->second;

				// set parameters and execute
				if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
				{
					CollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CollisionCallbackLuaFunctor*>(pCallback);
					// parameters in LuaFunctor are set slightly differently
					pLuaFunctor->setParameter1(pFirstActor);
					pLuaFunctor->setParameter2(pSecondActor);
				}
				else
				{
					val.set(reinterpret_cast<void*>(pFirstActor));
					pCallback->setParameter(0, val);
					val.set(reinterpret_cast<void*>(pSecondActor));
					pCallback->setParameter(1, val);
				}
				// execute the callback
				(*pCallback)();
			}
		}
	}

	void CollisionManager::onStartTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor)
	{
		GameActorObject *pFirstGameActor;
		GameActorObject *pSecondGameActor;

		pFirstGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(firstActor->getName()));
		pSecondGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(secondActor->getName()));

		onTouchGeneric(mRWLockGlobalCallbacks, mpGlobalStartCallback, mRWLockPerActorStartCallbacks, mPerActorStartCallbacks
			, mRWLockPerGroupStartCallbacks, mPerGroupStartCallbacks, pFirstGameActor, pSecondGameActor);
	}

	void CollisionManager::onEndTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor)
	{
		GameActorObject *pFirstGameActor;
		GameActorObject *pSecondGameActor;

		pFirstGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(firstActor->getName()));
		pSecondGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(secondActor->getName()));

		onTouchGeneric(mRWLockGlobalCallbacks, mpGlobalStopCallback, mRWLockPerActorStopCallbacks, mPerActorStopCallbacks
			, mRWLockPerGroupStopCallbacks, mPerGroupStopCallbacks, pFirstGameActor, pSecondGameActor);
	}

	void CollisionManager::onTouch(NxOgre::Actor* firstActor, NxOgre::Actor* secondActor)
	{
		GameActorObject *pFirstGameActor;
		GameActorObject *pSecondGameActor;

		pFirstGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(firstActor->getName()));
		pSecondGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(secondActor->getName()));

		onTouchGeneric(mRWLockGlobalCallbacks, mpGlobalCallback, mRWLockPerActorCallbacks, mPerActorCallbacks
			, mRWLockPerGroupCallbacks, mPerGroupCallbacks, pFirstGameActor, pSecondGameActor);
	}

	NxOgre::CharacterHitReport::Response CollisionManager::onActor(NxOgre::Character* pCharacter, NxOgre::Actor* pActor, NxOgre::Shape* pShape, NxOgre::ActorGroup* pGroup, const NxControllerShapeHit& shapeHit)
	{
		GameCharacterObject* pGameCharacter;
		GameActorObject* pGameActor;
		CollisionProperties collisionProps;

		pGameCharacter = static_cast<GameCharacterObject*>(GameObjectFactory::getSingleton().findByName(pCharacter->getName()));
		pGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(pActor->getName()));

		collisionProps.mWorldPosition = Ogre::Vector3(shapeHit.worldPos.x, shapeHit.worldPos.y, shapeHit.worldPos.z);
		collisionProps.mWorldNormal = Ogre::Vector3(shapeHit.worldNormal.x, shapeHit.worldNormal.y, shapeHit.worldNormal.z);
		collisionProps.mDirection = Ogre::Vector3(shapeHit.dir.x, shapeHit.dir.y, shapeHit.dir.z);
		collisionProps.mLength = shapeHit.length;

		characterActorGeneric(mRWLockGlobalCharacterCallbacks, mpGlobalActorCharacterCallback, mRWLockPerActorCharacterCallbacks, mPerActorCharacterCallbacks
			, mRWLockPerGroupCharacterCallbacks, mPerGroupActorCharacterCallbacks, mRWLockPerCharacterActorCallbacks, mPerCharacterActorCallbacks
			, pGameCharacter, pGameActor, collisionProps);

		return NxOgre::CharacterHitReport::RS_Push;
	}

	NxOgre::CharacterHitReport::Response CollisionManager::onCharacterHit(NxOgre::Character* pCharacter, NxOgre::Actor* pActor, NxOgre::Shape* pShape, NxOgre::ActorGroup* pGroup, const NxControllersHit& controllerHit)
	{
		GameCharacterObject* pGameCharacter;
		GameActorObject* pGameActor;
		CollisionProperties collisionProps;

		pGameCharacter = static_cast<GameCharacterObject*>(GameObjectFactory::getSingleton().findByName(pCharacter->getName()));
		pGameActor = static_cast<GameActorObject*>(GameObjectFactory::getSingleton().findByName(pActor->getName()));

		collisionProps.mWorldPosition = Ogre::Vector3::ZERO;
		collisionProps.mWorldNormal = Ogre::Vector3::ZERO;
		collisionProps.mDirection = Ogre::Vector3::ZERO;
		collisionProps.mLength = 0;

		characterActorGeneric(mRWLockGlobalCharacterCallbacks, mpGlobalActorCharacterCallback, mRWLockPerActorCharacterCallbacks, mPerActorCharacterCallbacks
			, mRWLockPerGroupCharacterCallbacks, mPerGroupActorCharacterCallbacks, mRWLockPerCharacterActorCallbacks, mPerCharacterActorCallbacks
			, pGameCharacter, pGameActor, collisionProps);

		return NxOgre::CharacterHitReport::RS_Push;
	}

	void CollisionManager::setGlobalStartTouchCallback(FunctorBase* pCallback)
	{
		Poco::ScopedRWLock lock(mRWLockGlobalCallbacks, true);

		mpGlobalStartCallback = pCallback;
	}

	void CollisionManager::setGlobalEndTouchCallback(FunctorBase* pCallback)
	{
		Poco::ScopedRWLock lock(mRWLockGlobalCallbacks, true);

		mpGlobalStopCallback = pCallback;
	}

	void CollisionManager::setGlobalTouchCallback(FunctorBase* pCallback)
	{
		Poco::ScopedRWLock lock(mRWLockGlobalCallbacks, true);

		mpGlobalCallback = pCallback;
	}

	void CollisionManager::setPerGroupStartTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerGroupStartCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerGroupStartCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this group from the map, 
		// otherwise we set the callback for this group to pCallback
		if (pCallback == NULL)
		{
			mPerGroupStartCallbacks.erase(groupName);
		}
		else
		{
			mPerGroupStartCallbacks[groupName] = pCallback;
		}
	}

	void CollisionManager::setPerGroupEndTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerGroupStartCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerGroupStopCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this group from the map, 
		// otherwise we set the callback for this group to pCallback
		if (pCallback == NULL)
		{
			mPerGroupStopCallbacks.erase(groupName);
		}
		else
		{
			mPerGroupStopCallbacks[groupName] = pCallback;
		}
	}

	void CollisionManager::setPerGroupTouchCallback(const Ogre::String& groupName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerGroupStartCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerGroupCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this group from the map, 
		// otherwise we set the callback for this group to pCallback
		if (pCallback == NULL)
		{
			mPerGroupCallbacks.erase(groupName);
		}
		else
		{
			mPerGroupCallbacks[groupName] = pCallback;
		}
	}

	void CollisionManager::setPerActorStartTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception)
	{
		// Check that pGameActor is not NULL
		if (pGameActor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setPerActorStartTouchCallback(): pGameActor is NULL.");
		}

		// Acquire a write lock on the mPerActorStartCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorStartCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorStartCallbacks.erase(pGameActor->getName());
		}
		else
		{
			mPerActorStartCallbacks[pGameActor->getName()] = pCallback;
		}
	}

	void CollisionManager::setPerActorStartTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerActorStartCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorStartCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorStartCallbacks.erase(gameActorName);
		}
		else
		{
			mPerActorStartCallbacks[gameActorName] = pCallback;
		}
	}

	void CollisionManager::setPerActorEndTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback)  throw (Exception)
	{
		// Check that pGameActor is not NULL
		if (pGameActor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setPerActorStopTouchCallback(): pGameActor is NULL.");
		}

		// Acquire a write lock on the mPerActorStopCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorStopCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorStopCallbacks.erase(pGameActor->getName());
		}
		else
		{
			mPerActorStopCallbacks[pGameActor->getName()] = pCallback;
		}
	}

	void CollisionManager::setPerActorEndTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerActorStopCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorStopCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorStopCallbacks.erase(gameActorName);
		}
		else
		{
			mPerActorStopCallbacks[gameActorName] = pCallback;
		}
	}

	void CollisionManager::setPerActorTouchCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception)
	{
		// Check that pGameActor is not NULL
		if (pGameActor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setPerActorTouchCallback(): pGameActor is NULL.");
		}

		// Acquire a write lock on the mPerActorCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorCallbacks.erase(pGameActor->getName());
		}
		else
		{
			mPerActorCallbacks[pGameActor->getName()] = pCallback;
		}
	}

	void CollisionManager::setPerActorTouchCallback(const Ogre::String& gameActorName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerActorCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorCallbacks.erase(gameActorName);
		}
		else
		{
			mPerActorCallbacks[gameActorName] = pCallback;
		}
	}

	// Actor - Character collisions //

	void CollisionManager::enableActorCharacterCollisionReporting(Scene *pScene)
	{
		pScene->getWorld()->getCharacterController()->addHitReport(this);
	}

	void CollisionManager::characterActorGeneric(Poco::RWLock& globalRWLock, FunctorBase* pGlobalCallback, Poco::RWLock& perActorRWLock
		, CollisionManager::CollisionCallbackMap& perActorCharacterCallbackMap, Poco::RWLock& perGroupRWLock
		, CollisionManager::CollisionCallbackMap& perGroupCharacterCallbackMap, Poco::RWLock& perCharacterRWLock
		, CollisionManager::CollisionCallbackMap& perCharacterActorCallbackMap, GameCharacterObject* pCharacter, GameActorObject* pActor
		, CollisionManager::CollisionProperties collisionProps)
	{
		CollisionCallbackMapIterator iter;
		NxOgre::ActorGroup *pActorGroup;
		Value val;

		// Acquire a read lock on the global callbacks
		Poco::ScopedRWLock lockGlobal(globalRWLock, false);

		// set parameters and execute
		if (pGlobalCallback != NULL)
		{
			// set the parameters
			if (pGlobalCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CharacterActorCollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CharacterActorCollisionCallbackLuaFunctor*>(pGlobalCallback);
				// parameters in LuaFunctor are set slightly differently
				pLuaFunctor->setParameter1(pCharacter);
				pLuaFunctor->setParameter2(pActor);
				pLuaFunctor->setParameter3(collisionProps);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pCharacter));
				pGlobalCallback->setParameter(0, val);
				val.set(reinterpret_cast<void*>(pActor));
				pGlobalCallback->setParameter(1, val);
				val.set(reinterpret_cast<void*>(&collisionProps));
				pGlobalCallback->setParameter(2, val);
			}
			// execute the callback
			(*pGlobalCallback)();
		}

		// Acquire a read lock on the perActorCallbackMap
		Poco::ScopedRWLock lockPerActor(perActorRWLock, false);

		// Get the per actor callback and call it, if it indeed exists
		iter = perActorCharacterCallbackMap.find(pActor->getName());
		if (iter != perActorCharacterCallbackMap.end())
		{
			FunctorBase *pCallback = iter->second;

			// set parameters and execute
			if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CharacterActorCollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CharacterActorCollisionCallbackLuaFunctor*>(pCallback);
				// parameters in LuaFunctor are set slightly differently
				pLuaFunctor->setParameter1(pCharacter);
				pLuaFunctor->setParameter2(pActor);
				pLuaFunctor->setParameter3(collisionProps);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pCharacter));
				pCallback->setParameter(0, val);
				val.set(reinterpret_cast<void*>(pActor));
				pCallback->setParameter(1, val);
				val.set(reinterpret_cast<void*>(&collisionProps));
				pCallback->setParameter(2, val);
			}
			// execute the callback
			(*pCallback)();
		}

		// Acquire a read lock on the perGroupCallbackMap
		Poco::ScopedRWLock lockPerGroup(perGroupRWLock, false);

		// Get the per group callback and call it, if it indeed exists
		pActorGroup = pActor->getGroup();
		if (pActorGroup != NULL)
		{
			iter = perGroupCharacterCallbackMap.find(pActorGroup->getName());
			if (iter != perGroupCharacterCallbackMap.end())
			{
				FunctorBase *pCallback = iter->second;

				// set parameters and execute
				if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
				{
					CharacterActorCollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CharacterActorCollisionCallbackLuaFunctor*>(pCallback);
					// parameters in LuaFunctor are set slightly differently
					pLuaFunctor->setParameter1(pCharacter);
					pLuaFunctor->setParameter2(pActor);
					pLuaFunctor->setParameter3(collisionProps);
				}
				else
				{
					val.set(reinterpret_cast<void*>(pCharacter));
					pCallback->setParameter(0, val);
					val.set(reinterpret_cast<void*>(pActor));
					pCallback->setParameter(1, val);
					val.set(reinterpret_cast<void*>(&collisionProps));
					pCallback->setParameter(2, val);
				}
				// execute the callback
				(*pCallback)();
			}
		}

		// Acquire a read lock on the perCharacerActorCallbackMap
		Poco::ScopedRWLock lockPerCharacter(perCharacterRWLock, false);

		// Get the per character callback and call it, if it indeed exists
		iter = perCharacterActorCallbackMap.find(pCharacter->getName());
		if (iter != perCharacterActorCallbackMap.end())
		{
			FunctorBase *pCallback = iter->second;

			// set parameters and execute
			if (pCallback->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
			{
				CharacterActorCollisionCallbackLuaFunctor *pLuaFunctor = static_cast<CharacterActorCollisionCallbackLuaFunctor*>(pCallback);
				pLuaFunctor->setParameter1(pCharacter);
				pLuaFunctor->setParameter2(pActor);
				pLuaFunctor->setParameter3(collisionProps);
			}
			else
			{
				val.set(reinterpret_cast<void*>(pCharacter));
				pCallback->setParameter(0, val);
				val.set(reinterpret_cast<void*>(pActor));
				pCallback->setParameter(1, val);
				val.set(reinterpret_cast<void*>(&collisionProps));
				pCallback->setParameter(2, val);
			}
			// execute the callback
			(*pCallback)();
		}
	}

	void CollisionManager::setGlobalActorCharacterCallback(FunctorBase* pCallback)
	{
		Poco::ScopedRWLock lock(mRWLockGlobalCharacterCallbacks, true);

		mpGlobalActorCharacterCallback = pCallback;
	}

	void CollisionManager::setPerGroupCharacterCallback(const Ogre::String& groupName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerGroupCharacterCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerGroupCharacterCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this group from the map, 
		// otherwise we set the callback for this group to pCallback
		if (pCallback == NULL)
		{
			mPerGroupActorCharacterCallbacks.erase(groupName);
		}
		else
		{
			mPerGroupActorCharacterCallbacks[groupName] = pCallback;
		}
	}

	void CollisionManager::setPerActorCharacterCallback(GameActorObject* pGameActor, FunctorBase* pCallback) throw (Exception)
	{
		// Check that pGameActor is not NULL
		if (pGameActor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setPerActorCharacterCallback(): pGameActor is NULL.");
		}

		// Acquire a write lock on the mPerActorCharacterCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCharacterCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorCharacterCallbacks.erase(pGameActor->getName());
		}
		else
		{
			mPerActorCharacterCallbacks[pGameActor->getName()] = pCallback;
		}
	}

	void CollisionManager::setPerActorCharacterCallback(const Ogre::String& gameActorName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerActorCharacterCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCharacterCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerActorCharacterCallbacks.erase(gameActorName);
		}
		else
		{
			mPerActorCharacterCallbacks[gameActorName] = pCallback;
		}
	}

	void CollisionManager::setPerCharacterActorCallback(GameCharacterObject* pGameCharacter, FunctorBase* pCallback) throw (Exception)
	{
		// Check that pGameActor is not NULL
		if (pGameCharacter == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "CollisionManager::setPerCharacterActorCallback(): pGameCharacter is NULL.");
		}

		// Acquire a write lock on the mPerCharacterActorCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCharacterCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerCharacterActorCallbacks.erase(pGameCharacter->getName());
		}
		else
		{
			mPerCharacterActorCallbacks[pGameCharacter->getName()] = pCallback;
		}
	}

	void CollisionManager::setPerCharacterActorCallback(const Ogre::String& gameCharacterName, FunctorBase* pCallback)
	{
		// Acquire a write lock on the mPerCharacterActorCallbacks map
		Poco::ScopedRWLock lock(mRWLockPerActorCharacterCallbacks, true);

		// If pCallback is NULL we remove any existing callback for this actor from the map, 
		// otherwise we set the callback for this actor to pCallback
		if (pCallback == NULL)
		{
			mPerCharacterActorCallbacks.erase(gameCharacterName);
		}
		else
		{
			mPerCharacterActorCallbacks[gameCharacterName] = pCallback;
		}
	}

} // namespace Myoushu

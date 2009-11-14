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
 * @file GameObject.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <string>

#include "Poco/RefCountedObject.h"
#include "Ogre.h"

#include "Platform.h"
#include "NamedObject.h"
#include "NamedInstance.h"
#include "GameObjectAction.h"
#include "KeyValueProperties.h"
#include "Serializable.h"
#include "Scene.h"

namespace Myoushu
{
	/**
	 * The base class for all static and dynamic objects in the game, for instance, tables, chairs or character avatars. It extends from 
	 * the Actor class for collision detection and physics.
	 */
	class MYOUSHU_API GameObject : public NamedObject<GameObject>, public NamedInstance, public Poco::RefCountedObject
	{
		public:
			/** 
			 * Constructor 
			 * @param name The unique name of the GameObject instance.
			 */
			GameObject(const Ogre::String& name);

			/** Destructor */			 
			~GameObject();

			CLASS_NAME_FUNCTIONS(GameObject);

			/**
			 * Binds a GameObjectAction to this GameObject instance.
			 * @param action The GameObjectAction instance to add to this GameObject. This object takes ownership of action
			 *				 and will destroy it when appropriate.
			 * @throws Exception::E_NULL_POINTER if action is NULL.
			 */
			void addAction(GameObjectAction *action) throw (Exception);

			/**
			 * Gets the GameObjectAction instance with the specified name that has been bound to this
			 * object.
			 * @param actionName The name of the GameObjectAction instance to get.
			 * @return The GameObjectAction instance with the specified name, or NULL if no such instance
			 *		   could be found.
			 */
			GameObjectAction* getAction(const Ogre::String& actionName);

			/**
			 * Fire a start action event.
			 * @param action The name of the character action.
			 * @return true if the action is defined and was fired, false otherwise.
			 */
			bool startAction(const Ogre::String& actionName);

			/**
			 * Fire a stopaction event.
			 * @param action The name of the character action.
			 * @return true if the action is defined and was fired, false otherwise.
			 */
			bool stopAction(const Ogre::String& actionName);

			/** Gets the KeyValueProperties instance of this GameObject. */
			KeyValueProperties& getProperties();

			/** Gets the KeyValueProperties instance pointer of this GameObject. */
			KeyValueProperties* getPropertiesPtr();

			/** Gets the KeyValueProperties instance of this GameObject. */
			const KeyValueProperties& getProperties() const;

			/** Gets the KeyValueProperties instance pointer of this GameObject. */
			const KeyValueProperties* getPropertiesPtr() const;

			/** 
			 * Gets the Scene instance that contains this GameObject instance. By default
			 * this function returns NULL in the GameObject class, since there is no logical way
			 * to place a GameObject in a scene. Inheriting classes such as GameActorObject and
			 * GameBodyObject can be placed in Scenes and such inheriting class shall override
			 * this function to return their parent Scene instance.
			 */
			virtual Scene* getScene();

			/**
			 * Gets the up vector for this game object. For base game objects this function just
			 * returns calls getLocalUpVector. Extending classes must implement this function for more appropriate
			 * functionality.
			 */
			virtual Ogre::Vector3 getGlobalUpVector();

			/** Gets the local up vector of this object. The default value is 0 1 0. */
			Ogre::Vector3 getLocalUpVector();

			/** Sets the local up vector of this object. */
			void setLocalUpVector(const Ogre::Vector3& upVector);

			/**
			 * Gets the vector that defines the global forward facing direction of this object.
			 * The default implementation just calls getLocalForwardVector(). Extending classes
			 * must implement this function for more appropriate functionality.
			 */
			virtual Ogre::Vector3 getGlobalForwardVector();

			/** Gets the local forward vector of this object. The default value is 0 0 -1. */
			Ogre::Vector3 getLocalForwardVector();

			/** Sets the local forward vector of this object. */
			void setLocalForwardVector(const Ogre::Vector3& forwardVector);

			/**
			 * Equality operator. GameObjects must have unique names. Thus object with the same names are considered
			 * to be the same object.
			 * @param object The instance to test for equality with this instance.
			 */
			bool operator==(const GameObject& object);

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

		protected:
			/** Type definition for a map of action strings to GameObjectAction instances */
			typedef std::map<Ogre::String, Poco::AutoPtr<GameObjectAction> > ActionMapType;
			/** Type definition for an entry in the map of action strings to GameObjectAction instances */
			typedef std::pair<Ogre::String, Poco::AutoPtr<GameObjectAction> > ActionMapEntry;
			/** Type definition for the iterator type of the action map. */
			typedef ActionMapType::iterator ActionMapIterator;
			/** Type definition for the const iterator type of the action map. */
			typedef ActionMapType::const_iterator ActionMapConstIterator;

			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** A map of GameObjectActions */
			ActionMapType actionMap;
			/** The KeyValueProperties instance of the GameObject. */
			KeyValueProperties mProperties;
			/** A vector defining the up direction of the object in its local frame of reference. */
			Ogre::Vector3 mLocalUpVector;
			/** A vector defining the forward direction of the object in its local frame of reference. */
			Ogre::Vector3 mLocalForwardVector;

		private:
			/** Nullary Constructor */
			GameObject();
	};

	// inlines
	inline Ogre::Vector3 GameObject::getGlobalUpVector()
	{
		return getLocalUpVector();
	}

	inline Ogre::Vector3 GameObject::getLocalUpVector()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mLocalUpVector;
	}

	inline void GameObject::setLocalUpVector(const Ogre::Vector3& upVector)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mLocalUpVector = upVector;
	}

	inline Ogre::Vector3 GameObject::getGlobalForwardVector()
	{
		return getLocalForwardVector();
	}

	inline Ogre::Vector3 GameObject::getLocalForwardVector()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mLocalForwardVector;
	}

	inline void GameObject::setLocalForwardVector(const Ogre::Vector3& forwardVector)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mLocalForwardVector = forwardVector;
	}

	inline KeyValueProperties& GameObject::getProperties()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mProperties;
	}

	inline KeyValueProperties* GameObject::getPropertiesPtr()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return &mProperties;
	}

	inline const KeyValueProperties& GameObject::getProperties() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mProperties;
	}

	inline const KeyValueProperties* GameObject::getPropertiesPtr() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return &mProperties;
	}

	inline Scene* GameObject::getScene()
	{
		return NULL;
	}

	inline bool GameObject::operator==(const GameObject& object)
	{
		return (getName() == object.getName());
	}
} // Myoushu

#endif

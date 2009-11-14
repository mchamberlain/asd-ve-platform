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
 * @file GameObjectAction.h
 * @author ME Chamberlain
 * @date October 2008
 */

#ifndef MYOUSHU_GAME_OBJECT_ACTION_H
#define MYOUSHU_GAME_OBJECT_ACTION_H

#include "Ogre.h"
#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "NamedInstance.h"
#include "NamedObject.h"
#include "NamedObjectInstanceCreator.h"
#include "ActionStringCallbackBase.h"
#include "ActionStringCallback.h"
#include "ActionStringClassCallback.h"
#include "Exception.h"
#include "Serializable.h"

namespace Myoushu
{

	/** Forward declaration for GameObject because of circular dependancy. */
	class GameObject;

	/**
	 * This class stores information about a generic character action. It stores information about possibly
	 * playing an animation when a character action is fired. It also has start and stop function callbacks.
	 * A start callback can be seen as associated with a button press on a controller and a stop callback with a button release.
	 * For a toggle action one would implement the toggle code in the start callback and nothing in the stop callback, for instance.
	 */
	class MYOUSHU_API GameObjectAction : public NamedInstance, public Poco::RefCountedObject, public NamedObjectInstanceCreator<GameObjectAction>
	{
		public:
			/** The base class for callbacks from GameObjectAction instances. */
			typedef ActionStringCallbackBase<void, GameObjectAction> GameObjectActionCallbackBase;

			/** A global function, lua function or generic FunctorBase based callback for a GameObjectAction. */
			typedef ActionStringCallback<void, GameObjectAction> GameObjectActionCallback;

			/** A pointer to a global function return void and taking a GameObjectObjectAction pointer as a parameter. */
			typedef ActionStringCallback<void, GameObjectAction>::ActionStringCallbackGlobalFunction GameObjectActionCallbackGlobalFunction;

			/** The LuaFunctor type used for Lua callbacks. */
			typedef ActionStringCallback<void, GameObjectAction>::ActionStringCallbackLuaFunctor GameObjectActionCallbackLuaFunctor;

			/** Nullary Constructor. Should only be used in conjunction with Serializable::populateInstance(). */
			GameObjectAction();

			/**
			 * Constructor.
			 * @param name The name of the action.
			 * @param gameObject The GameObject instance this action is bound to.
			 * @param toggleAction Flag indicating whether this is a toggle action. Toggle actions only use action start 
			 *					   callbacks (no stop callbacks) and the animation is toggled on or off every time the 
			 *					   action is started.
			 * @param animationName The name of the character animation to play, if any.
			 * @param animBehaviour The manner in which to play the animation, loop, once, only one frame.
			 * @param restartAnimation Flag indicating whether the animation should be restarted when the action is started.
			 * @param playCounter If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 *					  increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 *					  if the counter is zero. This is useful in situations where there are multiple actions that play the
			 *					  same animation.
			 */
			GameObjectAction(const Ogre::String& name, GameObject *gameObject, bool toggleAction = false) throw (Exception);

			/** Destructor. */
			virtual ~GameObjectAction();

			CLASS_NAME_FUNCTIONS(GameObjectAction);

			/**
			 * Sets the action start callback to the specified callback instance.
			 * @param startCallback The GameObjectActionCallbackBase instance to set the action start callback to.
			 * @throws Exception::E_NULL_POINTER if startCallback is NULL.
			 */
			void setStartCallback(GameObjectActionCallbackBase *startCallback) throw (Exception);

			/**
			 * Sets the action start callback to the specified global function. 
			 * Functions are of the form void functionName(GameObject*).
			 * @param functionPtr Pointer to the global function to set as the action start callback.
			 * @throws Exception::E_NULL_POINTER if functionPtr is NULL.
			 */
			void setStartCallback(GameObjectActionCallbackGlobalFunction functionPtr) throw (Exception);

			/**
			 * Sets the action start callback to the specified Lua function.
			 * @param luaFunction The name of the Lua function to call for the action start callback.
			 */
			void setStartCallback(const Ogre::String& luaFunction);

			/**
			 * Sets the action start callback to the specified Lua function.
			 * @param luaFunction Pointer to the GameObjectActionCallbackLuaFunctor instance that defines the Lua function to call
			 *					  for the action start callback.
			 * @throws Exception::E_NULL_POINTER if luaFunction is NULL.
			 */
			void setStartCallback(GameObjectActionCallbackLuaFunctor *luaFunction) throw (Exception);

			/**
			 * Sets the action start callback to the specified class method.
			 * Functions are of the form void C::functionName(GameObject*).
			 * @param functionPtr Pointer to the global function to set as the action start callback.
			 * @throws Exception::E_NULL_POINTER if classPtr or functionPtr is NULL.
			 */
			template <class C>
			void setStartCallback(C *classPtr, void (C::*functionPtr)(GameObjectAction*)) throw (Exception);

			/**
			 * Sets the action stop callback to the specified callback instance.
			 * @param stopCallback The GameObjectActionCallbackBase instance to set the action stop callback to.
			 * @throws Exception::E_NULL_POINTER if stopCallback is NULL.
			 */
			void setStopCallback(GameObjectActionCallbackBase *stopCallback) throw (Exception);

			/**
			 * Sets the action stop callback to the specified global function. 
			 * Functions are of the form void functionName(GameObject*).
			 * @param functionPtr Pointer to the global function to set as the action stop callback.
			 * @throws Exception::E_NULL_POINTER if functionPtr is NULL.
			 */
			void setStopCallback(GameObjectActionCallbackGlobalFunction functionPtr) throw (Exception);

			/**
			 * Sets the action stop callback to the specified Lua function.
			 * @param luaFunction The name of the Lua function to call for the action stop callback.
			 */
			void setStopCallback(const Ogre::String& luaFunction);

			/**
			 * Sets the action stop callback to the specified Lua function.
			 * @param luaFunction Pointer to the GameObjectActionCallbackLuaFunctor instance that defines the Lua function to call
			 *					  for the action stop callback.
			 * @throws Exception::E_NULL_POINTER if luaFunction is NULL.
			 */
			void setStopCallback(GameObjectActionCallbackLuaFunctor *luaFunction) throw (Exception);

			/**
			 * Sets the action stop callback to the specified class method.
			 * Functions are of the form void C::functionName(GameObject*).
			 * @param functionPtr Pointer to the global function to set as the action stop callback.
			 * @throws Exception::E_NULL_POINTER if classPtr or functionPtr is NULL.
			 */
			template <class C>
			void setStopCallback(C *classPtr, void (C::*functionPtr)(GameObjectAction*)) throw (Exception);

			/** This function is called when the action is started. */
			virtual void startAction();

			/** This function is called when the action is stopped. */
			virtual void stopAction();

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
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** The GameObject this action instance is bound to. */
			GameObject *mGameObject;
			/** Flag indicating whether this is a toggle action. Toggle actions only use action start callbacks (no stop callbacks)
			 * and the animation is toggled on or off every time the action is started. */
			bool mToggleAction;
			/** The callback to use when the action is started. */
			Poco::AutoPtr<GameObjectActionCallbackBase> mpStartCallback;
			/** The callback to use when the action is stopped. */
			Poco::AutoPtr<GameObjectActionCallbackBase> mpStopCallback;
	};

	// templated functions
	template <class C>
	void GameObjectAction::setStartCallback(C *classPtr, void (C::*functionPtr)(GameObjectAction*)) throw (Exception)
	{
		ActionStringClassCallback<void, C, GameObjectAction> *callback;

		// Create the callback, this throws an exception if classPtr or functionPtr is NULL
		callback = new ActionStringClassCallback<void, C, GameObjectAction>(getName() + "_start", classPtr, functionPtr);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		mpStartCallback = callback;
	}

	template <class C>
	void GameObjectAction::setStopCallback(C *classPtr, void (C::*functionPtr)(GameObjectAction*)) throw (Exception)
	{
		ActionStringClassCallback<void, C, GameObjectAction> *callback;

		// Create the callback, this throws an exception if classPtr or functionPtr is NULL
		callback = new ActionStringClassCallback<void, C, GameObjectAction>(getName() + "_stop", classPtr, functionPtr);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		mpStopCallback = callback;
	}

} // namespace Myoushu

#endif

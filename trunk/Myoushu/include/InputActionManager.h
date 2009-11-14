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
 * @file InputActionManager.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef INPUT_ACTION_MANAGER_H
#define INPUT_ACTION_MANAGER_H

#include <string>
#include <map>
#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "InputActionCallbackBase.h"
#include "InputActionCallback.h"
#include "ActionStringClassCallback.h"

namespace Myoushu
{
	/**
	 * Manages the binding of input action strings to callback functions and functors. It is used to define a function that must be called when
	 * input actions occur, due to key presses for example.
	 */
	class MYOUSHU_API InputActionManager : public Ogre::Singleton<InputActionManager>
	{
		public:
			/** Iterator type for the action event multi map */
			typedef std::multimap<std::string, Poco::AutoPtr<InputActionCallbackBase> >::iterator ActionEventMapIter;

			/** Constant iterator for the action event multi map */
			typedef std::multimap<std::string, Poco::AutoPtr<InputActionCallbackBase> >::const_iterator ActionEventMapConstIter;

			/** A typedef for the entries in the multi map */
			typedef std::pair<std::string, Poco::AutoPtr<InputActionCallbackBase> > ActionEventMapEntry;

			/** Constructor. */
			InputActionManager();

			/** Destructor */
			virtual ~InputActionManager();

			/** Disables all callbacks for all actions (present and future). */
			void disableCallbacks();

			/** Disables all callbacks for all actions, except those actions specified in the exceptions set. */
			void disableCallbacks(const std::list<std::string>& exceptions);

			/** Enables all callbacks for all actions. */
			void enableCallbacks();

			/**
			 * Returns the value of the mCallbacksDisabled flag. If callbacks are disabled there might be some actions that are
			 * exempt, use isCallbacksForActionEnabled() to test a specific action.
			 */
			bool isCallbacksDisabled();

			/** Checks whether the callbacks for the specified action is enabled. */
			bool isCallbacksForActionEnabled(const std::string& action);

			/**
			 * Checks whether the specified input action already exists in the system.
			 * @param inputAction The input action string to check for.
			 * @return true if the input action exists, false otherwise.
			 */
			bool actionExists(const std::string& inputAction);

			/**
			 * Gets all of the callbacks associated with the specified input action and puts them into the
			 * specified std::list.
			 * @param inputAction The input action string
			 * @param list The list to insert the callbacks into. If the list is emtpy after the function call, then
			 * 						 there are no callbacks registered for the action.
			 */
			void getInputActionCallbacks(const std::string& inputAction, std::list<InputActionCallbackBase *> &list);

			/**
			 * Gets all of the callbacks associated with the specified input action.
			 * @param inputAction The input action string
			 * @return NULL if no callbacks were found, or a pointer to a std::list of InputActionCallbackBase
			 *				 pointers. The user must free the list when done.
			 */
			std::list<InputActionCallbackBase *>* getInputActionCallbacks(const std::string& inputAction);

			/**
			 * Add a callback for an input action. If the input action specified does not exist, it will be
			 * created. The InputActionManager takes ownership of inputActionCallback.
			 * @param inputActionCallback The InputActionCallbackBase instance to associate with this inputAction.
			 * @throws Exception::E_NULL_POINTER if inputActionCallback is NULL.
			 */
			void addInputActionCallback(InputActionCallbackBase *inputActionCallback) throw (Exception);

			/**
			 * Add a callback to a global function for an input action. If the input action specified does not exist, it will be
			 * created.
			 * @param inputAction The input action string.
			 * @param functionPtr Pointer to the global function to use as callback for this input action.
			 * @throws Exception::E_NULL_POINTER if functionPtr is NULL.
			 */
			void addInputActionCallback(const std::string& inputAction, InputActionCallbackGlobalFunction functionPtr) throw (Exception);

			/**
			 * Add a callback to a lua function that takes an InputMessage* as parameter, for an input action. If the input action specified does not exist, it will be
			 * created.
			 * @param inputAction The input action string.
			 * @param luaFunction The name of the luaFunction.
			 */
			void addInputActionCallback(const std::string& inputAction, const std::string& luaFunction);

			/**
			 * Add a callback to a lua function for an input action. If the input action specified does not exist, it will be
			 * created. The InputActionManager takes ownership of luaFunction.
			 * @param inputAction The input action string.
			 * @param luaFunction Pointer to a LuaFunctor instance.
			 * @throws Exception::E_NULL_POINTER if luaFunction is NULL.
			 */
			void addInputActionCallback(const std::string& inputAction, InputActionCallbackLuaFunctor *luaFunction) throw (Exception);

			/**
			 * Add a callback to a function wrapped in FunctorBase for an input action. If the input action specified does not exist, it will be
			 * created. The InputActionManager takes ownership of pFunctor.
			 * @param inputAction The input action string.
			 * @param pFunctor Pointer to a FunctorBase instance instance.
			 * @throws Exception::E_NULL_POINTER if luaFunction is NULL.
			 */
			void addInputActionCallback(const std::string& inputAction, FunctorBase *pFunctor) throw (Exception);

			/**
			 * Add a callback to a class method for an input action. If the input action specified does not exist, it will be
			 * created.
			 * @param inputAction The input action string.
			 * @param classPtr Pointer to the class instance to call the method from.
			 * @param functionPtr Pointer to the class method.
			 * @throws Exception::E_NULL_POINTER if classPtr or functionPtr is NULL.
			 */
			template <class C>
			void addInputActionCallback(const std::string& inputAction, C *classPtr, void (C::*functionPtr)(InputMessage*)) throw (Exception)
			{
				ActionStringClassCallback<void, C, InputMessage> *callback;

				// Create the callback, this throws an exception if classPtr or functionPtr is NULL
				callback = new ActionStringClassCallback<void, C, InputMessage>(inputAction, classPtr, functionPtr);

				// Add the callback to the multimap
				Poco::ScopedRWLock lock(rwLock, true);
				actionEventMap.insert(ActionEventMapEntry(inputAction, callback));
			}

			/**
			 * Removes all callbacks associated with the specified inputAction.
			 * @param inputAction The input action to remove.
			 */
			void removeInputAction(const std::string& inputAction);

		protected:
			/** read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** Flag indicating whether all callbacks are disabled. */
			bool mCallbacksDisabled;
			/** 
			 * A set used when mCallbacksDisabled is true. Actions in this list do not have their callbacks
			 * disabled when mCallbacksDisabled is true.
			 */
			std::set<std::string> mDisableExceptions;

		private:
			/** InputAction and event mappings */
			std::multimap<std::string, Poco::AutoPtr<InputActionCallbackBase> > actionEventMap;
	};

	// inlines
	inline bool InputActionManager::isCallbacksDisabled()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mCallbacksDisabled;
	}

} // Myoushu

#endif

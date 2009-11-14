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
 * @file InputActionManager.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "InputActionManager.h"

//template<>
//Myoushu::InputActionManager* Ogre::Singleton<Myoushu::InputActionManager>::ms_Singleton = NULL;

namespace Myoushu
{
	InputActionManager::InputActionManager() : mCallbacksDisabled(false)
	{
	}

	InputActionManager::~InputActionManager()
	{
		// Clear the action event map
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.clear();
	}

	void InputActionManager::disableCallbacks()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (mCallbacksDisabled)
		{
			LOG(EngineLog::LM_WARNING, "InputActionManager::disableCallbacks(): callbacks already disabled, ignoring...");
			return;
		}

		mDisableExceptions.clear();
		mCallbacksDisabled = true;
	}

	void InputActionManager::disableCallbacks(const std::list<std::string>& exceptions)
	{
		std::list<std::string>::const_iterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		if (mCallbacksDisabled)
		{
			LOG(EngineLog::LM_WARNING, "InputActionManager::disableCallbacks(exceptions): callbacks already disabled, ignoring...");
			return;
		}

		mCallbacksDisabled = true;
		mDisableExceptions.clear();
		for (iter = exceptions.begin(); iter != exceptions.end(); ++iter)
		{
			mDisableExceptions.insert(*iter);
		}
	}

	void InputActionManager::enableCallbacks()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mCallbacksDisabled = false;
		mDisableExceptions.clear();
	}

	bool InputActionManager::isCallbacksForActionEnabled(const std::string& action)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (!mCallbacksDisabled)
		{
			return true;
		}

		return (mDisableExceptions.find(action) != mDisableExceptions.end());
	}

	bool InputActionManager::actionExists(const std::string& inputAction)
	{
		std::pair<ActionEventMapIter, ActionEventMapIter> range;
		ActionEventMapIter iter;

		// Get the range of callbacks for the specified input action
		range = actionEventMap.equal_range(inputAction);

		// If there are no callbacks, return NULL
		if (range.first == range.second)
		{
			return false;
		}

		return true;
	}

	std::list<InputActionCallbackBase *>* InputActionManager::getInputActionCallbacks(const std::string& inputAction)
	{
		std::list<InputActionCallbackBase *> *list;
		std::pair<ActionEventMapIter, ActionEventMapIter> range;
		ActionEventMapIter iter;

		// Get the range of callbacks for the specified input action
		range = actionEventMap.equal_range(inputAction);

		// If there are no callbacks, return NULL
		if (range.first == range.second)
		{
			return NULL;
		}

		// Create the list
		list = new std::list<InputActionCallbackBase *>();

		// Fill the list
		for (iter = range.first; iter != range.second; ++iter)
		{
			Poco::AutoPtr<InputActionCallbackBase>& pCallback = iter->second;
			list->push_back(pCallback.get());
		}

		return list;
	}

	void InputActionManager::getInputActionCallbacks(const std::string& inputAction, std::list<InputActionCallbackBase *> &list)
	{
		std::pair<ActionEventMapIter, ActionEventMapIter> range;
		ActionEventMapIter iter;

		// Empty the list
		list.clear();

		// Get the range of callbacks for the specified input action
		range = actionEventMap.equal_range(inputAction);

		// If there are no callbacks, return NULL
		if (range.first == range.second)
		{
			return;
		}

		// Fill the list
		for (iter = range.first; iter != range.second; ++iter)
		{
			Poco::AutoPtr<InputActionCallbackBase>& pCallback = iter->second;
			list.push_back(pCallback.get());
		}
	}

	void InputActionManager::addInputActionCallback(InputActionCallbackBase *inputActionCallback) throw (Exception)
	{
		// Make sure inputActionCallback is not NULL
		if (inputActionCallback == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputActionManager::addInputActionCallback(): inputActionCallback is NULL.");
		}

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.insert(ActionEventMapEntry(inputActionCallback->getActionString(), inputActionCallback));
	}

	void InputActionManager::addInputActionCallback(const std::string& inputAction, InputActionCallbackGlobalFunction functionPtr) throw (Exception)
	{
		InputActionCallback *callback;

		// Make sure functionPtr is not NULL
		if (functionPtr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputActionManager::addInputActionCallback(): functionPtr is NULL.");
		}

		// Create the InputActionCallback instance
		callback = new InputActionCallback(inputAction, functionPtr);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.insert(ActionEventMapEntry(inputAction, callback));
	}

	void InputActionManager::addInputActionCallback(const std::string& inputAction, const std::string& luaFunction)
	{
		InputActionCallback *callback;

		// Create the InputActionCallback instance
		callback = new InputActionCallback(inputAction, luaFunction);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.insert(ActionEventMapEntry(inputAction, callback));
	}

	void InputActionManager::addInputActionCallback(const std::string& inputAction, InputActionCallbackLuaFunctor *luaFunction) throw (Exception)
	{
		InputActionCallback *callback;

		// Create the InputActionCallback instance, throws an exception if luaFunction is NULL.
		callback = new InputActionCallback(inputAction, luaFunction);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.insert(ActionEventMapEntry(inputAction, callback));
	}

	void InputActionManager::addInputActionCallback(const std::string& inputAction, FunctorBase *pFunctor) throw (Exception)
	{
		InputActionCallback *callback;

		// Create the InputActionCallback instance, throws an exception if luaFunction is NULL.
		callback = new InputActionCallback(inputAction, pFunctor);

		// Add the callback to the multimap
		Poco::ScopedRWLock lock(rwLock, true);
		actionEventMap.insert(ActionEventMapEntry(inputAction, callback));
	}

	void InputActionManager::removeInputAction(const std::string& inputAction)
	{

		Poco::ScopedRWLock lock(rwLock, true);

		actionEventMap.erase(inputAction);
	}

} // Myoushu

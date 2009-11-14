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
 * @file ActionStringCallback.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef ACTION_STRING_CALLBACK_H
#define ACTION_STRING_CALLBACK_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "ActionStringCallbackBase.h"
#include "FunctorBase.h"
#include "LuaFunctor.h"
#include "ScriptManager.h"
#include "NamedObject.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * This class wraps a callback for a specified actionString. The actionString is bound to
	 * an ActionStringCallback instance which is used to determine which function to
	 * call, if any. 
	 *
	 * The function signature for event callbacks is:
	 * {@code RT functionName(T*)}
	 * It can be a global function, a Lua function or any instance that extends FunctorBase.
	 */
	template<class RT, class T>
	class ActionStringCallback : public ActionStringCallbackBase<RT, T>
	{
		public:
			/** A pointer to a global function return void and taking a InputMessage pointer as a parameter. */
			typedef RT (*ActionStringCallbackGlobalFunction)(T*);
			/** The LuaFunctor type used for Lua callbacks. */
			typedef typename Myoushu::LuaFunctor<void, 1, Poco::AutoPtr<T> > ActionStringCallbackLuaFunctor;

			/**
			 * Constructor for a lua function based callback.
			 * @param actionString The input action string
			 * @param luaFunction String containing the lua function to call.
			 */
			ActionStringCallback(const std::string& actionString, const std::string& luaFunction);

			/**
			 * Constructor for a lua function based callback. The ActionStringCallback instance takes ownership
			 * of the ActionStringCallbackLuaFunctor instance passed to it.
			 * @param actionString The input action string
			 * @param luaFunction ActionStringCallbackLuaFunctor instance wrapping the lua function to call
			 *										for this input action.
			 * @throws Exception::E_NULL_POINTER if luaFunction is NULL.
			 */
			ActionStringCallback(const std::string& actionString, ActionStringCallbackLuaFunctor *luaFunction) throw (Exception);

			/**
			 * Constructor for a lua function based callback.
			 * @param actionString The input action string
			 * @param functionPtr Pointer to the a global function to use as callback
			 * @throws Exception::E_NULL_POINTER if functionPtr is NULL.
			 */
			ActionStringCallback(const std::string& actionString, ActionStringCallbackGlobalFunction functionPtr) throw (Exception);

			/**
			 * Constructor for a generic functor based callback.
			 * @param actionString The input action string
			 * @param pFunctor Pointer to an instance that extends from FunctorBase.
			 * @throws Exception::E_NULL_POINTER if pFunctor is NULL.
			 */
			ActionStringCallback(const std::string& actionString, FunctorBase *pFunctor) throw (Exception);

			/** Destructor. */
			~ActionStringCallback();

			/**
			 * Getter for the luaFunction functor.
			 * @return The luaFunction functor.
			 */
			const ActionStringCallbackLuaFunctor* getLuaFunction() const;

			/**
			 * Getter for the luaFunction functor.
			 * @return The luaFunction functor.
			 */
			ActionStringCallbackLuaFunctor* getLuaFunction();

			/**
			 * Getter for the pointer to a global callback function.
			 * @return a function pointer.
			 */
			ActionStringCallbackGlobalFunction getFunctionPtr();

			/** Getter for the mFunctor field, an instance that extends from FunctorBase. */
			const FunctorBase* getFunctor() const;

			/** Getter for the mFunctor field, an instance that extends from FunctorBase. */
			FunctorBase* getFunctor();

			/**
			 * Execute the callback function.
			 * @param parameter The parameter for the callback function call.
			 */
			RT executeCallback(T *parameter);

		private:
			/** Pointer to a global function to use as a callback */
			ActionStringCallbackGlobalFunction functionPtr;
			/** LuaFunctor containing a lua function to use as a callback */
			Poco::AutoPtr<ActionStringCallbackLuaFunctor> luaFunction;
			/** Any functor implementation that extends from FunctorBase. */
			Poco::AutoPtr<FunctorBase> mFunctor;

			/** Nullary Constructor */
			ActionStringCallback();
	};

	// inlines
	template<class RT, class T>
	inline const typename ActionStringCallback<RT, T>::ActionStringCallbackLuaFunctor* ActionStringCallback<RT, T>::getLuaFunction() const
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return luaFunction;
	}

	template<class RT, class T>
	inline typename ActionStringCallback<RT, T>::ActionStringCallbackLuaFunctor* ActionStringCallback<RT, T>::getLuaFunction()
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return luaFunction;
	}

	template<class RT, class T>
	inline typename ActionStringCallback<RT, T>::ActionStringCallbackGlobalFunction ActionStringCallback<RT, T>::getFunctionPtr()
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return functionPtr;
	}

	template<class RT, class T>
	inline const FunctorBase* ActionStringCallback<RT, T>::getFunctor() const
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return mFunctor.get();
	}

	template<class RT, class T>
	inline FunctorBase* ActionStringCallback<RT, T>::getFunctor()
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return mFunctor.get();
	}

	// non-inlines
	template<class RT, class T>
	ActionStringCallback<RT, T>::ActionStringCallback(const std::string& actionString, const std::string& luaFunction)
	: ActionStringCallbackBase<RT, T>(actionString), functionPtr(NULL),
		luaFunction(new ActionStringCallbackLuaFunctor(luaFunction, NamedObject<T>::getStaticClassName() + "*")),
		mFunctor(NULL)
	{
	}

	template<class RT, class T>
	ActionStringCallback<RT, T>::ActionStringCallback(const std::string& actionString, ActionStringCallbackLuaFunctor *luaFunction) throw (Exception)
	: ActionStringCallbackBase<RT, T>(actionString), functionPtr(NULL), luaFunction(luaFunction), mFunctor(NULL)
	{
		// Make sure that luaFunction is not NULL
		if (luaFunction == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ActionStringCallback::ActionStringCallback(): luaFunction is NULL");
		}
	}

	template<class RT, class T>
	ActionStringCallback<RT, T>::ActionStringCallback(const std::string& actionString, ActionStringCallbackGlobalFunction functionPtr) throw (Exception) 
		: ActionStringCallbackBase<RT, T>(actionString), functionPtr(functionPtr), luaFunction(NULL), mFunctor(NULL)
	{
		// Check that functionPtr is not NULL
		if (functionPtr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputActonCallback::ActionStringCallback(): functionPtr is NULL.");
		}
	}

	template<class RT, class T>
	ActionStringCallback<RT, T>::ActionStringCallback(const std::string& actionString, FunctorBase *pFunctor) throw (Exception) 
		: ActionStringCallbackBase<RT, T>(actionString), functionPtr(NULL), luaFunction(NULL), mFunctor(pFunctor)
	{
		// Check that pFunctor is not NULL
		if (pFunctor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "InputActonCallback::ActionStringCallback(): pFunctor is NULL.");
		}
	}

	template<class RT, class T>
	ActionStringCallback<RT, T>::ActionStringCallback() : functionPtr(NULL), luaFunction(NULL), mFunctor(NULL)
	{
	}

	template<class RT, class T>
	ActionStringCallback<RT, T>::~ActionStringCallback()
	{
	}

	template<class RT, class T>
	RT ActionStringCallback<RT, T>::executeCallback(T *parameter)
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		// Normal function callback
		if (functionPtr != NULL)
		{
			// Execute the callback
			return functionPtr(parameter);
		}
		else if (luaFunction.get() != NULL)
		{
			// Create a shared autoptr
			Poco::AutoPtr<T> aPtr(parameter, true);

			// Set the parameter for the lua function
			luaFunction->setParameter1(aPtr);

			// Schedule the lua function for execution
			ScriptManager::getSingleton().executeFunction(luaFunction);

			// We currently do not support return values from lua functions
			// We return 1 to indicate that the function was executed and 0 if no execution occured
			return static_cast<RT>(1);
		}
		else if (mFunctor.get() != NULL)
		{
			Value v;

			// Create a shared autoptr
			//Poco::AutoPtr<T> aPtr(parameter, true);

			// Set the parameter for the function
			//v.set(aPtr.get());
			v.set(reinterpret_cast<void*>(parameter));
			mFunctor->setParameter(0, v);

			// Execute the function
			(*mFunctor)();

			// We currently do not support return values from functors
			// We return 1 to indicate that the function was executed and 0 if no execution occured
			return static_cast<RT>(1);
		}

		return static_cast<RT>(0);
	}

} // Myoushu

#endif

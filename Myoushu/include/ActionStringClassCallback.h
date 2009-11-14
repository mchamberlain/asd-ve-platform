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
 * @file ActionStringClassCallback.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef ACTION_STRING_CLASS_CALLBACK_H
#define ACTION_STRING_CLASS_CALLBACK_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "ActionStringCallbackBase.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class wraps a class method callback for a specified actionString. The actionString is bound to
	 * an ActionStringCallback instance which is used to determine which function to
	 * call, if any.
	 *
	 * The function signature for event callbacks is:
	 * {@code RT C::functionName(T*)}
	 */
	template<class RT, class C, class T>
	class ActionStringClassCallback : public ActionStringCallbackBase<RT, T>
	{
		public:
			/** A pointer to a class method that returns void and takes a InputMessage pointer as a parameter. */
			typedef RT (C::*ActionStringClassCallbackFunction)(T*);

			/**
			 * Constructor for a class method based callback.
			 * @param actionString The input action string
			 * @param classPtr Pointer to the class instance to use.
			 * @param functionPtr Pointer to the a global function to use as callback
			 * @throws Exception::E_NULL_POINTER if classPtr or functionPtr is NULL.
			 */
			ActionStringClassCallback(const std::string& actionString, C* classPtr, ActionStringClassCallbackFunction functionPtr) throw (Exception);

			/** Destructor. */
			~ActionStringClassCallback();

			/**
			 * Getter for the pointer to a global callback function.
			 * @return a function pointer.
			 */
			inline ActionStringClassCallbackFunction getFunctionPtr();

			/**
			 * Execute the callback function.
			 * @param parameter The parameter for the callback function call.
			 */
			inline RT executeCallback(T *parameter);

		private:
			/** Pointer to the class instance to use */
			C* classPtr;
			/** Pointer to a global function to use as a callback */
			ActionStringClassCallbackFunction functionPtr;

			/** Nullary Constructor */
			ActionStringClassCallback();
	};

	// non-inlines
	template<class RT, class C, class T>
	ActionStringClassCallback<RT, C, T>::ActionStringClassCallback(const std::string& actionString, C* classPtr, ActionStringClassCallbackFunction functionPtr) throw (Exception) : ActionStringCallbackBase<RT, T>(actionString)
	{
		// Check that neither classPtr nor functionPtr is NULL
		if ((classPtr == NULL) || (functionPtr == NULL))
		{
			// throw an exception if one of them is NULL
			throw Exception(Exception::E_NULL_POINTER, "ActionStringClassCallback::ActionStringClassCallback(): classPtr or functionPtr is NULL!");
		}

		this->classPtr = classPtr;
		this->functionPtr = functionPtr;
	}

	template<class RT, class C, class T>
	ActionStringClassCallback<RT, C, T>::ActionStringClassCallback()
	{
	}

	template<class RT, class C, class T>
	ActionStringClassCallback<RT, C, T>::~ActionStringClassCallback()
	{
	}

	// inlines

	template<class RT, class C, class T>
	inline typename ActionStringClassCallback<RT, C, T>::ActionStringClassCallbackFunction ActionStringClassCallback<RT, C, T>::getFunctionPtr()
	{
		Poco::ScopedRWLock locl(this->rwLock, false);

		return functionPtr;
	}

	template<class RT, class C, class T>
	inline RT ActionStringClassCallback<RT, C, T>::executeCallback(T *parameter)
	{
		Poco::ScopedRWLock lock(this->rwLock, false);

		return (classPtr->*functionPtr)(parameter);
	}
} // Myoushu

#endif

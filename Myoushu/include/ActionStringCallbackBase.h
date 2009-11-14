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
 * @file ActionStringCallbackBase.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef ACTION_STRING_CALLBACK_BASE_H
#define ACTION_STRING_CALLBACK_BASE_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"

namespace Myoushu
{
	/**
	 * This class serves as the base class for classes that wrap a callback for a specified actionString.
	 * The actionString is bound to
	 * an ActionStringCallback instance which is used to determine which function to
	 * call, if any.
	 *
	 * The function signature for event callbacks is:
	 * {@code RT functionName(T*)
	 * It can be a global function, a Lua function or any function wrapped in a functor that extends from FunctorBase.
	 */
	template<class RT, class T>
	class ActionStringCallbackBase : public Poco::RefCountedObject
	{
		public:
			/**
			 * Constructor.
			 * @param actionString The inputActoin stirng.
			 */
			ActionStringCallbackBase(const std::string& actionString);

			/** Destructor */
			~ActionStringCallbackBase();

			/**
			 * Getter for the actionString string.
			 * @return The actionString string.
			 */
			std::string getActionString() const;

			/**
			 * Execute the callback function.
			 * @param parameter The parameter for the callback function call.
			 * @return The valued returned by the callback function. In the case of lua functions zero will be returned.
			 */
			virtual RT executeCallback(T *parameter) = 0;

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The input action */
			std::string actionString;

			/** Nullary Constructor */
			ActionStringCallbackBase();
	};

	// non-inlines
	template<class RT, class T>
	ActionStringCallbackBase<RT, T>::ActionStringCallbackBase(const std::string& actionString) : actionString(actionString)
	{
	}

	template<class RT, class T>
	ActionStringCallbackBase<RT, T>::ActionStringCallbackBase()
	{
	}

	template<class RT, class T>
	ActionStringCallbackBase<RT, T>::~ActionStringCallbackBase()
	{
	}

	// inlines
	template<class RT, class T>
	inline std::string ActionStringCallbackBase<RT, T>::getActionString() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return actionString;
	}

}

#endif

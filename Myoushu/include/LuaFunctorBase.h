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
 * @file LuaFunctorBase.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef LUA_FUNCTOR_BASE_H
#define LUA_FUNCTOR_BASE_H

#include "lua.hpp"
#include "Poco/RWLock.h"

#include "FunctorBase.h"

namespace Myoushu
{
	/**
	 * An abstract class that serves as a base class for LuaFunctors.
	 */
	class MYOUSHU_API LuaFunctorBase : public FunctorBase, public NamedObject<LuaFunctorBase>
	{
		public:

			/** 
			 * Constructor.
			 * @param functionName The Lua function name that is wrapped by this functor.
			 * @param queue Defaults to true. If true when operator()() is called a queued message is sent for
			 *				function execution, and the function is executed on the next exection of the ScriptTask.
			 *				If false the wrapped function in the functor is executed immediately.
			 *				Queued executed tends to be safer and is the preferred method, but in some instances the 
			 *				order of execution of native C\C++ and Lua functions becomes important so synchronous execution
			 *				is allowed.
			 */
			LuaFunctorBase(const std::string& functionName, bool queue = true);

			/** Destructor. */
			virtual ~LuaFunctorBase();

			CLASS_NAME_FUNCTIONS(LuaFunctorBase);

			/** Gets the Lua function name that is wrapped by this Functor. */
			std::string getFunctionName() const;

			/** Sets the mQueue flag. */
			void setQueue(bool queue);

			/** Gets the mQueue flag. */
			bool getQueue() const;

			/**
			 * Execute the Lua function wrapped by this functor.
			 * @param luaState The lua state to use to execute the function.
			 */
			virtual void operator()(lua_State *luaState) throw(Exception) = 0;

			/**
			 * Execute the function wrapped by this functor. The Lua functor requires the lua_State to
			 * be specified when a functor is executed. This fetches the default lua_State and calls the other
			 * version of operator()();
			 */
			virtual void operator()() throw (Exception);

		protected:
			/** Read/write mutex. */
			mutable Poco::RWLock mRWLock;
			/** The function name in Lua */
			std::string mFunctionName;
			/**
			 * If true when operator()() is called a queued message is sent for
			 * function execution, and the function is executed on the next exection of the ScriptTask.
			 * If false the wrapped function in the functor is executed immediately.
			 * Queued executed tends to be safer and is the preferred method, but in some instances the 
			 * order of execution of native C\C++ and Lua functions becomes important so synchronous execution
			 * is allowed.
			 */
			bool mQueue;

		private:
			/** Hide nullary constructor. */
			LuaFunctorBase();

	};

	// inlines
	inline LuaFunctorBase::LuaFunctorBase()
	{
	}

	inline std::string LuaFunctorBase::getFunctionName() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mFunctionName;
	}

	inline void LuaFunctorBase::setQueue(bool queue)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mQueue = queue;
	}

	inline bool LuaFunctorBase::getQueue() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mQueue;
	}

} // Myoushu

#endif

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
 * @file LuaParser.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef LUA_PARSER_H
#define LUA_PARSER_H

#include "lua.hpp"

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class wraps the lua_State and defines some methods to execute scripts and load some LUA standard
	 * libs.
	 */
	class MYOUSHU_API LuaParser
	{
		public:
			/** Constructor */
			LuaParser();

			/** Destructor */
			virtual ~LuaParser();

			/**
			 * Gets the lua_State pointer. When this pointer is used, the user should also use the getLuaStateLock()
			 * function to get a read write mutex for the state and use it to ensure thread safety.
			 * @return The lua_State pointer.
			 */
			inline lua_State* getLuaState()
			{
				return luaState;
			}

			/**
			 * Gets the lua_State const pointer. When this pointer is used, the user should also use the getLuaStateLock()
			 * function to get a read write mutex for the state and use it to ensure thread safety.
			 * @return The lua_State const pointer.
			 */
			inline const lua_State* getLuaState() const
			{
				return luaState;
			}

			/**
			 * Acquires a read or write lock on the lua_State.
			 * @param write Indicates if a read or write lock should be acquired.
			 */
			void getLuaStateLock(bool write = false) const;

			/**
			 * Releases the a previously acquired read or write lock on the lua_State.
			 */
			void releaseLuaStateLock() const;

			/**
			 * Execute a LUA script.
			 * @param script The script to execute.
			 * @throw Exception::E_LUA_ERROR if an error occurred during script execution.
			 */
			void execute(const Ogre::String& script) throw (Exception);


		protected:
			/** Read write mutex for thread safety*/
			mutable Poco::RWLock rwLock;
			/** Read write mutex for the LuaState */
			mutable Poco::RWLock rwLockLuaState;
			/** The LuaState */
			lua_State *luaState;
	};
} // Myoushu

#endif

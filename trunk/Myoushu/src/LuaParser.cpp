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
 * @file LuaParser.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <sstream>

#include "lua.hpp"

#include "LuaParser.h"
#include "EngineLog.h"

namespace Myoushu
{
	LuaParser::LuaParser()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing the LUA state");

		// Initialize LUA
		luaState = lua_open();

		// Load some standard LUA libraries
		luaL_openlibs(luaState);
	}

	LuaParser::~LuaParser()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (luaState)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying the LUA state");

			lua_close(luaState);
			luaState = NULL;
		}
	}

	void LuaParser::getLuaStateLock(bool write) const
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (!write)
		{
			rwLockLuaState.readLock();
		}
		else
		{
			rwLockLuaState.writeLock();
		}
	}

	void LuaParser::releaseLuaStateLock() const
	{
		Poco::ScopedRWLock lock(rwLock, true);

		rwLockLuaState.unlock();
	}

	void LuaParser::execute(const Ogre::String& script) throw (Exception)
	{
		std::ostringstream str;
		int result;

		Poco::ScopedRWLock(rwLock, false);

		try
		{
			rwLockLuaState.writeLock();
			result = luaL_dostring(luaState, script.c_str());
		}
		catch (std::exception& e)
		{
			rwLockLuaState.unlock();
			throw Exception(Exception::E_LUA_ERROR, e.what());
		}

		rwLockLuaState.unlock();

		if (result != 0)
		{
			str << "LuaParser::execute(): error while executing lua script: " << lua_tostring(luaState, -1);

			lua_pop(luaState, 1);

			throw Exception(Exception::E_LUA_ERROR, str.str());
		}
	}

} // Myoushu

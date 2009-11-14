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
 * @file Console.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "Console.h"

//template<>
//Myoushu::Console *Ogre::Singleton<Myoushu::Console>::ms_Singleton = NULL;

namespace Myoushu
{
	int luaPrint(lua_State *L)
	{
		OutputStream *out;
		int n;
		int i;

		// Get the output stream
		out = Console::getSingletonPtr();
		// Don't print if out is NULL.
		if (out == NULL)
		{
			return luaL_error(L, LUA_QL("print") " output stream is NULL. ");
		}

		// number of arguments
		n = lua_gettop(L);
		lua_getglobal(L, "tostring");

		for (i = 1; i <= n; i ++)
		{
			const char *s;
			// function to be called
			lua_pushvalue(L, -1);
			// value to print
			lua_pushvalue(L, i);
			lua_call(L, 1, 1);
			// get result
			s = lua_tostring(L, -1);
			if (s == NULL)
			{
				return luaL_error(L, LUA_QL("tostring") " must return a string to "
														 LUA_QL("print"));
			}
			if (i > 1)
			{
				(*out) << "\t";
			}
			(*out) << s;
			// pop result
			lua_pop(L, 1);
		}
		(*out) << "\n";

		return 0;
	}

	//*** CONSOLE CLASS ***//

	Console::Console(bool visible) : OutputStream(messageStream), visible(visible)
	{
	}

	Console::~Console()
	{
	}

	void Console::setVisible(bool visible)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->visible = visible;
	}

	void Console::toggleVisible()
	{
		setVisible(!visible);
	}

	void Console::redirectLuaOutputToConsole(LuaParser &luaParser)
	{
		luaParser.getLuaStateLock(true);

		lua_pushcfunction(luaParser.getLuaState(), luaPrint);
		lua_setglobal(luaParser.getLuaState(), "print");

		luaParser.releaseLuaStateLock();
	}

} // Myoushu



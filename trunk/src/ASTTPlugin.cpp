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
along with The ASD Assist VE Platform.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file ASTTPlugin.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "ScriptManager.h"
#include "EngineLog.h"

#include "ASTTPlugin.h"
#include "ASTTLua.h"

namespace Educational
{
	void ASTTPlugin::install()
	{
	}

	void ASTTPlugin::initialise()
	{
		LOG(Myoushu::EngineLog::LM_INFO_ENGINE, "[ASTTPlugin]: Creating EducationalQuestionsManager Singleton...");
		pEduQuestionsManager = new EducationalQuestionsManager();

		LOG(Myoushu::EngineLog::LM_INFO_ENGINE, "[ASTTPlugin]: Setting up wrappers for Lua...");

		// Initialise the Lua state with the Lua wrappers for this library
		Myoushu::LuaParser& luaParser = Myoushu::ScriptManager::getSingleton().getDefaultLuaParser();
		lua_State *pLuaState = luaParser.getLuaState();

		luaParser.getLuaStateLock(true);

		luaopen_ASTT(pLuaState);

		luaParser.releaseLuaStateLock();
	}

	void ASTTPlugin::shutdown()
	{
		if (pEduQuestionsManager)
		{
			LOG(Myoushu::EngineLog::LM_INFO_ENGINE, "[ASTTPlugin]: Destroying EducationalQuestionsManager Singleton...");
			delete pEduQuestionsManager;
			pEduQuestionsManager = NULL;
		}
	}

	void ASTTPlugin::uninstall()
	{
	}

} // namespace Educational

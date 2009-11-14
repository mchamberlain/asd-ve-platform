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
 * @file ScriptManager.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>

// Stupid dumb-ass windows headers mess up std::min and std::max if NOMINMAX is not defined
#define NOMINMAX
#include "TextFileManager.h"

#include "ScriptManager.h"

//template<>
//Myoushu::ScriptManager* Ogre::Singleton<Myoushu::ScriptManager>::ms_Singleton = NULL;

namespace Myoushu
{
	ScriptManager::ScriptManager()
	{
	}

	ScriptManager::~ScriptManager()
	{
	}

	void ScriptManager::executeScriptFile(const Ogre::String& scriptFile, const Ogre::String& resourceGroup, bool queue) throw (Exception)
	{
		TextFileManager *txtFileMgr;
		TextFilePtr textFile;

//		Poco::ScopedRWLock lock(rwLock, false);

		txtFileMgr = TextFileManager::getSingletonPtr();

		// Ensure that the TextFileManager exists.
		if (txtFileMgr == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ScriptManager::executeScriptFile(): The TextFileManager does not exist.");
		}

		try
		{
			// Remove any existing instance of this in the resource manager.
			txtFileMgr->remove(scriptFile);

			textFile = txtFileMgr->load(scriptFile, resourceGroup);

		}
		catch (Ogre::Exception& e)
		{
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}

		executeScript(textFile->getString(), queue);
	}

	void ScriptManager::executeScript(const Ogre::String& script, bool queue)
	{
		// Send a Message that the given script must be executed
		if (queue)
		{
			// Queue it
			NotificationManager::getSingleton().queueNotification(new ScriptMessage(ScriptMessage::SM_EXECUTE, script));
		}
		else
		{
			// Send it now
			NotificationManager::getSingleton().sendNotification(new ScriptMessage(ScriptMessage::SM_EXECUTE, script));
		}
	}

	void ScriptManager::executeFunction(LuaFunctorBase *luaFunctor, bool queue) throw (Exception)
	{
		ScriptMessage *scriptMessage;

		// Cheack that luaFunctor is not NULL
		if (luaFunctor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ScriptManager::executeFunction(): luaFunctor is NULL.");
		}

		// Create and queue the script message
		//scriptMessage = new ScriptMessage(luaFunctor);
		scriptMessage = ObjectPool<ScriptMessage>::getSingleton().get(true);
		scriptMessage->setMessageType(ScriptMessage::SM_EXECUTE_LUA_FUNCTOR);
		scriptMessage->setLuaFunctor(static_cast<LuaFunctorBase*>(luaFunctor->clone()));

		if (queue)
		{
			// Queue the message
			NotificationManager::getSingleton().queueNotification(scriptMessage);
		}
		else
		{
			// Send it now
			NotificationManager::getSingleton().sendNotification(scriptMessage);
		}
	}

	void ScriptManager::executeFunction(const std::string& functionName, bool queue)
	{
		LuaFunctor<void, 0> *luaFunctor;
		ScriptMessage *scriptMessage;

		// Create the Lua Functor
		luaFunctor = new LuaFunctor<void, 0>(functionName);

		// Create the ScriptMessage
		//scriptMessage = new ScriptMessage(luaFunctor);
		scriptMessage = ObjectPool<ScriptMessage>::getSingleton().get(true);
		scriptMessage->setMessageType(ScriptMessage::SM_EXECUTE_LUA_FUNCTOR);
		scriptMessage->setLuaFunctor(luaFunctor);

		if (queue)
		{
			// Queue the message
			NotificationManager::getSingleton().queueNotification(scriptMessage);
		}
		else
		{
			// Send it now
			NotificationManager::getSingleton().sendNotification(scriptMessage);
		}
	}

} // Myoushu

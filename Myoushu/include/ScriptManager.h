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
 * @file ScriptManager.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include "Poco/RWLock.h"
#include "Ogre.h"
#include "MyGUI.h"

#include "Platform.h"
#include "Singleton.h"
#include "LuaParser.h"
#include "Exception.h"
#include "Constants.h"
#include "ScriptMessage.h"
#include "NotificationManager.h"
#include "LuaFunctor.h"
#include "ObjectPool.h"

namespace Myoushu
{
	/**
	 * This class acts as a manager for LUA scripts. It sends messages to the ScriptTask for various actions, for instance
	 * script executions.
	 */
	class MYOUSHU_API ScriptManager : public Ogre::Singleton<ScriptManager>
	{
		public:
			/** Nullary Constructor */
			ScriptManager();

			/** Destructor */
			~ScriptManager();

			/**
			 * Get the default LuaParser.
			 * @return A reference to the default LuaParser.
			 */
			LuaParser& getDefaultLuaParser();

			/**
			 * Execute a LUA script from a file. This method sends a message to the ScriptTask to
			 * execute the script as soon as possible.
			 * @param scriptFile The LUA script file to execute.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 * @throw Exception::E_NULL_POINTER if the TextFileManager does not exist.
			 * @throw Exception::E_OGRE_EXCEPTION if an error occurred while loading the file.
			 */
			void executeScriptFile(const Ogre::String& scriptFile, const Ogre::String& resourceGroup = Constants::RG_SCRIPTS, bool queue = true) throw (Exception);

			/**
			 * Execute a LUA script. This method sends a message to the ScriptTask to
			 * execute the script as soon as possible.
			 * @param script The LUA script to execute.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 */
			void executeScript(const Ogre::String& script, bool queue = true);

			/**
			 * Execute a Lua function. This method sends a message to the ScriptTask to
			 * execute the function as soon as possible.
			 * @param luaFunctor A LuaFunctorBase instance that wraps the lua function to be executed.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 * @throws Exception::E_NULL_POINTER if luaFunctor is NULL.
			 */
			void executeFunction(LuaFunctorBase *luaFunctor, bool queue = true) throw (Exception);

			/**
			 * Execute a Lua function. This method sends a message to the ScriptTask to
			 * execute the function as soon as possible.
			 * @param functionName The name of the Lua function to execute.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 */
			void executeFunction(const std::string& functionName, bool queue = true);

			/**
			 * Execute a Lua function. This method sends a message to the ScriptTask to
			 * execute the function as soon as possible.
			 * @param functionName The name of the Lua function to execute.
			 * @param param1Type A string containing the type of the fisrt parameter.
			 * @param param1 The first parameter to pass to the function.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 */
			template <typename P1>
			void executeFunction(const std::string& functionName, const std::string& param1Type, P1 param1, bool queue = true)
			{
				LuaFunctor<void, 1, P1> *luaFunctor;
				ScriptMessage *scriptMessage;

				// Create the Lua Functor
				luaFunctor = new LuaFunctor<void, 1, P1>(functionName, param1Type);
				luaFunctor->setParameter1(param1);

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
					// Send message now
					NotificationManager::getSingleton().sendNotification(scriptMessage);
				}
			}

			/**
			 * Execute a Lua function. This method sends a message to the ScriptTask to
			 * execute the function as soon as possible.
			 * @param functionName The name of the Lua function to execute.
			 * @param param1Type A string containing the type of the fisrt parameter.
			 * @param param1 The first parameter to pass to the function.
			 * @param param2Type A string containing the type of the second parameter.
			 * @param param2 The second parameter to pass to the function.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 */
			template <typename P1, typename P2>
			void executeFunction(const std::string& functionName, const std::string& param1Type, P1 param1, const std::string& param2Type, P2 param2, bool queue = true)
			{
				LuaFunctor<void, 2, P1, P2> *luaFunctor;
				ScriptMessage *scriptMessage;

				// Create the Lua Functor
				luaFunctor = new LuaFunctor<void, 2, P1, P2>(functionName, param1Type, param2Type);
				luaFunctor->setParameter1(param1);
				luaFunctor->setParameter2(param2);

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
					// Send message now
					NotificationManager::getSingleton().sendNotification(scriptMessage);
				}
			}

			/**
			 * Execute a Lua function. This method sends a message to the ScriptTask to
			 * execute the function as soon as possible.
			 * @param functionName The name of the Lua function to execute.
			 * @param param1Type A string containing the type of the fisrt parameter.
			 * @param param1 The first parameter to pass to the function.
			 * @param param2Type A string containing the type of the second parameter.
			 * @param param2 The second parameter to pass to the function.
			 * @param param3Type A string containing the type of the third parameter.
			 * @param param3 The third parameter to pass to the function.
			 * @param queue Defaults to true. If true the script is only executed when the ScriptTask is next executed. If false
			 *				the script is executed synchronously, immediately. 
			 */
			template <typename P1, typename P2, typename P3>
			void executeFunction(const std::string& functionName, const std::string& param1Type, P1 param1, const std::string& param2Type, P2 param2, const std::string& param3Type, P3 param3, bool queue = true)
			{
				LuaFunctor<void, 3, P1, P2, P3> *luaFunctor;
				ScriptMessage *scriptMessage;

				// Create the Lua Functor
				luaFunctor = new LuaFunctor<void, 3, P1, P2, P3>(functionName, param1Type, param2Type, param3Type);
				luaFunctor->setParameter1(param1);
				luaFunctor->setParameter2(param2);
				luaFunctor->setParameter3(param3);

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
					// Send message now
					NotificationManager::getSingleton().sendNotification(scriptMessage);
				}
			}

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** The default LuaParser */
			LuaParser luaParser;
	};

	// inlines
	inline LuaParser& ScriptManager::getDefaultLuaParser()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return luaParser;
	}

} // Myoushu

#endif

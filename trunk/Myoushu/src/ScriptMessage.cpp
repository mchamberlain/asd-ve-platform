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
 * @file ScriptMessage.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "ScriptMessage.h"
#include "LuaFunctor.h"
#include "ObjectPool.h"

namespace Myoushu
{
	CLASS_NAME(ScriptMessage, "Myoushu::ScriptMessage");

	ScriptMessage::ScriptMessage(ScriptMessageType messageType, const Ogre::String& script) : messageType(messageType), script(script), luaFunctor(NULL)
	{
	}

	ScriptMessage::ScriptMessage(LuaFunctorBase* luaFunctor) : messageType(SM_EXECUTE_LUA_FUNCTOR), script(""), luaFunctor(luaFunctor)
	{
	}

	ScriptMessage::ScriptMessage() : messageType(SM_UNKNOWN), script(""), luaFunctor(NULL)
	{
	}

	ScriptMessage::~ScriptMessage()
	{
		if (luaFunctor)
		{
			delete luaFunctor;
			luaFunctor = NULL;
		}
	}

	void ScriptMessage::clear()
	{
		Message::clear();

		Poco::ScopedRWLock lock(rwLock, true);

		// Set all member variables to their zero values
		messageType = SM_UNKNOWN;
		script = "";

		if (luaFunctor)
		{
			delete luaFunctor;
			luaFunctor = NULL;
		}
	}

	void ScriptMessage::clone(ScriptMessage *dest) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		// Check that dest is not NULL
		if (dest == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "ScriptMessage::clone(): dest is NULL.");
		}

		*dest = *this;
	}

	ScriptMessage* ScriptMessage::clone() const
	{
		ScriptMessage *scriptMessage;

		Poco::ScopedRWLock lock(rwLock, false);

		if (messageType != SM_EXECUTE_LUA_FUNCTOR)
		{
			//return new ScriptMessage(messageType, script);
			scriptMessage = ObjectPool<ScriptMessage>::getSingleton().get(true);
			scriptMessage->setMessageType(messageType);
			scriptMessage->setScript(script);
		}
		else
		{
			//return new ScriptMessage((LuaFunctorBase*) luaFunctor->clone());
			scriptMessage = ObjectPool<ScriptMessage>::getSingleton().get(true);
			scriptMessage->setMessageType(ScriptMessage::SM_EXECUTE_LUA_FUNCTOR);
			scriptMessage->setLuaFunctor(static_cast<LuaFunctorBase*>(luaFunctor->clone()));
		}

		return scriptMessage;
	}

	ScriptMessage& ScriptMessage::operator=(const ScriptMessage& message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		Message::operator=(message);

		messageType = message.getMessageType();
		script = message.getScript();
		luaFunctor = static_cast<LuaFunctorBase*>(message.getLuaFunctor()->clone());

		return *this;
	}

} // Myoushu

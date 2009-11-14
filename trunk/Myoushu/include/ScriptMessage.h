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
 * @file ScriptMessage.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef SCRIPT_MESSAGE_H
#define SCRIPT_MESSAGE_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "LuaFunctorBase.h"
#include "Cloneable.h"

namespace Myoushu
{
	/**
	 * This class wraps messages sent to the ScriptTask. This can be scripts that must be executed for instance,
	 * or functions that have been registered that must be executed.
	 */
	class MYOUSHU_API ScriptMessage : public NamedObject<ScriptMessage>, public Message
	{
		public:
			/** This enumeration represents the different types of ScriptMessages that can be sent/received */
			enum ScriptMessageType
			{
				/** Execute the specified script */
				SM_EXECUTE,
				/** Execute a Lua Function wrapped in a LuaFunctor. */
				SM_EXECUTE_LUA_FUNCTOR,
				/** Suspend script execution */
				SM_SLEEP,
				/** Unknown message type */
				SM_UNKNOWN
			};

			/** Nullary Constructor */
			ScriptMessage();

			/**
			 * Constructor.
			 * @param messageType The ScriptMessageType of this message.
			 * @param script The script (mainly used for SM_EXECUTE).
			 */
			ScriptMessage(ScriptMessageType messageType, const Ogre::String& script);

			/**
			 * Constructor. Creates a SM_EXECUTE_LUA_FUNCTOR ScriptMessage.
			 * @param functor A pointer to the Lua Functor to execute. The ScriptMessage takes ownership of the functor.
			 */
			ScriptMessage(LuaFunctorBase* functor);

			/** Destructor */
			~ScriptMessage();

			CLASS_NAME_FUNCTIONS(ScriptMessage);

			/**
			 * Get the message type of this ScriptMessage.
			 * @return The ScriptMessageType of this message.
			 */
			ScriptMessageType getMessageType() const;

			/**
			 * Sets the message type of this ScriptMessage.
			 * @param type The new ScriptMessageType for this message.
			 */
			void setMessageType(ScriptMessageType type);

			/**
			 * Get the script associated with this message.
			 * @return The script associated with this message.
			 */
			const Ogre::String& getScript() const;

			/**
			 * Sets the script wrapped in this message. (the script to execute generally)
			 * @param script An Ogre::String containing a lua script.
			 */
			void setScript(const Ogre::String& script);

			/**
			 * Const getter for the LuaFunctor instance encapsulated in this message.
			 * @return A const instance of LuaFunctorBase.
			 */
			const LuaFunctorBase* getLuaFunctor() const;

			/**
			 * Getter for the LuaFunctor instance encapsulated in this message.
			 * @return An instance of LuaFunctorBase.
			 */
			LuaFunctorBase* getLuaFunctor();

			/**
			 * Sets the luaFunctor to execute. Used with message type SM_EXECUTE_LUA_FUNCTOR.
			 * @param luaFunctor A LuaFunctorBase instance wrapping a lua function that should be scheduled for execution.
			 *					 The ScriptMessage takes ownership of the pointer.
			 */
			void setLuaFunctor(LuaFunctorBase *luaFunctor);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(ScriptMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			ScriptMessage* clone() const;

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 * @return A reference to this instance
			 */
			ScriptMessage& operator=(const ScriptMessage& message);

		protected:
			/** Read write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** The ScriptMessageType of this message */
			ScriptMessageType messageType;
			/** The script */
			Ogre::String script;
			/** A LuaFunctor instance */
			LuaFunctorBase *luaFunctor;

	};

	// inlines
	inline ScriptMessage::ScriptMessageType ScriptMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return messageType;
	}

	inline void ScriptMessage::setMessageType(ScriptMessageType type)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		messageType = type;
	}

	inline const Ogre::String& ScriptMessage::getScript() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return script;
	}

	inline void ScriptMessage::setScript(const Ogre::String& script)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->script = script;
	}

	inline const LuaFunctorBase* ScriptMessage::getLuaFunctor() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return luaFunctor;
	}

	inline LuaFunctorBase* ScriptMessage::getLuaFunctor()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return luaFunctor;
	}

	inline void ScriptMessage::setLuaFunctor(LuaFunctorBase *luaFunctor)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (this->luaFunctor != NULL)
		{
			delete this->luaFunctor;
		}

		this->luaFunctor = luaFunctor;
	}

} // Myoushu

#endif

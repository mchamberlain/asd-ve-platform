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
 * @file Console.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <sstream>

#include "Poco/RWLock.h"
#include "Ogre.h"
#include "lua.hpp"

#include "Platform.h"
#include "Singleton.h"
#include "OutputStream.h"
#include "LuaParser.h"

namespace Myoushu
{
	/**
	 * A replacement function of the normal Lua print function. If this function is bound
	 * to the Lua print function, all printing will be outputted to the console window
	 * and not standard out.
	 * @param L The lua state.
	 */
	int MYOUSHU_API luaPrint(lua_State *L);

	/**
	 * This class is used to manage the developers console used in the engine.
	 */
	class MYOUSHU_API Console : public OutputStream, public Ogre::Singleton<Console>
	{
		public:
			/**
			 * Constructor
			 * @param visible The initial value for the visible flag
			 */
			Console(bool visible = false);

			/** Destructor */
			virtual ~Console();

			/**
			 * Gets the current string in the messageStream.
			 * @return The current string in the messageStream.
			 */
			inline std::string getMessageStreamString() const
			{
				Poco::ScopedRWLock lock(rwLock, false);

				return messageStream.str();
			}

			/** Clears the messageStream */
			inline void clearMessageStream()
			{
				Poco::ScopedRWLock lock(rwLock, true);

				messageStream.str("");
			}

			/**
			 * This method redirects the lua output from the lua state
			 * encapsulated in the specified LuaParser instance to this Console.
			 * @param luaParser The LuaParser's lua_State output to redirect.
			 */
			void redirectLuaOutputToConsole(LuaParser &luaParser);

			/**
			 * In addition to setting the visible flag, this function should make the Console
			 * visible or not to the user based on the value of visible.
			 * @param visible The new value for the visible flag.
			 */
			virtual void setVisible(bool visible);

			/**
			 * Toggle Console visibility.
			 */
			virtual void toggleVisible();

			/**
			 * Update the GUI. This will be called by the GUITask periodically. Typically this
			 * can be used to flush an output stream to the console window.
			 */
			virtual void update() = 0;

		protected:
			/** Read/write lock for thread safety */
			mutable Poco::RWLock lock;
			/** stringstream that contains the next message that should be displayed in the console */
			std::ostringstream messageStream;
			/** Visible flag */
			bool visible;
	};
} // Myoushu

#endif

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
 * @file InputActionCallback.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef INPUT_ACTION_CALLBACK_H
#define INPUT_ACTION_CALLBACK_H

#include "ActionStringCallback.h"
#include "InputMessage.h"

namespace Myoushu
{
	/**
	 * This class wraps a callback for a specified inputString. If the input system receives an input event
	 * that is bound to the actionString, an InputActionCallback instance is used to determine which function to
	 * call, if any. In other words if space bar is bound to jump, this class is used to bind the function that
	 * makes the player jump to the jump input action. It is also possible to not use InputActionCallbacks and
	 * just register a function that receives InputMessage instances if you want more control over managing
	 * input events.
	 *
	 * The function signature for event callbacks is:
	 * {@code void functionName(InputMessage *)}
	 * It can be a global function, Lua function or a function wrapped in an implementation of FunctorBase.
	 */
	typedef ActionStringCallback<void, InputMessage> InputActionCallback;

	/** A pointer to a global function return void and taking a InputMessage pointer as a parameter. */
	typedef ActionStringCallback<void, InputMessage>::ActionStringCallbackGlobalFunction InputActionCallbackGlobalFunction;

	/** The LuaFunctor type used for Lua callbacks. */
	typedef ActionStringCallback<void, InputMessage>::ActionStringCallbackLuaFunctor InputActionCallbackLuaFunctor;
}

#endif

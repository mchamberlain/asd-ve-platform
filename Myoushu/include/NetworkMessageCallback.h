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
 * @file NetworkMessageCallback.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef NETWORK_MESSAGE_CALLBACK_H
#define NETWORK_MESSAGE_CALLBACK_H

#include "ActionStringCallback.h" 
#include "ActionStringClassCallback.h"
#include "NetworkMessage.h"

namespace Myoushu
{
	/**
	 * The base class for callbacks to control network events. Callbacks can be associated with the different types of
	 * messages that are received over the network (via one of the NetworkListenBehaviour implementations). These callbacks
	 * can then be used to control responses to these messages.
	 * The function signature for event callbacks is:
	 * {@code bool functionName(NetworkMessage *)}
	 * It can be a global function, or Lua function. In the case of Lua functions the return type is ignored as the Lua function is called asynchronously.
	 * Lua implementations must use the NetworkManager to react upon received messages.
	 */
	typedef ActionStringCallback<bool, NetworkMessage> NetworkMessageCallback;

	/** A pointer to a global function return bool and taking a NetworkMessage pointer as a parameter. */
	typedef ActionStringCallback<bool, NetworkMessage>::ActionStringCallbackGlobalFunction NetworkMessageCallbackGlobalFunction;

	/** The LuaFunctor type used for Lua callbacks. */
	typedef ActionStringCallback<void, NetworkMessage>::ActionStringCallbackLuaFunctor NetworkMessageCallbackLuaFunctor;
}

#endif

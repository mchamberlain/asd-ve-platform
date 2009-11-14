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
 * @file LUAFunctor.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef LUA_FUNCTOR_H
#define LUA_FUNCTOR_H

#include <iostream>
#include <sstream>
#include <cctype>

#include "Poco/RWLock.h"
#include "lua.hpp"
//#include "tolua++.h"
//#include "MyGUI.h"

#include "Platform.h"
#include "MyoushuLua.h"
#include "LuaFunctorBase.h"
#include "Cloneable.h"
#include "EngineLog.h"

namespace Myoushu
{
	/** Represents an unspecified type. */
	struct UnspecifiedType
	{
	};

	/**
	 * A lua function wrapper that allows functions with up to three parameters. All parameters are stored "by-value" in the functor
	 * instance. For pointer types use references instead of pointers as the functor converts everything into pointers
	 * internally.
	 * @param T The return type of the lua function that will be wrapped.
	 * @param numParams The number of parameters the function takes.
	 * @param P1Type A string containing the type of P1, e.g. "int".
	 * @param P1 The first parameter type.
	 * @param P2Type A string containing the type of P2, e.g. "int".
	 * @param P2 The second parameter type.
	 * @param P3Type A string containing the type of P3, e.g. "int".
	 * @param P3 The third parameter type.
	 */
	template <class T, unsigned int numParams = 0, class P1 = UnspecifiedType, class P2 = UnspecifiedType, class P3 = UnspecifiedType>
	class LuaFunctor : public LuaFunctorBase
	{
		public:
			/**
			 * Constructor for a Lua Function with no parameters.
			 * @param functionName The Lua function name.
			 */
			LuaFunctor(const std::string& functionName) : LuaFunctorBase(functionName)
			{
				assert(numParams <= 0 && "numParams > 0");

				parameter1Type = "UnspecifiedType";
				parameter2Type = "UnspecifiedType";
				parameter3Type = "UnspecifiedType";
			}

			/**
			 * Constructor for a Lua Function with one parameters.
			 * @param functionName The Lua function name.
			 * @param parameter1Type The type of the first parameter as a string.
			 */
			LuaFunctor(const std::string& functionName, const std::string& parameter1Type) :
			LuaFunctorBase(functionName), parameter1Type(parameter1Type)
			{
				assert(numParams <= 1 && "numParams > 1");

				trimType(this->parameter1Type);
				parameter2Type = "UnspecifiedType";
				parameter3Type = "UnspecifiedType";
			}

			/**
			 * Constructor for a Lua Function with two parameters.
			 * @param functionName The Lua function name.
			 * @param parameter1Type The type of the first parameter as a string.
			 * @param parameter2Type The type of the second parameter as a string.
			 */
			LuaFunctor(const std::string& functionName, const std::string& parameter1Type, const std::string& parameter2Type)
				: LuaFunctorBase(functionName), parameter1Type(parameter1Type), parameter2Type(parameter2Type)
			{
				assert(numParams <= 2 && "numParams > 2");

				trimType(this->parameter1Type);
				trimType(this->parameter2Type);
				parameter3Type = "UnspecifiedType";
			}

			/**
			 * Constructor for a Lua Function with three parameters.
			 * @param functionName The Lua function name.
			 * @param parameter1Type The type of the first parameter as a string.
			 * @param parameter2Type The type of the second parameter as a string.
			 * @param parameter3Type The type of the third parameter as a string.
			 */
			LuaFunctor(const std::string& functionName, const std::string& parameter1Type, const std::string& parameter2Type
				, const std::string& parameter3Type) : LuaFunctorBase(functionName), parameter1Type(parameter1Type)
				, parameter2Type(parameter2Type), parameter3Type(parameter3Type)
			{
				assert(numParams <= 3 && "numParams > 3");
				trimType(this->parameter1Type);
				trimType(this->parameter2Type);
				trimType(this->parameter3Type);
			}

			/**
			 * Sets the parameter at the specified index to be passed to the wrapped function. This function is not supported
			 * in LuaFunctor and throws an Exception::E_UNIMPLEMENTED if used.
			 */
			virtual void setParameter(unsigned int i, Value v) throw (Exception)
			{
				throw Exception(Exception::E_UNIMPLEMENTED, "LuaFunctor::setParameter(): LuaFunctor does not support this function, use setParamter[1,2,...]() instead.");
			}

			/**
			 * Set the first parameter.
			 * This function cannot be called if numParams is less than one.
			 * @param parameter1 The value to set the first parameter too.
			 */
			inline void setParameter1(P1 parameter1)
			{
				assert(numParams >= 1 && "Tried to set parameter 1 with numParams < 1");

				Poco::ScopedRWLock lock(rwLock, true);

				this->parameter1 = parameter1;
			}

			/**
			 * Set the second parameter.
			 * This function cannot be called if numParams is less than two.
			 * @param parameter2 The value to set the second parameter too.
			 */
			inline void setParameter2(P2 parameter2)
			{
				assert(numParams >= 2 && "Tried to set parameter 1 with numParams < 2");

				Poco::ScopedRWLock lock(rwLock, true);

				this->parameter2 = parameter2;
			}

			/**
			 * Set the third parameter.
			 * This function cannot be called if numParams is less than three.
			 * @param parameter3 The value to set the third parameter too.
			 */
			inline void setParameter3(P3 parameter3)
			{
				assert(numParams >= 3 && "Tried to set parameter 1 with numParams < 3");

				Poco::ScopedRWLock lock(rwLock, true);

				this->parameter3 = parameter3;
			}

			/**
			 * Clones the functor.
			 * @return A new cloned instance.
			 */
			Cloneable* clone() const
			{
				LuaFunctor<T, numParams, P1, P2, P3>* newFunctor;

				Poco::ScopedRWLock lock(rwLock, false);

				newFunctor = NULL;

				switch (numParams)
				{
					case 0:
						newFunctor = new LuaFunctor<T, numParams, P1, P2, P3>(getFunctionName());
					break;
					case 1:
						newFunctor = new LuaFunctor<T, numParams, P1, P2, P3>(getFunctionName(), parameter1Type);
						newFunctor->setParameter1(parameter1);
					break;
					case 2:
						newFunctor = new LuaFunctor<T, numParams, P1, P2, P3>(getFunctionName(), parameter1Type, parameter2Type);
						newFunctor->setParameter1(parameter1);
						newFunctor->setParameter2(parameter2);
					break;
					case 3:
						newFunctor = new LuaFunctor<T, numParams, P1, P2, P3>(getFunctionName(), parameter1Type, parameter2Type, parameter3Type);
						newFunctor->setParameter1(parameter1);
						newFunctor->setParameter2(parameter2);
						newFunctor->setParameter3(parameter3);
					break;
					default:
						assert(numParams <= 3 && "numParams > 3");
						newFunctor = NULL;
					break;
				}

				return static_cast<Cloneable*>(newFunctor);
			}

			/**
			 * Remove spaces from the end of a string.
			 * @param type The type string to remove the spaces from.
			 */
			void trimType(std::string& type)
			{
				unsigned int pos;

				for (pos = type.length() - 1; (pos >= 0) && (isspace(type[pos])); pos--)
				{
				}

				if (pos <= type.length() - 1)
				{
					type.erase(pos + 1, type.length() - 1);
				}
			}

			/**
			 * Push a user type parameter (cast user type to void*) onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string.
			 * @param parameter The parameter to push.
			 * @throws Exception::E_INVALID_PARAMETERS if the specified type does not exist in the LUA state.
			 */
			template<class P>
			void pushType(lua_State* luaState, const std::string& type, P* parameter) throw (Exception)
			{
				std::string tType;
				swig_module_info *pModule;
				swig_type_info *pTypeInfo;

				if (type == "UnspecifiedType")
				{
					return;
				}

				tType = type;

				// Get the swig_module_info for the Myoushu module
				pModule = SWIG_GetModule(luaState);

				if (tType.find_last_of("*") == tType.length() - 1)
				{
					pushType(luaState, type, reinterpret_cast<void**>(parameter));
				}
				else if (tType.find_last_of("&") == tType.length() - 1)
				{
					tType.erase(tType.length() - 1, tType.length());
					trimType(tType);
					tType += " *";

					pTypeInfo = SWIG_TypeQueryModule(pModule, pModule, tType.c_str());
					if (pTypeInfo != NULL)
					{
						SWIG_NewPointerObj(luaState, parameter, pTypeInfo, 0);
					}
					else
					{
						throw Exception(Exception::E_INVALID_PARAMETERS, "Myoushu::LuaFunctor::pushType(): specified type: " + tType + " not in LUA state.");
					}
				}
				else
				{
					tType += " *";
					pTypeInfo = SWIG_TypeQueryModule(pModule, pModule, tType.c_str());
					if (pTypeInfo != NULL)
					{
						SWIG_NewPointerObj(luaState, reinterpret_cast<void*>(parameter), pTypeInfo, 0);
					}
					else
					{
						throw Exception(Exception::E_INVALID_PARAMETERS, "Myoushu::LuaFunctor::pushType(): specified type: " + tType + " not in LUA state.");
					}
				}
			}

			inline void pushType(lua_State *luaState, const std::string& type, void** parameter) throw (Exception)
			{
				std::string tType;
				swig_module_info *pModule;
				swig_type_info *pTypeInfo;

				if (type == "UnspecifiedType")
				{
					return;
				}

				tType = type;

				// Get the swig_module_info for the Myoushu module
				pModule = SWIG_GetModule(luaState);

				if (tType.find_last_of("*") == tType.length() - 1)
				{
					//tType.erase(tType.length() - 1, tType.length());
					//trimType(tType);

					pTypeInfo = SWIG_TypeQueryModule(pModule, pModule, tType.c_str());
					if (pTypeInfo != NULL)
					{
						SWIG_NewPointerObj(luaState, *parameter, pTypeInfo, 0);
					}
					else
					{
						throw Exception(Exception::E_INVALID_PARAMETERS, "Myoushu::LuaFunctor::pushType(): specified type: " + tType + " not in LUA state.");
					}
				}
				else
				{
					throw Exception(Exception::E_INVALID_PARAMETERS, "Myoushu::LuaFunctor::pushType(): parameter is a pointer but tType, " + tType + ", is not.");
				}
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, UnspecifiedType* parameter) throw (Exception)
			{
				// Do nothing if parameter type is unspecified
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, bool* parameter) throw (Exception)
			{
				lua_pushboolean(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, char* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, unsigned char* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, short* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, unsigned short* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, int* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, unsigned int* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, long* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, unsigned long* parameter) throw (Exception)
			{
				lua_pushinteger(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, float* parameter) throw (Exception)
			{
				lua_pushnumber(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, double* parameter) throw (Exception)
			{
				lua_pushnumber(luaState, *parameter);
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, const std::string& parameter) throw (Exception)
			{
				lua_pushstring(luaState, parameter.c_str());
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, std::string& parameter) throw (Exception)
			{
				lua_pushstring(luaState, parameter.c_str());
			}

			/**
			 * Push a parameter onto the lua stack.
			 * @param luaState The Lua state.
			 * @param type Type string -- ignored in this case.
			 * @param parameter The parameter to push.
			 */
			inline void pushType(lua_State *luaState, const std::string& type, std::string* parameter) throw (Exception)
			{
				lua_pushstring(luaState, parameter->c_str());
			}

//			/**
//			 * Push a parameter onto the lua stack.
//			 * @param luaState The Lua state.
//			 * @param type Type string -- ignored in this case.
//			 * @param parameter The parameter to push.
//			 */
//
//			inline void pushType(lua_State *luaState, const std::string& type, MyGUI::Widget* parameter) throw (Exception)
//			{
//				tolua_pushusertype(luaState, (void*) parameter, "MyGUI::Widget");
//			}

			/**
			 * Execute the Lua function that is wrapped in this functor.
			 * @param luaState The Lua state to use to execute the function.
			 * @return The value the Lua function returned.
			 * @throws Exception::E_LUA_ERROR if there was an error executing the function.
			 * @throws Exception::E_INVALID_PARAMETER if one of the parameters that should be passed to the LUA function is not defined 
			 *			in the LUA state.
			 */
			T operator()(lua_State* luaState) throw (Exception)
			{
				std::ostringstream str;
				int result;
				int top;
				unsigned int numResults;

				Poco::ScopedRWLock lock(rwLock, false);

				top = lua_gettop(luaState);

				// Get and push the function onto the Lua stack
				lua_getglobal(luaState, getFunctionName().c_str());

				if (!lua_isfunction(luaState, -1))
				{
					lua_settop(luaState, top);

					throw Exception(Exception::E_LUA_ERROR, "function not found.");
				}

				// Push the parameters onto the Lua stack
				switch (numParams)
				{
					case 0:
						// Don't push any parameters
					break;
					case 1:
						pushType(luaState, parameter1Type.c_str(), &parameter1);
					break;
					case 2:
						pushType(luaState, parameter1Type.c_str(), &parameter1);
						pushType(luaState, parameter2Type.c_str(), &parameter2);
					break;
					case 3:
						pushType(luaState, parameter1Type.c_str(), &parameter1);
						pushType(luaState, parameter2Type.c_str(), &parameter2);
						pushType(luaState, parameter3Type.c_str(), &parameter3);
					break;
					default:
						assert(numParams <= 3 && "numParams > 3");
					break;
				}

				result = 0;
				numResults = 0;
				// Execute the function
				result = lua_pcall(luaState, numParams, numResults, 0);

				if (result != 0)
				{
					str << "LuaParser::execute(): error while executing lua function: " << lua_tostring(luaState, -1);

					lua_pop(luaState, 1);

					throw Exception(Exception::E_LUA_ERROR, str.str());
				}
			}

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** A string containing the type of the first parameter. */
			std::string parameter1Type;
			/** The first parameter. */
			P1 parameter1;
			/** A string containing the type of the second parameter. */
			std::string parameter2Type;
			/** The second parameter. */
			P2 parameter2;
			/** A string containing the type of the third parameter. */
			std::string parameter3Type;
			/** The third parameter. */
			P3 parameter3;

			/** Nullary Constructor */
			LuaFunctor()
			{
			}
	};

} // Myoushu

#endif

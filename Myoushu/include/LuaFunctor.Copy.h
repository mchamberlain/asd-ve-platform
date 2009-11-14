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
#include <vector>

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

	/**
	 * A lua function wrapper.
	 */
	class LuaFunctor : public LuaFunctorBase
	{
		public:
			/**
			 * Constructor for a Lua Function with no parameters.
			 * @param functionName The Lua function name.
			 */
			LuaFunctor(const std::string& functionName, bool queue = true) : LuaFunctorBase(functionName)
			{
			}

			/**
			 * Sets the parameter at the specified index to be passed to the wrapped function. This function is not supported
			 * in LuaFunctor and throws an Exception::E_UNIMPLEMENTED if used.
			 */
			virtual void setParameter(unsigned int i, Value v) throw (Exception)
			{
				Poco::ScopedRWLock lock(mRWLock, true);

				mValues[i] = v;
			}

			/**
			 * Clones the functor.
			 * @return A new cloned instance.
			 */
			Cloneable* clone() const
			{
				LuaFunctor* newFunctor;
				ValueVectorConstIterator iter;
				unsigned int i;

				Poco::ScopedRWLock lock(rwLock, false);

				newFunctor = NULL;

				newFunctor = new LuaFunctor(getFunctionName(), getQueue());

				i = 0;
				for (iter = mValues.begin(); iter != mValues.end(); ++iter)
				{
					newFunctor->setParameter(i, *iter);
					i++;
				}

				return static_cast<Cloneable*>(newFunctor);
			}

			/**
			 * Remove spaces from the start and end of a string and any enum, struct or class keyword at the beginnig
			 * of the string.
			 * @param type The type string to remove the spaces from.
			 */
			void trimType(std::string& type)
			{
				unsigned int pos;

				// Trim spaces from the beginning of the string
				for (pos = 0; (pos < type.length()) && (isspace(type[pos])); pos++)
				{
				}

				if (pos > 0)
				{
					type.erase(0, pos - 1);
				}

				// Trim spaces from the end of the string
				for (pos = type.length() - 1; (pos >= 0) && (isspace(type[pos])); pos--)
				{
				}

				if (pos <= type.length() - 1)
				{
					type.erase(pos + 1, type.length() - 1);
				}

				pos = type.find("enum ", 0);
				if (pos == 0)
				{
					type.erase(pos, pos + 5);
				}
				else
				{
					pos = type.find("class ", 0);
					if (pos == 0)
					{
						type.erase(pos, pos + 6);
					}
					else
					{
						pos = type.find("struct ", 0);
						if ((pos != std::string::npos) && (pos == 0))
						{
							type.erase(pos, pos + 7);
						}
					}
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
			void pushType(lua_State* luaState, std::string& type, P* parameter) throw (Exception)
			{
				std::string tType;
				swig_module_info *pModule;
				swig_type_info *pTypeInfo;

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


			/**
			 * Execute the Lua function that is wrapped in this functor.
			 * @param luaState The Lua state to use to execute the function.
			 * @return The value the Lua function returned.
			 * @throws Exception::E_LUA_ERROR if there was an error executing the function.
			 * @throws Exception::E_INVALID_PARAMETER if one of the parameters that should be passed to the LUA function is not defined 
			 *			in the LUA state.
			 */
			void operator()(lua_State* luaState) throw (Exception)
			{
				ValueVectorIterator iter;
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
				for (iter = mValues.begin(); iter != mValues.end(); ++iter)
				{
					Value& val = *iter;

					switch (val.getType())
					{
						case Value::VT_CHAR:
							pushType(luaState, "", val.getChar());
						break;
						case Value::VT_UCHAR:
							pushType(luaState, "", val.getUChar());
						break;
						case Value::VT_SHORT:
							pushType(luaState, "", val.getShort());
						break;
						case Value::VT_USHORT:
							pushType(luaState, "", val.getUShort());
						break;
						case Value::VT_INT:
							pushType(luaState, "", val.getInt());
						break;
						case Value::VT_UINT:
							pushType(luaState, "", val.getUInt());
						break;
						case Value::VT_LONG:
							pushType(luaState, "", val.getLong());
						break;
						case Value::VT_ULONG:
							pushType(luaState, "", val.getULong());
						break;
						case Value::VT_FLOAT:
							pushType(luaState, "", val.getFloat());
						break;
						case Value::VT_DOUBLE:
							pushType(luaState, "", val.getDouble());
						break;
						case Value::VT_STRING:
							pushType(luaState, "", val.getString());
						break;
						case Value::VT_NAMED_INSTANCE:
							pushType(luaState, trimType(typeid(*val.getNamedInstance())), val.getNamedInstance());
						break;
						case Value::VT_VOID_PTR:
							pushType(luaState, trimType(typeid(val.getVoidPtr())), val.getVoidPtr());
						break;
						case Value::VT_CONST_NAMED_INSTANCE:
							pushType(luaState, trimType(typeid(*val.getConstNamedInstance())), val.getConstNamedInstance());
						break;
						case Value::VT_CONST_VOID_PTR:
							pushType(luaState, trimType(typeid(val.getConstVoidPtr())), val.getConstVoidPtr());
						break;
					}
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
			/** Type definition of a std::vector of Value instances. */
			typedef std::vector<Value> ValueVector;
			/** Type definition of an iterator for ValueVector. */
			typedef ValueVector::iterator ValueVectorIterator;
			/** Type definition of a const_iterator for ValueVector. */
			typedef ValueVector::const_iterator ValueVectorConstIterator;

			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** A std::vector of the current parameters. */
			ValueVector mValues;

			/** Nullary Constructor */
			LuaFunctor()
			{
			}
	};

} // Myoushu

#endif

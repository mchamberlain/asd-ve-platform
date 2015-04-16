#ifndef ASTT_LUA_H
#define ASTT_LUA_H

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

//#define SWIG_name      "ASTT"
//#define SWIG_init      luaopen_ASTT
//#define SWIG_init_user luaopen_ASTT_user

//#define SWIG_LUACODE   luaopen_ASTT_luacode


/* Exported function */
#ifdef __cplusplus
extern "C" {
#endif
	SWIGEXPORT int luaopen_ASTT(lua_State* L);
#ifdef __cplusplus
}
#endif

#endif




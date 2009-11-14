#ifndef MYOUSHU_LUA_H
#define MYOUSHU_LUA_H

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

#define SWIG_name      "Myoushu"
#define SWIG_init      luaopen_Myoushu
#define SWIG_init_user luaopen_Myoushu_user

#define SWIG_LUACODE   luaopen_Myoushu_luacode

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__)) 
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__)) 
# else
#   define SWIGUNUSED 
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif 
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED 
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

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

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif 
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif


/* -----------------------------------------------------------------------------
 * swigrun.swg
 *
 * This file contains generic C API SWIG runtime support for pointer
 * type checking.
 * ----------------------------------------------------------------------------- */

/* This should only be incremented when either the layout of swig_type_info changes,
   or for whatever reason, the runtime changes incompatibly */
#define SWIG_RUNTIME_VERSION "4"

/* define SWIG_TYPE_TABLE_NAME as "SWIG_TYPE_TABLE" */
#ifdef SWIG_TYPE_TABLE
# define SWIG_QUOTE_STRING(x) #x
# define SWIG_EXPAND_AND_QUOTE_STRING(x) SWIG_QUOTE_STRING(x)
# define SWIG_TYPE_TABLE_NAME SWIG_EXPAND_AND_QUOTE_STRING(SWIG_TYPE_TABLE)
#else
# define SWIG_TYPE_TABLE_NAME
#endif

/*
  You can use the SWIGRUNTIME and SWIGRUNTIMEINLINE macros for
  creating a static or dynamic library from the SWIG runtime code.
  In 99.9% of the cases, SWIG just needs to declare them as 'static'.
  
  But only do this if strictly necessary, ie, if you have problems
  with your compiler or suchlike.
*/

#ifndef SWIGRUNTIME
# define SWIGRUNTIME SWIGEXPORT
#endif

#ifndef SWIGRUNTIMEINLINE
# define SWIGRUNTIMEINLINE SWIGRUNTIME SWIGINLINE
#endif

/*  Generic buffer size */
#ifndef SWIG_BUFFER_SIZE
# define SWIG_BUFFER_SIZE 1024
#endif

/* Flags for pointer conversions */
#define SWIG_POINTER_DISOWN        0x1
#define SWIG_CAST_NEW_MEMORY       0x2

/* Flags for new pointer objects */
#define SWIG_POINTER_OWN           0x1


/* 
   Flags/methods for returning states.
   
   The SWIG conversion methods, as ConvertPtr, return and integer 
   that tells if the conversion was successful or not. And if not,
   an error code can be returned (see swigerrors.swg for the codes).
   
   Use the following macros/flags to set or process the returning
   states.
   
   In old versions of SWIG, code such as the following was usually written:

     if (SWIG_ConvertPtr(obj,vptr,ty.flags) != -1) {
       // success code
     } else {
       //fail code
     }

   Now you can be more explicit:

    int res = SWIG_ConvertPtr(obj,vptr,ty.flags);
    if (SWIG_IsOK(res)) {
      // success code
    } else {
      // fail code
    }

   which is the same really, but now you can also do

    Type *ptr;
    int res = SWIG_ConvertPtr(obj,(void **)(&ptr),ty.flags);
    if (SWIG_IsOK(res)) {
      // success code
      if (SWIG_IsNewObj(res) {
        ...
	delete *ptr;
      } else {
        ...
      }
    } else {
      // fail code
    }
    
   I.e., now SWIG_ConvertPtr can return new objects and you can
   identify the case and take care of the deallocation. Of course that
   also requires SWIG_ConvertPtr to return new result values, such as

      int SWIG_ConvertPtr(obj, ptr,...) {         
        if (<obj is ok>) {			       
          if (<need new object>) {		       
            *ptr = <ptr to new allocated object>; 
            return SWIG_NEWOBJ;		       
          } else {				       
            *ptr = <ptr to old object>;	       
            return SWIG_OLDOBJ;		       
          } 				       
        } else {				       
          return SWIG_BADOBJ;		       
        }					       
      }

   Of course, returning the plain '0(success)/-1(fail)' still works, but you can be
   more explicit by returning SWIG_BADOBJ, SWIG_ERROR or any of the
   SWIG errors code.

   Finally, if the SWIG_CASTRANK_MODE is enabled, the result code
   allows to return the 'cast rank', for example, if you have this

       int food(double)
       int fooi(int);

   and you call
 
      food(1)   // cast rank '1'  (1 -> 1.0)
      fooi(1)   // cast rank '0'

   just use the SWIG_AddCast()/SWIG_CheckState()
*/

#define SWIG_OK                    (0) 
#define SWIG_ERROR                 (-1)
#define SWIG_IsOK(r)               (r >= 0)
#define SWIG_ArgError(r)           ((r != SWIG_ERROR) ? r : SWIG_TypeError)  

/* The CastRankLimit says how many bits are used for the cast rank */
#define SWIG_CASTRANKLIMIT         (1 << 8)
/* The NewMask denotes the object was created (using new/malloc) */
#define SWIG_NEWOBJMASK            (SWIG_CASTRANKLIMIT  << 1)
/* The TmpMask is for in/out typemaps that use temporal objects */
#define SWIG_TMPOBJMASK            (SWIG_NEWOBJMASK << 1)
/* Simple returning values */
#define SWIG_BADOBJ                (SWIG_ERROR)
#define SWIG_OLDOBJ                (SWIG_OK)
#define SWIG_NEWOBJ                (SWIG_OK | SWIG_NEWOBJMASK)
#define SWIG_TMPOBJ                (SWIG_OK | SWIG_TMPOBJMASK)
/* Check, add and del mask methods */
#define SWIG_AddNewMask(r)         (SWIG_IsOK(r) ? (r | SWIG_NEWOBJMASK) : r)
#define SWIG_DelNewMask(r)         (SWIG_IsOK(r) ? (r & ~SWIG_NEWOBJMASK) : r)
#define SWIG_IsNewObj(r)           (SWIG_IsOK(r) && (r & SWIG_NEWOBJMASK))
#define SWIG_AddTmpMask(r)         (SWIG_IsOK(r) ? (r | SWIG_TMPOBJMASK) : r)
#define SWIG_DelTmpMask(r)         (SWIG_IsOK(r) ? (r & ~SWIG_TMPOBJMASK) : r)
#define SWIG_IsTmpObj(r)           (SWIG_IsOK(r) && (r & SWIG_TMPOBJMASK))

/* Cast-Rank Mode */
#if defined(SWIG_CASTRANK_MODE)
#  ifndef SWIG_TypeRank
#    define SWIG_TypeRank             unsigned long
#  endif
#  ifndef SWIG_MAXCASTRANK            /* Default cast allowed */
#    define SWIG_MAXCASTRANK          (2)
#  endif
#  define SWIG_CASTRANKMASK          ((SWIG_CASTRANKLIMIT) -1)
#  define SWIG_CastRank(r)           (r & SWIG_CASTRANKMASK)
SWIGINTERNINLINE int SWIG_AddCast(int r) { 
  return SWIG_IsOK(r) ? ((SWIG_CastRank(r) < SWIG_MAXCASTRANK) ? (r + 1) : SWIG_ERROR) : r;
}
SWIGINTERNINLINE int SWIG_CheckState(int r) { 
  return SWIG_IsOK(r) ? SWIG_CastRank(r) + 1 : 0; 
}
#else /* no cast-rank mode */
#  define SWIG_AddCast
#  define SWIG_CheckState(r) (SWIG_IsOK(r) ? 1 : 0)
#endif


#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*swig_converter_func)(void *, int *);
typedef struct swig_type_info *(*swig_dycast_func)(void **);

/* Structure to store information on one type */
typedef struct swig_type_info {
  const char             *name;			/* mangled name of this type */
  const char             *str;			/* human readable name of this type */
  swig_dycast_func        dcast;		/* dynamic cast function down a hierarchy */
  struct swig_cast_info  *cast;			/* linked list of types that can cast into this type */
  void                   *clientdata;		/* language specific type data */
  int                    owndata;		/* flag if the structure owns the clientdata */
} swig_type_info;

/* Structure to store a type and conversion function used for casting */
typedef struct swig_cast_info {
  swig_type_info         *type;			/* pointer to type that is equivalent to this type */
  swig_converter_func     converter;		/* function to cast the void pointers */
  struct swig_cast_info  *next;			/* pointer to next cast in linked list */
  struct swig_cast_info  *prev;			/* pointer to the previous cast */
} swig_cast_info;

/* Structure used to store module information
 * Each module generates one structure like this, and the runtime collects
 * all of these structures and stores them in a circularly linked list.*/
typedef struct swig_module_info {
  swig_type_info         **types;		/* Array of pointers to swig_type_info structures that are in this module */
  size_t                 size;		        /* Number of types in this module */
  struct swig_module_info *next;		/* Pointer to next element in circularly linked list */
  swig_type_info         **type_initial;	/* Array of initially generated type structures */
  swig_cast_info         **cast_initial;	/* Array of initially generated casting structures */
  void                    *clientdata;		/* Language specific module data */
} swig_module_info;

/* 
  Compare two type names skipping the space characters, therefore
  "char*" == "char *" and "Class<int>" == "Class<int >", etc.

  Return 0 when the two name types are equivalent, as in
  strncmp, but skipping ' '.
*/
SWIGRUNTIME int
SWIG_TypeNameComp(const char *f1, const char *l1,
		  const char *f2, const char *l2);

/*
  Check type equivalence in a name list like <name1>|<name2>|...
  Return 0 if not equal, 1 if equal
*/
SWIGRUNTIME int
SWIG_TypeEquiv(const char *nb, const char *tb);

/*
  Check type equivalence in a name list like <name1>|<name2>|...
  Return 0 if equal, -1 if nb < tb, 1 if nb > tb
*/
SWIGRUNTIME int
SWIG_TypeCompare(const char *nb, const char *tb);


/*
  Check the typename
*/
SWIGRUNTIME swig_cast_info *
SWIG_TypeCheck(const char *c, swig_type_info *ty);

/* 
  Identical to SWIG_TypeCheck, except strcmp is replaced with a pointer comparison
*/
SWIGRUNTIME swig_cast_info *
SWIG_TypeCheckStruct(swig_type_info *from, swig_type_info *ty);

/*
  Cast a pointer up an inheritance hierarchy
*/
SWIGRUNTIMEINLINE void *
SWIG_TypeCast(swig_cast_info *ty, void *ptr, int *newmemory);

/* 
   Dynamic pointer casting. Down an inheritance hierarchy
*/
SWIGRUNTIME swig_type_info *
SWIG_TypeDynamicCast(swig_type_info *ty, void **ptr);

/*
  Return the name associated with this type
*/
SWIGRUNTIMEINLINE const char *
SWIG_TypeName(const swig_type_info *ty);

/*
  Return the pretty name associated with this type,
  that is an unmangled type name in a form presentable to the user.
*/
SWIGRUNTIME const char *
SWIG_TypePrettyName(const swig_type_info *type);

/* 
   Set the clientdata field for a type
*/
SWIGRUNTIME void
SWIG_TypeClientData(swig_type_info *ti, void *clientdata);

SWIGRUNTIME void
SWIG_TypeNewClientData(swig_type_info *ti, void *clientdata);
  
/*
  Search for a swig_type_info structure only by mangled name
  Search is a O(log #types)
  
  We start searching at module start, and finish searching when start == end.  
  Note: if start == end at the beginning of the function, we go all the way around
  the circular list.
*/
SWIGRUNTIME swig_type_info *
SWIG_MangledTypeQueryModule(swig_module_info *start, 
                            swig_module_info *end, 
		            const char *name);

/*
  Search for a swig_type_info structure for either a mangled name or a human readable name.
  It first searches the mangled names of the types, which is a O(log #types)
  If a type is not found it then searches the human readable names, which is O(#types).
  
  We start searching at module start, and finish searching when start == end.  
  Note: if start == end at the beginning of the function, we go all the way around
  the circular list.
*/
SWIGRUNTIME swig_type_info *
SWIG_TypeQueryModule(swig_module_info *start, 
                     swig_module_info *end, 
		     const char *name);

/* 
   Pack binary data into a string
*/
SWIGRUNTIME char *
SWIG_PackData(char *c, void *ptr, size_t sz);

/* 
   Unpack binary data from a string
*/
SWIGRUNTIME const char *
SWIG_UnpackData(const char *c, void *ptr, size_t sz);

/* 
   Pack 'void *' into a string buffer.
*/
SWIGRUNTIME char *
SWIG_PackVoidPtr(char *buff, void *ptr, const char *name, size_t bsz);

SWIGRUNTIME const char *
SWIG_UnpackVoidPtr(const char *c, void **ptr, const char *name);

SWIGRUNTIME char *
SWIG_PackDataName(char *buff, void *ptr, size_t sz, const char *name, size_t bsz);

SWIGRUNTIME const char *
SWIG_UnpackDataName(const char *c, void *ptr, size_t sz, const char *name);

#ifdef __cplusplus
}
#endif

/* -----------------------------------------------------------------------------
 * See the LICENSE file for information on copyright, usage and redistribution
 * of SWIG, and the README file for authors - http://www.swig.org/release.html.
 *
 * luarun.swg
 *
 * This file contains the runtime support for Lua modules
 * and includes code for managing global variables and pointer
 * type checking.
 * ----------------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"
#include <stdlib.h>  /* for malloc */
#include <assert.h>  /* for a few sanity tests */

/* -----------------------------------------------------------------------------
 * global swig types
 * ----------------------------------------------------------------------------- */
/* Constant table */
#define SWIG_LUA_INT     1
#define SWIG_LUA_FLOAT   2
#define SWIG_LUA_STRING  3
#define SWIG_LUA_POINTER 4
#define SWIG_LUA_BINARY  5
#define SWIG_LUA_CHAR    6

/* Structure for variable linking table */
typedef struct {
  const char *name;
  lua_CFunction get;
  lua_CFunction set;
} swig_lua_var_info;

/* Constant information structure */
typedef struct {
    int type;
    char *name;
    long lvalue;
    double dvalue;
    void   *pvalue;
    swig_type_info **ptype;
} swig_lua_const_info;

typedef struct {
  const char     *name;
  lua_CFunction   method;
} swig_lua_method;

typedef struct {
  const char     *name;
  lua_CFunction   getmethod;
  lua_CFunction   setmethod;
} swig_lua_attribute;

typedef struct swig_lua_class {
  const char    *name;
  swig_type_info   **type;
  lua_CFunction  constructor;
  void    (*destructor)(void *);
  swig_lua_method   *methods;
  swig_lua_attribute     *attributes;
  struct swig_lua_class **bases;
  const char **base_names;
} swig_lua_class;

/* this is the struct for wrappering all pointers in SwigLua
*/
typedef struct {
  swig_type_info   *type;
  int     own;  /* 1 if owned & must be destroyed */
  void        *ptr;
} swig_lua_userdata;

/* this is the struct for wrapping arbitary packed binary data
(currently it is only used for member function pointers)
the data ordering is similar to swig_lua_userdata, but it is currently not possible
to tell the two structures apart within Swig, other than by looking at the type
*/
typedef struct {
  swig_type_info   *type;
  int     own;  /* 1 if owned & must be destroyed */
  char data[1];       /* arbitary amount of data */    
} swig_lua_rawdata;

/* Common SWIG API */
#define SWIG_NewPointerObj(L, ptr, type, owner)       SWIG_Lua_NewPointerObj(L, (void *)ptr, type, owner)
#define SWIG_ConvertPtr(L,idx, ptr, type, flags)    SWIG_Lua_ConvertPtr(L,idx,ptr,type,flags)
#define SWIG_MustGetPtr(L,idx, type,flags, argnum,fnname)  SWIG_Lua_MustGetPtr(L,idx, type,flags, argnum,fnname)
/* for C++ member pointers, ie, member methods */
#define SWIG_ConvertMember(L, idx, ptr, sz, ty)       SWIG_Lua_ConvertPacked(L, idx, ptr, sz, ty)
#define SWIG_NewMemberObj(L, ptr, sz, type)      SWIG_Lua_NewPackedObj(L, ptr, sz, type)

/* Runtime API */
#define SWIG_GetModule(clientdata) SWIG_Lua_GetModule((lua_State*)(clientdata))
#define SWIG_SetModule(clientdata, pointer) SWIG_Lua_SetModule((lua_State*) (clientdata), pointer)
#define SWIG_MODULE_CLIENTDATA_TYPE lua_State*

/* Contract support */
#define SWIG_contract_assert(expr, msg)  \
  if (!(expr)) { lua_pushstring(L, (char *) msg); goto fail; } else

/* helper #defines */
#define SWIG_fail {goto fail;}
#define SWIG_fail_arg(func_name,argnum,type) \
  {lua_pushfstring(L,"Error in %s (arg %d), expected '%s' got '%s'",\
  func_name,argnum,type,SWIG_Lua_typename(L,argnum));\
  goto fail;}
#define SWIG_fail_ptr(func_name,argnum,type) \
  SWIG_fail_arg(func_name,argnum,(type && type->str)?type->str:"void*")
#define SWIG_check_num_args(func_name,a,b) \
  if (lua_gettop(L)<a || lua_gettop(L)>b) \
  {lua_pushfstring(L,"Error in %s expected %d..%d args, got %d",func_name,a,b,lua_gettop(L));\
  goto fail;}


#define SWIG_Lua_get_table(L,n) \
  (lua_pushstring(L, n), lua_rawget(L,-2))

#define SWIG_Lua_add_function(L,n,f) \
  (lua_pushstring(L, n), \
      lua_pushcfunction(L, f), \
      lua_rawset(L,-3))

/* special helper for allowing 'nil' for usertypes */
#define SWIG_isptrtype(L,I) (lua_isuserdata(L,I) || lua_isnil(L,I))

#ifdef __cplusplus
/* Special helper for member function pointers 
it gets the address, casts it, then dereferences it */
//#define SWIG_mem_fn_as_voidptr(a)  (*((char**)&(a)))
#endif

/* storing/access of swig_module_info */
SWIGRUNTIME swig_module_info *
SWIG_Lua_GetModule(lua_State* L);

SWIGRUNTIME void
SWIG_Lua_SetModule(lua_State* L, swig_module_info *module);

/* -----------------------------------------------------------------------------
 * global variable support code: modules
 * ----------------------------------------------------------------------------- */

/* this function is called when trying to set an immutable.
default value is to print an error.
This can removed with a compile flag SWIGLUA_IGNORE_SET_IMMUTABLE */
SWIGINTERN int SWIG_Lua_set_immutable(lua_State* L);

/* the module.get method used for getting linked data */
SWIGINTERN int SWIG_Lua_module_get(lua_State* L);

/* the module.set method used for setting linked data */
SWIGINTERN int SWIG_Lua_module_set(lua_State* L);

/* registering a module in lua */
SWIGINTERN void  SWIG_Lua_module_begin(lua_State* L,const char* name);

/* ending the register */
SWIGINTERN void  SWIG_Lua_module_end(lua_State* L);

/* adding a linked variable to the module */
SWIGINTERN void SWIG_Lua_module_add_variable(lua_State* L,const char* name,lua_CFunction getFn,lua_CFunction setFn);

/* adding a function module */
SWIGINTERN void  SWIG_Lua_module_add_function(lua_State* L,const char* name,lua_CFunction fn);

/* -----------------------------------------------------------------------------
 * global variable support code: classes
 * ----------------------------------------------------------------------------- */

/* the class.get method, performs the lookup of class attributes */
SWIGINTERN int  SWIG_Lua_class_get(lua_State* L);

/* the class.set method, performs the lookup of class attributes */
SWIGINTERN int  SWIG_Lua_class_set(lua_State* L);

/* the class.destruct method called by the interpreter */
SWIGINTERN int  SWIG_Lua_class_destruct(lua_State* L);

/* gets the swig class registry (or creates it) */
SWIGINTERN void  SWIG_Lua_get_class_registry(lua_State* L);

/* helper fn to get the classes metatable from the register */
SWIGINTERN void  SWIG_Lua_get_class_metatable(lua_State* L,const char* cname);

/* helper add a variable to a registered class */
SWIGINTERN void  SWIG_Lua_add_class_variable(lua_State* L,const char* name,lua_CFunction getFn,lua_CFunction setFn);

/* helper to recursively add class details (attributes & operations) */
SWIGINTERN void  SWIG_Lua_add_class_details(lua_State* L,swig_lua_class* clss);

/* set up the base classes pointers.
Each class structure has a list of pointers to the base class structures.
This function fills them.
It cannot be done at compile time, as this will not work with hireachies
spread over more than one swig file. 
Therefore it must be done at runtime, querying the SWIG type system.
*/
SWIGINTERN void SWIG_Lua_init_base_class(lua_State* L,swig_lua_class* clss);

/* performs the entire class registration process */
SWIGINTERN void  SWIG_Lua_class_register(lua_State* L,swig_lua_class* clss);

/* -----------------------------------------------------------------------------
 * Class/structure conversion fns
 * ----------------------------------------------------------------------------- */

/* helper to add metatable to new lua object */
SWIGINTERN void _SWIG_Lua_AddMetatable(lua_State* L,swig_type_info *type);

/* pushes a new object into the lua stack */
SWIGRUNTIME void SWIG_Lua_NewPointerObj(lua_State* L,void* ptr,swig_type_info *type, int own);

/* takes a object from the lua stack & converts it into an object of the correct type
 (if possible) */
SWIGRUNTIME int  SWIG_Lua_ConvertPtr(lua_State* L,int index,void** ptr,swig_type_info *type,int flags);

SWIGRUNTIME void* SWIG_Lua_MustGetPtr(lua_State* L,int index,swig_type_info *type,int flags,
       int argnum,const char* func_name);

/* pushes a packed userdata. user for member fn pointers only */
SWIGRUNTIME void SWIG_Lua_NewPackedObj(lua_State* L,void* ptr,size_t size,swig_type_info *type);
    
/* converts a packed userdata. user for member fn pointers only */
SWIGRUNTIME int  SWIG_Lua_ConvertPacked(lua_State* L,int index,void* ptr,size_t size,swig_type_info *type);

/* a function to get the typestring of a piece of data */
SWIGRUNTIME const char *SWIG_Lua_typename(lua_State *L, int tp);

/* lua callable function to get the userdata's type */
SWIGRUNTIME int SWIG_Lua_type(lua_State* L);

/* lua callable function to compare userdata's value
the issue is that two userdata may point to the same thing
but to lua, they are different objects */
SWIGRUNTIME int SWIG_Lua_equal(lua_State* L);
/* -----------------------------------------------------------------------------
 * global variable support code: class/struct typemap functions
 * ----------------------------------------------------------------------------- */

/* Install Constants */
SWIGINTERN void
SWIG_Lua_InstallConstants(lua_State* L, swig_lua_const_info constants[]);
/* -----------------------------------------------------------------------------
 * executing lua code from within the wrapper
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_DOSTRING_FAIL /* Allows redefining of error function */
#define SWIG_DOSTRING_FAIL(S) fprintf(stderr,"%s\n",S)
#endif
/* Executes a C string in Lua a really simple way of calling lua from C
Unfortunately lua keeps changing its API's, so we need a conditional compile
In lua 5.0.X its lua_dostring()
In lua 5.1.X its luaL_dostring()
*/
SWIGINTERN int 
SWIG_Lua_dostring(lua_State *L, const char* str);
#ifdef __cplusplus
}
#endif

/* Exported function */
#ifdef __cplusplus
extern "C" {
#endif
	SWIGEXPORT int SWIG_init(lua_State* L);
#ifdef __cplusplus
}
#endif

#endif




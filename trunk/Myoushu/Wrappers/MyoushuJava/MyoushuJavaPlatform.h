/**
 * @file MyoushuJavaPlatform.h
 * @author ME Chamberlain
 * @date April 2008
 */

/**
 * This file defines some platform specific settings.
 */

#ifndef MYOUSHU_JAVA_PLATFORM_H
#define MYOUSHU_JAVA_PLATFORM_H

// Stupid dumb-ass windows headers mess up std::min and std::max if NOMINMAX is not defined
#define NOMINMAX

// include some standard integer types and limits
#ifndef _MSC_VER
#	include <stdint.h>
#endif

// If DEBUG or _DEBUG is defined, define MYOUSHU_JAVA_DEBUG
#if (defined(DEBUG) || defined(_DEBUG))
#	if !defined(MYOUSHU_JAVA_DEBUG)
#		define MYOUSHU_JAVA_DEBUG
#	endif
#elif defined(MYOUSHU_JAVA_DEBUG)
#	undef MYOUSHU_JAVA_DEBUG
#endif

// If Windows is being used, we have to declare the classes as being exported or imported
// depending on whether a shared library is being built. In Linux or other platforms this is
// not necessary.
#if defined(_WIN32) || defined(_WIN64)
#	if defined(MYOUSHU_JAVA_DLL)
#		define MYOUSHU_JAVA_API __declspec(dllexport)
#	else
#		define MYOUSHU_JAVA_API __declspec(dllimport)
#	endif
#else
#	define MYOUSHU_JAVA_API
#endif

// Find the architecture type
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#	define MYOUSHU_JAVA_ARCH_TYPE MYOUSHU_JAVA_ARCH_64
	/** An unsigned integer type to store memory addresses. */
#	ifndef _MSC_VER
		typedef uint64_t memUInt;
#	else
		typedef size_t memUInt;
#	endif
#else
#	define MYOUSHU_JAVA_ARCH_TYPE MYOUSHU_JAVA_ARCH_32
	/** An unsigned integer type to store memory addresses. */
#	ifndef _MSC_VER
		typedef uint32_t memUInt;
#	else
		typedef size_t memUInt;
#	endif
#endif

// Make sure that NULL is defined
#ifndef NULL
#	define NULL 0
#endif

// Fix MSVC broken static casting between class types
#if defined(_MSC_VER) && (_MSC_VER <= 1500)
#	define STATIC_CAST_PTR(destType, srcType, ptr) ((destType)((size_t) ptr + ((size_t)(destType)1 - (size_t)(srcType)(destType)1)))
#else
#	define STATIC_CAST_PTR(destType, srcType, ptr) static_cast<destType>(ptr)
#endif

#endif // PLATFORM_H

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
along with The ASD Assist VE Platform.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file Platform.h
 * @author ME Chamberlain
 * @date April 2008
 */

/**
 * This file defines some platform specific settings.
 */

#ifndef ASTT_PLATFORM_H
#define ASTT_PLATFORM_H

// Stupid dumb-ass windows headers mess up std::min and std::max if NOMINMAX is not defined
#define NOMINMAX

// include some standard integer types and limits
#ifndef _MSC_VER
#	include <stdint.h>
#endif

// If DEBUG or _DEBUG is defined, define ASTT_DEBUG
#if (defined(DEBUG) || defined(_DEBUG))
#	if !defined(ASTT_DEBUG)
#		define ASTT_DEBUG
#	endif
#elif defined(ASTT_DEBUG)
#	undef ASTT_DEBUG
#endif

// If Windows is being used, we have to declare the classes as being exported or imported
// depending on whether a shared library is being built. In Linux or other platforms this is
// not necessary.
#if defined(_WIN32) || defined(_WIN64)
#	if defined(ASTT_DLL)
#		define ASTT_API __declspec(dllexport)
#	else
#		define ASTT_API __declspec(dllimport)
#	endif
#else
#	define ASTT_API
#endif

// Find the architecture type
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#	define ASTT_ARCH_TYPE ASTT_ARCH_64
	/** An unsigned integer type to store memory addresses. */
#	ifndef _MSC_VER
		typedef uint64_t memUInt;
#	else
		typedef size_t memUInt;
#	endif
#else
#	define ASTT_ARCH_TYPE ASTT_ARCH_32
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

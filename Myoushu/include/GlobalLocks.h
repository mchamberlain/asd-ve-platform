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
 * @file GlobalLocks.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef GLOBAL_LOCKS_H
#define GLOBAL_LOCKS_H

#include "Poco/RWLock.h"

#include "Platform.h"

namespace Myoushu
{
	/**
	 * This class defines some static locks that are used throughout the engine.
	 * These are mostly to enforce mutual exclusion on third party libraries that are not thread safe.
	 */
	class MYOUSHU_API GlobalLocks
	{
		public:
			/** Read/write Mutex on the Ogre::Root object. */
			static Poco::RWLock rwLockOgreRoot;

			/** Read/Write Mutex on accesses to MyGUI. */
			static Poco::RWLock rwLockMyGUI;

			/** Read/Write Mutex on accesses to NxOgre. */
			static Poco::RWLock rwLockNxOgre;
	};
} // Myoushu

#endif

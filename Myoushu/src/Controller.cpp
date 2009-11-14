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
 * @file Controller.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "Controller.h"

namespace Myoushu
{
	CLASS_NAME(Controller, "Myoushu::Controller");

	Controller::Controller(const Ogre::String& name) : NamedInstance(name), enabled(true)
	{
	}

	Controller::~Controller()
	{
	}

	memUInt Controller::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Controller::serialize(): buffer is NULL!");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		writtenSize = writePrimitiveType(enabled, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Controller::serialize(): buffer is too small.");
		}

		return totalSize;
	}

	memUInt Controller::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Controller::populateInstance(): buffer is NULL!");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		readSize = readPrimitiveType(enabled, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Controller::populateInstance(): buffer is too small.");
		}

		return totalSize;
	}

} // Myoushu

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
 * @file NamedInstance.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "NamedInstance.h"

namespace Myoushu
{
	CLASS_NAME(NamedInstance, "Myoushu::NamedInstance");

	NamedInstance::NamedInstance(const std::string& instanceName) : instanceName(instanceName)
	{
	}

	NamedInstance::~NamedInstance()
	{
	}

	memUInt NamedInstance::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		char *pBuf;
		memUInt writeSize;
		memUInt totalSize;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NamedInstance::populateInstance(): pMem is NULL.");
		}

		pBuf = static_cast<char*>(pMem);
		writeSize = 0;
		totalSize = 0;

		// Read the name field
		writeSize = writeString(instanceName, pBuf);
		pBuf += writeSize;
		totalSize += writeSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NamedInstance::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

	memUInt NamedInstance::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		const char *pBuf;
		memUInt readSize;
		memUInt totalSize;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NamedInstance::populateInstance(): pMem is NULL.");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// Read the name field
		readSize = readString(instanceName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "NamedInstance::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // Myoushu

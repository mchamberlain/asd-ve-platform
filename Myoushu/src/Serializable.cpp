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
 * @file Serializable.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include "Serializable.h"
#include "EngineLog.h"

namespace Myoushu
{

	memUInt Serializable::writeString(const std::string& str, void* pBuf) const
	{
		memUInt uBuf;

		uBuf = (memUInt) pBuf;
		uBuf += writePrimitiveType(str.length(), reinterpret_cast<void*>(uBuf));
		memcpy(reinterpret_cast<void *>(uBuf), str.c_str(), str.length());

		return sizeof(char) * str.length() + sizeof(size_t);
	}

	memUInt Serializable::writeStringArray(const std::string* str, memUInt cnt, void* pBuf) const
	{
		memUInt writtenSize;
		memUInt size;
		memUInt uBuf;

		writtenSize = 0;
		uBuf = (memUInt) pBuf;
		for (memUInt i = 0; i < cnt; i++)
		{
			size = writeString(str[i], reinterpret_cast<void*>(uBuf));
			uBuf += size;
			writtenSize += size;
		}

		return writtenSize;
	}

	memUInt Serializable::writeOgreVector3(const Ogre::Vector3& vector, void* pBuf) const
	{
		memUInt writtenSize;
		memUInt uBuf;
		Ogre::Real temp;

		writtenSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 3; i++)
		{
			temp = vector[i];
			memcpy(reinterpret_cast<Ogre::Real*>(uBuf), &temp, sizeof(Ogre::Real));
			uBuf += sizeof(Ogre::Real);
			writtenSize += sizeof(Ogre::Real);
		}

		return writtenSize;
	}

	memUInt Serializable::writeNxVec3(const NxVec3& vector, void* pBuf) const
	{
		memUInt writtenSize;
		memUInt uBuf;
		NxReal temp;

		writtenSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 3; i++)
		{
			temp = vector[i];
			memcpy(reinterpret_cast<NxReal*>(uBuf), &temp, sizeof(NxReal));
			uBuf += sizeof(NxReal);
			writtenSize += sizeof(NxReal);
		}

		return writtenSize;
	}

	memUInt Serializable::writeOgreQuaternion(const Ogre::Quaternion& vector, void* pBuf) const
	{
		memUInt writtenSize;
		memUInt uBuf;
		Ogre::Real temp;

		writtenSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 4; i++)
		{
			temp = vector[i];
			memcpy(reinterpret_cast<Ogre::Real*>(uBuf), &temp, sizeof(Ogre::Real));
			uBuf += sizeof(Ogre::Real);
			writtenSize += sizeof(Ogre::Real);
		}

		return writtenSize;
	}

	memUInt Serializable::readString(std::string& str, const void* pBuf)
	{
		std::string::size_type strLength;
		memUInt readSize;
		memUInt uBuf;
		
		uBuf = (memUInt) pBuf;
		strLength = 0;
		readSize = readPrimitiveType(strLength, reinterpret_cast<void*>(uBuf));
		uBuf += readSize;

		readSize += sizeof(char) * strLength;
		str.clear();
		if (strLength > 0)
		{
			str.assign(reinterpret_cast<char *>(uBuf), strLength);
		}

		return readSize;
	}

	memUInt Serializable::readStringArray(std::string* str, memUInt cnt, const void* pBuf)
	{
		memUInt size;
		memUInt readSize;
		memUInt uBuf;

		size = 0;
		readSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < cnt; i++)
		{
			size = readString(str[i], reinterpret_cast<void*>(uBuf));
			readSize += size;
			uBuf += size;
		}

		return readSize;
	}

	memUInt Serializable::readOgreVector3(Ogre::Vector3& vector, const void* pBuf)
	{
		memUInt size;
		memUInt readSize;
		memUInt uBuf;

		size = 0;
		readSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 3; i++)
		{
			size = readPrimitiveType(vector[i], reinterpret_cast<void*>(uBuf));
			readSize += size;
			uBuf += size;
		}

		return readSize;
	}

	memUInt Serializable::readNxVec3(NxVec3& vector, const void* pBuf)
	{
		memUInt size;
		memUInt readSize;
		memUInt uBuf;

		size = 0;
		readSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 3; i++)
		{
			size = readPrimitiveType(vector[i], reinterpret_cast<void*>(uBuf));
			readSize += size;
			uBuf += size;
		}

		return readSize;
	}

	memUInt Serializable::readOgreQuaternion(Ogre::Quaternion& quat, const void* pBuf)
	{
		memUInt size;
		memUInt readSize;
		memUInt uBuf;

		size = 0;
		readSize = 0;
		uBuf = (memUInt) pBuf;
		for (unsigned int i = 0; i < 4; i++)
		{
			size = readPrimitiveType(quat[i], reinterpret_cast<void*>(uBuf));
			readSize += size;
			uBuf += size;
		}

		return readSize;
	}

} // namespace Myoushu


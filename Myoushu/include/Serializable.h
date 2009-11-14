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
 * @file Serializable.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef MYOUSHU_SERIALIZABLE_H
#define MYOUSHU_SERIALIZABLE_H

#include "Ogre.h"
#include "NxOgre.h"

#include "Platform.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class provides functions and an interface for serializing an instance and reading or creating an instance from
	 * serialized data.
	 */
	class MYOUSHU_API Serializable
	{
		public:
			/** 
			 * An enumeration of serialization targets. In the case of ST_NETWORK certain optimizations and logic (appending the host IP address
			 * to certain name and identifier fields for instance) can be made.
			 */
			enum SerializationTarget
			{
				/** Allows for the specific optimizations or logic when serializing data for network transmission. */
				ST_NETWORK = 0,
				/** Allows for the specific optimizations or logic when serializing data for updating an instance over a network transmission. */
				ST_NETWORK_UPDATE = 0,
				/** Unknown serialization target. */
				ST_UNKNOWN
			};

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialized data (in bytes).
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception) = 0;

			/**
			 * Populates this instance with the serialized description read from the specified buffer.
			 * @param pMem The buffer to read the instance description from.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the data read (in bytes).
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception) = 0;

		protected:
			/**
			 * Writes a primitive type (bool, char, short, int, long (with unsigned), float, double and enum.
			 * @param value The primitive value to write.
			 * @param pBuf The memory buffer to write too.
			 * @return The number of bytes written to the buffer.
			 */
			template<class T>
			memUInt writePrimitiveType(T value, void* pBuf) const;

			/**
			 * Writes an array of a primitive type (bool, char, short, int, long (with unsigned), float, double and enum.
			 * @param value Pointer to the start of the array.
			 * @param cnt The number of elements in the array to write.
			 * @param pBuf The memory buffer to write too.
			 * @return The number of bytes written to the buffer.
			 */
			template<class T>
			memUInt writePrimitiveTypeArray(T* values, memUInt cnt, void* pBuf) const;

			/**
			 * Serializes the given string to the given buffer.
			 * @param str The std::string to serialize.
			 * @param pBuf The buffer to serialize the string too.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt writeString(const std::string& str, void* pBuf) const;

			/**
			 * Serializes the given array of strings to the given buffer.
			 * @param str The array of std::string instances to serialize.
			 * @param cnt The number of elements in the array.
			 * @param pBuf The buffer to serialize the strings too.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt writeStringArray(const std::string* str, memUInt cnt, void* pBuf) const;

			/**
			 * Serialises an Ogre::Vector3 instance to the given buffer.
			 * @param vector The Ogre::Vector3 to serialize.
			 * @param pBuf The buffer to serialize the vector to.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt writeOgreVector3(const Ogre::Vector3& vector, void* pBuf) const;

			/**
			 * Serialises an NxVec3 instance to the given buffer.
			 * @param vector The NxVec3 to serialize.
			 * @param pBuf The buffer to serialize the vector to.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt writeNxVec3(const NxVec3& vector, void* pBuf) const;

			/**
			 * Serialises an Ogre::Quaternion instance to the given buffer.
			 * @param vector The Ogre::Quaternion to serialize.
			 * @param pBuf The buffer to serialize the vector to.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt writeOgreQuaternion(const Ogre::Quaternion& quat, void* pBuf) const;

			/**
			 * Reads a primitive type (bool, char, short, int, long (with unsigned), float, double and enum.
			 * @param value The primitive value to read.
			 * @param pBuf The memory buffer to read from.
			 * @return The number of bytes written to the buffer.
			 */
			template<class T>
			memUInt readPrimitiveType(T& value, const void* pBuf);

			/**
			 * Reads an array of a primitive type (bool, char, short, int, long (with unsigned), float, double and enum.
			 * @param value Pointer to the start of the array.
			 * @param cnt The number of elements in the array to read.
			 * @param pBuf The memory buffer to read from.
			 * @return The number of bytes written to the buffer.
			 */
			template<class T>
			memUInt readPrimitiveTypeArray(T* values, memUInt cnt, const void* pBuf);

			/**
			 * Serializes the given string to the given buffer.
			 * @param str The std::string to populate.
			 * @param pBuf The buffer to read the string from.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt readString(std::string& str, const void* pBuf);

			/**
			 * Serializes the given array of strings to the given buffer.
			 * @param str The array of std::string instances to populate.
			 * @param cnt The number of elements in the array.
			 * @param pBuf The buffer to read the strings from.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt readStringArray(std::string* str, memUInt cnt, const void* pBuf);

			/**
			 * Serialises an Ogre::Vector3 instance to the given buffer.
			 * @param vector The Ogre::Vector3 to populate.
			 * @param pBuf The buffer to read the vector from.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt readOgreVector3(Ogre::Vector3& vector, const void* pBuf);

			/**
			 * Serialises an NxVec3 instance to the given buffer.
			 * @param vector The NxVec3 to populate.
			 * @param pBuf The buffer to read the vector from.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt readNxVec3(NxVec3& vector, const void* pBuf);

			/**
			 * Serialises an Ogre::Quaternion instance to the given buffer.
			 * @param vector The Ogre::Quaternion to populate.
			 * @param pBuf The buffer to read the vector from.
			 * @return The number of bytes written to the buffer.
			 */
			memUInt readOgreQuaternion(Ogre::Quaternion& quat, const void* pBuf);
	};

	// templates
	template<class T>
	memUInt Serializable::writePrimitiveType(T value, void *pBuf) const
	{
		memcpy(pBuf, &value, sizeof(T));

		return sizeof(T);
	}

	template<class T>
	memUInt Serializable::writePrimitiveTypeArray(T* values, memUInt cnt, void *pBuf) const
	{
		memUInt writtenSize;
		memUInt uBuf;

		writtenSize = 0;
		uBuf = (memUInt) pBuf;
		for (memUInt i = 0; i < cnt; i++)
		{
			memcpy(reinterpret_cast<void*>(uBuf), &values[i], sizeof(T));
			uBuf += sizeof(T);
			writtenSize += sizeof(T);
		}

		return writtenSize;
	}

	template<class T>
	memUInt Serializable::readPrimitiveType(T& value, const void* pBuf)
	{
		//value = *reinterpret_cast<const T*>(pBuf);
		memcpy(&value, pBuf, sizeof(T));

		return sizeof(T);
	}

	template<class T>
	memUInt Serializable::readPrimitiveTypeArray(T* values, memUInt cnt, const void* pBuf)
	{
		memUInt readSize;
		memUInt uBuf;

		readSize = 0;
		uBuf = (memUInt) pBuf;
		for (memUInt i = 0; i < cnt; i++)
		{
			//values[i] = *(reinterpret_cast<T*>(uBuf));
			memcpy(values + i, reinterpret_cast<void*>(uBuf), sizeof(T));
			uBuf += sizeof(T);
			readSize += sizeof(T);
		}

		return readSize;
	}

} // namespace Myoushu

#endif

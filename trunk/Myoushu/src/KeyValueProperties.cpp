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
 * @file KeyValueProperties.cpp
 * @author ME Chamberlain
 * @date October 2008
 */

#include "KeyValueProperties.h"

namespace Myoushu
{
	KeyValueProperties::KeyValueProperties()
	{
	}

	KeyValueProperties::~KeyValueProperties()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		keyValueMap.clear();
	}

	void KeyValueProperties::clear()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		keyValueMap.clear();
	}

	void KeyValueProperties::insert(const std::string& key, Value *value) throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		keyValueMap[key] = value;
	}

	Value* KeyValueProperties::removeAndGetValue(const std::string& key)
	{
		KeyValueMapIterator iter;
		Value *value;

		Poco::ScopedRWLock lock(rwLock, true);

		iter = keyValueMap.find(key);
		if (iter == keyValueMap.end())
		{
			return NULL;
		}

		value = iter->second;
		// Use duplicate to increase the reference count since the object should not be auto freed here but
		// returned by the function
		value->duplicate();
		keyValueMap.erase(iter);

		return value;
	}

	bool KeyValueProperties::remove(const std::string& key)
	{
		KeyValueMapIterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		iter = keyValueMap.find(key);
		if (iter == keyValueMap.end())
		{
			return false;
		}

		keyValueMap.erase(iter);

		return true;
	}

	Value* KeyValueProperties::get(const std::string& key)
	{
		KeyValueMapIterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		iter = keyValueMap.find(key);
		if (iter == keyValueMap.end())
		{
			return NULL;
		}

		return iter->second;
	}

	const Value* KeyValueProperties::get(const std::string& key) const
	{
		KeyValueMapConstIterator iter;

		Poco::ScopedRWLock lock(rwLock, true);

		iter = keyValueMap.find(key);
		if (iter == keyValueMap.end())
		{
			return NULL;
		}

		return iter->second;
	}

	memUInt KeyValueProperties::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;
		KeyValueMap::const_iterator iter;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KeyValueProperties::serialize(): buffer is NULL.");
		}

		totalSize = 0;
		writtenSize = 0;
		pBuf = static_cast<char*>(pMem);

		// First write the number of property entries, then iterate over the map and serialize the key-value pairs.
		writtenSize = writePrimitiveType(keyValueMap.size(), pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::serialize(): buffer too small.");
		}

		for (iter = keyValueMap.begin(); iter != keyValueMap.end(); ++iter)
		{
			const Value *value = iter->second;

			// Write the key as a string
			writtenSize = writeString(iter->first, pBuf);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::serialize(): buffer too small.");
			}

			// Serialize the Value instance
			writtenSize = value->serialize(pBuf, size - totalSize, sTarget);
			pBuf += writtenSize;
			totalSize += writtenSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::serialize(): buffer too small.");
			}
		}

		return totalSize;
	}

	memUInt KeyValueProperties::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;
		unsigned int numOfEntries;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "KeyValueProperties::populateInstance(): buffer is NULL.");
		}

		readSize = 0;
		totalSize = 0;
		pBuf = static_cast<const char*>(pMem);

		// First read the number of property entries, then iterate over the map and serialize the key-value pairs.
		numOfEntries = 0;
		readSize = readPrimitiveType(numOfEntries, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::populateInstance(): buffer too small.");
		}

		for (unsigned int i = 0; i < numOfEntries; i++)
		{
			std::string key;
			Value *value;

			// Read the key as a string
			key = "";
			readSize = readString(key, pBuf);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::populateInstance(): buffer too small.");
			}

			// populate the Value instance
			value = new Value();
			readSize = value->populateInstance(pBuf, size - totalSize, sTarget);
			pBuf += readSize;
			totalSize += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "KeyValueProperties::populateInstance(): buffer too small.");
			}

			// Add the entry to the keyValueMap
			keyValueMap.insert(KeyValueMapEntry(key, value));
		}

		return totalSize;
	}

} // namespace Myoushu

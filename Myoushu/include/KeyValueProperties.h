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
 * @file KeyValueProperties.h
 * @author ME Chamberlain
 * @date October 2008
 */

#ifndef MYOUSHU_KEY_VALUE_PROPERTIES_H
#define MYOUSHU_KEY_VALUE_PROPERTIES_H

#include <map>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Value.h"
#include "Exception.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * A simple hash based implementation of a key value set. Values are wrapped in Value objects and keys are strings.
	 */
	class MYOUSHU_API KeyValueProperties : public Serializable
	{
		public:
			/** Type definition for the map type used in this class. */
			typedef std::map<std::string, Poco::AutoPtr<Value> > KeyValueMap;
			/** Type definition for the entries in the KeyValueMap. */
			typedef std::pair<std::string, Poco::AutoPtr<Value> > KeyValueMapEntry;
			/** Type definition for the standard iterator over the key value map. */
			typedef KeyValueMap::iterator KeyValueMapIterator;
			/** Type definition for the constant iterator over the key value map. */
			typedef KeyValueMap::const_iterator KeyValueMapConstIterator;

			/** Nullary Constructor. */
			KeyValueProperties();

			/** Destructor */
			virtual ~KeyValueProperties();

			/** Clears the map of keys to Values. */
			void clear();

			/** Get the beginning iterator over the map of keys to Value instances. */
			KeyValueMapIterator getBeginIterator();

			/** Get the end iterator over the map of keys to Value instances. */
			KeyValueMapIterator getEndIterator();

			/** Get the beginning iterator over the map of keys to Value instances. */
			KeyValueMapConstIterator getBeginConstIterator() const;

			/** Get the end iterator over the map of keys to Value instances. */
			KeyValueMapConstIterator getEndConstIterator() const;

			/**
			 * Insert a key value pair into the map.
			 * @param key The key of the Value to insert.
			 * @param value The Value instance to insert. This object takes ownership of the pointer
			 *				and will free it when appropriate.
			 * @throws Exception::E_NULL_POINTER if value is NULL.
			 */
			void insert(const std::string& key, Value *value) throw (Exception);

			/**
			 * Removes an entry from the map.
			 * @param key The key of the entry to remove.
			 * @return The Value instance mapped to the key. This object releases ownership of 
			 *		   the Value instance and the user must free it.
			 *		   If the key is not in the map NULL is returned.
			 */
			Value* removeAndGetValue(const std::string& key);

			/**
			 * Removes an entry from the map.
			 * @param key The key of the entry to remove.
			 * @return True if the key is found in the map and the Value was removed, false otherwise.
			 */
			bool remove(const std::string& key);

			/**
			 * Gets the Value instance mapped to the specified key.
			 * @param key The key of the entry to find.
			 * @return The Value instance mapped to the specified key, or NULL if the key is not in the map.
			 */
			Value* get(const std::string& key);

			/**
			 * Gets the Value instance mapped to the specified key.
			 * @param key The key of the entry to find.
			 * @return The Value instance mapped to the specified key, or NULL if the key is not in the map.
			 */
			const Value* get(const std::string& key) const;

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialized data (in bytes).
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception);

			/**
			 * Populates this instance with the serialized description read from the specified buffer.
			 * @param pMem The buffer to read the instance description from.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the data read (in bytes).
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The map of keys to values. */
			KeyValueMap keyValueMap;
	};

	// inlines
	inline KeyValueProperties::KeyValueMapIterator KeyValueProperties::getBeginIterator()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return keyValueMap.begin();
	}

	inline KeyValueProperties::KeyValueMapIterator KeyValueProperties::getEndIterator()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return keyValueMap.end();
	}

	inline KeyValueProperties::KeyValueMapConstIterator KeyValueProperties::getBeginConstIterator() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return keyValueMap.begin();
	}

	inline KeyValueProperties::KeyValueMapConstIterator KeyValueProperties::getEndConstIterator() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return keyValueMap.end();
	}
} // namespace Myoushu

#endif

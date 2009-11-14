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
 * @file GameLogEntity.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "GameLogEntity.h"
#include "EngineLog.h"

namespace Myoushu
{
	CLASS_NAME(GameLogEntity, "Myoushu::GameLogEntity");

	GameLogEntity::GameLogEntity(const std::string& name) : NamedInstance(name)
	{
	}

	GameLogEntity::GameLogEntity(const std::string& name, const GameLogEntityEntry::AttributeNamesVector& attributeNames) : NamedInstance(name)
	{
		GameLogEntityEntry::AttributeNamesVector::const_iterator iter;

		for (iter = attributeNames.begin(); iter != attributeNames.end(); ++iter)
		{
			mAttributeNames.push_back(*iter);
		}
	}

	GameLogEntity::~GameLogEntity()
	{
	}

	void GameLogEntity::addAttributeToPrimaryKey(const std::string& attributeName) throw (Exception)
	{
		// We do not support changing the primary key if there are already entries in memory.
		if (!mEntries.empty())
		{
			throw Exception(Exception::E_UNIMPLEMENTED, "GameLogEntity::addAttributeToPrimaryKey(): no support for changing the primary key if there are already entries in the entity.");
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		mKeyAttributes.push_back(attributeName);
	}

	void GameLogEntity::addEntry(GameLogEntityEntry *pEntry) throw (Exception)
	{
		// Ensure that pEntry is not NULL
		if (pEntry == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameLogEntity::addEntry(): pEntry is NULL.");
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		mEntries[getPrimaryKeyFromEntry(pEntry)] = pEntry;
	}

	GameLogEntityEntry* GameLogEntity::addEntry(const std::list<Value>& values)
	{
		GameLogEntityEntry pEntry(mAttributeNames);
		GameLogEntityEntry *pNewEntry;
		GameLogEntity::Iterator existEntryIter;
		std::list<Value>::const_iterator iter;
		unsigned int index;

		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that the values list contains the correct number of values
		if (values.size() != mAttributeNames.size())
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "GameLogEntity::addEntry(): incorrect number of values.");
		}

		// Populate the entry
		index = 0;
		for (iter = values.begin(); iter != values.end(); ++iter)
		{
			pEntry.setValue(index, *iter);
			index++;
		}

		// Add the entry to the map of entries. It is stored in an AutoPtr container
		// which means that it will be memory managed by reference counting.
		existEntryIter = mEntries.find(getPrimaryKeyFromEntry(&pEntry));
		if (existEntryIter == mEntries.end())
		{
			pNewEntry = new GameLogEntityEntry(mAttributeNames);
			(*pNewEntry) = pEntry;
			mEntries[getPrimaryKeyFromEntry(&pEntry)] = pNewEntry;
		}
		else
		{
			*(existEntryIter->second) = pEntry;
			pNewEntry = existEntryIter->second;
		}

		// Return the new entry
		return pNewEntry;
	}

	const GameLogEntityEntry* GameLogEntity::getEntry(const std::string& primaryKey)
	{
		KeyEntryMap::const_iterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		iter = mEntries.find(primaryKey);
		if (iter == mEntries.end())
		{
			return NULL;
		}

		return iter->second;
	}

	const GameLogEntityEntry* GameLogEntity::getEntry(const std::list<std::string>& primaryKey)
	{
		KeyEntryMap::const_iterator entryIter;
		std::list<std::string>::const_iterator keyIter;
		std::string key;

		for (keyIter = primaryKey.begin(); keyIter != primaryKey.end(); ++keyIter)
		{
			key += *keyIter;
		}

		Poco::ScopedRWLock lock(mRWLock, false);

		entryIter = mEntries.find(key);
		if (entryIter == mEntries.end())
		{
			return NULL;
		}

		return entryIter->second;
	}

	std::string GameLogEntity::getPrimaryKeyFromEntry(GameLogEntityEntry *pEntry) throw (Exception)
	{
		std::list<std::string>::const_iterator iter;
		std::string key;

		// Check that pEntry is not NULL
		if (pEntry == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameLogEntity::getPrimaryKeyFromEntry(): pEntry is NULL.");
		}

		for (iter = mKeyAttributes.begin(); iter != mKeyAttributes.end(); ++iter)
		{
			key += pEntry->getValue(*iter).toString();
		}

		return key;
	}

	void GameLogEntity::getPrimaryKeys(std::vector<std::string>& primaryKeysVector)
	{
		ConstIterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		primaryKeysVector.clear();
		for (iter = begin(); iter != end(); ++iter)
		{
			primaryKeysVector.push_back(iter->first);
		}
	}

} // namespace Myoushu

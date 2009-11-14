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
 * @file GameLogEntityEntry.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "GameLogEntityEntry.h"
#include "EngineLog.h"

namespace Myoushu
{
	GameLogEntityEntry::GameLogEntityEntry(const AttributeNamesVector& attributeNames)
	{
		AttributeNamesVector::const_iterator iter;
		unsigned int i;

		Poco::ScopedRWLock lock(mRWLock, true);

		// Setup the vector of attribute names and the map of indices to attribute names.
		i = 0;
		for (iter = attributeNames.begin(); iter != attributeNames.end(); ++iter)
		{
			mAttributeNames.push_back(*iter);
			mAttributeIndexMap[*iter] = i;
			i++;
		}
		
		mEntry.resize(i);
		mChanged = false;
	}

	GameLogEntityEntry::~GameLogEntityEntry()
	{
	}

	std::string GameLogEntityEntry::getAttributeName(unsigned int index) const throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that the index is not out of bounds
		if (index >= mAttributeNames.size())
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry::getAttributeName(): index out of bounds");
		}

		return mAttributeNames[index];
	}

	void GameLogEntityEntry::setValue(const std::string& attributeName, const Value& value) throw (Exception)
	{
		AttributeIndexMap::iterator iter;
		unsigned int index;

		Poco::ScopedRWLock lock(mRWLock, true);

		// Check that the attribute name is valid
		iter = mAttributeIndexMap.find(attributeName);
		if (iter == mAttributeIndexMap.end())
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry()::setValue(): attribute " + attributeName + " is invalid.");
		}

		index = iter->second;
		// Set the value
		mEntry[index] = value;

		mChanged = true;
	}

	void GameLogEntityEntry::setValue(unsigned int index, const Value& value) throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		// Check that the index is not out of bounds
		if (index >= mAttributeNames.size())
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry::setValue(): index out of bounds");
		}

		// Set the value
		mEntry[index] = value;

		mChanged = true;
	}

	Value GameLogEntityEntry::getValue(const std::string& attributeName) const throw (Exception)
	{
		AttributeIndexMap::const_iterator iter;
		unsigned int index;

		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that the attribute name is valid
		iter = mAttributeIndexMap.find(attributeName);
		if (iter == mAttributeIndexMap.end())
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry()::getValue(): attribute " + attributeName + " is invalid.");
		}

		index = iter->second;
		if (index >= mEntry.size())
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry()::getValue(): index out of bounds.");
		}

		// Get the value
		return mEntry[index];
	}

	Value GameLogEntityEntry::getValue(unsigned int index) const throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Check that the index is not out of bounds
		if ((index >= mAttributeNames.size()) || (index >= mEntry.size()))
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "GameLogEntityEntry::setValue(): index out of bounds");
		}

		// Get the value
		return mEntry[index];
	}

	GameLogEntityEntry& GameLogEntityEntry::operator=(const GameLogEntityEntry& rhs)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mAttributeNames.clear();
		mAttributeIndexMap.clear();
		mEntry.clear();

		mAttributeNames = rhs.mAttributeNames;
		mAttributeIndexMap = rhs.mAttributeIndexMap;
		mEntry = rhs.mEntry;
		mChanged = true;

		return *this;
	}

} // namespace Myoushu

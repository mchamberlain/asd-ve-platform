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
 * @file GameLogEntityEntry.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_GAME_LOG_ENTITY_ENTRY
#define MYOUSHU_GAME_LOG_ENTITY_ENTRY

#include <string>
#include <list>
#include <map>
#include <vector>

#include "Poco/RefCountedObject.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "Exception.h"
#include "Value.h"

namespace Myoushu
{
	/**
	 * An entry in a GameLogEntityEntry. Analagous to a row in a table in a relational database.
	 */
	class MYOUSHU_API GameLogEntityEntry : public Poco::RefCountedObject
	{
		public:
			/** A typedef of a vector of strings that is used as the datastructure to store attribute names. */
			typedef std::vector<std::string> AttributeNamesVector;
			/** A typedef of a map of strings to indices. */
			typedef std::map<std::string, unsigned int> AttributeIndexMap;	
			/** A typedef of a vector of Value instances. */
			typedef std::vector<Value> ValueVector;

			/**
			 * Constructor.
			 * @param attributeNames The names of this attributes that can be stored in this entry.
			 */
			GameLogEntityEntry(const AttributeNamesVector& attributeNames);

			/** Destructor */
			virtual ~GameLogEntityEntry();

			/** Gets the attribute names. */
			std::vector<std::string> getAttributeNames() const;

			/**
			 * Gets the attribute name at the specified index.
			 * @param index The index of the attribute name to get.
			 * @return The attribute name at the specified index.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the index is out of bounds.
			 */
			std::string getAttributeName(unsigned int index) const throw (Exception);

			/** Gets the number of attributes stored in this entry. */
			unsigned int getNumberOfAttributes() const;

			/**
			 * Sets the value stored at this attribute.
			 * @param attributeName The name of the attribute to set a value for.
			 * @param value The value to set at the specified attribute.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the specified attribute name is invalid.
			 */
			void setValue(const std::string& attributeName, const Value& value) throw (Exception);

			/**
			 * Sets the value stored at this attribute.
			 * @param index The index of the attribute to set a value for.
			 * @param value The value to set at the specified attribute.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the specified index is out of bounds.
			 */
			void setValue(unsigned int index, const Value& value) throw (Exception);

			/** 
			 * Gets the value stored at this attribute. 
			 * @param attributeName The name of the attribute to set a value for.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the specified attribute name is invalid.
			 */
			Value getValue(const std::string& attributeName) const throw (Exception);

			/** 
			 * Gets the value stored at this attribute.
			 * @param index The index of the attribute to set a value for.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the specified index is out of bounds.
			 */
			Value getValue(unsigned int index) const throw (Exception);

			/** Gets the changed flag, indicating whether this entry has been changed since the last commit. */
			bool getChanged() const;

			/**
			 * Sets the changed flag, indicating that this entry has been changed and should be included
			 * in the next commit. It is not neccesary to use this method, the instance will automatically
			 * set this flag to true when changes are made.
			 */
			void setChanged(bool changed);

			/** Sets the content of this entry equal to the content in rhs. */
			GameLogEntityEntry& operator=(const GameLogEntityEntry& rhs);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The names of the attributes. */
			AttributeNamesVector mAttributeNames;
			/** A map of attribute strings to their indices. */
			AttributeIndexMap mAttributeIndexMap;
			/** A vector of values. */
			ValueVector mEntry;
			/** A flag that indicates whether this entry has been changed. */
			bool mChanged;

	}; //class GameLogEnttiyAttribute

	// inlines
	inline std::vector<std::string> GameLogEntityEntry::getAttributeNames() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAttributeNames;
	}

	inline unsigned int GameLogEntityEntry::getNumberOfAttributes() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAttributeNames.size();
	}

	inline bool GameLogEntityEntry::getChanged() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mChanged;
	}

	inline void GameLogEntityEntry::setChanged(bool changed)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mChanged = changed;
	}

} // namespace Myoushu

#endif

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
 * @file GameLogEntity.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_GAME_LOG_ENTITY
#define MYOUSHU_GAME_LOG_ENTITY

#include <string>
#include <map>
#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "NamedObject.h"
#include "NamedInstance.h"
#include "GameLogEntityEntry.h"

namespace Myoushu
{
	/**
	 * Base class of an entity in the data capturing system. Analagous to a table in a relational database. It contains a number of
	 * GameLogEntityEntry instances as rows.
	 */
	class MYOUSHU_API GameLogEntity : public NamedInstance, public NamedObject<GameLogEntity>, public Poco::RefCountedObject
	{
		public:
			typedef std::map<std::string, Poco::AutoPtr<GameLogEntityEntry> > KeyEntryMap;

			typedef KeyEntryMap::iterator Iterator;

			typedef KeyEntryMap::const_iterator ConstIterator;

			/**
			 * Constructor.
			 * @param name The name of this entity.
			 */
			GameLogEntity(const std::string& name = "GameLogEntity");

			/**
			 * Constructor.
			 * @param name The name of this entity.
			 * @param attributeNames The names of the different attributes that can be stored in an entry
			 *						 in this entity.
			 */
			GameLogEntity(const std::string& name, const GameLogEntityEntry::AttributeNamesVector& attributeNames);

			/** Destructor */
			virtual ~GameLogEntity();

			CLASS_NAME_FUNCTIONS(GameLogEntity);

			/**
			 * Adds an attribute to the list of attributes that constitute the primary key of
			 * an entry in this entity.
			 * @param attributeName The attribute name to add to the primary key.
			 * @throws Exception::E_INDEX_OUT_OF_BOUNDS if the attributeName is invalid.
			 * @throws Exception::E_UNIMPLEMENTED if there are already data loaded into this entity.
			 */
			void addAttributeToPrimaryKey(const std::string& attributeName) throw (Exception);

			/**
			 * Adds a new entry to this entity. This instance takes ownership of the GameLogEntityEntry instance
			 * and will destroy it when appropriate.
			 * @param pEntry Pointer to a GameLogEntityEntry instance to add to this entity.
			 * @throws Exception::E_NULL_POINTER if pEntry is NULL.
			 */
			void addEntry(GameLogEntityEntry *pEntry) throw (Exception);

			/**
			 * Creates and returns a new, GameLogEntityEntry instance set with the specified values.
			 * The instance is managed by this GameLogEntity instance and will be destroyed when appropriate.
			 * @param values A list of values to initialise the attributes in the entry to. Every value
			 *				 must be specified.
			 * @return The newly created and initialised GameLogEntityEntry instance.
			 * @throws Exception::E_INVALID_PARAMETERS if there are not enough or too many entries
			 *										   in values.
			 */
			GameLogEntityEntry* addEntry(const std::list<Value>& values);

			/**
			 * Gets an entry, that is currently in memory, by its primary key.
			 * This method will not fetch entries from disc or other storage, for that
			 * use the read* functions.
			 * @param primaryKey The primary key of the entry, as a string. That is: the concatenation
			 *					 of the string representation of the values/attributes that constitute
			 *					 the key for this entry.
			 * @return The GameLogEntityEntry instance that corresponds to the primaryKey, or NULL if no
			 *		   such instance could be found.
			 */
			const GameLogEntityEntry* getEntry(const std::string& primaryKey);

			/**
			 * Gets an entry, that is currently in memory, by its primary key.
			 * This method will not fetch entries from disc or other storage, for that
			 * use the read* functions.
			 * @param primaryKey The primary key of the entry, as a list of strings. That is: 
			 *					 the string representations of the values/attributes that constitute
			 *					 the key for this entry.
			 * @return The GameLogEntityEntry instance that corresponds to the primaryKey, or NULL if no
			 *		   such instance could be found.
			 */
			const GameLogEntityEntry* getEntry(const std::list<std::string>& primaryKey);

			/** 
			 * Constructs the string representation of the primary key of an entry.
			 * @param pEntry The GameLogEntityEntry instance to construct the key for.
			 * @throws Exception::E_NULL_POINTER if pEntry is NULL.
			 */
			std::string getPrimaryKeyFromEntry(GameLogEntityEntry *pEntry) throw (Exception);

			/** Gets a vector of strings containing the attribute names for this entity. */
			GameLogEntityEntry::AttributeNamesVector getAttributeNames() const;

			/** Gets the const_iterator to the first GameLogEntityEntry in this entity. */
			ConstIterator begin() const;

			/** Gets the const_iterator to just past the last GameLogEntityEntry in this entity. */
			ConstIterator end() const;

			/** Gets the iterator to the first GameLogEntityEntry in this entity. */
			Iterator begin();

			/** Gets the iterator to just past the last GameLogEntityEntry in this entity. */
			Iterator end();

			/** Gets a const_iteartor to the first attribute name of this entity. */
			GameLogEntityEntry::AttributeNamesVector::const_iterator attributeNamesBegin() const;

			/** Gets a const_iterator to just past the last attribute name of this entity. */
			GameLogEntityEntry::AttributeNamesVector::const_iterator attributeNamesEnd() const;

			/** Gets a const_iteartor to the first primary key attribute name of this entity. */
			std::list<std::string>::const_iterator keyAttributesBegin() const;

			/** Gets a const_iterator to just past the last primary key attribute name of this entity. */
			std::list<std::string>::const_iterator keyAttributesEnd() const;

			/** Populates the supplied vector with all of the primary keys of entries that are in memory. */
			void getPrimaryKeys(std::vector<std::string>& primaryKeysVector);

			/**
			 * Reads an entry from a secondary storage source into memory. This
			 * is a pure virtual function, deriving classes need to implement this
			 * function, if applicable.  Depending on the type of secondary storage used
			 * read requests might not be completed immediately. The checkRead() function must be used, with
			 * the read ID returned from this function, to check whehter the read completed successfully.
			 * From there the getEntry() functions can be used to get the entry.
			 * @param primaryKey The primary key of the entry, as a list of strings. That is: 
			 *					 the string representations of the values/attributes that constitute
			 *					 the key for this entry.
			 * @return A unique read ID for this read request.
			 */
			virtual memUInt readEntry(const std::list<std::string>& primaryKey) = 0;

			/**
			 * This function checks whether the read opertion for the specified read ID
			 * has completed. If it has completed, the function returns true and the getEntry() functions
			 * can be used to get the entry. This is a pure virtual function, deriving classes need to
			 * implement this function, if applicable.
			 */
			virtual bool checkRead(memUInt readID) = 0;

			/**
			 * Commit all GameLogEntityEntry instances, that have their changed flags set to true, to
			 * secondary storage. Depending on the implementation this function might return before the
			 * commit is complete: the checkCommit() function must be used to check whether the previous
			 * commit operation has completed. This is a pure virtual function, deriving classes need to
			 * implement this function, if applicable.
			 */
			virtual void commit() = 0;

			/**
			 * This function checks whether the previous commit operation has completed. This is a pure 
			 * virtual function, deriving classes need to implement this function, if applicable.
			 */
			virtual bool checkCommit() = 0;

			/**
			 * This method reads updated information, for all entries currently in memory, from secondary storage.
			 * This is a pure virtual function, deriving classes need to implement this function, if applicable.
			 * Depending on the implementation, this function could return before the operation completes: the update
			 * could be scheduled to happen in a separate thread or at some later stage. The checkUpdate() function
			 * must be used to check whether the update operation has completed.
			 * @param overwrite If the overwrite flag is true, entries that have their changed flags set to true,
			 *					will be overwritten with the version currently on secondary storage, losing any
			 *					possible changes that have been made.
			 */
			virtual void update(bool overwrite = false) = 0;

			/**
			 * This function checks whether the previous update operation has completed. This is a pure 
			 * virtual function, deriving classes need to implement this function, if applicable.
			 */
			virtual bool checkUpdate() = 0;

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** Map of string-based keys to GameLogEntityEntries. */
			KeyEntryMap mEntries;
			/** The names of the different attributes that could be stored in an entry in this entity. */
			GameLogEntityEntry::AttributeNamesVector mAttributeNames;
			/** The list of attribute names that make-up the primary key of an entry. */
			std::list<std::string> mKeyAttributes;

	}; // class GameLogEntity

	// inlines
	inline GameLogEntityEntry::AttributeNamesVector GameLogEntity::getAttributeNames() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAttributeNames;
	}

	inline GameLogEntity::ConstIterator GameLogEntity::begin() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntries.begin();
	}

	inline GameLogEntity::ConstIterator GameLogEntity::end() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntries.end();
	}

	inline GameLogEntity::Iterator GameLogEntity::begin()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntries.begin();
	}

	inline GameLogEntity::Iterator GameLogEntity::end()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mEntries.end();
	}

	inline GameLogEntityEntry::AttributeNamesVector::const_iterator GameLogEntity::attributeNamesBegin() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAttributeNames.begin();
	}

	inline GameLogEntityEntry::AttributeNamesVector::const_iterator GameLogEntity::attributeNamesEnd() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAttributeNames.end();
	}

	inline std::list<std::string>::const_iterator GameLogEntity::keyAttributesBegin() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mKeyAttributes.begin();
	}

	inline std::list<std::string>::const_iterator GameLogEntity::keyAttributesEnd() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mKeyAttributes.end();
	}

} // namespace Myoushu

#endif

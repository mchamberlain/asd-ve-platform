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
 * @file SQLiteGameLogEntity.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_SQLITE_GAME_LOG_ENTITY_H
#define MYOUSHU_SQLITE_GAME_LOG_ENTITY_H

#include "GameLogEntity.h"

namespace Myoushu
{
	/**
	 * An implementation of the GameLogEntity class using SQLite for storage. Delayed read and write operations are used.
	 */
	class MYOUSHU_API SQLiteGameLogEntity : public GameLogEntity, public NamedObject<SQLiteGameLogEntity>
	{
		public:
			/**
			 * Constructor.
			 * @param name The name of this entity.
			 */
			SQLiteGameLogEntity(const std::string& name = "SQLiteGameLogEntity");

			/**
			 * Constructor.
			 * @param name The name of this entity.
			 * @param attributeNames The names of the different attributes that can be stored in an entry
			 *						 in this entity.
			 */
			SQLiteGameLogEntity(const std::string& name, const GameLogEntityEntry::AttributeNamesVector& attributeNames);

			/** Destructor */
			virtual ~SQLiteGameLogEntity();

			CLASS_NAME_FUNCTIONS(SQLiteGameLogEntity);

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
			virtual memUInt readEntry(const std::list<std::string>& primaryKey);

			/**
			 * This function checks whether the read opertion for the specified read ID
			 * has completed. If it has completed, the function returns true and the getEntry() functions
			 * can be used to get the entry. This is a pure virtual function, deriving classes need to
			 * implement this function, if applicable.
			 */
			virtual bool checkRead(memUInt readID);

			/**
			 * This function is called to inform this entity that an entry has been read from from secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void readCompleted(memUInt readID);

			/**
			 * Commit all GameLogEntityEntry instances, that have their changed flags set to true, to
			 * secondary storage. Depending on the implementation this function might return before the
			 * commit is complete: the checkCommit() function must be used to check whether the previous
			 * commit operation has completed. This is a pure virtual function, deriving classes need to
			 * implement this function, if applicable.
			 */
			virtual void commit();

			/**
			 * This function checks whether the previous commit operation has completed. This is a pure 
			 * virtual function, deriving classes need to implement this function, if applicable.
			 */
			virtual bool checkCommit();

			/**
			 * This function is called to inform this entity that it has been committed to secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void commitCompleted();

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
			virtual void update(bool overwrite = false);

			/**
			 * This function checks whether the previous update operation has completed. This is a pure 
			 * virtual function, deriving classes need to implement this function, if applicable.
			 */
			virtual bool checkUpdate();

			/**
			 * This function is called to inform this entity that it has been updated from secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void updateCompleted();

		protected:
			/** A map of read IDs to names of entities that is to be read from secondary storage. */
			std::map<memUInt, std::string> mPendingReadIDToName;
			/** A map of names of entities, that is to be read from secondary storage, to read IDs. */
			std::map<std::string, memUInt> mPendingNameToReadID;
			/** The last assigned read ID. */
			memUInt mLastAssignedReadID;
			/** A flag indicating whether a commit should be performed. */
			bool mCommitPending;
			/** A flag indiciating whether an update should be performed. */
			bool mUpdatePending;

	}; // class SQLiteGameLogEntity
} // namespace Myoushu

#endif

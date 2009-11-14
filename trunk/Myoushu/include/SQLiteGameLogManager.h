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
 * @file SQLiteGameLogManager.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_SQLITE_GAME_LOG_MANAGER
#define MYOUSHU_SQLITE_GAME_LOG_MANAGER

#include "GameLogManager.h"
#include "Singleton.h"

namespace Myoushu
{
	/**
	 * An implementation of the GameLogManager class using SQLite for storage. Delayed read and write operations are used.
	 */
	class MYOUSHU_API SQLiteGameLogManager : public GameLogManager, public Ogre::Singleton<SQLiteGameLogManager>
	{
		public:
			/** Nullary Constructor. */
			SQLiteGameLogManager();

			/** Destructor. */
			virtual ~SQLiteGameLogManager();

			/** 
			 * Create an instance using with specified name. Extending classes can change
			 * the return type of this function to an appropriate type.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 */
			virtual GameLogEntity* make(const std::string& name);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual GameLogEntity* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Creates a new GameLogEntity instance that is managed by this manager. This is a factory method.
			 * @param name The name of the entity.
			 * @param attributeNames The names of the atributes that will be stored in entries in this entity.
			 */
			virtual GameLogEntity* makeEntity(const std::string& name, std::vector<std::string> attributeNames);

			/*
			 * If an entity is not in memory, i.e. getEntity returns NULL, but it
			 * is on the secondary storage backing this logging system, this function
			 * fethces it from the secondary storage. Due to implementation specifics and threading
			 * this function might return before the entity has been fetched. The read ID returned
			 * by this function must be used with the checkRead() to test whether the entity has been
			 * read into memory. This is a pure virtual function, and must be implemented by deriving
			 * classes.
			 * @param name The name of the entity to fetch from secondary storage.
			 */
			virtual memUInt readEntity(const std::string& name);

			/**
			 * Checks whether a previous readEntry operation, specified by the readID value, has completed.
			 * This is a pure virtual function that must be implemented by deriving classes.
			 * @param readID The ID returned by the readEntity() call.
			 * @return true if the read operation completed, false otherwise.
			 */
			virtual bool checkRead(memUInt readID) const;

			/**
			 * This function is called to inform this entity that an entry has been read from from secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void readCompleted(memUInt readID);

			/**
			 * Commits any changes to the GameLogEntities and their entries in memory to secondary storage.
			 * Due to implementation specifics and threading this function might return before the commit
			 * operation is completed or even started. The checkCommit() function must be used to test 
			 * whether the commit operation has completed. This is a pure virtual function, and must
			 * be implemented by deriving classes.
			 */
			virtual void commit();

			/**
			 * Checks whether the previous commit operation has been completed. See commit(). This is a 
			 * pure virtual function, and must be implemented by deriving classes.
			 * @return true if the commit operation completed, false otherwise.
			 */
			virtual bool checkCommit();

			/**
			 * This function is called to inform this entity that it has been committed to secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void commitCompleted();

			/**
			 * The update function reads the current state of the entities that are in memory, from secondary
			 * storage, overwriting any changes that might have been made to the objects that are in memory.
			 * Due to implementation specifics and threading this function might return before the update
			 * operation is completed or even started. The checkUpdate() function must be used to test 
			 * whether the update operation has completed. This is a pure virtual function, and must
			 * be implemented by deriving classes.
			 */
			virtual void update();

			/**
			 * Checks whether the previous update operation has been completed. See update(). This is a 
			 * pure virtual function, and must be implemented by deriving classes.
			 * @return true if the update operation completed, false otherwise.
			 */
			virtual bool checkUpdate();

			/**
			 * This function is called to inform this entity that it has been updated from secondary storage. This
			 * should not be called by users, it is called internally.
			 */
			void updateCompleted();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
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

	}; // class SQLiteGameLogManager
} // namespace Myoushu

#endif

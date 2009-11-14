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
 * @file GameLogManager.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_GAME_LOG_MANAGER
#define MYOUSHU_GAME_LOG_MANAGER

#include <vector>
#include <map>

#include "Poco/RWLock.h"

#include "Platform.h"
#include "NamedObjectFactory.h"
#include "GameLogEntity.h"

namespace Myoushu
{
	/**
	 * Base class of a manager class for the data capturing system.
	 */
	class MYOUSHU_API GameLogManager : public NamedObjectFactory<GameLogEntity>
	{
		public:
			/** Constructor. */
			GameLogManager();

			/** Destructor. */
			virtual ~GameLogManager();

			/** 
			 * Adds an existing entity to the manager. The manager takes ownership of the entity
			 * and will destroy it when appropriate.
			 * @param pEntity The entity to add.
			 * @throws Exception:E_NULL_POINTER if pEntity is NULL.
			 */
			void addEntity(GameLogEntity *pEntity) throw (Exception);

			/**
			 * Creates a new GameLogEntity instance that is managed by this manager. This is a factory method.
			 * @param name The name of the entity.
			 * @param attributeNames The names of the atributes that will be stored in entries in this entity.
			 */
			virtual GameLogEntity* makeEntity(const std::string& name, std::vector<std::string> attributeNames) = 0;

			/**
			 * Gets an entity by its name
			 * @param name The name of the entity to find.
			 * @return The GameLogEntity instance with the specified name, or NULL otherwise.
			 */
			GameLogEntity* getEntity(const std::string& name);

			/**
			 * If an entity is not in memory, i.e. getEntity returns NULL, but it
			 * is on the secondary storage backing this logging system, this function
			 * fethces it from the secondary storage. Due to implementation specifics and threading
			 * this function might return before the entity has been fetched. The read ID returned
			 * by this function must be used with the checkRead() to test whether the entity has been
			 * read into memory. This is a pure virtual function, and must be implemented by deriving
			 * classes.
			 * @param name The name of the entity to fetch from secondary storage.
			 */
			virtual memUInt readEntity(const std::string& name) = 0;

			/**
			 * Checks whether a previous readEntry operation, specified by the readID value, has completed.
			 * This is a pure virtual function that must be implemented by deriving classes.
			 * @param readID The ID returned by the readEntity() call.
			 * @return true if the read operation completed, false otherwise.
			 */
			virtual bool checkRead(memUInt readID) const = 0;

			/**
			 * Commits any changes to the GameLogEntities and their entries in memory to secondary storage.
			 * Due to implementation specifics and threading this function might return before the commit
			 * operation is completed or even started. The checkCommit() function must be used to test 
			 * whether the commit operation has completed. This is a pure virtual function, and must
			 * be implemented by deriving classes.
			 */
			virtual void commit() = 0;

			/**
			 * Checks whether the previous commit operation has been completed. See commit(). This is a 
			 * pure virtual function, and must be implemented by deriving classes.
			 * @return true if the commit operation completed, false otherwise.
			 */
			virtual bool checkCommit() = 0;

			/**
			 * The update function reads the current state of the entities that are in memory, from secondary
			 * storage, overwriting any changes that might have been made to the objects that are in memory.
			 * Due to implementation specifics and threading this function might return before the update
			 * operation is completed or even started. The checkUpdate() function must be used to test 
			 * whether the update operation has completed. This is a pure virtual function, and must
			 * be implemented by deriving classes.
			 */
			virtual void update() = 0;

			/**
			 * Checks whether the previous update operation has been completed. See update(). This is a 
			 * pure virtual function, and must be implemented by deriving classes.
			 * @return true if the update operation completed, false otherwise.
			 */
			virtual bool checkUpdate() = 0;
	}; // class GameLogManager
} // namespace Myoushu

#endif

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
 * @file ReplayFactory.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_REPLAY_FACTORY_H
#define MYOUSHU_REPLAY_FACTORY_H

#include "Platform.h"
#include "NamedObjectFactory.h"
#include "Singleton.h"
#include "Replay.h"

namespace Myoushu
{
	/**
	 * A NamedObjectFactory implementation for creating Replay instances.
	 */
	class MYOUSHU_API ReplayFactory : public NamedObjectFactory<Replay>, public Ogre::Singleton<ReplayFactory>
	{
		public:
			/** Nullary Constructor. */
			ReplayFactory();

			/** Destructor. */
			virtual ~ReplayFactory();

			/**
			 * Find an object in this factory by name.
			 * @param name The name of the object to find.
			 * @return A pointer to the instance with the specified name,
			 *		   or NULL if no such instance could be found in this factory.
			 */
			virtual Replay* findByName(const Ogre::String& replayName);

			/** 
			 * Create an instance with specified name. If an instance with this name already exists,
			 * a new instance will be created by appending a number to the end of the specified name,
			 * or the existing instance will be returned, this behaviour depends on the ensureUniqueName flag.
			 * @param replayName The name for the instance to create.
			 * @return The newly created (or existing) instance.
			 */
			virtual Replay* make(const std::string& replayName);

			/** 
			 * Create an instance with specified name. If an instance with this name already exists,
			 * a new instance will be created by appending a number to the end of the specified name,
			 * or the existing instance will be returned, this behaviour depends on the ensureUniqueName flag.
			 * @param replayName The name for the instance to create.
			 * @param ensureUniqueName If true, if an instance with the same name already exists, a number will
			 *						   be appended to the name in order to create a new instance. If false, the
			 *						   existing instance will be returned, and no new instance will be created.
			 * @return The newly created (or existing) instance.
			 */
			virtual Replay* make(const std::string& replayName, bool ensureUniqueName);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual Replay* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Creates a new Replay instance and opens it for reading or writing depending on the parameters.
			 * @param replayName The name of the replay. This is also the file name. A .replay extension is
			 *					 automatically added. If a replay with this name already exists in the factory,
			 *					 the name will be changed to be unique and a new instance will be created.
			 * @param resourceGroup The Ogre resource group that contains the replay.
			 * @param openForWriting If false the Replay is opened for reading, otherwise it is opened for
			 *						 writing.
			 * @param overwrite When openForWriting is true, and this flag is true, if a file with the same
			 *					same name exists, it will be overwritten.
			 * @return The new Replay instance, ready for reading or writing (depending on the parameters specified).
			 */
			virtual Replay* make(const std::string& replayName, const std::string& resourceGroup, bool openForWrite, bool overwrite = true);


	}; // class ReplayFactory

	// inlines
	inline Replay* ReplayFactory::findByName(const Ogre::String& replayName)
	{
		return static_cast<Replay*>(NamedObjectFactory<Replay>::findByName(replayName));
	}

} // namespace Myoushu

#endif

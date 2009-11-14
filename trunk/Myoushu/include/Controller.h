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
 * @file Controller.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Ogre.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "NamedObject.h"
#include "NamedInstance.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * Abstract base class for a Controller. Controllers are registered with the ControllerTask upon creation.
	 * All active Controllers are updated in the update function of the ControllerTask.
	 */
	class MYOUSHU_API Controller : public NamedObject<Controller>, public NamedInstance, public Poco::RefCountedObject
	{
		public:
			/** 
			 * Constructor 
			 * @param name The name for this Controller.
			 */
			Controller(const Ogre::String& name);

			/** Destructor */
			virtual ~Controller();

			CLASS_NAME_FUNCTIONS(Controller);

			/**
			 * Disables or enables the Controller.
			 * @param enabled Flag indicating whether the Controller should be enabled or disabled.
			 */
			void setEnabled(bool enabled);

			/**
			 * Gets whether this Controller is enabled or not.
			 * @return true if this Controller is enabled, false otherwise.
			 */
			bool isEnabled();

			/**
			 * This method is called by the ControllerTask.
			 * @param timeDelta The time that has passed since the previous
			 *					update in mircoseconds.
			 */
			virtual void update(unsigned long timeDelta) = 0;

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
			/** Flag indicating whether this Controller is enabled. */
			bool enabled;
	};

	// inlines

	inline void Controller::setEnabled(bool enabled)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->enabled = enabled;
	}

	inline bool Controller::isEnabled()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return enabled;
	}

} // Myoushu

#endif

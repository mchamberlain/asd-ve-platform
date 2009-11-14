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
 * @file NamedInstance.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef NAMED_INSTANCE_H
#define NAMED_INSTANCE_H

#include <string>

#include "Poco/RWLock.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * This class provides an instantiated class with a name.
	 */
	class MYOUSHU_API NamedInstance : public NamedObject<NamedInstance>, public Serializable
	{
		public:
			/**
			 * Constructor.
			 * @param instanceName The name of the instance.
			 */
			NamedInstance(const std::string& instanceName);

			/** Destructor */
			~NamedInstance();

			CLASS_NAME_FUNCTIONS(NamedInstance);

			/**
			 * Gets the instance name.
			 * @return A std::string containing the instanceName field.
			 */
			std::string getName() const;

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
			/** Read/write mutex on instanceName. */
			mutable Poco::RWLock instanceNameRWLock;
			/** The name of the instance. */
			std::string instanceName;

			/**
			 * Sets the name of this instance. Names should be set with caution as some object factory methods rely on knowing
			 * the name of an instance, if the name changes and the entry in the factory was not updated it could cause problems.
			 */
			virtual void setName(const std::string& name);
	};

	//inlines
	inline std::string NamedInstance::getName() const
	{
		Poco::ScopedRWLock lock(instanceNameRWLock, false);

		return instanceName;
	}

	inline void NamedInstance::setName(const std::string& name)
	{
		Poco::ScopedRWLock lock(instanceNameRWLock, true);

		instanceName = name;
	}

} // Myoushu

#endif

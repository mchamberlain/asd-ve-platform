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
 * @file Message.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

#include "Poco/Notification.h"
#include "Poco/RefCountedObject.h"
#include "Poco/Net/IPAddress.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"
#include "Cloneable.h"
#include "PoolObject.h"
#include "PoolObjectReferenceCounter.h"
#include "Serializable.h"

namespace Myoushu
{
	/**
	 * The base class of all messages passed between objects in the engine.
	 *
	 * Classes that derive from Message should also derive from NamedObject.
	 */
	class MYOUSHU_API Message : public Cloneable, public NamedObject<Message>, public Poco::Notification, public PoolObject, public Serializable
	{
		public:
			/**
			 * Nullary Constructor.
			 */
			Message();

			/**
			 * Destructor.
			 */
			virtual ~Message();

			CLASS_NAME_FUNCTIONS(Message);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			virtual Message* clone() const = 0;

			/** Clone this instance into message. */
			Message& operator=(const Message& message);

			/** Gets the IP address of the host that created this message. */
			Poco::Net::IPAddress getCreator() const;

			/** Sets the mCreator field, the IP of the host that created this message. */
			void setCreator(const Poco::Net::IPAddress& creator);

			/** 
			 * Sets the mCreator field, the IP of the host that created this message.
			 * @param creatorIP The IP of the host that created this message, as a string.
			 * @return true if creatorIP is a valid IP address, false otherwise.
			 */
			bool setCreator(const std::string& creatorIP);

			/** 
			 * Clears or resets the fields of the Message instance. This method resets the mCreator field to the local IP. 
			 * It is crucial that classes that override the clear() function call Message::clear() in their version of clear().
			 */
			virtual void clear();

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialised data.
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

		private:
			/** The IP address of the host that created this message. */
			Poco::Net::IPAddress mCreator;
	};

	// inlines
	inline Poco::Net::IPAddress Message::getCreator() const
	{
		return mCreator;
	}

	inline void Message::setCreator(const Poco::Net::IPAddress& creator)
	{
		mCreator = creator;
	}

	inline bool Message::setCreator(const std::string& creatorIP)
	{
		return Poco::Net::IPAddress::tryParse(creatorIP, mCreator);
	}

} // Myoushu

#endif

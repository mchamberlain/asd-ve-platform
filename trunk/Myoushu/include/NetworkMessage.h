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
 * @file NetworkMessage.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef MYOUSHU_NETWORK_MESSAGE_H
#define MYOUSHU_NETWORK_MESSAGE_H

#include "Poco/Net/HostEntry.h"
#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Message.h"

namespace Myoushu
{
	/**
	 * A message used to communicate with the NetworkTransmitTask. This message can encapsulate other
	 * class instances or messages. The NetworkTransmitTask transmits NetworkMessages to connected peers.
	 * The NetworkListenTask will populate a NetworkMessage with a message received over the network.
	 */
	class MYOUSHU_API NetworkMessage : public Message, public NamedObject<NetworkMessage>
	{
		public:
			/** An enumeration of NetworkMessage types. */
			enum NetworkMessageType
			{
				/** A client wants to connect to a server */
				NM_CONNECT = 0,
				/** A client wants to disconnect from a server */
				NM_DISCONNECT,
				/** A server acknowledges and approves a client's connection. */
				NM_ACK_CONNECT,
				/** A general acknowledgement used to confirm that a message was recevied. */
				NM_ACK,
				/** One host pings another. */
				NM_PING,
				/** Response to a NM_PING message. */
				NM_PONG,
				/** A network message that encapsulates a serialized engine message (such as an InputMessage). */
				NM_ENCAPSULATED_MESSAGE,
				/** A message indicating the the included object must be created. */
				NM_CREATE_OBJECT,
				/** A message indicating the the included object must be destroyed. */
				NM_DESTROY_OBJECT,
				/** A message indicating the the named object must be updated with the included data. */
				NM_UPDATE_OBJECT,
				/** The message type is unknown. */
				NM_UNKNOWN
			};
	
			/** Constructor */
			NetworkMessage();

			/**
			 * Constructor.
			 * @param type The type of this NetworkMessage.
			 */
			NetworkMessage(NetworkMessageType type);

			/** Destructor. */
			virtual ~NetworkMessage();

			CLASS_NAME_FUNCTIONS(NetworkMessage);

			/**
			 * Sets the mType field.
			 * @param type The new NetworkMessageType for this instance.
			 */
			void setType(NetworkMessageType type);

			/** Gets the mType field. */
			NetworkMessageType getType() const;

			/** Sets the IP address of the destination host to send this message to. */
			void setDestination(Poco::Net::IPAddress destination);

			/** Gets the currently set IP address of the host to send this message to. */
			Poco::Net::IPAddress getDestination() const;

			/** Sets the IP address of the host where this message originated. */
			void setSource(Poco::Net::IPAddress source);

			/** Gets the currently set IP address of the host where this message originated. */
			Poco::Net::IPAddress getSource() const;

			/** Gets the currently set IP address of the host where this message originated, as string. */
			std::string getSourceAsString() const;

			/**
			 * Sets the encapsulated message. In this version of this method the encapsulatedMessage is memory managed by reference counting.
			 * @param encapsulatedMessage The Message instance to encapsulate in this NetworkMessage.
			 */
			void setEncapsulatedMessage(Poco::AutoPtr<Message> encapsulatedMessage);

			/**
			 * Sets the encapsulated message. This instance takes ownership of the encapsulated message instance and will
			 * delete it when appropriate.
			 * @param encapsulatedMessage The Message instance to encapsulate in this NetworkMessage.
			 */
			void setEncapsulatedMessage(Message *encapsulatedMessage);

			/** Gets the currently set encapsulated message. */
			Message* getEncapsulatedMessage();

			/** Sets the name of the object to be created, deleted or updated. */
			void setObjectName(const std::string objectName);

			/** Gets the name of the object to be created, deleted or updated. */
			std::string getObjectName() const;

			/** Sets the class name of the object to be created, deleted or updated. */
			void setObjectClassName(const std::string objectClassName);

			/** Gets the class name of the object to be cretaed, deleted or updated. */
			std::string getObjectClassName() const;

			/** 
			 * Sets the attached object used with the NM_*_OBJECT message types. This is the object
			 * associated with mObjectName and mObjectClassName. The NetworkMessage instance will serialize the object
			 * and attach it to the end of the NetworkMessage serialization. Receiving classes then use the mObjectName, mObjectClassName and
			 * serialization to reconstruct the object.
			 *
			 * This NetworkMessage instance does not take ownership of the object and will not free it.
			 * @param attachedObject The Serializable object to attach to this network message, if any.
			 */
			void setAttachedObject(Serializable *attachedObject);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(NetworkMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			NetworkMessage* clone() const;

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 */
			NetworkMessage& operator=(const NetworkMessage& message);

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

		protected:
			/** Read/write lock for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The type of this NetworkMessage */
			NetworkMessageType mType;
			/** IP Address of the source of this message. */
			Poco::Net::IPAddress mSource;
			/** IP Address of the host to send the message to. */
			Poco::Net::IPAddress mDestination;
			/** An encapsulated engine message, that will be serialized and transmitted along with this NetworkMessage. */
			Poco::AutoPtr<Message> mEncapsulatedMessage;
			/** The name of an object to be created, deleted or updated. */
			std::string mObjectName;
			/** The class name of the object to be created, deleted, or updated if applicable. */
			std::string mObjectClassName;
			/** The object referenced in mObjectName and mObjectClassName. The sender must attach the object to this NetworkMessage
			 * class. It will be serialized and added to the end of the NetworkMessage serialization during transmission. Receiving classes
			 * can then use this data to reconstruct the object.
			 */
			Serializable *pAttachedObject;
	};

	// inlines
	inline void NetworkMessage::setType(NetworkMessage::NetworkMessageType type)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mType = type;
	}

	inline NetworkMessage::NetworkMessageType NetworkMessage::getType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mType;
	}

	inline void NetworkMessage::setEncapsulatedMessage(Poco::AutoPtr<Message> encapsulatedMessage)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mEncapsulatedMessage = encapsulatedMessage;
	}

	inline void NetworkMessage::setEncapsulatedMessage(Message *encapsulatedMessage)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mEncapsulatedMessage = encapsulatedMessage;
	}

	inline Message* NetworkMessage::getEncapsulatedMessage()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mEncapsulatedMessage.get();
	}

	inline void NetworkMessage::setDestination(Poco::Net::IPAddress destination)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mDestination = destination;
	}

	inline Poco::Net::IPAddress NetworkMessage::getDestination() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mDestination;
	}

	inline void NetworkMessage::setSource(Poco::Net::IPAddress source)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mSource = source;
	}

	inline Poco::Net::IPAddress NetworkMessage::getSource() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSource;
	}

	inline std::string NetworkMessage::getSourceAsString() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSource.toString();
	}

	inline void NetworkMessage::setObjectName(const std::string objectName)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mObjectName = objectName;
	}

	inline std::string NetworkMessage::getObjectName() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mObjectName;
	}

	inline void NetworkMessage::setObjectClassName(const std::string objectClassName)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mObjectClassName = objectClassName;
	}

	inline std::string NetworkMessage::getObjectClassName() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mObjectClassName;
	}

	inline void NetworkMessage::setAttachedObject(Serializable *attachedObject)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		pAttachedObject = attachedObject;
	}

} // namespace Myoushu

#endif

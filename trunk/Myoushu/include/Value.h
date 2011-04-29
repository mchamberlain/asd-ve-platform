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
 * @file Value.h
 * @author ME Chamberlain
 * @date October 2008
 */

#ifndef MYOUSHU_VALUE_H
#define MYOUSHU_VALUE_H

#include <typeinfo>
#include <string>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"
#include "jni.h"

#include "Platform.h"
#include "NamedInstance.h"
#include "Serializable.h"
#include "Message.h"

namespace Myoushu
{
	/**
	 * A simple wrapper class to store one of various types of values.
	 */
	class MYOUSHU_API Value : public Poco::RefCountedObject, public Serializable
	{
		public:
			/** Enumeration that defines the type of the stored value. */
			enum ValueType
			{
				/** char type */
				VT_CHAR = 0,
				/** unsigned char type */
				VT_UCHAR,
				/** short type */
				VT_SHORT,
				/** unsigned short type */
				VT_USHORT,
				/** int type */
				VT_INT,
				/** unsigned int type */
				VT_UINT,
				/** long type */
				VT_LONG,
				/** unsigned long type */
				VT_ULONG,
				/** float type */
				VT_FLOAT,
				/** double type */
				VT_DOUBLE,
				/** string type */
				VT_STRING,
				/** Instance of NamedInstance */
				VT_NAMED_INSTANCE,
				/** void pointer type */
				VT_VOID_PTR,
				/** const Instance of NamedInstance */
				VT_CONST_NAMED_INSTANCE,
				VT_CONST_REF_COUNTED_OBJECT,
				VT_CONST_MESSAGE,
				/** const void pointer type */
				VT_CONST_VOID_PTR,
				/** JNI jvalue type. */
				VT_JVALUE,
				/** Unknown type */
				VT_UNKNOWN
			};

			/** This union is used to store the value in this instance. */
			typedef union ValuesUnion
			{
				char mChar;
				unsigned char mUChar;
				short mShort;
				unsigned short mUShort;
				int mInt;
				unsigned int mUInt;
				long mLong;
				unsigned long mULong;
				float mFloat;
				double mDouble;
				std::string *mString;
				NamedInstance *mNamedInstance;
				void *mVoidPtr;
				const NamedInstance *mConstNamedInstance;
				const Message *mConstMessage;
				const Poco::RefCountedObject *mConstRefCountedObj;
				const void *mConstVoidPtr;
				jvalue mJValue;
			};

			/** Nullary Constructor. */
			Value();

			/** Copy constructor. */
			Value(const Value& v);

			/** Destructor. */
			virtual ~Value();

			/** Clears any existing value set in this instance, must be called by all set() functions before a new value is set. */
			void clearValue();

			/**
			 * Stores a char value in this type. 
			 * @param value The char value to store in this instance.
			 */
			void set(char value);

			/**
			 * Stores an unsigned char value in this type. 
			 * @param value The unsigned char value to store in this instance.
			 */
			void set(unsigned char value);

			/**
			 * Stores a short value in this type. 
			 * @param value The short value to store in this instance.
			 */
			void set(short value);

			/**
			 * Stores a unsigned short value in this type. 
			 * @param value The unsigned short value to store in this instance.
			 */
			void set(unsigned short value);

			/**
			 * Stores a int value in this type. 
			 * @param value The int value to store in this instance.
			 */
			void set(int value);

			/**
			 * Stores an unsigned int value in this type. 
			 * @param value The unsigned int value to store in this instance.
			 */
			void set(unsigned int value);

			/**
			 * Stores a long value in this type. 
			 * @param value The long value to store in this instance.
			 */
			void set(long value);

			/**
			 * Stores a unsigned long value in this type. 
			 * @param value The unsigned long value to store in this instance.
			 */
			void set(unsigned long value);

			/**
			 * Stores a float value in this type. 
			 * @param value The float value to store in this instance.
			 */
			void set(float value);

			/**
			 * Stores a double value in this type. 
			 * @param value The double value to store in this instance.
			 */
			void set(double value);

			/**
			 * Stores a std::string value in this type. 
			 * @param value The std::string value to store in this instance.
			 */
			void set(const std::string& value);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(NamedInstance *value, bool autoPtr = false);

			/**
			 * Stores a void pointer in this type. 
			 * @param value The void pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(void *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(const NamedInstance *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(const Message *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(const Poco::RefCountedObject *value, bool autoPtr = false);

			/**
			 * Stores a void pointer in this type. 
			 * @param value The void pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void set(const void *value, bool autoPtr = false);

			/**
			 * Stores a jvalue in this type. 
			 * @param value The jvalue to store in this instance.
			 */
			void set(jvalue value);

			/**
			 * Stores a char value in this type. 
			 * @param value The char value to store in this instance.
			 */
			void setChar(char value);

			/**
			 * Stores an unsigned char value in this type. 
			 * @param value The unsigned char value to store in this instance.
			 */
			void setUChar(unsigned char value);

			/**
			 * Stores a short value in this type. 
			 * @param value The short value to store in this instance.
			 */
			void setShort(short value);

			/**
			 * Stores a unsigned short value in this type. 
			 * @param value The unsigned short value to store in this instance.
			 */
			void setUShort(unsigned short value);

			/**
			 * Stores a int value in this type. 
			 * @param value The int value to store in this instance.
			 */
			void setInt(int value);

			/**
			 * Stores an unsigned int value in this type. 
			 * @param value The unsigned int value to store in this instance.
			 */
			void setUInt(unsigned int value);

			/**
			 * Stores a long value in this type. 
			 * @param value The long value to store in this instance.
			 */
			void setLong(long value);

			/**
			 * Stores a unsigned long value in this type. 
			 * @param value The unsigned long value to store in this instance.
			 */
			void setULong(unsigned long value);

			/**
			 * Stores a float value in this type. 
			 * @param value The float value to store in this instance.
			 */
			void setFloat(float value);

			/**
			 * Stores a double value in this type. 
			 * @param value The double value to store in this instance.
			 */
			void setDouble(double value);

			/**
			 * Stores a std::string value in this type. 
			 * @param value The std::string value to store in this instance.
			 */
			void setString(const std::string& value);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setNamedInstancePtr(NamedInstance *value, bool autoPtr = false);

			/**
			 * Stores a void pointer in this type. 
			 * @param value The void pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setVoidPtr(void *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setConstNamedInstancePtr(const NamedInstance *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setConstMessagePtr(const Message *value, bool autoPtr = false);

			/**
			 * Stores a NamedInstance instance pointer in this type. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setConstRefCountedObjectPtr(const Poco::RefCountedObject *value, bool autoPtr = false);

			/**
			 * Stores a void pointer in this type. 
			 * @param value The void pointer to store in this instance.
			 * @param autoPtr If true it indicates that value is an instance of Poco::RefCountedObject and is held in a Poco::AutoPtr.
			 *				  This means that duplicate() and release() shall be called as appropriate to increase and decrease the reference count.
			 *				  Defaults to false.
			 */
			void setConstVoidPtr(const void *value, bool autoPtr = false);

			/**
			 * Stores a jvalue in this type. 
			 * @param value The jvalue to store in this instance.
			 */
			void setJValue(jvalue value);

			/**
			 * Gets a char value from this value stored in this instance. 
			 * @param value The char reference to use to store that value from this instance in.
			 */
			bool get(char& value) const;

			/**
			 * Gets an unsigned char value from this value stored in this instance. 
			 * @param value The unsigned char reference to use to store that value from this instance in.
			 */
			bool get(unsigned char& value) const;

			/**
			 * Gets a short value from this value stored in this instance. 
			 * @param value The short reference to use to store that value from this instance in.
			 */
			bool get(short& value) const;

			/**
			 * Gets a unsigned short value from this value stored in this instance. 
			 * @param value The unsigned short reference to use to store that value from this instance in.
			 */
			bool get(unsigned short& value) const;

			/**
			 * Gets a int value from this value stored in this instance. 
			 * @param value The int reference to use to store that value from this instance in.
			 */
			bool get(int& value) const;

			/**
			 * Gets an unsigned int value from this value stored in this instance. 
			 * @param value The unsigned int reference to use to store that value from this instance in.
			 */
			bool get(unsigned int& value) const;

			/**
			 * Gets a long value from this value stored in this instance. 
			 * @param value The long reference to use to store that value from this instance in.
			 */
			bool get(long& value) const;

			/**
			 * Gets a unsigned long value from this value stored in this instance. 
			 * @param value The unsigned long reference to use to store that value from this instance in.
			 */
			bool get(unsigned long& value) const;

			/**
			 * Gets a float value from this value stored in this instance. 
			 * @param value The float reference to use to store that value from this instance in.
			 */
			bool get(float& value) const;

			/**
			 * Gets a double value from this value stored in this instance. 
			 * @param value The double reference to use to store that value from this instance in.
			 */
			bool get(double& value) const;

			/**
			 * Gets a std::string value from this value stored in this instance. 
			 * @param value The std::string reference to use to store that value from this instance in.
			 */
			bool get(std::string& value) const;

			/**
			 * Gets a NamedInstance instance pointer from this value stored in this instance. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 */
			bool get(NamedInstance* &value) const;

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @param value The void pointer to store in this instance.
			 */
			bool get(void* &value) const;

			/**
			 * Gets a NamedInstance instance pointer from this value stored in this instance. 
			 * @param value The NamedInstance instance pointer to store in this instance.
			 */
			bool get(const NamedInstance* &value) const;

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @param value The void pointer to store in this instance.
			 */
			bool get(const void* &value) const;

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @param value The void pointer to store in this instance.
			 */
			bool get(const Message* &value) const;

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @param value The void pointer to store in this instance.
			 */
			bool get(const Poco::RefCountedObject* &value) const;

			/**
			 * Gets a jvalue from this value stored in this instance. 
			 * @param value The jreference to use to store that value from this instance in.
			 */
			bool get(jvalue& value) const;

			/**
			 * Gets a char value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not char.
			 */
			char getChar() const throw (Exception);

			/**
			 * Gets an unsigned char value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not unsigned char.
			 */
			unsigned char getUnsignedChar() const throw (Exception);

			/**
			 * Gets a short value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not short.
			 */
			short getShort() const throw (Exception);

			/**
			 * Gets a unsigned short value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not unsigned short.
			 */
			unsigned short getUnsignedShort() const throw (Exception);

			/**
			 * Gets a int value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not int.
			 */
			int getInt() const throw (Exception);

			/**
			 * Gets an unsigned int value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not unsigned int.
			 */
			unsigned int getUnsignedInt() const throw (Exception);

			/**
			 * Gets a long value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not long.
			 */
			long getLong() const throw (Exception);

			/**
			 * Gets a unsigned long value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not unsigned long.
			 */
			unsigned long getUnsignedLong() const throw (Exception);

			/**
			 * Gets a float value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not float.
			 */
			float getFloat() const throw (Exception);

			/**
			 * Gets a double value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not double.
			 */
			double getDouble() const throw (Exception);

			/**
			 * Gets a std::string value from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not std::string.
			 */
			std::string getString() const throw (Exception);

			/**
			 * Gets a NamedInstance instance pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not NamedInstance*.
			 */
			NamedInstance* getNamedInstance() const throw (Exception);

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not void*.
			 */
			void* getVoidPtr() const throw (Exception);

			/**
			 * Gets a NamedInstance instance pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not NamedInstance*.
			 */
			const NamedInstance* getConstNamedInstance() const throw (Exception);

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not void*.
			 */
			const void* getConstVoidPtr() const throw (Exception);

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not void*.
			 */
			const Message* getConstMessage() const throw (Exception);

			/**
			 * Gets a void pointer from this value stored in this instance. 
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not void*.
			 */
			const Poco::RefCountedObject* getConstRefCountedObject() const throw (Exception);

			/**
			 * Gets a jvalue from this value stored in this instance. 
			 * @param convert If true the function attempts to convert a non-jvalue stored in this Value
			 *				  instance into the correct type for the jvalue.
			 * @throws Exception::E_INVALID_PARAMETERS if the value wrapped in this instance is not jvalue.
			 */
			jvalue getJValue( bool convert = false ) const throw (Exception);

			/** Gets the type stored in this Value instance. */
			ValueType getType() const;

			/** Gets the mValue field from this Value instance. */
			ValuesUnion getValue() const;

			/**
			 * Gets the mAutoPtr flag. If this flag is true it means that a NamedInstance* or void* stored in this instance
			 * must be treated as an autoptr. That means the reference count will be increased by one 
			 * (by calling the duplicate() function, it is assumed the object will be an extension of Poco::RefCountedObject
			 * ) when this flag is set to true and decreased by one when a different value is set, the flag is set to false or
			 * if the destructor of this Value instance is called while mAutoPtr is true.
			 */
			bool getAutoPtr() const;

			/** Returns a string representation of the value stored in this instance. */
			std::string toString() const;

			/**
			 * Assignment operator. Assigns the value from the specified Value instance
			 * to this instance.
			 * @param rhs The Value instance to assign the value from.
			 * @return this instance after the assignment.
			 */
			Value& operator=(const Value& rhs);

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
			/** Read/write mutex on mAutoPtr for thread safety. */
			mutable Poco::RWLock mRWLockAutoPtr;
			/** This union is used to store the value in this instance. */
			ValuesUnion mValue;
			/** Stores the type of the value that is stored in mValue. */
			ValueType mType;
			/**
			 * If this flag is true it means that a NamedInstance* or void* stored in this instance
			 * must be treated as an autoptr. That means the reference count will be increased by one 
			 * (by calling the duplicate() function, it is assumed the object will be an extension of Poco::RefCountedObject
			 * ) when this flag is set to true and decreased by one when a different value is set, the flag is set to false or
			 * if the destructor of this Value instance is called while mAutoPtr is true.
			 */
			bool mAutoPtr;

			/**
			 * This function is called by all set() functions, just before mValue is changed. If mAutoPtr is true and
			 * the current value is a void* or NamedInstance*, release is on the value.
			 */
			void valueChangeCheckAutoPtr();
	};

	// inlines
	inline void Value::setChar(char value)
	{
		set(value);
	}

	inline void Value::setUChar(unsigned char value)
	{
		set(value);
	}

	inline void Value::setShort(short value)
	{
		set(value);
	}

	inline void Value::setUShort(unsigned short value)
	{
		set(value);
	}

	inline void Value::setInt(int value)
	{
		set(value);
	}

	inline void Value::setUInt(unsigned int value)
	{
		set(value);
	}

	inline void Value::setLong(long value)
	{
		set(value);
	}

	inline void Value::setULong(unsigned long value)
	{
		set(value);
	}

	inline void Value::setFloat(float value)
	{
		set(value);
	}

	inline void Value::setDouble(double value)
	{
		set(value);
	}

	inline void Value::setString(const std::string& value)
	{
		set(value);
	}

	inline void Value::setNamedInstancePtr(NamedInstance *value, bool autoPtr)
	{
		set(value, autoPtr);
	}

	inline void Value::setVoidPtr(void *value, bool autoPtr)
	{
		set(value, autoPtr);
	}

	inline void Value::setConstNamedInstancePtr(const NamedInstance *value, bool autoPtr)
	{
		set(value, autoPtr);
	}

	inline void Value::setConstMessagePtr(const Message *value, bool autoPtr)
	{
		set(value, autoPtr);
	}

	inline void Value::setConstRefCountedObjectPtr(const Poco::RefCountedObject *value, bool autoPtr)
	{
		set(value, autoPtr);
	}
	
	inline void Value::setConstVoidPtr(const void *value, bool autoPtr)
	{
		set(value, autoPtr);
	}

	inline void Value::setJValue(jvalue value)
	{
		set(value);
	}

	inline Value::ValueType Value::getType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mType;
	}

	inline Value::ValuesUnion Value::getValue() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mValue;
	}

	inline bool Value::getAutoPtr() const
	{
		Poco::ScopedRWLock(mRWLockAutoPtr, false);
		return mAutoPtr;
	}

} // namespace Myoushu

#endif

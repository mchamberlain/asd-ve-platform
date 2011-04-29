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
 * @file Value.cpp
 * @author ME Chamberlain
 * @date October 2008
 */

#include "Value.h"
#include "EngineLog.h"

namespace Myoushu
{
	Value::Value() : mValue(), mType(VT_UNKNOWN), mAutoPtr(false)
	{
	}

	Value::Value(const Value& v) : mValue(), mType(VT_UNKNOWN), mAutoPtr(false)
	{
		(*this) = v;
	}

	Value::~Value()
	{
		clearValue();
	}

	void Value::clearValue()
	{
		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		if (mType == VT_STRING)
		{
			delete mValue.mString;
			mValue.mString = NULL;
		}

		valueChangeCheckAutoPtr();

		mType = VT_UNKNOWN;
		mValue.mDouble = 0.0;
		mAutoPtr = false;
	}

	void Value::set(char value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_CHAR;
		mValue.mChar = value;
	}

	void Value::set(unsigned char value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_UCHAR;
		mValue.mUChar = value;
	}

	void Value::set(short value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_SHORT;
		mValue.mShort = value;
	}

	void Value::set(unsigned short value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_USHORT;
		mValue.mUShort = value;
	}

	void Value::set(int value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_INT;
		mValue.mInt = value;
	}

	void Value::set(unsigned int value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_UINT;
		mValue.mUInt = value;
	}

	void Value::set(long value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_LONG;
		mValue.mLong = value;
	}

	void Value::set(unsigned long value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_ULONG;
		mValue.mULong = value;
	}

	void Value::set(float value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_FLOAT;
		mValue.mFloat = value;
	}

	void Value::set(double value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_DOUBLE;
		mValue.mDouble = value;
	}

	void Value::set(const std::string& value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_STRING;
		mValue.mString = new std::string(value);
	}

	void Value::set(NamedInstance *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_NAMED_INSTANCE;
		mValue.mNamedInstance = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<Poco::RefCountedObject*>(mValue.mNamedInstance);
			pRefCountedObj->duplicate();
		}
	}

	void Value::set(void *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_VOID_PTR;
		mValue.mVoidPtr = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<Poco::RefCountedObject*>(mValue.mVoidPtr);
			pRefCountedObj->duplicate();
		}

	}

	void Value::set(const NamedInstance *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_CONST_NAMED_INSTANCE;
		mValue.mConstNamedInstance = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstNamedInstance);
			pRefCountedObj->duplicate();
		}
	}

	void Value::set(const Message *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_CONST_MESSAGE;
		mValue.mConstMessage = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstMessage);
			pRefCountedObj->duplicate();
		}
	}

	void Value::set(const Poco::RefCountedObject *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_CONST_REF_COUNTED_OBJECT;
		mValue.mConstRefCountedObj = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			if ( value )
			{
				value->duplicate();
			}
		}

	}

	void Value::set(const void *value, bool autoPtr)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_CONST_VOID_PTR;
		mValue.mConstVoidPtr = value;

		if (autoPtr)
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstVoidPtr);
			if ( pRefCountedObj )
			{
				pRefCountedObj->duplicate();
			}
		}

	}

	void Value::set(jvalue value)
	{
		clearValue();

		// Acquire a write lock
		Poco::ScopedRWLock lock(rwLock, true);

		mType = VT_JVALUE;
		mValue.mJValue = value;
	}

	bool Value::get(char& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_CHAR)
		{
			value = mValue.mChar;
			return true;
		}

		return false;
	}

	bool Value::get(unsigned char& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_UCHAR)
		{
			value = mValue.mUChar;
			return true;
		}

		return false;
	}

	bool Value::get(short& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_SHORT)
		{
			value = mValue.mShort;
			return true;
		}

		return false;
	}

	bool Value::get(unsigned short& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_USHORT)
		{
			value = mValue.mUShort;
			return true;
		}

		return false;
	}

	bool Value::get(int& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_INT)
		{
			value = mValue.mInt;
			return true;
		}

		return false;
	}

	bool Value::get(unsigned int& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_UINT)
		{
			value = mValue.mUInt;
			return true;
		}

		return false;
	}

	bool Value::get(long& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_LONG)
		{
			value = mValue.mLong;
			return true;
		}

		return false;
	}

	bool Value::get(unsigned long& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_ULONG)
		{
			value = mValue.mULong;
			return true;
		}

		return false;
	}

	bool Value::get(float& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_FLOAT)
		{
			value = mValue.mFloat;
			return true;
		}

		return false;
	}

	bool Value::get(double& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_DOUBLE)
		{
			value = mValue.mDouble;
			return true;
		}

		return false;
	}

	bool Value::get(std::string& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_STRING)
		{
			value = *(mValue.mString);
			return true;
		}

		return false;
	}

	bool Value::get(NamedInstance* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_NAMED_INSTANCE)
		{
			value = const_cast<NamedInstance*>(mValue.mNamedInstance);
			return true;
		}

		return false;
	}

	bool Value::get(void* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_VOID_PTR)
		{
			value = const_cast<void*>(mValue.mVoidPtr);
			return true;
		}

		return false;
	}

	bool Value::get(const NamedInstance* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_CONST_NAMED_INSTANCE)
		{
			value = mValue.mConstNamedInstance;
			return true;
		}

		return false;
	}

	bool Value::get(const Message* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_CONST_MESSAGE)
		{
			value = mValue.mConstMessage;
			return true;
		}

		return false;
	}

	bool Value::get(const Poco::RefCountedObject* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_CONST_REF_COUNTED_OBJECT)
		{
			value = mValue.mConstRefCountedObj;
			return true;
		}

		return false;
	}

	bool Value::get(const void* &value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_CONST_VOID_PTR)
		{
			value = mValue.mConstVoidPtr;
			return true;
		}

		return false;
	}

	bool Value::get(jvalue& value) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType == VT_JVALUE)
		{
			value = mValue.mJValue;
			return true;
		}

		return false;
	}

	char Value::getChar() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_CHAR)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getChar(): value is not a char!");
		}

		return mValue.mChar;
	}

	unsigned char Value::getUnsignedChar() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_UCHAR)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getUnsignedChar(): value is not an unsigned char!");
		}

		return mValue.mUChar;
	}

	short Value::getShort() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_SHORT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getShort(): value is not a short!");
		}

		return mValue.mShort;
	}

	unsigned short Value::getUnsignedShort() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_USHORT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getUnsignedShort(): value is not an unsigned short!");
		}

		return mValue.mUShort;
	}

	int Value::getInt() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_INT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getInt(): value is not an integer!");
		}

		return mValue.mInt;
	}

	unsigned int Value::getUnsignedInt() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_UINT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getUnsignedInt(): value is not an unsigned int!");
		}

		return mValue.mChar;
	}

	long Value::getLong() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_LONG)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getLong(): value is not a long!");
		}

		return mValue.mLong;
	}

	unsigned long Value::getUnsignedLong() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_ULONG)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getUnsignedLong(): value is not a unsigned long!");
		}

		return mValue.mULong;
	}

	float Value::getFloat() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_FLOAT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getFloat(): value is not a float!");
		}

		return mValue.mFloat;
	}

	double Value::getDouble() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_DOUBLE)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getDouble(): value is not a double!");
		}

		return mValue.mDouble;
	}

	std::string Value::getString() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_STRING)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getString(): value is not a string!");
		}

		return *mValue.mString;
	}

	NamedInstance* Value::getNamedInstance() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_NAMED_INSTANCE)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getNamedInstance(): value is not a NamedInstance*!");
		}

		return const_cast<NamedInstance*>(mValue.mNamedInstance);
	}

	void* Value::getVoidPtr() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_VOID_PTR)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getVoidPtr(): value is not a void*!");
		}

		return const_cast<void*>(mValue.mVoidPtr);
	}

	const NamedInstance* Value::getConstNamedInstance() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_CONST_NAMED_INSTANCE)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getConstNamedInstance(): value is not a const NamedInstance*!");
		}

		return mValue.mConstNamedInstance;
	}

	const Message* Value::getConstMessage() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_CONST_MESSAGE)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getConstMessage(): value is not a const Message*!");
		}

		return mValue.mConstMessage;
	}

	const Poco::RefCountedObject* Value::getConstRefCountedObject() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_CONST_REF_COUNTED_OBJECT)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getConstRefCountedObject(): value is not a const Poco::RefCountedObject*!");
		}

		return mValue.mConstRefCountedObj;
	}

	const void* Value::getConstVoidPtr() const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mType != VT_CONST_VOID_PTR)
		{
			throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getVoidPtr(): value is not a const void*!");
		}

		return mValue.mConstVoidPtr;
	}

	jvalue Value::getJValue( bool convert ) const throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if ( !convert )
		{
			if (mType != VT_JVALUE)
			{
				throw Exception(Exception::E_INVALID_PARAMETERS, "Value::getJValue(): value is not a jvalue!");
			}

			return mValue.mJValue;
		}
		else
		{
			jvalue val;
			switch ( mType )
			{
				case VT_NAMED_INSTANCE:
					val.j = reinterpret_cast<jlong>( mValue.mNamedInstance );
					break;
				case VT_CONST_REF_COUNTED_OBJECT:
					val.j = reinterpret_cast<jlong>( mValue.mConstRefCountedObj );
					break;
				case VT_CONST_MESSAGE:
					val.j = reinterpret_cast<jlong>( mValue.mConstMessage );
					break;
				case VT_CONST_VOID_PTR:
					val.j = reinterpret_cast<jlong>( mValue.mConstVoidPtr );
					break;
				case VT_VOID_PTR:
					val.j = reinterpret_cast<jlong>( mValue.mVoidPtr );
					break;
				case VT_CHAR:
					val.b = static_cast< jbyte >( mValue.mChar );
					break;
				case VT_UCHAR:
					val.c = static_cast< jchar >( mValue.mUChar );
					break;
				case VT_SHORT:
					val.s = static_cast< jshort >( mValue.mShort );
					break;
				case VT_USHORT:
					val.i = static_cast< jint >( mValue.mUShort );
					break;
				case VT_INT:
					val.i = static_cast< jint >( mValue.mInt );
					break;
				case VT_UINT:
					val.j = static_cast< jlong >( mValue.mUInt );
					break;
				case VT_LONG:
					val.j = static_cast< jlong >( mValue.mLong );
					break;
				case VT_ULONG:
					val.j = static_cast< jlong >( mValue.mULong );
					break;
				case VT_FLOAT:
					val.f = static_cast< jfloat >( mValue.mFloat );
					break;
				case VT_DOUBLE:
					val.d = static_cast< jdouble >( mValue.mDouble );
					break;
				case VT_STRING:
					break;
				default:
					val = mValue.mJValue;
					break;
			}

			return val;
		}
	}

	Value& Value::operator=(const Value& rhs)
	{
		clearValue();

		Poco::ScopedRWLock lock(rwLock, true);

		mType = rhs.getType();

		if (mType == VT_STRING)
		{
			mValue.mString = new std::string(rhs.getString());
		}
		else
		{
			mValue = rhs.getValue();
		}

		if ( (rhs.getAutoPtr() ) && ( (mType == VT_VOID_PTR ) || ( mType == VT_CONST_VOID_PTR ) || ( mType == VT_NAMED_INSTANCE ) || ( mType == VT_CONST_NAMED_INSTANCE )
			|| ( mType == VT_CONST_MESSAGE ) || ( mType == VT_CONST_REF_COUNTED_OBJECT ) ) )
		{
			Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
			mAutoPtr = true;

			const Poco::RefCountedObject *pRefCountedObj = NULL;
			switch ( mType )
			{
				case VT_VOID_PTR:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mVoidPtr);
					break;
				case VT_CONST_VOID_PTR:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstVoidPtr);
					break;
				case VT_NAMED_INSTANCE:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mNamedInstance);
					break;
				case VT_CONST_NAMED_INSTANCE:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstNamedInstance);
					break;
				case VT_CONST_MESSAGE:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstMessage);
					break;
				case VT_CONST_REF_COUNTED_OBJECT:
					pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstRefCountedObj);
					break;
			}

			if ( pRefCountedObj )
			{
				pRefCountedObj->duplicate();
			}
		}


		return *this;
	}

	std::string Value::toString() const
	{
		std::stringstream sStr;

		switch (mType)
		{
			case VT_CHAR:
				sStr << mValue.mChar;
				break;
			case VT_UCHAR:
				sStr << mValue.mUChar;
				break;
			case VT_SHORT:
				sStr << mValue.mShort;
				break;
			case VT_USHORT:
				sStr << mValue.mUShort;
				break;
			case VT_INT:
				sStr << mValue.mInt;
				break;
			case VT_UINT:
				sStr << mValue.mUInt;
				break;
			case VT_LONG:
				sStr << mValue.mLong;
				break;
			case VT_ULONG:
				sStr << mValue.mULong;
				break;
			case VT_FLOAT:
				sStr << mValue.mFloat;
				break;
			case VT_DOUBLE:
				sStr << mValue.mDouble;
				break;
			case VT_STRING:
				if (mValue.mString != NULL)
				{
					sStr << (*(mValue.mString));
				}
				else
				{
					sStr << "NULL";
				}
				break;
			case VT_NAMED_INSTANCE:
				sStr << reinterpret_cast<memUInt>(mValue.mNamedInstance);
				break;
			case VT_VOID_PTR:
				sStr << reinterpret_cast<memUInt>(mValue.mVoidPtr);
				break;
			case VT_CONST_NAMED_INSTANCE:
				sStr << reinterpret_cast<memUInt>(mValue.mConstNamedInstance);
				break;
			case VT_CONST_VOID_PTR:
				sStr << reinterpret_cast<memUInt>(mValue.mConstVoidPtr);
				break;
			case VT_JVALUE:
				LOG(EngineLog::LM_WARNING, "unsupported string conversion (jvalue) in Value instance...");
				break;
			default:
				LOG(EngineLog::LM_ERROR, "unknown type in Value instance...");
		}

		return sStr.str();
	}

	memUInt Value::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Value::serialize(): buffer is NULL.");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// Write the type of the value stored
		writtenSize = writePrimitiveType(mType, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Value::serialize(): buffer too small.");
		}

		// Write the value with the correct type
		switch (mType)
		{
			case VT_CHAR:
				writtenSize = writePrimitiveType(mValue.mChar, pBuf);
				break;
			case VT_UCHAR:
				writtenSize = writePrimitiveType(mValue.mUChar, pBuf);
				break;
			case VT_SHORT:
				writtenSize = writePrimitiveType(mValue.mShort, pBuf);
				break;
			case VT_USHORT:
				writtenSize = writePrimitiveType(mValue.mUShort, pBuf);
				break;
			case VT_INT:
				writtenSize = writePrimitiveType(mValue.mInt, pBuf);
				break;
			case VT_UINT:
				writtenSize = writePrimitiveType(mValue.mUInt, pBuf);
				break;
			case VT_LONG:
				writtenSize = writePrimitiveType(mValue.mLong, pBuf);
				break;
			case VT_ULONG:
				writtenSize = writePrimitiveType(mValue.mULong, pBuf);
				break;
			case VT_FLOAT:
				writtenSize = writePrimitiveType(mValue.mFloat, pBuf);
				break;
			case VT_DOUBLE:
				writtenSize = writePrimitiveType(mValue.mDouble, pBuf);
				break;
			case VT_STRING:
				writtenSize = writeString(*(mValue.mString), pBuf);
				break;
			case VT_NAMED_INSTANCE:
				LOG(EngineLog::LM_WARNING, "NamedInstance * serialization not supported in Value...");
				break;
			case VT_VOID_PTR:
				LOG(EngineLog::LM_WARNING, "void * serialization not supported in Value...");
				break;
			case VT_CONST_NAMED_INSTANCE:
				LOG(EngineLog::LM_WARNING, "const NamedInstance * serialization not supported in Value...");
				break;
			case VT_CONST_MESSAGE:
				LOG(EngineLog::LM_WARNING, "const Message * serialization not supported in Value...");
				break;
			case VT_CONST_REF_COUNTED_OBJECT:
				LOG(EngineLog::LM_WARNING, "const Poco::RefCountedObject * serialization not supported in Value...");
				break;
			case VT_CONST_VOID_PTR:
				LOG(EngineLog::LM_WARNING, "const void * serialization not supported in Value...");
				break;
			case VT_JVALUE:
				writtenSize = writePrimitiveType(mValue.mJValue, pBuf);
				break;
			default:
				LOG(EngineLog::LM_ERROR, "unknown type in Value instance...");
		}

		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Value::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt Value::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Value::populateInstance(): buffer is NULL.");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// In the special case of a string being set, we have to free it before we populate this Value instance with new data
		if ((mType == VT_STRING) && (mValue.mString != NULL))
		{
			delete mValue.mString;
			mValue.mString = NULL;
		}

		// Read the type of the value stored
		readSize = readPrimitiveType(mType, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Value::populateInstance(): buffer too small.");
		}

		// Read the value with the correct type
		switch (mType)
		{
			case VT_CHAR:
				readSize = readPrimitiveType(mValue.mChar, pBuf);
				break;
			case VT_UCHAR:
				readSize = readPrimitiveType(mValue.mUChar, pBuf);
				break;
			case VT_SHORT:
				readSize = readPrimitiveType(mValue.mShort, pBuf);
				break;
			case VT_USHORT:
				readSize = readPrimitiveType(mValue.mUShort, pBuf);
				break;
			case VT_INT:
				readSize = readPrimitiveType(mValue.mInt, pBuf);
				break;
			case VT_UINT:
				readSize = readPrimitiveType(mValue.mUInt, pBuf);
				break;
			case VT_LONG:
				readSize = readPrimitiveType(mValue.mLong, pBuf);
				break;
			case VT_ULONG:
				readSize = readPrimitiveType(mValue.mULong, pBuf);
				break;
			case VT_FLOAT:
				readSize = readPrimitiveType(mValue.mFloat, pBuf);
				break;
			case VT_DOUBLE:
				readSize = readPrimitiveType(mValue.mDouble, pBuf);
				break;
			case VT_STRING:
				readSize = readString(*(mValue.mString), pBuf);
				break;
			case VT_NAMED_INSTANCE:
				LOG(EngineLog::LM_WARNING, "NamedInstance * serialization not supported in Value...");
				break;
			case VT_VOID_PTR:
				LOG(EngineLog::LM_WARNING, "void * serialization not supported in Value...");
				break;
			case VT_CONST_NAMED_INSTANCE:
				LOG(EngineLog::LM_WARNING, "const NamedInstance * serialization not supported in Value...");
				break;
			case VT_CONST_MESSAGE:
				LOG(EngineLog::LM_WARNING, "const Message * serialization not supported in Value...");
				break;
			case VT_CONST_REF_COUNTED_OBJECT:
				LOG(EngineLog::LM_WARNING, "const Poco::RefCountedObject * serialization not supported in Value...");
				break;
			case VT_CONST_VOID_PTR:
				LOG(EngineLog::LM_WARNING, "const void * serialization not supported in Value...");
				break;
			case VT_JVALUE:
				readSize = readPrimitiveType(mValue.mJValue, pBuf);
				break;
			default:
				LOG(EngineLog::LM_ERROR, "unknown type in Value instance...");
		}

		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "Value::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

	void Value::valueChangeCheckAutoPtr()
	{
		if (!getAutoPtr())
		{
			return;
		}

		if (mType == VT_VOID_PTR)
		{
			Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<Poco::RefCountedObject*>(mValue.mVoidPtr);
			pRefCountedObj->release();
		}
		else if (mType == VT_CONST_VOID_PTR)
		{
			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstVoidPtr);
			pRefCountedObj->release();
		}
		else if (mType == VT_NAMED_INSTANCE)
		{
			Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<Poco::RefCountedObject*>(mValue.mNamedInstance);
			pRefCountedObj->release();
		}
		else if (mType == VT_CONST_NAMED_INSTANCE)
		{
			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstNamedInstance);
			pRefCountedObj->release();
		}
		else if (mType == VT_CONST_MESSAGE)
		{
			const Poco::RefCountedObject *pRefCountedObj = reinterpret_cast<const Poco::RefCountedObject*>(mValue.mConstMessage);
			pRefCountedObj->release();
		}
		else if (mType == VT_CONST_REF_COUNTED_OBJECT)
		{
			mValue.mConstRefCountedObj->release();
		}

		Poco::ScopedRWLock lock(mRWLockAutoPtr, true);
		mAutoPtr = false;
	}

} // namespace Myoushu

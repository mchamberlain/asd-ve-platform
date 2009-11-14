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
 * @file GameCharacterObjectControllerBinding.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "GameCharacterObjectControllerBinding.h"
#include "NetworkManager.h"

namespace Myoushu
{
	GameCharacterObjectControllerBinding::GameCharacterObjectControllerBinding() : inputAction(""), characterAction(""), 
		direction(Ogre::Vector3::ZERO), rotationAxis(Ogre::Vector3::ZERO), deviceAxis(-1), once(false)
	{
	}

	GameCharacterObjectControllerBinding::GameCharacterObjectControllerBinding(const Ogre::String& inputAction
		, const Ogre::String& characterAction, const Ogre::Vector3& direction, const Ogre::Vector3& rotationAxis, int deviceAxis, bool once) 
		: inputAction(inputAction), characterAction(characterAction), direction(direction), rotationAxis(rotationAxis), deviceAxis(deviceAxis)
		, once(once)
	{
	}

	GameCharacterObjectControllerBinding::~GameCharacterObjectControllerBinding()
	{
	}


	GameCharacterObjectControllerBinding& GameCharacterObjectControllerBinding::operator=(const GameCharacterObjectControllerBinding& rhs)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		inputAction = rhs.getInputAction();
		characterAction = rhs.getCharacterAction();
		direction = rhs.getDirection();
		once = rhs.isOnce();

		return *this;
	}

	memUInt GameCharacterObjectControllerBinding::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectControllerBinding::serialize(): buffer is NULL.");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// Write the inputAction member

		// If the serialization is for network transmission (sTarget == ST_NETWORK) then we append the local IP to the inputAction to ensure
		// that it is unique on the target host and identifiable as belonging to this host
		if (sTarget == ST_NETWORK)
		{
			writtenSize = writeString(inputAction + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
		}
		else
		{
			writtenSize = writeString(inputAction, pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		// Write the characterAction member
		writtenSize = writeString(characterAction, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		// Write the direction vector
		writtenSize = writeOgreVector3(direction, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		// Write the rotationAxis vector
		writtenSize = writeOgreVector3(rotationAxis, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		// Write the deviceAxis
		writtenSize = writePrimitiveType(deviceAxis, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		// Write the once boolean member
		writtenSize = writePrimitiveType(once, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt GameCharacterObjectControllerBinding::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectControllerBinding::populateInstance(): buffer is NULL.");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// Read the inputAction member
		readSize = readString(inputAction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		// Read the characterAction member
		readSize = readString(characterAction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		// Read the direction vector
		readSize = readOgreVector3(direction, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		// Read the rotationAxis vector
		readSize = readOgreVector3(rotationAxis, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		// Read the deviceAxis
		readSize = readPrimitiveType(deviceAxis, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		// Read the once boolean member
		readSize = readPrimitiveType(once, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectControllerBinding::populateInstance(): buffer too small.");
		}

		return totalSize;
	}

} // namespace Myoushu

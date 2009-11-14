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
 * @file MoveableObjectController.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "MoveableObjectController.h"

namespace Myoushu
{
	MoveableObjectController::MoveableObjectController(const Ogre::String& name, Ogre::Real maxMovementSpeed, Ogre::Real movementAcceleration
		, Ogre::Real maxRotationSpeed, Ogre::Real rotationAcceleration) : Controller(name), mMovementSpeed(0), mMaxMovementSpeed(maxMovementSpeed)
		, mMovementAcceleration(movementAcceleration), mRotationSpeed(0), mMaxRotationSpeed(maxRotationSpeed)
		, mRotationAcceleration(rotationAcceleration), mpLinkedController(NULL)
	{
	}

	void MoveableObjectController::linkSpeedsWith(MoveableObjectController* otherController)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpLinkedController = otherController;

		if (otherController == NULL)
		{
			return;
		}

		otherController->setMovementAcceleration(mMovementAcceleration);
		otherController->setMaxMovementSpeed(mMaxMovementSpeed);
		otherController->setRotationAcceleration(mRotationAcceleration);
		otherController->setMaxRotationSpeed(mMaxRotationSpeed);
	}

	void MoveableObjectController::stop()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMovementSpeed = 0;
		mRotationSpeed = 0;
	}

	void MoveableObjectController::update(unsigned long timeDelta)
	{
		// If mpLinkedController is not NULL, update the speeds of mpLinkedController to match this controller's speed
		updateLinkedController();
	}

	void MoveableObjectController::updateLinkedController()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (mpLinkedController == NULL)
		{
			return;
		}

		mpLinkedController->setMovementAcceleration(mMovementAcceleration);
		mpLinkedController->setMaxMovementSpeed(mMaxMovementSpeed);
		mpLinkedController->setMovementSpeed(mMovementSpeed);
		mpLinkedController->setRotationAcceleration(mRotationAcceleration);
		mpLinkedController->setMaxRotationSpeed(mMaxRotationSpeed);
		mpLinkedController->setRotationSpeed(mRotationSpeed);
	}

	memUInt MoveableObjectController::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt writtenSize;
		memUInt totalSize;
		char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MoveableObjectController::serialize(): buffer is NULL!");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// First serialize using the parent class' method
		writtenSize = Controller::serialize(pBuf, size, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;

		// Write mMovementSpeed
		writtenSize = writePrimitiveType(mMovementSpeed, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		// Write mMaxMovementSpeed
		writtenSize = writePrimitiveType(mMaxMovementSpeed, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		// Write mMovementAcceleration
		writtenSize = writePrimitiveType(mMovementAcceleration, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		// Write mRotationSpeed
		writtenSize = writePrimitiveType(mRotationSpeed, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		// Write mMaxRotationSpeed
		writtenSize = writePrimitiveType(mMaxRotationSpeed, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		// Write mRotationAcceleration
		writtenSize = writePrimitiveType(mRotationAcceleration, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::serialize(): buffer is too small.");
		}

		return totalSize;
	}

	memUInt MoveableObjectController::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		const char *pBuf;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "MoveableObjectController::populateInstance(): buffer is NULL!");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// First populateInstance using the parent class' method
		readSize = Controller::populateInstance(pBuf, size, sTarget);
		pBuf += readSize;
		totalSize += readSize;

		// Read mMovementSpeed
		readSize = readPrimitiveType(mMovementSpeed, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		// Read mMaxMovementSpeed
		readSize = readPrimitiveType(mMaxMovementSpeed, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		// Read mMovementAcceleration
		readSize = readPrimitiveType(mMovementAcceleration, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		// Read mRotationSpeed
		readSize = readPrimitiveType(mRotationSpeed, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		// Read mMaxRotationSpeed
		readSize = readPrimitiveType(mMaxRotationSpeed, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		// Read mRotationAcceleration
		readSize = readPrimitiveType(mRotationAcceleration, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MoveableObjectController::populateInstance(): buffer is too small.");
		}

		return totalSize;
	}

} // namespace Myoushu
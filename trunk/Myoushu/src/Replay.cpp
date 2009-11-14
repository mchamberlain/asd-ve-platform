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
 * @file Replay.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "Poco/File.h"

#include "Replay.h"
#include "Constants.h"
#include "ObjectPoolBase.h"
#include "NotificationManager.h"
#include "EngineLog.h"
#include "Random.h"

namespace Myoushu
{
	CLASS_NAME(Replay, "Myoushu::Replay");

	const std::string Replay::TIMESTAMP_STRING = "Timestamp";
	const std::string Replay::NO_RANDOM_STRING = "No_Random";

	Replay::Replay(const std::string& name) : NamedInstance(name), mpInputStream(), mOutputStream(), mAccumulatedPlayTime(0), mPreviousTimestamp(0), mRandomStateProcessed(false)
	{
		pBuffer = new char[Constants::REPLAY_TASK_BUFFER_SIZE];
	}

	Replay::Replay(const std::string& name, const std::string& group, bool openForWriting) : NamedInstance(name), mpInputStream(), mOutputStream(), mRandomStateProcessed(false)
		, mAccumulatedPlayTime(0), mPreviousTimestamp(0)
	{
		pBuffer = new char[Constants::REPLAY_TASK_BUFFER_SIZE];

		if (!openForWriting)
		{
			openForPlayback(group);
		}
		else
		{
			this->openForWriting(group);
		}
	}

	Replay::~Replay()
	{
		if (pBuffer != NULL)
		{
			delete [] pBuffer;
			pBuffer = NULL;
		}
		if (!mpInputStream.isNull())
		{
			mpInputStream->close();
			// Ogre shared pointer: is reference counted
			mpInputStream.setNull();
		}

		if (mOutputStream.is_open())
		{
			mOutputStream.close();
		}

		mRandomStateProcessed = false;
	}

	void Replay::openForWriting(const std::string& group, bool overwrite) throw (Exception)
	{
		std::string fullFilePath;
		std::string groupName;

		// If group == "" use the default Constants::RG_REPLAYS for the replays resource group
		if (group == "")
		{
			groupName = Constants::RG_REPLAYS;
		}
		else
		{
			groupName = group;
		}

		// Get the Ogre::ResourceGroupManager instance and find the path to the Constants::RG_REPLAYS resource group.
		Ogre::FileInfoListPtr pFileInfoList = Ogre::ResourceGroupManager::getSingleton().listResourceFileInfo(groupName, true);

		if (pFileInfoList->empty())
		{
			// if the list is empty, open/create the file in the current working directory
			fullFilePath = "";
		}
		else
		{
			// Use the first path in the file info list as the path 
			const Ogre::FileInfo& fileInfo = pFileInfoList->front();
			fullFilePath = fileInfo.path + "/";
		}
		// Append the file name to the path
		fullFilePath += getName() + ".replay";

		Poco::ScopedRWLock lock(mRWLock, true);

		// If the stream is somehow already open, close it first
		if (mOutputStream.is_open())
		{
			mOutputStream.close();
		}
		if (!mpInputStream.isNull())
		{
			mpInputStream->close();
			// Ogre shared pointer: is reference counted
			mpInputStream.setNull();
		}

		mPreviousTimestamp = 0;

		// If overwrite is true, we truncate the existing file
		if (overwrite)
		{
			Poco::File file(fullFilePath);

			// If the file exists, delete it
			if (file.exists())
			{
				file.remove();
			}
		}

		// Open the file
		mOutputStream.open(fullFilePath.c_str(), std::ios::out | std::ios::binary);

		mRandomStateProcessed = false;
	}

	void Replay::openForPlayback(const std::string& group) throw (Exception)
	{
		std::string groupName;

		// If group == "" use the default Constants::RG_REPLAYS for the replays resource group
		if (group == "")
		{
			groupName = Constants::RG_REPLAYS;
		}
		else
		{
			groupName = group;
		}

		// If we have an existing open stream, close it
		if (mOutputStream.is_open())
		{
			mOutputStream.close();
		}
		if (!mpInputStream.isNull())
		{
			mpInputStream->close();
			// Ogre shared pointer: is reference counted
			mpInputStream.setNull();
		}
		
		// Open the replay via the Ogre::ResourceGroupManager
		mpInputStream = Ogre::ResourceGroupManager::getSingleton().openResource(getName() + ".replay", groupName, false);

		// Throw an exception if the file could not be found
		if (mpInputStream.isNull())
		{
			throw Exception(Exception::E_FILE_NOT_FOUND, "Replay::openForPlayback(): file: " + getName() + ".replay not found!");
		}

		reset();

		mRandomStateProcessed = false;
	}

	void Replay::write(unsigned int timestamp, const Message& message) throw (Exception)
	{
		memUInt writeSize;
		memUInt totalSize;
		memUInt pBuf;

		writeSize = 0;
		totalSize = 0;

		if (!mOutputStream.is_open())
		{
			// If the output stream is not open, throw a Exception::E_FILE_NOT_OPEN exception.
			throw Exception(Exception::E_FILE_NOT_OPEN, "Replay::write(): the file, " + getName() + ".replay, is not open.");
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		pBuf = reinterpret_cast<memUInt>(pBuffer);

		// Check whether the random number generator state has been written to the file
		if (!mRandomStateProcessed)
		{
			Random *pRandom = Random::getSingletonPtr();

			// If a random number generator singleton exists, write its current state to the replay file
			if (pRandom != NULL)
			{
				writeSize = writeString("Random", reinterpret_cast<void*>(pBuf));
				pBuf += writeSize;
				totalSize += writeSize;

				writeSize = pRandom->serialize(reinterpret_cast<void*>(pBuf), Constants::REPLAY_TASK_BUFFER_SIZE - totalSize);
				pBuf += writeSize;
				totalSize += writeSize;
			}
			else
			{
				writeSize = writeString(NO_RANDOM_STRING, reinterpret_cast<void*>(pBuf));
				pBuf += writeSize;
				totalSize += writeSize;
			}

			// Write the total size of the Random instance to the file
			mOutputStream.write(reinterpret_cast<char*>(&totalSize), sizeof(memUInt) / sizeof(char));
			mOutputStream.write(pBuffer, totalSize / sizeof(char));
			mRandomStateProcessed = true;

			writeSize = 0;
			totalSize = 0;
			pBuf = reinterpret_cast<memUInt>(pBuffer);
		}

		if ((timestamp != mPreviousTimestamp) || (static_cast<long>(mOutputStream.tellp()) == 0L))
		{
			// If the timestamps differ, update mPreviousTimestamp and write the new timestamp to the file.
			mPreviousTimestamp = timestamp;

			writeSize = writeString(TIMESTAMP_STRING, reinterpret_cast<void*>(pBuf));
			pBuf += writeSize;
			totalSize += writeSize;

			writeSize = writePrimitiveType(timestamp, reinterpret_cast<void*>(pBuf));
			pBuf += writeSize;
			totalSize += writeSize;
		}

		// Write the class name of the message instance to the buffer
		writeSize = writeString(message.getClassName(), reinterpret_cast<void*>(pBuf));
		pBuf += writeSize;
		totalSize += writeSize;
		// Serialize the message instance to the buffer
		writeSize = message.serialize(reinterpret_cast<void*>(pBuf), Constants::REPLAY_TASK_BUFFER_SIZE - totalSize);
		pBuf += writeSize;
		totalSize += writeSize;

		// Write the total size of the timestamp + message to the file first, and then dump the buffer to the file
		mOutputStream.write(reinterpret_cast<char*>(&totalSize), sizeof(memUInt) / sizeof(char));
		mOutputStream.write(pBuffer, totalSize / sizeof(char));
	}

	void Replay::close()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mRandomStateProcessed = false;

		if (!mpInputStream.isNull())
		{
			mpInputStream->close();
			// Ogre shared pointer: is reference counted
			mpInputStream.setNull();
		}

		if (mOutputStream.is_open())
		{
			mOutputStream.close();
		}
	}

	bool Replay::play(unsigned long timeDelta) throw (Exception)
	{
		unsigned long timestamp;
		memUInt size;
		memUInt totalSize;
		memUInt readSize;
		memUInt pBuf;
		Message *pMessage;
		std::string description;
		ObjectPoolBase *pPool;
		bool hasNext;

		Poco::ScopedRWLock lock(mRWLock, true);

		totalSize = 0;
		size = 0;
		readSize = 0;

		if (mpInputStream.isNull())
		{
			throw Exception(Exception::E_FILE_NOT_OPEN, "Replay::play(): file, " + getName() + ".replay, not open.");
		}

		// Check whether the random number generator state has been written to the file
		if ((!mRandomStateProcessed) && (mAccumulatedPlayTime == 0))
		{
			std::string mRandomClassName;
			Random *pRandom = Random::getSingletonPtr();

			// Read the total size of the random instance
			mpInputStream->read(static_cast<void*>(&totalSize), sizeof(memUInt));
			if (totalSize > Constants::REPLAY_TASK_BUFFER_SIZE)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "Replay::play(): buffer too small.");
			}
			size = totalSize;

			// Read a block of totalSize bytes from the stream into memory
			readSize = mpInputStream->read(reinterpret_cast<void*>(pBuffer), totalSize);
			if ((readSize == 0) || (readSize != totalSize))
			{
				throw Exception(Exception::E_GENERAL_EXCEPTION, "Replay::play(): error reading Random instance data from file.");
			}

			totalSize = 0;
			pBuf = reinterpret_cast<memUInt>(pBuffer);

			readSize = readString(mRandomClassName, reinterpret_cast<void*>(pBuf));
			pBuf += readSize;
			totalSize += readSize;

			// If the class name of the random number generator is not NO_RANDOM_STRING then
			// the state of the random number generator is included in the replay.
			if (mRandomClassName != NO_RANDOM_STRING)
			{
				// If the Random singleton does not exist, create it
				if (pRandom == NULL)
				{
					pRandom = new Random();
				}

				readSize = pRandom->populateInstance(reinterpret_cast<void*>(pBuf), size - totalSize);
				pBuf += readSize;
				totalSize += readSize;
			}

			// Set this flag to true to indicate that we have dealt with the random number generator state.
			mRandomStateProcessed = true;
			totalSize = 0;
			size = 0;
			readSize = 0;
		}

		mAccumulatedPlayTime += timeDelta;

		// hasNext will determine whether the outer loop continues
		hasNext = false;
		do
		{
			// Read the total size of the next either timestamp and message or just message
			mpInputStream->read(static_cast<void*>(&totalSize), sizeof(memUInt));
			if (totalSize > Constants::REPLAY_TASK_BUFFER_SIZE)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "Replay::play(): buffer too small.");
			}
			size = totalSize;

			// Read a block of totalSize bytes from the stream into memory
			readSize = mpInputStream->read(reinterpret_cast<void*>(pBuffer), totalSize);
			if ((readSize == 0) || (readSize != totalSize))
			{
				throw Exception(Exception::E_GENERAL_EXCEPTION, "Replay::play(): error reading data from file.");
			}

			// Read the description of the item
			pBuf = reinterpret_cast<memUInt>(pBuffer);
			while ((size > 0) && (size <= totalSize))
			{
				readSize = readString(description, reinterpret_cast<void*>(pBuf));
				size -= readSize;
				pBuf += readSize;

				if (description == TIMESTAMP_STRING)
				{
					// Read the timestamp
					readSize = readPrimitiveType(timestamp, reinterpret_cast<void*>(pBuf));
					size -= readSize;
					pBuf += readSize;

					if ((timestamp < mPreviousTimestamp) || (timestamp > mAccumulatedPlayTime))
					{
						// The message that follows should not be played yet, seek backward in the stream
						// with sizeof(memUInt) + totalSize so that we are ready to read it again in
						// the next iteration
						mpInputStream->seek(mpInputStream->tell() - sizeof(memUInt) - totalSize);
						// Stop the outer loop as well
						hasNext = false;
						// Exit the loop
						break;
					}
					else
					{
						hasNext = true;
						mPreviousTimestamp = timestamp;
					}
				}
				else 
				{
					// Instantiate and populate the Message instance
					pPool = ObjectPoolBase::getObjectPoolFromClassName(description);
					if (pPool == NULL)
					{
						// Log an error and continue to the next iteration of the loop
						LOG(EngineLog::LM_WARNING, "Replay::play(): Encountered an unknown class: " + description);
						// Set size to zero so that we skip the data
						size = 0;
						continue;
					}
					else
					{
						pMessage = static_cast<Message*>(pPool->get(true));
						readSize = pMessage->populateInstance(reinterpret_cast<void*>(pBuf), size);
						size -= readSize;
						pBuf += readSize;

						// dispatch the message
						NotificationManager::getSingleton().queueNotification(pMessage);
					}
				}
			}
		} while (hasNext);

		return !(mpInputStream->eof());
	}

	void Replay::reset()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		mAccumulatedPlayTime = 0;
		mPreviousTimestamp = 0;
	}

	memUInt Replay::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		throw Exception(Exception::E_UNIMPLEMENTED, "Replay::serialize(): not implemented, see write().");
	}

	memUInt Replay::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		throw Exception(Exception::E_UNIMPLEMENTED, "Replay::serialize(): not implemented, see play().");
	}

} // namespace Myoushu

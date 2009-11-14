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
 * @file Replay.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_REPLAY_H
#define MYOUSHU_REPLAY_H

#include <list>
#include <fstream>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "Ogre.h"

#include "Platform.h"
#include "NamedInstance.h"
#include "NamedObject.h"
#include "Value.h"
#include "Message.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This class encapsulates a replay. It has basic functions for writing messages to 
	 * a replay file and reading and sending messages from a replay file. 
	 */
	class MYOUSHU_API Replay : public NamedInstance, public NamedObject<Replay>, public Poco::RefCountedObject
	{
		public:
			/** 
			 * Constructor.
			 * @param name The name of the replay (base file name).
			 */
			Replay(const std::string& name = "Replay");

			/**
			 * Constructor. Either opens the replay for reading or opens it for writing. By default it
			 * opens the replay for reading.
			 * @param name The name of the replay (base file name).
			 * @param group The resource group the replay should be/is in.
			 * @param openForWriting If this is true the replay is opened for reading instead of writing.
			 */
			Replay(const std::string& name, const std::string& group, bool openForWriting = false);

			/** Destructor */
			virtual ~Replay();

			CLASS_NAME_FUNCTIONS(Replay);

			/** 
			 * Opens the replay file for writing.  The filename of the replay is based on the name of this instance.
			 * If the file does not exist it will be created.
			 * @param overwrite If the the file exists, and this flag is true, it will
			 *					be overwritten. If the flag is false, data will only be
			 *					appended.
			 * @param group The resource group the replay should be in. This determines where the file will be saved.
			 */
			virtual void openForWriting(const std::string& group = "", bool overwrite = true) throw (Exception);

			/** 
			 * Opens the replay file for playback. The filename of the replay is based on the name of this instance.
			 * @param group The resource group the replay is in. This determines where to look for the file.
			 */
			virtual void openForPlayback(const std::string& group) throw (Exception);

			/**
			 * Appends a timestamped Message to the end of the replay file.
			 * @param timestamp The timestamp
			 * @param message The Message to serialize and append to the replay file.
			 * @throw Exception::E_FILE_NOT_OPEN if the file is not open (i.e. openForWriting() has not been called).
			 */
			virtual void write(unsigned int timestamp, const Message& message) throw (Exception);

			/** 
			 * Sends all relevant messages for the replay. See also reset().
			 * @param timeDelta The time that has passed since the last call to this function.
			 * @return true if the replay is not finished yet, false if the replay is finished.
			 */
			virtual bool play(unsigned long timeDelta) throw (Exception);

			/** Call this function before the first call to play() when playing back a replay. */
			virtual void reset();

			/** Close any open streams for reading and writing. */
			virtual void close();

			/**
			 * Unimplemented.
			 * @throws Exception::E_UNIMPLEMENTED
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception);

			/**
			 * Unimplemented.
			 * @throws Exception::E_UNIMPLEMENTED
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception);

		protected:
			/** The Timestamp string as it is saved to the replay file to indicate timestamp values. */
			static const std::string TIMESTAMP_STRING;
			/** 
			 * The string used to indicate that the replay does not contain the initial state of the
			 * random number generator.
			 */
			static const std::string NO_RANDOM_STRING;

			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** Ogre::DataStream pointer used to read replay data from during playback. */
			Ogre::DataStreamPtr mpInputStream;
			/** Output stream that is used to write replay data to. */
			std::ofstream mOutputStream;
			/** The accumulated time that the replay has been playing. */
			unsigned long mAccumulatedPlayTime;
			/** Previous timestamp, used when recording/writing */
			unsigned long mPreviousTimestamp;
			/** A temporary buffer used when writing a replay */
			char *pBuffer;
			/** A flag indicating whether the random number generator state has been saved or loaded when
			 * recording or playing back a replay.
			 */
			bool mRandomStateProcessed;

	}; // class Replay

} // namespace Myoushu

#endif

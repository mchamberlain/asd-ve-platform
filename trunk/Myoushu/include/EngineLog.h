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
 * @file EngineLog.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef ENGINELOG_H
#define ENGINELOG_H

#include <sstream>
#include <fstream>
#include <string>

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "OutputStream.h"

/**
 * Logs a message of the specified type in a thread safe manner.
 * @param messageType The log message type, defined in EngineLog.
 * @param msg The message to log. It can be in stream format, i.e. "test " << var1 << " etc."
 */
#define LOG(messageType, msg) \
Myoushu::EngineLog::getSingleton().getPublicLock().writeLock(); \
Myoushu::EngineLog::getSingleton().messageStart(messageType); \
Myoushu::EngineLog::getSingleton() << msg; \
Myoushu::EngineLog::getSingleton().messageEnd(); \
Myoushu::EngineLog::getSingleton().getPublicLock().unlock();

// Define a LOG_DEBUG macro for logging that should only happen in debug
// mode
#ifdef MYOUSHU_DEBUG
#	define LOG_DEBUG(messageType, msg) LOG(messageType, msg)
#else
#	define LOG_DEBUG(messageType, msg)
#endif

namespace Myoushu
{
	/** A simple text file logger. */

	class MYOUSHU_API EngineLog : public OutputStream, public Ogre::Singleton<EngineLog>
	{
		public:
			/** The various log message types. */
			enum LogMessageType
			{
				/** An informational message from the engine */
				LM_INFO_ENGINE = 0,
				/** An informational message from the application using the engine. */
				LM_INFO_APPLICATION,
				/** A warning */
				LM_WARNING,
				/** A error message, could be fatal. */
				LM_ERROR
			};

			/**
			 * Constructor
			 * @param secondaryStream Defaults to NULL. If non NULL all log messages are outputted
			 * to this stream as well.
			 */
			EngineLog(OutputStream *secondaryStream = NULL);

			/**Destructor */
			~EngineLog();

			/**
			 * Set the secondary stream of the logger.
			 * @param secondaryStream The new secondaryStream, can be NULL.
			 */
			inline void setSecondaryStream(OutputStream *secondaryStream)
			{
				this->secondaryStream = secondaryStream;
			}

			/** Get the currently set log message type. */
			inline LogMessageType getMessageType() const {
				// Acquire a read lock
				Poco::ScopedRWLock lock(rwLock, false);

				return messageType;
			}

			/** Set the LogMessageType to be used by future messages that are logged.
			 * @param messageType The new LogMessageType.
			 */
			inline void setMessageType(LogMessageType messageType)
			{
				Poco::ScopedRWLock lock(rwLock, true);

				this->messageType = messageType;
			}

			/**
			 * Returns the public read write lock that threads can use to get
			 * exclusive access to the EngineLog Singleton.
			 * @return The public Poco::RWLock reference.
			 */
			inline Poco::RWLock& getPublicLock() const
			{
				return publicLock;
			}

			/**
			 * Writes the time and the message type to the log file.
			 * @param messageType The type of message.
			 */
			void messageStart(LogMessageType messageType);

			/**
			 * Writes the time and the message type to the log file.
			 * Uses the messageType member variable to determine the message type.
			 */
			void messageStart();

			/**
			 * Writes the time and the message type to the log file.
			 */
			void messageEnd();

		private:
			/** A mutex that can be used by threads to get an exclusive lock on the
			 * entire EngineLog Singleton.
			 */
			mutable Poco::RWLock publicLock;
			/** The current log message type. */
			LogMessageType messageType;
			/** Log file stream */
			std::ofstream logFile;
			/** The secondary output stream */
			OutputStream *secondaryStream;
			/** Temporary stringstream */
			std::ostringstream tempStream;
	};
} // namespace Mysoushu

#endif

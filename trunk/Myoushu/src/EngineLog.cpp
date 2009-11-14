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
 * @file EngineLog.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

#include "Poco/RWLock.h"

#include "EngineLog.h"
#include "Constants.h"

//template<>
//Myoushu::EngineLog* Ogre::Singleton<Myoushu::EngineLog>::ms_Singleton = NULL;

namespace Myoushu
{

/****************************************************************************/
	EngineLog::EngineLog(OutputStream *secondaryStream) : OutputStream(tempStream),
	messageType(LM_INFO_ENGINE), logFile(Constants::LOG_FILENAME.c_str(), std::ios_base::out),
	secondaryStream(secondaryStream), tempStream()
	{
		// Clear tempStream
		tempStream.str("");

		//Append a separator line to the log file so that every run of the engine has a separator
		tempStream << std::endl << "/****************************************************************************/" << std::endl << std::endl;
	}

/****************************************************************************/
	EngineLog::~EngineLog()
	{
		logFile.close();
	}

/****************************************************************************/
	void EngineLog::messageStart(LogMessageType messageType) {
		struct tm *timeStruct;
		time_t tt;

		Poco::ScopedRWLock lock(rwLock, true);

		// First add the time to the message
		tt = time(NULL);
		// We don't have to free timeStruct, localtime writes to a static buffer that could potentially
		// be overwritten by some other function, yikes!
		timeStruct = localtime(&tt);
		tempStream << timeStruct->tm_mday << "-" << timeStruct->tm_mon + 1 << "-" << timeStruct->tm_year + 1900 << " "
							 << timeStruct->tm_hour << ":" << timeStruct->tm_min << ":" << timeStruct->tm_sec << " ";

		switch (messageType)
		{
			case LM_INFO_ENGINE:
				tempStream << "Info_Engine: ";
			break;
			case LM_INFO_APPLICATION:
				tempStream << "Info_Application: ";
			break;
			case LM_WARNING:
				tempStream << "WARNING: ";
			break;
			case LM_ERROR:
				tempStream << "ERROR: ";
			break;
			default:
				tempStream << "Unknown message type: ";
			break;
		}
	}

/****************************************************************************/
	void EngineLog::messageStart() {
		LogMessageType messageType;

		// Get a read lock to read the messageType member variable.
		// Can't lock the entire function since that will cause dead lock when
		// messageStart(messageType) is called.
		rwLock.readLock();
		messageType = this->messageType;
		rwLock.unlock();

		this->messageStart(messageType);
	}

/****************************************************************************/
	void EngineLog::messageEnd() {
		std::string logStr;

		Poco::ScopedRWLock lock(rwLock, true);

		tempStream << std::endl;

		// Ouput the log message to the default stream
		logStr = tempStream.str();
		logFile << logStr;
		logFile.flush();

		// If a secondary stream is defined, output the message there as well
		if (secondaryStream != NULL)
		{
			(*secondaryStream) << logStr;
		}

		// Clear tempStream
		tempStream.str("");
	}

} // Myoushu

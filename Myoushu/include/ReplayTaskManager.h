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
 * @file ReplayTaskManager.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef REPLAY_TASK_MANAGER_H
#define REPLAY_TASK_MANAGER_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Constants.h"
#include "Exception.h"
#include "Replay.h"

namespace Myoushu
{
	/**
	 * This is a helper class for managing the ReplayTask.
	 */
	class MYOUSHU_API ReplayTaskManager : public Ogre::Singleton<ReplayTaskManager>
	{
		public:
			/** Constructor */
			ReplayTaskManager();

			/** Destructor */
			~ReplayTaskManager();

			/**
			 * Plays a replay. If the replay with the supplied name could not be found, an exception
			 * is thrown.
			 * @param replayName The name of the replay. This must be the base file name, without extension.
			 * @param group The OGRE resource group that contains the replay (this determines the location on the harddrive).
			 * @throws Exception::E_FILE_NOT_FOUND if the replay could not be found.
			 */
			virtual void play(const std::string& replayName, const std::string& group) throw (Exception);

			/**
			 * Plays a replay.
			 * @param pReplay The Replay in question.
			 * @throws Exception::E_NULL_POINTER if pReplay is NULL.
			 */
			virtual void play(Replay *pReplay) throw (Exception);

			/**
			 * Start recording a replay. The overwrite flag is used to determine whether an existing reply should
			 * be overwritten or not.
			 * @param replayName The name of the replay. This must be the base file name, without extension.
			 * @param group The OGRE resource group that will contain the replay (this determines the location on the harddrive).
			 * @param overwrite If true any existing file with the same name will be overwritten.
			 * @throws Exception::E_FILE_NOT_FOUND if the replay could not be found.
			 */
			virtual void record(const std::string& replayName, const std::string& group, bool overwrite = true) throw (Exception);

			/**
			 * Records a replay.
			 * @param pReplay The Replay in question.
			 * @param overwrite If true any existing file with the same name will be overwritten.
			 * @throws Exception::E_NULL_POINTER if pReplay is NULL.
			 */
			virtual void record(Replay *pReplay, bool overwrite = true) throw (Exception);

			/** Pause the currently playing or recording replay, if any. */
			virtual void pause();

			/** Stop the currently playing or recording replay, if any. */
			virtual void stop();

	}; // class ReplayTaskManager
} // namespace

#endif

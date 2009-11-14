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
 * @file ReplayTask.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef REPLAY_TASK_H
#define REPLAY_TASK_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Task.h"
#include "Exception.h"
#include "ReplayMessage.h"
#include "InputMessage.h"
#include "Replay.h"

namespace Myoushu
{

	/**
	 * This Task records activities taking place in the engine. These recordings can then be played
	 * back at a later stage.
	 */
	class MYOUSHU_API ReplayTask : public NamedObject<ReplayTask>, public Task
	{
		public:
			/**
			 * Constructor.
			 * @param priority The priority of the Task.
			 * @param name The name of the Task.
			 * @param executionInterval The amount of time, in microseconds, between executions of this Task. 
			 *							To execute in every frame use 0. Defaults to 0. To execute twice
			 *							a second use 500000 for instance.
			 * @param iterationLimit If the task misses its executionInterval, iterationLimit controls how many
			 *						 extra executions of the Task will be performed to catch up. Task that are
			 *						 slow and computationally expensive should not set this limit higher than one
			 *						 since it will slow the engine down if it cannot consistently run the task at
			 *						 its intervals. Higher iterationLimits are meant for lighter
			 *						 but important tasks, like game logic updates.
			 */
			ReplayTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			ReplayTask();

			/** Destructor. */
			~ReplayTask();

			CLASS_NAME_FUNCTIONS(ReplayTask);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method should sets the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Sets state to TS_KILLED.
			 */
			void kill();

			/** Returns true if the task is busy with replay playback. */
			bool getPlaying() const;

			/** Returns true if the task is busy recording a replay. */
			bool getRecording() const;

			/** Returns true if the replay recording/playback is paused. */
			bool getPaused() const;

			/** Returns the mpReplay instance */
			Replay* getReplay();

			/**
			 * Message handler function for ReplayMessage instances. ReplayMessages
			 * will control the state of the ReplayTask, i.e. recording/playback pause, stop
			 * resume etc.
			 * @param message The ReplayMessage that was received by this instance.
			 */
			void receiveReplayMessage(const Poco::AutoPtr<ReplayMessage>& message);

			/**
			 * Message handler function for InputMessage instances. When the replay task
			 * is recording, it will register to receive InputMessages. These messages will
			 * be serialised, timestamped and then saved.
			 * @param message The InputMessage that was received.
			 */
			void receiveInputMessage(const Poco::AutoPtr<InputMessage>& message);

		protected:
			/** Flag indicating whether the task is playing a replay. */
			bool mPlaying;
			/** Flag indicating whether the task is recording a replay. */
			bool mRecording;
			/** 
			 * Flag indicating whether the task is paused (looking at mPlaying and mRecording will
			 * inform us as to whether the task was playing or recording a replay when it was paused.
			 */
			bool mPaused;
			/** The Replay instance used for recording or playback. */
			Replay *mpReplay;
			/** The accumulated time that the replay has been playing/recording */
			unsigned long mAccumulatedTime;

			/** Called internally to pause recording/playback */
			void pause();

			/** Called internally to resume recording/playback */
			void resume();

			/** Called internally to stop recording/playback. */
			void stop();
	};

	//inlines
	inline bool ReplayTask::getPlaying() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mPlaying;
	}

	inline bool ReplayTask::getRecording() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mRecording;
	}

	inline bool ReplayTask::getPaused() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mPaused;
	}

	inline Replay* ReplayTask::getReplay()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mpReplay;
	}

} // Myoushu

#endif

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
 * @file ReplayTask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include "ReplayTask.h"
#include "Constants.h"
#include "EngineLog.h"
#include "Exception.h"
#include "NotificationManager.h"
#include "ReplayFactory.h"

#define REPLAY_TASK_BUFFER_SIZE 1024

namespace Myoushu
{
	CLASS_NAME(ReplayTask, "Myoushu::ReplayTask");

	ReplayTask::ReplayTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
		, mPlaying(false), mRecording(false), mPaused(false), mpReplay(NULL), mAccumulatedTime(0)
	{
	}

	ReplayTask::ReplayTask() : Task(0), mPlaying(false), mRecording(false), mPaused(false), mpReplay(NULL), mAccumulatedTime(0)
	{
	}

	ReplayTask::~ReplayTask()
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		NotificationManager::getSingleton().removeQueue(reinterpret_cast<memUInt>(this));
	}

	void ReplayTask::init() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "Initializing ReplayTask.");

		NotificationManager::getSingleton().addObserver(this, &ReplayTask::receiveReplayMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_INITIALIZED;
	}

	void ReplayTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void ReplayTask::execute(unsigned long timeDelta)
	{
		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		if ((mPlaying) || (mRecording))
		{
			Poco::ScopedRWLock lock(rwLock, true);

			mAccumulatedTime += timeDelta;
		}

		// Tell the NotificationManager to deliver all queued messages for this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

		rwLock.readLock();
		if (!mPaused)
		{
			if ((mPlaying) && (mpReplay != NULL))
			{
				try
				{
					if (!mpReplay->play(timeDelta))
					{
						// We have reached the end of the replay
						rwLock.unlock();
						stop();
						rwLock.readLock();
					}
				}
				catch (Exception &e)
				{
					// Error during playback, stop playback and log error
					LOG(EngineLog::LM_ERROR, "ReplayTask::execute(): error while playing replay: " << e.getMsg());
					rwLock.unlock();
					stop();
					rwLock.readLock();
				}
			}

			rwLock.unlock();
		}
	}

	void ReplayTask::kill()
	{
		NotificationManager::getSingleton().removeObserver(this, &ReplayTask::receiveReplayMessage);

		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void ReplayTask::pause()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (((mPlaying) || (mRecording)) && (!mPaused))
		{
			mPaused = true;
			if (mRecording)
			{
				// Unregister to receive messages, we ignore all activity while recording is paused
				NotificationManager::getSingleton().removeObserver(this, &ReplayTask::receiveInputMessage);
			}
		}
	}

	void ReplayTask::resume()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (mPaused)
		{
			mPaused = false;
			if (mRecording)
			{
				// Register to receive messages again, so that we can continue recording
				NotificationManager::getSingleton().addObserver(this, &ReplayTask::receiveInputMessage);
			}
		}
	}

	void ReplayTask::stop()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if ((mRecording) && (!mPaused))
		{
			// Unregister to receive messages, we ignore all activity while recording is paused
			NotificationManager::getSingleton().removeObserver(this, &ReplayTask::receiveInputMessage);
		}

		if (mpReplay != NULL)
		{
			mpReplay->close();
			mpReplay = NULL;
		}

		// Set the accumulated time to zero
		mAccumulatedTime = 0;
		mPlaying = false;
		mRecording = false;
		mPaused = false;
	}

	void ReplayTask::receiveReplayMessage(const Poco::AutoPtr<ReplayMessage>& message)
	{
		// Check that message is not null
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "ReplayTask::receiveReplayMessage(): message is NULL!");
			return;
		}

		switch (message->getMessageType())
		{
			case ReplayMessage::RM_START_RECORDING:
				{
					// Stop any recording or playback
					stop();

					Poco::ScopedRWLock lock(rwLock, true);

					// Set the accumulated time to zero
					mAccumulatedTime = 0;
					mRecording = true;
					// Register to receive messages to record
					NotificationManager::getSingleton().addObserver(this, &ReplayTask::receiveInputMessage);
					// Get the Replay instance
					mpReplay = ReplayFactory::getSingleton().findByName(message->getReplayName());
				}
				break;
			case ReplayMessage::RM_START_PLAYBACK:
				{
					// Stop any recording or playback
					stop();

					Poco::ScopedRWLock lock(rwLock, true);

					// Set the accumulated time to zero
					mAccumulatedTime = 0;
					mPlaying = true;
					// Set the name of the replay to play
					mpReplay = ReplayFactory::getSingleton().findByName(message->getReplayName());
				}
				break;
			case ReplayMessage::RM_STOP:
				// Stop any recording or playback
				stop();
				break;
			case ReplayMessage::RM_PAUSE:
				pause();
				break;
			case ReplayMessage::RM_RESUME:
				resume();
				break;
			case ReplayMessage::RM_UNKNOWN:
			default:
				LOG(EngineLog::LM_WARNING, "ReplayTask::receiveReplayMessage(): unknown message received.");
				break;
		}
	}

	void ReplayTask::receiveInputMessage(const Poco::AutoPtr<InputMessage>& message)
	{
		// Check that message is not null
		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "ReplayTask::receiveInputMessage(): message is NULL!");
			return;
		}

		if ((!mRecording) || (mPaused))
		{
			LOG(EngineLog::LM_WARNING, "ReplayTask::receiveInputMessage(): received InputMessage while paused or not recording...");

			return;
		}

		try
		{
			// Get the timestamp and write the message to the replay using the Replay instance
			mpReplay->write(mAccumulatedTime, *message);
		}
		catch (Exception &e)
		{
			LOG(EngineLog::LM_ERROR, "ReplayTask::receiveInputMessage(): error writing to replay file: " << e.getMsg());
		}
	}

} // Myoushu

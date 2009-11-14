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
 * @file VideoTask.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef VIDEO_TASK_H
#define VIDEO_TASK_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Ogre.h"
#include "OgreTextAreaOverlayElement.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Task.h"
#include "Exception.h"
#include "VideoTaskMessage.h"

namespace Myoushu
{

	/**
	 * This Task renders the scene, and controls the render window.
	 */
	class MYOUSHU_API VideoTask : public NamedObject<VideoTask>, public Task
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
			VideoTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			VideoTask();

			/** Destructor. */
			~VideoTask();

			CLASS_NAME_FUNCTIONS(VideoTask);

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

			/** 
			 * Returns a string with the minimum, maximum, average and current frame rate. 
			 * @param cumulativeDelta The time difference between the current and previous call to this function, in milliseconds.
			 */
			std::string VideoTask::getFPSStatsString(unsigned long cumulativeDelta);

			/** Handler function for receving VideoTaskMessage instances. */
			void receiveVideoTaskMessage(const Poco::AutoPtr<VideoTaskMessage>& pMessage) throw (Exception);

		protected:
			/** The time between updates to the FPS status string, in milliseconds. */
			static const unsigned int TIME_BETWEEN_FPS_UPDATES_IN_MILLIS;
			/** An overlay for displaying FPS stats. */
			Ogre::Overlay *mpFPSOverlay;
			/** An overlay container that will contain the FPS text area overlay element. */
			Ogre::OverlayContainer *mpFPSContainer;
			/** Pointer to an Ogre::TextAreaOverlayElement used to display frame rate statistics. */
			Ogre::TextAreaOverlayElement *mpFPSTextArea;
			/** The last timestamp, in milliseconds, at which the fps string was updated. */
			unsigned long mFPSLastUpdateTime;
			/** The frame number of the previous frame in which the fps string was updated. */
			unsigned long mLastUpdateFrameNumber;
			/** The number of frames that has been rendered by this task. */
			unsigned long mFrameCnt;

			/** Creates the Ogre::Overlay for displaying frame rate statistics. */
			void createFPSOverlay();
	};
} // Myoushu

#endif

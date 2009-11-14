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
 * @file OgreOggSoundTask.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_OGRE_OGG_SOUND_TASK_H
#define MYOUSHU_OGRE_OGG_SOUND_TASK_H

#include "OgreOggSound.h"

#include "ConcurrentTask.h"

#include "MyoushuOgreOggSoundPlatform.h"

namespace Myoushu
{
	/**
	 * An extension of ConcurrentTask, the OgreOggSoundTask manages sounds in the engine. This default implementation
	 * uses the OgreOggSound plugin for the Ogre engine to manage sound.
	 */
	class MYOUSHU_OGRE_OGG_SOUND_API OgreOggSoundTask : public ConcurrentTask, public NamedObject<OgreOggSoundTask>
	{
		public:
			/** Constructor.
			 * @param name The name of the instance.
			 * @param priority The priority of the task in the Kernel.
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
			OgreOggSoundTask(const std::string& name, int priority, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Destructor.
			 */
			~OgreOggSoundTask();

			CLASS_NAME_FUNCTIONS(OgreOggSoundTask);

			/**
			 * Initializes the task.
			 */
			virtual void init() throw (Exception);

			/**
			 * Suspend the Task. This method should set the TaskState to TS_SUSPENDED.
			 */
			virtual void suspend();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			virtual void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Should set state to TS_KILLED.
			 */
			virtual void kill();

			/**
			 * This is the main execution area of the thread. The current execution of the
			 * thread takes place in the function.
			 */
			 virtual void run();

		protected:
			/** The OgreOggSoundManager instance that manages the sound hardware. */
			OgreOggSound::OgreOggSoundManager *mpOgreOggSoundManager;
	};
} // Myoushu

#endif

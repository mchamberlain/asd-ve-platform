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
 * @file AnimationTask.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef ANIMATION_TASK_H
#define ANIMATION_TASK_H

#include <string>
#include <map>
#include <set>

#include "Poco/AutoPtr.h"
#include "Ogre.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Task.h"
#include "Exception.h"
#include "AnimationTaskMessage.h"
#include "FunctorBase.h"

namespace Myoushu
{
	/**
	 * This class manages a timer and sends messages to other Tasks about the time that has
	 * passed since the last execution phase. (Time between frames basically)
	 */
	class MYOUSHU_API AnimationTask : public NamedObject<AnimationTask>, public Task
	{
		public:
			/** Type definition for the value entries in the map, an animation state and a play counter. */
			typedef std::pair<Ogre::AnimationState*, unsigned int> AnimationMapValueEntry;
			/** Type definition for the map of animation addresses to animation pointers. */
			typedef std::map<memUInt, AnimationMapValueEntry> AnimationMap;
			/** Type definition for the iterator of the map of addresses to animation pointers. */
			typedef AnimationMap::iterator AnimationMapIterator;
			/** Type defintion for the entries in the map */
			typedef std::pair<memUInt, AnimationMapValueEntry> AnimationMapEntry;
			/** Type definition of an animation address to a callback functor. */
			typedef std::map<memUInt, FunctorBase*> AnimationCallbackMap;
			/** Type defintion of an entry in AnimationCallbackMap. */
			typedef AnimationCallbackMap::value_type AnimationCallbackMapEntry;

			/** Constructor.
			 * @param priority The priority of the task.
			 * @param name The name of the instance.
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
			AnimationTask(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			AnimationTask();

			/** Destructor */
			~AnimationTask();

			CLASS_NAME_FUNCTIONS(AnimationTask);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method should set the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Kill the task. Should set state to TS_KILLED.
			 */
			void kill();

			/**
			 * Execute one iteration of the task.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Method for handling AnimationTaskMessages sent to this instance.
			 * @param message The AnimationTaskMessage to process.
			 */
			void receiveAnimationTaskMessage(const Poco::AutoPtr<AnimationTaskMessage>& message);

		protected:
			/** Calls a callback for the supplied animation from the supplied AnimationCallbackMap. */
			void callCallback(Ogre::AnimationState *pAState, AnimationCallbackMap *pCallbackMap);

		private:
			/** Read/write mutex for thread safety on the activeAnimations map. */
			mutable Poco::RWLock mRWLockActiveAnimations;
			/** Read/write mutex for thread safety on the callbacks maps. */
			mutable Poco::RWLock mRWLockCallbacks;
			/** Map of active animations */
			AnimationMap activeAnimations;
			/** Map of callbacks to call when for an animation when it starts playing. */
			AnimationCallbackMap mStartCallbacks;
			/** Map of callbacks to call when for an animation when it stops playing. */
			AnimationCallbackMap mStopCallbacks;
			/** The set of animation addresses of animations starting in the next call to execute. */
			std::set<memUInt> mStartingAnimations;
	};
} // Myoushu

#endif


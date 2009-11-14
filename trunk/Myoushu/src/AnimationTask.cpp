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
 * @file AnimationTask.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "AnimationTask.h"
#include "EngineLog.h"
#include "NotificationManager.h"
#include "Constants.h"

namespace Myoushu
{
	CLASS_NAME(AnimationTask, "Myoushu::AnimationTask");

	AnimationTask::AnimationTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
	{
	}

	AnimationTask::AnimationTask() : Task(0)
	{
	}

	AnimationTask::~AnimationTask()
	{
		// Remove any message queues associated with this instance
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void AnimationTask::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Add an observer for AnimationTaskMessages to this instance
		NotificationManager::getSingleton().addObserver(this, &AnimationTask::receiveAnimationTaskMessage);

		state = TS_INITIALIZED;
	}

	void AnimationTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Remove message observer
		NotificationManager::getSingleton().removeObserver(this, &AnimationTask::receiveAnimationTaskMessage);

		state = TS_SUSPENDED;
	}

	void AnimationTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_KILLED;
	}

	void AnimationTask::callCallback(Ogre::AnimationState *pAState, AnimationCallbackMap *pCallbackMap)
	{
		AnimationCallbackMap::iterator callbackIter;
		FunctorBase *pFunctor;
		Value val;

		// If the animation has ended and it has a stop callback functor, call it
		Poco::ScopedRWLock lock(mRWLockCallbacks, false);

		callbackIter = pCallbackMap->find(reinterpret_cast<memUInt>(pAState));
		if (callbackIter != pCallbackMap->end())
		{
			pFunctor = callbackIter->second;
			if (pFunctor != NULL)
			{
				// Lua callbacks use different setParameter function
				if (pFunctor->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
				{
					LuaFunctor<void, 2, Ogre::AnimationState*, bool> *pLuaFunctor = static_cast<LuaFunctor<void, 2, Ogre::AnimationState*, bool>* >(pFunctor);
					pLuaFunctor->setParameter1(pAState);
					pLuaFunctor->setParameter2(pAState->getLoop());
				}
				else
				{
					val.set(reinterpret_cast<void*>(pAState));
					pFunctor->setParameter(0, val);
					val.set(static_cast<char>(pAState->getLoop()));
					pFunctor->setParameter(1, val);
				}
				(*pFunctor)();
			}
		}
	}

	void AnimationTask::execute(unsigned long timeDelta)
	{
		double deltaSec;
		std::list<memUInt> finishedAnimations;
		std::list<memUInt>::iterator finishedAnimationsIter;
		AnimationMapIterator iter;
		Value val;

		if (getState() != TS_RUNNING)
		{
			setState(TS_RUNNING);
		}

		// Dispatch all waiting messages of this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

		deltaSec = ((double) timeDelta) / MICROSECONDS_IN_SECOND;

		{
			Poco::ScopedRWLock lock(mRWLockActiveAnimations, false);
			// Update animations
			for (iter = activeAnimations.begin(); iter != activeAnimations.end(); ++iter)
			{
				AnimationMapValueEntry entry = iter->second;
				Ogre::AnimationState *animationState = entry.first;

				// Check if the animation has ended, and add it to a list of animations to be removed from the active list
				if ((animationState->hasEnded()) || (!animationState->getEnabled()))
				{
					finishedAnimations.push_back(iter->first);
					animationState->setEnabled(false);

					// If the animation has a stop callback, call it
					callCallback(animationState, &mStopCallbacks);
				}
				else
				{
					// Add the time since the last update to the animation
					animationState->addTime(deltaSec);

					// Check if this animation is just starting, if it is call its start callback
					if (mStartingAnimations.erase(reinterpret_cast<memUInt>(animationState)) == 1)
					{
						callCallback(animationState, &mStartCallbacks);
					}
				}
			}
		}

		mStartingAnimations.clear();

		{
			Poco::ScopedRWLock lock(mRWLockActiveAnimations, true);
			Poco::ScopedRWLock lockCallbacks(mRWLockCallbacks, true);

			// Remove the animations that have ended from the list of active animations
			for (finishedAnimationsIter = finishedAnimations.begin(); finishedAnimationsIter != finishedAnimations.end(); ++finishedAnimationsIter)
			{
				memUInt animationAddress = *finishedAnimationsIter;
				activeAnimations.erase(animationAddress);

				// Remove any callbacks associated with this animation
				mStartCallbacks.erase(animationAddress);
				mStopCallbacks.erase(animationAddress);
			}
		}
	}

	void AnimationTask::receiveAnimationTaskMessage(const Poco::AutoPtr<AnimationTaskMessage>& message)
	{
		AnimationMapEntry entry;
		AnimationMapIterator iter;
		AnimationMapValueEntry valueEntry;
		Ogre::AnimationState *animation;
		memUInt animationAddress;
		FunctorBase *pFunctor;

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "AnimationTask::receiveAnimationTaskMessage(): message is NULL.");

			return;
		}

		Poco::ScopedRWLock lock(mRWLockActiveAnimations, true);

		animation = message->getAnimation();
		animationAddress = reinterpret_cast<memUInt>(animation);
		if (animation != NULL)
		{
			iter = activeAnimations.find(animationAddress); 
		}

		switch (message->getMessageType())
		{
			case AnimationTaskMessage::AM_ENABLE:
				// If the playCounter flag is true, increment the playCounter if the animation is active, other just start 
				// playing the animation if the counter is one.
				if ((message->isPlayCounter()) && (iter != activeAnimations.end()))
				{
					valueEntry = iter->second;
					valueEntry.second++;
				}
				else
				{
					// Set the loop, restart and enabled values for the animation
					animation->setLoop(message->isLoop());
					if (message->isRestart())
					{
						animation->setTimePosition(0.0f);
					}
					animation->setEnabled(true);

					valueEntry.first = animation;
					valueEntry.second = 1;
				}

				// Add this animations start and stop callbacks to the callback maps
				pFunctor = message->getStartCallback();
				if (pFunctor != NULL)
				{
					Poco::ScopedRWLock lock(mRWLockCallbacks, true);
					mStartCallbacks[animationAddress] = pFunctor;
				}
				pFunctor = message->getStopCallback();
				if (pFunctor != NULL)
				{
					Poco::ScopedRWLock lock(mRWLockCallbacks, true);
					mStopCallbacks[animationAddress] = pFunctor;
				}

				// Add it to the list of active animations
				activeAnimations[animationAddress] = valueEntry;

				// Add it to the set of starting animations
				mStartingAnimations.insert(animationAddress);
				break;

			case AnimationTaskMessage::AM_DISABLE:
				if (iter != activeAnimations.end())
				{
					// If the playCounter flag is true, decrement the playCounter if the animation is active, otherwise just stop 
					// playing the animation if the counter <= 0.
					if (message->isPlayCounter())
					{
						valueEntry = iter->second;
						valueEntry.second--;
						if (valueEntry.second == 0)
						{
							// Mark animation as disabled and remove it from the list
							// of active animations
							animation->setEnabled(false);
							activeAnimations.erase(animationAddress);
							// Remove any callbacks associated with this animation
							{
								Poco::ScopedRWLock lock(mRWLockCallbacks, true);
								mStartCallbacks.erase(animationAddress);
								mStopCallbacks.erase(animationAddress);
							}
						}
						else
						{
							activeAnimations[animationAddress] = valueEntry;
						}
					}
					else
					{
						// Mark animation as disabled and remove it from the list
						// of active transformations
						animation->setEnabled(false);
						activeAnimations.erase(animationAddress);
						// Remove any callbacks associated with this animation
						{
							Poco::ScopedRWLock lock(mRWLockCallbacks, true);
							mStartCallbacks.erase(animationAddress);
							mStopCallbacks.erase(animationAddress);
						}
					}
				}
				break;
			case AnimationTaskMessage::AM_DISABLE_ALL:
				{
					// Remove all active animations and their callbacks
					Poco::ScopedRWLock(mRWLockCallbacks, true);
					for (iter = activeAnimations.begin(); iter != activeAnimations.end(); ++iter)
					{
						animationAddress = iter->first;
						mStartCallbacks.erase(animationAddress);
						mStopCallbacks.erase(animationAddress);
					}
					activeAnimations.clear();
					mStartingAnimations.clear();
				}
				break;
		}
	}

} // namespace Myoushu

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
 * @file PhysicsTask.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "PhysicsTask.h"
#include "EngineLog.h"
#include "Constants.h"
#include "GlobalLocks.h"
#include "TimerTask.h"

namespace Myoushu
{
	CLASS_NAME(PhysicsTask, "Myoushu::PhysicsTask");

	PhysicsTask::PhysicsTask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit)
		, world(NULL), physXDriver(NULL), timeSinceLastStep(0)
	{
	}

	PhysicsTask::PhysicsTask() : Task("PhysicsTask", 0), world(NULL), physXDriver(NULL), timeSinceLastStep(0)
	{
	}

	PhysicsTask::~PhysicsTask()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		// Remove the message queue for this class
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void PhysicsTask::init() throw (Exception)
	{
		NxOgre::PhysXDriverParams params;

		Poco::ScopedRWLock lock(rwLock, true);

		// Disable use of the frame listener, and enable html logging
		params.setToDefault();
		params.useFrameListener = false;
		params.shutdownOnErrors = false;
		params.logtype = NxOgre::PhysXDriverParams::LT_HTML;

		try
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the Physics World.");
			// Create the physics universe
			world = new NxOgre::World(params);
			// Get the PhysXDriver instance
			physXDriver = world->getPhysXDriver();
			//physXDriver->getSDK()->setParameter(NX_CONTINUOUS_CD, 1.0f);
			// In DEBUG mode we create a link to the remote debugger
			#ifdef MYOUSHU_DEBUG
				physXDriver->createDebuggerConnection();
			#endif
		}
		catch (...)
		{
			throw Exception(Exception::E_GENERAL_EXCEPTION, "Error initializing NxOgre.");
		}

		// Register this class to receive timer message
		//NotificationManager::getSingleton().addObserver<PhysicsTask, TimerTaskMessage>(this, &PhysicsTask::receiveTimerTaskMessage);

		// Set the task state to initialized
		state = TS_INITIALIZED;
	}

	void PhysicsTask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void PhysicsTask::execute(unsigned long timeDelta)
	{
		double deltaSec;

		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}
		rwLock.unlock();
		
		Poco::ScopedRWLock lock(rwLock, false);

		// Receive any queued messages for this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

		if ((physXDriver) && (timeDelta > 0))
		{
			// Obtain a write lock on the physics system
			Poco::ScopedRWLock nxOgreLock(GlobalLocks::rwLockNxOgre, true);

			deltaSec = static_cast<double>(timeDelta) / MICROSECONDS_IN_SECOND;
			// Update the physics simulation
			physXDriver->simulate(deltaSec);
			physXDriver->render(deltaSec);
		}
	}

	void PhysicsTask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);
		Poco::ScopedRWLock nxOgreLock(GlobalLocks::rwLockNxOgre, true);

		// Unregister the class from receive timer messages
		//NotificationManager::getSingleton().removeObserver<PhysicsTask, TimerTaskMessage>(this, &PhysicsTask::receiveTimerTaskMessage);

		// In DEBUG mode we created a link to the remote debugger, so we must close it
		#ifdef MYOUSHU_DEBUG
			physXDriver->destroyDebuggerConnection();
		#endif

		if (world)
		{
			delete world;

			world = NULL;
			physXDriver = NULL;
		}

		state = TS_KILLED;
	}

	void PhysicsTask::receiveTimerTaskMessage(const Poco::AutoPtr<TimerTaskMessage>& message)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "PhysicsTask::receiveTimerTaskMessage(): NULL TimerTaskMessage received.");

			return;
		}

		switch (message->getMessageType())
		{
			case TimerTaskMessage::TM_UPDATE:
				// delta is in microseconds, we have to convert it to seconds
				timeSinceLastStep = ((Ogre::Real) message->getDelta()) / ((Ogre::Real) MICROSECONDS_IN_SECOND);
			break;
			default:
				LOG(EngineLog::LM_WARNING, "PhysicsTask::receiveTimerTaskMessage(): Unknown TimerTaskMessage received.");
			break;
		}
	}

} // Myoushu

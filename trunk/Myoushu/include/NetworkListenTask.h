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
 * @file NetworkListenTask.h
 * @author ME Chamberlain
 * @date November 2008
 */

#ifndef MYOUSHU_NETWORK_LISTEN_TASK
#define MYOUSHU_NETWORK_LISTEN_TASK

#include "Poco/Net/DatagramSocket.h"

#include "Platform.h"
#include "ConcurrentTask.h"
#include "Singleton.h"
#include "NetworkListenBehaviour.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * A concurrent task that listens for incoming messages over the network using the UDP protocol. Any received messages are handled by
	 * the currently defined NetworkListenBehaviour instance.
	 */
	class MYOUSHU_API NetworkListenTask : public ConcurrentTask, public Ogre::Singleton<NetworkListenTask>, public NamedObject<NetworkListenTask>
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
			NetworkListenTask(const std::string& name, int priority, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Destructor.
			 */
			~NetworkListenTask();

			CLASS_NAME_FUNCTIONS(NetworkListenTask);

			/**
			 * Sets the NetworkListenBehaviour instance used by this instance. This instance
			 * takes ownership of the specified NetworkListenBehaviour instance, and will free it
			 * when appropriate.
			 * @param listenBehaviour Pointer to the NetworkListenBehaviour instance to use. This instance
			 *						  takes ownership of the specified NetworkListenBehaviour instance, and will free it
			 *						  when appropriate.
			 */
			void setNetworkListenBehaviour(NetworkListenBehaviour *listenBehaviour);

			/** 
			 * Gets the NetworkListenBehaviour instance used by this instance. 
			 * The NetworkListenBehaviour instance must
			 * not be freed by users, this instance owns it and will free it when appropriate.
			 */
			NetworkListenBehaviour* getNetworkListenBehaviour();

			/** 
			 * Gets the NetworkListenBehaviour instance used by this instance. 
			 * The NetworkListenBehaviour instance must
			 * not be freed by users, this instance owns it and will free it when appropriate.
			 */
			const NetworkListenBehaviour* getNetworkListenBehaviour() const;

			/**
			 * Initializes the task.
			 */
			virtual void init() throw (Exception);

			/**
			 * Suspend the Task. This method sets the TaskState to TS_SUSPENDED.
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
			/** The datagram socket used to listen for incoming messages. */
			Poco::Net::DatagramSocket mListenSocket;
			/** Pointer to the NetworkListenBehaviour used by this task to process received messages. */
			NetworkListenBehaviour *mListenBehaviour;
	};

	// inlines
	inline void NetworkListenTask::setNetworkListenBehaviour(NetworkListenBehaviour *listenBehaviour)
	{
		// Check that listenBehaviour is not NULL
		if (listenBehaviour == NULL)
		{
			LOG(EngineLog::LM_ERROR, "NetworkListenTask::setNetworkListenBehaviour(): listenBehavior is NULL.");
			throw Exception(Exception::E_NULL_POINTER, "NetworkListenTask::setNetworkListenBehaviour(): listenBehaviour is NULL.");
		}

		Poco::ScopedRWLock lock(rwLock, true);

		// If there is an existing instance set in mListenBehaviour, free it
		if (mListenBehaviour != NULL)
		{
			delete mListenBehaviour;
		}

		mListenBehaviour = listenBehaviour;
	}

	inline NetworkListenBehaviour* NetworkListenTask::getNetworkListenBehaviour()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mListenBehaviour;
	}

	inline const NetworkListenBehaviour* NetworkListenTask::getNetworkListenBehaviour() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mListenBehaviour;
	}

}

#endif

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
 * @file NetworkTransmitTaskTCPTCP.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef MYOUSHU_NETWORK_TRANSMIT_TASK_TCP
#define MYOUSHU_NETWORK_TRANSMIT_TASK_TCP

#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "NetworkTransmitTask.h"
#include "NamedObject.h"
#include "NetworkMessage.h"

namespace Myoushu
{
	/**
	 * This task receives engine messages about data to transmit accross the network. When the execute function
	 * is called the task process any messages it has received and transmits it accross the network. This
	 * task uses the TCP protocol.
	 */
	class MYOUSHU_API NetworkTransmitTaskTCP : public NetworkTransmitTask, public NamedObject<NetworkTransmitTaskTCP>
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
			NetworkTransmitTaskTCP(int priority, const std::string& name, unsigned long executionInterval = 0, unsigned int iterationLimit = 1);

			/**
			 * Nullary Constructor.
			 */
			NetworkTransmitTaskTCP();

			/** Destructor */
			~NetworkTransmitTaskTCP();

			CLASS_NAME_FUNCTIONS(NetworkTransmitTaskTCP);

			/**
			 * Initializes the task.
			 */
			void init() throw (Exception);

			/**
			 * Suspend the Task. This method sets the TaskState to TS_SUSPENDED.
			 */
			void suspend();

			/**
			 * Execute one iteration of the task. Messages sent to this task via the NetworkManager is converted into messages that are sent
			 * over the network.
			 * @param timeDelta The time since last execution in microseconds.
			 */
			void execute(unsigned long timeDelta);

			/**
			 * Kill the task. Sets state to TS_KILLED.
			 */
			void kill();
	};

} // namespace Myoushu

#endif

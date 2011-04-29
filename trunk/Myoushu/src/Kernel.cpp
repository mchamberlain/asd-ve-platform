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
 * @file Kernel.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <list>
#include "assert.h"

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Ogre.h"

#include "Task.h"
#include "ConcurrentTask.h"
#include "Kernel.h"
#include "Exception.h"
#include "NotificationManager.h"
#include "KernelMessage.h"
#include "EngineLog.h"
#include "TimerTask.h"
#include "Constants.h"

//template <>
//Myoushu::Kernel* Ogre::Singleton<Myoushu::Kernel>::ms_Singleton = NULL;

namespace Myoushu
{
	Kernel::Kernel()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Set the execute variable to false.
		setExecuting(false);

		// Initialize the taskPoolChanged boolean
		setTaskPoolChanged(true);

		// Register the receiveMessage function of this instance to receive KernelMessages
		// sent via the Notification system.
		NotificationManager::getSingleton().addObserver(this, &Kernel::receiveMessage);
	}

	Kernel::~Kernel()
	{
		TaskPoolIter it;

		Poco::ScopedRWLock lock(rwLock, true);

		for (it = taskPool.begin(); it != taskPool.end(); )
		{
			if ((*it)->getState() != Task::TS_KILLED)
			{
				(*it)->kill();
			}
			it = taskPool.erase(it);
		}

		// Remove the KernelMessage observer
		NotificationManager::getSingleton().removeObserver(this, &Kernel::receiveMessage);
		// Remove the Kernel's NotificationQueue
		NotificationManager::getSingleton().removeQueue((memUInt) this);
	}

	void Kernel::addTask(Poco::AutoPtr<Task> task) throw (Exception)
	{
		TaskPoolIter it;
		bool inserted;

		Poco::ScopedRWLock lock(rwLock, true);

		inserted = false;

		if (task.get() == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Kernel::addTask: task pointer is null.");
		}

		// Task pool is changing, will differ from executePool
		setTaskPoolChanged(true);

		for (it = taskPool.begin(); (it != taskPool.end()) && (!inserted); ++it)
		{
			if (task->getPriority() < (*it)->getPriority())
			{
				taskPool.insert(it, task);
				inserted = true;
			}
		}

		if (!inserted)
		{
			taskPool.push_back(task);
		}
	}

	void Kernel::suspendTask(Poco::AutoPtr<Task> task) throw (Exception)
	{
		if (task.get() == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Kernel::suspendTask: task pointer is null.");
		}

		if (task->getState() != Task::TS_SUSPENDED)
		{
			task->suspend();
		}
	}

	Poco::AutoPtr<Task> Kernel::suspendTask(const std::string& name)
	{
		TaskPoolIter it;
		Poco::AutoPtr<Task> task;

		Poco::ScopedRWLock lock(rwLock, false);

		task = NULL;

		for (it = taskPool.begin(); it != taskPool.end(); ++it)
		{
			if ((*it)->getName() == name)
			{
				task = *it;
				if (task->getState() != Task::TS_SUSPENDED)
				{
					task->suspend();
				}

				break;
			}
		}

		return task;
	}

	void Kernel::removeTask(Poco::AutoPtr<Task> task) throw (Exception)
	{
		TaskPoolIter it;
		Poco::ScopedRWLock lock(rwLock, true);

		if (task.get() == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Kernel::removeTask: task pointer is null.");
		}

		for (it = taskPool.begin(); it != taskPool.end(); )
		{
			if (task == (*it))
			{

				if (task->getState() != Task::TS_KILLED)
				{
					task->kill();
				}
				// Task pool is changing, will differ from executePool
				setTaskPoolChanged(true);

				it = taskPool.erase(it);

				break;
			}
			else
			{
				it++;
			}
		}
	}

	Poco::AutoPtr<Task> Kernel::removeTask(const std::string& name)
	{
		TaskPoolIter it;
		Poco::AutoPtr<Task> task;

		Poco::ScopedRWLock lock(rwLock, true);

		task = NULL;

		for (it = taskPool.begin(); it != taskPool.end(); )
		{
			if ((*it)->getName() == name)
			{
				// Task pool is changing, will differ from executePool
				setTaskPoolChanged(true);

				task = *it;
				it = taskPool.erase(it);
				if (task->getState() != Task::TS_KILLED)
				{
					task->kill();
				}

				break;
			}
			else
			{
				it++;
			}
		}

		return task;
	}

	void Kernel::execute()
	{
		Task *task;
		TaskPoolIter it;
		unsigned long timeBetweenExecutions;
		unsigned long currentTimeInSec;
		unsigned long timeDelta;
		bool executed;

		setExecuting(true);

		do
		{
			NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

			if (isTaskPoolChanged())
			{
				// Set taskPoolChanged to false
				setTaskPoolChanged(false);

				// Acquire a write lock on the execute task list
				Poco::ScopedRWLock executeTaskListLock(rwLockExecuteTaskList, true);

				// Clear the list
				executeTaskList.clear();

				{
					// Acquire a read lock on the taskPool
					Poco::ScopedRWLock lock(rwLock, false);
					// Copy the taskPool to executeTaskList
					executeTaskList = taskPool;
				}
			}

			currentTimeInSec = 0;
			timeDelta = 0;

			{
				// Execute tasks from executeTaskList, this allows other operations (add/remove task etc. to
				// execute while the Kernel is executing tasks
				Poco::ScopedRWLock lock(rwLockExecuteTaskList, false);
				for (it = executeTaskList.begin(); it != executeTaskList.end(); ++it)
				{
					task = *it;

					if ((task->getState() == Task::TS_INITIALIZED) || (task->getState() == Task::TS_RUNNING))
					{
						if (task->getExecutionInterval() <= 0)
						{
							task->execute(timeDelta);
							if (task->getClassName() == NamedObject<TimerTask>::getStaticClassName())
							{
								// If this is the timer task, update the absolute running time of the engine
								currentTimeInSec = TimerTask::getSingleton().getAbsTime();
								// and the time between frames
								timeDelta = TimerTask::getSingleton().getDelta();
							}
							// Update the timeLastExecuted timestamp of the task.
							task->setTimeLastExecuted(currentTimeInSec);
						}
						else
						{
							// Calculte the time that has passed since this task was last executed
							timeBetweenExecutions = currentTimeInSec - task->getTimeLastExecuted();
							// In case the currentTimeInSec has wrapped around, we need to add 1 to timeBetweenExecutions
							if (currentTimeInSec < task->getTimeLastExecuted())
							{
								timeBetweenExecutions += 1ul;
							}

							executed = false;
							// If the timeBetweenExecutions is greater than or equal to the exectionInterval of the task, execute the task.
							// The Task is executed as many times as is needed until timeBetweenExecutions is less than the executionInterval.
							for (unsigned int iteration = 1; (timeBetweenExecutions >= task->getExecutionInterval()) && (iteration <= task->getIterationLimit()); iteration++)
							{
								if (!executed)
								{
									executed = true;
								}
								if (iteration != task->getIterationLimit())
								{
									task->execute(task->getExecutionInterval());

									// Update the time last executed incrementally. This is in case the execute function depends on the
									// timeLastExecuted field (It shouldn't it should only depend on executionInterval).
									task->setTimeLastExecuted(task->getTimeLastExecuted() + task->getExecutionInterval());
								}
								else
								{
									task->execute(timeBetweenExecutions);

									// Update the time last executed.
									task->setTimeLastExecuted(currentTimeInSec);
								}

								timeBetweenExecutions -= task->getExecutionInterval();
							}

							if (executed)
							{
								// Update the timeLastExecuted timestamp of the task.
								task->setTimeLastExecuted(currentTimeInSec);
							}
						}
					}
				}
			}

		} while (isExecuting());

		killAllTasks();
	}

	void Kernel::initAllTasks()
	{
		TaskPoolIter it;
		std::list<Poco::AutoPtr<Task> > tasksToRemove;

		Poco::ScopedRWLock lock(rwLock, false);
		tasksToRemove.clear();

		for (it = taskPool.begin(); it != taskPool.end(); ++it)
		{
			if ((*it)->getState() == Task::TS_CREATED)
			{
				// Try to initialise a task. If it fails, suspend the task. If that fails remove the task from
				// the kernel.
				try
				{
					(*it)->init();
				}
				catch (...)
				{
					LOG(EngineLog::LM_ERROR, "Error initialising task: " << (*it)->getName() << ", suspending task.");
					try
					{
						(*it)->suspend();
					}
					catch (...)
					{
						LOG(EngineLog::LM_ERROR, "Error suspending task: " << (*it)->getName() << ", removing task.");
						tasksToRemove.push_back(*it);
					}
				}
			}
		}

		// Remove the tasks that failed to initialise and failed to be suspended
		it = tasksToRemove.begin();
		while (it != tasksToRemove.end())
		{
			Poco::AutoPtr<Task>& task = *it;

			// Remove tasks from the list of tasks to remove and advance the iterator
			it = tasksToRemove.erase(it);
			// Remove the task from the kernel
			removeTask(task);
		}
	}

	void Kernel::killAllTasks()
	{
		TaskPoolIter it;

		Poco::ScopedRWLock lock(rwLock, false);

		for (it = taskPool.begin(); it != taskPool.end(); ++it )
		{
			if ((*it)->getState() != Task::TS_KILLED)
			{
				(*it)->kill();
			}
		}
	}

	void Kernel::startConcurrentTasks()
	{
		TaskPoolIter it;
		Poco::AutoPtr<ConcurrentTask> concurrentTask;

		Poco::ScopedRWLock lock(rwLock, false);

		for (it = taskPool.begin(); it != taskPool.end(); ++it)
		{
			concurrentTask = (*it).cast<ConcurrentTask>();

			if (concurrentTask.get() != NULL)
			{
				concurrentTask->start(*concurrentTask);
			}
		}
	}

	void Kernel::receiveMessage(const Poco::AutoPtr<KernelMessage>& message)
	{
		Poco::AutoPtr<Task> task;

		Poco::AutoPtr<KernelMessage>& kernelMessage = const_cast<Poco::AutoPtr<KernelMessage>& >(message);

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "Kernel received a NULL message.");

			return;
		}

		switch (message->getMessageType())
		{
			case KernelMessage::KM_SHUTDOWN:
				// We have to acquire a write lock on the executing's lock before we
				// can write to it.
				setExecuting(false);
			break;
			case KernelMessage::KM_ADD_TASK:
				// Add the Task to the Kernel
				addTask(kernelMessage->getTask());
			break;
			case KernelMessage::KM_REMOVE_TASK:
				// Check if the Task instance is given, or only the name
				task = kernelMessage->getTask();
				if (task.get() != NULL)
				{
					// Remove the Task using a pointer to it
					removeTask(task);
				}
				else
				{
					// Remove the Task by searching for it by name
					removeTask(kernelMessage->getTaskName());
				}
			break;
			case KernelMessage::KM_SUSPEND_TASK:
				// Check if the Task instance is given, or only the name
				task = kernelMessage->getTask();
				if (task.get() != NULL)
				{
					// Suspend the Task using a pointer to it
					suspendTask(task);
				}
				else
				{
					// Suspend the Task by searching for it by name
					suspendTask(kernelMessage->getTaskName());
				}
			break;
			case KernelMessage::KM_INIT_ALL_TASKS:
				// Initialize all the Tasks
				initAllTasks();
			break;
			default:
				LOG(EngineLog::LM_WARNING, "Kernel received an unknown message.");
			break;
		}
	}

} // Myoushu

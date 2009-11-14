/**
 * @file SampleNetwork.cpp
 * @author ME Chamberlain
 * @date August 2008
 */

#include "KernelManager.h"
#include "Constants.h"

#include "SampleNetwork.h"
#include "SampleNetworkGameTask.h"

SampleNetwork::SampleNetwork()
{
}

SampleNetwork::~SampleNetwork()
{
}

void SampleNetwork::start(int argc, char **argv)
{
	SampleNetworkGameTask *gameTask;

	// Initialize the Myoushu engine
	this->main(argc, argv);
	this->init();

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	// Create and add the SampleNetworkGameTask to the Kernel
	gameTask = new SampleNetworkGameTask(Myoushu::Constants::GAME_TASK_PRIORITY, "SampleNetworkGameTask"
		, Myoushu::Constants::GAME_TASK_EXECUTION_INTERVAL, Myoushu::Constants::GAME_TASK_ITERATION_LIMIT);
	Myoushu::KernelManager::getSingleton().addTask(gameTask);
	Myoushu::KernelManager::getSingleton().initAllTasks();

	this->run();
}

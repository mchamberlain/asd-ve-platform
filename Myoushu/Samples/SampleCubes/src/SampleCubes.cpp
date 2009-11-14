/**
 * @file SampleCubes.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "KernelManager.h"
#include "Constants.h"

#include "SampleCubes.h"
#include "SampleCubesGameTask.h"

SampleCubes::SampleCubes()
{
}

SampleCubes::~SampleCubes()
{
}

void SampleCubes::start(int argc, char **argv)
{
	SampleCubesGameTask *gameTask;

	// Initialize the Myoushu engine
	try
	{
		this->main(argc, argv);
		this->init();
	}
	catch (...)
	{
		return;
	}

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	// Create and add the SampleCubesGameTask to the Kernel
	gameTask = new SampleCubesGameTask(Myoushu::Constants::GAME_TASK_PRIORITY, "SampleCubesGameTask"
		, Myoushu::Constants::GAME_TASK_EXECUTION_INTERVAL, Myoushu::Constants::GAME_TASK_ITERATION_LIMIT);
	Myoushu::KernelManager::getSingleton().addTask(gameTask);
	Myoushu::KernelManager::getSingleton().initAllTasks();

	this->run();
}

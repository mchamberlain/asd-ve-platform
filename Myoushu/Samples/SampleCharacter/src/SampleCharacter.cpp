/**
 * @file SampleCharacter.cpp
 * @author ME Chamberlain
 * @date August 2008
 */

#include "KernelManager.h"
#include "Constants.h"

#include "SampleCharacter.h"
#include "SampleCharacterGameTask.h"

SampleCharacter::SampleCharacter()
{
}

SampleCharacter::~SampleCharacter()
{
}

void SampleCharacter::start(int argc, char **argv)
{
	SampleCharacterGameTask *gameTask;

	// Initialize the Myoushu engine
	this->main(argc, argv);
	this->init();

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	// Create and add the SampleCharacterGameTask to the Kernel
	gameTask = new SampleCharacterGameTask(Myoushu::Constants::GAME_TASK_PRIORITY, "SampleCharacterGameTask"
		, Myoushu::Constants::GAME_TASK_EXECUTION_INTERVAL, Myoushu::Constants::GAME_TASK_ITERATION_LIMIT);
	Myoushu::KernelManager::getSingleton().addTask(gameTask);
	Myoushu::KernelManager::getSingleton().initAllTasks();

	this->run();
}

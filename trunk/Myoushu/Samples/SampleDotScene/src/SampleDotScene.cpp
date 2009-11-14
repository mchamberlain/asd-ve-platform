/**
 * @file SampleDotScene.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "KernelManager.h"
#include "Constants.h"

#include "SampleDotScene.h"
#include "SampleDotSceneGameTask.h"

SampleDotScene::SampleDotScene()
{
}

SampleDotScene::~SampleDotScene()
{
}

void SampleDotScene::start(int argc, char **argv)
{
	SampleDotSceneGameTask *gameTask;

	// Initialize the Myoushu engine
	this->main(argc, argv);

	// Load the MyoushuDotScene plugin
	#if defined(_WIN32) || defined(_WIN64)
		#ifdef MYOUSHU_DEBUG
			loadPlugin("myoushuDotScene_d");
		#else
			loadPlugin("myoushuDotScene");
		#endif
	#else
		#ifdef MYOUSHU_DEBUG
			loadPlugin("libmyoushuDotScene_d");
		#else
			loadPlugin("libmyoushuDotScene");
		#endif
	#endif
	this->init();

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	// Create and add the SampleDotSceneGameTask to the Kernel
	gameTask = new SampleDotSceneGameTask(Myoushu::Constants::GAME_TASK_PRIORITY, "SampleDotSceneGameTask", Myoushu::Constants::GAME_TASK_EXECUTION_INTERVAL);
	Myoushu::KernelManager::getSingleton().addTask(gameTask);
	Myoushu::KernelManager::getSingleton().initAllTasks();

	this->run();
}

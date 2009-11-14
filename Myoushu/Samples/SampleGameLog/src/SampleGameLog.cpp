/**
 * @file SampleGameLog.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "KernelManager.h"
#include "ScriptManager.h"
#include "Constants.h"

#include "SampleGameLog.h"

SampleGameLog::SampleGameLog()
{
}

SampleGameLog::~SampleGameLog()
{
}

void SampleGameLog::start(int argc, char **argv)
{
	// Initialize the Myoushu engine
	this->main(argc, argv);
	this->init();

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	this->run();
}

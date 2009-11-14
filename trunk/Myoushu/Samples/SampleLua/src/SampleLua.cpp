/**
 * @file SampleLua.cpp
 * @author ME Chamberlain
 * @date June 2008
 */

#include "KernelManager.h"
#include "ScriptManager.h"
#include "Constants.h"

#include "SampleLua.h"

SampleLua::SampleLua()
{
}

SampleLua::~SampleLua()
{
}

void SampleLua::start(int argc, char **argv)
{
	// Initialize the Myoushu engine
	this->main(argc, argv);
	// Load the MyoushuOgreOggSound plugin
	#if defined(_WIN32) || defined(_WIN64)
		#ifdef MYOUSHU_DEBUG
			loadPlugin("myoushuOgreOggSound_d");
		#else
			loadPlugin("myoushuOgreOggSound");
		#endif
	#else
		#ifdef MYOUSHU_DEBUG
			loadPlugin("libmyoushuOgreOggSound_d");
		#else
			loadPlugin("libmyoushuOgreOggSound");
		#endif
	#endif
	this->init();

	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");
	// Schedule the main.lua script for execution
	Myoushu::ScriptManager::getSingleton().executeScriptFile("main.lua");

	this->run();
}

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
 * @file SocialSkills.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "KernelManager.h"
#include "ScriptManager.h"
#include "Constants.h"

#include "SocialSkills.h"

SocialSkills::SocialSkills()
{
}

SocialSkills::~SocialSkills()
{
}

void SocialSkills::start(int argc, char **argv)
{
	// Initialize the Myoushu engine
	this->main(argc, argv);

	// Load the ASTT plugin
	#if defined(_WIN32) || defined(_WIN64)
		#ifdef MYOUSHU_DEBUG
			loadPlugin("astt_d");
			loadPlugin("MyoushuDotScene_d");
			loadPlugin("myoushuOgreOggSound_d");
		#else
			loadPlugin("astt");
			loadPlugin("MyoushuDotScene");
			loadPlugin("myoushuOgreOggSound");
		#endif
	#else
		#ifdef MYOUSHU_DEBUG
			loadPlugin("libastt_d");
			loadPlugin("libMyoushuDotScene_d");
			loadPlugin("libmyoushuOgreOggSound_d");
		#else
			loadPlugin("libastt");
			loadPlugin("libMyoushuDotScene");
			loadPlugin("libmyoushuOgreOggSound");
		#endif
	#endif

	this->init();

	Myoushu::ScriptManager::getSingleton().executeScriptFile("GUIInit.lua");

	this->run();
}

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
along with The ASD Assist VE Platform.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file ASTTPlugin.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef ASTT_DOT_SCENE_PLUGIN_H
#define ASTT_DOT_SCENE_PLUGIN_H

#include "Poco/RWLock.h"

#include "Plugin.h"

#include "ASTTPlatform.h"
#include "EducationalQuestionsManager.h"

namespace Educational
{
	/** Class defining a generic Myoushu plugin. */
	class ASTT_API ASTTPlugin : public Myoushu::Plugin
	{
		public:
			/** Constructor. */
			ASTTPlugin(const std::string& name = "ASTTPlugin");

			/** Destructor. */
			virtual ~ASTTPlugin();

			/** 
			 * The plugin install sequence. This is called during engine start-up and should not rely 
			 * on other plugins or system already existing. It should only do a basic creation and installation
			 * sequence.
			 */
			virtual void install();

			/**
			 * Called after initial system start up and plugin installation. This section can rely on other
			 * systems and plugins existing and should do the initialisation necessary for the plugin to
			 * function.
			 */
			virtual void initialise();

			/**
			 * This is the opposite of shutdown, it is called before key parts of the system are unloaded.
			 */
			virtual void shutdown();

			/**
			 * Performs the final plugin uninstall sequence, unregister and destory the plugin instance.
			 */
			virtual void uninstall();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The EducationalQuestionsManager singleton. */
			EducationalQuestionsManager *pEduQuestionsManager;
	};

	// inlines
	inline ASTTPlugin::ASTTPlugin(const std::string& name) : Myoushu::Plugin(name)
	{
	}

	inline ASTTPlugin::~ASTTPlugin()
	{
	}
}

#endif



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

#ifndef MYOUSHU_PLUGIN_H
#define MYOUSHU_PLUGIN_H

#include "Platform.h"
#include "NamedInstance.h"

namespace Myoushu
{
	/** Class defining a generic Myoushu plugin. */
	class MYOUSHU_API Plugin : public NamedInstance
	{
		public:
			/** Constructor. */
			Plugin(const std::string& name = "Plugin");

			/** Destructor. */
			virtual ~Plugin();

			/** 
			 * The plugin install sequence. This is called during engine start-up and should not rely 
			 * on other plugins or system already existing. It should only do a basic creation and installation
			 * sequence.
			 */
			virtual void install() = 0;

			/**
			 * Called after initial system start up and plugin installation. This section can rely on other
			 * systems and plugins existing and should do the initialisation necessary for the plugin to
			 * function.
			 */
			virtual void initialise() = 0;

			/**
			 * This is the opposite of shutdown, it is called before key parts of the system are unloaded.
			 */
			virtual void shutdown() = 0;

			/**
			 * Performs the final plugin uninstall sequence, unregister and destory the plugin instance.
			 */
			virtual void uninstall() = 0;
	};

	// inlines
	inline Plugin::Plugin(const std::string& name) : NamedInstance(name)
	{
	}

	inline Plugin::~Plugin()
	{
	}
}

#endif



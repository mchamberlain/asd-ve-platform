/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morn� Chamberlain & Stellenbosch University

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
 * @file RoadToTheMoon.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef SAMPLE_LUA_H
#define SAMPLE_LUA_H

#include "Application.h"

class RoadToTheMoon : public Myoushu::Application
{
	public:
		/** Nullary Constructor. */
		RoadToTheMoon();

		/** Destructor */
		~RoadToTheMoon();

		/**
		 * Start the sample application.
		 * Calls the main() and init() in Myoushu::Application.
		 * @param argc Number of command line parameters including the filename that was executed
		 * @param argv Array of null terminiated C-style strings containing the command line parameters.
		 */
		void start(int argc, char **argv);
};

#endif

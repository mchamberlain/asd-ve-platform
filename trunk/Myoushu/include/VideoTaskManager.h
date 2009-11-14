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
 * @file VideoTaskManager.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef VIDEO_TASK_MANAGER_H
#define VIDEO_TASK_MANAGER_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Constants.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This is a helper class for managing the VideoTask.
	 */
	class MYOUSHU_API VideoTaskManager : public Ogre::Singleton<VideoTaskManager>
	{
		public:
			/** Constructor */
			VideoTaskManager();

			/** Destructor */
			~VideoTaskManager();

			/**
			 * Gets a Ogre::RenderWindow instance by name. If an instance with the specified name does not exist, NULL is returned.
			 * @param name The name of the Ogre::RenderWindow instance to find. This parameter defaults to Constants::DEFAULT_RENDER_TARGET,
			 *			   the default render window for the engine.
			 */
			Ogre::RenderWindow* getRenderWindow(const Ogre::String& name = Constants::MAIN_RENDER_TARGET);

			/** Sets whether the VideoTask should display the frame rate statistics on screen. */
			void showFPS(bool show);

	}; // class VideoTaskManager
} // namespace

#endif

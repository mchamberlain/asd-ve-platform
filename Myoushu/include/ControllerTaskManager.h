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
 * @file ControllerTaskManager.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Exception.h"
#include "Controller.h"

namespace Myoushu
{
	/**
	 * The ControllerTaskManager manages the ControllerTask and sends it messages for adding and removing Controllers.
	 */
	class MYOUSHU_API ControllerTaskManager : public Ogre::Singleton<ControllerTaskManager>
	{
		public:
			/** Nullary Constructor */
			ControllerTaskManager();

			/** Destructor */
			virtual ~ControllerTaskManager();

			/**
			 * Sends a message to the ControllerTask to add the specified Controller to its list of Controllers.
			 * @param controller The Controller instance to add.
			 * @throws Exception::E_NULL_POINTER if controller is NULL.
			 */
			void addController(Controller *controller) throw (Exception);

			/**
			 * Sends a message to the ControllerTask to add the specified Controller to its list of Controllers.
			 * @param name The name of the Controller to add.
			 * @return true if the Controller was found and the message was sent, false if the Controller
			 *		   with the specified name could not be found.
			 */
			bool addController(const Ogre::String& name);

			/**
			 * Sends a message to the ControllerTask to remove the specified Controller from its list of Controllers.
			 * @param controller The Controller instance to remove.
			 * @throws Exception::E_NULL_POINTER if controller is NULL.
			 */
			void removeController(Controller *controller) throw (Exception);

			/**
			 * Sends a message to the ControllerTask to remove the specified Controller from its list of Controllers.
			 * @param name The name of the Controller to remove.
			 * @return true if the Controller was found and the message was sent, false if the Controller
			 *		   with the specified name could not be found.
			 */
			bool removeController(const Ogre::String& name);
	};
} // namespace Myoushu

#endif

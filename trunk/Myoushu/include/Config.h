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
 * @file Config.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "Ogre.h"
#include "Poco/RWLock.h"
#include "Poco/Util/MapConfiguration.h"

#include "Singleton.h"
#include "Exception.h"
#include "InputDevice.h"

namespace Myoushu
{
	/** A configuration system based on the Poco MapConfiguration class. */

	class MYOUSHU_API Config : public Poco::Util::MapConfiguration, public Ogre::Singleton<Config>
	{
		public:
			/** Constructor */
			Config();

			/** Destructor */
			~Config();

			/**
			 * Load configuration from a file.
			 * @param filename The filename of the configuration file.
			 * @throws Exception If any error occurs.
			 */
			void loadConfig(const Ogre::String& filename) throw (Exception);

			/**
			 * Bind an input event on an input device to an input action.
			 * @param inputDevice The device to bind the action to.
			 * @param inputIdentifier The identifier of the input event on the device, i.e. the identifier for when
			 *						  the 'A' button is pressed on the keyboard. InputDevice classes have constants
			 *						  defined for all input events.
			 * @param inputAction The action to bind this input event to, i.e. 'strafe-left'.
			 */
			void bindInputAction(const InputDevice *inputDevice, const std::string& inputIdentifier, const std::string& inputAction);

			/**
			 * Unbind an input event from an input device and input action.
			 * @param inputDevice The device to unbind the action from.
			 * @param inputIdentifier The identifier of the input event on the device, i.e. the identifier for when
			 *						  the 'A' button is pressed on the keyboard. InputDevice classes have constants
			 *						  defined for all input events.
			 * @param inputAction The action to unbind this input event from, i.e. 'strafe-left'.
			 */
			void unbindInputAction(const InputDevice *inputDevice, const std::string& inputIdentifier, const std::string& inputAction);

			/** A string constant used to fetch the resolution from the configuration map. */
			static const Ogre::String VID_WIDTH;
			/** A string constant used to fetch the resolution from the configuration map. */
			static const Ogre::String VID_HEIGHT;
			/** A string constant used to fetch the colour depth from the configuration map. */
			static const Ogre::String VID_BITS;
			/** A string constant used to fetch the fullscreen flag from the configuration map. */
			static const Ogre::String VID_FULLSCREEN;
			/** A string constant used to fetch the vertical sync flag from the configuration map. */
			static const Ogre::String VID_VSYNC;
			/** A string constant used to fetch the antialiasing setting from the configuration map. */
			static const Ogre::String VID_ANTIALIASING;
			/** A string constant used to fetch the anisotropic filtering settings from the configuration map. */
			static const Ogre::String VID_ANISOTROPIC_FILTERING;
			/** The prefix used for all input configurations */
			static const Ogre::String INPUT_PREFIX;
			/** The mouse input sensitivity. */
			static const Ogre::String INPUT_MOUSE_SENSITIVITY;

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;

	};
} // Myousho

#endif // CONFIG_H

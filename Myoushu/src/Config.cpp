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
 * @file Config.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <iostream>

#include "Poco/Util/MapConfiguration.h"
#include "Poco/Exception.h"
#include "Ogre.h"
#include "TextFileManager.h"

#include "Config.h"
#include "Constants.h"
#include "Exception.h"

//template<>
//Myoushu::Config* Ogre::Singleton<Myoushu::Config>::ms_Singleton = NULL;

namespace Myoushu
{

/****************************************************************************/
		Config::Config()
		{
		}

/****************************************************************************/
		Config::~Config()
		{
		}

/****************************************************************************/
		void Config::loadConfig(const Ogre::String& filename) throw (Exception)
		{
			TextFileManager *txtFileMgr;
			TextFilePtr textFile;
			std::vector<Ogre::String>::const_iterator it;

			Poco::ScopedRWLock lock(rwLock, true);

			txtFileMgr = TextFileManager::getSingletonPtr();

			// Ensure that the TextFileManager exists.
			if (txtFileMgr == NULL)
			{
				throw Exception(Exception::E_NULL_POINTER, "Config::loadConfig: txtFileMgr pointer is null.");
			}

			try
			{
				// Remove any existing instance of this in the resource manager.
				txtFileMgr->remove(filename);

				textFile = txtFileMgr->load(filename, Constants::RG_CONFIGFILES);

			}
			catch (Ogre::Exception& e)
			{
				throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
			}

			try
			{
				const Ogre::String&	text = textFile->getString();

				// Split the text into name value pairs. Tokens are separated by any white space.
				const std::vector<Ogre::String>& nameValuePairs = Ogre::StringUtil::split(text, "\t\n\r ");

				// Add the name value pairs to the MapConfiguration
				it = nameValuePairs.begin();
				while (it != nameValuePairs.end())
				{
					const Ogre::String& option = *it;
					it++;

					if (it != nameValuePairs.end())
					{
						this->setString(option, *it);
					}

					it++;
				}
			}
			catch (Poco::Exception& e)
			{
				throw Exception(Exception::E_POCO_EXCEPTION, e.displayText());
			}
			catch (Ogre::Exception& e)
			{
				throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
			}
			catch (std::exception& e)
			{
				throw Exception(Exception::E_STD_EXCEPTION, e.what());
			}
		}

		void Config::bindInputAction(const InputDevice *inputDevice, const std::string& inputIdentifier, const std::string& inputAction)
		{
			if (inputDevice == NULL)
			{
				return;
			}

			setString(inputDevice->getInputEventString(inputIdentifier), inputAction);
		}

		void Config::unbindInputAction(const InputDevice *inputDevice, const std::string& inputIdentifier, const std::string& inputAction)
		{
			if (inputDevice == NULL)
			{
				return;
			}

			// Removal hack for the time being, Poco::Util::MapConfiguration has no removal functions
			setString(inputDevice->getInputEventString(inputIdentifier), "");
		}

		const Ogre::String Config::VID_WIDTH = "app.video.width";
		const Ogre::String Config::VID_HEIGHT = "app.video.height";
		const Ogre::String Config::VID_BITS = "app.video.bits";
		const Ogre::String Config::VID_FULLSCREEN = "app.video.fullscreen";
		const Ogre::String Config::VID_VSYNC = "app.video.vsync";
		const Ogre::String Config::VID_ANTIALIASING = "app.video.antialiasing";
		const Ogre::String Config::VID_ANISOTROPIC_FILTERING = "app.video.anisotropic";
		const Ogre::String Config::INPUT_PREFIX = "input";
		const Ogre::String Config::INPUT_MOUSE_SENSITIVITY = "input.mouse.sensitivity";
} // Myoushu

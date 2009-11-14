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
 * @file OISInputDevice.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef OIS_INPUT_DEVICE_H
#define OIS_INPUT_DEVICE_H

#include "Platform.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * The base class for OIS based input devices.
	 */
	template <class C>
	class OISInputDevice
	{
		public:
			/**
			 * Constructor.
			 * @param oisDevice The OIS::Object instance associated with this device.
			 */
			OISInputDevice(C *oisDevice) : oisDevice(oisDevice)
			{
			}

			/** Destructor */
			~OISInputDevice()
			{
//				if (oisDevice)
//				{
//					LOG(EngineLog::LM_INFO_ENGINE, "Destroying OISInputDevice: " << oisDevice->vendor());
//					OIS::InputManager::destroyInputObject(oisDevice);
//				}
			}

			/**
			 * Calls the capture method of the OIS::Object associated with this device. This will update
			 * the device and call any event callbacks that have been registered.
			 */
			inline void capture()
			{
				if (oisDevice)
				{
					oisDevice->capture();
				}
			}

			/**
			 * Get the OIS::Object instance associated with this device.
			 * @return The OIS::Object instance associated with this device.
			 */
			inline C* getOISDevice()
			{
				return oisDevice;
			}

		protected:
			/** A pointer to the OIS input device instance. */
			C* oisDevice;

		private:
			/** Nullary Constructor */
			OISInputDevice()
			{
			}
	};
} // Myoushu

#endif

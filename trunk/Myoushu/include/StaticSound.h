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
 * @file StaticSound.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef STATIC_SOUND_H
#define STATIC_SOUND_H

#include "Sound.h"

namespace Myoushu
{
	/** 
	 * The base class for all static sound implementations. A static sound is a sound that is completely loaded
	 * into memory before it is played, it is not streamed while played.
	 */
	class MYOUSHU_API StaticSound : public Sound, public NamedObject<StaticSound>
	{
		public:
			/**
			 * Constructor.
			 * @param name The unique name of this Sound instance.
			 */
			StaticSound(const std::string& name = "StaticSound");

			/** Destructor */
			virtual ~StaticSound();

			CLASS_NAME_FUNCTIONS(StaticSound);

			/**
			 * Opens an audio file and starts to read it into memory.
			 * @param pDataStream The stream to read the audio data from.
			 */
			virtual void open(Ogre::DataStreamPtr pDataStream) = 0;

			/**
			 * Opens an audio file and starts to read it into memory using
			 * a shared buffer.
			 * @param fileName The audio file path.
			 * @param pBuffer The shared memory buffer.
			 */
			virtual void open(const std::string& fileName, memUInt pBuffer) = 0;

	}; // class StaticSound

} // namespace Myoushu

#endif

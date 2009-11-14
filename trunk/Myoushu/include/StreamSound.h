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
 * @file StreamSound.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef STREAM_SOUND_H
#define STREAM_SOUND_H

#include "Sound.h"

namespace Myoushu
{
	/** 
	 * The base class for all streaming sound implementations. A streaming sound is a sound that is streamed
	 * from a source while it is played.
	 */
	class MYOUSHU_API StreamSound : public Sound, public NamedObject<StreamSound>
	{
		public:
			/**
			 * Constructor.
			 * @param name The unique name of this Sound instance.
			 */
			StreamSound(const std::string& name = "StreamSound");

			/** Destructor */
			virtual ~StreamSound();

			CLASS_NAME_FUNCTIONS(StreamSound);

			/**
			 * Opens an audio file and starts to read it into memory.
			 * @param pDataStream The stream to read the audio data from.
			 */
			virtual void open(Ogre::DataStreamPtr pDataStream) = 0;

	}; // class StreamSound

} // namespace Myoushu

#endif

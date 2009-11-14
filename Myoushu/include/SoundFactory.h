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
 * @file SoundFactory.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_SOUND_FACTORY_H
#define MYOUSHU_SOUND_FACTORY_H

#include "NamedObjectFactory.h"

#include "Sound.h"
#include "StaticSound.h"
#include "StreamSound.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * A base class for a factory that creates Sound instances. Specific implementations can be defined by plug-ins.
	 */
	class MYOUSHU_API SoundFactory : public NamedObjectFactory<Sound>
	{
		public:
			/** Constructor */
			SoundFactory();

			/** Destructor */
			virtual ~SoundFactory();

			/**
			 * Creates a StaticSound instance.
			 * @param name Unique name for the sound.
			 * @param filePath The path to the sound file.
			 * @param loop A boolean indiciating whether the sound should loop.
			 * @param preBuffer A flag indicating whether a source should be attached at creation.
			 * @return Pointer to the created Sound instance or NULL if there was a problem.
			 */
			virtual StaticSound* makeStaticSound(const std::string& name, const std::string& filePath, bool loop = false, bool preBuffer = false) = 0;

			/**
			 * Creates a StaticSound instance.
			 * @param name Unique name for the sound.
			 * @param filePath The path to the sound file.
			 * @param loop A boolean indiciating whether the sound should loop.
			 * @param preBuffer A flag indicating whether a source should be attached at creation.
			 * @return Pointer to the created Sound instance or NULL if there was a problem.
			 */
			virtual StreamSound* makeStreamSound(const std::string& name, const std::string& filePath, bool loop = false, bool preBuffer = false) = 0;

			/** 
			 * Destroys the supplied instance.
			 * @param pInstance The Sound instance to destroy (must have been created by this factory).
			 */
			virtual void destroyInstance(Sound* pInstance) throw (Exception) = 0;

			/** Removes and destroys all sounds in this factory. */
			virtual void destroyAll() = 0;
	};

	//inlines
	inline SoundFactory::SoundFactory()
	{
	}

	inline SoundFactory::~SoundFactory()
	{
	}

} // namespace Myoushu

#endif

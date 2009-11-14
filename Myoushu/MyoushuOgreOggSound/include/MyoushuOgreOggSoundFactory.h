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
 * @file MyoushuOgreOggSoundFactory.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_OGRE_OGG_SOUND_FACTORY_H
#define MYOUSHU_OGRE_OGG_SOUND_FACTORY_H

#include "SoundFactory.h"
#include "Singleton.h"

#include "MyoushuOgreOggSoundPlatform.h"
#include "MyoushuOgreOggStaticSound.h"
#include "MyoushuOgreOggStreamSound.h"

namespace Myoushu
{
	class MYOUSHU_OGRE_OGG_SOUND_API MyoushuOgreOggSoundFactory : public SoundFactory, public Ogre::Singleton<MyoushuOgreOggSoundFactory>
	{
		public:
			/** Constructor */
			MyoushuOgreOggSoundFactory();

			/** Destructor */
			virtual ~MyoushuOgreOggSoundFactory();

			/** 
			 * Create an instance using with specified name. Creates a MyoushuOgreOggStaticSound instance.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 */
			virtual MyoushuOgreOggStaticSound* make(const std::string& name);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual Sound* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Creates a StaticSound instance.
			 * @param name Unique name for the sound.
			 * @param filePath The path to the sound file.
			 * @param loop A boolean indiciating whether the sound should loop.
			 * @param preBuffer A flag indicating whether a source should be attached at creation.
			 * @return Pointer to the created Sound instance or NULL if there was a problem.
			 */
			virtual MyoushuOgreOggStaticSound* makeStaticSound(const std::string& name, const std::string& filePath, bool loop = false, bool preBuffer = false);

			/**
			 * Creates a StaticSound instance.
			 * @param name Unique name for the sound.
			 * @param filePath The path to the sound file.
			 * @param loop A boolean indiciating whether the sound should loop.
			 * @param preBuffer A flag indicating whether a source should be attached at creation.
			 * @return Pointer to the created Sound instance or NULL if there was a problem.
			 */
			virtual MyoushuOgreOggStreamSound* makeStreamSound(const std::string& name, const std::string& filePath, bool loop = false, bool preBuffer = false);

			/** 
			 * Destroys the supplied instance.
			 * @param pInstance The Sound instance to destroy (must have been created by this factory).
			 */
			virtual void destroyInstance(Sound* pInstance) throw (Exception);

			/** Removes and destroys all sounds in this factory. */
			virtual void destroyAll();
	};
} // namespace Myoushu

#endif

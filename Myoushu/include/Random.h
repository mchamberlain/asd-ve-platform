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
 * @file Random.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_RANDOM_H
#define MYOUSHU_RANDOM_H

#include "MTRandom.h"
#include "Singleton.h"

namespace Myoushu
{
	/** Global random number generator singleton. It extends MTRandom. */
	class MYOUSHU_API Random : public MTRandom, public Ogre::Singleton<Random>
	{
		public:
			/** Constructor. */
			Random();

			/** Constructor. */
			Random(unsigned int seed);

			/** Destructor. */
			virtual ~Random();
	}; // class RandomBase

	// inlines
	inline Random::Random() : MTRandom()
	{
	}

	inline Random::Random(unsigned int seed) : MTRandom(seed)
	{
	}

	inline Random::~Random()
	{
	}

} //namespace Myoushu

#endif

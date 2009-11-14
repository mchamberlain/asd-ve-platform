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
 * @file RandomBase.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_RANDOM_BASE_H
#define MYOUSHU_RANDOM_BASE_H

#include "Platform.h"
#include "Serializable.h"

namespace Myoushu
{
	/** 
	 * An abstract class for implementing pseudorandom number generators. 
	 * This class inherits from the Serializable class to allow for saving and loading
	 * the state of the random number generator.
	 */
	class MYOUSHU_API RandomBase : public Serializable
	{
		public:
			/** Set the seed for this random number generator. */
			virtual void seed(int seed) = 0;

			/** 
			 * Get the next random number, in the range [0, 2^32-1]. The seed() function must
			 * be called at least once before the first call to this function.
			 */
			virtual unsigned int generate() = 0;

			/** Returns the next pseudorandom number, but normalises it to the range [min, max]. */
			virtual int generate(int min, int max) = 0;

			/** Returns the next pseudorandom number, but normalises it to the range [0, 1]. */
			virtual double generateDouble() = 0;

			/** Returns the next pseudorandom number, but normalises it to the range [min, max]. */
			virtual double generateDouble(double min, double max) = 0;
	}; // class RandomBase

} //namespace Myoushu

#endif

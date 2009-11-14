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
 * @file MTRandom.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef MYOUSHU_MT_RANDOM_H
#define MYOUSHU_MT_RANDOM_H

#include "Poco/RWLock.h"

#include "RandomBase.h"

namespace Myoushu
{
	/** A random number generator that uses the MT19937 algorithm. */
	class MYOUSHU_API MTRandom : public RandomBase
	{
		public:
			static const unsigned int W;
			static const unsigned int N;
			static const unsigned int M;
			static const unsigned int R;
			static const unsigned int A;
			static const unsigned int U;
			static const unsigned int S;
			static const unsigned int B;
			static const unsigned int T;
			static const unsigned int C;
			static const unsigned int L;

			/** Nullary constructor */
			MTRandom();

			/** Constructor. Calls the seed() function with the specified seed. */
			MTRandom(unsigned int seed);

			/** Destructor. */
			virtual ~MTRandom();

			/** Set the seed for this random number generator. */
			virtual void seed(int seed);

			/** 
			 * Get the next random number, in the range [0, 2^32-1]. The seed() function must
			 * be called at least once before the first call to this function.
			 */
			virtual unsigned int generate();

			/** Returns the next pseudorandom number, but normalises it to the range [min, max]. */
			virtual int generate(int min, int max);

			/** Returns the next pseudorandom number, but normalises it to the range [0, 1]. */
			virtual double generateDouble();

			/** Returns the next pseudorandom number, but normalises it to the range [min, max]. */
			virtual double generateDouble(double min, double max);

			/** Gets the current index into the generator state. */
			unsigned int getIndex() const;

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the serialized data (in bytes).
			 */
			virtual memUInt serialize(void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) const throw (Exception);

			/**
			 * Populates this instance with the serialized description read from the specified buffer.
			 * @param pMem The buffer to read the instance description from.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return The size of the data read (in bytes).
			 */
			virtual memUInt populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget = ST_UNKNOWN) throw (Exception);

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The current index into the state of the generator. */
			unsigned int mIndex;
			/** The state of the generator. */
			unsigned int *mpMTState;

			/** Generate the state of the generator. */
			void generateNumbers();

	}; // class MTRandom

	// inlines
	inline unsigned int MTRandom::getIndex() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mIndex;
	}

	inline int MTRandom::generate(int min, int max)
	{
		return static_cast<int>((static_cast<double>(generate()) / static_cast<double>(0xFFFFFFFFu) * static_cast<double>(max - min) + min));
	}

	inline double MTRandom::generateDouble()
	{
		return static_cast<double>(generate() / static_cast<double>(0xFFFFFFFFu));
	}

	inline double MTRandom::generateDouble(double min, double max)
	{
		return generateDouble() * (max - min) + min;
	}
} //namespace Myoushu

#endif

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
 * @file MTRandom.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "MTRandom.h"
#include "EngineLog.h"

namespace Myoushu
{
	const unsigned int MTRandom::W = 32;
	const unsigned int MTRandom::N = 624;
	const unsigned int MTRandom::M = 397;
	const unsigned int MTRandom::R = 31;
	const unsigned int MTRandom::A = 0x9908B0DF;
	const unsigned int MTRandom::U = 11;
	const unsigned int MTRandom::S = 7;
	const unsigned int MTRandom::B = 0x9D2C5680;
	const unsigned int MTRandom::T = 15;
	const unsigned int MTRandom::C = 0xEFC60000;
	const unsigned int MTRandom::L = 18;

	MTRandom::MTRandom() : mIndex(0)
	{
		mpMTState = new unsigned int[N];
	}

	MTRandom::MTRandom(unsigned int seed) : mIndex(0)
	{
		mpMTState = new unsigned int[N];
		this->seed(seed);
	}

	MTRandom::~MTRandom()
	{
		if (mpMTState)
		{
			delete [] mpMTState;
			mpMTState = NULL;
		}
	}

	void MTRandom::seed(int seed)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpMTState[0] = seed;
		for (unsigned int i = 1; i < N; i++)
		{
			mpMTState[i] = 1812433253 * (mpMTState[i - 1] ^ (mpMTState[i-1]) >> 30) + i;
		}
	}

	unsigned int MTRandom::generate()
	{
		if (getIndex() == 0)
		{
			generateNumbers();
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		unsigned int y = mpMTState[mIndex];
		y = y ^ (y >> U);
		y = y ^ ((y << S) & B);
		y = y ^ ((y << T) & C);
		y = y ^ (y >> L);

		mIndex = (mIndex + 1) & N;

		return y;
	}

	void MTRandom::generateNumbers()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		for (unsigned int i = 0; i < N; i++)
		{
			int y = (0x80000000 & mpMTState[i]) + (0xFFFFFFFE & mpMTState[(i+1) & N]);
			mpMTState[i] = mpMTState[(i + M) % N] ^ (y >> 1);
			if ((y % 2) == 1)
			{
				mpMTState[i] = (mpMTState[i] ^ A);
			}
		}
	}

	memUInt MTRandom::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		memUInt pBuf;
		memUInt writeSize;
		memUInt totalSize;

		writeSize = 0;
		totalSize = 0;
		pBuf = reinterpret_cast<memUInt>(pMem);

		Poco::ScopedRWLock lock(mRWLock, false);

		// Write mIndex
		writeSize = writePrimitiveType(mIndex, reinterpret_cast<void*>(pBuf));
		totalSize += writeSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MTRandom::serialize(): the buffer is too small.");
		}
		pBuf += writeSize;

		// write the generator state
		for (unsigned int i = 0; i < N; i++)
		{
			writeSize = writePrimitiveType(mpMTState[i], reinterpret_cast<void*>(pBuf));
			totalSize += writeSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "MTRandom::serialize(): the buffer is too small.");
			}
			pBuf += writeSize;
		}

		return totalSize;
	}

	memUInt MTRandom::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		memUInt readSize;
		memUInt totalSize;
		memUInt pBuf;

		readSize = 0;
		totalSize = 0;
		pBuf = reinterpret_cast<memUInt>(pMem);

		Poco::ScopedRWLock lock(mRWLock, true);

		// read mIndex
		readSize = readPrimitiveType(mIndex, reinterpret_cast<const void*>(pBuf));
		totalSize += readSize;
		pBuf += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "MTRandom::populateInstance(): buffer is too small.");
		}

		// read generator state
		for (unsigned int i = 0; i < N; i++)
		{
			readSize = readPrimitiveType(mpMTState[i], reinterpret_cast<const void*>(pBuf));
			totalSize += readSize;
			pBuf += readSize;
			if (totalSize > size)
			{
				throw Exception(Exception::E_BUFFER_TOO_SMALL, "MTRandom::populateInstance(): buffer is too small.");
			}
		}

		return totalSize;
	}

} //namespace Myoushu

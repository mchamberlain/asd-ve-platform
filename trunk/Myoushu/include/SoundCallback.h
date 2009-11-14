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
 * @file SoundCallback.h
 * @author ME Chamberlain
 * @date April 2009
 */

#ifndef MYOUSHU_SOUND_CALLBACK_H
#define MYOUSHU_SOUND_CALLBACK_H

#include "Poco/RWLock.h"

#include "Platform.h"
#include "FunctorBase.h"
#include "Sound.h"

namespace Myoushu
{
	/**
	 * A callback class used by Sound instances to call a function when the sound ends or is looped.
	 */
	class MYOUSHU_API SoundCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking one Sound pointer as parameter. */
			typedef void (*SoundCallbackGlobalFunction)(Sound*);

			/** Constructor */
			SoundCallback(SoundCallbackGlobalFunction pFunction);

			/** Destructor */
			virtual ~SoundCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** Sets the parameters for the callback function call: the Sound instance. */
			void setParameters(Sound *pSound);

			/**
			 * Execute the function wrapped by this functor.
			 */
			virtual void operator()() throw (Exception);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock mRWLock;
			/** Pointer to the function to execute */
			SoundCallbackGlobalFunction mpFunction;
			/** The Sound instance involved in this callback */
			Sound* mpSound;

	}; // class FunctorBase
} // namespace Myoushu

#endif

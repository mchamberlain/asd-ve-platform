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
 * @file CollisionCallback.h
 * @author ME Chamberlain
 * @date March 2009
 */

#ifndef MYOUSHU_COLLISION_CALLBACK_H
#define MYOUSHU_COLLISION_CALLBACK_H

#include "Poco/RWLock.h"

#include "Platform.h"
#include "FunctorBase.h"
#include "GameActorObject.h"

namespace Myoushu
{
	/**
	 * A callback used for notification about collisions between objects in the virtual world.
	 */
	class MYOUSHU_API CollisionCallback : public FunctorBase
	{
		public:
			/** A pointer to a global function returning void and taking two GameActorObject pointers as parameters. */
			typedef void (*CollisionCallbackGlobalFunction)(GameActorObject*, GameActorObject*);

			/** Constructor */
			CollisionCallback(CollisionCallbackGlobalFunction pFunction);

			/** Destructor */
			virtual ~CollisionCallback();

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/** Sets the parameters for the callback function call: the two GameActorObjects that is involved in a collision. */
			void setParameters(GameActorObject* pFirstActor, GameActorObject *pSecondActor);

			/**
			 * Execute the function wrapped by this functor.
			 */
			virtual void operator()() throw (Exception);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock mRWLock;
			/** Pointer to the function to execute */
			CollisionCallbackGlobalFunction mpFunction;
			/** One of the actors involved in the collision */
			GameActorObject *mpFirstActor;
			/** The other actor involved in the collision */
			GameActorObject *mpSecondActor;
			
	}; // class FunctorBase
} // namespace Myoushu

#endif

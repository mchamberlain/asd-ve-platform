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
 * @file FunctorBase.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef FUNCTOR_BASE_H
#define FUNCTOR_BASE_H

#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "Cloneable.h"
#include "Exception.h"
#include "Value.h"
#include "NamedObject.h"
#include "NamedInstance.h"

namespace Myoushu
{
	/**
	 * An abstract class that serves as a base class for Functors.
	 */
	class MYOUSHU_API FunctorBase : public Cloneable, public Poco::RefCountedObject, public NamedObject<FunctorBase>, public NamedInstance
	{
		public:
			/** 
			 * Constructor
			 * @param name The name of this Functor instance. Defaults to "Functor".
			 */
			FunctorBase(const std::string& name = "Functor");

			CLASS_NAME_FUNCTIONS(FunctorBase);

			/** 
			 * Sets the parameters to pass to the function wrapped by this functor. 
			 * @param index The index of the parameter, starting from 0.
			 * @param v The parameter for the specified index.
			 * @throws Exception if index is larger than the number of parameters supported by the wrapped function.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception) = 0;

			/**
			 * Execute the function wrapped by this functor.
			 */
			virtual void operator()() throw(Exception) = 0;
	};

} // Myoushu

#endif

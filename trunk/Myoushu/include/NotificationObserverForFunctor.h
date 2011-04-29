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
 * @file NotificationObserverForFunctor.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_NOTIFICATION_OBSERVER_FOR_FUNCTOR_H
#define MYOUSHU_NOTIFICATION_OBSERVER_FOR_FUNCTOR_H

#include <string>
#include <map>
#include <list>

#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/RWLock.h"

#include "Platform.h"
#include "FunctorBase.h"
#include "LuaFunctorBase.h"
#include "LuaFunctor.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * A proxy class that acts as an observer for messages that should be delivered to functors. Used in the NotificationManager
	 * set up message delivery to functors. 
	 */
	class MYOUSHU_API NotificationObserverForFunctor : public Poco::RefCountedObject
	{
		public:
			/** Constructor. */
			NotificationObserverForFunctor();

			/** Destructor. */
			virtual ~NotificationObserverForFunctor();

			/** Adds a Functor. A map is used between the supplied messageType (use getClassName()) and the functor, thus only one functor per type is stored. */
			void addFunctor(const std::string& messageType, FunctorBase *pFunctor);

			/** 
			 * Removes the pointer to the FunctorBase instance for the specified message type.
			 * @param messageType The type of the message the Functor to remove is mapped to 
			 *					  (use ::getClassName() or ::getStaticClassName() to get the class name
			 *					  of the message object.)
			 * @return The FunctorBase instance that was removed. If no instance was removed NULL is returned.
			 */
			FunctorBase* removeFunctor(const std::string& messageType);

			/** Gets the number of entries in the type name to Functor map. */
			uint32 numMappedFunctors() const;

			/** Gets a list of the message types (as strings) that this instance handles. */
			void getMessageTypes(std::list<std::string> &messageTypeList) const;

			/**
			 * Handler function that will be called by the NotificationManager when messages are to be delivered
			 * to the FunctorBase instance stored in this instance.
			 * @param message The message T instance to deliver.
			 * @throws Exception::E_NULL_POINTER if mpFunctor is NULL.
			 */
			template<class T>
			void handler(const Poco::AutoPtr<T>& message) throw (Exception);

		protected:
			/** Read/write for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The functors to call when the handler() function is called. */
			std::map<std::string, FunctorBase*> mFunctorMap;
	}; // class NotificationObserverForFunctor

	// template implementations
	template<class T>
	void NotificationObserverForFunctor::handler(const Poco::AutoPtr<T>& message) throw (Exception)
	{
		FunctorBase *pFunctor;

		// Get the FunctorBase instance for the type T
		{
			std::map<std::string, FunctorBase*>::iterator iter;

			Poco::ScopedRWLock lock(mRWLock, false);

			iter = mFunctorMap.find(NamedObject<T>::getStaticClassName());
			// Throw an exception if type T has no associated functor in this instance
			if (iter == mFunctorMap.end())
			{
				throw Exception(Exception::E_NO_SUCH_ELEMENT, "NotificationObserverForFunctor::handler(): No functor assigned to type: " + NamedObject<T>::getStaticClassName());
			}
			pFunctor = iter->second;
		}

		// Ensure that pFunctor is not NULL
		if (pFunctor == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "NotificationObserverForFunctor::handler(): mpFunctor is NULL.");
		}

		// Check if pFunctor is a LuaFunctorBase instance, if it is we can support nicer parameter handling
		// otherwise use the default functions from FunctorBase
		if (pFunctor->getClassName() == NamedObject<LuaFunctorBase>::getStaticClassName())
		{
			LuaFunctor<void, 1, Poco::AutoPtr<T> >* pLuaFunctor = static_cast<LuaFunctor<void, 1, Poco::AutoPtr<T> >*>(pFunctor);

			pLuaFunctor->setParameter1(message);
		}
		else
		{
			Value val;

			//val.setConstVoidPtr( reinterpret_cast<const void*>( message.get() ), true);
			//val.setConstRefCountedObjectPtr( static_cast< const Poco::RefCountedObject* >( message.get() ), true );
			val.setConstMessagePtr( static_cast< const Message* >( message.get() ), true );
			pFunctor->setParameter(0, val);
		}

		// Call the function
		(*pFunctor)();
	}

	// inlines
	inline void NotificationObserverForFunctor::addFunctor(const std::string& messageType, FunctorBase *pFunctor)
	{
		Poco::ScopedRWLock lock(mRWLock, true);
		mFunctorMap.insert(std::pair<std::string, FunctorBase*>(messageType, pFunctor));
	}
	
	inline uint32 NotificationObserverForFunctor::numMappedFunctors() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mFunctorMap.size();
	}

} // namespace Myoushu

#endif

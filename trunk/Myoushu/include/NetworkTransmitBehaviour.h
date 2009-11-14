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
 * @file NetworkTransmitBehaviour.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_NETWORK_TRANSMIT_BEHAVIOUR
#define MYOUSHU_NETWORK_TRANSMIT_BEHAVIOUR

#include <list>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "NetworkMessage.h"
#include "EngineLog.h"

namespace Myoushu
{
	/**
	 * The base class of behaviours for managing the logic about how and when messages are transmitted over the network.
	 */
	class MYOUSHU_API NetworkTransmitBehaviour : public Poco::RefCountedObject
	{
		public:
			/** Nullary Constructor. */
			NetworkTransmitBehaviour();

			/** Destructor */
			virtual ~NetworkTransmitBehaviour();

			/**
			 * Initializes the behaviour. Typically this function would register the behaviour to receive various types of
			 * engine messages, including NetworkMessages.
			 */
			virtual void init() = 0;

			/**
			 * Process any queued (from the NotificationManager) messages, including NetworkMessages, and any other relevant logic and
			 * create a list of NetworkMessages that should be transmitted over the network.
			 */
			virtual void update() = 0;

			/** 
			 * Get the list of NetworkMessages to transmit over the network, typically this function will be called after a call to
			 * update().
			 */
			virtual const std::list<Poco::AutoPtr<NetworkMessage> >& getMessagesToTransmit() const;

			/** Clears the list of NetworkMessages that should be transmitted. */
			virtual void clearListOfMessagesToTransmit();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** A list of NetworkMessages that should be transmitted over the network. */
			std::list<Poco::AutoPtr<NetworkMessage> > mMessagesToTransmit;
	};

	// inlines
	inline const std::list<Poco::AutoPtr<NetworkMessage> >& NetworkTransmitBehaviour::getMessagesToTransmit() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mMessagesToTransmit;
	}

	inline void NetworkTransmitBehaviour::clearListOfMessagesToTransmit()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mMessagesToTransmit.clear();
	}

} // namespace Myoushu

#endif

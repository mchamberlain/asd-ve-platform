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
 * @file ReplayMessage.h
 * @author ME Chamberlain
 * @date May 2009
 */

#ifndef REPLAY_MESSAGE_H
#define REPLAY_MESSAGE_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Cloneable.h"
#include "Replay.h"

namespace Myoushu
{
	/**
	 * This class wraps messages sent to the ReplayTask for starting/stopping a recording or playback.
	 */
	class MYOUSHU_API ReplayMessage : public NamedObject<ReplayMessage>, public Message
	{
		public:
			/** This enumeration represents the different types of ReplayMessages that can be sent/received */
			enum ReplayMessageType
			{
				/** Unknown replay message type */
				RM_UNKNOWN = 0,
				/** A message indicating that a new replay recording should start. */
				RM_START_RECORDING,
				/** A message indicating that a replay should be played back. */
				RM_START_PLAYBACK,
				/** A message indiciating that recording/playback should stop. */
				RM_STOP,
				/** A message indicating that recording/playback should be paused. */
				RM_PAUSE,
				/** A message indicating that a paused recording/playback should continue. */
				RM_RESUME
			};

			/** Nullary Constructor */
			ReplayMessage();

			/**
			 * Constructor.
			 * @param messageType The ReplayMessageType of this message.
			 * @param replayName The name of the replay.
			 */
			ReplayMessage(ReplayMessageType messageType, const std::string& replayName);

			/** Destructor */
			virtual ~ReplayMessage();

			CLASS_NAME_FUNCTIONS(ReplayMessage);

			/**
			 * Get the message type of this ReplayMessage.
			 * @return The ReplayMessageType of this message.
			 */
			ReplayMessageType getMessageType() const;

			/**
			 * Sets the message type of this ReplayMessage.
			 * @param type The new ReplayMessageType for this message.
			 */
			void setMessageType(ReplayMessageType type);

			/**
			 * Get the script associated with this message.
			 * @return The name of the replay
			 */
			const std::string& getReplayName() const;

			/**
			 * Sets the name of the replay.
			 * @param replayName The name of the replay.
			 */
			void setReplayName(const std::string& replayName);

			/** Gets the mpReplay field. */
			const Replay* getReplay() const;

			/** Sets the mpReplay field. */
			void setReplay(Replay* pReplay);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			ReplayMessage* clone() const;

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 * @return A reference to this instance
			 */
			ReplayMessage& operator=(const ReplayMessage& message);

		protected:
			/** Read write mutex for thread safety */
			mutable Poco::RWLock mRWLock;
			/** The ReplayMessageType of this message */
			ReplayMessageType mMessageType;
			/** The name of the replay. */
			std::string mReplayName;
			/** Pointer to a Replay instance, if applicable to the message type. */
			Replay *mpReplay;

	};

	// inlines
	inline ReplayMessage::ReplayMessageType ReplayMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mMessageType;
	}

	inline void ReplayMessage::setMessageType(ReplayMessage::ReplayMessageType type)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mMessageType = type;
	}

	inline const std::string& ReplayMessage::getReplayName() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mReplayName;
	}

	inline void ReplayMessage::setReplayName(const std::string& replayName)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mReplayName = replayName;
	}

	inline const Replay* ReplayMessage::getReplay() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mpReplay;
	}

	inline void ReplayMessage::setReplay(Replay* pReplay)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mpReplay = pReplay;
	}

} // Myoushu

#endif

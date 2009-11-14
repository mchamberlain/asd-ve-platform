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
 * @file GameCharacterObjectAction.h
 * @author ME Chamberlain
 * @date September 2008
 */

#ifndef MYOUSHU_GAME_CHARACTER_OBJECT_ACTION_H
#define MYOUSHU_GAME_CHARACTER_OBJECT_ACTION_H

#include "Ogre.h"
#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "GameObjectAction.h"
#include "Exception.h"

namespace Myoushu
{

	/** Forward declaration for GameCharacterObject because of circular dependancy. */
	class GameCharacterObject;

	/**
	 * This class stores information about a generic character action. It stores information about possibly
	 * playing an animation when a character action is fired. It also has start and stop function callbacks.
	 * A start callback can be seen as associated with a button press on a controller and a stop callback with a button release.
	 * For a toggle action one would implement the toggle code in the start callback and nothing in the stop callback, for instance.
	 */
	class MYOUSHU_API GameCharacterObjectAction : public GameObjectAction, public NamedObjectInstanceCreator<GameCharacterObjectAction>
	{
		public:
			/** An enumeration that can be used to set how the animation associated with this action is fired. */
			enum AnimationBehaviour
			{
				/** The animation will be looped until stopped. */
				AM_LOOP,
				/** The animation will play once. */
				AM_ONCE,
				/** One frame of the animation will be played. */
				AM_ONE_FRAME,
				/** Do not play an animation. */
				AM_NO_ANIMATION
			};

			/** Nullary Constructor. Should only be used in conjunction with populateInstance(). */
			GameCharacterObjectAction();

			/**
			 * Constructor.
			 * @param name The name of the action.
			 * @param character The GameCharacterObject instance this action is bound to.
			 * @param toggleAction Flag indicating whether this is a toggle action. Toggle actions only use action start 
			 *					   callbacks (no stop callbacks) and the animation is toggled on or off every time the 
			 *					   action is started.
			 * @param animationName The name of the character animation to play, if any.
			 * @param animBehaviour The manner in which to play the animation, loop, once, only one frame.
			 * @param restartAnimation Flag indicating whether the animation should be restarted when the action is started.
			 * @param playCounter If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 *					  increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 *					  if the counter is zero. This is useful in situations where there are multiple actions that play the
			 *					  same animation.
			 */
			GameCharacterObjectAction(const Ogre::String& name, GameCharacterObject *character, bool toggleAction = false
				, const Ogre::String& animationName = "", AnimationBehaviour animBehaviour = AM_LOOP, bool restartAnimation = false
				, bool playCounter = false) throw (Exception);

			/** Destructor. */
			virtual ~GameCharacterObjectAction();

			CLASS_NAME_FUNCTIONS(GameCharacterObjectAction);

			/** Gets the GameCharacterObject that this action belongs to. */
			GameCharacterObject* getGameCharacterObject();

			/** This function is called when the action is started. */
			virtual void startAction();

			/** This function is called when the action is stopped. */
			virtual void stopAction();

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
			/** Reference to the GameCharacterObejct that this action is bound to. */
			GameCharacterObject* mCharacter;
			/** The name of the animation to play. */
			Ogre::String mAnimationName;
			/** The manner in which the animation is played when the action is started/stopped */
			AnimationBehaviour mAnimBehaviour;
			/** Flag indicating whether the animation should be restarted every time. */
			bool mRestartAnimation;
			/** Flag indicating whether the animation of this action is playing. */
			bool mAnimationPlaying;
			/** If true animation playback and stopping is based on a counter. When the animation is played a counter is
			 * increased. When the an animation is 'stopped' the counter is decreased and the animation only stops
			 * if the counter is zero. This is useful in situations where there are multiple actions that play the
			 * same animation.
			 */
			bool mPlayCounter;
	};

	// inlines

	inline GameCharacterObject* GameCharacterObjectAction::getGameCharacterObject()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mCharacter;
	}

} // namespace Myoushu

#endif

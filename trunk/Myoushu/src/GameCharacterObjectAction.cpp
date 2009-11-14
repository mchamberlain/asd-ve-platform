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
 * @file GameCharacterObjectAction.cpp
 * @author ME Chamberlain
 * @date September 2008
 */

#include "GameCharacterObjectAction.h"
#include "GameCharacterObject.h"
#include "NetworkManager.h"
#include "GameObjectFactory.h"

namespace Myoushu
{
	CLASS_NAME(GameCharacterObjectAction, "Myoushu::GameCharacterObjectAction");

	GameCharacterObjectAction::GameCharacterObjectAction() : GameObjectAction(), mCharacter(NULL), mAnimationName(""), mAnimBehaviour(AM_LOOP)
		, mRestartAnimation(false), mAnimationPlaying(false), mPlayCounter(false)
	{
	}

	GameCharacterObjectAction::GameCharacterObjectAction(const Ogre::String& name, GameCharacterObject *character, bool toggleAction
		, const Ogre::String& animationName, AnimationBehaviour animBehaviour, bool restartAnimation, bool playCounter) throw (Exception) 
		: GameObjectAction(name, character, toggleAction), mCharacter(character), mAnimationName(animationName), mAnimBehaviour(animBehaviour)
		, mRestartAnimation(restartAnimation), mAnimationPlaying(false), mPlayCounter(playCounter)
	{
	}

	GameCharacterObjectAction::~GameCharacterObjectAction()
	{
	}

	void GameCharacterObjectAction::startAction()
	{
		if (mAnimationName != "")
		{
			// If this is not a toggle action, or the animation is not playing, start playing the animation.
			if ((!mToggleAction) || (!mAnimationPlaying))
			{
				switch (mAnimBehaviour)
				{
					case AM_LOOP:
						mCharacter->playAnimation(mAnimationName, mRestartAnimation, true, mPlayCounter);
						mAnimationPlaying = true;
						break;

					case AM_ONCE:
						mCharacter->playAnimation(mAnimationName, mRestartAnimation, false, mPlayCounter);
						mAnimationPlaying = true;
						break;

					case AM_ONE_FRAME:
						mCharacter->playAnimation(mAnimationName, mRestartAnimation, false, mPlayCounter);
						mAnimationPlaying = true;
						break;

					default:
						break;
				}
			}
			else
			{
				// If this is a toggle action and the animation is playing, stop playing it
				mCharacter->stopAnimation(mAnimationName, mPlayCounter);
				mAnimationPlaying = false;
			}
		}

		// If a start callback has been set, call it
		if (mpStartCallback)
		{
			mpStartCallback->executeCallback(this);
		}
	}

	void GameCharacterObjectAction::stopAction()
	{
		// If this is a toggle action exit the function. Toggle actions do not use stop action callbacks.
		if (mToggleAction)
		{
			return;
		}

		if (mAnimationName != "")
		{
			mCharacter->stopAnimation(mAnimationName, mPlayCounter);
			mAnimationPlaying = false;
		}

		// If a stop callback has been set, call it
		if (mpStopCallback)
		{
			mpStopCallback->executeCallback(this);
		}
	}

	memUInt GameCharacterObjectAction::serialize(void *pMem, memUInt size, SerializationTarget sTarget) const throw (Exception)
	{
		char* pBuf;
		memUInt writtenSize;
		memUInt totalSize;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectAction::serialize(): pMem is NULL.");
		}

		pBuf = static_cast<char*>(pMem);
		writtenSize = 0;
		totalSize = 0;

		// Serialize the fields of this instance
		// At the moment we ignore the callback function pointers

		// First call the parent class' serialize function
		writtenSize = GameObjectAction::serialize(pBuf, size, sTarget);
		pBuf += writtenSize;
		totalSize += writtenSize;

		// Write the name of the GameCharacterObject that this action belongs too
		if (mCharacter != NULL)
		{
			if (sTarget == ST_NETWORK)
			{
				writtenSize = writeString(mCharacter->getName() + "_" + NetworkManager::getSingleton().getLocalIP().toString(), pBuf);
			}
			else
			{
				writtenSize = writeString(mCharacter->getName(), pBuf);
			}
		}
		else
		{
			writtenSize = writeString("", pBuf);
		}
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mAnimationName field
		writtenSize = writeString(mAnimationName, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mAnimBehaviour field
		writtenSize = writePrimitiveType(mAnimBehaviour, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mRestartAnimation field
		writtenSize = writePrimitiveType(mRestartAnimation, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mAnimationPlaying field
		writtenSize = writePrimitiveType(mAnimationPlaying, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mPlayCounter field
		writtenSize = writePrimitiveType(mPlayCounter, pBuf);
		pBuf += writtenSize;
		totalSize += writtenSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		return totalSize;
	}

	memUInt GameCharacterObjectAction::populateInstance(const void *pMem, memUInt size, SerializationTarget sTarget) throw (Exception)
	{
		const char* pBuf;
		memUInt readSize;
		memUInt totalSize;
		std::string characterName;

		if (pMem == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameCharacterObjectAction::serialize(): pMem is NULL.");
		}

		pBuf = static_cast<const char*>(pMem);
		readSize = 0;
		totalSize = 0;

		// Serialize the fields of this instance
		// At the moment we ignore the callback function pointers

		// First call the parent class' serialize function
		readSize = GameObjectAction::populateInstance(pMem, size, sTarget);
		pBuf += readSize;
		totalSize += readSize;

		readSize = readString(characterName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::populateInstance(): buffer too small.");
		}
		mCharacter = dynamic_cast<GameCharacterObject*>(GameObjectFactory::getSingleton().findByName(characterName));

		// Write the mAnimationName field
		readSize = readString(mAnimationName, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mAnimBehaviour field
		readSize = readPrimitiveType(mAnimBehaviour, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mRestartAnimation field
		readSize = readPrimitiveType(mRestartAnimation, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mAnimationPlaying field
		readSize = readPrimitiveType(mAnimationPlaying, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		// Write the mPlayCounter field
		readSize = readPrimitiveType(mPlayCounter, pBuf);
		pBuf += readSize;
		totalSize += readSize;
		if (totalSize > size)
		{
			throw Exception(Exception::E_BUFFER_TOO_SMALL, "GameCharacterObjectAction::serialize(): buffer too small.");
		}

		return totalSize;
	}

} // namespace Myoushu

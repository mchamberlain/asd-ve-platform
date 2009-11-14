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
 * @file InputMessage.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_MESSAGE_H
#define INPUT_MESSAGE_H

#include "InputDeviceMessage.h"

namespace Myoushu
{
	/**
	 * This class represents a message sent about an input action fired by an InputDevice.
	 * For instance, key presses or mouse movements.
	 */
	class MYOUSHU_API InputMessage : public InputDeviceMessage, public NamedObject<InputMessage>
	{
		public:
			/**
			 * Input action string if there is no action bound to the device interaction that triggered this
			 * message
			 */
			static const std::string NO_ACTION;

			/** 
			 * Constructor. 
			 */
			InputMessage(InputDevice *inputDevice = NULL);

			/**
			 * Constructor.
			 * @param deviceAction The DeviceAction for this message.
			 * @param inputAction The input action string for this message.
			 * @param deviceType The InputDevice::InputDeviceType of the InputDevice that spawned this message.
			 * @param deviceState An array of values representing the device state.
			 * 										See the description of the member variable deviceState.
			 * @param actionVector A vector associated with the input action, can be a directional vector for instance.
			 * @param inputIdentifiers The input identifier strings, i.e. 'a' if the a button is pressed on a keyboard.
			 *						  See the various constants defined in the KeyboardInputDevice, or MouseInputDevice classes
			 *						  for example.
			 * @throw Exception::E_NULL_POINTER if deviceState is NULL.
			 */
			InputMessage(InputDevice *inputDevice, DeviceAction deviceAction, const std::string& inputAction, InputDevice::InputDeviceType deviceType, const int deviceState[DEVICE_STATE_LENGTH], const Ogre::Vector3& actionVector, const std::string inputIdentifiers[MAX_NUMBER_OF_INPUT_IDENTIFIERS]) throw (Exception);

			/** Destructor */
			~InputMessage();

			CLASS_NAME_FUNCTIONS(InputMessage);

			/**
			 * Get the input action string in this message.
			 * @return The input action string of this message.
			 */
			std::string getInputAction() const;

			/**
			 * Sets the input action string of this InputMessage.
			 * @param inputAction The new input action string.
			 */
			void setInputAction(const std::string& inputAction);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(InputMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			InputMessage* clone() const;

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 */
			InputMessage& operator=(const InputMessage& message);

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 */
			InputMessage& operator=(const InputDeviceMessage& message);

			/**
			 * Serializes a class to the specified buffer.
			 * @param pMem The buffer to serialize the instance to.
			 * @param size The size of the buffer.
			 * @param sTarget The serialization target. See the description of SerializationTarget enumeration.
			 * @return 
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
			/** The InputAction */
			std::string inputAction;
	};

	// inlines
	inline std::string InputMessage::getInputAction() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return inputAction;
	}

	inline void InputMessage::setInputAction(const std::string& inputAction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->inputAction = inputAction;
	}

} // Myoushu

#endif

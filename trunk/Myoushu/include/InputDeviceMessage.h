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
 * @file InputDeviceMessage.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef INPUT_DEVICE_MESSAGE_H
#define INPUT_DEVICE_MESSAGE_H

#include <string>

#include "Poco/RWLock.h"
#include "Poco/Notification.h"
#include "Ogre.h"

#include "Platform.h"
#include "NamedObject.h"
#include "Message.h"
#include "InputDevice.h"
#include "Exception.h"
#include "Cloneable.h"

#define DEVICE_STATE_LENGTH 8

/**
 * The maximum number of input identifiers that can be encapsulated in an
 * InputDeviceMessage instance.
 */
#define MAX_NUMBER_OF_INPUT_IDENTIFIERS 6

namespace Myoushu
{
	/**
	 * This class represents a message sent about an input action fired by an InputDevice.
	 * For instance, key presses or mouse movements.
	 */
	class MYOUSHU_API InputDeviceMessage : public NamedObject<InputDeviceMessage>, public Message
	{
		public:
			/**
			 * An enumeration of device actions, DA_PRESS if a button is pressed for instance.
			 */
			enum DeviceAction
			{
				/** A button was pressed. */
				DA_PRESS,
				/** A button was released. */
				DA_RELEASE,
				/** Movement along an axis. */
				DA_MOVE
			};

			/**
			 * Index into the device state array storing the code of the button
			 * that was pressed/released on the device. Valid if the device action is
			 * DA_PRESS and for all device types.
			 */
			static const unsigned int DS_BUTTON_INDEX;
			/**
			 * Index into the device state array storing the state of all buttons on
			 * the device. Valid if the device type is IDT_MOUSE.
			 */
			static const unsigned int DS_BUTTONS_STATE_INDEX;
			/**
			 * Index into the device state array storing the value of the X axis on
			 * the device. Valid for all devices with an X axis (IDT_MOUSE, IDT_GAMEPAD) and
			 * for all device actions.
			 */
			static const unsigned int DS_X_INDEX;
			/**
			 * Index into the device state array storing the value of the Y axis on
			 * the device. Valid for all devices with a Y axis (IDT_MOUSE, IDT_GAMEPAD) and
			 * for all device actions.
			 */
			static const unsigned int DS_Y_INDEX;
			/**
			 * Index into the device state array storing the value of the Z axis on
			 * the device. Valid for all devices with a Z axis (IDT_MOUSE, IDT_GAMEPAD) and
			 * for all device actions.
			 */
			static const unsigned int DS_Z_INDEX;
			/**
			 * Index into the device state array storing the value of the change in value on
			 * the X axis since the previous DA_MOVE device action. Only valid for DA_MOVE actions.
			 */
			static const unsigned int DS_X_REL_INDEX;
			/**
			 * Index into the device state array storing the value of the change in value on
			 * the Y axis since the previous DA_MOVE device action. Only valid for DA_MOVE actions.
			 */
			static const unsigned int DS_Y_REL_INDEX;
			/**
			 * Index into the device state array storing the value of the change in value on
			 * the Z axis since the previous DA_MOVE device action. Only valid for DA_MOVE actions.
			 */
			static const unsigned int DS_Z_REL_INDEX;

			/** 
			 * Constructor. 
			 */
			InputDeviceMessage(InputDevice *inputDevice = NULL);

			/**
			 * Constructor.
			 * @param deviceAction The DeviceAction for this message.
			 * @param deviceType The InputDevice::InputDeviceType of the InputDevice that spawned this message.
			 * @param deviceState An array of values representing the device state.
			 * 										See the description of the member variable deviceState.
			 * @param actionVector A vector associated with the input action, can be a directional vector for instance.
			 * @param inputIdentifiers The input identifier strings, i.e. 'a' if the a button is pressed on a keyboard.
			 *						  See the various constants defined in the KeyboardInputDevice, or MouseInputDevice classes
			 *						  for example.
			 * @throw Exception::E_NULL_POINTER if deviceState is NULL.
			 */
			InputDeviceMessage(InputDevice *inputDevice, DeviceAction deviceAction, InputDevice::InputDeviceType deviceType, const int deviceState[DEVICE_STATE_LENGTH], const Ogre::Vector3& actionVector, const std::string inputIdentifiers[MAX_NUMBER_OF_INPUT_IDENTIFIERS]) throw (Exception);

			/** Destructor */
			~InputDeviceMessage();

			CLASS_NAME_FUNCTIONS(InputDeviceMessage);

			/**
			 * Getter for the InputDevice instance that spawned this message.
			 * @return The InputDevice instance that spawned this message.
			 */
			const InputDevice* getInputDevice() const;

			/**
			 * Setter for the InputDevice instance that spawned this message.
			 * @param inputDevice Pointer to the InputDevice instance that spawned this message.
			 */
			void setInputDevice(InputDevice *inputDevice);

			/**
			 * Get the InputDevice::InputDeviceType of the InputDevice that spawned this message.
			 * @return The InputDevice::InputDeviceType of the InputDevice that spawned this message.
			 */
			InputDevice::InputDeviceType getDeviceType() const;

			/**
			 * Get the DeviceAction in this message.
			 * @return The DeviceAction of this message.
			 */
			DeviceAction getDeviceAction() const;

			/**
			 * Gets an element in the actionVector.
			 * @param index The index of the element to return.
			 * @return The element at the specified index in the actionVector.
			 * @throw Exception::E_INDEX_OUT_OF_BOUNDS if index is out of bounds.
			 */
			Ogre::Real getActionVector(unsigned int index) const throw (Exception);

			/**
			 * Copy the values from the actionVector vector into the specified vector.
			 * @param destVector The Ogre::Vector3 reference to copy the values from actionVector too.
			 */
			void getActionVector(Ogre::Vector3& destVector) const;

			/**
			 * Gets an entry in the deviceState array.
			 * @param index The index of the entry to fetch.
			 * @return An entry in the deviceState array.
			 * @throw Exception::E_INDEX_OUT_OF_BOUNDS if index is out of bounds.
			 */
			int getDeviceState(unsigned int index) const throw (Exception);

			/**
			 * Sets the device type.
			 * @param deviceType The InputDevice::InputDeviceType that spawned this message.
			 */
			void setDeviceType(InputDevice::InputDeviceType deviceType);

			/**
			 * Sets the DeviceAction of this DeviceMessage.
			 * @param deviceAction The new DeviceAction.
			 */
			void setDeviceAction(DeviceAction deviceAction);

			/**
			 * Sets an entry in the deviceState array.
			 * @param index The index of the entry to set.
			 * @param value The new value for the entry.
			 * @throw Exception::E_INDEX_OUT_OF_BOUNDS if index is out of bounds.
			 */
			void setDeviceState(unsigned int index, int value) throw (Exception);

			/**
			 * Sets an entry in actionVector.
			 * @param index The index of the entry to set.
			 * @param value The new value for the entry.
			 * @throw Exception::E_INDEX_OUT_OF_BOUNDS if index is out of bounds.
			 */
			void setActionVector(unsigned int index, Ogre::Real value) throw (Exception);

			/**
			 * Sets an the actionVector.
			 * @param otherVector The Ogre::Vector3 to set the actionVector too.
			 */
			void setActionVector(const Ogre::Vector3& otherVector);

			/**
			 * Getter for the input identifier string, i.e. 'a' if
			 * the a button is pressed on a keyboard.
			 * @return The input identifier in a std::string.
			 */
			std::string getInputIdentifier(unsigned int index) const;

			/**
			 * Setter for the input identifier string.
			 * @param inputIdentifier The input identifier string, i.e. 'a' if the a
			 *						  button is pressed on a keyboard.
			 */
			void setInputIdentifier(unsigned int index, const std::string& inputIdentifier);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones the instance.
			 * @param dest The instance to copy this instance too.
			 * @throw Exception::E_NULL_POINTER if dest is NULL.
			 */
			void clone(InputDeviceMessage *dest) const throw (Exception);

			/**
			 * Clones the instance.
			 * @return The new cloned instance.
			 */
			InputDeviceMessage* clone() const;

			/**
			 * Sets this Message instance to be a copy of the supplied instance.
			 * @param message The Message instance to copy.
			 */
			InputDeviceMessage& operator=(const InputDeviceMessage& message);

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
			/** Read/write lock for thread safety. */
			mutable Poco::RWLock rwLock;
			/** The InputDevice instance that sent the message */
			InputDevice *inputDevice;
			/** The DeviceAction */
			DeviceAction deviceAction;
			/** The type of InputDevice that sent this message. */
			InputDevice::InputDeviceType deviceType;
			/**
			 * A List of integer values representing the device state.
			 * Depending on the type of device different values will be
			 * stored. See the DS_* constants.
			 */
			int deviceState[DEVICE_STATE_LENGTH];
			/** A vector that encodes directions for movement for example. */
			Ogre::Vector3 actionVector;
			/** Array input identifier strings, i.e. 'a' if the a button is pressed on a keyboard */
			std::string inputIdentifiers[MAX_NUMBER_OF_INPUT_IDENTIFIERS];
	};

	// inlines
	inline const InputDevice* InputDeviceMessage::getInputDevice() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return inputDevice;
	}

	inline void InputDeviceMessage::setInputDevice(InputDevice *inputDevice)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->inputDevice = inputDevice;
	}

	inline InputDevice::InputDeviceType InputDeviceMessage::getDeviceType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return deviceType;
	}

	inline InputDeviceMessage::DeviceAction InputDeviceMessage::getDeviceAction() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return deviceAction;
	}

	inline void InputDeviceMessage::getActionVector(Ogre::Vector3& destVector) const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		destVector = actionVector;
	}

	inline void InputDeviceMessage::setDeviceType(InputDevice::InputDeviceType deviceType)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->deviceType = deviceType;
	}

	inline void InputDeviceMessage::setDeviceAction(InputDeviceMessage::DeviceAction deviceAction)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->deviceAction = deviceAction;
	}

	inline void InputDeviceMessage::setActionVector(const Ogre::Vector3& otherVector)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		actionVector = otherVector;
	}

	inline std::string InputDeviceMessage::getInputIdentifier(unsigned int index) const
	{
		assert(index < MAX_NUMBER_OF_INPUT_IDENTIFIERS && "index exceeds inputIdentifiers array size.");
		Poco::ScopedRWLock lock(rwLock, false);

		return inputIdentifiers[index];
	}

	inline void InputDeviceMessage::setInputIdentifier(unsigned int index, const std::string& inputIdentifier) 
	{
		assert(index < MAX_NUMBER_OF_INPUT_IDENTIFIERS && "index exceeds inputIdentifiers array size.");
		Poco::ScopedRWLock lock(rwLock, true);

		inputIdentifiers[index] = inputIdentifier;
	}

} // Myoushu

#endif

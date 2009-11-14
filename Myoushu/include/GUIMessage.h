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
 * @file GUIMessage.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef GUI_MESSAGE_H
#define GUI_MESSAGE_H

#include "Poco/RWLock.h"
#include "Ogre.h"

#include "Platform.h"
#include "Message.h"
#include "NamedObject.h"
#include "Cloneable.h"

namespace Myoushu
{
	/**
	 * This class represents messages that can be sent about actions the GUI system should take, for example
	 * showing or hiding the cursor.
	 */
	class MYOUSHU_API GUIMessage : public Message, public NamedObject<GUIMessage>
	{
		public:
			/**
			 * Represents all of the messages that can be encapsulated in GUIMessage.
			 */
			enum GUIMessageType
			{
				/** An unknown message type */
				GM_UNKNOWN = 0,
				/** Toggle the visibility of the entire GUI */
				GM_TOGGLE_GUI_VISIBLE,
				/** Toggle the visibility of the cursor */
				GM_TOGGLE_CURSOR,
				/** Load a GUI layout */
				GM_LOAD_LAYOUT,
				/** Change the current skin of the GUI */
				GM_CHANGE_SKIN,
				/** Toggle the visibility of a widget */
				GM_TOGGLE_WIDGET_VISIBLE,
				/** Destroy a widget */
				GM_DESTROY,
				/** Create a widget */
				GM_CREATE,
				/** Message to set the widget that has mouse focus. */
				GM_SET_MOUSE_FOCUS,
				/** Message to set the widget that has key focus. */
				GM_SET_KEY_FOCUS,
				/** Translate the captions of all widgets */
				GM_TRANSLATE_WIDGETS,
				/** Translate the caption of a widget */
				GM_TRANSLATE_WIDGET
			};

			/** Constructor */
			GUIMessage();

			/** Destructor */
			~GUIMessage();

			CLASS_NAME_FUNCTIONS(GUIMessage);

			/**
			 * Gets the GUIMessageType of this message.
			 * @return the GUIMessageType of this message.
			 */
			GUIMessageType getMessageType() const;

			/**
			 * Sets the GUIMessageType of this message.
			 * @param messageType The new GUIMessageType for this message.
			 */
			void setMessageType(GUIMessageType messageType);

			/**
			 * Gets the visible flag.
			 * @return The visible flag.
			 */
			bool isVisible() const;

			/**
			 * Sets the visible flag.
			 * @param visible The value to set the visible flag too.
			 */
			void setVisible(bool visible);

			/** Gets the position of a widget, generally used with a GM_CREATE message. */
			Ogre::Vector2 getPosition() const;

			/** Sets the position of a widget, generally used with a GM_CREATE message. */
			void setPosition(const Ogre::Vector2& position);

			/** Gets the size of a widget, generally used with a GM_CREATE message. */
			Ogre::Vector2 getSize() const;

			/** Sets the size of a widget, generally used with a GM_CREATE message. */
			void setSize(const Ogre::Vector2& size);

			/** Gets the relative flag. If true positions and sizes are taken as relative to parents or screen size. */
			bool getRelative() const;

			/** Sets the relative flag. If true positions and sizes are taken as relative to parents or screen size. */
			void setRelative(bool relative);

			/** Gets the type of a widget, generally used with a GM_CREATE messages. */
			Ogre::String getWidgetType() const;

			/** Sets the type of a widget, generally used with a GM_CREATE messages. */
			void setWidgetType(const Ogre::String& widgetType);

			/** Gets the name of a widget, generally used with a GM_CREATE and GM_DESTROY messages. */
			Ogre::String getWidgetName() const;

			/** Sets the name of a widget, generally used with a GM_CREATE and GM_DESTROY messages. */
			void setWidgetName(const Ogre::String& widgetName);

			/**
			 * Gets the message field. The message field contains information related to messageType, for instance
			 * the file name of the ilayout or skin to load.
			 * @return The message field.
			 */
			Ogre::String getMessage() const;

			/**
			 * Sets the message field.
			 * @param message The message to set the message field too.
			 */
			void setMessage(const Ogre::String& message);

			/**
			 * Gets the resourceGroup field. The Ogre::ResourceGroup associated with some of the actions,
			 * for instance the resource group that contains the layout or skin files.
			 * @return The resourceGroup field.
			 */
			Ogre::String getResourceGroup() const;

			/**
			 * Sets the resourceGroup field.
			 * @param resourceGroup The string to set the resourceGroup field too.
			 */
			void setResourceGroup(const Ogre::String& resourceGroup);

			/** Clears the memeber variables of the instance. */
			void clear();

			/**
			 * Clones this message.
			 * @return A cloned instance of this message.
			 */
			GUIMessage* clone() const;

			/**
			 * Assignment operator. Assigns the values from rhs to this instance.
			 * @param rhs The GUIMessage instance to assign values from.
			 */
			GUIMessage& operator=(const GUIMessage &rhs);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** The message type */
			GUIMessageType messageType;
			/** A boolean used in messages about visibility toggling. */
			bool visible;
			/** The position of the widget to create. */
			Ogre::Vector2 mPosition;
			/** The size of the widget to create. */
			Ogre::Vector2 mSize;
			/** Whether positions and sizes should be taken as relative or absolute. */
			bool mRelative;
			/** The type of the widget to create. */
			Ogre::String mWidgetType;
			/** The name of a widget to create or destroy. */
			Ogre::String mWidgetName;
			/** A string containing the generic message. This can be the filename of the layout file to load for instance. */
			Ogre::String message;
			/**
			 * The Ogre::ResourceGroup associated with some of the actions, for instance the resource group that contains
			 * the layout or skin files.
			 */
			Ogre::String resourceGroup;
	};

	// inlines
	inline GUIMessage::GUIMessageType GUIMessage::getMessageType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return messageType;
	}

	inline void GUIMessage::setMessageType(GUIMessageType messageType)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->messageType = messageType;
	}

	inline bool GUIMessage::isVisible() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return visible;
	}

	inline void GUIMessage::setVisible(bool visible)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->visible = visible;
	}

	inline Ogre::Vector2 GUIMessage::getPosition() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mPosition;
	}

	inline void GUIMessage::setPosition(const Ogre::Vector2& position)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mPosition = position;
	}

	inline Ogre::Vector2 GUIMessage::getSize() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mSize;
	}

	inline void GUIMessage::setSize(const Ogre::Vector2& size)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mSize = size;
	}

	inline bool GUIMessage::getRelative() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mRelative;
	}

	inline void GUIMessage::setRelative(bool relative)
	{
		Poco::ScopedRWLock lock(rwLock, true);
	
		mRelative = relative;
	}

	inline Ogre::String GUIMessage::getWidgetType() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mWidgetType;
	}

	inline void GUIMessage::setWidgetType(const Ogre::String& widgetType)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mWidgetType = widgetType;
	}

	inline Ogre::String GUIMessage::getWidgetName() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mWidgetName;
	}

	inline void GUIMessage::setWidgetName(const Ogre::String& widgetName)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mWidgetName = widgetName;
	}

	inline Ogre::String GUIMessage::getMessage() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return message;
	}

	inline void GUIMessage::setMessage(const Ogre::String& message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->message = message;
	}

	inline Ogre::String GUIMessage::getResourceGroup() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return resourceGroup;
	}

	inline void GUIMessage::setResourceGroup(const Ogre::String& resourceGroup)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		this->resourceGroup = resourceGroup;
	}
} // Myoushu

#endif

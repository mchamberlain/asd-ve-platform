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
 * @file GUIManager.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>
#include "assert.h"

#include "GUIManager.h"
#include "NotificationManager.h"
#include "GUIMessage.h"
#include "GlobalLocks.h"
#include "LuaFunctor.h"
#include "ScriptManager.h"
#include "ScriptMessage.h"
#include "EngineLog.h"
#include "ObjectPool.h"

//template<>
//Myoushu::GUIManager* Ogre::Singleton<Myoushu::GUIManager>::ms_Singleton = NULL;

namespace Myoushu
{
	GUIManager::GUIManager(MyGUI::Gui *mGUI) : mGUI(mGUI)
	{
	}

	GUIManager::~GUIManager()
	{
	}

	void GUIManager::loadSkin(const Ogre::String& skinFile, const Ogre::String& resourceGroup) throw (Exception)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_CHANGE_SKIN);
		message->setMessage(skinFile);
		message->setResourceGroup(resourceGroup);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::loadLayout(const Ogre::String& layoutFile, const Ogre::String& resourceGroup, bool visible) throw (Exception)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_LOAD_LAYOUT);
		message->setMessage(layoutFile);
		message->setVisible(visible);
		message->setResourceGroup(resourceGroup);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::hideWidget(const Ogre::String& widgetName)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TOGGLE_WIDGET_VISIBLE);
		message->setVisible(false);
		message->setMessage(widgetName);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::showWidget(const Ogre::String& widgetName)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TOGGLE_WIDGET_VISIBLE);
		message->setVisible(true);
		message->setMessage(widgetName);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::destroyWidgetDelayed(const Ogre::String& widgetName)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_DESTROY);
		message->setWidgetName(widgetName);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::destroyWidget(const Ogre::String& widgetName)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_DESTROY);
		message->setWidgetName(widgetName);

		// Send the message
		NotificationManager::getSingleton().sendNotification(message);
	}

	MyGUI::WidgetPtr GUIManager::getWidget(const Ogre::String& widgetName)
	{
		Poco::ScopedRWLock lock(rwLock, false);
		Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, false);

		// Get the widget
		return mGUI->findWidgetT(widgetName);
	}

	void GUIManager::showCursor()
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TOGGLE_CURSOR);
		message->setVisible(true);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::hideCursor()
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TOGGLE_CURSOR);
		message->setVisible(false);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::createWidgetDelayed(const std::string& name, const std::string& type, const Ogre::Vector2& position, const Ogre::Vector2& size, const std::string& text, bool relative, bool visible)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_CREATE);
		message->setVisible(visible);
		message->setWidgetName(name);
		message->setWidgetType(type);
		message->setPosition(position);
		message->setSize(size);
		message->setRelative(relative);
		message->setMessage(text);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	MyGUI::WidgetPtr GUIManager::createWidget(const std::string& name, const std::string& type, const Ogre::Vector2& position, const Ogre::Vector2& size, const std::string& text, bool relative, bool visible)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_CREATE);
		message->setVisible(visible);
		message->setWidgetName(name);
		message->setWidgetType(type);
		message->setPosition(position);
		message->setSize(size);
		message->setRelative(relative);
		message->setMessage(text);

		// Send the message
		NotificationManager::getSingleton().sendNotification(message);

		return getWidget(name);
	}

	void GUIManager::setMouseFocus(const std::string& widgetName) const
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage():
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_SET_MOUSE_FOCUS);
		message->setWidgetName(widgetName);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::setKeyFocus(const std::string& widgetName) const
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage():
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_SET_KEY_FOCUS);
		message->setWidgetName(widgetName);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::clearMouseFocus() const
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage():
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_SET_MOUSE_FOCUS);
		message->setWidgetName("");

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::clearKeyFocus() const
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage():
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_SET_KEY_FOCUS);
		message->setWidgetName("");

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::translateCaptions()
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TRANSLATE_WIDGETS);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::translateCaption(const Ogre::String& widgetName)
	{
		GUIMessage *message;

		// Create the message
		//message = new GUIMessage();
		message = ObjectPool<GUIMessage>::getSingleton().get(true);
		message->setMessageType(GUIMessage::GM_TRANSLATE_WIDGET);

		// Send the message
		NotificationManager::getSingleton().queueNotification(message);
	}

	void GUIManager::registerCallbacks(const Ogre::String& widgetName)
	{
		MyGUI::WidgetPtr widget;
		Ogre::String handler;

		Poco::ScopedRWLock lock(rwLock, false);

		GlobalLocks::rwLockMyGUI.readLock();
		// Get the widget
		widget = mGUI->findWidgetT(widgetName);

		// If no widget with that name is found, do nothing
		if (widget == NULL)
		{
			GlobalLocks::rwLockMyGUI.unlock();
			return;
		}

		// Bind the events with the global engine delegates for the events which will in turn call the scripted event
		// handlers.
		// eventMouseButtonClick
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_CLICK);
		if (handler.length() != 0)
		{
			widget->eventMouseButtonClick = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseButtonClick);
		}
		// eventMouseButtonDoubleClick
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_DOUBLE_CLICK);
		if (handler.length() != 0)
		{
			widget->eventMouseButtonDoubleClick = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseButtonDoubleClick);
		}
		// eventMouseButtonPressed
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_PRESSED);
		if (handler.length() != 0)
		{
			widget->eventMouseButtonPressed = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseButtonPressed);
		}
		// eventMouseButtonReleased
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_RELEASED);
		if (handler.length() != 0)
		{
			widget->eventMouseButtonReleased = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseButtonReleased);
		}
		// eventMouseSetFocus
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_SET_FOCUS);
		if (handler.length() != 0)
		{
			widget->eventMouseSetFocus = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseSetFocus);
		}
		// eventMouseLostFocus
		handler = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_LOST_FOCUS);
		if (handler.length() != 0)
		{
			widget->eventMouseLostFocus = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMouseLostFocus);
		}
		// eventRootMouseChangeFocus
		handler = widget->getUserString(Constants::MYGUI_EVENT_ROOT_MOUSE_CHANGE_FOCUS);
		if (handler.length() != 0)
		{
			widget->eventRootMouseChangeFocus = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventRootMouseChangeFocus);
		}
		// eventKeyButtonReleased
		handler = widget->getUserString(Constants::MYGUI_EVENT_KEY_BUTTON_RELEASED);
		if (handler.length() != 0)
		{
			widget->eventKeyButtonReleased = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventKeyButtonReleased);
		}
		// eventRootKeyChangeFocus
		handler = widget->getUserString(Constants::MYGUI_EVENT_ROOT_KEY_CHANGE_FOCUS);
		if (handler.length() != 0)
		{
			widget->eventRootKeyChangeFocus = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventRootKeyChangeFocus);
		}
		// eventEditSelectAccept
		handler = widget->getUserString(Constants::MYGUI_EVENT_EDIT_SELECT_ACCEPT);
		// Only MyGUI::Edit has eventEditSelectAccept
		if ((handler.length() != 0) && (widget->getTypeName() == MyGUI::Edit::getClassTypeName()))
		{
			MyGUI::Edit *pEdit = static_cast<MyGUI::Edit*>(widget);
			pEdit->eventEditSelectAccept = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventEditSelectAccept);
		}
		// eventEditTextChange
		handler = widget->getUserString(Constants::MYGUI_EVENT_EDIT_TEXT_CHANGE);
		// Only MyGUI::Edit has eventEditTextChange
		if ((handler.length() != 0) && (widget->getTypeName() == MyGUI::Edit::getClassTypeName()))
		{
			MyGUI::Edit *pEdit = static_cast<MyGUI::Edit*>(widget);
			pEdit->eventEditTextChange = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventEditTextChange);
		}
		// eventListChangePosition
		handler = widget->getUserString(Constants::MYGUI_EVENT_LIST_CHANGE_POSITION);
		if (handler.length() != 0)
		{
			// Only MyGUI::List and MyGUI::MultiList have eventListChangePosition 
			if (widget->getTypeName() == MyGUI::List::getClassTypeName())
			{
				MyGUI::List *pList = static_cast<MyGUI::List*>(widget);
				pList->eventListChangePosition = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventListChangePosition);
			}
			else if (widget->getTypeName() == MyGUI::MultiList::getClassTypeName())
			{
				MyGUI::MultiList *pList = static_cast<MyGUI::MultiList*>(widget);
				pList->eventListChangePosition = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMultiListChangePosition);
			}
		}
		// eventListSelectAccept
		handler = widget->getUserString(Constants::MYGUI_EVENT_LIST_SELECT_ACCEPT);
		if (handler.length() != 0) 
		{
			// Only MyGUI::List and MyGUI::MultiList have eventListSelectAccept 
			if (widget->getTypeName() == MyGUI::List::getClassTypeName())
			{
				MyGUI::List *pList = static_cast<MyGUI::List*>(widget);
				pList->eventListSelectAccept = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventListSelectAccept);
			}
			else if (widget->getTypeName() == MyGUI::MultiList::getClassTypeName())
			{
				MyGUI::MultiList *pList = static_cast<MyGUI::MultiList*>(widget);
				pList->eventListSelectAccept = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventMultiListSelectAccept);
			}
		}
		// eventComboChangePosition
		handler = widget->getUserString(Constants::MYGUI_EVENT_COMBO_CHANGE_POSITION);
		if (handler.length() != 0)
		{
			// Only MyGUI::ComboBox has eventComboChangePosition 
			if (widget->getTypeName() == MyGUI::ComboBox::getClassTypeName())
			{
				MyGUI::ComboBox *pComboBox = static_cast<MyGUI::ComboBox*>(widget);
				pComboBox->eventComboChangePosition = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventComboChangePosition);
			}
		}
		// eventComboAccept
		handler = widget->getUserString(Constants::MYGUI_EVENT_COMBO_ACCEPT);
		if (handler.length() != 0) 
		{
			// Only MyGUI::Combobox has eventComboAccept 
			if (widget->getTypeName() == MyGUI::ComboBox::getClassTypeName())
			{
				MyGUI::ComboBox *pComboBox = static_cast<MyGUI::ComboBox*>(widget);
				pComboBox->eventComboAccept = MyGUI::newDelegate(GUIManager::getSingletonPtr(), &GUIManager::myguiEventComboAccept);
			}
		}

		GlobalLocks::rwLockMyGUI.unlock();
	}

	void GUIManager::myguiEventMouseButtonClick(MyGUI::WidgetPtr widget)
	{
		Ogre::String functionName;

		assert(widget != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_CLICK);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseButtonClick(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", widget);
	}

	void GUIManager::myguiEventMouseButtonDoubleClick(MyGUI::WidgetPtr widget)
	{
		Ogre::String functionName;

		assert(widget != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_DOUBLE_CLICK);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseButtonClick(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", widget);
	}

	void GUIManager::myguiEventMouseButtonPressed(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id)
	{
		Ogre::String functionName;

		assert(widget != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_PRESSED);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseButtonClick(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", widget, "int", left, "int", top);
	}

	void GUIManager::myguiEventMouseButtonReleased(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id)
	{
		Ogre::String functionName;

		assert(widget != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = widget->getUserString(Constants::MYGUI_EVENT_MOUSE_BUTTON_RELEASED);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseButtonClick(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", widget, "int", left, "int", top);
	}

	void GUIManager::myguiEventMouseSetFocus(MyGUI::WidgetPtr sender, MyGUI::WidgetPtr old)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_MOUSE_SET_FOCUS);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseSetFocus(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender, "MyGUI::Widget*", old);
	}

	void GUIManager::myguiEventMouseLostFocus(MyGUI::WidgetPtr sender, MyGUI::WidgetPtr newW)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_MOUSE_LOST_FOCUS);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventMouseLostFocus(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender, "MyGUI::Widget*", newW);
	}

	void GUIManager::myguiEventRootMouseChangeFocus(MyGUI::WidgetPtr sender, bool focus)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_ROOT_MOUSE_CHANGE_FOCUS);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventRootMouseChangeFocus(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender, "bool", focus);
	}

	void GUIManager::myguiEventKeyButtonReleased(MyGUI::WidgetPtr widget, MyGUI::KeyCode keyCode)
	{
		Ogre::String functionName;

		assert(widget != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = widget->getUserString(Constants::MYGUI_EVENT_KEY_BUTTON_RELEASED);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventKeyButtonReleased(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", widget, "MyGUI::KeyCode", keyCode);
	}

	void GUIManager::myguiEventRootKeyChangeFocus(MyGUI::WidgetPtr sender, bool focus)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_ROOT_KEY_CHANGE_FOCUS);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventRootKeyChangeFocus(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender, "bool", focus);
	}

	void GUIManager::myguiEventEditSelectAccept(MyGUI::WidgetPtr sender)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_EDIT_SELECT_ACCEPT);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventEditSelectAccept(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender);
	}

	void GUIManager::myguiEventEditTextChange(MyGUI::WidgetPtr sender)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_EDIT_TEXT_CHANGE);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventEditTextChange(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::Widget*", sender);
	}

	void GUIManager::myguiEventListSelectAccept(MyGUI::ListPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_LIST_SELECT_ACCEPT);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventListSelectAccept(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::List*", sender, "size_t", index);
	}

	void GUIManager::myguiEventListChangePosition(MyGUI::ListPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_LIST_CHANGE_POSITION);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventListChangePosition(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::List*", sender, "size_t", index);
	}

	void GUIManager::myguiEventMultiListSelectAccept(MyGUI::MultiListPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_LIST_SELECT_ACCEPT);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventListSelectAccept(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::MultiList*", sender, "size_t", index);
	}

	void GUIManager::myguiEventMultiListChangePosition(MyGUI::MultiListPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_LIST_CHANGE_POSITION);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventListChangePosition(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::MultiList*", sender, "size_t", index);
	}

	void GUIManager::myguiEventComboAccept(MyGUI::ComboBoxPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_COMBO_ACCEPT);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventComboAccept(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::ComboBox*", sender, "size_t", index);
	}

	void GUIManager::myguiEventComboChangePosition(MyGUI::ComboBoxPtr sender, size_t index)
	{
		Ogre::String functionName;

		assert(sender != NULL && "Event fired on NULL widget.");

		Poco::ScopedRWLock lock(rwLock, false);

		// Find the event hanlder function name
		functionName = sender->getUserString(Constants::MYGUI_EVENT_COMBO_CHANGE_POSITION);

		// Log an error if there is no event handler function registered
		if (functionName.length() == 0)
		{
			LOG(EngineLog::LM_ERROR, "GUIManager::myguiEventComboChangePosition(): no event handler function registered.");

			return;
		}

		// Create and send the ScriptMessage
		ScriptManager::getSingletonPtr()->executeFunction(functionName, "MyGUI::ComboBox*", sender, "size_t", index);
	}
} // Myoushu


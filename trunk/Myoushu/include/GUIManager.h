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
 * @file GUIManager.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#define NOMINMAX

#include "Poco/RWLock.h"
#include "MyGUI.h"
#include "Ogre.h"

#include "Platform.h"
#include "Singleton.h"
#include "Constants.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * This is a helper class for GUI management throughout the engine. It creates and
	 * sends messages to the GUITask.
	 */
	class MYOUSHU_API GUIManager : public Ogre::Singleton<GUIManager>
	{
		public:
			/**
			 * Constructor.
			 * @param mGUI The MyGUI::Gui instance for the GUI.
			 */
			GUIManager(MyGUI::Gui *mGUI);

			/** Destructor */
			~GUIManager();

			/**
			 * Change the current skin of the GUI to the specified one.
			 * @param skinFile Filename that contains the skin information.
			 * @param resourceGroup The Ogre::ResourceGroup that contains the skinFile.
			 * @throw Exception::E_MYGUI_EXCEPTION if an error occurs.
			 */
			void loadSkin(const Ogre::String& skinFile, const Ogre::String& resourceGroup = Constants::RG_GUI) throw (Exception);

			/**
			 * Load a layout file.
			 * @param layoutFile The layout file to load.
			 * @param resourceGroup The Ogre::ResourceGroup that contains the file.
			 * @param visible Flag that indicates if the widgets created in the layout file must be visible when this function
			 *								terminates.
			 * @throw Exception::E_MYGUI_EXCEPTION if an error occurs.
			 */
			void loadLayout(const Ogre::String& layoutFile, const Ogre::String& resourceGroup = Constants::RG_GUI, bool visible = false) throw (Exception);

			/**
			 * Hide a widget.
			 * @param widgetName The name of the MyGUI::Widget to hide.
			 */
			void hideWidget(const Ogre::String& widgetName);

			/**
			 * Show a widget.
			 * @param widgetName The name of the MyGUI::Widget to show.
			 */
			void showWidget(const Ogre::String& widgetName);

			/**
			 * Destroy the specified widget by sending a message to the GUITask to destroy
			 * the widget at its earliest convenience.
			 * @param widgetName The name of the widget to destroy.
			 */
			void destroyWidgetDelayed(const Ogre::String& widgetName);

			/**
			 * Destroy the specified widget immediately, best not used for batch deletes, see
			 * destroyWidgetDelayed().
			 * @param widgetName The name of the widget to destroy.
			 */
			void destroyWidget(const Ogre::String& widgetName);

			/** Gets a widget by name. */
			MyGUI::WidgetPtr getWidget(const Ogre::String& widgetName);

			/** Show the GUI cursor. */
			void showCursor();

			/** Hide the GUI cursor. */
			void hideCursor();

			/**
			 * Creates a MyGUI::Widget instance by send a message to the GUITask. The GUITask will create it when
			 * it next executes, then getWidget() can be used to get a pointer to the created widget. For immediate
			 * creation see createWidget().
			 * @param name The name of the widget to create, must be unique.
			 * @param type The type of the widget. Can be found with MyGUI::<T>::getClassTypeName()
			 * @param position The position of the text given in absolute or relative coordinates, depending
			 *				   the value of the relative flag.
			 * @param size The size of the static text container in absolute or relative coordinates, depending
			 *				   on the value of the relative flag.
			 * @param text The text to display.
			 * @param relative Flag inditicating whether relative or absolute coordinates should be used.
			 * @param visible Flag indicating whether the text should be visible or not.
			 */
			void createWidgetDelayed(const std::string& name, const std::string& type, const Ogre::Vector2& position, const Ogre::Vector2& size, const std::string& text, bool relative = true, bool visible = true);

			/**
			 * Creates a MyGUI::Widget instance. This version creates and returns the widget immediately.
			 * It is best not used to create large numbers of widgets, for that rather use the delayed creation
			 * version, createWidgetDelayed().
			 * @param name The name of the widget to create, must be unique.
			 * @param type The type of the widget. Can be found with MyGUI::<T>::getClassTypeName()
			 * @param position The position of the text given in absolute or relative coordinates, depending
			 *				   the value of the relative flag.
			 * @param size The size of the static text container in absolute or relative coordinates, depending
			 *				   on the value of the relative flag.
			 * @param text The text to display.
			 * @param relative Flag inditicating whether relative or absolute coordinates should be used.
			 * @param visible Flag indicating whether the text should be visible or not.
			 * @return A pointer to the created MyGUI::Widget instance or NULL if the widget could not be created.
			 */
			MyGUI::WidgetPtr createWidget(const std::string& name, const std::string& type, const Ogre::Vector2& position, const Ogre::Vector2& size, const std::string& text, bool relative = true, bool visible = true);

			/** 
			 * Sets the widget that has mouse focus.
			 * @param widgetName The name of the widget.
			 */
			void setMouseFocus(const std::string& widgetName) const;

			/** 
			 * Sets the widget that has key focus.
			 * @param widgetName The name of the widget.
			 */
			void setKeyFocus(const std::string& widgetName) const;

			/** Removes mouse focus from whatever widget currently has focus. */
			void clearMouseFocus() const;

			/** Removes key focus from whatever widget currently has focus. */
			void clearKeyFocus() const;

			/**
			 * Using the currently loaded translations in DefaultTranslation and
			 * the untranslatedCaption userdata key-value pair in a widget, this method
			 * sets the captions of all widgets to their translated versions.
			 */
			void translateCaptions();

			/**
			 * Using the currently loaded translation in DefaultTranslation and
			 * the untranslatedCaption userdata key-value pair in the widget, this method
			 * sets the caption of the specified widget to its translated version.
			 * @param widgetName The name of the widget to translate the caption of.
			 */
			void translateCaption(const Ogre::String& widgetName);
			
			/**
			 * Register all the LUA based event handlers for a widget. The MyGUI::UserData associated
			 * with the specified MyGUI::Widget is searched for specific event handler definitions and these
			 * are registered with the engine.
			 *
			 * The event handlers must be specified with the same members you would use to create delegates for
			 * events, i.e. eventMouseButtonClick is the key, the data is the function name to use as event handler in
			 * LUA. You are free to choose the function name.
			 * @param widgetName The name of the MyGUI::Widget to register the event handlers for.
			 */
			void registerCallbacks(const Ogre::String& widgetName);

			/**
			 * Global event handler for the MyGUI eventMouseButtonClick. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param widget The MyGUI::Widget that was clicked.
			 */
			void myguiEventMouseButtonClick(MyGUI::WidgetPtr widget);

			/**
			 * Global event handler for the MyGUI eventMouseButtonDoubleClick. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param widget The MyGUI::Widget that was doubleClicked.
			 */
			void myguiEventMouseButtonDoubleClick(MyGUI::WidgetPtr widget);

			/**
			 * Global event handler for the MyGUI eventMouseButtonDoubleClick. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param widget The MyGUI::Widget that sent the event.
			 * @param left Left (X) mouse coordinate
			 * @param top Top (Y) mouse coordinate
			 * @param id MyGUI::MouseButton instance for the mouse button that was pressed.
			 */
			void myguiEventMouseButtonPressed(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id);

			/**
			 * Global event handler for the MyGUI eventMouseButtonDoubleClick. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param widget The MyGUI::Widget that sent the event.
			 * @param left Left (X) mouse coordinate
			 * @param top Top (Y) mouse coordinate
			 * @param id MyGUI::MouseButton instance for the mouse button that was released.
			 */
			void myguiEventMouseButtonReleased(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id);

			/**
			 * Global event handler for the MyGUI eventMouseSetFocus. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that got focus.
			 * @param old The MyGUI::Widget that lost focus.
			 */
			void myguiEventMouseSetFocus(MyGUI::WidgetPtr sender, MyGUI::WidgetPtr old);

			/**
			 * Global event handler for the MyGUI eventRootMouseChangeFocus. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that sent the event.
			 * @param focus True if this sender got focus, false if it lost focus.
			 */
			void myguiEventRootMouseChangeFocus(MyGUI::WidgetPtr sender, bool focus);

			/**
			 * Global event handler for the MyGUI eventMouseLostFocus. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that lost focus.
			 * @param old The MyGUI::Widget that got focus.
			 */
			void myguiEventMouseLostFocus(MyGUI::WidgetPtr sender, MyGUI::WidgetPtr newW);

			/**
			 * Global event handler for the MyGUI eventKeyButtonReleased. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param widget The MyGUI::Widget that was clicked.
			 */
			void myguiEventKeyButtonReleased(MyGUI::WidgetPtr widget, MyGUI::KeyCode keyCode);

			/**
			 * Global event handler for the MyGUI eventRootKeyChangeFocus. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that sent the event.
			 * @param focus True if this sender got focus, false if it lost focus.
			 */
			void myguiEventRootKeyChangeFocus(MyGUI::WidgetPtr sender, bool focus);

			/**
			 * Global event handler for the MyGUI eventEditSelectAccept. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that sent the event.
			 */
			void myguiEventEditSelectAccept(MyGUI::WidgetPtr sender);

			/**
			 * Global event handler for the MyGUI eventEditTextChanged. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::Widget that sent the event.
			 */
			void myguiEventEditTextChange(MyGUI::WidgetPtr sender);

			/**
			 * Global event handler for the MyGUI eventListSelectAccept. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::List that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventListSelectAccept(MyGUI::ListPtr sender, size_t index);

			/**
			 * Global event handler for the MyGUI eventListChangePosition. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::List that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventListChangePosition(MyGUI::ListPtr sender, size_t index);

			/**
			 * Global event handler for the MyGUI eventListSelectAccept. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::List that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventMultiListSelectAccept(MyGUI::MultiListPtr sender, size_t index);

			/**
			 * Global event handler for the MyGUI eventListChangePosition. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::List that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventMultiListChangePosition(MyGUI::MultiListPtr sender, size_t index);

			/**
			 * Global event handler for the MyGUI eventComboBoxAccept. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::ComboBox that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventComboAccept(MyGUI::ComboBoxPtr sender, size_t index);

			/**
			 * Global event handler for the MyGUI eventComboBoxChangePosition. Used by all widgets that have scripted (LUA)
			 * event handlers for this event. This function schedules a call to the scripted event handler of the widget.
			 * @param sender The MyGUI::ComboBox that sent the event.
			 * @param index The index of the 
			 */
			void myguiEventComboChangePosition(MyGUI::ComboBoxPtr sender, size_t index);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** The MyGUI::Gui instance */
			MyGUI::Gui *mGUI;

			/** Nullary Constructor */
			GUIManager();
	};
} // Myoushu

#endif

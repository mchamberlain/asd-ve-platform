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
 * @file MyGUIConsole.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef MYGUI_CONSOLE_H
#define MYGUI_CONSOLE_H

#include "MyGUI.h"
#include "Ogre.h"

#include "Console.h"
#include "Constants.h"

namespace Myoushu
{
	/** A MyGUI based implementation of the developers console in the engine. */
	class MYOUSHU_API MyGUIConsole : public Console
	{
		public:
			/** The layout filename */
			static const Ogre::String CONSOLE_LAYOUT_FILE;
			/** The name of the console window */
			static const Ogre::String CONSOLE_WINDOW;
			/** The name of the list box in the console window */
			static const Ogre::String CONSOLE_WINDOW_LIST;
			/** The name of the text input box in the console window */
			static const Ogre::String CONSOLE_WINDOW_EDIT;

			/**
			 * Constructor.
			 * @param consoleWindowFile The filename of the console window layout file.
			 * @param resourceGroup The Ogre resource group it can be found in.
			 * @param visible Should it be visible initially.
			 */
			MyGUIConsole(const Ogre::String& consoleWindow = CONSOLE_LAYOUT_FILE, const Ogre::String& resourceGroup = Constants::RG_GUI, bool visible = false);

			/** Destructor. Unloads and destroys the console window. */
			~MyGUIConsole();

			/**
			 * In addition to setting the visible flag, this function makes the Console
			 * visible or not to the user based on the value of visible.
			 * @param visible The new value for the visible flag.
			 */
			void setVisible(bool visible);

			/**
			 * Toggles Console visibility.
			 */
			void toggleVisible();

			/**
			 * Update the GUI. This will be called by the GUITask periodically. Typically this
			 * can be used to flush an output stream to the console window.
			 */
			void update();

			/**
			 * This function is called by MyGUI when a key is pressed anywhere in the console window.
			 * @param widget The MyGUI::Widget that had focus when the key was pressed.
			 * @param keyCode The integer key code.
			 * @param keyChar The character representing the key.
			 */
			void InputCallbackKeyPressed(MyGUI::WidgetPtr widget, MyGUI::KeyCode keyCode, MyGUI::Char keyChar);

		private:
			/** Vector of all widgets in the Console window */
			MyGUI::VectorWidgetPtr widgetVector;
			/** The main output text box of the console */
			MyGUI::List *listWidget;

			/**
			 * Initialize the specified widget and all of its children
			 * @param widget Widget to initialize
			 */
			void initializeWidgets(MyGUI::WidgetPtr widget);
	};
} // Myoushu

#endif

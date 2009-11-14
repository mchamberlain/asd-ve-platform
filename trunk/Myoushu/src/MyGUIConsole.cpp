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
 * @file MyGUIConsole.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <iostream>

#include "MyGUIConsole.h"
#include "GlobalLocks.h"
#include "EngineLog.h"
#include "GUIManager.h"
#include "ScriptManager.h"

namespace Myoushu
{
	const Ogre::String MyGUIConsole::CONSOLE_LAYOUT_FILE = "ConsoleWindow.layout";
	const Ogre::String MyGUIConsole::CONSOLE_WINDOW = "ConsoleWindow";
	const Ogre::String MyGUIConsole::CONSOLE_WINDOW_LIST = "ConsoleWindowList";
	const Ogre::String MyGUIConsole::CONSOLE_WINDOW_EDIT = "ConsoleWindowEdit";

	MyGUIConsole::MyGUIConsole(const Ogre::String& consoleWindow, const Ogre::String& resourceGroup, bool visible)
	{
		MyGUI::VectorWidgetPtr::iterator iter;
		MyGUI::WidgetPtr widget;

		rwLock.writeLock();
		GlobalLocks::rwLockMyGUI.writeLock();

		listWidget = NULL;

		// Load the specified layout
		widgetVector = MyGUI::LayoutManager::getInstance().load(consoleWindow, resourceGroup);
		rwLock.unlock();

		Poco::ScopedRWLock lock(rwLock, false);
		// Set the visibility of the widgets
		for (iter = widgetVector.begin(); iter != widgetVector.end(); ++iter)
		{
			// Setup the key pressed callback
			widget = *iter;

			initializeWidgets(widget);

			if (visible)
			{
				widget->show();
			}
			else
			{
				widget->hide();
			}
		}
		GlobalLocks::rwLockMyGUI.unlock();
	}

	MyGUIConsole::~MyGUIConsole()
	{
		MyGUI::VectorWidgetPtr::iterator iter;

		Poco::ScopedRWLock lock(rwLock, false);

		// Use the GUIManager to destroy all of the console window widgets
		for (iter = widgetVector.begin(); iter != widgetVector.end(); ++iter)
		{
			GUIManager::getSingleton().destroyWidget((*iter)->getName());
		}

	}

	void MyGUIConsole::initializeWidgets(MyGUI::WidgetPtr widget)
	{
		// Setup the key pressed callback
		widget->eventKeyButtonPressed = MyGUI::newDelegate(this, &MyGUIConsole::InputCallbackKeyPressed);

		if (widget->getName() == CONSOLE_WINDOW_LIST)
		{
			listWidget = dynamic_cast<MyGUI::List*>(widget);
		}

		MyGUI::EnumeratorWidgetPtr childWidgetPtrEnum = widget->getEnumerator();

		while (childWidgetPtrEnum.next())
		{
			initializeWidgets(childWidgetPtrEnum.current());
		}
	}

	void MyGUIConsole::setVisible(bool visible)
	{
		MyGUI::VectorWidgetPtr::iterator iter;
		MyGUI::WidgetPtr pWidget;

		// Set the value of visible
		rwLock.writeLock();
		// If the value of visible doesn't change, exit the function
		if (this->visible == visible)
		{
			rwLock.unlock();

			return;
		}

		this->visible = visible;
		rwLock.unlock();

		Poco::ScopedRWLock lock(rwLock, false);

		GlobalLocks::rwLockMyGUI.readLock();
		// Set the visibility of the widgets
		for (iter = widgetVector.begin(); iter != widgetVector.end(); ++iter)
		{
			pWidget = *iter;

			if (visible)
			{
				pWidget->show();
			}
			else
			{
				pWidget->hide();
				if (pWidget->getName() == CONSOLE_WINDOW_EDIT)
				{
				}
			}
		}

		// When the console becomes visible, give the text box widget key focus. When the console disappears
		// remove key focus from the text box widget.
		pWidget = MyGUI::Gui::getInstance().findWidgetT(CONSOLE_WINDOW_EDIT);
		if (visible)
		{
			MyGUI::InputManager::getInstance().setKeyFocusWidget(pWidget);
		}
		else
		{
			MyGUI::InputManager::getInstance().resetKeyFocusWidget(pWidget);
		}

		GlobalLocks::rwLockMyGUI.unlock();
	}

	void MyGUIConsole::toggleVisible()
	{
		setVisible(!visible);
	}

	void MyGUIConsole::update()
	{
		std::string message;
		std::string line;
		unsigned int i;
		unsigned int j;
		unsigned int maxCharCnt;

		Poco::ScopedRWLock lock(rwLock, true);

		message = messageStream.str();

		if ((listWidget != NULL) && (message.length() > 0))
		{
			GlobalLocks::rwLockMyGUI.writeLock();

			// Determine the max character count per line, at the moment the font size is hardcoded, still
			// have to figure out how to get that from MyGUI.
			maxCharCnt = (unsigned int) listWidget->getSize().width / 7;

			// Take the messageStream string and split it up into separate strings for every line it contains
			j = 0;
			for (i = 0; i < message.length(); i++)
			{
				if ((message[i] == '\n') || (i - j == maxCharCnt))
				{
					// If it is an empty line, just add the empty string to the list
					if (i - j == 0)
					{
						listWidget->addItem("");
					}
					else
					{
						// Get the line
						line = message.substr(j, i - j);
						listWidget->addItem(line);
					}

					if (message[i] == '\n')
					{
						// Set the start index (j) for the next line
						j = i + 1;
					}
					else
					{
						j = i;
					}
				}
			}
			// We must scroll if the last item is not visible
			listWidget->beginToItemLast();

			// Clear the message stream
			messageStream.str("");
			GlobalLocks::rwLockMyGUI.unlock();
		}
	}

	void MyGUIConsole::InputCallbackKeyPressed(MyGUI::WidgetPtr widget, MyGUI::KeyCode keyCode, MyGUI::Char keyChar)
	{
		MyGUI::Edit *editBox;
		std::string text;

		// Ensure that widget is not NULL
		if (widget == NULL)
		{
			LOG(EngineLog::LM_WARNING, "MyGUIConsole::InputCallbackKeyPressed(): widget is NULL.");

			return;
		}

		if (widget->getName() == CONSOLE_WINDOW_EDIT)
		{
			// Execute whatever is in the text input box as a script
			if (keyCode == MyGUI::KC_RETURN)
			{
				editBox = dynamic_cast<MyGUI::Edit*>(widget);
				if (editBox != NULL)
				{
					// Get the text from the input text box
					text = editBox->getOnlyText();

					// Add it to the console window
					messageStream << text << std::endl;

					// Clear the input text box
					editBox->setOnlyText("");

					// Schedule the command for execution
					ScriptManager::getSingleton().executeScript(text);
				}
			}
		}

		// Hide the window if escape is pressed
		if (keyCode == MyGUI::KC_ESCAPE)
		{
			setVisible(false);
		}
	}

} // Myoushu

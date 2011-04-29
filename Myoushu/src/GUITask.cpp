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
 * @file GUITask.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <list>
#include <string>
#include <iostream>

#define NOMINMAX

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"
#include "MyGUI.h"
#include "Ogre.h"

#include "GUITask.h"
#include "NamedObject.h"
#include "GlobalLocks.h"
#include "NotificationManager.h"
#include "Exception.h"
#include "Constants.h"
#include "TimerTaskMessage.h"
#include "EngineLog.h"
#include "InputMessage.h"
#include "GUIMessage.h"
#include "GUIManager.h"
#include "ScriptManager.h"
#include "EngineLog.h"
#include "TimerTask.h"
#include "InputActionManager.h"
#include "DefaultTranslation.h"

namespace Myoushu
{
	CLASS_NAME(GUITask, "Myoushu::GUITask");

	GUITask::GUITask(int priority, const std::string& name, unsigned long executionInterval, unsigned int iterationLimit) : Task(name, priority, executionInterval, iterationLimit), mpPlatform(NULL), mpGUI(NULL), mpConsole(NULL), mpGUIManager(NULL), mGUIDisabledCallbacks(false)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mpGUI = NULL;
		mpGUIManager = NULL;
		mpConsole = NULL;
		state = TS_CREATED;
	}

	GUITask::GUITask() : Task("GUITask", 0), mpPlatform(NULL), mpGUI(NULL), mpConsole(NULL), mpGUIManager(NULL), mGUIDisabledCallbacks(false)
	{
	}

	GUITask::~GUITask()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting " << this->getClassName() << ": " << this->getName());

		// Remove message queue
		NotificationManager::getSingleton().removeQueue((memUInt) this);

	}

	void GUITask::init() throw (Exception)
	{
		Ogre::Root *root;
		Ogre::RenderWindow *renderWindow;

		Poco::ScopedRWLock lock(rwLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Initializing GUITask.");

		// Get the Ogre RenderWindow
		GlobalLocks::rwLockOgreRoot.readLock();

		root = Ogre::Root::getSingletonPtr();
		if (root == NULL)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			throw Exception(Exception::E_NULL_POINTER, "GUITask::init(): Ogre::Root doesn't exist.");
		}
		renderWindow = dynamic_cast<Ogre::RenderWindow*>(root->getRenderTarget(Constants::MAIN_RENDER_TARGET));
		if (renderWindow == NULL)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			throw Exception(Exception::E_NULL_POINTER, "GUITask::init(): The RenderWindow doesn't exist.");
		}

		GlobalLocks::rwLockOgreRoot.unlock();

		try
		{
			// Create and initialize the GUI
			GlobalLocks::rwLockMyGUI.writeLock();
			GlobalLocks::rwLockOgreRoot.writeLock();

			// New in MyGUI 3.0.0, init the MyGUI::OgrePlatform instance
			if (mpPlatform == NULL)
			{
				mpPlatform = new MyGUI::OgrePlatform();
				mpPlatform->initialise(renderWindow);
			}

			if (mpGUI == NULL)
			{
				mpGUI = new MyGUI::Gui();
				// Create the GUIManager
				LOG(EngineLog::LM_INFO_ENGINE, "Creating the GUIManager");
				mpGUIManager = new GUIManager(mpGUI);
			}
			mpGUI->initialise("core.xml", Constants::RG_GUI);

			GlobalLocks::rwLockOgreRoot.unlock();
			GlobalLocks::rwLockMyGUI.unlock();

			if (mpConsole == NULL)
			{
				// Create the Console
				LOG(EngineLog::LM_INFO_ENGINE, "Creating the Console");
				mpConsole = new MyGUIConsole();
				// Redirect Lua output to the console
				mpConsole->redirectLuaOutputToConsole(ScriptManager::getSingleton().getDefaultLuaParser());
			}
			EngineLog::getSingleton().setSecondaryStream(mpConsole);
		}
		catch (Ogre::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			GlobalLocks::rwLockMyGUI.unlock();
			throw Exception(Exception::E_OGRE_EXCEPTION, e.what());
		}
		catch (MyGUI::Exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			GlobalLocks::rwLockMyGUI.unlock();
			throw Exception(Exception::E_MYGUI_EXCEPTION, e.getFullDescription());
		}
		catch (std::exception& e)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			GlobalLocks::rwLockMyGUI.unlock();
			throw Exception(Exception::E_STD_EXCEPTION, e.what());
		}
		catch (...)
		{
			GlobalLocks::rwLockOgreRoot.unlock();
			GlobalLocks::rwLockMyGUI.unlock();
			throw Exception(Exception::E_UNKNOWN_ERROR, "Unknown error during GUITask init.");
		}

		// Register the GUITask message handler functions
		//NotificationManager::getSingleton().addObserver<GUITask, TimerTaskMessage>(this, &GUITask::receiveTimerTaskMessage);
		NotificationManager::getSingleton().addObserver<GUITask, InputMessage>(this, &GUITask::receiveInputMessage);
		NotificationManager::getSingleton().addObserver<GUITask, GUIMessage>(this, &GUITask::receiveGUIMessage);

		//try
		//{
		//	// Schedule the GUI init script for execution
		//	ScriptManager::getSingleton().executeScriptFile(Constants::GUI_INIT_SCRIPT_FILENAME);
		//}
		//catch (Exception& e)
		//{
		//	LOG(EngineLog::LM_WARNING, "Error loading GUIInit.lua script: " << e.what() << ". Continuing without it.");
		//}

		state = TS_INITIALIZED;
	}

	void GUITask::suspend()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		state = TS_SUSPENDED;
	}

	void GUITask::execute(unsigned long timeDelta)
	{
		rwLock.writeLock();

		if (state != TS_RUNNING)
		{
			state = TS_RUNNING;
		}
		rwLock.unlock();

		if (mpConsole)
		{
			mpConsole->update();
		}

		// Tell the NotificationManager to deliver all queued messages for this task
		NotificationManager::getSingleton().dispatchQueuedNotifications((memUInt) this);

		GlobalLocks::rwLockMyGUI.writeLock();
		// Inject the time into MyGUI
		// delta is in microseconds, we have to convert it to seconds
		mpGUI->injectFrameEntered(((double) timeDelta) / MICROSECONDS_IN_SECOND);

		GlobalLocks::rwLockMyGUI.unlock();
	}

	void GUITask::kill()
	{
		Poco::ScopedRWLock lock(rwLock, true);

		if (mpConsole)
		{
			EngineLog::getSingleton().setSecondaryStream(NULL);
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying the Console");
			delete mpConsole;
			mpConsole = NULL;
		}

		if (mpGUI)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Shutting down MyGUI");
			GlobalLocks::rwLockMyGUI.writeLock();
			mpGUI->shutdown();
			delete mpGUI;
			mpGUI = NULL;
			GlobalLocks::rwLockMyGUI.unlock();
		}

		// Destroy the GUIManager singleton
		if (mpGUIManager)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying the GUIManager");
			delete mpGUIManager;
			mpGUIManager = NULL;
		}

		// Remove the message handler functions
		//NotificationManager::getSingleton().removeObserver<GUITask, TimerTaskMessage>(this, &GUITask::receiveTimerTaskMessage);
		NotificationManager::getSingleton().removeObserver<GUITask, InputMessage>(this, &GUITask::receiveInputMessage);
		NotificationManager::getSingleton().removeObserver<GUITask, GUIMessage>(this, &GUITask::receiveGUIMessage);

		state = TS_KILLED;
	}

	void GUITask::receiveTimerTaskMessage(const Poco::AutoPtr<TimerTaskMessage>& message)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GUITask::receiveTimerTaskMessage(): NULL TimerTaskMessage received.");

			return;
		}

		switch (message->getMessageType())
		{
			case TimerTaskMessage::TM_UPDATE:
				// If time has passed since the last frame, update the GUI
				if (message->getDelta() > 0)
				{
					GlobalLocks::rwLockMyGUI.writeLock();
					// Inject the time into MyGUI
					// delta is in microseconds, we have to convert it to seconds
					mpGUI->injectFrameEntered(((Ogre::Real) message->getDelta()) / ((Ogre::Real) MICROSECONDS_IN_SECOND));

					GlobalLocks::rwLockMyGUI.unlock();
				}
			break;
			default:
				LOG(EngineLog::LM_WARNING, "GUITask::receiveTimerTaskMessage(): Unknown TimerTaskMessage received.");
			break;
		}
	}

	void GUITask::receiveInputMessage(const Poco::AutoPtr<InputMessage>& message)
	{
		// Get a read lock on the GUITask and a write lock on the MyGUI library.
		Poco::ScopedRWLock lock(rwLock, false);
		Poco::ScopedRWLock myGUILock(GlobalLocks::rwLockMyGUI, false);

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GUITask::receiveInputMessage(): NULL InputMessage received.");

			return;
		}

		// Check the device type. MyGUI has specific functions for keyboard and mouse input
		if (message->getDeviceType() == InputDevice::IDT_KEYBOARD)
		{
			switch (message->getDeviceAction())
			{
				// Button pressed
				case InputMessage::DA_PRESS:
					mpGUI->injectKeyPress(MyGUI::KeyCode(static_cast<MyGUI::KeyCode::Enum>(message->getDeviceState(InputMessage::DS_BUTTON_INDEX))));
				break;
				// Button released
				case InputMessage::DA_RELEASE:
					mpGUI->injectKeyRelease(MyGUI::KeyCode(static_cast<MyGUI::KeyCode::Enum>(message->getDeviceState(InputMessage::DS_BUTTON_INDEX))));
				break;
				// Unknown action, shouldn't happen...
				default:
					LOG(EngineLog::LM_WARNING, "GUITask::receiveInputMessage(): Unknown DeviceAction received.");
				break;
			}
		}
		else if (message->getDeviceType() == InputDevice::IDT_MOUSE)
		{
			switch (message->getDeviceAction())
			{
				// Button pressed
				case InputMessage::DA_PRESS:
					mpGUI->injectMousePress(message->getDeviceState(InputMessage::DS_X_INDEX),
																 message->getDeviceState(InputMessage::DS_Y_INDEX),
																 MyGUI::MouseButton(static_cast<MyGUI::MouseButton::Enum>(message->getDeviceState(InputMessage::DS_BUTTON_INDEX))));
				break;
				// Button released
				case InputMessage::DA_RELEASE:
					mpGUI->injectMouseRelease(message->getDeviceState(InputMessage::DS_X_INDEX),
																	 message->getDeviceState(InputMessage::DS_Y_INDEX),
																	 MyGUI::MouseButton(static_cast<MyGUI::MouseButton::Enum>(message->getDeviceState(InputMessage::DS_BUTTON_INDEX))));
				break;
				// Mouse moved
				case InputMessage::DA_MOVE:
					mpGUI->injectMouseMove(message->getDeviceState(InputMessage::DS_X_INDEX),
																message->getDeviceState(InputMessage::DS_Y_INDEX),
																message->getDeviceState(InputMessage::DS_Z_INDEX));
				break;
				// Unknown action, shouldn't get here
				default:
					LOG(EngineLog::LM_WARNING, "GUITask::receiveInputMessage(): Unknown DeviceAction received.");
				break;
			}
		}
		else
		{
			LOG(EngineLog::LM_WARNING, "GUITask::receiveInputMessage(): Unknown InputDeviceType received.");
		}

		// Check whether any GUI element has focus, if there is an element with focus, disable input action
		// callbacks, otherwise ensure that callbacks are enabled
		if (MyGUI::InputManager::getInstance().isFocusKey())
		{
			if (!InputActionManager::getSingleton().isCallbacksDisabled())
			{
				mGUIDisabledCallbacks = true;
				// A widget has key focus, disable input action callbacks
				InputActionManager::getSingleton().disableCallbacks();
			}
		}
		else
		{
			if (mGUIDisabledCallbacks)
			{
				// No widgets have key focus, enable input action callbacks
				InputActionManager::getSingleton().enableCallbacks();
				mGUIDisabledCallbacks = false;
			}
		}
	}

	void GUITask::receiveGUIMessage(const Poco::AutoPtr<GUIMessage>& message)
	{
		MyGUI::VectorWidgetPtr widgetVector;
		MyGUI::VectorWidgetPtr::iterator iter;
		MyGUI::WidgetPtr widget;

		widget = NULL;

		if (message.get() == NULL)
		{
			LOG(EngineLog::LM_WARNING, "GUITask::receiveGUIMessage(): NULL GUIMessage received.");

			return;
		}

		switch (message->getMessageType())
		{
			case GUIMessage::GM_TOGGLE_GUI_VISIBLE:
			break;
			case GUIMessage::GM_TOGGLE_CURSOR:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					// Show or hide the mouse pointer
					if (message->isVisible())
					{
						mpGUI->showPointer();
					}
					else
					{
						mpGUI->hidePointer();
					}
				}
			break;
			case GUIMessage::GM_LOAD_LAYOUT:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					// Load the specified layout
					widgetVector = MyGUI::LayoutManager::getInstance().load(message->getMessage(), message->getResourceGroup());

					// Set the visibility of the widgets
					for (iter = widgetVector.begin(); iter != widgetVector.end(); ++iter)
					{
						if (message->isVisible())
						{
							(*iter)->show();
						}
						else
						{
							(*iter)->hide();
						}
					}
				}
			break;
			case GUIMessage::GM_CHANGE_SKIN:
				// Load the new skin
				MyGUI::SkinManager::getInstance().load(message->getMessage(), message->getResourceGroup());
			break;
			case GUIMessage::GM_TOGGLE_WIDGET_VISIBLE:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					MyGUI::WidgetPtr pFocusWidget = MyGUI::InputManager::getInstance().getKeyFocusWidget();
					widget = mpGUI->findWidgetT(message->getMessage());

					if (widget == NULL)
					{
						LOG(EngineLog::LM_ERROR, "Can't find MyGUI Widget: " << message->getMessage());
					}
					else
					{
						if (message->isVisible())
						{
							widget->show();
						}
						else
						{
							widget->hide();
							if (widget == pFocusWidget)
							{
								// If the widget that we are hiding had focus, we have to remove the focus
								// MyGUI should do this automatically on a widget that is being hidden...
								MyGUI::InputManager::getInstance().resetKeyFocusWidget();
							}
						}
					}
				}
			break;
			case GUIMessage::GM_DESTROY:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					// Find the widget
					widget = mpGUI->findWidgetT(message->getWidgetName());

					// If it was found, destroy it
					if (widget != NULL)
					{
						mpGUI->destroyWidget(widget);
					}
					else
					{
						LOG(EngineLog::LM_ERROR, "Can't find MyGUI Widget: " << message->getMessage());
					}
				}
			break;
			case GUIMessage::GM_CREATE:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					// Create the widget
					if (message->getRelative())
					{
						widget = mpGUI->createWidgetRealT(message->getWidgetType(), message->getWidgetType(), message->getPosition().x, message->getPosition().y, message->getSize().x, message->getSize().y, MyGUI::ALIGN_CENTER, "Back", message->getWidgetName());
					}
					else
					{
						widget = mpGUI->createWidgetT(message->getWidgetType(), message->getWidgetType(), message->getPosition().x, message->getPosition().y, message->getSize().x, message->getSize().y, MyGUI::ALIGN_CENTER, "Back", message->getWidgetName());
					}

					widget->setVisible( message->isVisible() );
					widget->setCaption( MyGUI::UString( message->getMessage() ) );

					// If it could not be created, log an error
					if (widget == NULL)
					{
						LOG(EngineLog::LM_ERROR, "Can't create MyGUI Widget: " << message->getWidgetName());
					}
				}
			break;
			case GUIMessage::GM_SET_MOUSE_FOCUS:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					if (message->getWidgetName() != "")
					{
						// TODO: unimplemented
					}
					else
					{
						MyGUI::InputManager::getInstance().resetMouseFocusWidget();
					}
				}
			break;
			case GUIMessage::GM_SET_KEY_FOCUS:
				{
					Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

					if (message->getWidgetName() != "")
					{
						MyGUI::WidgetPtr pWidget = mpGUI->findWidgetT(message->getWidgetName());
						if (pWidget != NULL)
						{
							MyGUI::InputManager::getInstance().setKeyFocusWidget(pWidget);
						}
						else
						{
							LOG(EngineLog::LM_WARNING, "GUITask::receiveGUIMessage(): GUIMessage::GM_SET_KEY_FOCUS: no widget with name: " + message->getWidgetName());
						}
					}
					else
					{
						MyGUI::InputManager::getInstance().resetKeyFocusWidget();
					}
				}
			break;
			case GUIMessage::GM_TRANSLATE_WIDGETS:
				translateAllCaptions();
			break;
			case GUIMessage::GM_TRANSLATE_WIDGET:
				translateCaption(message->getMessage());
			break;
			case GUIMessage::GM_UNKNOWN:
			default:
				LOG(EngineLog::LM_WARNING, "GUITask::receiveGUIMessage(): Unknown GUIMessage received.");
			break;
		}
	}

	void GUITask::translateAllCaptions()
	{
		MyGUI::VectorWidgetPtr::const_iterator widgetPtrIter;
		std::list<MyGUI::EnumeratorWidgetPtr> widgetEnumStack;
		DefaultTranslation *pTranslation;
		std::string untranslatedCaption;
		Ogre::UTFString translatedString;

		Poco::ScopedRWLock lock(rwLock, false);
		Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

		// Get the DefaultTranslation singleton to be used to translate captions
		pTranslation = DefaultTranslation::getSingletonPtr();

		// Get enumerator over all widgets that are children of the MyGUI root widget
		// and push on to the stack of widget enumerators. We push an enumerator of child widgets
		// onto the stack for each widget, so that we can process all widgets in levels of the widget tree
		widgetEnumStack.push_front(mpGUI->getEnumerator());

		while (!widgetEnumStack.empty())
		{
			// Get the widget enumerator at the top of the stack
			MyGUI::EnumeratorWidgetPtr widgetEnum = widgetEnumStack.front();
			// Remove the top element from the stack
			widgetEnumStack.pop_front();

			// Translate the captions of all widgets
			while (widgetEnum.next())
			{
				// Get the current widget from the enumerator
				const MyGUI::WidgetPtr pWidget = widgetEnum.current();
				
				// Push the enumerator of the children of the current widget on to the widget enumerator stack
				widgetEnumStack.push_front(pWidget->getEnumerator());
				
				translatedString = "";
				// Use the unstranslatedCaption userString value as the untranslated caption of the widget
				untranslatedCaption = pWidget->getUserString("untranslatedCaption");
				// If we couldn't find 'untranslatedCaption' we try some alternatives, 'untranslatedcaption',
				// 'UntranslatedCaption' and 'UNTRANSLATEDCAPTION'
				if (untranslatedCaption == "")
				{
					untranslatedCaption = pWidget->getUserString("untranslatedcaption");
					if (untranslatedCaption == "")
					{
						untranslatedCaption = pWidget->getUserString("UntranslatedCaption");
						if (untranslatedCaption == "")
						{
							untranslatedCaption = pWidget->getUserString("UNTRANSLATEDCAPTION");
						}
					}
				}

				if (untranslatedCaption.length() != 0)
				{
					// Translate the untranslated caption
					translatedString = pTranslation->translate(untranslatedCaption);
				
					if (translatedString.length() != 0)
					{
						// If there was a translation defined for the untranslatedCaption, set the caption
						// of the widget to the translated version
						pWidget->setCaption(MyGUI::UString(translatedString.asWStr()));

						// If we are working with StaticImage, we use the translated caption to set an image for
						// a differnt language, the translated caption gives us the texture to use.
						if (pWidget->getTypeName() == MyGUI::StaticImage::getClassTypeName())
						{
							MyGUI::StaticImage *pSImage = static_cast<MyGUI::StaticImage*>(pWidget);

							pSImage->setImageTexture(translatedString.asUTF8());
						}
					}
					else
					{
						pWidget->setCaption(MyGUI::UString(untranslatedCaption));
					}
				}
			}
		}
	}

	void GUITask::translateCaption(const Ogre::String& widgetName)
	{
		MyGUI::WidgetPtr pWidget;
		DefaultTranslation *pTranslation;

		Poco::ScopedRWLock lock(rwLock, false);
		Poco::ScopedRWLock lockMyGUI(GlobalLocks::rwLockMyGUI, true);

		pTranslation = DefaultTranslation::getSingletonPtr();

		pWidget = mpGUI->findWidgetT(widgetName);

		if (pWidget != NULL)
		{
			Ogre::UTFString translatedString;
			std::string untranslatedCaption = pWidget->getUserString("untranslatedCaption");

			// If we couldn't find 'untranslatedCaption' we try some alternatives, 'untranslatedcaption',
			// 'UntranslatedCaption' and 'UNTRANSLATEDCAPTION'
			if (untranslatedCaption == "")
			{
				untranslatedCaption = pWidget->getUserString("untranslatedcaption");
				if (untranslatedCaption == "")
				{
					untranslatedCaption = pWidget->getUserString("UntranslatedCaption");
					if (untranslatedCaption == "")
					{
						untranslatedCaption = pWidget->getUserString("UNTRANSLATEDCAPTION");
					}
				}
			}

			translatedString = pTranslation->translate(untranslatedCaption);

			pWidget->setCaption(MyGUI::UString(translatedString.asWStr()));

			// If we are working with StaticImage, we use the translated caption to set an image for
			// a differnt language, the translated caption gives us the texture to use.
			if ((translatedString.length() != 0) && (pWidget->getTypeName() == MyGUI::StaticImage::getClassTypeName()))
			{
				MyGUI::StaticImage *pSImage = static_cast<MyGUI::StaticImage*>(pWidget);

				pSImage->setImageTexture(translatedString.asUTF8());
			}
		}
	}

} // Myoushu


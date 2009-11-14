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
 * @file Constants.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

#include "Ogre.h"

#include "Platform.h"

#define MICROSECONDS_IN_SECOND static_cast<Ogre::Real>(1000000)

namespace Myoushu
{
	/** This class defines various static constants used throughout the engine. */

	class MYOUSHU_API Constants
	{
		public:
			/** Name of the author */
			static const Ogre::String AUTHOR;

			/** Major version number */
			static const Ogre::String VER_MAJOR;
			/** Minor version number */
			static const Ogre::String VER_MINOR;

			/** The application's title */
			static const Ogre::String APPLICATION_TITLE;
			
			/** The engine log filename */
			static const std::string LOG_FILENAME;
			/** The path to the config files */
			static const Ogre::String CONFIG_FILES_PATH;
			/** The video configuration file name */
			static const Ogre::String VIDEO_CONFIG_FILENAME;
			/** The input configuration file name */
			static const Ogre::String INPUT_CONFIG_FILENAME;
			/** The resources configuration file name */
			static const Ogre::String RESOURCES_CONFIG_FILENAME;
			/** The helpers script filename */
			static const Ogre::String HELPERS_SCRIPT;
			/** Init script for the GUI system */
			static const Ogre::String GUI_INIT_SCRIPT_FILENAME;

			/** The config files resource group. */
			static const Ogre::String RG_CONFIGFILES;
			/** The GUI resource group. */
			static const Ogre::String RG_GUI;
			/** The textfiles resource group. */
			static const Ogre::String RG_TEXTFILES;
			/** The textures resource group. */
			static const Ogre::String RG_TEXTURES;
			/** The models resource group. */
			static const Ogre::String RG_MODELS;
			/** The shaders resrouce group. */
			static const Ogre::String RG_SHADERS;
			/** The scripts resource group. */
			static const Ogre::String RG_SCRIPTS;
			/** The replays resource group. */
			static const Ogre::String RG_REPLAYS;
			/** The fonts resource group. */
			static const Ogre::String RG_FONTS;
			/** The collision mesh resource group */
			static const Ogre::String RG_COLLISION_MESH;

			/** The main render target identifier (name of the window) */
			static const Ogre::String MAIN_RENDER_TARGET;

			/** Hard coded console action */
			static const std::string INPUT_ACTION_CONSOLE;

			/** The default Camera */
			static const Ogre::String DEFAULT_CAMERA;
			/** The default SceneManager */
			static const Ogre::String DEFAULT_SCENE_MANAGER;

			/** The priority of the TimerTask. */
			static const int TIMER_TASK_PRIORITY;
			/** The execution interval of the TimerTask: the time between executions, in microseconds. */
			static const unsigned long TIMER_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the TimerTask. */
			static const unsigned int TIMER_TASK_ITERATION_LIMIT;
			/** The name of the TimerTask. */
			static const std::string TIMER_TASK_NAME;
			/** The priority of the PhysicsTask. */
			static const int PHYSICS_TASK_PRIORITY;
			/** The execution interval of the PhysicsTask: the time between executions, in microseconds. */
			static const unsigned long PHYSICS_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the PhysicsTask. */
			static const unsigned int PHYSICS_TASK_ITERATION_LIMIT;
			/** The name of the PhysicsTask. */
			static const std::string PHYSICS_TASK_NAME;
			/** The priority of the InputTask. */
			static const int INPUT_TASK_PRIORITY;
			/** The execution interval of the InputTask: the time between executions, in microseconds. */
			static const unsigned long INPUT_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the InputTask. */
			static const unsigned int INPUT_TASK_ITERATION_LIMIT;
			/** The name of the InputTask. */
			static const std::string INPUT_TASK_NAME;
			/** The priority of the InputActionTask. */
			static const int INPUT_ACTION_TASK_PRIORITY;
			/** The execution interval of the InputActionTask: the time between executions, in microseconds. */
			static const unsigned long INPUT_ACTION_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the InputActionTask. */
			static const unsigned int INPUT_ACTION_TASK_ITERATION_LIMIT;
			/** The name of the InputActionTask. */
			static const std::string INPUT_ACTION_TASK_NAME;
			/** The priority of the ControllerTask. */
			static const int CONTROLLER_TASK_PRIORITY;
			/** The execution interval of the ControllerTask: the time between executions, in microseconds. */
			static const unsigned long CONTROLLER_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the ControllerTask. */
			static const unsigned int CONTROLLER_TASK_ITERATION_LIMIT;
			/** The name of the ControllerTask. */
			static const std::string CONTROLLER_TASK_NAME;
			/** The priority of the ScriptTask. */
			static const int SCRIPT_TASK_PRIORITY;
			/** The execution interval of the ScriptTask: the time between executions, in microseconds. */
			static const unsigned long SCRIPT_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the ScriptTask. */
			static const unsigned int SCRIPT_TASK_ITERATION_LIMIT;
			/** The name of the ScriptTask. */
			static const std::string SCRIPT_TASK_NAME;
			/** The priority of the GameTask. */
			static const int GAME_TASK_PRIORITY;
			/** The execution interval of the GameTask: the time between executions, in microseconds. */
			static const unsigned long GAME_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the GameTask. */
			static const unsigned int GAME_TASK_ITERATION_LIMIT;
			/** The name of the GameTask */
			static const std::string GAME_TASK_NAME;
			/** The priority of the GUITask. */
			static const int GUI_TASK_PRIORITY;
			/** The execution interval of the GUITask: the time between executions, in microseconds. */
			static const unsigned long GUI_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the GUITask. */
			static const unsigned int GUI_TASK_ITERATION_LIMIT;
			/** The name of the GUITask. */
			static const std::string GUI_TASK_NAME;
			/** The priority of the AnimationTask. */
			static const int ANIMATION_TASK_PRIORITY;
			/** The execution interval of the AnimationTask: the time between executions, in microseconds. */
			static const unsigned long ANIMATION_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the AnimationTask. */
			static const unsigned int ANIMATION_TASK_ITERATION_LIMIT;
			/** The name of the AnimationTask. */
			static const std::string ANIMATION_TASK_NAME;
			/** The priority of the VideoTask. */
			static const int VIDEO_TASK_PRIORITY;
			/** The execution interval of the VideoTask: the time between executions, in microseconds. */
			static const unsigned long VIDEO_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the VideoTask. */
			static const unsigned int VIDEO_TASK_ITERATION_LIMIT;
			/** The name of the VideoTask. */
			static const std::string VIDEO_TASK_NAME;
			/** The priority of the NetworkListenTask. */
			static const int NETWORK_LISTEN_TASK_PRIORITY;
			/** The execution interval of the NetworkListenTask: the time between executions, in microseconds. */
			static const unsigned long NETWORK_LISTEN_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the NetworkListenTask. */
			static const unsigned int NETWORK_LISTEN_TASK_ITERATION_LIMIT;
			/** The name of the NetworkListenTask. */
			static const std::string NETWORK_LISTEN_TASK_NAME;
			/** The priority of the NetworkTransmitTask. */
			static const int NETWORK_TRANSMIT_TASK_PRIORITY;
			/** The execution interval of the NetworkTransmitTask: the time between executions, in microseconds. */
			static const unsigned long NETWORK_TRANSMIT_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the NetworkTransmitTask. */
			static const unsigned int NETWORK_TRANSMIT_TASK_ITERATION_LIMIT;
			/** The name of the NetworkTransmitTask. */
			static const std::string NETWORK_TRANSMIT_TASK_NAME;
			/** The priority of the AudioTask. */
			static const int AUDIO_TASK_PRIORITY;
			/** The execution interval of the AudioTask: the time between executions, in microseconds. */
			static const unsigned long AUDIO_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the AudioTask. */
			static const unsigned int AUDIO_TASK_ITERATION_LIMIT;
			/** The name of the AudioTask */
			static const std::string AUDIO_TASK_NAME;
			/** The priority of the GameLogTask. */
			static const int GAME_LOG_TASK_PRIORITY;
			/** The execution interval of the GameLogTask: the time between executions, in microseconds. */
			static const unsigned long GAME_LOG_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the GameLogTask. */
			static const unsigned int GAME_LOG_TASK_ITERATION_LIMIT;
			/** The name of the GameLogTask */
			static const std::string GAME_LOG_TASK_NAME;
			/** The priority of the ReplayTask. */
			static const int REPLAY_TASK_PRIORITY;
			/** The execution interval of the ReplayTask: the time between executions, in microseconds. */
			static const unsigned long REPLAY_TASK_EXECUTION_INTERVAL;
			/** The iterationLimit of the ReplayTask. */
			static const unsigned int REPLAY_TASK_ITERATION_LIMIT;
			/** The name of the ReplayTask */
			static const std::string REPLAY_TASK_NAME;

			/** The name of the overlay used to write FPS statistics to screen */
			static const std::string FPS_OVERLAY_NAME;

			/** TimerTaskMessage ObjectPool size */
			static const unsigned int TIMER_TASK_MESSAGE_POOL_SIZE;
			/** InputDeviceMessage ObjectPool size */
			static const unsigned int INPUT_DEVICE_MESSAGE_POOL_SIZE;
			/** InputMessage ObjectPool size */
			static const unsigned int INPUT_MESSAGE_POOL_SIZE;
			/** ControllerTaskMessage ObjectPool size */
			static const unsigned int CONTROLLER_TASK_MESSAGE_POOL_SIZE;
			/** KernelMessage ObjectPool size */
			static const unsigned int KERNEL_MESSAGE_POOL_SIZE;
			/** ScriptMessage ObjectPool size */
			static const unsigned int SCRIPT_MESSAGE_POOL_SIZE;
			/** GUIMessage ObjectPool size */
			static const unsigned int GUI_MESSAGE_POOL_SIZE;
			/** AnimationTaskMessage ObjectPool size */
			static const unsigned int ANIMATION_TASK_MESSAGE_POOL_SIZE;
			/** NetworkMessage ObjectPool size */
			static const unsigned int NETWORK_MESSAGE_POOL_SIZE;
			/** GameLogMessage ObjectPool size */
			static const unsigned int GAME_LOG_MESSAGE_POOL_SIZE;
			/** ReplayMessage ObjectPool size */
			static const unsigned int REPLAY_MESSAGE_POOL_SIZE;
			/** VideoTaskMessage ObjectPool size */
			static const unsigned int VIDEO_TASK_MESSAGE_POOL_SIZE;

			/** The port to listen on for incoming messages over the network. */
			static const unsigned int NETWORK_LISTEN_PORT;
			/** The size, in bytes, of the receive buffer for network messages. */
			static const unsigned int NETWORK_RECEIVE_BUFFER_SIZE;
			/** The size, in bytes, of the transmit buffer for network messages. */
			static const unsigned int NETWORK_TRANSMIT_BUFFER_SIZE;

			/** The size, in bytes, of the buffer used when serialising messages in the Replay Task. */
			static const unsigned int REPLAY_TASK_BUFFER_SIZE;

			/** MyGUI event handlers: eventMouseLostFocus */
			static const Ogre::String MYGUI_EVENT_MOUSE_LOST_FOCUS;
			/** MyGUI event handlers: eventMouseSetFocus */
			static const Ogre::String MYGUI_EVENT_MOUSE_SET_FOCUS;
			/** MyGUI event handlers: eventMouseDrag */
			static const Ogre::String MYGUI_EVENT_MOUSE_DRAG;
			/** MyGUI event handlers: eventMouseWheel */
			static const Ogre::String MYGUI_EVENT_MOUSE_WHEEL;
			/** MyGUI event handlers: eventMouseButtonPressed */
			static const Ogre::String MYGUI_EVENT_MOUSE_BUTTON_PRESSED;
			/** MyGUI event handlers: eventMouseButtonReleased */
			static const Ogre::String MYGUI_EVENT_MOUSE_BUTTON_RELEASED;
			/** MyGUI event handlers: eventMouseButtonClick */
			static const Ogre::String MYGUI_EVENT_MOUSE_BUTTON_CLICK;
			/** MyGUI event handlers: eventMouseButtonDoubleClick */
			static const Ogre::String MYGUI_EVENT_MOUSE_BUTTON_DOUBLE_CLICK;
			/** MyGUI event handlers: eventKeyLostFocus */
			static const Ogre::String MYGUI_EVENT_KEY_LOST_FOCUS;
			/** MyGUI event handlers: eventKeySetFocus */
			static const Ogre::String MYGUI_EVENT_KEY_SET_FOCUS;
			/** MyGUI event handlers: eventKeyButtonPressed */
			static const Ogre::String MYGUI_EVENT_KEY_BUTTON_PRESSED;
			/** MyGUI event handlers: eventKeyButtonReleased */
			static const Ogre::String MYGUI_EVENT_KEY_BUTTON_RELEASED;
			/** MyGUI event handlers: eventRootMouseChangeFocus */
			static const Ogre::String MYGUI_EVENT_ROOT_MOUSE_CHANGE_FOCUS;
			/** MyGUI event handlers: eventRootKeyChangeFocus */
			static const Ogre::String MYGUI_EVENT_ROOT_KEY_CHANGE_FOCUS;
			/** MyGUI event handlers: eventActionInfo */
			static const Ogre::String MYGUI_EVENT_ACTION_INFO;
			/** MyGUI event handlers: _requestGetDragItemInfo */
			static const Ogre::String MYGUI_REQUEST_GET_DRAG_ITEM_INFO;
			/** MyGUI event handlers: eventEditSelectAccept */
			static const Ogre::String MYGUI_EVENT_EDIT_SELECT_ACCEPT;
			/** MyGUI event handlers: eventEditTextChange */
			static const Ogre::String MYGUI_EVENT_EDIT_TEXT_CHANGE;
			/** MyGUI event handlers: eventListSelectAccept */
			static const Ogre::String MYGUI_EVENT_LIST_SELECT_ACCEPT;
			/** MyGUI event handlers: eventListChangePosition */
			static const Ogre::String MYGUI_EVENT_LIST_CHANGE_POSITION;
			/** MyGUI event handlers: eventComboAccept */
			static const Ogre::String MYGUI_EVENT_COMBO_ACCEPT;
			/** MyGUI event handlers: eventComboChangePosition */
			static const Ogre::String MYGUI_EVENT_COMBO_CHANGE_POSITION;
	};
} // Myoushu

#endif // CONSTANTS_H

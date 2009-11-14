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
 * @file Constants.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <string>

#include "Ogre.h"

#include "Constants.h"

namespace Myoushu
{
	const Ogre::String Constants::AUTHOR = "ME Chamberlain";

	const Ogre::String Constants::VER_MAJOR = "0";
	const Ogre::String Constants::VER_MINOR = "1";

	const Ogre::String Constants::APPLICATION_TITLE = "Myoushu -- Test";

	const Ogre::String Constants::LOG_FILENAME = "engine.log";
	const Ogre::String Constants::CONFIG_FILES_PATH = "../../config/";
	const Ogre::String Constants::VIDEO_CONFIG_FILENAME = "video.cfg";
	const Ogre::String Constants::INPUT_CONFIG_FILENAME = "input.cfg";
	const Ogre::String Constants::RESOURCES_CONFIG_FILENAME = "resources.cfg";
	const Ogre::String Constants::HELPERS_SCRIPT = "helpers.lua";
	const Ogre::String Constants::GUI_INIT_SCRIPT_FILENAME = "GUIInit.lua";

	const Ogre::String Constants::RG_CONFIGFILES = "configFiles";
	const Ogre::String Constants::RG_GUI = "GUI";
	const Ogre::String Constants::RG_TEXTFILES = "textFiles";
	const Ogre::String Constants::RG_TEXTURES = "textures";
	const Ogre::String Constants::RG_MODELS = "models";
	const Ogre::String Constants::RG_SHADERS = "shaders";
	const Ogre::String Constants::RG_SCRIPTS = "scripts";
	const Ogre::String Constants::RG_REPLAYS = "replays";
	const Ogre::String Constants::RG_FONTS = "fonts";
	const Ogre::String Constants::RG_COLLISION_MESH = "collision_meshes";

	const Ogre::String Constants::MAIN_RENDER_TARGET = "myoushu_rendertarget";

	const std::string Constants::INPUT_ACTION_CONSOLE = "console";

	const Ogre::String Constants::DEFAULT_CAMERA = "defalutCamera";
	const Ogre::String Constants::DEFAULT_SCENE_MANAGER = "defaultSceneManager";

	const int Constants::TIMER_TASK_PRIORITY = 1;
	const unsigned long Constants::TIMER_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::TIMER_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::TIMER_TASK_NAME = "TimerTask";
	const int Constants::PHYSICS_TASK_PRIORITY = 5;
	const unsigned long Constants::PHYSICS_TASK_EXECUTION_INTERVAL = 1000000 / 100;
	const unsigned int Constants::PHYSICS_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::PHYSICS_TASK_NAME = "PhysicsTask";
	const int Constants::INPUT_TASK_PRIORITY = 10;
	const unsigned long Constants::INPUT_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::INPUT_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::INPUT_TASK_NAME = "InputTask";
	const int Constants::INPUT_ACTION_TASK_PRIORITY = 20;
	const unsigned long Constants::INPUT_ACTION_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::INPUT_ACTION_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::INPUT_ACTION_TASK_NAME = "InputActionTask";
	const int Constants::CONTROLLER_TASK_PRIORITY = 30;
	const unsigned long Constants::CONTROLLER_TASK_EXECUTION_INTERVAL = 1000000 / 100;
	const unsigned int Constants::CONTROLLER_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::CONTROLLER_TASK_NAME = "ControllerTask";
	const int Constants::GAME_TASK_PRIORITY = 45;
	const unsigned long Constants::GAME_TASK_EXECUTION_INTERVAL = 1000000 / 60;
	const unsigned int Constants::GAME_TASK_ITERATION_LIMIT = 4;
	const std::string Constants::GAME_TASK_NAME = "GameTask";
	const int Constants::SCRIPT_TASK_PRIORITY = 50;
	const unsigned int Constants::SCRIPT_TASK_ITERATION_LIMIT = 1;
	const unsigned long Constants::SCRIPT_TASK_EXECUTION_INTERVAL = 0;
	const std::string Constants::SCRIPT_TASK_NAME = "ScriptTask";
	const int Constants::GUI_TASK_PRIORITY = 90;
	const unsigned long Constants::GUI_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::GUI_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::GUI_TASK_NAME = "GUITask";
	const int Constants::ANIMATION_TASK_PRIORITY = 95;
	const unsigned long Constants::ANIMATION_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::ANIMATION_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::ANIMATION_TASK_NAME = "AnimationTask";
	const int Constants::VIDEO_TASK_PRIORITY = 100;
	const unsigned long Constants::VIDEO_TASK_EXECUTION_INTERVAL = 1000000 / 100;
	const unsigned int Constants::VIDEO_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::VIDEO_TASK_NAME = "VideoTask";
	const int Constants::NETWORK_LISTEN_TASK_PRIORITY = 2;
	const unsigned long Constants::NETWORK_LISTEN_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::NETWORK_LISTEN_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::NETWORK_LISTEN_TASK_NAME = "NetworkListenTask";
	const int Constants::NETWORK_TRANSMIT_TASK_PRIORITY = 99;
	const unsigned long Constants::NETWORK_TRANSMIT_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::NETWORK_TRANSMIT_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::NETWORK_TRANSMIT_TASK_NAME = "NetworkTransmitTask";
	const int Constants::AUDIO_TASK_PRIORITY = 80;
	const unsigned long Constants::AUDIO_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::AUDIO_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::AUDIO_TASK_NAME = "AudioTask";
	const int Constants::GAME_LOG_TASK_PRIORITY = 85;
	const unsigned long Constants::GAME_LOG_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::GAME_LOG_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::GAME_LOG_TASK_NAME = "GameLogTask";
	const int Constants::REPLAY_TASK_PRIORITY = 3;
	const unsigned long Constants::REPLAY_TASK_EXECUTION_INTERVAL = 0;
	const unsigned int Constants::REPLAY_TASK_ITERATION_LIMIT = 1;
	const std::string Constants::REPLAY_TASK_NAME = "ReplayTask";

	const std::string Constants::FPS_OVERLAY_NAME = "FPSOverlay";

	const unsigned int Constants::TIMER_TASK_MESSAGE_POOL_SIZE = 2;
	const unsigned int Constants::INPUT_DEVICE_MESSAGE_POOL_SIZE = 30;
	const unsigned int Constants::INPUT_MESSAGE_POOL_SIZE = 30;
	const unsigned int Constants::CONTROLLER_TASK_MESSAGE_POOL_SIZE = 30;
	const unsigned int Constants::KERNEL_MESSAGE_POOL_SIZE = 10;
	const unsigned int Constants::SCRIPT_MESSAGE_POOL_SIZE = 20;
	const unsigned int Constants::GUI_MESSAGE_POOL_SIZE = 10;
	const unsigned int Constants::ANIMATION_TASK_MESSAGE_POOL_SIZE = 10;
	const unsigned int Constants::NETWORK_MESSAGE_POOL_SIZE = 30;
	const unsigned int Constants::GAME_LOG_MESSAGE_POOL_SIZE = 30;
	const unsigned int Constants::REPLAY_MESSAGE_POOL_SIZE = 5;
	const unsigned int Constants::VIDEO_TASK_MESSAGE_POOL_SIZE = 5;

	const unsigned int Constants::NETWORK_LISTEN_PORT = 25000;
	const unsigned int Constants::NETWORK_RECEIVE_BUFFER_SIZE = 10240;
	const unsigned int Constants::NETWORK_TRANSMIT_BUFFER_SIZE = 10240;

	const unsigned int Constants::REPLAY_TASK_BUFFER_SIZE = 10240;

	const Ogre::String Constants::MYGUI_EVENT_MOUSE_LOST_FOCUS = "eventMouseLostFocus";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_SET_FOCUS = "eventMouseSetFocus";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_DRAG = "eventMouseDrag";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_WHEEL = "eventMouseWheel";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_BUTTON_PRESSED = "eventMouseButtonPressed";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_BUTTON_RELEASED = "eventMouseButtonReleased";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_BUTTON_CLICK = "eventMouseButtonClick";
	const Ogre::String Constants::MYGUI_EVENT_MOUSE_BUTTON_DOUBLE_CLICK = "eventMouseButtonDoubleClick";
	const Ogre::String Constants::MYGUI_EVENT_KEY_LOST_FOCUS = "eventKeyLostFocus";
	const Ogre::String Constants::MYGUI_EVENT_KEY_SET_FOCUS = "eventKeySetFocus";
	const Ogre::String Constants::MYGUI_EVENT_KEY_BUTTON_PRESSED = "eventKeyButtonPressed";
	const Ogre::String Constants::MYGUI_EVENT_KEY_BUTTON_RELEASED = "eventKeyButtonReleased";
	const Ogre::String Constants::MYGUI_EVENT_ROOT_MOUSE_CHANGE_FOCUS = "eventRootMouseChangeFocus";
	const Ogre::String Constants::MYGUI_EVENT_ROOT_KEY_CHANGE_FOCUS = "eventRootKeyChangeFocus";
	const Ogre::String Constants::MYGUI_EVENT_ACTION_INFO = "eventActionInfo";
	const Ogre::String Constants::MYGUI_REQUEST_GET_DRAG_ITEM_INFO = "_requestGetDragItemInfo";
	const Ogre::String Constants::MYGUI_EVENT_EDIT_SELECT_ACCEPT = "eventEditSelectAccept";
	const Ogre::String Constants::MYGUI_EVENT_EDIT_TEXT_CHANGE = "eventEditTextChange";
	const Ogre::String Constants::MYGUI_EVENT_LIST_SELECT_ACCEPT = "eventListSelectAccept";
	const Ogre::String Constants::MYGUI_EVENT_LIST_CHANGE_POSITION = "eventListChangePosition";
	const Ogre::String Constants::MYGUI_EVENT_COMBO_ACCEPT = "eventComboxAccept";
	const Ogre::String Constants::MYGUI_EVENT_COMBO_CHANGE_POSITION = "eventComboChangePosition";
}

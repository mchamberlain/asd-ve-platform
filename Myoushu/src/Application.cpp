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
 * @file Application.cpp
 * @author ME Chamberlain
 * @date April 2008
 */

#include <iostream>

// Fix windows or MSVC issues with std::max and std::min
#define NOMINMAX

#include "OgreDynLibManager.h"
#include "OgreDynLib.h"

#include "lua.hpp"
//#include "tolua++.h"

#include "Application.h"
#include "Constants.h"
#include "MyoushuLua.h"
#include "NamedObjectInstanceCreator.h"
#include "GameObjectAction.h"
#include "GameCharacterObjectAction.h"
#include "GameCharacterObjectController.h"
#include "NetworkListenTaskTCP.h"
#include "NetworkTransmitTaskTCP.h"

//template<>
//Myoushu::Application* Ogre::Singleton<Myoushu::Application>::ms_Singleton = NULL;

namespace Myoushu
{
	CLASS_NAME(Application, "Myoushu::Application");

	/****************************************************************************/

	Application::Application() :
	pRandom(NULL),
	root(NULL),
	cfg(NULL),
	log(NULL),
	txtFileMgr(NULL),
	defaultTranslation(NULL),
	namedObjectInstanceCreatorManager(NULL),
	notificationManager(NULL),
	kernelManager(NULL),
	scriptManager(NULL),
	gameObjectFactory(NULL),
	sceneFactory(NULL),
	controllerFactory(NULL),
	replayFactory(NULL),
	inputActionManager(NULL),
	animationManager(NULL),
	controllerTaskManager(NULL),
	networkManager(NULL),
	collisionManager(NULL),
	videoTaskManager(NULL),
	sqliteGameLogManager(NULL),
	replayTaskManager(NULL),
	contentImporterManager(NULL),
	soundPluginManager(NULL),
	functorManager(NULL),
	kernel(NULL),
	videoTask(NULL),
	timerTask(NULL),
	inputTask(NULL),
	inputActionTask(NULL),
	scriptTask(NULL),
	guiTask(NULL),
	physicsTask(NULL),
	animationTask(NULL),
	controllerTask(NULL),
	networkListenTask(NULL),
	networkTransmitTask(NULL),
	sqliteGameLogTask(NULL),
	timerTaskMessagePool(NULL),
	inputDeviceMessagePool(NULL),
	inputMessagePool(NULL),
	kernelMessagePool(NULL),
	scriptMessagePool(NULL),
	guiMessagePool(NULL),
	animationTaskMessagePool(NULL),
	controllerTaskMessagePool(NULL),
	gameLogMessagePool(NULL),
	replayMessagePool(NULL),
	videoTaskMessagePool(NULL),
	mConfigFilePath(Constants::CONFIG_FILES_PATH),
	mInitialised(false),
	mArgc(0),
	mArgv(NULL)
	{
	}

	/****************************************************************************/

	Application::~Application()
	{
	}

	/****************************************************************************/

	void Application::main(int argc, char **argv)
	{
		Ogre::LogManager* logMgr;
		Ogre::Log *ogreLog;

		// Check whether a command line argument was specified, and use it to set the configuration
		// file path
		if (argc == 2)
		{
			setConfigFilePath(argv[1]);
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		// Create the engine logger.
		log = new EngineLog();
	 	LOG(EngineLog::LM_INFO_ENGINE, "Engine Log initialized.");

		//Redirect Ogre output to a log file instead of the console.
	 	LOG(EngineLog::LM_INFO_ENGINE, "Creating Ogre's log manager.");
		logMgr = new Ogre::LogManager();
		ogreLog = Ogre::LogManager::getSingleton().createLog("ogre.log", true, false, false);

		LOG(EngineLog::LM_INFO_ENGINE, "Creating Ogre's root singleton.");
		GlobalLocks::rwLockOgreRoot.writeLock();
		root = new Ogre::Root("", "", "");
		GlobalLocks::rwLockOgreRoot.unlock();

		mArgc = argc;
		mArgv = argv;
	}

	/****************************************************************************/

	void Application::init() throw (Exception)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		log = EngineLog::getSingletonPtr();

		LOG(EngineLog::LM_INFO_ENGINE, "Starting Engine.");

		LOG(EngineLog::LM_INFO_ENGINE, "Creating random number generator...");
		pRandom = new Random(time(NULL));

		// Create the configuration singleton
		cfg = new Config();
	 	LOG(EngineLog::LM_INFO_ENGINE, "Config system initialized.");

		try
		{
			// Setup resource manager
			LOG(EngineLog::LM_INFO_ENGINE, "[Application] Setting up resource manager.");
			setupResourceManager();
			LOG(EngineLog::LM_INFO_ENGINE, "Resource manager initialised.");
		}
		catch (Ogre::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Error setting up resource manager: " << e.what());
		}
		// Load config file resources
		try
		{
			initialiseResourceGroups(Constants::RG_CONFIGFILES);
			initialiseResourceGroups(Constants::RG_FONTS);
		}
		catch (Ogre::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Error initialising resource groups: " << e.what());
		}

		txtFileMgr = TextFileManager::getSingletonPtr();

		// Load the configuraiton files.
	 	LOG(EngineLog::LM_INFO_ENGINE, "Loading configuration files.");
		try
		{
			cfg->loadConfig(Constants::VIDEO_CONFIG_FILENAME);
			cfg->loadConfig(Constants::INPUT_CONFIG_FILENAME);
		}
		catch (Exception& e)
		{
			// If there was a problem loading the video config, we revert to hardcoded defaults.
			LOG(EngineLog::LM_ERROR, "Loading config file: " << e.what());

			cfg->setInt(Config::VID_WIDTH, 800);
			cfg->setInt(Config::VID_HEIGHT, 600);
			cfg->setBool(Config::VID_FULLSCREEN, false);
			cfg->setBool(Config::VID_VSYNC, false);
		}

		try
		{
			// Create the DefaultTranslation singleton
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the DefaultTranslation");
			defaultTranslation = new DefaultTranslation();

			// Create the NamedObjectInstanceCreatorManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the NamedObjectInstanceCreatorManager");
			namedObjectInstanceCreatorManager = NamedObjectInstanceCreatorManager::getSingletonPtr();
			if (namedObjectInstanceCreatorManager == NULL)
			{
				namedObjectInstanceCreatorManager = new NamedObjectInstanceCreatorManager();
			}

			// Create the NotificationManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the NotificationManager");
			notificationManager = new NotificationManager();

			// Create the KernelManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the KernelManager");
			kernelManager = new KernelManager();

			// Create the InputActionManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the InputActionManager");
			inputActionManager = new InputActionManager();

			// Create the ScriptManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ScriptManager");
			scriptManager = new ScriptManager();

			// Create the GameObjectFactory
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the GameObjectFactory");
			gameObjectFactory = new GameObjectFactory();

			// Create the SceneFactory
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the SceneFactory");
			sceneFactory = new SceneFactory();

			// Create the ControllerFactory
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ControllerFactory");
			controllerFactory = new ControllerFactory();

			// Create the ReplayFactory
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ReplayFactory");
			replayFactory = new ReplayFactory();

			// Create the AnimationManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the AnimationManager");
			animationManager = new AnimationManager();

			// Create the ControllerTaskManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ControllerTaskManager");
			controllerTaskManager = new ControllerTaskManager();

			// Create the NetworkManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the NetworkManager");
			networkManager = new NetworkManager();

			// Create the CollisionManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the CollisionManager");
			collisionManager = new CollisionManager();

			// Create the VideoTaskManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the VideoTaskManager");
			videoTaskManager = new VideoTaskManager();

			// Create the SQLiteGameLogManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the SQLiteGameLogManager");
			sqliteGameLogManager = new SQLiteGameLogManager();

			// Create the ReplayTaskManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ReplayTaskManager");
			replayTaskManager = new ReplayTaskManager();

			// Create the ContentImporterManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ContentImporterManager");
			contentImporterManager = new ContentImporterManager();

			// Create the SoundPluginManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the SoundPluginManager");
			soundPluginManager = new SoundPluginManager();

			// Create the FunctorManager
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the FunctorManager");
			functorManager = new FunctorManager();

			// Create the ObjectPools
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the ObjectPool singletons");
			initObjectPools();

			// Create the ObjectPools
			LOG(EngineLog::LM_INFO_ENGINE, "Registering instance creator functions.");
			registerInstanceCreators();

			// Create the PhysicsTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating PhysicsTask");
			physicsTask = new PhysicsTask(Constants::PHYSICS_TASK_PRIORITY, Constants::PHYSICS_TASK_NAME
				, Constants::PHYSICS_TASK_EXECUTION_INTERVAL, Constants::PHYSICS_TASK_ITERATION_LIMIT);
			physicsTask->init();

			// Set the NxOgre::World class in the SceneFactory
			sceneFactory->setWorld(physicsTask->getWorld());

			// Create the VideoTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating VideoTask");
			videoTask = new VideoTask(Constants::VIDEO_TASK_PRIORITY, Constants::VIDEO_TASK_NAME
				, Constants::VIDEO_TASK_EXECUTION_INTERVAL, Constants::VIDEO_TASK_ITERATION_LIMIT);
			videoTask->init();

			LOG(EngineLog::LM_INFO_ENGINE, "Loading plugins");
			loadPlugins();

			LOG(EngineLog::LM_INFO_ENGINE, "Initializing resources.");
			// Initialises resources
			initialiseResourceGroups();

			// Create the TimerTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating TimerTask");
			timerTask = new TimerTask(Constants::TIMER_TASK_PRIORITY, Constants::TIMER_TASK_NAME);

			// Create the InputTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating InputTask");
			inputTask = new InputTask(Constants::INPUT_TASK_PRIORITY, Constants::INPUT_TASK_NAME
				, Constants::INPUT_TASK_EXECUTION_INTERVAL, Constants::INPUT_TASK_ITERATION_LIMIT);

			// Create the InputActionTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating InputActionTask");
			inputActionTask = new InputActionTask(Constants::INPUT_ACTION_TASK_PRIORITY, Constants::INPUT_ACTION_TASK_NAME
				, Constants::INPUT_ACTION_TASK_EXECUTION_INTERVAL, Constants::INPUT_ACTION_TASK_ITERATION_LIMIT);

			// Create the ScriptTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating ScriptTask");
			scriptTask = new ScriptTask(Constants::SCRIPT_TASK_PRIORITY, Constants::SCRIPT_TASK_NAME
				, Constants::SCRIPT_TASK_EXECUTION_INTERVAL, Constants::SCRIPT_TASK_ITERATION_LIMIT);

			// Create the GUITask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating GUITask");
			guiTask = new GUITask(Constants::GUI_TASK_PRIORITY, Constants::GUI_TASK_NAME
				, Constants::GUI_TASK_EXECUTION_INTERVAL, Constants::GUI_TASK_ITERATION_LIMIT);

			// Create the AnimationTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating AnimationTask");
			animationTask = new AnimationTask(Constants::ANIMATION_TASK_PRIORITY, Constants::ANIMATION_TASK_NAME
				, Constants::ANIMATION_TASK_EXECUTION_INTERVAL, Constants::ANIMATION_TASK_ITERATION_LIMIT);

			// Create the ControllerTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating ControllerTask");
			controllerTask = new ControllerTask(Constants::CONTROLLER_TASK_PRIORITY, Constants::CONTROLLER_TASK_NAME
				, Constants::CONTROLLER_TASK_EXECUTION_INTERVAL, Constants::CONTROLLER_TASK_ITERATION_LIMIT);

			// Create the NetworkListenTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating NetworkListenTask");
			networkListenTask = new NetworkListenTask(Constants::NETWORK_LISTEN_TASK_NAME, Constants::NETWORK_LISTEN_TASK_PRIORITY
				, Constants::NETWORK_LISTEN_TASK_EXECUTION_INTERVAL, Constants::NETWORK_LISTEN_TASK_ITERATION_LIMIT);

			// Create the NetworkTransmitTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating NetworkTransmitTask");
			networkTransmitTask = new NetworkTransmitTask(Constants::NETWORK_TRANSMIT_TASK_PRIORITY, Constants::NETWORK_TRANSMIT_TASK_NAME
				, Constants::NETWORK_TRANSMIT_TASK_EXECUTION_INTERVAL, Constants::NETWORK_TRANSMIT_TASK_ITERATION_LIMIT);

			// Create the SQLiteGameLogTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating SQLiteGameLogTask");
			sqliteGameLogTask = new SQLiteGameLogTask(Constants::GAME_LOG_TASK_PRIORITY, Constants::GAME_LOG_TASK_NAME
				, Constants::GAME_LOG_TASK_EXECUTION_INTERVAL, Constants::GAME_LOG_TASK_ITERATION_LIMIT);

			// Create the ReplayTask
			LOG(EngineLog::LM_INFO_ENGINE, "Creating ReplayTask");
			replayTask = new ReplayTask(Constants::REPLAY_TASK_PRIORITY, Constants::REPLAY_TASK_NAME
				, Constants::REPLAY_TASK_EXECUTION_INTERVAL, Constants::REPLAY_TASK_ITERATION_LIMIT);

			// Create the Kernel
			LOG(EngineLog::LM_INFO_ENGINE, "Creating the Kernel");
			kernel = new Kernel();
			kernel->addTask(timerTask);
			kernel->addTask(networkListenTask);
			kernel->addTask(inputTask);
			kernel->addTask(inputActionTask);
			kernel->addTask(controllerTask);
			kernel->addTask(scriptTask);
			kernel->addTask(guiTask);
			kernel->addTask(animationTask);
			kernel->addTask(networkTransmitTask);
			kernel->addTask(sqliteGameLogTask);
			kernel->addTask(replayTask);

			LOG(EngineLog::LM_INFO_ENGINE, "Initializing plugins.");
			initialisePlugins();

			LOG(EngineLog::LM_INFO_ENGINE, "Initializing all Tasks.");
			kernel->initAllTasks();

			kernel->addTask(physicsTask);
			kernel->addTask(videoTask);

			//Create lua bindings
			LOG(EngineLog::LM_INFO_ENGINE, "Exposing objects to lua.");
			setupScriptBindings();

			// The engine is initialised
			setInitialised(true);

		}
		catch (Ogre::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Application::init caught exception: " << e.what());
			throw e;
		}
		catch (Poco::Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Application::init caught exception: " << e.displayText());
			throw e;
		}
		catch (Exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Application::init caught exception: " << e.what());
			throw e;
		}
		catch (std::exception& e)
		{
			LOG(EngineLog::LM_ERROR, "Application::init caught exception: " << e.what());
			throw e;
		}
		catch (...)
		{
			LOG(EngineLog::LM_ERROR, "Application::init caught unknown exception.");
			throw;
		}

	}

	/****************************************************************************/

	void Application::initObjectPools() throw (Exception)
	{
		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the TimerTaskMessagePool...");
		timerTaskMessagePool = new ObjectPool<TimerTaskMessage>(Constants::TIMER_TASK_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the InputDeviceMessagePool...");
		inputDeviceMessagePool = new ObjectPool<InputDeviceMessage>(Constants::INPUT_DEVICE_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the InputMessagePool...");
		inputMessagePool = new ObjectPool<InputMessage>(Constants::INPUT_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the KernelMessagePool...");
		kernelMessagePool = new ObjectPool<KernelMessage>(Constants::KERNEL_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the ScriptMessagePool...");
		scriptMessagePool = new ObjectPool<ScriptMessage>(Constants::SCRIPT_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the GUIMessagePool...");
		guiMessagePool = new ObjectPool<GUIMessage>(Constants::GUI_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the AnimationTaskMessagePool...");
		animationTaskMessagePool = new ObjectPool<AnimationTaskMessage>(Constants::ANIMATION_TASK_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the ControllerTaskMessagePool...");
		controllerTaskMessagePool = new ObjectPool<ControllerTaskMessage>(Constants::CONTROLLER_TASK_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the NetworkMessagePool...");
		networkMessagePool = new ObjectPool<NetworkMessage>(Constants::NETWORK_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the GameLogMessagePool...");
		gameLogMessagePool = new ObjectPool<GameLogMessage>(Constants::GAME_LOG_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the ReplayMessagePool...");
		replayMessagePool = new ObjectPool<ReplayMessage>(Constants::REPLAY_MESSAGE_POOL_SIZE);

		LOG(EngineLog::LM_INFO_ENGINE, "\t Creating the VideoTaskMessagePool...");
		videoTaskMessagePool = new ObjectPool<VideoTaskMessage>(Constants::VIDEO_TASK_MESSAGE_POOL_SIZE);
	}

	/****************************************************************************/

	void Application::destroyObjectPools() throw (Exception)
	{
		if (timerTaskMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the TimerTaskMessagePool.");
			delete timerTaskMessagePool;
			timerTaskMessagePool = NULL;
		}

		if (inputMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the InputMessagePool.");
			delete inputMessagePool;
			inputMessagePool = NULL;
		}

		if (inputDeviceMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the InputDeviceMessagePool.");
			delete inputDeviceMessagePool;
			inputDeviceMessagePool = NULL;
		}

		if (kernelMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the KernelMessagePool.");
			delete kernelMessagePool;
			kernelMessagePool = NULL;
		}

		if (scriptMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the ScriptMessagePool.");
			delete scriptMessagePool;
			scriptMessagePool = NULL;
		}

		if (guiMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the GUIMessagePool.");
			delete guiMessagePool;
			guiMessagePool = NULL;
		}

		if (animationTaskMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the AnimationTaskMessagePool.");
			delete animationTaskMessagePool;
			animationTaskMessagePool = NULL;
		}

		if (controllerTaskMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the ControllerTaskMessagePool.");
			delete controllerTaskMessagePool;
			controllerTaskMessagePool = NULL;
		}

		if (networkMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the NetworkMessagePool.");
			delete networkMessagePool;
			networkMessagePool = NULL;
		}

		if (gameLogMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the GameLogMessagePool.");
			delete gameLogMessagePool;
			gameLogMessagePool = NULL;
		}

		if (replayMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the ReplayMessagePool.");
			delete replayMessagePool;
			replayMessagePool = NULL;
		}

		if (videoTaskMessagePool != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "\t Destroying the VideoTaskMessagePool.");
			delete videoTaskMessagePool;
			videoTaskMessagePool = NULL;
		}
	}

	/****************************************************************************/

	void Application::registerInstanceCreators()
	{
		REGISTER_INSTANCE_CREATOR(GameObjectAction);
		REGISTER_INSTANCE_CREATOR(GameCharacterObjectAction);
		REGISTER_INSTANCE_CREATOR(GameCharacterObjectController);
	}

	/****************************************************************************/

	void Application::run() throw (Exception)
	{
		//try
		//{

			LOG(EngineLog::LM_INFO_ENGINE, "Starting concurrent tasks.");
			kernel->startConcurrentTasks();

			LOG(EngineLog::LM_INFO_ENGINE, "Application is now executing.");
			kernel->execute();

			LOG(EngineLog::LM_INFO_ENGINE, "Kernel has finished execution!");
		//}
		//catch (Ogre::Exception& e)
		//{
		//	LOG(EngineLog::LM_ERROR, "Application::run caught exception: " << e.what());
		//}
		//catch (Poco::Exception& e)
		//{
		//	LOG(EngineLog::LM_ERROR, "Application::run caught exception: " << e.displayText());
		//}
		//catch (Exception& e)
		//{
		//	LOG(EngineLog::LM_ERROR, "Application::run caught exception: " << e.what());
		//}
		//catch (std::exception& e)
		//{
		//	LOG(EngineLog::LM_ERROR, "Application::run caught exception: " << e.what());
		//}
		//catch (...)
		//{
		//	LOG(EngineLog::LM_ERROR, "Application::run caught unknown exception.");
		//}

		//clean up singletons

		//LOG(EngineLog::LM_INFO_ENGINE, "Deleting Kernel.");
		//if (kernel)
		//{
		//	delete kernel;
		//}

		LOG(EngineLog::LM_INFO_ENGINE, "Shutting down plugins.");
		shutdownPlugins();

		Poco::ScopedRWLock lock(mRWLock, true);

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the FunctorManager.");
		if (functorManager)
		{
			delete functorManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the SoundPluginManager.");
		if (soundPluginManager)
		{
			delete soundPluginManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ContentImporterManager.");
		if (contentImporterManager)
		{
			delete contentImporterManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ReplayTaskManager.");
		if (replayTaskManager)
		{
			delete replayTaskManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the SQLiteGameLogManager.");
		if (sqliteGameLogManager)
		{
			delete sqliteGameLogManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the VideoTaskManager.");
		if (videoTaskManager)
		{
			delete videoTaskManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the NetworkManager.");
		if (networkManager)
		{
			delete networkManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the CollisionManager.");
		if (collisionManager)
		{
			delete collisionManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ControllerTaskManager.");
		if (controllerTaskManager)
		{
			delete controllerTaskManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the AnimationManager.");
		if (animationManager)
		{
			delete animationManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ReplayFactory.");
		if (replayFactory)
		{
			delete replayFactory;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ControllerFactory.");
		if (controllerFactory)
		{
			delete controllerFactory;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the GameObjectFactory.");
		if (gameObjectFactory)
		{
			delete gameObjectFactory;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the SceneFactory.");
		if (sceneFactory)
		{
			delete sceneFactory;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting Kernel.");
		if (kernel)
		{
			delete kernel;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting textfile resource manager.");
		if (txtFileMgr)
		{
			delete txtFileMgr;
		}

	 	LOG(EngineLog::LM_INFO_ENGINE, "Deleting Config.");
	 	if (cfg)
		{
	 		delete cfg;
	 	}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the NotificationManager.");
		if (notificationManager)
		{
			delete notificationManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the KernelManager.");
		if (kernelManager)
		{
			delete kernelManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the InputActionManager.");
		if (inputActionManager)
		{
			delete inputActionManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ScriptManager.");
		if (scriptManager)
		{
			delete scriptManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the NamedObjectInstanceCreatorManager.");
		if (namedObjectInstanceCreatorManager)
		{
			delete namedObjectInstanceCreatorManager;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the DefaultTranslation Singleton.");
		if (defaultTranslation)
		{
			delete defaultTranslation;
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Deleting the ObjectPool singletons...");
		destroyObjectPools();

		if (pRandom)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "Destroying random number generator...");
			delete pRandom;
			pRandom = NULL;
		}

		// The engine is no longer initialised
		setInitialised(false);

	 	LOG(EngineLog::LM_INFO_ENGINE, "Unloading plugins.");
		unloadPlugins();

		GlobalLocks::rwLockOgreRoot.writeLock();
		LOG(EngineLog::LM_INFO_ENGINE, "Deleting Ogre Root.");
		root = Ogre::Root::getSingletonPtr();
		if (root)
		{
			delete root;
		}
		GlobalLocks::rwLockOgreRoot.unlock();

		LOG(EngineLog::LM_INFO_ENGINE, "Stopping Engine Log and finally the entire engine.");
		if (log)
		{
			delete log;
		}
	}

	/****************************************************************************/

	void Application::loadPlugin(const std::string& name) throw (Exception)
	{
		Ogre::DynLib *pDynLib;

		// Get the Ogre::DynLibManager instance and try to load the plugin library
		try
		{
			pDynLib = Ogre::DynLibManager::getSingleton().load(name);
		}
		catch (Ogre::Exception& e)
		{
			throw Exception(Exception::E_OGRE_EXCEPTION, "Application::loadPlugin(): " + std::string(e.what()));
		}

		if (pDynLib == NULL)
		{
			throw Exception(Exception::E_FILE_NOT_FOUND, "Application::loadPlugin(): couldn't find the file for plugin: " + name);
		}

		{
			Poco::ScopedRWLock lock(mRWLockPluginLibs, true);

			// Add it to the list of plugin libraries
			mPluginLibs.insert(PluginLibsMap::value_type(name, pDynLib));
		}

		// Find the dllStartPlugin function
		DLLPluginFunctionPtr pStartFunc = static_cast<DLLPluginFunctionPtr>(pDynLib->getSymbol("dllStartPlugin"));

		if (pStartFunc == NULL)
		{
			throw Exception(Exception::E_GENERAL_EXCEPTION, "Application::loadPlugin(): couldn't find the dllStartPlugin() function in plugin: " + name);
		}

		// Call it, pStartFunc should call installPlugin
		pStartFunc();
	}

	/****************************************************************************/

	void Application::unloadPlugin(const std::string& name) throw (Exception)
	{
		PluginLibsMap::iterator iter;
		Ogre::DynLib *pDynLib;

		{
			Poco::ScopedRWLock lock(mRWLockPluginLibs, false);

			// Find the Ogre::DynLib instance
			iter = mPluginLibs.find(name);
			if (iter == mPluginLibs.end())
			{
				// Plugin library not found, it has not been loaded
				throw Exception(Exception::E_NO_SUCH_ELEMENT, "Application::unloadPlugin(): Couldn't find the \"" + name + "\"plugin in the list of loaded plugins.");
			}

			pDynLib = iter->second;
		}

		// Find the dllStopPlugin() function
		DLLPluginFunctionPtr pStopFunc = static_cast<DLLPluginFunctionPtr>(pDynLib->getSymbol("dllStopPlugin"));
		
		if (pStopFunc != NULL)
		{
			// This function should call uninstallPlugin()
			pStopFunc();
		}
		else
		{
			LOG(EngineLog::LM_WARNING, "Application::unloadPlugin(): couldn't find the dllStopPlugin() function in plugin \"" + name + "\", ignoring...");				
		}

		Poco::ScopedRWLock lock(mRWLockPluginLibs, true);

		// Remove from the mPluginLibs map
		mPluginLibs.erase(iter);
		// Ogre::DynLib instance will be destroyed by Ogre::DynLibManager
		Ogre::DynLibManager::getSingleton().unload(pDynLib);
	}

	/****************************************************************************/

	void Application::installPlugin(Plugin *pPlugin) throw (Exception)
	{
		// Check that pPlugin is not NULL
		if (pPlugin == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Application::installPlugin(): pPlugin is NULL.");
		}

		// Add the Plugin instance to the mPlugins map
		{
			Poco::ScopedRWLock lock(mRWLockPlugins, true);
			mPlugins.insert(PluginsMap::value_type(pPlugin->getName(), pPlugin));
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Installing plugin: " << pPlugin->getName());
		// Call the install() function of the plugin
		pPlugin->install();

		// If the engine has already been initialised, call the initialise function of the plugin
		Poco::ScopedRWLock lock(mRWLockInitialised, false);

		if (getInitialised())
		{
			pPlugin->initialise();
		}
		LOG(EngineLog::LM_INFO_ENGINE, "Installed plugin: " << pPlugin->getName() << " successfully.");
	}

	/****************************************************************************/

	void Application::uninstallPlugin(Plugin *pPlugin) throw (Exception)
	{
		PluginsMap::iterator iter;

		// Check that pPlugin is not NULL
		if (pPlugin == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Application::installPlugin(): pPlugin is NULL.");
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Uninstalling plugin: " << pPlugin->getName());

		Poco::ScopedRWLock lock(mRWLockPlugins, true);

		iter = mPlugins.find(pPlugin->getName());
		if (iter != mPlugins.end())
		{
			// If the engine is initialised, call shutdown() on the Plugin instance
			if (getInitialised())
			{
				pPlugin->shutdown();
			}

			// Call the uninstall() function of the Plugin instance
			pPlugin->uninstall();

			// Remove the plugin from the mPlugins map
			mPlugins.erase(iter);
		}

		LOG(EngineLog::LM_INFO_ENGINE, "Uninstalled plugin: " << pPlugin->getName() << " successfully.");
	}

	/****************************************************************************/
	
	void Application::unloadPlugins()
	{
		PluginLibsMap::reverse_iterator iter;

		Poco::ScopedRWLock lock(mRWLockPluginLibs, false);
		for (iter = mPluginLibs.rbegin(); iter != mPluginLibs.rend(); ++iter)
		{
			// Get the Ogre::DynLib instance
			Ogre::DynLib *pDynLib = iter->second;

			// Find the dllStopPlugin() function
			DLLPluginFunctionPtr pStopFunc = static_cast<DLLPluginFunctionPtr>(pDynLib->getSymbol("dllStopPlugin"));
			if (pStopFunc != NULL)
			{
				pStopFunc();
			}
			else
			{
				// Log a warning if we could not find the dllStopPlugin method
				LOG(EngineLog::LM_WARNING, "Application::unloadPlugins(): couldn't find dllStopPlugin() function in plugin " << iter->first);
			}
			// Unload the plugin library from the Ogre::DynLibManager
			Ogre::DynLibManager::getSingleton().unload(pDynLib);
		}

		// Clear the mPluginLibs map
		mPluginLibs.clear();
	}

	/****************************************************************************/

	void Application::initialisePlugins()
	{
		PluginsMap::iterator iter;

		Poco::ScopedRWLock lock(mRWLockPlugins, false);
		for (iter = mPlugins.begin(); iter != mPlugins.end(); ++iter)
		{
			Plugin *pPlugin = iter->second;

			pPlugin->initialise();
		}
	}

	/****************************************************************************/

	void Application::shutdownPlugins()
	{
		PluginsMap::reverse_iterator iter;

		Poco::ScopedRWLock lock(mRWLockPlugins, false);
		for (iter = mPlugins.rbegin(); iter != mPlugins.rend(); ++iter)
		{
			Plugin *pPlugin = iter->second;

			pPlugin->shutdown();
		}
	}

	/****************************************************************************/

	void Application::setupScriptBindings()
	{
		lua_State* luaState;

		// Get the default LuaParser and then get the lua_State pointer
		LuaParser& luaParser = ScriptManager::getSingleton().getDefaultLuaParser();
		luaState = luaParser.getLuaState();

		// Acquire a write lock on the lua_State before we start exposing functions via tolua++
		luaParser.getLuaStateLock(true);

		// Expose the engine to Lua
		//tolua_MyoushuLua_open(luaState);
		SWIG_init(luaState);

		// Load the helpers script into the lua state
		ScriptManager::getSingleton().executeScriptFile(Constants::HELPERS_SCRIPT);

		luaParser.releaseLuaStateLock();
	}

	/****************************************************************************/

	void Application::loadPlugins()
	{
		#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN64)
			#ifdef MYOUSHU_DEBUG
				Ogre::Root::getSingletonPtr()->loadPlugin("ogreoctree_d");
				Ogre::Root::getSingletonPtr()->loadPlugin("ogreparticlefx_d");
			#else
				Ogre::Root::getSingletonPtr()->loadPlugin("ogreoctree");
				Ogre::Root::getSingletonPtr()->loadPlugin("ogreparticlefx");
			#endif
		#else
			#ifdef MYOUSHU_DEBUG
				Ogre::Root::getSingletonPtr()->loadPlugin("libogreoctree_d");
				Ogre::Root::getSingletonPtr()->loadPlugin("libogreparticlefx_d");
			#else
				Ogre::Root::getSingletonPtr()->loadPlugin("libogreoctree");
				Ogre::Root::getSingletonPtr()->loadPlugin("libogreparticlefx");
			#endif
		#endif
	}

	/****************************************************************************/

	void Application::setupResourceManager() throw (Ogre::Exception)
	{
		TextFileManager *txtFileMgr;
		Ogre::ConfigFile cf;
		Ogre::ResourceGroupManager *resourceGroupMgr = Ogre::ResourceGroupManager::getSingletonPtr();

		// Create the TextFileManager
		txtFileMgr = new TextFileManager();
	 	LOG(EngineLog::LM_INFO_ENGINE, "TextFileManager created.");

		// Load the resources.cfg file
		cf.load(mConfigFilePath + Constants::RESOURCES_CONFIG_FILENAME);
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		// Read the file and create resource groups and add the specified paths to it
		while (seci.hasMoreElements())
		{
			// secName represents a ResourceGroup
			Ogre::String secName = seci.peekNextKey();

			Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();

			// Loop through the paths and add it to the resource group
			for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin();i != settings->end(); ++i)
			{
				Ogre::String typeName = i->first;
				Ogre::String archName = i->second;

				resourceGroupMgr->addResourceLocation(archName, typeName, secName);
			}

		}
	}

	void Application::initialiseResourceGroups(const Ogre::String& group) throw (Ogre::Exception)
	{
		Ogre::ResourceGroupManager *resourceGroupMgr = Ogre::ResourceGroupManager::getSingletonPtr();

		if (group == "")
		{
			// Initialize the resource groups
			resourceGroupMgr->initialiseAllResourceGroups();
		}
		else
		{
			// Initialise a specified resource group
			resourceGroupMgr->initialiseResourceGroup(group);
		}
	}


	/*****************************************************************************/
} // Myoushu

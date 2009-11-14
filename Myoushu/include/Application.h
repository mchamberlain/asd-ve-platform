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
 * @file Application.h
 * @author ME Chamberlain
 * @date April 2008
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Poco/RWLock.h"

//#include "OgreNoMemoryMacros.h"
//regular mem handler
//#include "OgreMemoryMacros.h"
#include "Ogre.h"
#include "TextFileManager.h"

#include "Platform.h"
#include "Singleton.h"
#include "NamedObject.h"
#include "EngineLog.h"
#include "Config.h"
#include "NotificationManager.h"
#include "ScriptManager.h"
#include "InputActionManager.h"
#include "KernelManager.h"
#include "GameObjectFactory.h"
#include "SceneFactory.h"
#include "ControllerFactory.h"
#include "AnimationManager.h"
#include "ControllerTaskManager.h"
#include "NetworkManager.h"
#include "NamedObjectInstanceCreatorManager.h"
#include "CollisionManager.h"
#include "VideoTaskManager.h"
#include "SQLiteGameLogManager.h"
#include "ReplayFactory.h"
#include "ReplayTaskManager.h"
#include "ContentImporterManager.h"
#include "SoundPluginManager.h"
#include "FunctorManager.h"
#include "LuaParser.h"
#include "GlobalLocks.h"
#include "Kernel.h"
#include "TimerTask.h"
#include "VideoTask.h"
#include "GUITask.h"
#include "InputTask.h"
#include "InputActionTask.h"
#include "ScriptTask.h"
#include "PhysicsTask.h"
#include "AnimationTask.h"
#include "ControllerTask.h"
#include "NetworkListenTask.h"
#include "NetworkTransmitTask.h"
#include "SQLiteGameLogTask.h"
#include "ReplayTask.h"
#include "ObjectPool.h"
#include "TimerTaskMessage.h"
#include "InputMessage.h"
#include "KernelMessage.h"
#include "ScriptMessage.h"
#include "GUIMessage.h"
#include "AnimationTaskMessage.h"
#include "ControllerTaskMessage.h"
#include "NetworkMessage.h"
#include "GameLogMessage.h"
#include "ReplayMessage.h"
#include "VideoTaskMessage.h"
#include "Random.h"
#include "Plugin.h"
#include "DefaultTranslation.h"

/**
 * Myoushu is a 3D Virtual Environment Engine that uses the Ogre 3D graphics engine and the Lua scripting language.
 */

namespace Myoushu
{

	/**
	 * Application entry point for a program created with the Myoushu engine.
	 */

	class MYOUSHU_API Application : public Ogre::Singleton<Application>, public NamedObject<Application>
	{
		public:
			/** Constructor. */
			Application();
			/** Destructor */
			~Application();

			CLASS_NAME_FUNCTIONS(Application);

			/** Initialization of Ogre that needs to be done prior to starting engine */
			void main(int argc = 0, char **argv = NULL);

			/** Sets the path to the configuration files used by the engine. */
			void setConfigFilePath(const std::string& configFilePath);

			/** Gets the currently set path to the configuration files used by the engine. */
			std::string getConfigFilePath() const;

			/**
			 * Initialize the engine. 
			 * @throw Exception
			 */
			void init() throw (Exception);

			/**
			 * Run the application (starts Kernel execution). The application is executed in the
			 * the same thread that this method is called from.
			 * @throw Exception
			 */
			void run() throw (Exception);

			/**
			 * Loads a shared library based plugin. This method should not be used for statically linked libraries.
			 * This method will call the dllStartPlugin global function defined in the plugin library, this function
			 * must call Application::installPlugin to install the plugin.
			 * @param name The name of the plugin. This must be the filename without an extension.
			 * @throws Exception::E_FILE_NOT_FOUND if the plugin library could not be found.
			 */
			void loadPlugin(const std::string& name) throw (Exception);

			/**
			 * Unloads a shared library based plugin. This method should not be used for statically linked libraries.
			 * This method will call the dllStopPlugin global function defined in the plugin library, this function
			 * must call Application::uninstallPlugin to uninstall the plugin.
			 * @param name The name of the plugin. This must be the filename without an extension.
			 * @throws Exception::E_FILE_NOT_FOUND if the plugin library could not be found.
			 */
			void unloadPlugin(const std::string& name) throw (Exception);

			/**
			 * Installs a plugin into the engine. The install() function of the plugin instance
			 * is called.
			 * @param pPlugin The Plugin instance to install.
			 * @throws Exception::E_NULL_POINTER if pPlugin is NULL.
			 */
			void installPlugin(Plugin *pPlugin) throw (Exception);

			/**
			 * Uninstalls a plugin from the engine. The uninstall() function of the plugin instance
			 * is called.
			 * @param pPlugin The Plugin instance to uninstall.
			 * @throws Exception::E_NULL_POINTER if pPlugin is NULL.
			 */
			void uninstallPlugin(Plugin *pPlugin) throw (Exception);

			/** Gets the value of the mInitialised flag. */
			bool getInitialised() const;

		protected:
			/** Type definition of a map of strings to Ogre::DynLib instances. */
			typedef std::map<std::string, Ogre::DynLib*> PluginLibsMap;
			/** Type definition of a map of strings to Plugin instances. */
			typedef std::map<std::string, Plugin*> PluginsMap;
			typedef void (*DLLPluginFunctionPtr)(void);

			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** Random number generator singleton. */
			Random *pRandom;
			/** Ogre Root */
			Ogre::Root *root;
			/** The Config singleton */
			Config *cfg;
			/** The EngineLog */
			EngineLog *log;
			/** The TextFileManager (Ogre resource manager) */
			TextFileManager *txtFileMgr;
			/** DefaultTranslation Singleton */
			DefaultTranslation *defaultTranslation;
			/** NamedObjectInstanceCreatorManager singleton */
			NamedObjectInstanceCreatorManager *namedObjectInstanceCreatorManager;
			/** NotificationManager singleton */
			NotificationManager *notificationManager;
			/** The KernelManager singleton */
			KernelManager *kernelManager;
			/** The ScriptManager singleton */
			ScriptManager *scriptManager;
			/** The InputActionManager singleton */
			InputActionManager *inputActionManager;
			/** The GameObjectFactory singleton */
			GameObjectFactory *gameObjectFactory;
			/** The SceneFactory singleton */
			SceneFactory *sceneFactory;
			/** The ControllerFactory singleton */
			ControllerFactory *controllerFactory;
			/** The ReplayFactory singleton */
			ReplayFactory *replayFactory;
			/** The AnimationManager singleton */
			AnimationManager *animationManager;
			/** The ControllerTaskManager singleton */
			ControllerTaskManager *controllerTaskManager;
			/** The NetworkManager singleton */
			NetworkManager *networkManager;
			/** The CollisionManager singleton */
			CollisionManager *collisionManager;
			/** The VideoTaskManager singleton */
			VideoTaskManager *videoTaskManager;
			/** The SQLiteGameLogManager */
			SQLiteGameLogManager *sqliteGameLogManager;
			/** The ReplayTaskManager */
			ReplayTaskManager *replayTaskManager;
			/** The ContentImporterManger singleton. */
			ContentImporterManager *contentImporterManager;
			/** The SoundPluginManger singleton. */
			SoundPluginManager *soundPluginManager;
			/** The FunctorManger singleton. */
			FunctorManager *functorManager;
			/** The Kernel */
			Kernel *kernel;
			/** The VideoTask */
			VideoTask *videoTask;
			/** The TimerTask */
			TimerTask *timerTask;
			/** The InputTask */
			InputTask *inputTask;
			/** The InputActionTask */
			InputActionTask *inputActionTask;
			/** The ScriptTask */
			ScriptTask *scriptTask;
			/** The GUITask */
			GUITask *guiTask;
			/** The PhysicsTask */
			PhysicsTask *physicsTask;
			/** The AnimationTask */
			AnimationTask *animationTask;
			/** The ControllerTask */
			ControllerTask *controllerTask;
			/** The NetworkListenTask */
			NetworkListenTask *networkListenTask;
			/** The NetworkTransmitTask */
			NetworkTransmitTask *networkTransmitTask;
			/** SQLiteGameLogTask */
			SQLiteGameLogTask *sqliteGameLogTask;
			/** ReplayTask */
			ReplayTask *replayTask;
			/** TimerTaskMessage Pool */
			ObjectPool<TimerTaskMessage> *timerTaskMessagePool;
			/** InputDeviceMessage Pool */
			ObjectPool<InputDeviceMessage> *inputDeviceMessagePool;
			/** InputMessage Pool */
			ObjectPool<InputMessage> *inputMessagePool;
			/** KernelMessage Pool */
			ObjectPool<KernelMessage> *kernelMessagePool;
			/** ScriptMessage Pool */
			ObjectPool<ScriptMessage> *scriptMessagePool;
			/** GUIMessage Pool */
			ObjectPool<GUIMessage> *guiMessagePool;
			/** NetworkMessage Pool */
			ObjectPool<NetworkMessage> *networkMessagePool;
			/** AnimatonTaskMessage Pool */
			ObjectPool<AnimationTaskMessage> *animationTaskMessagePool;
			/** ControllerTaskMessage Pool */
			ObjectPool<ControllerTaskMessage> *controllerTaskMessagePool;
			/** GameLogMessage pool */
			ObjectPool<GameLogMessage> *gameLogMessagePool;
			/** ReplayMessage pool */
			ObjectPool<ReplayMessage> *replayMessagePool;
			/** VideoTaskMessage pool */
			ObjectPool<VideoTaskMessage> *videoTaskMessagePool;
			/** The path to the config files used by the engine. */
			std::string mConfigFilePath;
			/** Read/write mutexes for thread safety on mPluginLibs, mPlugins and mInitialised. */
			mutable Poco::RWLock mRWLockPluginLibs;
			mutable Poco::RWLock mRWLockPlugins;
			mutable Poco::RWLock mRWLockInitialised;
			/** Map of Ogre::DynLib instances, the loaded shared library plugins. */
			PluginLibsMap mPluginLibs;
			/** Map of Plugin instances. */
			PluginsMap mPlugins;
			/** Flag indicating whether the engine is initialised. */
			bool mInitialised;

			/** Creates the various ObjectPool singletons. */
			void initObjectPools() throw (Exception);

			/** Destroyes the previously initialized ObjectPool singletons. */
			void destroyObjectPools() throw (Exception);

			/** Register classes with instance creator functions with the NamedObjectInstanceCreatorManager singleton. */
			void registerInstanceCreators();

			/** Unloads all loaded plugins. */
			void unloadPlugins();

			/** Initialises all installed plugins, called during the init() function. */
			void initialisePlugins();

			/** Shutdowns all installed plugins. Called when the engine shutsdown. */
			void shutdownPlugins();

			/** Sets the value of the mInitialised flag. */
			void setInitialised(bool initialised);

		private:
			/** Expose various functions to lua through tolua++. */
			void setupScriptBindings();

			/** Load the various plugins Ogre needs. */
			void loadPlugins();

			/** Setup the resource manager and load the resources required at startup. */
			void setupResourceManager() throw (Ogre::Exception);

			/** Initialise the specified resource group or all uninitialised resource groups.
			 * @param group The resource group to initialise. If group == "" all uninitialised
			 *				resource groups are initialised.
			 */
			void initialiseResourceGroups(const Ogre::String& group = "") throw (Ogre::Exception);

			/** Command line argument count. */
			int mArgc;
			/** Command line arguments */
			char** mArgv;
	};

	// inlines
	inline void Application::setConfigFilePath(const std::string& configFilePath)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mConfigFilePath = configFilePath;
	}

	inline std::string Application::getConfigFilePath() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mConfigFilePath;
	}

	inline bool Application::getInitialised() const
	{
		Poco::ScopedRWLock lock(mRWLockInitialised, false);

		return mInitialised;
	}

	inline void Application::setInitialised(bool initialised)
	{
		Poco::ScopedRWLock lock(mRWLockInitialised, true);

		mInitialised = initialised;
	}
}

#endif // APPLICATION_H

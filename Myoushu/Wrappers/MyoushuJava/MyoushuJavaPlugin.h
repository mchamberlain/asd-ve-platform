/**
 * @file MyoushuJavaPlugin.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_JAVA_PLUGIN_H
#define MYOUSHU_JAVA_PLUGIN_H

#include "Poco/RWLock.h"

#include "Plugin.h"

#include "MyoushuJavaPlatform.h"
#include "JavaFunctorFactory.h"

namespace Myoushu
{
	/** Class defining a generic Myoushu plugin. */
	class MYOUSHU_JAVA_API MyoushuJavaPlugin : public Myoushu::Plugin
	{
		public:
			/** Constructor. */
			MyoushuJavaPlugin(const std::string& name = "MyoushuJavaPlugin");

			/** Destructor. */
			virtual ~MyoushuJavaPlugin();

			/** 
			 * The plugin install sequence. This is called during engine start-up and should not rely 
			 * on other plugins or system already existing. It should only do a basic creation and installation
			 * sequence.
			 */
			virtual void install();

			/**
			 * Called after initial system start up and plugin installation. This section can rely on other
			 * systems and plugins existing and should do the initialisation necessary for the plugin to
			 * function.
			 */
			virtual void initialise();

			/**
			 * This is the opposite of shutdown, it is called before key parts of the system are unloaded.
			 */
			virtual void shutdown();

			/**
			 * Performs the final plugin uninstall sequence, unregister and destory the plugin instance.
			 */
			virtual void uninstall();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** The JavaFunctorFactory singleton */
			JavaFunctorFactory *mpFactory;
	};

	// inlines
	inline MyoushuJavaPlugin::MyoushuJavaPlugin(const std::string& name) : Myoushu::Plugin(name), mpFactory(NULL)
	{
	}

	inline MyoushuJavaPlugin::~MyoushuJavaPlugin()
	{
	}
}

#endif



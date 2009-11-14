/**
 * @file MyoushuJavaPlugin.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "EngineLog.h"
#include "FunctorManager.h"

#include "MyoushuJavaPlugin.h"

namespace Myoushu
{
	void MyoushuJavaPlugin::install()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		// Create the JavaFunctorFactory singleton
		LOG(EngineLog::LM_INFO_ENGINE, "[MyoushuJava]: Creating JavaFunctorFactory singleton...");
		mpFactory = new JavaFunctorFactory();
	}

	void MyoushuJavaPlugin::initialise()
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		// Register the JavaFunctorFactory singleton with the FunctorManager of the engine
		FunctorManager::getSingleton().registerFunctorFactory(mpFactory, NamedObject<JavaFunctor>::getStaticClassName());
	}

	void MyoushuJavaPlugin::shutdown()
	{
		// Unregister the MyoushuDotSceneContentImporterFactory singleton with the FunctorManager of the engine
		FunctorManager::getSingleton().unregisterFunctorFactory(NamedObject<JavaFunctor>::getStaticClassName());
	}

	void MyoushuJavaPlugin::uninstall()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		// Destroy the JavaFunctorFactory singleton
		if (mpFactory != NULL)
		{
			LOG(EngineLog::LM_INFO_ENGINE, "[MyoushuJava]: Destroying JavaFunctorFactory singleton...");
			delete mpFactory;
			mpFactory = NULL;
		}
	}

} // namespace Myoushu

/**
 * @file MyoushuJavaPluginDLL.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "MyoushuJavaPlatform.h"
#include "MyoushuJavaPlugin.h"

#include "Application.h"

namespace Myoushu
{
	static MyoushuJavaPlugin *pPlugin;

	extern "C" void MYOUSHU_JAVA_API dllStartPlugin()
	{
		pPlugin = new MyoushuJavaPlugin();

		Myoushu::Application::getSingleton().installPlugin(pPlugin);
	}

	extern "C" void MYOUSHU_JAVA_API dllStopPlugin()
	{
		if (pPlugin != NULL)
		{
			Myoushu::Application::getSingleton().uninstallPlugin(pPlugin);

			delete pPlugin;
		}
	}
}

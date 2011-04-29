/**
 * @file SampleCubes.Java
 * @author ME Chamberlain
 * @date January 2009
 */
 
import MyoushuJava.*;
 
public class SampleCubes extends Application
{

	public SampleCubes()
	{
		super();
	}
	
	public void start()
	{
		SampleCubesGameTask gameTask;
                TestTask testTask;

		// Initialize the Myoushu engine
		try
		{
			this.main();
            loadPlugin("MyoushuJava");
            loadPlugin("myoushuDotScene");
			init();
		}
		catch (java.lang.Exception e)
		{
			return;
		}

        // Run the GUIInit.lua script
        ScriptManager.getSingleton().executeScriptFile("GUIInit.lua", Constants.getRG_GUI());

		// Create and add the SampleCubesGameTask to the Kernel
		gameTask = new SampleCubesGameTask(Constants.getGAME_TASK_PRIORITY(), "SampleCubesGameTask"
			, Constants.getGAME_TASK_EXECUTION_INTERVAL(), Constants.getGAME_TASK_ITERATION_LIMIT());
                testTask = new TestTask(Constants.getGAME_TASK_PRIORITY(), "SampleCubesGameTask"
			, Constants.getGAME_TASK_EXECUTION_INTERVAL(), Constants.getGAME_TASK_ITERATION_LIMIT());
		KernelManager.getSingleton().addTask(gameTask);
		KernelManager.getSingleton().addTask(testTask);
		KernelManager.getSingleton().initAllTasks();

		run();
	}
}

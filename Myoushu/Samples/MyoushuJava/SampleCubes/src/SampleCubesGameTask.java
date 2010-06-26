
import MyoushuJava.*;

public class SampleCubesGameTask extends GameTask
{
	private static final float ROTATE_RATE = 0.1f;
	private static final float PITCH_RATE = 0.1f;
	private static final float MOVEMENT_RATE = 2.0f;
	private static final float SHOOT_SPEED = 100.0f;
	private static final float MICROSECONDS_IN_SECOND = 1000000.0f;
	private static final int PYRAMID_CUBE_BASE_CNT = 31;
	private static final int PILLAR_CUBE_CNT = 30;
	private static final int CUBE_HEIGHT = 2;

	/** The scene manager */
	private Scene scene;	
	/** The camera */
	private Camera camera;
	/** Mouse X coordinate */
	private int x;
	/** Mouse Y coordinate */
	private int y;
	/** Mouse Z coordinate */
	private int z;
	/** Cube cnt */
	private int cubeCnt;

	public SampleCubesGameTask(int priority, String name, long executionInterval, long iterationLimit)
	{
		super(priority, name, executionInterval, iterationLimit);
		scene = null;
		camera = null;
		x = 0;
		y = 0;
		z = 0;
		cubeCnt = 0;
	}

	public void init()
	{
		Light light;
        JavaFunctorFactory functorFactory = JavaFunctorFactory.getSingletonPtr();

		InputDevice kbInputDevice = InputDeviceFactory.getSingleton().getInputDevice("keyboard0").get();
		InputDevice msInputDevice = InputDeviceFactory.getSingleton().getInputDevice("mouse0").get();

		Config config = Singleton_Config.getSingleton();
		InputActionManager inputActionManager = Singleton_InputActionManager.getSingleton();

		// Bind spacebar to the createCube.
		config.bindInputAction(kbInputDevice, KeyboardInputDevice.getKI_SPACE(), "createCube");
		// Bind 1 to create a pillar of cubes
		config.bindInputAction(kbInputDevice, KeyboardInputDevice.getKI_1(), "createCubePillar");
		// Bind 2 to create a pyramid of cubes
		config.bindInputAction(kbInputDevice, KeyboardInputDevice.getKI_2(), "createCubePyramid");
		// Bind 'S' to toggle shadows
		config.bindInputAction(kbInputDevice, KeyboardInputDevice.getKI_S(), "toggleShadows");
		// Bind mouse movement to camera transformation
		config.bindInputAction(msInputDevice, MouseInputDevice.getMI_X_AXIS(), "transformCamera");
		config.bindInputAction(msInputDevice, MouseInputDevice.getMI_Y_AXIS(), "transformCamera");
		config.bindInputAction(msInputDevice, MouseInputDevice.getMI_WHEEL(), "transformCamera");

		// Register the function callback for the createCube action
		//inputActionManager.addInputActionCallback("createCube", this, &createCube);
		JavaFunctor functor = functorFactory.make("Functor");
        functor.setNumParams(1);
		functor.setMethod(this, "createCube", "(J)V");
		inputActionManager.addInputActionCallback("createCube", functor);
		// Register the function callback for the createCubePillar action
		functor = functorFactory.make("Functor");
        functor.setNumParams(1);
		functor.setMethod(this, "createCubePillar", "(J)V");
		inputActionManager.addInputActionCallback("createCubePillar", functor);
		// Register the function callback for the createCubePyramid action
		functor = functorFactory.make("Functor");
        functor.setNumParams(1);
		functor.setMethod(this, "createCubePyramid", "(J)V");
		inputActionManager.addInputActionCallback("createCubePyramid", functor);
		// Register the function callback for the toggleShadows action
		functor = functorFactory.make("Functor");
        functor.setNumParams(1);
		functor.setMethod(this, "toggleShadows", "(J)V");
		inputActionManager.addInputActionCallback("toggleShadows", functor);
		// Register the function callback for the transformCamera action
		functor = functorFactory.make("Functor");
        functor.setNumParams(1);
		functor.setMethod(this, "transformCamera", "(J)V");
		inputActionManager.addInputActionCallback("transformCamera", functor);

		// Setup the camera
		scene = Singleton_SceneFactory.getSingleton().find(Constants.getDEFAULT_SCENE_MANAGER());

		// If the scene manager cannot be found, log an error.
		if (scene == null)
		{
			//LOG(EngineLog.LM_ERROR, "Default scene manager not found: " << Constants.DEFAULT_SCENE_MANAGER);
			//throw Exception(Exception.E_NULL_POINTER, "Default scene manager not found.");
			return;
		}

		// Setup the camera
		camera = scene.getCamera(Constants.getDEFAULT_CAMERA());
		camera.setPosition(0, 20, 50);
		camera.lookAt(0, 20, 0);
		camera.setNearClipDistance(5);
		camera.setFarClipDistance(1000);

		// Setup shadows and lighting
		scene.setAmbientLight(new ColourValue(0.1f, 0.1f, 0.1f));
		scene.setShadowTechnique(ShadowTechnique.SHADOWTYPE_STENCIL_MODULATIVE);
		light = scene.createLight("Light1");
		light.setType(Light.LightTypes.LT_POINT);
		light.setPosition(-100, 100, 100);
		light.setDiffuseColour(1.0f, 1.0f, 1.0f);
		light.setSpecularColour(1.0f, 1.0f, 1.0f);

		// Set gravity and add a floor
		scene.setGravity(new Vector3(0f, -9.81f, 0f));
		scene.addFloor();

		Singleton_NetworkManager.getSingleton().setNetworkListenBehaviour(new P2PNetworkListenBehaviour());
                
                ContentImporter mpDotSceneImporter = Singleton_ContentImporterManager.getSingleton().make("Myoushu::MyoushuDotSceneProcessorImpl", "mpDotSceneImporter");
                System.out.println( "mpDotSceneImporter " + mpDotSceneImporter );

		// Call GameTask init method
		super.init();
	}

	public void toggleShadows(long messagePtr)
	{
		InputMessage message;

		message = new InputMessage(messagePtr, false);

		if ((message == null) || (message.getDeviceAction() != InputMessage.DeviceAction.DA_RELEASE))
		{
			return;
		}

		if (scene.getShadowTechnique() != ShadowTechnique.SHADOWTYPE_NONE)
		{
			scene.setShadowTechnique(ShadowTechnique.SHADOWTYPE_NONE);
		}
		else
		{
			scene.setShadowTechnique(ShadowTechnique.SHADOWTYPE_STENCIL_MODULATIVE);
		}
	}

	public void transformCamera(long messagePtr)
	{
		int relX;
		int relY;
		int relZ;
		float timeDelta;
		Vector3 vec;
		InputMessage inputMessage;

		inputMessage = new InputMessage(messagePtr, false);

		// Ensure a valid message was received, and that at least one of the mouse buttons is down
		if ((inputMessage == null) || (inputMessage.getDeviceAction() != InputMessage.DeviceAction.DA_MOVE))
		{
			return;
		}

		vec = new Vector3();

		// Get the time since since the last frame in seconds
		timeDelta = ((float) Singleton_TimerTask.getSingleton().getDelta()) / MICROSECONDS_IN_SECOND;

		relX = inputMessage.getDeviceState(InputMessage.getDS_X_INDEX()) - x;
		relY = inputMessage.getDeviceState(InputMessage.getDS_Y_INDEX()) - y;
		relZ = inputMessage.getDeviceState(InputMessage.getDS_Z_INDEX()) - z;

		if (inputMessage.getDeviceState(InputMessage.getDS_BUTTONS_STATE_INDEX()) == 1)
		{
			// Left mouse button is down
			camera.yaw(new Radian(relX * ROTATE_RATE * timeDelta));
			camera.pitch(new Radian(relY * PITCH_RATE * timeDelta));
		}
		else if (inputMessage.getDeviceState(InputMessage.getDS_BUTTONS_STATE_INDEX()) == 2)
		{
			// Right mouse button is down
			vec = Vector3.getZERO();
			vec.setX(1.0f * -relX * MOVEMENT_RATE * timeDelta);
			camera.moveRelative(vec);
			vec = Vector3.getZERO();
			vec.setY(1.0f * -relY * MOVEMENT_RATE * timeDelta);
			camera.moveRelative(vec);
		}
		else if (inputMessage.getDeviceState(InputMessage.getDS_BUTTONS_STATE_INDEX()) == 3)
		{
			// Both buttons down
			vec = Vector3.getZERO();
			vec.setZ(1.0f * relY * 2.0f * MOVEMENT_RATE * timeDelta);
			camera.moveRelative(vec);
		}
		
			vec = Vector3.getZERO();
			vec.setZ(-1.0f * relZ * 2.0f * MOVEMENT_RATE * timeDelta);
		camera.moveRelative(vec);

		// Update stored x and y values
		x = inputMessage.getDeviceState(InputMessage.getDS_X_INDEX());
		y = inputMessage.getDeviceState(InputMessage.getDS_Y_INDEX());
		z = inputMessage.getDeviceState(InputMessage.getDS_Z_INDEX());
	}

	public void createCube(long messagePtr)
	{
		Pose pose;
		ActorParams actorParams;
		InputMessage inputMessage;

		inputMessage = new InputMessage(messagePtr, false);

		// Only created a cube if the button is pressed
		if ((inputMessage != null) && (inputMessage.getDeviceAction() == InputMessage.DeviceAction.DA_RELEASE))
		{
			return;
		}

		GameObjectFactory gameObjectFactory = Singleton_GameObjectFactory.getSingleton();

		// If the scene manager cannot be found, log an error.
		if (scene == null)
		{
			//LOG(EngineLog.LM_ERROR, "Default scene manager not found: " << Constants.DEFAULT_SCENE_MANAGER);
			return;
		}

		Vector3 direction = camera.getDirection();
		actorParams = new ActorParams("mass: 100, linearvelocity: "
			+ direction.getX() * SHOOT_SPEED + " "
			+ direction.getY() * SHOOT_SPEED + " "
			+ direction.getZ() * SHOOT_SPEED);

		pose = new Pose(camera.getPosition(), camera.getOrientation());
		GameBodyObject body = gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new CubeShape(2.0f), pose, actorParams);
                KeyValueProperties p = body.getProperties();
                Value v = new Value();
                v.set( 10.0f );
                p.insert( "test", v);
                Value v2 = p.get( "test" );
                System.out.println( "From properties, value test: " + v2.getFloat() );

                System.out.println( scene.getActor( body.getName() ) );
                System.out.println( Utility.castGameBodyObjectToActor(body) );
                System.out.println( "mass: " + Utility.castGameBodyObjectToActor(body).getMass() );
		cubeCnt++;
		//LOG(EngineLog.LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
	}

	public void createCubePillar(long messagePtr)
	{
		Pose pose;
		ActorParams actorParams;
		InputMessage inputMessage;

        System.out.println("Pillar " + messagePtr);
        
		inputMessage = new InputMessage(messagePtr, false);

		// Only created a cube if the button is pressed
		if ((inputMessage != null) && (inputMessage.getDeviceAction() == InputMessage.DeviceAction.DA_RELEASE))
		{
			return;
		}

		GameObjectFactory gameObjectFactory = Singleton_GameObjectFactory.getSingleton();

		// If the scene manager cannot be found, log an error.
		if (scene == null)
		{
			//LOG(EngineLog.LM_ERROR, "Default scene manager not found: " << Constants.DEFAULT_SCENE_MANAGER);
			return;
		}

		actorParams = new ActorParams("mass: 50");

		for (int i = 0; i < PILLAR_CUBE_CNT; i++)
		{
    		pose = new Pose(new Vector3(0, CUBE_HEIGHT / 2 + i * (CUBE_HEIGHT), 0));
			gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new CubeShape(2.0f), pose, actorParams);
			cubeCnt++;
		}

		//LOG(EngineLog.LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
	}

	public void createCubePyramid(long messagePtr)
	{
		Pose pose;
		ActorParams actorParams;
		int cubeBaseCnt;
		InputMessage inputMessage;

		inputMessage = new InputMessage(messagePtr, false);

		// Only created a cube if the button is pressed
		if ((inputMessage != null) && (inputMessage.getDeviceAction() == InputMessage.DeviceAction.DA_RELEASE))
		{
			return;
		}

		GameObjectFactory gameObjectFactory = Singleton_GameObjectFactory.getSingleton();

		// If the scene manager cannot be found, log an error.
		if (scene == null)
		{
			//LOG(EngineLog.LM_ERROR, "Default scene manager not found: " << Constants.DEFAULT_SCENE_MANAGER);
			return;
		}

		actorParams = new ActorParams("mass: 50");

		for (cubeBaseCnt = PYRAMID_CUBE_BASE_CNT; cubeBaseCnt >= 1; cubeBaseCnt -= 2)
		{
			float leftMostCubeCenter = -cubeBaseCnt * CUBE_HEIGHT / 2 + CUBE_HEIGHT / 2;
			float yCenter = (PYRAMID_CUBE_BASE_CNT - cubeBaseCnt) / 2 * CUBE_HEIGHT + CUBE_HEIGHT / 2;

			for (int i = 0; i < cubeBaseCnt; i++)
			{
				pose = new Pose(new Vector3(leftMostCubeCenter + i * CUBE_HEIGHT, yCenter, 0));
				gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new CubeShape(2.0f), pose, actorParams);

				cubeCnt++;
			}
		}

		//LOG(EngineLog.LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
	}
}
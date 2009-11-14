#include <iostream>

#include "Ogre.h"
#include "NxOgre.h"

#include "Config.h"
#include "InputActionManager.h"
#include "SceneFactory.h"
#include "InputDeviceFactory.h"
#include "KeyboardInputDevice.h"
#include "MouseInputDevice.h"
#include "GUIManager.h"
#include "Constants.h"
#include "GameObjectFactory.h"
#include "EngineLog.h"
#include "Exception.h"
#include "NetworkManager.h"
#include "P2PNetworkListenBehaviour.h"
#include "TimerTask.h"

#include "SampleCubesGameTask.h"

#define ROTATE_RATE 0.001f
#define PITCH_RATE 0.001f
#define MOVEMENT_RATE 0.02f
#define SHOOT_SPEED 100.0f

SampleCubesGameTask::SampleCubesGameTask(int priority, const std::string& name, double executionInterval, unsigned int iterationLimit) : GameTask(priority, name, executionInterval, iterationLimit), scene(NULL), camera(NULL), x(0), y(0), z(0), cubeCnt(0)
{
}

SampleCubesGameTask::~SampleCubesGameTask()
{
}

void SampleCubesGameTask::init() throw (Myoushu::Exception)
{
	Ogre::Light *light;

	const Myoushu::InputDevice *kbInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("keyboard0").get();
	const Myoushu::InputDevice *msInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("mouse0").get();

	Myoushu::Config &config = Myoushu::Config::getSingleton();
	Myoushu::InputActionManager &inputActionManager = Myoushu::InputActionManager::getSingleton();

	// Bind spacebar to the createCube.
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_SPACE, "createCube");
	// Bind 1 to create a pillar of cubes
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_1, "createCubePillar");
	// Bind 2 to create a pyramid of cubes
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_2, "createCubePyramid");
	// Bind 'S' to toggle shadows
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_S, "toggleShadows");
	// Bind mouse movement to camera transformation
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_X_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_Y_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_WHEEL, "transformCamera");

	// Register the function callback for the createCube action
	inputActionManager.addInputActionCallback("createCube", this, &SampleCubesGameTask::createCube);
	// Register the function callback for the createCubePillar action
	inputActionManager.addInputActionCallback("createCubePillar", this, &SampleCubesGameTask::createCubePillar);
	// Register the function callback for the createCubePyramid action
	inputActionManager.addInputActionCallback("createCubePyramid", this, &SampleCubesGameTask::createCubePyramid);
	// Register the function callback for the toggleShadows action
	inputActionManager.addInputActionCallback("toggleShadows", this, &SampleCubesGameTask::toggleShadows);
	// Register the function callback for the transformCamera action
	inputActionManager.addInputActionCallback("transformCamera", this, &SampleCubesGameTask::transformCamera);

	// Setup the camera
	scene = Myoushu::SceneFactory::getSingleton().find(Myoushu::Constants::DEFAULT_SCENE_MANAGER);

	// If the scene manager cannot be found, log an error.
	if (scene == NULL)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "Default scene manager not found: " << Myoushu::Constants::DEFAULT_SCENE_MANAGER);
		throw Myoushu::Exception(Myoushu::Exception::E_NULL_POINTER, "Default scene manager not found.");
	}

	// Setup the camera
	camera = scene->getCamera(Myoushu::Constants::DEFAULT_CAMERA);
	camera->setPosition(0, 20, 50);
	camera->lookAt(0, 20, 0);
	camera->setNearClipDistance(5);

	// Setup shadows and lighting
	scene->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	scene->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	light = scene->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(-100, 100, 100);
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);

	// Set gravity and add a floor
	scene->setGravity(Ogre::Vector3(0, -9.81, 0));
	scene->addFloor();

	Myoushu::NetworkManager::getSingleton().setNetworkListenBehaviour(new Myoushu::P2PNetworkListenBehaviour());

	// Call GameTask init method
	GameTask::init();
}

void SampleCubesGameTask::toggleShadows(Myoushu::InputMessage *message)
{
	if ((message == NULL) || (message->getDeviceAction() != Myoushu::InputDeviceMessage::DA_RELEASE))
	{
		return;
	}

	if (scene->getShadowTechnique() != Ogre::SHADOWTYPE_NONE)
	{
		scene->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	}
	else
	{
		scene->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	}
}

void SampleCubesGameTask::transformCamera(Myoushu::InputMessage *inputMessage)
{
	int relX;
	int relY;
	int relZ;
	float timeDelta;

	// Ensure a valid message was received, and that at least one of the mouse buttons is down
	if ((inputMessage == NULL) || (inputMessage->getDeviceAction() != Myoushu::InputDeviceMessage::DA_MOVE))
	{
		return;
	}

	// Get the time since since the last frame in seconds
	if (Myoushu::Constants::INPUT_TASK_EXECUTION_INTERVAL != 0)
	{
		timeDelta = ((float) Myoushu::Constants::INPUT_TASK_EXECUTION_INTERVAL) / MICROSECONDS_IN_SECOND;
	}
	else
	{
		timeDelta = ((float) Myoushu::TimerTask::getSingleton().getDelta()) / MICROSECONDS_IN_SECOND;
	}
	timeDelta = 1.0f;

	relX = inputMessage->getDeviceState(Myoushu::InputMessage::DS_X_INDEX) - x;
	relY = inputMessage->getDeviceState(Myoushu::InputMessage::DS_Y_INDEX) - y;
	relZ = inputMessage->getDeviceState(Myoushu::InputMessage::DS_Z_INDEX) - z;

	if (inputMessage->getDeviceState(Myoushu::InputMessage::DS_BUTTONS_STATE_INDEX) == 1)
	{
		// Left mouse button is down
		camera->yaw(Ogre::Radian(relX * ROTATE_RATE * timeDelta));
		camera->pitch(Ogre::Radian(relY * PITCH_RATE * timeDelta));
	}
	else if (inputMessage->getDeviceState(Myoushu::InputMessage::DS_BUTTONS_STATE_INDEX) == 2)
	{
		// Right mouse button is down
		camera->moveRelative(Ogre::Vector3::UNIT_X * -relX * MOVEMENT_RATE * timeDelta);
		camera->moveRelative(Ogre::Vector3::UNIT_Y * -relY * MOVEMENT_RATE * timeDelta);
	}
	else if (inputMessage->getDeviceState(Myoushu::InputMessage::DS_BUTTONS_STATE_INDEX) == 3)
	{
		// Both buttons down
		camera->moveRelative(Ogre::Vector3::UNIT_Z * relY * 2.0f * MOVEMENT_RATE * timeDelta);
	}
	
	camera->moveRelative(-Ogre::Vector3::UNIT_Z * relZ * 2.0f * MOVEMENT_RATE * timeDelta);

	// Update stored x and y values
	x = inputMessage->getDeviceState(Myoushu::InputMessage::DS_X_INDEX);
	y = inputMessage->getDeviceState(Myoushu::InputMessage::DS_Y_INDEX);
	z = inputMessage->getDeviceState(Myoushu::InputMessage::DS_Z_INDEX);
}

void SampleCubesGameTask::createCube(Myoushu::InputMessage *inputMessage)
{
	NxOgre::Pose pose;
	NxOgre::ActorParams actorParams;

	// Only created a cube if the button is pressed
	if ((inputMessage != NULL) && (inputMessage->getDeviceAction() == Myoushu::InputDeviceMessage::DA_RELEASE))
	{
		return;
	}

	Myoushu::GameObjectFactory &gameObjectFactory = Myoushu::GameObjectFactory::getSingleton();

	// If the scene manager cannot be found, log an error.
	if (scene == NULL)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "Default scene manager not found: " << Myoushu::Constants::DEFAULT_SCENE_MANAGER);
		return;
	}

	actorParams.mMass = 100;
	
	const Ogre::Vector3& direction = camera->getDirection();

	actorParams.mLinearVelocity = NxVec3(direction.x, direction.y, direction.z) * SHOOT_SPEED;
	pose = NxOgre::Pose(camera->getPosition(), camera->getOrientation());
	gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new NxOgre::CubeShape(2.0), pose, actorParams);

	cubeCnt++;
	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
}

void SampleCubesGameTask::createCubePillar(Myoushu::InputMessage *inputMessage)
{
	NxOgre::Pose pose;
	NxOgre::ActorParams actorParams;

	// Only created a cube if the button is pressed
	if ((inputMessage != NULL) && (inputMessage->getDeviceAction() == Myoushu::InputDeviceMessage::DA_RELEASE))
	{
		return;
	}

	Myoushu::GameObjectFactory &gameObjectFactory = Myoushu::GameObjectFactory::getSingleton();

	// If the scene manager cannot be found, log an error.
	if (scene == NULL)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "Default scene manager not found: " << Myoushu::Constants::DEFAULT_SCENE_MANAGER);
		return;
	}

	actorParams.mMass = 50;

	for (unsigned int i = 0; i < PILLAR_CUBE_CNT; i++)
	{
		pose = Ogre::Vector3(0, CUBE_HEIGHT / 2 + i * (CUBE_HEIGHT), 0);
		gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new NxOgre::CubeShape(2.0), pose, actorParams);
		cubeCnt++;
	}

	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
}

void SampleCubesGameTask::createCubePyramid(Myoushu::InputMessage *inputMessage)
{
	NxOgre::Pose pose;
	NxOgre::ActorParams actorParams;
	int cubeBaseCnt;

	// Only created a cube if the button is pressed
	if ((inputMessage != NULL) && (inputMessage->getDeviceAction() == Myoushu::InputDeviceMessage::DA_RELEASE))
	{
		return;
	}

	Myoushu::GameObjectFactory &gameObjectFactory = Myoushu::GameObjectFactory::getSingleton();

	// If the scene manager cannot be found, log an error.
	if (scene == NULL)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "Default scene manager not found: " << Myoushu::Constants::DEFAULT_SCENE_MANAGER);
		return;
	}

	actorParams.mMass = 50;

	for (cubeBaseCnt = PYRAMID_CUBE_BASE_CNT; cubeBaseCnt >= 1; cubeBaseCnt -= 2)
	{
		Ogre::Real leftMostCubeCenter = -cubeBaseCnt * CUBE_HEIGHT / 2 + CUBE_HEIGHT / 2;
		Ogre::Real yCenter = (PYRAMID_CUBE_BASE_CNT - cubeBaseCnt) / 2 * CUBE_HEIGHT + CUBE_HEIGHT / 2;

		for (unsigned int i = 0; i < cubeBaseCnt; i++)
		{
			pose = Ogre::Vector3(leftMostCubeCenter + i * CUBE_HEIGHT, yCenter, 0);
			gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new NxOgre::CubeShape(2.0), pose, actorParams);

			cubeCnt++;
		}
	}

	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "Cube count: " << cubeCnt);
}

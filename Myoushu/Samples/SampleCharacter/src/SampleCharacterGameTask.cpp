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
#include "ControllerFactory.h"
#include "ControllerTaskManager.h"
#include "GameCharacterObjectAction.h"
#include "CollisionManager.h"
#include "ActorCharacterCollisionClassCallback.h"
#include "CameraWithGameObjectController.h"

#include "SampleCharacterGameTask.h"

#define ROTATE_RATE 0.1f
#define PITCH_RATE 0.1f
#define MOVEMENT_RATE 2.0f
#define SHOOT_SPEED 100.0f

SampleCharacterGameTask::SampleCharacterGameTask(int priority, const std::string& name, double executionInterval, unsigned int iterationLimit) 
	: GameTask(priority, name, executionInterval, iterationLimit), scene(NULL), camera(NULL), x(0), y(0), z(0), character(NULL), controller(NULL)
{
}

SampleCharacterGameTask::~SampleCharacterGameTask()
{
}

void SampleCharacterGameTask::init() throw (Myoushu::Exception)
{
	Ogre::Light *light;

	const Myoushu::InputDevice *kbInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("keyboard0").get();
	const Myoushu::InputDevice *msInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("mouse0").get();

	Myoushu::Config &config = Myoushu::Config::getSingleton();
	Myoushu::InputActionManager &inputActionManager = Myoushu::InputActionManager::getSingleton();

	// Bind spacebar to the createCube.
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_SPACE, "createCube");
	// Bind W to moveForward.
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_W, "moveForward");
	// Bind S to moveBackward
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_S, "moveBackward");
	// Bind A to strafeLeft
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_A, "strafeLeft");
	// Bind D to strafeRight
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_D, "strafeRight");
	// Bind H to toggleShadows
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_H, "toggleShadows");
	// Bind V to toggleView
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_V, "toggleView");
	// Bind mouse movement to camera transformation
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_X_AXIS, "transformCameraX");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_Y_AXIS, "transformCameraY");
	//config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_WHEEL, "transformCamera");

	inputActionManager.addInputActionCallback("createCube", this, &SampleCharacterGameTask::createCube);
	// Register the function callback for the moveForward action
	inputActionManager.addInputActionCallback("moveForward", this, &SampleCharacterGameTask::moveCharacter);
	// Register the function callback for the moveBackward action
	inputActionManager.addInputActionCallback("moveBackward", this, &SampleCharacterGameTask::moveCharacter);
	// Register the function callback for the stafeLeft action
	inputActionManager.addInputActionCallback("strafeLeft", this, &SampleCharacterGameTask::moveCharacter);
	// Register the function callback for the strafeRight action
	inputActionManager.addInputActionCallback("strafeRight", this, &SampleCharacterGameTask::moveCharacter);
	// Register the function callback for the toggleShadows action
	inputActionManager.addInputActionCallback("toggleShadows", this, &SampleCharacterGameTask::toggleShadows);
	// Register the function callback for the toggleView action
	inputActionManager.addInputActionCallback("toggleView", this, &SampleCharacterGameTask::toggleView);
	// Register the function callback for the transformCamera action
	//inputActionManager.addInputActionCallback("transformCamera", this, &SampleCharacterGameTask::transformCamera);

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
	camera->setPosition(0, 30, 15);
	camera->lookAt(0, 20, 0);
	camera->setFarClipDistance(1000);
	camera->setNearClipDistance(1);

	// Setup shadows and lighting
	scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	scene->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
	light = scene->createLight("Light1");
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(-100, 100, 100);
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 1.0, 1.0);

	// Set gravity and add a floor
	scene->setGravity(Ogre::Vector3(0, -9.81, 0));
	scene->addFloor();

	// Setup collision reporting
	Myoushu::CollisionManager::getSingleton().enableActorCharacterCollisionReporting(scene);
	Myoushu::CollisionManager::getSingleton().setGlobalActorCharacterCallback(new Myoushu::ActorCharacterCollisionClassCallback<SampleCharacterGameTask>(this, &SampleCharacterGameTask::actorCharacterCollision));

	createCharacter();

	// Call GameTask init method
	GameTask::init();
}

void SampleCharacterGameTask::actorCharacterCollision(Myoushu::GameCharacterObject *pCharacter, Myoushu::GameActorObject *pActor, Myoushu::CollisionManager::CollisionProperties cProps)
{
	//LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "Collision bewteen character: " << pCharacter->getName() << " and actor: " << pActor->getName());
}

void SampleCharacterGameTask::createCharacter()
{
	NxOgre::ActorParams actorParams;
	NxOgre::CharacterParams params;
	Myoushu::GameCharacterObjectAction *pCharacterAction;
	Myoushu::CameraWithGameObjectController* pCameraController;
	Ogre::Vector3 moveDirection;

	// Create fake floor for character to walk on
	actorParams.setToDefault();
	// Make the actor static by setting its mass to zero.
	actorParams.mMass = 0;
	Myoushu::GameObjectFactory::getSingleton().makeActor("FakeFloor", scene, new NxOgre::CubeShape(1000, 1, 1000), NxOgre::Pose(0, -0.5f, 0), actorParams);

	params.setToDefault();
	params.mType = NxOgre::CharacterParams::CT_Box;
	params.mDimensions = NxVec3(10, 10, 10);
	params.mUpAxis = NX_Y;

	// Create the character
	character = Myoushu::GameObjectFactory::getSingleton().makeCharacter("ninja", "ninja.mesh", "ninja.skeleton", scene, NxOgre::Pose(0, 10, 0), params);

	character->getNode()->setScale(1.0f / 10.0f, 1.0f / 10.0f, 1.0f / 10.0f);

	character->addAction("Walk", false, "Walk", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	character->addAction("Strafe", false, "Walk", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	character->addAction("Run", false, "Run", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	Myoushu::ControllerFactory::getSingleton().makeGameCharacterObjectCameraControllerPair("camera_controller", "ninja_controller", character, camera, "moveForward", "moveBackward"
		, "strafeLeft", "strafeRight", "transformCameraY", "transformCameraY", "transformCameraX", "transformCameraX", "Walk", "Walk", "Strafe", "Strafe"
		, Ogre::Vector3(0.0f, 19.0f, -1.0f), 20.0f, 20.0f, 30.0f, 0.25f, 0.15f);
}

void SampleCharacterGameTask::toggleShadows(Myoushu::InputMessage *message)
{
	if ((message == NULL) || (message->getDeviceAction() != Myoushu::InputMessage::DA_RELEASE))
	{
		return;
	}

	if (scene->getShadowTechnique() != Ogre::SHADOWTYPE_NONE)
	{
		scene->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
	}
	else
	{
		scene->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
	}
}

void SampleCharacterGameTask::toggleView(Myoushu::InputMessage *message)
{
	Myoushu::CameraWithGameObjectController* pCameraController;

	if ((message == NULL) || (message->getDeviceAction() != Myoushu::InputMessage::DA_RELEASE))
	{
		return;
	}

	pCameraController = static_cast<Myoushu::CameraWithGameObjectController*>(Myoushu::ControllerFactory::getSingleton().findByName("camera_controller"));
	if (pCameraController != NULL)
	{
		if (pCameraController->getDistanceFromObject() == 0)
		{
			pCameraController->setDistanceFromObject(20.0f);
		}
		else
		{
			pCameraController->setDistanceFromObject(0);
		}
	}
}

void SampleCharacterGameTask::transformCamera(Myoushu::InputMessage *inputMessage)
{
	int relX;
	int relY;
	int relZ;
	float timeDelta;

	// Ensure a valid message was received, and that at least one of the mouse buttons is down
	if ((inputMessage == NULL) || (inputMessage->getDeviceAction() != Myoushu::InputMessage::DA_MOVE))
	{
		return;
	}

	// Get the time since since the last frame in seconds
	timeDelta = ((float) Myoushu::Constants::INPUT_TASK_EXECUTION_INTERVAL) / MICROSECONDS_IN_SECOND;

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

void SampleCharacterGameTask::moveCharacter(Myoushu::InputMessage *inputMessage)
{
	//character->addMovement(NxOgre::Character::Direction::DR_Forward);
}

void SampleCharacterGameTask::execute(unsigned long timeDelta)
{
	GameTask::execute(timeDelta);
}

void SampleCharacterGameTask::createCube(Myoushu::InputMessage *inputMessage)
{
	NxOgre::Pose pose;
	NxOgre::ActorParams actorParams;

	// Only created a cube if the button is pressed
	if ((inputMessage != NULL) && (inputMessage->getDeviceAction() == Myoushu::InputMessage::DA_RELEASE))
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

	actorParams.setToDefault();
	actorParams.mMass = 100;
	
	const Ogre::Vector3& direction = camera->getDirection();

	actorParams.mLinearVelocity = NxVec3(direction.x, direction.y, direction.z) * SHOOT_SPEED;
	pose = NxOgre::Pose(camera->getPosition(), camera->getOrientation());
	gameObjectFactory.makeBody("Cube", "cube.mesh", scene, new NxOgre::CubeShape(2.0), pose, actorParams);
}
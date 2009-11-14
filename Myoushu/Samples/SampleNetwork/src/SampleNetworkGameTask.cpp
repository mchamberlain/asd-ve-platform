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
#include "NetworkManager.h"
#include "P2PNetworkListenBehaviour.h"
#include "P2PNetworkTransmitBehaviour.h"
#include "ObjectPool.h"

#include "SampleNetworkGameTask.h"

#define ROTATE_RATE 0.1f
#define PITCH_RATE 0.1f
#define MOVEMENT_RATE 2.0f
#define SHOOT_SPEED 100.0f

SampleNetworkGameTask::SampleNetworkGameTask(int priority, const std::string& name, double executionInterval, unsigned int iterationLimit) 
	: GameTask(priority, name, executionInterval, iterationLimit), scene(NULL), camera(NULL), x(0), y(0), z(0), character(NULL), controller(NULL)
{
}

SampleNetworkGameTask::~SampleNetworkGameTask()
{
}

void SampleNetworkGameTask::init() throw (Myoushu::Exception)
{
	Ogre::Light *light;
	Myoushu::P2PNetworkListenBehaviour *pNetBehaviour;
	Myoushu::P2PNetworkTransmitBehaviour *pNetTransmitBehaviour;

	const Myoushu::InputDevice *kbInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("keyboard0").get();
	const Myoushu::InputDevice *msInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("mouse0").get();

	Myoushu::Config &config = Myoushu::Config::getSingleton();
	Myoushu::InputActionManager &inputActionManager = Myoushu::InputActionManager::getSingleton();

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
	// Bind mouse movement to camera transformation
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_X_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_Y_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_WHEEL, "transformCamera");

	// Register the function callback for the moveForward action
	inputActionManager.addInputActionCallback("moveForward", this, &SampleNetworkGameTask::moveCharacter);
	// Register the function callback for the moveBackward action
	inputActionManager.addInputActionCallback("moveBackward", this, &SampleNetworkGameTask::moveCharacter);
	// Register the function callback for the stafeLeft action
	inputActionManager.addInputActionCallback("strafeLeft", this, &SampleNetworkGameTask::moveCharacter);
	// Register the function callback for the strafeRight action
	inputActionManager.addInputActionCallback("strafeRight", this, &SampleNetworkGameTask::moveCharacter);
	// Register the function callback for the toggleShadows action
	inputActionManager.addInputActionCallback("toggleShadows", this, &SampleNetworkGameTask::toggleShadows);
	// Register the function callback for the transformCamera action
	inputActionManager.addInputActionCallback("transformCamera", this, &SampleNetworkGameTask::transformCamera);

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

	createCharacter();

	// Set the Network behaviour to P2P
	pNetBehaviour = new Myoushu::P2PNetworkListenBehaviour();
	pNetBehaviour->setNetworkMessageCallback(Myoushu::NetworkMessage::NM_CONNECT, this, &SampleNetworkGameTask::processConnect);
	pNetBehaviour->setNetworkMessageCallback(Myoushu::NetworkMessage::NM_ACK_CONNECT, this, &SampleNetworkGameTask::processAckConnect);
	Myoushu::NetworkManager::getSingleton().setNetworkListenBehaviour(pNetBehaviour);

	// Set the NetworkTransmitBehaviour to P2P
	pNetTransmitBehaviour = new Myoushu::P2PNetworkTransmitBehaviour();
	// Disallow the transmission of the transformCamera action across the network
	pNetTransmitBehaviour->addDisallowedInputAction("transformCamera");
	Myoushu::NetworkManager::getSingleton().setNetworkTransmitBehaviour(pNetTransmitBehaviour);

	// Call GameTask init method
	GameTask::init();
}

void SampleNetworkGameTask::createCharacter()
{
	NxOgre::ActorParams actorParams;
	NxOgre::CharacterParams params;
	Myoushu::GameCharacterObjectAction *pCharacterAction;
	Ogre::Vector3 moveDirection;

	// Create fake floor for character to walk on
	actorParams.setToDefault();
	// Make the actor static by setting its mass to zero.
	actorParams.mMass = 0;
	Myoushu::GameObjectFactory::getSingleton().makeActor("FakeFloor", scene, new NxOgre::CubeShape(100, 1, 100), NxOgre::Pose(0, -0.5f, 0), actorParams);

	params.setToDefault();
	params.mType = NxOgre::CharacterParams::CT_Box;
	params.mDimensions = NxVec3(10, 5, 10);
	params.mUpAxis = NX_Y;

	// Create the character
	character = Myoushu::GameObjectFactory::getSingleton().makeCharacter("jaiqua", "jaiqua.mesh", "jaiqua.skeleton", scene, NxOgre::Pose(0, 10, 0), params);

	character->addAction("Walk", false, "Walk", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	character->addAction("Strafe", false, "Walk", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	character->addAction("Run", false, "Run", Myoushu::GameCharacterObjectAction::AM_LOOP, false, true);

	// Create the character controller
	controller = Myoushu::ControllerFactory::getSingleton().make("jaiqua_controller", character);
	moveDirection.x = 0;
	moveDirection.y = 0;
	moveDirection.z = -1;
	controller->bind("moveForward", "Walk", moveDirection);
	moveDirection.z = 1;
	controller->bind("moveBackward", "Walk", moveDirection);
	moveDirection.x = -1;
	moveDirection.z = 0;
	controller->bind("strafeLeft", "Strafe", moveDirection);
	moveDirection.x = 1;
	moveDirection.y = 0;
	controller->bind("strafeRight", "Strafe", moveDirection);
	controller->setMaxMovementSpeed(5);
	controller->setMovementAcceleration(10);

	Myoushu::ControllerTaskManager::getSingleton().addController(controller);
}

void SampleNetworkGameTask::toggleShadows(Myoushu::InputMessage *message)
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

void SampleNetworkGameTask::transformCamera(Myoushu::InputMessage *inputMessage)
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

void SampleNetworkGameTask::moveCharacter(Myoushu::InputMessage *inputMessage)
{
	//character->addMovement(NxOgre::Character::Direction::DR_Forward);
}

void SampleNetworkGameTask::execute(unsigned long timeDelta)
{
	GameTask::execute(timeDelta);
}

bool SampleNetworkGameTask::processConnect(Myoushu::NetworkMessage *networkMessage)
{
	Myoushu::NetworkManager *pNetworkMan;

	pNetworkMan = Myoushu::NetworkManager::getSingletonPtr();

	// Send the local character over to the remote host
	pNetworkMan->sendCreateObjectMessage(networkMessage->getSource().toString(), character->getName(), character->getClassName(), character);
	// Send the local character controller over to the remote host
	pNetworkMan->sendCreateObjectMessage(networkMessage->getSource().toString(), controller->getName(), controller->getClassName(), controller);

	return true;
}

bool SampleNetworkGameTask::processAckConnect(Myoushu::NetworkMessage *networkMessage)
{
	Myoushu::NetworkManager *pNetworkMan;

	pNetworkMan = Myoushu::NetworkManager::getSingletonPtr();

	// Send the local character over to the remote host
	pNetworkMan->sendCreateObjectMessage(networkMessage->getSource().toString(), character->getName(), character->getClassName(), character);
	// Send the local character controller over to the remote host
	pNetworkMan->sendCreateObjectMessage(networkMessage->getSource().toString(), controller->getName(), controller->getClassName(), controller);

	return true;
}

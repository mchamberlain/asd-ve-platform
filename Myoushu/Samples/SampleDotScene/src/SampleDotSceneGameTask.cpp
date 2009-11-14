#include <iostream>
#include <ostream>

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
#include "GlobalLocks.h"
#include "AnimationManager.h"
#include "CollisionManager.h"
#include "CollisionClassCallback.h"
#include "ContentImporterManager.h"
#include "TimerTask.h"

#include "SampleDotSceneGameTask.h"

#define SHOOT_SPEED 50.0f
#define ROTATE_RATE 0.1f
#define PITCH_RATE 0.1f
#define MOVEMENT_RATE 2.0f

SampleDotSceneGameTask::SampleDotSceneGameTask(int priority, const std::string& name, double executionInterval, unsigned int iterationLimit) : GameTask(priority, name, executionInterval, iterationLimit), scene(NULL), camera(NULL), mpDotSceneImporter(NULL), x(0), y(0), z(0), gui(NULL), animationsWindow(NULL), numAnimations(0)
{
}

SampleDotSceneGameTask::~SampleDotSceneGameTask()
{
}

void SampleDotSceneGameTask::init() throw (Myoushu::Exception)
{
	Ogre::Light *light;

	const Myoushu::InputDevice *kbInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("keyboard0").get();
	const Myoushu::InputDevice *msInputDevice = Myoushu::InputDeviceFactory::getSingleton().getInputDevice("mouse0").get();

	Myoushu::Config &config = Myoushu::Config::getSingleton();
	Myoushu::InputActionManager &inputActionManager = Myoushu::InputActionManager::getSingleton();

	// Bind spacebar to the createCube.
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_SPACE, "createCube");
	// Bind 'P' to print the scene graph
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_P, "printScene");
	// Bind 'S' to toggle shadows
	config.bindInputAction(kbInputDevice, Myoushu::KeyboardInputDevice::KI_S, "toggleShadows");
	// Bind mouse movement to camera transformation
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_X_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_Y_AXIS, "transformCamera");
	config.bindInputAction(msInputDevice, Myoushu::MouseInputDevice::MI_WHEEL, "transformCamera");

	// Register the function callback for the createCube action
	inputActionManager.addInputActionCallback("createCube", this, &SampleDotSceneGameTask::createCube);
	// Register the function callback for the printScene action
	inputActionManager.addInputActionCallback("printScene", this, &SampleDotSceneGameTask::printScene);
	// Register the function callback for the toggleShadows action
	inputActionManager.addInputActionCallback("toggleShadows", this, &SampleDotSceneGameTask::toggleShadows);
	// Register the function callback for the transformCamera action
	inputActionManager.addInputActionCallback("transformCamera", this, &SampleDotSceneGameTask::transformCamera);
	// Register the function callback for the loadDotSceneFile action
	inputActionManager.addInputActionCallback("loadDotSceneFile", this, &SampleDotSceneGameTask::loadDotSceneFile);

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
	camera->setPosition(0, 0, 5);
	camera->lookAt(0, 0, 0);
	camera->setNearClipDistance(1);

	// Setup shadows and lighting
	scene->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	//light = scene->createLight("Light1");
	//light->setType(Ogre::Light::LT_POINT);
	//light->setPosition(-100, 100, 100);
	//light->setDiffuseColour(1.0, 1.0, 1.0);
	//light->setSpecularColour(1.0, 1.0, 1.0);

	// Set gravity and add a floor
	scene->setGravity(Ogre::Vector3(0, -9.81, 0));
	//scene->addFloor(-15);

	// Set up collision callbacks
	Myoushu::CollisionManager::getSingleton().setActorGroupsCollidable(scene, "Weapons", "Weapons", Myoushu::CollisionManager::CP_NOTIFY_ON_START_TOUCH, false);
	Myoushu::CollisionManager::getSingleton().setGlobalStartTouchCallback(new Myoushu::CollisionClassCallback<SampleDotSceneGameTask>(this, &SampleDotSceneGameTask::startTouch));
	Myoushu::CollisionManager::getSingleton().setGlobalEndTouchCallback(new Myoushu::CollisionClassCallback<SampleDotSceneGameTask>(this, &SampleDotSceneGameTask::endTouch));
	Myoushu::CollisionManager::getSingleton().setGlobalTouchCallback(new Myoushu::CollisionClassCallback<SampleDotSceneGameTask>(this, &SampleDotSceneGameTask::touch));

	// Create the OgreDotScene importer
	mpDotSceneImporter = Myoushu::ContentImporterManager::getSingleton().make("Myoushu::MyoushuDotSceneProcessorImpl", "MyoushuDotSceneImporter");
	mpDotSceneImporter->initialize();

	// Call GameTask init method
	GameTask::init();
}

void SampleDotSceneGameTask::startTouch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor)
{
	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "startTouch: " << pFirstActor->getName() << " " << pSecondActor->getName());
}

void SampleDotSceneGameTask::endTouch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor)
{
	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "endTouch: " << pFirstActor->getName() << " " << pSecondActor->getName());
}

void SampleDotSceneGameTask::touch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor)
{
	LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "touch: " << pFirstActor->getName() << " " << pSecondActor->getName());
}

void SampleDotSceneGameTask::toggleShadows(Myoushu::InputMessage *message)
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

void SampleDotSceneGameTask::transformCamera(Myoushu::InputMessage *inputMessage)
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

void SampleDotSceneGameTask::setupSceneNodeAnimations()
{	
	// Load scene node animations
	Ogre::AnimationStateIterator iter = scene->getAnimationStateIterator();

	// Add all animations to animations window
	while (iter.hasMoreElements())
	{
		Ogre::AnimationState *aState = iter.getNext();
		addAnimationToWindow(aState);
	}
}

void SampleDotSceneGameTask::addAnimationToWindow(Ogre::AnimationState *aState)
{
	MyGUI::ButtonPtr checkbox;
	std::ostringstream oStringStream;

	if (!aState)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "addAnimationToWindow: aState is NULL.");
		return;
	}

	if (!gui)
	{
		gui = MyGUI::Gui::getInstancePtr();
	}

	// Acquire a lock on the MyGUI::Gui singleton
	Myoushu::GlobalLocks::rwLockMyGUI.writeLock();

	if (!animationsWindow)
	{
		// Get the animations window widget
		animationsWindow = gui->findWidget<MyGUI::Window>("AnimationsWindow");
	}

	// Create check box widget
	oStringStream << "CheckBox" << numAnimations;
	numAnimations++;
	checkbox = animationsWindow->createWidgetReal<MyGUI::Button>("CheckBox", 0.1f, (float) numAnimations * 0.15f, 0.8f, 0.1f, MyGUI::ALIGN_VCENTER, oStringStream.str());
	checkbox->setCaption(aState->getAnimationName());
	checkbox->setEnabled(true);
	checkbox->show();
	// Create callback for mouse clicks
	checkbox->eventMouseButtonClick = MyGUI::newDelegate(this, &SampleDotSceneGameTask::animationCheckBoxClicked);

	Myoushu::GlobalLocks::rwLockMyGUI.unlock();
}

void SampleDotSceneGameTask::animationCheckBoxClicked(MyGUI::WidgetPtr widget)
{
	MyGUI::ButtonPtr button;
	Ogre::AnimationState *aState;

	button = dynamic_cast<MyGUI::ButtonPtr>(widget);

	if (!button)
	{
		return;
	}

	aState = scene->getAnimationState(button->getCaption());

	if (button->getButtonPressed())
	{
		button->setButtonPressed(false);

		Myoushu::AnimationManager::getSingleton().stopAnimation(aState);
	}
	else
	{
		button->setButtonPressed(true);
		Myoushu::AnimationManager::getSingleton().playAnimation(aState, true);
	}
}

void SampleDotSceneGameTask::loadDotSceneFile(Myoushu::InputMessage *message)
{
	if (!mpDotSceneImporter)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "The OgreDotScene importer instance doesn't exist!");
		return;
	}

	if (!message)
	{
		LOG(Myoushu::EngineLog::LM_ERROR, "InputMessage is NULL.");
	}

	if (message->getDeviceAction() == Myoushu::InputDeviceMessage::DA_PRESS)
	{
		MyGUI::Edit *pEditBox;
		
		if (!gui)
		{
			gui = MyGUI::Gui::getInstancePtr();
		}

		// Acquire a lock on the MyGUI::Gui singleton
		Myoushu::GlobalLocks::rwLockMyGUI.readLock();

		// Get the animations window widget
		pEditBox = gui->findWidget<MyGUI::Edit>("fileEditBox");

		Myoushu::GlobalLocks::rwLockMyGUI.unlock();

		mpDotSceneImporter->importContent(scene, pEditBox->getOnlyText(), "scripts", NULL, "");

		// Loop through game objects and print some details to the console
		for (Myoushu::GameObjectFactory::ConstIterator iter = Myoushu::GameObjectFactory::getSingleton().begin(); iter != Myoushu::GameObjectFactory::getSingleton().end(); ++iter)
		{
			const Myoushu::GameObject *pGameObject = iter->second;

			LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "GameObject: Name: " << iter->first << " properties:");

			for (Myoushu::KeyValueProperties::KeyValueMapConstIterator iter2 = pGameObject->getProperties().getBeginConstIterator(); iter2 != pGameObject->getProperties().getEndConstIterator(); ++iter2)
			{
				const Myoushu::Value *pVal = iter2->second;

				LOG(Myoushu::EngineLog::LM_INFO_APPLICATION, "	Key: " << iter2->first << " Value: " << pVal->getValue().mInt);
			}
		}

		setupSceneNodeAnimations();

	}
}

void SampleDotSceneGameTask::createCube(Myoushu::InputMessage *inputMessage)
{
	NxOgre::Pose pose;
	NxOgre::ActorParams actorParams;
	NxOgre::ShapeParams shapeParams;

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

	actorParams.mGroupAsName = "Weapons";
	actorParams.mMass = 100;

	Ogre::Vector3 direction(camera->getDirection());
	direction.normalise();

	shapeParams.setToDefault();
	actorParams.mLinearVelocity = NxVec3(direction.x, direction.y, direction.z) * SHOOT_SPEED;
	actorParams.mNodeScale = Ogre::Vector3(0.25f, 0.25f, 0.25f);
	pose = NxOgre::Pose(camera->getPosition(), camera->getOrientation());
	gameObjectFactory.makeBody("Weaponised_Cube", "cube.mesh", scene, new NxOgre::CubeShape(0.25f * 2.0f, shapeParams), pose, actorParams);
}

void SampleDotSceneGameTask::printScene(Myoushu::InputMessage *message)
{
	if (message->getDeviceAction() == Myoushu::InputDeviceMessage::DA_RELEASE)
	{
		printSceneNode(scene->getRootSceneNode());
	}
}

void SampleDotSceneGameTask::printSceneNode(Ogre::Node *node)
{
	std::cout << "Name: " << node->getName() << std::endl;
	Ogre::Node::ChildNodeIterator iter = node->getChildIterator();

	while (iter.hasMoreElements())
	{
		Ogre::SceneNode::ObjectIterator objIter = static_cast<Ogre::SceneNode*>(node)->getAttachedObjectIterator();
		while (objIter.hasMoreElements())
		{
			std::cout << "\tEntity name: " << objIter.getNext()->getName() << std::endl;
		}

		printSceneNode(iter.getNext());
	}
}

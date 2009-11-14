/**
 * @file SampleDotSceneGameTask.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SAMPLE_COLLADA_GAME_TASK_H
#define SAMPLE_COLLADA_GAME_TASK_H

#include <string>
#include <list>

#include "MyGUI.h"

#include "ContentImporter.h"
#include "GameTask.h"
#include "InputMessage.h"

/** The GameTask for the SampleDotScene application of the Myoushu engine. */
class SampleDotSceneGameTask : public Myoushu::GameTask
{
	public:
		/**
		 * Constructor.
		 * @param priority The priority of the task.
		 * @param name The name of the task instance.
		 * @param iterationLimit If the task misses its executionInterval, iterationLimit controls how many
		 *						 extra executions of the Task will be performed to catch up. Task that are
		 *						 slow and computationally expensive should not set this limit higher than one
		 *						 since it will slow the engine down if it cannot consistently run the task at
		 *						 its intervals. Higher iterationLimits are meant for lighter
		 *						 but important tasks, like game logic updates.
		 */
		SampleDotSceneGameTask(int priority, const std::string& name, double executionInterval = 0.0, unsigned int iterationLimit = 1);

		/** Destructor */
		~SampleDotSceneGameTask();

		/**
		 * Initializes the Task. It first calls GameTask::init() and then
		 * proceeds to do some extra initializtion.
		 */
		void init() throw (Myoushu::Exception);

		void startTouch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor);

		void endTouch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor);

		void touch(Myoushu::GameActorObject *pFirstActor, Myoushu::GameActorObject *pSecondActor);

		/** Toggle shadows */
		void toggleShadows(Myoushu::InputMessage *message);

		/**
		 * Function that rotates, yaws and pitches and zooms the camera.
		 */
		void transformCamera(Myoushu::InputMessage *inputMessage);

		/**
		 * Imports a dotscene file
		 */
		void loadDotSceneFile(Myoushu::InputMessage *message);

		/** Sets up SceneNode animations. */
		void setupSceneNodeAnimations();

		/** 
		 * Add animation to Animations window 
		 * @param aState The Ogre::AnimationState representing the animation
		 *				 to add to the Animations window.
		 */
		void addAnimationToWindow(Ogre::AnimationState *aState);

		/**
		 * Called when the user clicks on a checkbox in the Animations
		 * window.
		 * @param widget The checkbox that was clicked on.
		 */
		void animationCheckBoxClicked(MyGUI::WidgetPtr widget);

		/** 
		 * Creates a cube. 
		 * @param inputMessage InputMessage instance created when the user pressed the button bound
		 *					   to the createCube action.
		 */
		void createCube(Myoushu::InputMessage *inputMessage);

		void printScene(Myoushu::InputMessage *message);

		void printSceneNode(Ogre::Node *node);

	private:
		/** The scene manager */
		Myoushu::Scene *scene;	
		/** The camera */
		Ogre::Camera *camera;
		/** The OgreDotSceneContentImporter instance */
		Myoushu::ContentImporter *mpDotSceneImporter;
		/** Mouse X coordinate */
		int x;
		/** Mouse Y coordinate */
		int y;
		/** Mouse Z coordinate */
		int z;
		/** MyGUI::Gui singleton */
		MyGUI::Gui *gui;
		/** Animations window */
		MyGUI::WindowPtr animationsWindow;
		/** Number of animations in window */
		unsigned int numAnimations;

};

#endif


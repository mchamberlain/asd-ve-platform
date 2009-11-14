/**
 * @file SampleCharacterGameTask.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SAMPLE_CHARACTER_GAME_TASK_H
#define SAMPLE_CHARACTER_GAME_TASK_H

#define PYRAMID_CUBE_BASE_CNT 31
#define PILLAR_CUBE_CNT 30
#define CUBE_HEIGHT 2

#include <string>

#include "GameTask.h"
#include "InputMessage.h"
#include "GameCharacterObject.h"
#include "GameCharacterObjectController.h"

/** The GameTask for the SampleCharacter application of the Myoushu engine. */
class SampleCharacterGameTask : public Myoushu::GameTask
{
	public:
		/**
		 * Constructor.
		 * @param priority The priority of the task.
		 * @param name The name of the task instance.
		 * @param executionInterval The amount of time, in seconds, between executions of this Task. 
		 *							To execute in every frame use 0.0. Defaults to 0.0. To execute twice
		 *							a second use 0.5 for instance.
		 * @param iterationLimit If the task misses its executionInterval, iterationLimit controls how many
		 *						 extra executions of the Task will be performed to catch up. Task that are
		 *						 slow and computationally expensive should not set this limit higher than one
		 *						 since it will slow the engine down if it cannot consistently run the task at
		 *						 its intervals. Higher iterationLimits are meant for lighter
		 *						 but important tasks, like game logic updates.
		 */
		SampleCharacterGameTask(int priority, const std::string& name, double executionInterval = 0.0, unsigned int iterationLimit = 1);

		/** Destructor */
		~SampleCharacterGameTask();

		/**
		 * Initializes the Task. It first calls GameTask::init() and then
		 * proceeds to do some extra initializtion.
		 */
		void init() throw (Myoushu::Exception);

		/** Collision callback function for actor-character collisions. */
		void actorCharacterCollision(Myoushu::GameCharacterObject *pCharacter, Myoushu::GameActorObject *pActor, Myoushu::CollisionManager::CollisionProperties cProps);

		/** Toggle shadows */
		void toggleShadows(Myoushu::InputMessage *message);

		/**
		 * Function that rotates, yaws and pitches and zooms the camera.
		 */
		void transformCamera(Myoushu::InputMessage *inputMessage);

		/** 
		 * Moves the character, based on the input action. 
		 * @param inputMessage InputMessage instance created when the user pressed the button bound
		 *					   to the createCube action.
		 */
		void moveCharacter(Myoushu::InputMessage *inputMessage);

		void toggleView(Myoushu::InputMessage *message);

		void createCube(Myoushu::InputMessage *inputMessage);

		/**
		 * Execute one iteration of the task.
		 * @param timeDelta The time since last execution in microseconds.
		 */
		void execute(unsigned long timeDelta);

	private:
		/** The scene manager */
		Myoushu::Scene *scene;	
		/** The camera */
		Ogre::Camera *camera;
		/** The character. */
		Myoushu::GameCharacterObject *character;
		/** The character controller */
		Myoushu::GameCharacterObjectController *controller;
		/** Mouse X coordinate */
		int x;
		/** Mouse Y coordinate */
		int y;
		/** Mouse Z coordinate */
		int z;

		/** Create the character. */
		void createCharacter();
};

#endif


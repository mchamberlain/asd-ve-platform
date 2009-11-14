/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morné Chamberlain & Stellenbosch University

The ASD Assist VE Platform is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License (with the added restriction
that this work and any derivative works may only be used for non-commercial purposes)
as published by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The ASD Assist VE Platform is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file GameObjectFactory.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "Ogre.h"
#include "NxOgre.h"

#include "Singleton.h"
#include "NamedObjectFactory.h"
#include "GameObject.h"
#include "GameActorObject.h"
#include "GameBodyObject.h"
#include "GameCharacterObject.h"
#include "Exception.h"

namespace Myoushu
{
	class MYOUSHU_API GameObjectFactory : public NamedObjectFactory<GameObject>, public Ogre::Singleton<GameObjectFactory>
	{
		public:
			/** Constructor */
			GameObjectFactory();

			/** Destructor */
			~GameObjectFactory();

			/**
			 * Creates a GameObject instance with the specified name.
			 * @param name The name for the instance that is to be created.
			 * @return A GameObject instance.
			 */
			virtual GameObject* make(const std::string& name);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual GameObject* make(const std::string& className, const std::string& name) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param scene The Scene to create the object in.
			 * @param name The name of the object.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param initialPose The initial pose of the object. This is basically the initial position and orientation of the object.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameActorObject* makeActor(const Ogre::String& name, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param meshName The mesh to use as visual representation, must end in .mesh.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param initialPose The initial NxOgre::Pose of the body.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, const Ogre::String& meshName, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param meshName The mesh to use as visual representation, must end in .mesh.
			 * @param sceneNode An existing scene node to use for this GameBodyObject.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param entity An existing entity to use.
			 * @param sceneNode An existing scene node to use for this GameBodyObject.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param entity An existing entity to use.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape An approximate shape to use for collision detection.
			 * @param initialPose The initial NxOgre::Pose of the body.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, Ogre::Entity *entity, Scene *scene, NxOgre::ShapeBlueprint *collisionShape, const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param meshName The mesh to use as visual representation, must end in .mesh.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape A .nxs file to use as a convex collision shape.
			 * @param shapeParams Parameters specifying the shape's properties.
			 * @param initialPose The initial NxOgre::Pose of the body.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, const Ogre::String& meshName, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams = NxOgre::ShapeParams(), const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param meshName The mesh to use as visual representation, must end in .mesh.
			 * @param sceneNode An existing scene node to use for this GameBodyObject.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape A .nxs file to use as a convex collision shape.
			 * @param shapeParams Parameters specifying the shape's properties.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, const Ogre::String& meshName, Ogre::SceneNode *sceneNode, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams = NxOgre::ShapeParams(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param entity An existing entity to use.
			 * @param sceneNode An existing scene node to use for this GameBodyObject.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape A .nxs file to use as a convex collision shape.
			 * @param shapeParams Parameters specifying the shape's properties.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, Ogre::SceneNode *sceneNode, Ogre::Entity *entity, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams = NxOgre::ShapeParams(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameObject with physical properties.
			 * @param name The name of the object.
			 * @param entity An existing entity to use.
			 * @param scene The Scene to create the object in.
			 * @param collisionShape A .nxs file to use as a convex collision shape.
			 * @param shapeParams Parameters specifying the shape's properties.
			 * @param initialPose The initial NxOgre::Pose of the body.
			 * @param actorParams Parameters specifying the objects physical properties.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameBodyObject* makeBody(const Ogre::String& name, Ogre::Entity *entity, Scene *scene, const Ogre::String& collisionShapeFileName, const NxOgre::ShapeParams shapeParams = NxOgre::ShapeParams(), const NxOgre::Pose& initialPose = NxOgre::Pose(), const NxOgre::ActorParams& actorParams = NxOgre::ActorParams()) throw (Exception);

			/**
			 * Creates a GameCharacterObject.
			 * @param name The name of the character.
			 * @param meshName The name of the mesh to use for the character. The mesh is loaded via Ogre's resource manager.
			 * @param skeletonMeshName The name of the skeleton mesh for the character.
			 * @param scene The Scene to create the character in.
			 * @param pose The initial position and orientation for the character.
			 * @param params The parameters to create the character with.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 */
			GameCharacterObject* makeCharacter(const Ogre::String& name, const Ogre::String& meshName, const Ogre::String& skeletonMeshName, Scene* scene
				, const NxOgre::Pose& pose, const NxOgre::CharacterParams& params) throw (Exception);

			/**
			 * Destroy the specified GameObject instance and remove it from the factory.
			 * @throws Exception::E_NULL_POINTER if gameObject is NULL.
			 */
			void destroy(GameObject *gameObject) throw (Exception);

			/**
			 * Destroys all GameObject instances that are in the specified Scene.
			 * @param pScene The Scene instance in question.
			 * @throws Exception::E_NULL_POINTER if pScene is NULL.
			 */
			virtual void destroyAllFromScene(Scene *pScene) throw (Exception);

		protected:
			/**
			 * This method checks whether the specified actor group exists in the specified scene. If acctorGroupName is not "", then
			 * only actorGroupName is used for the checking the existence of the group. If actorGroupName is "" then actorGroupID is used
			 * to check whether the group exists. If the group does not exist, the group is created if actorGroupName is not "". If actorGroupID
			 * is specified, but the group does not exist, we cannot create a new group ensuring that it will have actorGroupID as ID. In such a
			 * case false is returned.
			 * @param pScene The Scene instance to use to check for the actor group.
			 * @param actorGroupID The ID of the group to ensure the existence of.
			 * @param actorGroupName The name of the actor group to ensure the existence of. If actorGroupName is "" then this function
			 *						 does nothing.
			 * @return true if the specified group exists or could be created, false otherwise.
			 */
			bool ensureActorGroupExists(Scene *pScene, NxActorGroup actorGroupID, const Ogre::String& actorGroupName) const;

			/**
			 * Creates a convex collision shape instance from a collision shape file.
			 * @param fileName The name of the file.
			 * @param resourceGroup The Ogre resource group that contains the file.
			 * @return The NxOgre::ConvexShape instance if the shape was successfully loaded, NULL otherwise.
			 */
			NxOgre::ConvexShape* GameObjectFactory::getConvexShapeFromFile(const Ogre::String& fileName, const Ogre::String& resourceGroup = "", const NxOgre::ShapeParams shapeParams = NxOgre::ShapeParams());
	};
} // Myoushu

#endif

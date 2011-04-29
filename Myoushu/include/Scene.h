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
 * @file Scene.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef SCENE_H
#define SCENE_H

#include "Ogre.h"
#include "NxOgre.h"
#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "Platform.h"
#include "Exception.h"
#include "NamedObject.h"
#include "NamedInstance.h"

namespace Myoushu
{
	// Forward declaration of GameObject
	class GameObject;

	/**
	 * A small memory managed wrapper class encapsulating a NxOgre::Scene instance and a Ogre::SceneManager instance.
	 */
	class MYOUSHU_API Scene : public NamedObject<Scene>, public NamedInstance, public Poco::RefCountedObject
	{
		public:
			/**
			 * Constructor. Wrap the two specified instances.
			 * @param nxScene The NxOgre::Scene to wrap.
			 * @param sceneManager The Ogre::SceneManager instance to wrap.
			 */
			Scene(NxOgre::Scene *nxScene, Ogre::SceneManager *sceneManager) throw (Exception);

			/**
			 * Constructor. Create a NxOgre::Scene and use an existing Ogre::SceneManager.
			 * @param name The name that the instances should have.
			 * @param sceneTypeName The type of Ogre::SceneManager to create.
			 * @param world The NxOgre::World instance to use to create the NxOgre::Scene.
			 *				(for the Ogre::SceneManager the Ogre::Root singleton is used).
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 * @param sceneManager The existing Ogre::SceneManager instance to use.
			 */
			Scene(const Ogre::String& name, NxOgre::World *world, NxOgre::SceneParams& sceneParams, Ogre::SceneManager *sceneManager) throw (Exception);

			/**
			 * Constructor. Create NxOgre::Scene and Ogre::SceneManager instances with the
			 * specified parameters.
			 * @param name The name that the instances should have.
			 * @param sceneTypeName The type of Ogre::SceneManager to create.
			 * @param world The NxOgre::World instance to use to create the NxOgre::Scene.
			 *				(for the Ogre::SceneManager the Ogre::Root singleton is used).
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 */
			Scene(const Ogre::String& name, const Ogre::String& sceneTypeName, NxOgre::World *world, NxOgre::SceneParams& sceneParams) throw (Exception);

			/**
			 * Constructor. Create NxOgre::Scene and Ogre::SceneManager instances with the
			 * specified parameters.
			 * @param name The name that the instances should have.
			 * @param sceneTypeMask A type mask indicating the type of Ogre::SceneManager to create.
			 * @param world The NxOgre::World instance to use to create the NxOgre::Scene.
			 *				(for the Ogre::SceneManager the Ogre::Root singleton is used).
			 * @param sceneParams The scene parameters for the NxOgre::Scene instance.
			 */
			Scene(const Ogre::String& name, Ogre::SceneTypeMask sceneTypeMask, NxOgre::World *world, NxOgre::SceneParams& sceneParams) throw (Exception);

			/**
			 * Destructor.
			 * Destroys the two encapsulated scene instances if they were created in the constructor and not
			 * just passed as parameters.
			 */
			virtual ~Scene();

			CLASS_NAME_FUNCTIONS(Scene);

			/**
			 * Acquire a lock on the Ogre::SceneManager instance encapsulated in this instance.
			 * This method must be called before the {@code getOgreSceneManager()} is called
			 * and the {@code releaseLockOnOgreSceneManager()} must be called when the lock
			 * is no longer required.
			 * @param write True if the lock should be a write lock.
			 */
			void acquireLockOnOgreSceneManager(bool write = false) const;

			/**
			 * Acquire a lock on the NxOgre::Scene instance encapsulated in this instance.
			 * This method must be called before the {@code getNxOgreScene()} is called
			 * and the {@code releaseLockOnNxOgreScene()} must be called when the lock
			 * is no longer required.
			 * @param write True if the lock should be a write lock.
			 */
			void acquireLockOnNxOgreScene(bool write = false) const;

			/** Release a lock previously acquired by {@code acquireLockOnOgreSceneManager()} */
			void releaseLockOnOgreSceneManager() const;

			/** Release a lock previously acquired by {@code acquireLockOnNxOgreScene()} */
			void releaseLockOnNxOgreScene() const;

			/**
			 * Getter for the NxOgre::Scene instance.
			 * @return The const NxOgre::Scene instance.
			 */
			const NxOgre::Scene* getNxOgreScene() const;

			/**
			 * Getter for the Ogre::SceneManager instance.
			 * @return The const Ogre::SceneManager instance.
			 */
			const Ogre::SceneManager* getOgreSceneManager() const;

			/**
			 * Getter for the NxOgre::Scene instance.
			 * @return The const NxOgre::Scene instance.
			 */
			NxOgre::Scene* getNxOgreScene();

			/**
			 * Getter for the Ogre::SceneManager instance.
			 * @return The const Ogre::SceneManager instance.
			 */
			Ogre::SceneManager* getOgreSceneManager();

			/**
			 * Gets the GameObjects that intersect a ray cast.
			 * @param position The position to cast the ray from.
			 * @param direction The direction to cast the ray in.
			 * @param range The maximum distance along the ray to check for GameObject intersections.
			 * @param filter A filter for the type of objects to return. Defaults to NxOgre::AF_NONE which  means all types are returned.
			 *				 Other possibilties are NxOgre::AF_STATIC_SHAPES and NxOgre::AF_DYNAMIC_SHAPES.
			 * @return A std::list of GameObject instance pointers, unsorted. The list is empty if no objects intersect the ray.
			 */
			std::list<GameObject*> getGameObjectsFromRaycast(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::Real range, NxOgre::RayCaster::ActorFilter filter = NxOgre::RayCaster::AF_NONE);

			/**
			 * Gets the closest GameObject that intersects a ray cast.
			 * @param position The position to cast the ray from.
			 * @param direction The direction to cast the ray in.
			 * @param range The maximum distance along the ray to check for GameObject intersections.
			 * @param filter A filter for the type of object to return. Defaults to NxOgre::AF_NONE which  means all types are returned.
			 *				 Other possibilties are NxOgre::AF_STATIC_SHAPES and NxOgre::AF_DYNAMIC_SHAPES.
			 * @return The closest GameObject instance along the ray, NULL if no objects intersect the ray.
			 */
			GameObject* getClosestGameObjectFromRaycast(Ogre::Vector3 position, Ogre::Vector3 direction, Ogre::Real range, NxOgre::RayCaster::ActorFilter filter = NxOgre::RayCaster::AF_NONE);

			/**
			 * Gets all GameObject instances that are in the camera view.
			 * @param camera The camera to use.
			 * @param gameObjectList The list to which to add the GameObjects that are in the camera's view frustum.
			 */
			void getGameObjectsInCameraView(Ogre::Camera& camera, std::list<GameObject*> &gameObjectList);

			/**
			 * Equality operator. Scenes created with the SceneFactory have unique names, so 
			 * two Scenes are considered equal if they have the same name.
			 * @param otherScene The Scene instance to test equality with.
			 */
			bool operator==(const Scene& otherScene);

			//********** OGRE::SCENEMANAGER METHODS ***********//

			/** Retrieve the type name of this scene manager.
			@remarks
				This method has to be implemented by subclasses. It should
				return the type name of this SceneManager which agrees with 
				the type name of the SceneManagerFactory which created it.
			*/
			virtual const Ogre::String& getTypeName(void) const;

			/** Creates a camera to be managed by this scene manager.
				@remarks
					This camera must be added to the scene at a later time using
					the attachObject method of the SceneNode class.
				@param
					name Name to give the new camera.
			*/
			virtual Ogre::Camera* createCamera(const Ogre::String& name);

			/** Retrieves a pointer to the named camera.
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::Camera* getCamera(const Ogre::String& name) const;

			/** Returns whether a camera with the given name exists.
			*/
			virtual bool hasCamera(const Ogre::String& name) const;

			/** Removes a camera from the scene.
				@remarks
					This method removes a previously added camera from the scene.
					The camera is deleted so the caller must ensure no references
					to it's previous instance (e.g. in a SceneNode) are used.
				@param
					cam Pointer to the camera to remove
			*/
			virtual void destroyCamera(Ogre::Camera *cam);

			/** Removes a camera from the scene.
				@remarks
					This method removes an camera from the scene based on the
					camera's name rather than a pointer.
			*/
			virtual void destroyCamera(const Ogre::String& name);

			/** Removes (and destroys) all cameras from the scene.
				@remarks
					Some cameras are internal created to dealing with texture shadow,
					their aren't supposed to destroy outside. So, while you are using
					texture shadow, don't call this method, or you can set the shadow
					technique other than texture-based, which will destroy all internal
					created shadow cameras and textures.
			*/
			virtual void destroyAllCameras(void);

			/** Creates a light for use in the scene.
				@remarks
					Lights can either be in a fixed position and independent of the
					scene graph, or they can be attached to SceneNodes so they derive
					their position from the parent node. Either way, they are created
					using this method so that the SceneManager manages their
					existence.
				@param
					name The name of the new light, to identify it later.
			*/
			virtual Ogre::Light* createLight(const Ogre::String& name);

			/** Returns a pointer to the named Light which has previously been added to the scene.
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::Light* getLight(const Ogre::String& name) const;

			/** Returns whether a light with the given name exists.
			*/
			virtual bool hasLight(const Ogre::String& name) const;

			/** Removes the named light from the scene and destroys it.
				@remarks
					Any pointers held to this light after calling this method will be invalid.
			*/
			virtual void destroyLight(const Ogre::String& name);

			/** Removes the light from the scene and destroys it based on a pointer.
				@remarks
					Any pointers held to this light after calling this method will be invalid.
			*/
			virtual void destroyLight(Ogre::Light* light);
			/** Removes and destroys all lights in the scene.
			*/
			virtual void destroyAllLights(void);

			/** Advance method to increase the lights dirty counter due lights changed.
			@remarks
				Scene manager tracking lights that affecting the frustum, if changes
				detected (the changes includes light list itself and the light's position
				and attenuation range), then increase the lights dirty counter.
			@par
				For some reason, you can call this method to force whole scene objects
				re-populate their light list. But near in mind, call to this method
				will harm performance, so should avoid if possible.
			*/
			virtual void _notifyLightsDirty(void);

			/** Advance method to gets the lights dirty counter.
			@remarks
				Scene manager tracking lights that affecting the frustum, if changes
				detected (the changes includes light list itself and the light's position
				and attenuation range), then increase the lights dirty counter.
			@par
				When implementing customise lights finding algorithm relied on either
				SceneManager::_getLightsAffectingFrustum or SceneManager::_populateLightList,
				might check this value for sure that the light list are really need to
				re-populate, otherwise, returns cached light list (if exists) for better
				performance.
			*/
			Ogre::ulong _getLightsDirtyCounter(void) const;

			/** Get the list of lights which could be affecting the frustum.
			@remarks
				Note that default implementation of this method returns a cached light list,
				which is populated when rendering the scene. So by default the list of lights 
				is only available during scene rendering.
			*/
			virtual const Ogre::LightList& _getLightsAffectingFrustum(void) const;

			/** Populate a light list with an ordered set of the lights which are closest
			to the position specified.
			@remarks
				Note that since directional lights have no position, they are always considered
				closer than any point lights and as such will always take precedence. 
			@par
				Subclasses of the default SceneManager may wish to take into account other issues
				such as possible visibility of the light if that information is included in their
				data structures. This basic scenemanager simply orders by distance, eliminating 
				those lights which are out of range or could not be affecting the frustum (i.e.
				only the lights returned by SceneManager::_getLightsAffectingFrustum are take into
				account).
			@par
				The number of items in the list max exceed the maximum number of lights supported
				by the renderer, but the extraneous ones will never be used. In fact the limit will
				be imposed by Pass::getMaxSimultaneousLights.
			@param position The position at which to evaluate the list of lights
			@param radius The bounding radius to test
			@param destList List to be populated with ordered set of lights; will be cleared by 
				this method before population.
			*/
			virtual void _populateLightList(const Ogre::Vector3& position, Ogre::Real radius, Ogre::LightList& destList);


			/** Creates an instance of a SceneNode.
				@remarks
					Note that this does not add the SceneNode to the scene hierarchy.
					This method is for convenience, since it allows an instance to
					be created for which the SceneManager is responsible for
					allocating and releasing memory, which is convenient in complex
					scenes.
				@par
					To include the returned SceneNode in the scene, use the addChild
					method of the SceneNode which is to be it's parent.
				@par
					Note that this method takes no parameters, and the node created is unnamed (it is
					actually given a generated name, which you can retrieve if you want).
					If you wish to create a node with a specific name, call the alternative method
					which takes a name parameter.
			*/
			virtual Ogre::SceneNode* createSceneNode(void);

			/** Creates an instance of a SceneNode with a given name.
				@remarks
					Note that this does not add the SceneNode to the scene hierarchy.
					This method is for convenience, since it allows an instance to
					be created for which the SceneManager is responsible for
					allocating and releasing memory, which is convenient in complex
					scenes.
				@par
					To include the returned SceneNode in the scene, use the addChild
					method of the SceneNode which is to be it's parent.
				@par
					Note that this method takes a name parameter, which makes the node easier to
					retrieve directly again later.
			*/
			virtual Ogre::SceneNode* createSceneNode(const Ogre::String& name);

			/** Destroys a SceneNode with a given name.
			@remarks
				This allows you to physically delete an individual SceneNode if you want to.
				Note that this is not normally recommended, it's better to allow SceneManager
				to delete the nodes when the scene is cleared.
			*/
			virtual void destroySceneNode(const Ogre::String& name);

			/** Gets the SceneNode at the root of the scene hierarchy.
				@remarks
					The entire scene is held as a hierarchy of nodes, which
					allows things like relative transforms, general changes in
					rendering state etc (See the SceneNode class for more info).
					In this basic SceneManager class, the application using
					Ogre is free to structure this hierarchy however it likes,
					since it has no real significance apart from making transforms
					relative to each node (more specialised subclasses will
					provide utility methods for building specific node structures
					e.g. loading a BSP tree).
				@par
					However, in all cases there is only ever one root node of
					the hierarchy, and this method returns a pointer to it.
			*/
			virtual Ogre::SceneNode* getRootSceneNode(void) const;

			/** Retrieves a named SceneNode from the scene graph.
			@remarks
				If you chose to name a SceneNode as you created it, or if you
				happened to make a note of the generated name, you can look it
				up wherever it is in the scene graph using this method.
				@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::SceneNode* getSceneNode(const Ogre::String& name) const;

			/** Returns whether a scene node with the given name exists.
			*/
			virtual bool hasSceneNode(const Ogre::String& name) const;


			/** Create an Entity (instance of a discrete mesh).
				@param
					entityName The name to be given to the entity (must be unique).
				@param
					meshName The name of the Mesh it is to be based on (e.g. 'knot.oof'). The
					mesh will be loaded if it is not already.
			*/
			virtual Ogre::Entity* createEntity(const Ogre::String& entityName, const Ogre::String& meshName);

			/** Create an Entity (instance of a discrete mesh) from a range of prefab shapes.
				@param
					entityName The name to be given to the entity (must be unique).
				@param
					ptype The prefab type.
			*/
			virtual Ogre::Entity* createEntity(const Ogre::String& entityName, Ogre::SceneManager::PrefabType ptype);
			/** Retrieves a pointer to the named Entity. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::Entity* getEntity(const Ogre::String& name) const;
			/** Returns whether an entity with the given name exists.
			*/
			virtual bool hasEntity(const Ogre::String& name) const;

			/** Removes & destroys an Entity from the SceneManager.
				@warning
					Must only be done if the Entity is not attached
					to a SceneNode. It may be safer to wait to clear the whole
					scene if you are unsure use clearScene.
				@see
					SceneManager::clearScene
			*/
			virtual void destroyEntity(Ogre::Entity* ent);

			/** Removes & destroys an Entity from the SceneManager by name.
				@warning
					Must only be done if the Entity is not attached
					to a SceneNode. It may be safer to wait to clear the whole
					scene if you are unsure use clearScene.
				@see
					SceneManager::clearScene
			*/
			virtual void destroyEntity(const Ogre::String& name);

			/** Removes & destroys all Entities.
				@warning
					Again, use caution since no Entity must be referred to
					elsewhere e.g. attached to a SceneNode otherwise a crash
					is likely. Use clearScene if you are unsure (it clears SceneNode
					entries too.)
				@see
					SceneManager::clearScene
			*/
			virtual void destroyAllEntities(void);

			/** Create a ManualObject, an object which you populate with geometry
				manually through a GL immediate-mode style interface.
			@param
				name The name to be given to the object (must be unique).
			*/
			virtual Ogre::ManualObject* createManualObject(const Ogre::String& name);
			/** Retrieves a pointer to the named ManualObject. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::ManualObject* getManualObject(const Ogre::String& name) const;
			/** Returns whether a manual object with the given name exists.
			*/
			virtual bool hasManualObject(const Ogre::String& name) const;

			/** Removes & destroys a ManualObject from the SceneManager.
			*/
			virtual void destroyManualObject(Ogre::ManualObject* obj);
			/** Removes & destroys a ManualObject from the SceneManager.
			*/
			virtual void destroyManualObject(const Ogre::String& name);
			/** Removes & destroys all ManualObjects from the SceneManager.
			*/
			virtual void destroyAllManualObjects(void);
			/** Create a BillboardChain, an object which you can use to render
				a linked chain of billboards.
			@param
				name The name to be given to the object (must be unique).
			*/
			virtual Ogre::BillboardChain* createBillboardChain(const Ogre::String& name);
			/** Retrieves a pointer to the named BillboardChain. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::BillboardChain* getBillboardChain(const Ogre::String& name) const;
			/** Returns whether a billboard chain with the given name exists.
			*/
			virtual bool hasBillboardChain(const Ogre::String& name) const;

			/** Removes & destroys a BillboardChain from the SceneManager.
			*/
			virtual void destroyBillboardChain(Ogre::BillboardChain* obj);
			/** Removes & destroys a BillboardChain from the SceneManager.
			*/
			virtual void destroyBillboardChain(const Ogre::String& name);
			/** Removes & destroys all BillboardChains from the SceneManager.
			*/
			virtual void destroyAllBillboardChains(void);		
			/** Create a RibbonTrail, an object which you can use to render
				a linked chain of billboards which follows one or more nodes.
			@param
				name The name to be given to the object (must be unique).
			*/
			virtual Ogre::RibbonTrail* createRibbonTrail(const Ogre::String& name);
			/** Retrieves a pointer to the named RibbonTrail. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::RibbonTrail* getRibbonTrail(const Ogre::String& name) const;
			/** Returns whether a ribbon trail with the given name exists.
			*/
			virtual bool hasRibbonTrail(const Ogre::String& name) const;

			/** Removes & destroys a RibbonTrail from the SceneManager.
			*/
			virtual void destroyRibbonTrail(Ogre::RibbonTrail* obj);
			/** Removes & destroys a RibbonTrail from the SceneManager.
			*/
			virtual void destroyRibbonTrail(const Ogre::String& name);
			/** Removes & destroys all RibbonTrails from the SceneManager.
			*/
			virtual void destroyAllRibbonTrails(void);		

			/** Creates a particle system based on a template.
			@remarks
				This method creates a new ParticleSystem instance based on the named template
				(defined through ParticleSystemManager::createTemplate) and returns a 
				pointer to the caller. The caller should not delete this object, it will be freed at system shutdown, 
				or can be released earlier using the destroyParticleSystem method.
			@par
				Each system created from a template takes the template's settings at the time of creation, 
				but is completely separate from the template from there on. 
			@par
				Creating a particle system does not make it a part of the scene. As with other MovableObject
				subclasses, a ParticleSystem is not rendered until it is attached to a SceneNode. 
			@par
				This is probably the more useful particle system creation method since it does not require manual
				setup of the system. Note that the initial quota is based on the template but may be changed later.
			@param 
				name The name to give the new particle system instance.
			@param 
				templateName The name of the template to base the new instance on.
			*/
			virtual Ogre::ParticleSystem* createParticleSystem(const Ogre::String& name,
				const Ogre::String& templateName);
			/** Create a blank particle system.
			@remarks
				This method creates a new, blank ParticleSystem instance and returns a pointer to it.
				The caller should not delete this object, it will be freed at system shutdown, or can
				be released earlier using the destroyParticleSystem method.
			@par
				The instance returned from this method won't actually do anything because on creation a
				particle system has no emitters. The caller should manipulate the instance through it's 
				ParticleSystem methods to actually create a real particle effect. 
			@par
				Creating a particle system does not make it a part of the scene. As with other MovableObject
				subclasses, a ParticleSystem is not rendered until it is attached to a SceneNode. 
			@param
				name The name to give the ParticleSystem.
			@param 
				quota The maximum number of particles to allow in this system. 
			@param
				resourceGroup The resource group which will be used to load dependent resources
			*/
			virtual Ogre::ParticleSystem* createParticleSystem(const Ogre::String& name,
				size_t quota = 500, 
				const Ogre::String& resourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			/** Retrieves a pointer to the named ParticleSystem. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::ParticleSystem* getParticleSystem(const Ogre::String& name) const;
			/** Returns whether a particle system with the given name exists.
			*/
			virtual bool hasParticleSystem(const Ogre::String& name) const;

			/** Removes & destroys a ParticleSystem from the SceneManager.
			*/
			virtual void destroyParticleSystem(Ogre::ParticleSystem* obj);
			/** Removes & destroys a ParticleSystem from the SceneManager.
			*/
			virtual void destroyParticleSystem(const Ogre::String& name);
			/** Removes & destroys all ParticleSystems from the SceneManager.
			*/
			virtual void destroyAllParticleSystems(void);		

			/** Empties the entire scene, inluding all SceneNodes, Entities, Lights, 
				BillboardSets etc. Cameras are not deleted at this stage since
				they are still referenced by viewports, which are not destroyed during
				this process.
			*/
			virtual void clearScene(void);

			/** Sets the ambient light level to be used for the scene.
				@remarks
					This sets the colour and intensity of the ambient light in the scene, i.e. the
					light which is 'sourceless' and illuminates all objects equally.
					The colour of an object is affected by a combination of the light in the scene,
					and the amount of light that object reflects (in this case based on the Material::ambient
					property).
				@remarks
					By default the ambient light in the scene is ColourValue::Black, i.e. no ambient light. This
					means that any objects rendered with a Material which has lighting enabled (see Material::setLightingEnabled)
					will not be visible unless you have some dynamic lights in your scene.
			*/
			void setAmbientLight(const Ogre::ColourValue& colour);

			/** Returns the ambient light level to be used for the scene.
			*/
			const Ogre::ColourValue& getAmbientLight(void) const;

			/** Sets the source of the 'world' geometry, i.e. the large, mainly static geometry
				making up the world e.g. rooms, landscape etc.
				@remarks
					Depending on the type of SceneManager (subclasses will be specialised
					for particular world geometry types) you have requested via the Root or
					SceneManagerEnumerator classes, you can pass a filename to this method and it
					will attempt to load the world-level geometry for use. If you try to load
					an inappropriate type of world data an exception will be thrown. The default
					SceneManager cannot handle any sort of world geometry and so will always
					throw an exception. However subclasses like BspSceneManager can load
					particular types of world geometry e.g. "q3dm1.bsp".
			*/
			virtual void setWorldGeometry(const Ogre::String& filename);

			/** Sets the source of the 'world' geometry, i.e. the large, mainly 
				static geometry making up the world e.g. rooms, landscape etc.
				@remarks
					Depending on the type of SceneManager (subclasses will be 
					specialised for particular world geometry types) you have 
					requested via the Root or SceneManagerEnumerator classes, you 
					can pass a stream to this method and it will attempt to load 
					the world-level geometry for use. If the manager can only 
					handle one input format the typeName parameter is not required.
					The stream passed will be read (and it's state updated). 
				@param stream Data stream containing data to load
				@param typeName String identifying the type of world geometry
					contained in the stream - not required if this manager only 
					supports one type of world geometry.
			*/
			virtual void setWorldGeometry(Ogre::DataStreamPtr& stream, 
				const Ogre::String& typeName = Ogre::StringUtil::BLANK);

			/** Estimate the number of loading stages required to load the named
				world geometry. 
			@remarks
				This method should be overridden by SceneManagers that provide
				custom world geometry that can take some time to load. They should
				return from this method a count of the number of stages of progress
				they can report on whilst loading. During real loading (setWorldGeomtry),
				they should call ResourceGroupManager::_notifyWorldGeometryProgress exactly
				that number of times when loading the geometry for real.
			@note 
				The default is to return 0, ie to not report progress. 
			*/
			virtual size_t estimateWorldGeometry(const Ogre::String& filename);

			/** Estimate the number of loading stages required to load the named
				world geometry. 
			@remarks
				Operates just like the version of this method which takes a
				filename, but operates on a stream instead. Note that since the
				stream is updated, you'll need to reset the stream or reopen it
				when it comes to loading it for real.
			@param stream Data stream containing data to load
			@param typeName String identifying the type of world geometry
				contained in the stream - not required if this manager only 
				supports one type of world geometry.
			*/		
			virtual size_t estimateWorldGeometry(Ogre::DataStreamPtr& stream, 
				const Ogre::String& typeName = Ogre::StringUtil::BLANK);
			/** Asks the SceneManager to provide a suggested viewpoint from which the scene should be viewed.
				@remarks
					Typically this method returns the origin unless a) world geometry has been loaded using
					SceneManager::setWorldGeometry and b) that world geometry has suggested 'start' points.
					If there is more than one viewpoint which the scene manager can suggest, it will always suggest
					the first one unless the random parameter is true.
				@param
					random If true, and there is more than one possible suggestion, a random one will be used. If false
					the same one will always be suggested.
				@return
					On success, true is returned.
				@par
					On failiure, false is returned.
			*/
			virtual Ogre::ViewPoint getSuggestedViewpoint(bool random = false);

			/** Method for setting a specific option of the Scene Manager. These options are usually
				specific for a certain implemntation of the Scene Manager class, and may (and probably
				will) not exist across different implementations.
				@param
					strKey The name of the option to set
				@param
					pValue A pointer to the value - the size should be calculated by the scene manager
					based on the key
				@return
					On success, true is returned.
				@par
					On failiure, false is returned.
			*/
			virtual bool setOption( const Ogre::String& strKey, const void* pValue );

			/** Method for getting the value of an implementation-specific Scene Manager option.
				@param
					strKey The name of the option
				@param
					pDestValue A pointer to a memory location where the value will
					be copied. Currently, the memory will be allocated by the
					scene manager, but this may change
				@return
					On success, true is returned and pDestValue points to the value of the given
					option.
				@par
					On failiure, false is returned and pDestValue is set to NULL.
			*/
			virtual bool getOption( const Ogre::String& strKey, void* pDestValue );

			/** Method for verifying wether the scene manager has an implementation-specific
				option.
				@param
					strKey The name of the option to check for.
				@return
					If the scene manager contains the given option, true is returned.
				@remarks
					If it does not, false is returned.
			*/
			virtual bool hasOption( const Ogre::String& strKey ) const;
			/** Method for getting all possible values for a specific option. When this list is too large
				(i.e. the option expects, for example, a float), the return value will be true, but the
				list will contain just one element whose size will be set to 0.
				Otherwise, the list will be filled with all the possible values the option can
				accept.
				@param
					strKey The name of the option to get the values for.
				@param
					refValueList A reference to a list that will be filled with the available values.
				@return
					On success (the option exists), true is returned.
				@par
					On failure, false is returned.
			*/
			virtual bool getOptionValues( const Ogre::String& strKey, Ogre::StringVector& refValueList );

			/** Method for getting all the implementation-specific options of the scene manager.
				@param
					refKeys A reference to a list that will be filled with all the available options.
				@return
					On success, true is returned. On failiure, false is returned.
			*/
			virtual bool getOptionKeys( Ogre::StringVector& refKeys );

			/** Internal method for updating the scene graph ie the tree of SceneNode instances managed by this class.
				@remarks
					This must be done before issuing objects to the rendering pipeline, since derived transformations from
					parent nodes are not updated until required. This SceneManager is a basic implementation which simply
					updates all nodes from the root. This ensures the scene is up to date but requires all the nodes
					to be updated even if they are not visible. Subclasses could trim this such that only potentially visible
					nodes are updated.
			*/
			virtual void _updateSceneGraph(Ogre::Camera* cam);

			/** Internal method which parses the scene to find visible objects to render.
				@remarks
					If you're implementing a custom scene manager, this is the most important method to
					override since it's here you can apply your custom world partitioning scheme. Once you
					have added the appropriate objects to the render queue, you can let the default
					SceneManager objects _renderVisibleObjects handle the actual rendering of the objects
					you pick.
				@par
					Any visible objects will be added to a rendering queue, which is indexed by material in order
					to ensure objects with the same material are rendered together to minimise render state changes.
			*/
			virtual void _findVisibleObjects(Ogre::Camera* cam, Ogre::VisibleObjectsBoundsInfo* visibleBounds, bool onlyShadowCasters);

			/** Internal method for applying animations to scene nodes.
			@remarks
				Uses the internally stored AnimationState objects to apply animation to SceneNodes.
			*/
			virtual void _applySceneAnimations(void);

			/** Sends visible objects found in _findVisibleObjects to the rendering engine.
			*/
			virtual void _renderVisibleObjects(void);

			/** Prompts the class to send its contents to the renderer.
				@remarks
					This method prompts the scene manager to send the
					contents of the scene it manages to the rendering
					pipeline, possibly preceded by some sorting, culling
					or other scene management tasks. Note that this method is not normally called
					directly by the user application; it is called automatically
					by the Ogre rendering loop.
				@param camera Pointer to a camera from whose viewpoint the scene is to
					be rendered.
				@param vp The target viewport
				@param includeOverlays Whether or not overlay objects should be rendered
			*/
			virtual void _renderScene(Ogre::Camera* camera, Ogre::Viewport* vp, bool includeOverlays);

			/** Internal method for queueing the sky objects with the params as 
				previously set through setSkyBox, setSkyPlane and setSkyDome.
			*/
			virtual void _queueSkiesForRendering(Ogre::Camera* cam);



			/** Notifies the scene manager of its destination render system
				@remarks
					Called automatically by RenderSystem::addSceneManager
					this method simply notifies the manager of the render
					system to which its output must be directed.
				@param
					sys Pointer to the RenderSystem subclass to be used as a render target.
			*/
			virtual void _setDestinationRenderSystem(Ogre::RenderSystem* sys);

			/** Enables / disables a 'sky plane' i.e. a plane at constant
				distance from the camera representing the sky.
				@remarks
					You can create sky planes yourself using the standard mesh and
					entity methods, but this creates a plane which the camera can
					never get closer or further away from - it moves with the camera.
					(NB you could create this effect by creating a world plane which
					was attached to the same SceneNode as the Camera too, but this
					would only apply to a single camera whereas this plane applies to
					any camera using this scene manager).
				@note
					To apply scaling, scrolls etc to the sky texture(s) you
					should use the TextureUnitState class methods.
				@param
					enable True to enable the plane, false to disable it
				@param
					plane Details of the plane, i.e. it's normal and it's
					distance from the camera.
				@param
					materialName The name of the material the plane will use
				@param
					scale The scaling applied to the sky plane - higher values
					mean a bigger sky plane - you may want to tweak this
					depending on the size of plane.d and the other
					characteristics of your scene
				@param
					tiling How many times to tile the texture across the sky.
					Applies to all texture layers. If you need finer control use
					the TextureUnitState texture coordinate transformation methods.
				@param
					drawFirst If true, the plane is drawn before all other
					geometry in the scene, without updating the depth buffer.
					This is the safest rendering method since all other objects
					will always appear in front of the sky. However this is not
					the most efficient way if most of the sky is often occluded
					by other objects. If this is the case, you can set this
					parameter to false meaning it draws <em>after</em> all other
					geometry which can be an optimisation - however you must
					ensure that the plane.d value is large enough that no objects
					will 'poke through' the sky plane when it is rendered.
				@param
					bow If zero, the plane will be completely flat (like previous
					versions.  If above zero, the plane will be curved, allowing
					the sky to appear below camera level.  Curved sky planes are 
					simular to skydomes, but are more compatable with fog.
				@param xsegments, ysegments
					Determines the number of segments the plane will have to it. This
					is most important when you are bowing the plane, but may also be useful
					if you need tesselation on the plane to perform per-vertex effects.
				@param groupName
					The name of the resource group to which to assign the plane mesh.
			*/
			virtual void setSkyPlane(
				bool enable,
				const Ogre::Plane& plane, const Ogre::String& materialName, Ogre::Real scale = 1000,
				Ogre::Real tiling = 10, bool drawFirst = true, Ogre::Real bow = 0, 
				int xsegments = 1, int ysegments = 1, 
				const Ogre::String& groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			/** Return whether a key plane is enabled */

			/** Get the sky plane node, if enabled. */
			virtual Ogre::SceneNode* getSkyPlaneNode(void) const;

			/** Get the parameters used to construct the SkyPlane, if any **/
			virtual const Ogre::SceneManager::SkyPlaneGenParameters& getSkyPlaneGenParameters(void) const;

			/** Enables / disables a 'sky box' i.e. a 6-sided box at constant
				distance from the camera representing the sky.
				@remarks
					You could create a sky box yourself using the standard mesh and
					entity methods, but this creates a plane which the camera can
					never get closer or further away from - it moves with the camera.
					(NB you could create this effect by creating a world box which
					was attached to the same SceneNode as the Camera too, but this
					would only apply to a single camera whereas this skybox applies
					to any camera using this scene manager).
				@par
					The material you use for the skybox can either contain layers
					which are single textures, or they can be cubic textures, i.e.
					made up of 6 images, one for each plane of the cube. See the
					TextureUnitState class for more information.
				@param
					enable True to enable the skybox, false to disable it
				@param
					materialName The name of the material the box will use
				@param
					distance Distance in world coorinates from the camera to
					each plane of the box. The default is normally OK.
				@param
					drawFirst If true, the box is drawn before all other
					geometry in the scene, without updating the depth buffer.
					This is the safest rendering method since all other objects
					will always appear in front of the sky. However this is not
					the most efficient way if most of the sky is often occluded
					by other objects. If this is the case, you can set this
					parameter to false meaning it draws <em>after</em> all other
					geometry which can be an optimisation - however you must
					ensure that the distance value is large enough that no
					objects will 'poke through' the sky box when it is rendered.
				@param
					orientation Optional parameter to specify the orientation
					of the box. By default the 'top' of the box is deemed to be
					in the +y direction, and the 'front' at the -z direction.
					You can use this parameter to rotate the sky if you want.
				@param groupName
					The name of the resource group to which to assign the plane mesh.
			*/
			virtual void setSkyBox(
				bool enable, const Ogre::String& materialName, Ogre::Real distance = 5000,
				bool drawFirst = true, const Ogre::Quaternion& orientation = Ogre::Quaternion::IDENTITY,
				const Ogre::String& groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			/** Return whether a skybox is enabled */
			virtual bool isSkyBoxEnabled(void) const;

			/** Get the skybox node, if enabled. */
			virtual Ogre::SceneNode* getSkyBoxNode(void) const;

			/** Get the parameters used to generate the current SkyBox, if any */
			virtual const Ogre::SceneManager::SkyBoxGenParameters& getSkyBoxGenParameters(void) const;

			/** Enables / disables a 'sky dome' i.e. an illusion of a curved sky.
				@remarks
					A sky dome is actually formed by 5 sides of a cube, but with
					texture coordinates generated such that the surface appears
					curved like a dome. Sky domes are appropriate where you need a
					realistic looking sky where the scene is not going to be
					'fogged', and there is always a 'floor' of some sort to prevent
					the viewer looking below the horizon (the distortion effect below
					the horizon can be pretty horrible, and there is never anyhting
					directly below the viewer). If you need a complete wrap-around
					background, use the setSkyBox method instead. You can actually
					combine a sky box and a sky dome if you want, to give a positional
					backdrop with an overlayed curved cloud layer.
				@par
					Sky domes work well with 2D repeating textures like clouds. You
					can change the apparant 'curvature' of the sky depending on how
					your scene is viewed - lower curvatures are better for 'open'
					scenes like landscapes, whilst higher curvatures are better for
					say FPS levels where you don't see a lot of the sky at once and
					the exaggerated curve looks good.
				@param
					enable True to enable the skydome, false to disable it
				@param
					materialName The name of the material the dome will use
				@param
					curvature The curvature of the dome. Good values are
					between 2 and 65. Higher values are more curved leading to
					a smoother effect, lower values are less curved meaning
					more distortion at the horizons but a better distance effect.
				@param
					tiling How many times to tile the texture(s) across the
					dome.
				@param
					distance Distance in world coorinates from the camera to
					each plane of the box the dome is rendered on. The default
					is normally OK.
				@param
					drawFirst If true, the dome is drawn before all other
					geometry in the scene, without updating the depth buffer.
					This is the safest rendering method since all other objects
					will always appear in front of the sky. However this is not
					the most efficient way if most of the sky is often occluded
					by other objects. If this is the case, you can set this
					parameter to false meaning it draws <em>after</em> all other
					geometry which can be an optimisation - however you must
					ensure that the distance value is large enough that no
					objects will 'poke through' the sky when it is rendered.
				@param
					orientation Optional parameter to specify the orientation
					of the dome. By default the 'top' of the dome is deemed to
					be in the +y direction, and the 'front' at the -z direction.
					You can use this parameter to rotate the sky if you want.
				@param groupName
					The name of the resource group to which to assign the plane mesh.
			*/
			virtual void setSkyDome(
				bool enable, const Ogre::String& materialName, Ogre::Real curvature = 10,
				Ogre::Real tiling = 8, Ogre::Real distance = 4000, bool drawFirst = true,
				const Ogre::Quaternion& orientation = Ogre::Quaternion::IDENTITY,
				int xsegments = 16, int ysegments = 16, int ysegments_keep = -1,
				const Ogre::String& groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			/** Return whether a skydome is enabled */
			virtual bool isSkyDomeEnabled(void) const;

			/** Get the sky dome node, if enabled. */
			virtual Ogre::SceneNode* getSkyDomeNode(void) const;

			/** Get the parameters used to generate the current SkyDome, if any */
			virtual const Ogre::SceneManager::SkyDomeGenParameters& getSkyDomeGenParameters(void) const;

			/** Sets the fogging mode applied to the scene.
				@remarks
					This method sets up the scene-wide fogging effect. These settings
					apply to all geometry rendered, UNLESS the material with which it
					is rendered has it's own fog settings (see Material::setFog).
				@param
					mode Set up the mode of fog as described in the FogMode
					enum, or set to FOG_NONE to turn off.
				@param
					colour The colour of the fog. Either set this to the same
					as your viewport background colour, or to blend in with a
					skydome or skybox.
				@param
					expDensity The density of the fog in FOG_EXP or FOG_EXP2
					mode, as a value between 0 and 1. The default is 0.001. 
				@param
					linearStart Distance in world units at which linear fog starts to
					encroach. Only applicable if mode is
					FOG_LINEAR.
				@param
					linearEnd Distance in world units at which linear fog becomes completely
					opaque. Only applicable if mode is
					FOG_LINEAR.
			*/
			void setFog(
				Ogre::FogMode mode = Ogre::FOG_NONE, const Ogre::ColourValue& colour = Ogre::ColourValue::White,
				Ogre::Real expDensity = 0.001, Ogre::Real linearStart = 0.0, Ogre::Real linearEnd = 1.0);

			/** Returns the fog mode for the scene.
			*/
			virtual Ogre::FogMode getFogMode(void) const;

			/** Returns the fog colour for the scene.
			*/
			virtual const Ogre::ColourValue& getFogColour(void) const;

			/** Returns the fog start distance for the scene.
			*/
			virtual Ogre::Real getFogStart(void) const;

			/** Returns the fog end distance for the scene.
			*/
			virtual Ogre::Real getFogEnd(void) const;

			/** Returns the fog density for the scene.
			*/
			virtual Ogre::Real getFogDensity(void) const;


			/** Creates a new BillboardSet for use with this scene manager.
				@remarks
					This method creates a new BillboardSet which is registered with
					the SceneManager. The SceneManager will destroy this object when
					it shuts down or when the SceneManager::clearScene method is
					called, so the caller does not have to worry about destroying
					this object (in fact, it definitely should not do this).
				@par
					See the BillboardSet documentations for full details of the
					returned class.
				@param
					name The name to give to this billboard set. Must be unique.
				@param
					poolSize The initial size of the pool of billboards (see BillboardSet for more information)
				@see
					BillboardSet
			*/
			virtual Ogre::BillboardSet* createBillboardSet(const Ogre::String& name, unsigned int poolSize = 20);

			/** Retrieves a pointer to the named BillboardSet.
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::BillboardSet* getBillboardSet(const Ogre::String& name) const;
			/** Returns whether a billboardset with the given name exists.
			*/
			virtual bool hasBillboardSet(const Ogre::String& name) const;

			/** Removes & destroys an BillboardSet from the SceneManager.
				@warning
					Must only be done if the BillboardSet is not attached
					to a SceneNode. It may be safer to wait to clear the whole
					scene. If you are unsure, use clearScene.
			*/
			virtual void destroyBillboardSet(Ogre::BillboardSet* set);

			/** Removes & destroys an BillboardSet from the SceneManager by name.
				@warning
					Must only be done if the BillboardSet is not attached
					to a SceneNode. It may be safer to wait to clear the whole
					scene. If you are unsure, use clearScene.
			*/
			virtual void destroyBillboardSet(const Ogre::String& name);

			/** Removes & destroys all BillboardSets.
			@warning
			Again, use caution since no BillboardSet must be referred to
			elsewhere e.g. attached to a SceneNode otherwise a crash
			is likely. Use clearScene if you are unsure (it clears SceneNode
			entries too.)
			@see
			SceneManager::clearScene
			*/
			virtual void destroyAllBillboardSets(void);

			/** Tells the SceneManager whether it should render the SceneNodes which 
				make up the scene as well as the objects in the scene.
			@remarks
				This method is mainly for debugging purposes. If you set this to 'true',
				each node will be rendered as a set of 3 axes to allow you to easily see
				the orientation of the nodes.
			*/
			virtual void setDisplaySceneNodes(bool display);
			/** Returns true if all scene nodes axis are to be displayed */
			virtual bool getDisplaySceneNodes(void) const;

			/** Creates an animation which can be used to animate scene nodes.
			@remarks
				An animation is a collection of 'tracks' which over time change the position / orientation
				of Node objects. In this case, the animation will likely have tracks to modify the position
				/ orientation of SceneNode objects, e.g. to make objects move along a path.
			@par
				You don't need to use an Animation object to move objects around - you can do it yourself
				using the methods of the Node in your FrameListener class. However, when you need relatively
				complex scripted animation, this is the class to use since it will interpolate between
				keyframes for you and generally make the whole process easier to manage.
			@par
				A single animation can affect multiple Node objects (each AnimationTrack affects a single Node).
				In addition, through animation blending a single Node can be affected by multiple animations,
				athough this is more useful when performing skeletal animation (see Skeleton::createAnimation).
			@par
				Note that whilst it uses the same classes, the animations created here are kept separate from the
				skeletal animations of meshes (each Skeleton owns those animations).
			@param name The name of the animation, must be unique within this SceneManager.
			@param length The total length of the animation.
			*/
			virtual Ogre::Animation* createAnimation(const Ogre::String& name, Ogre::Real length);

			/** Looks up an Animation object previously created with createAnimation. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::Animation* getAnimation(const Ogre::String& name) const;
			/** Returns whether an animation with the given name exists.
			*/
			virtual bool hasAnimation(const Ogre::String& name) const;

			/** Destroys an Animation. 
			@remarks
				You should ensure that none of your code is referencing this animation objects since the 
				memory will be freed.
			*/
			virtual void destroyAnimation(const Ogre::String& name);

			/** Removes all animations created using this SceneManager. */
			virtual void destroyAllAnimations(void);

			/** Create an AnimationState object for managing application of animations.
			@remarks
				You can create Animation objects for animating SceneNode obejcts using the
				createAnimation method. However, in order to actually apply those animations
				you have to call methods on Node and Animation in a particular order (namely
				Node::resetToInitialState and Animation::apply). To make this easier and to
				help track the current time position of animations, the AnimationState object
				is provided. </p>
				So if you don't want to control animation application manually, call this method,
				update the returned object as you like every frame and let SceneManager apply 
				the animation state for you.
			@par
				Remember, AnimationState objects are disabled by default at creation time. 
				Turn them on when you want them using their setEnabled method.
			@par
				Note that any SceneNode affected by this automatic animation will have it's state
				reset to it's initial position before application of the animation. Unless specifically
				modified using Node::setInitialState the Node assumes it's initial state is at the
				origin. If you want the base state of the SceneNode to be elsewhere, make your changes
				to the node using the standard transform methods, then call setInitialState to 
				'bake' this reference position into the node.
			@par
				If the target of your animation is to be a generic AnimableValue, you
				should ensure that it has a base value set (unlike nodes this has no
				default). @see AnimableValue::setAsBaseValue.
			@param animName The name of an animation created already with createAnimation.
			*/
			virtual Ogre::AnimationState* createAnimationState(const Ogre::String& animName);

			/** Retrieves animation state as previously created using createAnimationState. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::AnimationState* getAnimationState(const Ogre::String& animName) const;
			/** Returns whether an animation state with the given name exists.
			*/
			virtual bool hasAnimationState(const Ogre::String& name) const;

			/** Destroys an AnimationState. 
			@remarks
				You should ensure that none of your code is referencing this animation 
				state object since the memory will be freed.
			*/
			virtual void destroyAnimationState(const Ogre::String& name);

			/** Removes all animation states created using this SceneManager. */
			virtual void destroyAllAnimationStates(void);

			/** Manual rendering method, for advanced users only.
			@remarks
				This method allows you to send rendering commands through the pipeline on
				demand, bypassing OGRE's normal world processing. You should only use this if you
				really know what you're doing; OGRE does lots of things for you that you really should
				let it do. However, there are times where it may be useful to have this manual interface,
				for example overlaying something on top of the scene rendered by OGRE.
			@par
				Because this is an instant rendering method, timing is important. The best 
				time to call it is from a RenderTargetListener event handler.
			@par
				Don't call this method a lot, it's designed for rare (1 or 2 times per frame) use. 
				Calling it regularly per frame will cause frame rate drops!
			@param rend A RenderOperation object describing the rendering op
			@param pass The Pass to use for this render
			@param vp Pointer to the viewport to render to
			@param worldMatrix The transform to apply from object to world space
			@param viewMatrix The transform to apply from world to view space
			@param projMatrix The transform to apply from view to screen space
			@param doBeginEndFrame If true, beginFrame() and endFrame() are called, 
				otherwise not. You should leave this as false if you are calling
				this within the main render loop.
			*/
			virtual void manualRender(Ogre::RenderOperation* rend, Ogre::Pass* pass, Ogre::Viewport* vp, 
				const Ogre::Matrix4& worldMatrix, const Ogre::Matrix4& viewMatrix, const Ogre::Matrix4& projMatrix, 
				bool doBeginEndFrame = false) ;

			/** Retrieves the internal render queue, for advanced users only.
			@remarks
				The render queue is mainly used internally to manage the scene object 
				rendering queue, it also exports some methods to allow advanced users 
				to configure the behavior of rendering process.
				Most methods provided by RenderQueue are supposed to be used 
				internally only, you should reference to the RenderQueue API for 
				more information. Do not access this directly unless you know what 
				you are doing.
			*/
			virtual Ogre::RenderQueue* getRenderQueue(void);

			/** Registers a new RenderQueueListener which will be notified when render queues
				are processed.
			*/
			virtual void addRenderQueueListener(Ogre::RenderQueueListener* newListener);

			/** Removes a listener previously added with addRenderQueueListener. */
			virtual void removeRenderQueueListener(Ogre::RenderQueueListener* delListener);

			/** Adds an item to the 'special case' render queue list.
			@remarks
				Normally all render queues are rendered, in their usual sequence, 
				only varying if a RenderQueueListener nominates for the queue to be 
				repeated or skipped. This method allows you to add a render queue to 
				a 'special case' list, which varies the behaviour. The effect of this
				list depends on the 'mode' in which this list is in, which might be
				to exclude these render queues, or to include them alone (excluding
				all other queues). This allows you to perform broad selective
				rendering without requiring a RenderQueueListener.
			@param qid The identifier of the queue which should be added to the
				special case list. Nothing happens if the queue is already in the list.
			*/
			virtual void addSpecialCaseRenderQueue(Ogre::uint8 qid);
			/** Removes an item to the 'special case' render queue list.
			@see SceneManager::addSpecialCaseRenderQueue
			@param qid The identifier of the queue which should be removed from the
				special case list. Nothing happens if the queue is not in the list.
			*/
			virtual void removeSpecialCaseRenderQueue(Ogre::uint8 qid);
			/** Clears the 'special case' render queue list.
			@see SceneManager::addSpecialCaseRenderQueue
			*/
			virtual void clearSpecialCaseRenderQueues(void);
			/** Sets the way the special case render queue list is processed.
			@see SceneManager::addSpecialCaseRenderQueue
			@param mode The mode of processing
			*/
			virtual void setSpecialCaseRenderQueueMode(Ogre::SceneManager::SpecialCaseRenderQueueMode mode);
			/** Gets the way the special case render queue list is processed. */
			virtual Ogre::SceneManager::SpecialCaseRenderQueueMode getSpecialCaseRenderQueueMode(void);
			/** Returns whether or not the named queue will be rendered based on the
				current 'special case' render queue list and mode.
			@see SceneManager::addSpecialCaseRenderQueue
			@param qid The identifier of the queue which should be tested
			@returns true if the queue will be rendered, false otherwise
			*/
			virtual bool isRenderQueueToBeProcessed(Ogre::uint8 qid);

			/** Sets the render queue that the world geometry (if any) this SceneManager
				renders will be associated with.
			@remarks
				SceneManagers which provide 'world geometry' should place it in a 
				specialised render queue in order to make it possible to enable / 
				disable it easily using the addSpecialCaseRenderQueue method. Even 
				if the SceneManager does not use the render queues to render the 
				world geometry, it should still pick a queue to represent it's manual
				rendering, and check isRenderQueueToBeProcessed before rendering.
			@note
				Setting this may not affect the actual ordering of rendering the
				world geometry, if the world geometry is being rendered manually
				by the SceneManager. If the SceneManager feeds world geometry into
				the queues, however, the ordering will be affected. 
			*/
			virtual void setWorldGeometryRenderQueue(Ogre::uint8 qid);
			/** Gets the render queue that the world geometry (if any) this SceneManager
				renders will be associated with.
			@remarks
				SceneManagers which provide 'world geometry' should place it in a 
				specialised render queue in order to make it possible to enable / 
				disable it easily using the addSpecialCaseRenderQueue method. Even 
				if the SceneManager does not use the render queues to render the 
				world geometry, it should still pick a queue to represent it's manual
				rendering, and check isRenderQueueToBeProcessed before rendering.
			*/
			virtual Ogre::uint8 getWorldGeometryRenderQueue(void);

			/** Allows all bounding boxes of scene nodes to be displayed. */
			virtual void showBoundingBoxes(bool bShow);

			/** Returns if all bounding boxes of scene nodes are to be displayed */
			virtual bool getShowBoundingBoxes() const;

			/** Internal method for notifying the manager that a SceneNode is autotracking. */
			virtual void _notifyAutotrackingSceneNode(Ogre::SceneNode* node, bool autoTrack);

	        
			/** Creates an AxisAlignedBoxSceneQuery for this scene manager. 
			@remarks
				This method creates a new instance of a query object for this scene manager, 
				for an axis aligned box region. See SceneQuery and AxisAlignedBoxSceneQuery 
				for full details.
			@par
				The instance returned from this method must be destroyed by calling
				SceneManager::destroyQuery when it is no longer required.
			@param box Details of the box which describes the region for this query.
			@param mask The query mask to apply to this query; can be used to filter out
				certain objects; see SceneQuery for details.
			*/
			virtual Ogre::AxisAlignedBoxSceneQuery* 
				createAABBQuery(const Ogre::AxisAlignedBox& box, unsigned long mask = 0xFFFFFFFF);
			/** Creates a SphereSceneQuery for this scene manager. 
			@remarks
				This method creates a new instance of a query object for this scene manager, 
				for a spherical region. See SceneQuery and SphereSceneQuery 
				for full details.
			@par
				The instance returned from this method must be destroyed by calling
				SceneManager::destroyQuery when it is no longer required.
			@param sphere Details of the sphere which describes the region for this query.
			@param mask The query mask to apply to this query; can be used to filter out
				certain objects; see SceneQuery for details.
			*/
			virtual Ogre::SphereSceneQuery* 
				createSphereQuery(const Ogre::Sphere& sphere, unsigned long mask = 0xFFFFFFFF);
			/** Creates a PlaneBoundedVolumeListSceneQuery for this scene manager. 
			@remarks
			This method creates a new instance of a query object for this scene manager, 
			for a region enclosed by a set of planes (normals pointing inwards). 
			See SceneQuery and PlaneBoundedVolumeListSceneQuery for full details.
			@par
			The instance returned from this method must be destroyed by calling
			SceneManager::destroyQuery when it is no longer required.
			@param volumes Details of the volumes which describe the region for this query.
			@param mask The query mask to apply to this query; can be used to filter out
			certain objects; see SceneQuery for details.
			*/
			virtual Ogre::PlaneBoundedVolumeListSceneQuery* 
				createPlaneBoundedVolumeQuery(const Ogre::PlaneBoundedVolumeList& volumes, unsigned long mask = 0xFFFFFFFF);


			/** Creates a RaySceneQuery for this scene manager. 
			@remarks
				This method creates a new instance of a query object for this scene manager, 
				looking for objects which fall along a ray. See SceneQuery and RaySceneQuery 
				for full details.
			@par
				The instance returned from this method must be destroyed by calling
				SceneManager::destroyQuery when it is no longer required.
			@param ray Details of the ray which describes the region for this query.
			@param mask The query mask to apply to this query; can be used to filter out
				certain objects; see SceneQuery for details.
			*/
			virtual Ogre::RaySceneQuery* 
				createRayQuery(const Ogre::Ray& ray, unsigned long mask = 0xFFFFFFFF);
			//PyramidSceneQuery* createPyramidQuery(const Pyramid& p, unsigned long mask = 0xFFFFFFFF);
			/** Creates an IntersectionSceneQuery for this scene manager. 
			@remarks
				This method creates a new instance of a query object for locating
				intersecting objects. See SceneQuery and IntersectionSceneQuery
				for full details.
			@par
				The instance returned from this method must be destroyed by calling
				SceneManager::destroyQuery when it is no longer required.
			@param mask The query mask to apply to this query; can be used to filter out
				certain objects; see SceneQuery for details.
			*/
			virtual Ogre::IntersectionSceneQuery* 
				createIntersectionQuery(unsigned long mask = 0xFFFFFFFF);

			/** Destroys a scene query of any type. */
			virtual void destroyQuery(Ogre::SceneQuery* query);

			/** Returns a specialised MapIterator over all cameras in the scene. 
			*/
			Ogre::SceneManager::CameraIterator getCameraIterator(void);

			/** Returns a specialised MapIterator over all animations in the scene. */
			Ogre::SceneManager::AnimationIterator getAnimationIterator(void);

			/** Returns a specialised MapIterator over all animation states in the scene. */
			Ogre::AnimationStateIterator getAnimationStateIterator(void);

			/** Sets the general shadow technique to be used in this scene.
			@remarks   
				There are multiple ways to generate shadows in a scene, and each has 
				strengths and weaknesses. 
				<ul><li>Stencil-based approaches can be used to 
				draw very long, extreme shadows without loss of precision and the 'additive'
				version can correctly show the shadowing of complex effects like bump mapping
				because they physically exclude the light from those areas. However, the edges
				are very sharp and stencils cannot handle transparency, and they involve a 
				fair amount of CPU work in order to calculate the shadow volumes, especially
				when animated objects are involved.</li>
				<li>Texture-based approaches are good for handling transparency (they can, for
				example, correctly shadow a mesh which uses alpha to represent holes), and they
				require little CPU overhead, and can happily shadow geometry which is deformed
				by a vertex program, unlike stencil shadows. However, they have a fixed precision 
				which can introduce 'jaggies' at long range and have fillrate issues of their own.</li>
				</ul>
			@par
				We support 2 kinds of stencil shadows, and 2 kinds of texture-based shadows, and one
				simple decal approach. The 2 stencil approaches differ in the amount of multipass work 
				that is required - the modulative approach simply 'darkens' areas in shadow after the 
				main render, which is the least expensive, whilst the additive approach has to perform 
				a render per light and adds the cumulative effect, whcih is more expensive but more 
				accurate. The texture based shadows both work in roughly the same way, the only difference is
				that the shadowmap approach is slightly more accurate, but requires a more recent
				graphics card.
			@par
				Note that because mixing many shadow techniques can cause problems, only one technique
				is supported at once. Also, you should call this method at the start of the 
				scene setup. 
			@param technique The shadowing technique to use for the scene.
			*/
			virtual void setShadowTechnique(Ogre::ShadowTechnique technique);
	        
			/** Gets the current shadow technique. */
			virtual Ogre::ShadowTechnique getShadowTechnique(void) const;

			/** Enables / disables the rendering of debug information for shadows. */
			virtual void setShowDebugShadows(bool debug);
			/** Are debug shadows shown? */
			virtual bool getShowDebugShadows(void ) const;

			/** Set the colour used to modulate areas in shadow. 
			@remarks This is only applicable for shadow techniques which involve 
				darkening the area in shadow, as opposed to masking out the light. 
				This colour provided is used as a modulative value to darken the
				areas.
			*/
			virtual void setShadowColour(const Ogre::ColourValue& colour);
			/** Get the colour used to modulate areas in shadow. 
			@remarks This is only applicable for shadow techniques which involve 
			darkening the area in shadow, as opposed to masking out the light. 
			This colour provided is used as a modulative value to darken the
			areas.
			*/
			virtual const Ogre::ColourValue& getShadowColour(void) const;
			/** Sets the distance a shadow volume is extruded for a directional light.
			@remarks
				Although directional lights are essentially infinite, there are many
				reasons to limit the shadow extrusion distance to a finite number, 
				not least of which is compatibility with older cards (which do not
				support infinite positions), and shadow caster elimination.
			@par
				The default value is 10,000 world units. This does not apply to
				point lights or spotlights, since they extrude up to their 
				attenuation range.
			*/
			virtual void setShadowDirectionalLightExtrusionDistance(Ogre::Real dist); 
			/** Gets the distance a shadow volume is extruded for a directional light.
			*/
			virtual Ogre::Real getShadowDirectionalLightExtrusionDistance(void) const;
			/** Sets the maximum distance away from the camera that shadows
			will be visible.
			@remarks
			Shadow techniques can be expensive, therefore it is a good idea
			to limit them to being rendered close to the camera if possible,
			and to skip the expense of rendering shadows for distance objects.
			This method allows you to set the distance at which shadows will no
			longer be rendered.
			@note
			Each shadow technique can interpret this subtely differently.
			For example, one technique may use this to eliminate casters,
			another might use it to attenuate the shadows themselves.
			You should tweak this value to suit your chosen shadow technique
			and scene setup.
			*/
			virtual void setShadowFarDistance(Ogre::Real distance);
			/** Gets the maximum distance away from the camera that shadows
			will be visible.
			*/
			virtual Ogre::Real getShadowFarDistance(void) const;

			/** Sets the maximum size of the index buffer used to render shadow
	 			primitives.
			@remarks
				This method allows you to tweak the size of the index buffer used
				to render shadow primitives (including stencil shadow volumes). The
				default size is 51,200 entries, which is 100k of GPU memory, or
				enough to render approximately 17,000 triangles. You can reduce this
				as long as you do not have any models / world geometry chunks which 
				could require more than the amount you set.
			@par
				The maximum number of triangles required to render a single shadow 
				volume (including light and dark caps when needed) will be 3x the 
				number of edges on the light silhouette, plus the number of 
				light-facing triangles.	On average, half the 
				triangles will be facing toward the light, but the number of 
				triangles in the silhouette entirely depends on the mesh - 
				angular meshes will have a higher silhouette tris/mesh tris
				ratio than a smooth mesh. You can estimate the requirements for
				your particular mesh by rendering it alone in a scene with shadows
				enabled and a single light - rotate it or the light and make a note
				of how high the triangle count goes (remembering to subtract the 
				mesh triangle count)
			@param size The number of indexes; divide this by 3 to determine the
				number of triangles.
			*/
			virtual void setShadowIndexBufferSize(size_t size);

			/// Get the size of the shadow index buffer
			virtual size_t getShadowIndexBufferSize(void) const;

			/** Set the size of the texture used for all texture-based shadows.
			@remarks
				The larger the shadow texture, the better the detail on 
				texture based shadows, but obviously this takes more memory.
				The default size is 512. Sizes must be a power of 2.
			@note This is the simple form, see setShadowTextureConfig for the more 
				complex form.
			*/
			virtual void setShadowTextureSize(unsigned short size);

			/** Set the detailed configuration for a shadow texture.
			@param shadowIndex The index of the texture to configure, must be < the
				number of shadow textures setting
			@param width, height The dimensions of the texture
			@param format The pixel format of the texture
			*/
			virtual void setShadowTextureConfig(size_t shadowIndex, unsigned short width, 
				unsigned short height, Ogre::PixelFormat format);
			/** Set the detailed configuration for a shadow texture.
			@param shadowIndex The index of the texture to configure, must be < the
				number of shadow textures setting
			@param config Configuration structure
			*/
			virtual void setShadowTextureConfig(size_t shadowIndex, 
				const Ogre::ShadowTextureConfig& config);

			/** Get an iterator over the current shadow texture settings. */
			Ogre::ConstShadowTextureConfigIterator getShadowTextureConfigIterator() const;

			/** Set the pixel format of the textures used for texture-based shadows.
			@remarks
				By default, a colour texture is used (PF_X8R8G8B8) for texture shadows,
				but if you want to use more advanced texture shadow types you can 
				alter this. If you do, you will have to also call
				setShadowTextureCasterMaterial and setShadowTextureReceiverMaterial
				to provide shader-based materials to use these customised shadow
				texture formats.
			@note This is the simple form, see setShadowTextureConfig for the more 
				complex form.
			*/
			virtual void setShadowTexturePixelFormat(Ogre::PixelFormat fmt);
			/** Set the number of textures allocated for texture-based shadows.
			@remarks
				The default number of textures assigned to deal with texture based
				shadows is 1; however this means you can only have one light casting
				shadows at the same time. You can increase this number in order to 
				make this more flexible, but be aware of the texture memory it will use.
			*/
			virtual void setShadowTextureCount(size_t count);

			/// Get the number of the textures allocated for texture based shadows
			size_t getShadowTextureCount(void) const;

			/** Sets the size and count of textures used in texture-based shadows. 
			@remarks
				@see setShadowTextureSize and setShadowTextureCount for details, this
				method just allows you to change both at once, which can save on 
				reallocation if the textures have already been created.
			@note This is the simple form, see setShadowTextureConfig for the more 
				complex form.
			*/
			virtual void setShadowTextureSettings(unsigned short size, unsigned short count, 
				Ogre::PixelFormat fmt = Ogre::PF_X8R8G8B8);

			/** Get a reference to the shadow texture currently in use at the given index.
			@note
				If you change shadow settings, this reference may no longer
				be correct, so be sure not to hold the returned reference over 
				texture shadow configuration changes.
			*/
			virtual const Ogre::TexturePtr& getShadowTexture(size_t shadowIndex);

			/** Sets the proportional distance which a texture shadow which is generated from a
				directional light will be offset into the camera view to make best use of texture space.
			@remarks
				When generating a shadow texture from a directional light, an approximation is used
				since it is not possible to render the entire scene to one texture. 
				The texture is projected onto an area centred on the camera, and is
				the shadow far distance * 2 in length (it is square). This wastes
				a lot of texture space outside the frustum though, so this offset allows
				you to move the texture in front of the camera more. However, be aware
				that this can cause a little shadow 'jittering' during rotation, and
				that if you move it too far then you'll start to get artefacts close 
				to the camera. The value is represented as a proportion of the shadow
				far distance, and the default is 0.6.
			*/
			virtual void setShadowDirLightTextureOffset(Ogre::Real offset);

			/** Gets the proportional distance which a texture shadow which is generated from a
			directional light will be offset into the camera view to make best use of texture space.
			*/
			virtual Ogre::Real getShadowDirLightTextureOffset(void)  const;

			/** Sets the proportional distance at which texture shadows begin to fade out.
			@remarks
				To hide the edges where texture shadows end (in directional lights)
				Ogre will fade out the shadow in the distance. This value is a proportional
				distance of the entire shadow visibility distance at which the shadow
				begins to fade out. The default is 0.7
			*/
			virtual void setShadowTextureFadeStart(Ogre::Real fadeStart);

			/** Sets the proportional distance at which texture shadows finish to fading out.
			@remarks
			To hide the edges where texture shadows end (in directional lights)
			Ogre will fade out the shadow in the distance. This value is a proportional
			distance of the entire shadow visibility distance at which the shadow
			is completely invisible. The default is 0.9.
			*/
			virtual void setShadowTextureFadeEnd(Ogre::Real fadeEnd);

			/** Sets whether or not texture shadows should attempt to self-shadow.
			@remarks
				The default implementation of texture shadows uses a fixed-function 
				colour texture projection approach for maximum compatibility, and 
				as such cannot support self-shadowing. However, if you decide to 
				implement a more complex shadowing technique using the 
				setShadowTextureCasterMaterial and setShadowTextureReceiverMaterial 
				there is a possibility you may be able to support 
				self-shadowing (e.g by implementing a shader-based shadow map). In 
				this case you might want to enable this option.
			@param selfShadow Whether to attempt self-shadowing with texture shadows
			*/
			virtual void setShadowTextureSelfShadow(bool selfShadow); 

			/// Gets whether or not texture shadows attempt to self-shadow.
			virtual bool getShadowTextureSelfShadow(void) const;

			/** Sets the default material to use for rendering shadow casters.
			@remarks
				By default shadow casters are rendered into the shadow texture using
				an automatically generated fixed-function pass. This allows basic
				projective texture shadows, but it's possible to use more advanced
				shadow techniques by overriding the caster and receiver materials, for
				example providing vertex and fragment programs to implement shadow
				maps.
			@par
				You can rely on the ambient light in the scene being set to the 
				requested texture shadow colour, if that's useful. 
			@note
				Individual objects may also override the vertex program in
				your default material if their materials include 
				shadow_caster_vertex_program_ref shadow_receiver_vertex_program_ref
				entries, so if you use both make sure they are compatible.
			@note
				Only a single pass is allowed in your material, although multiple
				techniques may be used for hardware fallback.
			*/
			virtual void setShadowTextureCasterMaterial(const Ogre::String& name);
			/** Sets the default material to use for rendering shadow receivers.
			@remarks
				By default shadow receivers are rendered as a post-pass using basic
				modulation. This allows basic projective texture shadows, but it's 
				possible to use more advanced shadow techniques by overriding the 
				caster and receiver materials, for example providing vertex and 
				fragment programs to implement shadow maps.
			@par
				You can rely on texture unit 0 containing the shadow texture, and 
				for the unit to be set to use projective texturing from the light 
				(only useful if you're using fixed-function, which is unlikely; 
				otherwise you should rely on the texture_viewproj_matrix auto binding)
			@note
				Individual objects may also override the vertex program in
				your default material if their materials include 
				shadow_caster_vertex_program_ref shadow_receiver_vertex_program_ref
				entries, so if you use both make sure they are compatible.
			@note
				Only a single pass is allowed in your material, although multiple
				techniques may be used for hardware fallback.
			*/
			virtual void setShadowTextureReceiverMaterial(const Ogre::String& name);

			/** Sets whether or not shadow casters should be rendered into shadow
				textures using their back faces rather than their front faces. 
			@remarks
				Rendering back faces rather than front faces into a shadow texture
				can help minimise depth comparison issues, if you're using depth
				shadowmapping. You will probably still need some biasing but you
				won't need as much. For solid objects the result is the same anyway,
				if you have objects with holes you may want to turn this option off.
				The default is to enable this option.
			*/
			virtual void setShadowCasterRenderBackFaces(bool bf);

			/** Gets whether or not shadow casters should be rendered into shadow
				textures using their back faces rather than their front faces. 
			*/
			virtual bool getShadowCasterRenderBackFaces() const;

			/** Set the shadow camera setup to use for all lights which don't have
				their own shadow camera setup.
			@see ShadowCameraSetup
			*/
			virtual void setShadowCameraSetup(const Ogre::ShadowCameraSetupPtr& shadowSetup);

			/** Get the shadow camera setup in use for all lights which don't have
				their own shadow camera setup.
			@see ShadowCameraSetup
			*/
			virtual const Ogre::ShadowCameraSetupPtr& getShadowCameraSetup() const;

			/** Sets whether we should use an inifinite camera far plane
				when rendering stencil shadows.
			@remarks
				Stencil shadow coherency is very reliant on the shadow volume
				not being clipped by the far plane. If this clipping happens, you
				get a kind of 'negative' shadow effect. The best way to achieve
				coherency is to move the far plane of the camera out to infinity,
				thus preventing the far plane from clipping the shadow volumes.
				When combined with vertex program extrusion of the volume to 
				infinity, which	Ogre does when available, this results in very
				robust shadow volumes. For this reason, when you enable stencil 
				shadows, Ogre automatically changes your camera settings to 
				project to infinity if the card supports it. You can disable this
				behaviour if you like by calling this method; although you can 
				never enable infinite projection if the card does not support it.
			@par	
				If you disable infinite projection, or it is not available, 
				you need to be far more careful with your light attenuation /
				directional light extrusion distances to avoid clipping artefacts
				at the far plane.
			@note
				Recent cards will generally support infinite far plane projection.
				However, we have found some cases where they do not, especially
				on Direct3D. There is no standard capability we can check to 
				validate this, so we use some heuristics based on experience:
				<UL>
				<LI>OpenGL always seems to support it no matter what the card</LI>
				<LI>Direct3D on non-vertex program capable systems (including 
				vertex program capable cards on Direct3D7) does not
				support it</LI>
				<LI>Direct3D on GeForce3 and GeForce4 Ti does not seem to support
				infinite projection<LI>
				</UL>
				Therefore in the RenderSystem implementation, we may veto the use
				of an infinite far plane based on these heuristics. 
			*/
			virtual void setShadowUseInfiniteFarPlane(bool enable);

			/** Is there a stencil shadow based shadowing technique in use? */
			virtual bool isShadowTechniqueStencilBased(void) const;
			/** Is there a texture shadow based shadowing technique in use? */
			virtual bool isShadowTechniqueTextureBased(void) const;
			/** Is there a modulative shadowing technique in use? */
			virtual bool isShadowTechniqueModulative(void) const;
			/** Is there an additive shadowing technique in use? */
			virtual bool isShadowTechniqueAdditive(void) const;
			/** Is the shadow technique integrated into primary materials? */
			virtual bool isShadowTechniqueIntegrated(void) const;
			/** Is there any shadowing technique in use? */
			virtual bool isShadowTechniqueInUse(void) const;

			/** Add a listener which will get called back on shadow
				events.
			*/
			virtual void addListener(Ogre::SceneManager::Listener* l);
			/** Remove a listener
			*/
			virtual void removeListener(Ogre::SceneManager::Listener* l);

			/** Creates a StaticGeometry instance suitable for use with this
				SceneManager.
			@remarks
				StaticGeometry is a way of batching up geometry into a more 
				efficient form at the expense of being able to move it. Please 
				read the StaticGeometry class documentation for full information.
			@param name The name to give the new object
			@returns The new StaticGeometry instance
			*/
			virtual Ogre::StaticGeometry* createStaticGeometry(const Ogre::String& name);
			/** Retrieve a previously created StaticGeometry instance. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::StaticGeometry* getStaticGeometry(const Ogre::String& name) const;
			/** Returns whether a static geometry instance with the given name exists. */
			virtual bool hasStaticGeometry(const Ogre::String& name) const;
			/** Remove & destroy a StaticGeometry instance. */
			virtual void destroyStaticGeometry(Ogre::StaticGeometry* geom);
			/** Remove & destroy a StaticGeometry instance. */
			virtual void destroyStaticGeometry(const Ogre::String& name);
			/** Remove & destroy all StaticGeometry instances. */
			virtual void destroyAllStaticGeometry(void);

			/** Creates a InstancedGeometry instance suitable for use with this
				SceneManager.
			@remarks
				InstancedGeometry is a way of batching up geometry into a more 
				efficient form, and still be able to move it. Please 
				read the InstancedGeometry class documentation for full information.
			@param name The name to give the new object
			@returns The new InstancedGeometry instance
			*/
			virtual Ogre::InstancedGeometry* createInstancedGeometry(const Ogre::String& name);
			/** Retrieve a previously created InstancedGeometry instance. */
			virtual Ogre::InstancedGeometry* getInstancedGeometry(const Ogre::String& name) const;
			/** Remove & destroy a InstancedGeometry instance. */
			virtual void destroyInstancedGeometry(Ogre::InstancedGeometry* geom);
			/** Remove & destroy a InstancedGeometry instance. */
			virtual void destroyInstancedGeometry(const Ogre::String& name);
			/** Remove & destroy all InstancedGeometry instances. */
			virtual void destroyAllInstancedGeometry(void);


			/** Create a movable object of the type specified.
			@remarks
				This is the generalised form of MovableObject creation where you can
				create a MovableObject of any specialised type generically, including
				any new types registered using plugins.
			@param name The name to give the object. Must be unique within type.
			@param typeName The type of object to create
			@param params Optional name/value pair list to give extra parameters to
				the created object.
			*/
			virtual Ogre::MovableObject* createMovableObject(const Ogre::String& name, 
				const Ogre::String& typeName, const Ogre::NameValuePairList* params = 0);
			/** Destroys a MovableObject with the name specified, of the type specified.
			@remarks
				The MovableObject will automatically detach itself from any nodes
				on destruction.
			*/
			virtual void destroyMovableObject(const Ogre::String& name, const Ogre::String& typeName);
			/** Destroys a MovableObject.
			@remarks
				The MovableObject will automatically detach itself from any nodes
				on destruction.
			*/
			virtual void destroyMovableObject(Ogre::MovableObject* m);
			/** Destroy all MovableObjects of a given type. */
			virtual void destroyAllMovableObjectsByType(const Ogre::String& typeName);
			/** Destroy all MovableObjects. */
			virtual void destroyAllMovableObjects(void);
			/** Get a reference to a previously created MovableObject. 
			@note Throws an exception if the named instance does not exist
			*/
			virtual Ogre::MovableObject* getMovableObject(const Ogre::String& name, const Ogre::String& typeName) const;
			/** Returns whether a movable object instance with the given name exists. */
			virtual bool hasMovableObject(const Ogre::String& name, const Ogre::String& typeName) const;
			/** Get an iterator over all MovableObect instances of a given type. 
			@note
				The iterator returned from this method is not thread safe, do not use this
				if you are creating or deleting objects of this type in another thread.
			*/
			virtual Ogre::SceneManager::MovableObjectIterator getMovableObjectIterator(const Ogre::String& typeName);
			/** Inject a MovableObject instance created externally.
			@remarks
				This method 'injects' a MovableObject instance created externally into
				the MovableObject instance registry held in the SceneManager. You
				might want to use this if you have a MovableObject which you don't
				want to register a factory for; for example a MovableObject which 
				cannot be generally constructed by clients. 
			@note
				It is important that the MovableObject has a unique name for the type,
				and that its getMovableType() method returns a proper type name.
			*/
			virtual void injectMovableObject(Ogre::MovableObject* m);
			/** Extract a previously injected MovableObject.
			@remarks
				Essentially this does the same as destroyMovableObject, but only
				removes the instance from the internal lists, it does not attempt
				to destroy it.
			*/
			virtual void extractMovableObject(const Ogre::String& name, const Ogre::String& typeName);
			/** Extract a previously injected MovableObject.
			@remarks
				Essentially this does the same as destroyMovableObject, but only
				removes the instance from the internal lists, it does not attempt
				to destroy it.
			*/
			virtual void extractMovableObject(Ogre::MovableObject* m);
			/** Extract all injected MovableObjects of a given type.
			@remarks
				Essentially this does the same as destroyAllMovableObjectsByType, 
				but only removes the instances from the internal lists, it does not 
				attempt to destroy them.
			*/
			virtual void extractAllMovableObjectsByType(const Ogre::String& typeName);

			/** Sets a mask which is bitwise 'and'ed with objects own visibility masks
				to determine if the object is visible.
			@remarks
				Note that this is combined with any per-viewport visibility mask
				through an 'and' operation. @see Viewport::setVisibilityMask
			*/
			virtual void setVisibilityMask(Ogre::uint32 vmask);

			/** Gets a mask which is bitwise 'and'ed with objects own visibility masks
				to determine if the object is visible.
			*/
			virtual Ogre::uint32 getVisibilityMask(void);

			/** Internal method for getting the combination between the global visibility
				mask and the per-viewport visibility mask.
			*/
			Ogre::uint32 _getCombinedVisibilityMask(void) const;

			/** Sets whether the SceneManager should search for visible objects, or
				whether they are being manually handled.
			@remarks
				This is an advanced function, you should not use this unless you know
				what you are doing.
			*/
			virtual void setFindVisibleObjects(bool find);

			/** Gets whether the SceneManager should search for visible objects, or
				whether they are being manually handled.
			*/
			virtual bool getFindVisibleObjects(void);

			/** Render something as if it came from the current queue.
				@param pass		Material pass to use for setting up this quad.
				@param rend		Renderable to render
				@param shadowDerivation Whether passes should be replaced with shadow caster / receiver passes
			 */
			virtual void _injectRenderWithPass(Ogre::Pass *pass, Ogre::Renderable *rend, bool shadowDerivation = true);

			/** Indicates to the SceneManager whether it should suppress changing
				the RenderSystem states when rendering objects.
			@remarks
				This method allows you to tell the SceneManager not to change any
				RenderSystem state until you tell it to. This method is only 
				intended for advanced use, don't use it if you're unsure of the 
				effect. The only RenderSystems calls made are to set the world 
				matrix for each object (note - view an projection matrices are NOT
				SET - they are under your control) and to render the object; it is up to 
				the caller to do everything else, including enabling any vertex / 
				fragment programs and updating their parameter state, and binding
				parameters to the RenderSystem.
			@note
				Calling this implicitly disables shadow processing since no shadows
				can be rendered without changing state.
			@param suppress If true, no RenderSystem state changes will be issued
				until this method is called again with a parameter of false.
			*/
			virtual void _suppressRenderStateChanges(bool suppress);
			
			/** Are render state changes suppressed? 
			@see _suppressRenderStateChanges
			*/
			virtual bool _areRenderStateChangesSuppressed(void) const;

			/** Internal method for setting up the renderstate for a rendering pass.
				@param pass The Pass details to set.
				@param evenIfSuppressed Sets the pass details even if render state
					changes are suppressed; if you are using this to manually set state
					when render state changes are suppressed, you should set this to 
					true.
				@param shadowDerivation If false, disables the derivation of shadow
					passes from original passes
				@returns
					A Pass object that was used instead of the one passed in, can
					happen when rendering shadow passes
			*/
			virtual const Ogre::Pass* _setPass(const Ogre::Pass* pass, 
				bool evenIfSuppressed = false, bool shadowDerivation = true);


			/** Indicates to the SceneManager whether it should suppress the 
				active shadow rendering technique until told otherwise.
			@remarks
				This is a temporary alternative to setShadowTechnique to suppress
				the rendering of shadows and forcing all processing down the 
				standard rendering path. This is intended for internal use only.
			@param suppress If true, no shadow rendering will occur until this
				method is called again with a parameter of false.
			*/
			virtual void _suppressShadows(bool suppress); 

			/** Are shadows suppressed? 
			@see _suppressShadows
			*/
			virtual bool _areShadowsSuppressed(void) const;

			/** Render the objects in a given queue group 
			@remarks You should only call this from a RenderQueueInvocation implementation
			*/
			virtual void _renderQueueGroupObjects(Ogre::RenderQueueGroup* group, 
				Ogre::QueuedRenderableCollection::OrganisationMode om);

			/** Advanced method for supplying an alternative visitor, used for parsing the
				render queues and sending the results to the renderer.
			@remarks
				You can use this method to insert your own implementation of the 
				QueuedRenderableVisitor interface, which receives calls as the queued
				renderables are parsed in a given order (determined by RenderQueueInvocationSequence)
				and are sent to the renderer. If you provide your own implementation of
				this visitor, you are responsible for either calling the rendersystem, 
				or passing the calls on to the base class implementation.
			@note
				Ownership is not taken of this pointer, you are still required to 
				delete it yourself once you're finished.
			@param visitor Your implementation of SceneMgrQueuedRenderableVisitor. 
				If you pass 0, the default implementation will be used.
			*/
//			void setQueuedRenderableVisitor(SceneManager::SceneMgrQueuedRenderableVisitor* visitor);

			/** Gets the current visitor object which processes queued renderables. */
//			SceneManager::SceneMgrQueuedRenderableVisitor* getQueuedRenderableVisitor(void) const;


			/** Get the rendersystem subclass to which the output of this Scene Manager
				gets sent
			*/
			Ogre::RenderSystem *getDestinationRenderSystem();

			/** Gets the current viewport being rendered (advanced use only, only 
				valid during viewport update. */
			Ogre::Viewport* getCurrentViewport(void) const;

			/** Returns a visibility boundary box for a specific camera. */
			const Ogre::VisibleObjectsBoundsInfo& getVisibleObjectsBoundsInfo(const Ogre::Camera* cam) const;

			/**  Returns the shadow caster AAB for a specific light-camera combination */
			const Ogre::VisibleObjectsBoundsInfo& getShadowCasterBoundsInfo(const Ogre::Light* light) const;

			//********** END:  OGRE::SCENEMANAGER METHODS ***********//

			//********** NXOGRE::SCENE METHODS ************//

			/**  getNxScene
			     Returns a copy of a pointer of the NxScene which the Scene works with.
			   
			     @return NxScene The NxScene's pointer
			 */
			NxScene* getNxScene();

			/** getWorld
			    Returns a copy of the World which the Scene is part of.
			   
			    @return World The World itself.
			 */
			NxOgre::World* getWorld();


			/**	setSceneController
			   	 Sets the Controller used for Simulation and Rendering of the NxScene. These can be Variable, Fixed,
			   	 or SuperFixed. You can use your own SceneController if you wish, otherwise the SceneController should
			     be specified in the SceneParams "time-step-method" with Fixed, Variable or SuperFixed as an option.
			   
			   	Garbage Collection
			   	 SceneController instance will be deleted on the destruction of the Scene.	
			   
			     @params SceneController Instance of the SceneController to use.
			 */  	
			void setSceneController(NxOgre::SceneController*);
			

			/**  Simulate
			   	  Advances the Simulation of the Scene, The World will automatically perform this operation for you. 
			   
			     @params NxReal(Time/Seconds)	Time to advance/Time since last Simulation		
			 */  	
			void simulate(NxReal);


			/**  Render
			   	  Moves and Orientates all Scene Nodes, Update Meshes and anything related to updating the visual
			   	  aspect of the Scene. World will automatically perform this operation for you.
			   
			      @params NxReal(Time/Seconds)	Time to advance/Time since last Render
			 */   	
			void render(NxReal);


			/**	 save
				  Save the current Scene and contents to a SceneBlueprint
			 */
			//NxOgre::Blueprints::SceneBlueprint  save();

			/**	 getSimType
			   	  Returns the NxSimulationType (Hardware/Software) of the Scene.
			   
			   	 @returns NxSimulationType		Simulation Type
			 */	 	
			//NxSimulationType getSimType() const;


			/**	  setGravity
				   Sets the gravitional constant for the Scene. 
			
				  @params	Ogre::Vector3(Acceleration/metres per second)	Gravitional Constant
			 */  	
			void setGravity(const Ogre::Vector3&);


			/**   getGravity
			   	   Gets the gravitional constant for the Scene. 
			   
			   	  @return	Ogre::Vector3(Acceleration/metres per second)	Gravitional Constant
			 */	  	
			Ogre::Vector3 getGravity() const;


			/**	  createActor
			   	   Text
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params identifier		Unique name of the Actor. (Leave blank for a auto-generated identifier)
			   	  @params ShapeBlueprint*	The first shape to use for the Actor (new ShapeName(...))
			   	  @params Pose				Global Pose of the Actor
			   	  @params ActorParams		ActorParams for this actor
			   
			   	 @return The created Actor
			 */	 	
			NxOgre::Actor*	createActor(const NxOgre::NxString& identifier, NxOgre::ShapeBlueprint*, const NxOgre::Pose&, NxOgre::ActorParams = NxOgre::ActorParams());


			// Ex
			void	batchCreateActors(const NxOgre::NxString& identifierPattern, NxU32 nbActors, NxOgre::ShapeBlueprint*, const NxOgre::Pose& poseOrigin, const NxOgre::Pose& poseDifference, NxOgre::Scene::BatchActionTimeFrame = NxOgre::Scene::BT_NOW, NxOgre::ActorParams = NxOgre::ActorParams());
			
			/**   destroyActor
			   	   Text
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params identifier		Unique name of the Actor to destroy.
			 */	  	
			void	destroyActor(const NxOgre::NxString&);


			// Ex
			void	batchDestroyActor(const NxOgre::NxString& identifier, NxOgre::Scene::BatchActionTimeFrame = NxOgre::Scene::BT_NEXT_AVAILABLE_BATCH);
			
			// Ex
			//void	batchDestroyActors(const NxOgre::NxString& identifierPattern, NxU32 nbActors, NxOgre::Scene::BatchActionTimeFrame = NxOgre::Scene::BT_NEXT_AVAILABLE_BATCH);
	
			// Ex
			void	batchDestroyActors(NxOgre::Actors, NxOgre::Scene::BatchActionTimeFrame = NxOgre::Scene::BT_NEXT_AVAILABLE_BATCH);

			/**   	  getActor
			   	   Returns a pointer to the Actor. If the Actor does not exist, then the Pointer value is NULL.
			   
			   	  @params identifier		Unique name of the Actor to fetch.
			   	  @return Actor				The Actor or NULL.
			 */	  	
			NxOgre::Actor*	getActor(const NxOgre::NxString&);


			/**	  getActors
			   	   Returns a pointer to the list of Actors in this Scene. Since your working with the "Master" list
			   	   of actors, you should be careful when handling with those Actors during a FrameSimulation. When
			   	   when adding or cloning Actors within a loop with the Master Loop may make the application freeze.
			   
			   	  @Hint
			   	   Use "Actors actor; mScene->getActors()->copy(actors);" to create a copy of the list of Actors.
			   
			   	  @params Actors The Master list of Actors.
			 */	  	
			NxOgre::Actors*	getActors();


			// Ex
			NxOgre::Actors getActorsFromIdentifier(NxOgre::NxStringOperator, const NxOgre::NxString& identifierPattern);
			
			// Ex
			NxOgre::Actors getActorsFromFrame(NxOgre::NxComparisonOperator, NxU32 frame);

			// Ex
			NxOgre::Actors& getActorsFromRegion(NxOgre::SimpleShape*, NxShapesType);
			
			// Ex
			NxOgre::Actors& getActorsFromLastRegion(NxShapesType);

			// Ex
			NxOgre::Actors getActorsFromRaycast(Ogre::Vector3 position, Ogre::Vector3 normal, NxReal range);

			/**   getNbActors
			   	   Gets the number of NxOgre Actors within the Scene. This does not keep account of NxActors with
			   	   a different UserData class such as Triggers or ForceFields, or manually created NxActors.
			   
			   	  @params NxU32		Total count of NxOgre Actors in this Scene.
			 */  	  	
			NxU32	getNbActors() const;


			/**   	   createBody
			   		Creates a Body (An Actor with an SceneNode) within a Scene. See Scene::createActor for more information.
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params meshIdentifier	Mesh of the first Entity in the SceneNode to use. (Leave blank for no mesh)
			   	  @see	  Scene::createActor for other Arguments.
			   
			   	 @return The created Body
			  */
			NxOgre::Body*	createBody(const NxOgre::NxString& meshIdentifier, NxOgre::ShapeBlueprint*, const NxOgre::Pose&, NxOgre::ActorParams = "");
			
			// Ex
			void	batchCreateBodies(const NxOgre::NxString& identifierPattern, const NxOgre::NxString& visualData, NxU32 nbActors, NxOgre::ShapeBlueprint*, const NxOgre::Pose& poseOrigin, const NxOgre::Pose& poseDifference, NxOgre::Scene::BatchActionTimeFrame = NxOgre::Scene::BT_NOW, NxOgre::ActorParams = NxOgre::ActorParams());
			

			/**   destroyBody
			   	   Destroys a Body. This function is the same as destroyActor.
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params identifier		Unique name of the Body to destroy.
			 */  	
			void	destroyBody(const NxOgre::NxString&);
			
			//////////////////////////////////////////////////////////////////////////////
			
			/**   createTrigger
			   	   Text
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params identifier		Unique name of the Body to destroy.
			 */
			NxOgre::Trigger* createTrigger(const NxOgre::NxString& identifier, NxOgre::ShapeBlueprint*, const NxOgre::Pose&, NxOgre::ActorParams = "");


			/**   destroyTrigger
			   	   Destroys a Trigger. This function is the same as destroyActor.
			   
			   	  Containers and Garbage Collection
			   	   Text
			   
			   	  @params identifier		Unique name of the Body to destroy.
			 */
			void	 destroyTrigger(const NxOgre::NxString&);
			
			NxOgre::Trigger* getTrigger(const NxOgre::NxString&);
			NxOgre::Triggers* getTriggers();
			NxU32	 getNbTriggers();

			//////////////////////////////////////////////////////////////////////////////

			NxOgre::SphericalJoint*		createSphericalJoint(NxOgre::Actor*, NxOgre::Actor*, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
			NxOgre::SphericalJoint*		createSphericalJoint(NxOgre::Actor*, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());

			NxOgre::RevoluteJoint*		createRevoluteJoint(NxOgre::Actor*, NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
			NxOgre::RevoluteJoint*		createRevoluteJoint(NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
		
			NxOgre::PrismaticJoint*		createPrismaticJoint(NxOgre::Actor*, NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
			NxOgre::PrismaticJoint*		createPrismaticJoint(NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
	
			NxOgre::CylindricalJoint*	createCylindricalJoint(NxOgre::Actor*, NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
			NxOgre::CylindricalJoint*	createCylindricalJoint(NxOgre::Actor*, const Ogre::Vector3 &axis, const Ogre::Vector3 &anchor, NxOgre::JointParams = NxOgre::JointParams());
		
			NxOgre::FixedJoint*		createFixedJoint(NxOgre::Actor*, NxOgre::Actor*, NxOgre::JointParams = NxOgre::JointParams());
			NxOgre::FixedJoint*		createFixedJoint(NxOgre::Actor*, NxOgre::JointParams = NxOgre::JointParams());
			

			//////////////////////////////////////////////////////////////////////////////

			void releaseJoint(NxOgre::Joint*);
			void releaseJoint(NxOgre::NxJointID);

			//////////////////////////////////////////////////////////////////////////////

#if (NX_USE_CHARACTER_API == 1)
			NxOgre::Character* createCharacter(const NxOgre::NxString &name, NxOgre::Pose p, NxOgre::CharacterParams cp);
			void  destroyCharacter(const NxOgre::NxString&);
#endif

			//////////////////////////////////////////////////////////////////////////////

			NxOgre::Material*		createMaterial(const NxOgre::NxString& name);
			void			destroyMaterial(const NxOgre::NxString& name);
			NxOgre::Material*		getMaterial(const NxOgre::NxString&);
			NxOgre::Material*		getMaterial(NxMaterialIndex);
			NxOgre::MaterialList*	getMaterials();
			NxU32			getNbMaterials();
			NxMaterialIndex getMaterialIndex(const NxOgre::NxString&);

			
			//void addMaterialPair(Ogre::Material*, NxOgre::Material*);
			//void addMaterialPair(const NxOgre::NxString& ogre, const NxOgre::NxString& nxogre);
			//void addMaterialPairsFromFile(const NxOgre::NxString& ogre, const NxOgre::NxString& nxogre);

			//////////////////////////////////////////////////////////////////////////////

			NxOgre::ActorGroup*	createActorGroup(const NxOgre::NxString& name);
			void		destroyActorGroup(const NxOgre::NxString& name);
			NxU32		getNbActorGroups() const;
			NxOgre::ActorGroups* getActorGroups();
			NxOgre::ActorGroupsByIndex* getActorGroupsByIndex();
			NxOgre::ActorGroup*	getActorGroup(const NxOgre::NxString& name);

			//////////////////////////////////////////////////////////////////////////////
			
			NxOgre::ShapeGroup*	createShapeGroup(const NxOgre::NxString& name);
			void		destroyShapeGroup(const NxOgre::NxString& name);
			NxU32		getNbShapeGroups() const;
			NxOgre::ShapeGroups* getShapeGroups();
			NxOgre::ShapeGroupsByIndex* getShapeGroupsByIndex();
			NxOgre::ShapeGroup*	getShapeGroup(const NxOgre::NxString& name);

			//////////////////////////////////////////////////////////////////////////////
			
#if (NX_SDK_VERSION_NUMBER >= 272) 
			NxOgre::DominanceGroup*	createDominanceGroup(const NxOgre::NxString& name);
			void		setDominanceGroupPair(const NxOgre::NxString& AGroup, const NxOgre::NxString& BGroup, NxReal ADominance, NxReal BDominance);
			void		setDominanceGroupPair(NxOgre::DominanceGroup* AGroup, NxOgre::DominanceGroup* BGroup, NxReal ADominance, NxReal BDominance);
			void		destroyDominanceGroup(const NxOgre::NxString& name);
			NxU32		getNbDominanceGroups() const;
			NxOgre::DominanceGroups* getDominanceGroups();
			NxOgre::DominanceGroupsByIndex* getDominanceGroupsByIndex();
			NxOgre::DominanceGroup*	getDominanceGroup(const NxOgre::NxString& name);
#endif
			//////////////////////////////////////////////////////////////////////////////

			void addFloor();

			/** Add a collision floor in the xz plane at the specified y position. */
			void addFloor(float y);

			//////////////////////////////////////////////////////////////////////////////

			// setStaticGeometry
			//  All future Actors with visualisations that are static, will now use the StaticGeometry
			//  Remember to build the static-geometry after adding all your static actors.
			// @param Ogre::StaticGeometry Current StaticGeometry to work with.
			void setStaticGeometry(Ogre::StaticGeometry*);

			// getStaticGeometry
			//  Returns the current StaticGeometry
			Ogre::StaticGeometry* getStaticGeometry();
			
			// removeStaticGeometry
			//  Removes the StaticGeometry pointer from the Scene. It does not adjust the static actors
			//  or deletes the StaticGeometry, it just sets the Scene's pointer to your StaticGeometry
			//  to null.
			void removeStaticGeometry();

			//////////////////////////////////////////////////////////////////////////////

#if (NX_USE_FLUID_API == 1)

			//NxOgre::Fluid*	createFluid(const NxOgre::Pose&, NxOgre::FluidParams);
			//void	destroyFluid(const NxOgre::NxString&);
			//NxU32	getNbFluids()	const;
			//NxOgre::Fluids*	getFluids();
#endif

			//////////////////////////////////////////////////////////////////////////////
		
#if (NX_USE_CLOTH_API == 1)
			NxOgre::Actor*	createDeformableActor(const NxOgre::NxString& meshName, NxOgre::ShapeBlueprint* roughShape, const NxOgre::Pose&, NxOgre::ActorParams, NxOgre::ClothParams, NxReal impulseThreshold, NxReal penetrationDepth = 0.0f);
			NxOgre::Cloth*	createCloth(const NxOgre::NxString& identifier, const NxOgre::Pose&, NxOgre::ClothParams);
			NxOgre::Cloth*	createCloth(const NxOgre::NxString& identifier, const NxOgre::NxString& meshName, const NxOgre::Pose&, NxOgre::ClothParams);
			void	destroyCloth(const NxOgre::NxString&);
			NxOgre::Cloths*	getCloths();
			NxU32 getNbCloths();
#endif
	
			//////////////////////////////////////////////////////////////////////////////

#if (NX_USE_SOFTBODY_API == 1)
			NxOgre::SoftBody*	createSoftBody(const NxOgre::NxString& TetAndMeshFilePrefix, const NxOgre::Pose&, NxOgre::SoftBodyParams);
			NxOgre::SoftBody*	createSoftBody(NxReal width, NxReal height, NxReal, const NxOgre::Pose&, NxOgre::SoftBodyParams);
			void		destroySoftBody(const NxOgre::NxString& identifier);
			NxU32		getNbSoftBodies();
			NxOgre::SoftBodies*	getSoftBodies();
#endif
	
			//////////////////////////////////////////////////////////////////////////////

#if (NX_USE_FORCEFIELD_API == 1)
			NxOgre::ForceField*		createForceField(const NxOgre::NxString& identifier, const NxOgre::Pose&, NxOgre::ShapeBlueprint* actorShape, NxOgre::ActorParams, NxOgre::ForceFieldParams);
			void			destroyForceField(const NxOgre::NxString&);
			NxU32			getNbForceFields();
			NxOgre::ForceFields*	getForceFields();
#endif

			//////////////////////////////////////////////////////////////////////////////

			void		_registerHelper(const NxOgre::NxString& name, NxOgre::Helper*);
			void		_unregisterHelper(const NxOgre::NxString&);

			void		idle();

			//********** END:  NXOGRE::SCENE METHODS ************//

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock rwLock;
			/** Read/write mutex on the Ogre::SceneManager instance */
			mutable Poco::RWLock rwLockSceneManager;
			/** Read/write mutex on the NxOgre::Scene instance */
			mutable Poco::RWLock rwLockNxScene;
			/** The NxOgre::Scene instance */
			NxOgre::Scene *nxScene;
			/** The Ogre::SceneManager instance */
			Ogre::SceneManager* sceneManager;
			/** The NxOgre::World instance */
			NxOgre::World *world;

		private:
			/** Flag indicating whether the NxOgre::Scene was created in the constructor. */
			bool nxSceneCreated;
			/** Flag indicating whether the Ogre::SceneManager was created in the constructor. */
			bool sceneManagerCreated;
	};

	// inlines
	inline void Scene::acquireLockOnOgreSceneManager(bool write) const
	{
		if (write)
		{
			rwLockSceneManager.writeLock();
		}
		else
		{
			rwLockSceneManager.readLock();
		}
	}

	inline void Scene::acquireLockOnNxOgreScene(bool write) const
	{
		if (write)
		{
			rwLockNxScene.writeLock();
		}
		else
		{
			rwLockNxScene.readLock();
		}
	}

	inline void Scene::releaseLockOnOgreSceneManager() const
	{
		rwLockSceneManager.unlock();
	}

	inline void Scene::releaseLockOnNxOgreScene() const
	{
		rwLockNxScene.unlock();
	}

	inline const NxOgre::Scene* Scene::getNxOgreScene() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxScene;
	}

	inline const Ogre::SceneManager* Scene::getOgreSceneManager() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return sceneManager;
	}

	inline NxOgre::Scene* Scene::getNxOgreScene()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return nxScene;
	}

	inline Ogre::SceneManager* Scene::getOgreSceneManager()
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return sceneManager;
	}

	inline bool Scene::operator==(const Scene& otherScene)
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return (this->instanceName == otherScene.getName());
	}
} // Myoushu

#endif


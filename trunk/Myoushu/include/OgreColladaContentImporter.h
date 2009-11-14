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
 * @file OgreColladaContentImporter.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef OGRE_COLLADA_CONTENT_IMPORTER_H
#define OGRE_COLLADA_CONTENT_IMPORTER_H

#include "Poco/RWLock.h"
#include "Ogre.h"
#include "OgreCollada.h"

#include "ContentImporter.h"
#include "Scene.h"

namespace Myoushu
{
	/**
	 * ContentImporter implementation using the OgreCollada library. This importer can be used to load
	 * meshes and scenes from collada (.dae) files.
	 */
	class MYOUSHU_API OgreColladaContentImporter : public ContentImporter, public OgreCollada::IResourceNotification
	{
		public:
			/**
			 * Constructor. Create a new instance of the content importer.
			 * @param scene The Scene instance to load content into, 
			 *				defaults to NULL.
			 */
			OgreColladaContentImporter(Scene *scene = NULL);

			/** Destructor */
			virtual ~OgreColladaContentImporter();

			/**
			 * Import content from the specified file
			 * to the scene previously specified.
			 * @throws Exception::E_NULL_POINTER if scene is NULL.
			 * @throws Exception::E_FILE_NOT_FOUND if the file could not be found.
			 * @throws Exception::E_UNEXPECTED_TYPE if the file is not compatible.
			 */
			void importContent(const std::string& path) throw (Exception);

			/**
			 * Get the list of scene nodes imported from the collada file.
			 * @return A const pointer to a std::list of Ogre::SceneNode instances.
			 */
			const std::list<Ogre::SceneNode*>* getSceneNodes() const;

			/**
			 * Get the list of entities imported from the collada file.
			 * @return A const pointer to a std::list of Ogre::Entity instances.
			 */
			const std::list<Ogre::Entity*>* getEntity() const;

			/**
			 * Get the list of cameras imported from the collada file.
			 * @return A const pointer to a std::list of Ogre::Camera instances.
			 */
			const std::list<Ogre::Camera*>* getCameras() const;

			/**
			 * Get the list of lights imported from the collada file.
			 * @return A const pointer to a std::list of Ogre::Light instances.
			 */
			const std::list<Ogre::Light*>* getLights() const;

			/**
			 * Get the list of resources imported from the collada file.
			 * @return A const pointer to a std::list of Ogre::Resource instances.
			 */
			const std::list<Ogre::Resource*>* getResources() const;

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;
			/** OgreCollada Importer/exporter instance */
			OgreCollada::ImpExp *ogreColladaImporter;
			/** List of scene nodes created in the last import operation. */
			std::list<Ogre::SceneNode*> sceneNodes;
			/** List of entites created in the last import operation. */
			std::list<Ogre::Entity*> entities;
			/** List of cameras created in the last import operation. */
			std::list<Ogre::Camera*> cameras;
			/** List of lights created in the last import operation. */
			std::list<Ogre::Light*> lights;
			/** List of resources created in the last import operation. */
			std::list<Ogre::Resource*> resources;

			/** Clears the scene nodes, entities, cameras, lights and resources lists. */
			void clearLists();

			// OgreCollada IResourceNotification overrides
			/**
			 * Called when a scene node is created.
			 * @param pNode The Ogre::SceneNode that has been created.
			 * @param pFColladaSceneNode The FCollada scene node that was created.
			 */
			void sceneNodeCreated(Ogre::SceneNode* pNode, FCDSceneNode* pFColladaSceneNode);

			/**
			 * Called when a scene node is created.
			 * @param pEntity The Ogre::Entity that has been created.
			 * @param pFColladaParentNode The FCollada scene node that owns the entity.
			 */
			void entityCreated(Ogre::Entity* pEntity, FCDSceneNode* pFColladaParentNode);

			/**
			 * Called when a camera is created.
			 * @param pCam The Ogre::Camera that has been created.
			 * @param pFColladaCamera The FCollada camera that was created.
			 */
			void cameraCreated(Ogre::Camera* pCam, FCDCamera* pFColladaCamera);

			/**
			 * Called when a light is created.
			 * @param pLight The Ogre::Light that has been created.
			 * @param pFColladaLight The FCollada light that was created.
			 */
			void lightCreated(Ogre::Light* pLight, FCDLight* pFColladaLight);

			/**
			 * Called when a resource is created.
			 * @param pResource The Ogre::Resource that has been created.
			 * @param pFColladaObject The FCDEntity instance that was created.
			 */
			void resourceCreated(Ogre::Resource* pResource, FCDEntity* pFColladaObject);

			/**
			 * Called when the default texture is set.
			 * @param rImage Ogre::Image with the default texture.
			 */
			void getDefaultTexture(Ogre::Image& rImage);
	};

	// inlines

	inline const std::list<Ogre::SceneNode*>* OgreColladaContentImporter::getSceneNodes() const
	{
		return &sceneNodes;
	}

	inline const std::list<Ogre::Entity*>* OgreColladaContentImporter::getEntity() const
	{
		return &entities;
	}

	inline const std::list<Ogre::Camera*>* OgreColladaContentImporter::getCameras() const
	{
		return &cameras;
	}

	inline const std::list<Ogre::Light*>* OgreColladaContentImporter::getLights() const
	{
		return &lights;
	}

	inline const std::list<Ogre::Resource*>* OgreColladaContentImporter::getResources() const
	{
		return &resources;
	}

} // namespace Myoushu

#endif

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
 * @file ContentImporter.h
 * @author ME Chamberlain
 * @date July 2008
 */

#ifndef CONTENT_IMPORTER_H
#define CONTENT_IMPORTER_H

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "Platform.h"
#include "Scene.h"
#include "Exception.h"
#include "NamedInstance.h"
#include "NamedObject.h"

namespace Myoushu
{
	/** 
	 * This abstract class serves as the base class for any classes that
	 * load content (models, scenes, meshes) from files into the engine.
	 */
	class MYOUSHU_API ContentImporter : public NamedInstance, public NamedObject<ContentImporter>, public Poco::RefCountedObject
	{
		public:

			/**
			 * Constructor.
			 * @param name The name of this ContentImporter instance.
			 */
			ContentImporter(const std::string& name = "ContentImporter");

			/** Destructor */
			virtual ~ContentImporter();

			CLASS_NAME_FUNCTIONS(ContentImporter);

			/**
			 * Pure virtual function, can be used by deriving classes to implement some form of
			 * initialisation if required. This function is not automatically called by the constructor.
			 */
			virtual void initialize() = 0;

			/**
			 * Pure virtual function, can be used by deriving classes to implement some form of shutdown
			 * process if required. This function is not automatically called by the destructor.
			 */
			virtual void shutdown() = 0;

			/**
			 * Virtual method, should import content from the specified file
			 * to the scene previously specified.
			 * @param pScene The Scene instance to load the content into.
			 * @param path The file to import.
			 * @param resourceGroup The resource group that contains the file. Defaults to "".
			 * @param pRootSceneNode An optional Ogre::SceneNode to use as the root node for the imported content. Defaults to NULL.
			 * @param importPrefix An optional prefix that will be added to the names of all imported content. Defaults to "".
			 * @throws Exception::E_NULL_POINTER if pScene is NULL.
			 * @throws Exception::E_FILE_NOT_FOUND if the file could not be found.
			 * @throws Exception::E_UNEXPECTED_TYPE if the file is not compatible.
			 */
			virtual void importContent(Scene *pScene, const std::string& path, const std::string& resourceGroup = "", Ogre::SceneNode *pRootSceneNode = NULL, const std::string &importPrefix = "") throw (Exception) = 0;
	};

} // namespace Myoushu

#endif

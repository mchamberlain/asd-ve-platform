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
 * @file MyoushuDotSceneProcessorImpl.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_DOTSCENE_PROCESSOR_IMPL_H
#define MYOUSHU_DOTSCENE_PROCESSOR_IMPL_H

#include "XNPPrerequisites.h"
#include "dotScenePrerequisites.h"
#include "DotSceneProcessorImpl.h"

#include "ContentImporter.h"
#include "Scene.h"
#include "VideoTaskManager.h"
#include "NamedObject.h"

#include "MyoushuDotScenePlatform.h"

namespace Myoushu
{
	/**
	 * This class is an implementation of the Ogre::dsi::DotSceneProcessorImpl interface, used to load .scene files into Ogre. In fact, this class is mostly a direct copy
	 * of the Ogre::dsi::DotSceneProcessorImpl_v1_0_0 class. The design of the Ogre::dsi::DotSceneProcessorImpl_v1_0_0 class made it difficult
	 * to modify for our needs by only using inheritence, so we opted to use it as a base for our own processor implementation.
	 */
	class MYOUSHU_DOTSCENE_API MyoushuDotSceneProcessorImpl : public ContentImporter, public Ogre::dsi::DotSceneProcessorImpl, public NamedObject<MyoushuDotSceneProcessorImpl>
	{
		public:
			typedef XmlNodeProcessing::XmlNodeProcessor XmlNodeProcessor;
			typedef XmlNodeProcessing::XmlNodeProcessorTreeBuilder XmlNodeProcessorTreeBuilder;
			typedef XmlNodeProcessing::CommonParamsOfXmlNodeProcessors CommonParamsOfXmlNodeProcessors;

			/** Nullary constructor */
			MyoushuDotSceneProcessorImpl(const std::string& name = "MyoushuDotSceneProcessorImpl");

			/** Destructor */
			virtual ~MyoushuDotSceneProcessorImpl();

			CLASS_NAME_FUNCTIONS(MyoushuDotSceneProcessorImpl);

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
			virtual void importContent(Scene *pScene, const std::string& path, const std::string& resourceGroup = "", Ogre::SceneNode *pRootSceneNode = NULL, const std::string &importPrefix = "") throw (Exception);

			/** @copydoc DotSceneProcessorImpl::initialize */
			virtual void initialize();

			/// @copydoc DotSceneProcessorImpl::load
			virtual void load(
				TiXmlDocument*				pXMLDoc,
				Ogre::SceneManager*			pSceneManager,
				Ogre::RenderWindow*			pRWin,
				const Ogre::String&			groupName,
				const Ogre::String&			strNamePrefix,
				Ogre::SceneNode*			pRootNode			= NULL,
				bool						doMaterials			= false,
				bool						forceShadowBuffers	= false,
				Ogre::dsi::DotSceneInfo**	ppDotSceneInfo		= 0);

			virtual void loadFile(
				const Ogre::String&			fileName,
				Scene*						pScene,
				Ogre::RenderWindow*			pRWin,
				const Ogre::String&			groupName,
				const Ogre::String&			strNamePrefix,
				Ogre::SceneNode*			pRootNode			= NULL,
				bool						doMaterials			= false,
				bool						forceShadowBuffers	= false,
				Ogre::dsi::DotSceneInfo**	ppDotSceneInfo		= 0);

			/// @copydoc DotSceneProcessorImpl::shutdown
			virtual void shutdown();

			const CommonParamsOfXmlNodeProcessors*	getCommonParams() const;
			CommonParamsOfXmlNodeProcessors*		getCommonParams();
			const Ogre::dsi::DotSceneNodeProcessorTreeBuilder*	getTreeBuilder() const;
			Ogre::dsi::DotSceneNodeProcessorTreeBuilder*		getTreeBuilder();

		private:
			Ogre::SceneNode*	mpRoot;
			Scene*				mpScene;
			Ogre::SceneManager* mpSceneManager;
			Ogre::RenderWindow*	mpWin;
			bool				mDoMats;
			bool				mShadow;
			bool				mDoInfo;
			TiXmlDocument*		mpXMLDoc;

			CommonParamsOfXmlNodeProcessors*				mCommonParamsOfXmlNodeProcessors;
			Ogre::dsi::DotSceneNodeProcessorTreeBuilder*	mDotSceneNodeProcessorTreeBuilder; 
			XmlNodeProcessor*								mRootXmlNodeProcessor;
	};

	// inlines
	inline void MyoushuDotSceneProcessorImpl::importContent(Scene *pScene, const std::string& path, const std::string& resourceGroup, Ogre::SceneNode *pRootSceneNode, const std::string &importPrefix) throw (Exception)
	{
		loadFile(path, pScene, VideoTaskManager::getSingleton().getRenderWindow(), resourceGroup, importPrefix, pRootSceneNode, true, true);
	}

} // namespace Myoushu

#endif

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
 * @file MyoushuDotSceneProcessorImpl.cpp
 * @author ME Chamberlain
 * @date February 2009
 */

#include "Exception.h"

#include "MyoushuDotSceneProcessorImpl.h"
#include "MyoushuDotSceneNodeProcessorTreeBuilder.h"

namespace Myoushu
{
	CLASS_NAME(MyoushuDotSceneProcessorImpl, "Myoushu::MyoushuDotSceneProcessorImpl");

	MyoushuDotSceneProcessorImpl::MyoushuDotSceneProcessorImpl(const std::string& name) 
		:   ContentImporter(name),
			mpRoot(NULL),
			mpScene(NULL),
			mpSceneManager(NULL),
			mpWin(NULL),
			mDoMats(false),
			mShadow(false),
			mDoInfo(false),
			mpXMLDoc(NULL),
			mCommonParamsOfXmlNodeProcessors(NULL),
			mDotSceneNodeProcessorTreeBuilder(NULL), 
			mRootXmlNodeProcessor(NULL)

	{
	}

	MyoushuDotSceneProcessorImpl::~MyoushuDotSceneProcessorImpl()
	{
		shutdown();
	}

		//***************************************************************************************************
		void MyoushuDotSceneProcessorImpl::initialize()
		{
			// Create common params of xml node processors and build the xml node processor tree.
			mCommonParamsOfXmlNodeProcessors = new CommonParamsOfXmlNodeProcessors;

			mDotSceneNodeProcessorTreeBuilder	= new MyoushuDotSceneNodeProcessorTreeBuilder(mCommonParamsOfXmlNodeProcessors);
			mRootXmlNodeProcessor				= mDotSceneNodeProcessorTreeBuilder->buildTree();
		}
		//***************************************************************************************************

		void MyoushuDotSceneProcessorImpl::load(
			TiXmlDocument*				pXMLDoc,
			Ogre::SceneManager*			pSceneManager,
			Ogre::RenderWindow*			pRWin,
			const Ogre::String&			groupName,
			const Ogre::String&			strNamePrefix,
			Ogre::SceneNode*			pRootNode,
			bool						doMaterials,
			bool						forceShadowBuffers,
			Ogre::dsi::DotSceneInfo**	ppDotSceneInfo
			)
		{
			// This version of the load function is not supported, throw a deprecated exception.
			throw Exception(Exception::E_DEPRECATED, "MyoushuDotSceneProcessorImpl::load()");
		}

		//***************************************************************************************************
		void MyoushuDotSceneProcessorImpl::loadFile(
			const Ogre::String&			fileName,
			Scene*						pScene,
			Ogre::RenderWindow*			pRWin,
			const Ogre::String&			groupName,
			const Ogre::String&			strNamePrefix,
			Ogre::SceneNode*			pRootNode,
			bool						doMaterials,
			bool						forceShadowBuffers,
			Ogre::dsi::DotSceneInfo**	ppDotSceneInfo
			)
		{
			Ogre::SceneManager *pSceneManager;

			// ------------------------------------------------ Copy parameters to member variables ------------------------------------------------
			assert(pScene); assert(pRWin);
			pSceneManager	= pScene->getOgreSceneManager();
			assert(pSceneManager);
			this->mpSceneManager	= pSceneManager; // This is a must.
			this->mpWin			= pRWin;		 // This is a must.

			// Create DotSceneInfo instance.
			if ( ppDotSceneInfo )
			{
				// If *ppDotSceneInfo is null, then user hasn't pre-created DotSceneInfo (this usually happens when he don't want us to
				// upgrade an already existing structure), so create a new DotSceneInfo instance.
				if ( !(*ppDotSceneInfo) ) *ppDotSceneInfo = new Ogre::dsi::DotSceneInfo;
			}

			// Load the .scene.
			this->mpXMLDoc = new TiXmlDocument(fileName);

			if (!this->mpXMLDoc->LoadFile()) 
			{ 
				this->mpXMLDoc->ClearError(); 

				// Try to look for the file in the resource paths... 
				Ogre::DataStreamPtr pStream = Ogre::ResourceGroupManager::getSingleton().openResource(fileName, groupName); 
				if(pStream->size()) 
				{
					Ogre::String s = pStream->getAsString() + "\0"; 
					this->mpXMLDoc->Parse(s.c_str()); 

					// Check for errors .
					if (this->mpXMLDoc->Error()) 
					{ 
						Ogre::String errDesc = mpXMLDoc->ErrorDesc(); 
						delete this->mpXMLDoc; 
						OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
									"An error occured while loading the .scene file named \"" + fileName + "\" :\n" + errDesc,
									"DotSceneProcessor::load"); 
					}
				}
				else
					// Since ResourceGroupManager::openResource() throws an exception if the file can not be opened, or the resource
					// group not found, this should be an invalid file (e.g. a file with 0 size).
					OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
								"An error occured while loading the .scene file named \"" + fileName + "\":\n "
								"The opened file has the size 0?!",
								"DotSceneProcessor::load"); 
			} 
			// say what we're doing to the interested public 
			this->updateProgressListeners("loading \"" + fileName + "\""); 

			// Do the root node.
			if (pRootNode)
				mpRoot = pRootNode;
			else
			{
				mpRoot = mpSceneManager->getRootSceneNode();
				if (!mpRoot)
					OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
								"Something went wrong while creating the child of the SceneRoot node.\nWEIRD", "MyoushuDotSceneProcessorImpl::load");
			}
			this->mDoMats		= doMaterials;
			this->mShadow		= forceShadowBuffers;
			this->mDoInfo		= ppDotSceneInfo != 0;
			this->mGroupName	= groupName;


			// ------------------------------------------------------- Set common parameters -------------------------------------------------------
			mCommonParamsOfXmlNodeProcessors->setParameter("Scene", pScene);
			mCommonParamsOfXmlNodeProcessors->setParameter("SceneManager", pSceneManager);
			mCommonParamsOfXmlNodeProcessors->setParameter("RootSceneNode", 0);

			//			mCommonParamsOfXmlNodeProcessors->setParameter("ResourceGroup", &ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
			mCommonParamsOfXmlNodeProcessors->setParameter("ResourceGroup", 0);
			//			mCommonParamsOfXmlNodeProcessors->setParameter("ResourceGroup", new String("UncreatedTestResourceGroup"));
			//			ResourceGroupManager::getSingleton().createResourceGroup("CreatedTestResourceGroup");
			//			mCommonParamsOfXmlNodeProcessors->setParameter("ResourceGroup", new String("CreatedTestResourceGroup"));
			//			mCommonParamsOfXmlNodeProcessors->setParameter("ResourceGroup", new String(""));

			mCommonParamsOfXmlNodeProcessors->setParameter("RenderWindow", pRWin);
			//mCommonParamsOfXmlNodeProcessors->setParameter("NamePrefix", new String("Test_"));
			mCommonParamsOfXmlNodeProcessors->setParameter("NamePrefix", new Ogre::String(strNamePrefix.c_str()));
			
			if ( ppDotSceneInfo )
				mCommonParamsOfXmlNodeProcessors->setParameter("DotSceneInfo", *ppDotSceneInfo);
			else // If ppDotSceneInfo is set to 0, then do not give information about the loaded scene at all.
				mCommonParamsOfXmlNodeProcessors->setParameter("DotSceneInfo", 0);


			// ----------------------------------------------------------- Load the scene ----------------------------------------------------------
			mRootXmlNodeProcessor->parseElement(0, mpXMLDoc->RootElement());

			// --- New testing version.
			// TESTING PART!!!
			// Test if resource declarations are created for resources loaded indirectly due to calls of e.g.
			// SceneManager::createEntity().
				//ResourceGroupManager::ResourceDeclarationList resourceDeclarationList = 
				//	ResourceGroupManager::getSingleton().getResourceDeclarationList(*((String*)mCommonParamsOfXmlNodeProcessors->getParameter("ResourceGroup")));
	
				//LogManager::getSingleton().logMessage("Resources declarations after loading the dotScene file: \n", LML_NORMAL, false);

				//for (	ResourceGroupManager::ResourceDeclarationList::iterator it = resourceDeclarationList.begin();
				//		it != resourceDeclarationList.end(); it++ )
				//{
				//	LogManager::getSingleton().logMessage(
				//		"Resource name: \"" + it->resourceName + "\"\n"
				//		"Resource type: \"" + it->resourceType + "\"\n",
				//		LML_NORMAL, false);
				//}
			// END OF TESTING PART!!!

			Ogre::StringVector optionKeys;
			bool success = mpSceneManager->getOptionKeys(optionKeys);
			Ogre::SceneManager::AnimationIterator itAnimation = mpSceneManager->getAnimationIterator();
			while ( itAnimation.hasMoreElements() )
			{
				Ogre::Animation* animation = itAnimation.getNext();
				Ogre::String animationName = animation->getName();
			}

			// ---
		}
		//***************************************************************************************************

		//***************************************************************************************************
		void MyoushuDotSceneProcessorImpl::shutdown()
		{
			if (mRootXmlNodeProcessor != NULL)
			{
				delete mRootXmlNodeProcessor;
				mRootXmlNodeProcessor = NULL;
			}

			if (mDotSceneNodeProcessorTreeBuilder != NULL)
			{
				delete mDotSceneNodeProcessorTreeBuilder;
				mDotSceneNodeProcessorTreeBuilder = NULL;
			}
		}
		//***************************************************************************************************

		//***************************************************************************************************
		const MyoushuDotSceneProcessorImpl::CommonParamsOfXmlNodeProcessors*
		MyoushuDotSceneProcessorImpl::getCommonParams() const
		{
			return mCommonParamsOfXmlNodeProcessors;
		}
		//***************************************************************************************************
		MyoushuDotSceneProcessorImpl::CommonParamsOfXmlNodeProcessors*
		MyoushuDotSceneProcessorImpl::getCommonParams()
		{
			return mCommonParamsOfXmlNodeProcessors;
		}
		//***************************************************************************************************
		const Ogre::dsi::DotSceneNodeProcessorTreeBuilder*
		MyoushuDotSceneProcessorImpl::getTreeBuilder() const
		{
			return mDotSceneNodeProcessorTreeBuilder;
		}
		//***************************************************************************************************
		Ogre::dsi::DotSceneNodeProcessorTreeBuilder*
			MyoushuDotSceneProcessorImpl::getTreeBuilder()
		{
			return mDotSceneNodeProcessorTreeBuilder;
		}

} // namespace Myoushu

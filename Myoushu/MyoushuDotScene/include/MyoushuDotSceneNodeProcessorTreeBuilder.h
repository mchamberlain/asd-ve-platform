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
 * @file MyoushuDotSceneNodeProcessorTreeBuilder.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_DOTSCENE_NODE_PROCESSOR_TREE_BUILDER_H
#define MYOUSHU_DOTSCENE_NODE_PROCESSOR_TREE_BUILDER_H

#include "dotSceneNodeProcessorTreeBuilder.h"

#include "Scene.h"

#include "MyoushuDotScenePlatform.h"
#include "MyoushuDotSceneUserDataElementProcessor.h"
#include "MyoushuDotScenePropertyElementProcessor.h"

namespace Myoushu
{
	/**
	 * An extension of Ogre::dsi::dotSceneNodeProcessorTreeBuilder that builds the parse tree for the XML based .scene files.
	 * In this extension we override the buildTree method to construct a tree that uses some custom element parsers we created, so
	 * that when Ogre::Entities are loaded these entities are converted into the relevant Myoushu::GameObjects.
	 */
	class MYOUSHU_DOTSCENE_API MyoushuDotSceneNodeProcessorTreeBuilder : public Ogre::dsi::DotSceneNodeProcessorTreeBuilder
	{
		public:
			MyoushuDotSceneNodeProcessorTreeBuilder(CommonParamsOfXmlNodeProcessors* commonParams);

			virtual ~MyoushuDotSceneNodeProcessorTreeBuilder();

			/// @copydoc XmlNodeProcessorTreeBuilder::buildTree()
			virtual XmlNodeProcessor*	buildTree();

		protected:
			/** Processor for <userData> elements */
			MyoushuDotSceneUserDataElementProcessor *mUserDataElementProcessor;
			/** Processor for <property> elements inside <userData> */
			MyoushuDotScenePropertyElementProcessor *mPropertyElementProcessor;
	};

} // namespace Myoushu

#endif

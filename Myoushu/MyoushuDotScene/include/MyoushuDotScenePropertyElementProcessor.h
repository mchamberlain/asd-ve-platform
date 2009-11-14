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
 * @file MyoushuDotScenePropertyElementProcessor.h
 * @author ME Chamberlain
 * @date February 2009
 */

#ifndef MYOUSHU_DOTSCENE_PROPERTY_ELEMENT_PROCESSOR_H
#define MYOUSHU_DOTSCENE_PROPERTY_ELEMENT_PROCESSOR_H

#include "dotSceneXmlNodeProcessors.h"

#include "MyoushuDotScenePlatform.h"

namespace Myoushu
{
	/** 
	 * A DotSceneXmlNodeProcessor implementation that parses <property> elements inside <userData> elements in a dot scene file. Entites, Lamps and Cameras can contain a
	 * userData element. The userData element then contains a number of property elements, for example:
	 * <userData>
	 *	<property type="BOOL" name="kinematic" value="1"/>
	 *	<property type="FLOAT" name="mass" value="10.0"/>
	 * </userData>
	 */
	class MYOUSHU_DOTSCENE_API MyoushuDotScenePropertyElementProcessor : public Ogre::DotSceneXmlNodeProcessor
	{
		public:
			/** Nullary Constructor. */
			MyoushuDotScenePropertyElementProcessor();

			/** Destructor */
			virtual ~MyoushuDotScenePropertyElementProcessor();

			/**
			 * Parse the <property> element.
			 * @param parent The parent element containing this property element.
			 * @param currentNode The current element.
			 */
			virtual void* parseElementImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode);
	};
} // namespace Myoushu

#endif

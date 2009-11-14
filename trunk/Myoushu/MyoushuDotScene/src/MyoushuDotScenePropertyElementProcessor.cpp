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

#include "GameObjectFactory.h"

#include "MyoushuDotScenePropertyElementProcessor.h"
#include "MyoushuDotSceneUserDataElementProcessor.h"

namespace Myoushu
{
	MyoushuDotScenePropertyElementProcessor::MyoushuDotScenePropertyElementProcessor() : Ogre::DotSceneXmlNodeProcessor()
	{
	}

	MyoushuDotScenePropertyElementProcessor::~MyoushuDotScenePropertyElementProcessor()
	{
	}

	void* MyoushuDotScenePropertyElementProcessor::parseElementImpl(XmlNodeProcessor* parent, TiXmlElement* currentNode)
	{
		Ogre::String parentParentName;
		Ogre::String propertyType;
		Ogre::String propertyName;
		Ogre::String propertyValueStr;
		Ogre::Real propertyValueFloat;
		bool propertyValueBool;
		int propertyValueInt;
		Value *pVal;
		MyoushuDotSceneUserDataElementProcessor *pUserDataProc;

		queryCurrElementNameAndFilenameAndDotSceneInfo(currentNode);

		pVal = NULL;

		// Parse the 'type' and 'name' attributes in this <property> element
		propertyType = parseAttribute("type", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, Ogre::String("INT"));
		propertyName = parseAttribute("name", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, Ogre::String(""));
		// Depending on the type of the property, parse the 'value' attribute and encapsulate it in pVal (a Value instance)
		if (propertyType == "INT")
		{
			propertyValueInt = parseAttribute("data", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, 0);
			pVal = new Value();
			pVal->set(propertyValueInt);
		}
		else if (propertyType == "BOOL")
		{
			propertyValueBool = parseAttribute("data", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, false);
			pVal = new Value();
			pVal->set(propertyValueBool);
		}
		else if (propertyType == "FLOAT")
		{
			propertyValueFloat = parseAttribute("data", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, 0.0f);
			pVal = new Value();
			pVal->set(propertyValueFloat);
		}
		else if (propertyType == "STRING")
		{
			propertyValueStr = parseAttribute("data", parent, currentNode, XmlNodeProcessor::XMLADD_REQUIRED, Ogre::String(""));
			pVal = new Value();
			pVal->set(propertyValueStr);
		}

		// Add the property to the KeyValueProperties maintained by the parent 
		pUserDataProc = static_cast<MyoushuDotSceneUserDataElementProcessor*>(parent);
		pUserDataProc->getKeyValueProperties().insert(propertyName, pVal);

		return pVal;
	}

} // namespace Myoushu

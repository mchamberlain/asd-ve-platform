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
 * @file ContentImporterFactory.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef MYOUSHU_CONTENT_IMPORTER_FACTORY_H
#define MYOUSHU_CONTENT_IMPORTER_FACTORY_H

#include "Platform.h"
#include "NamedObjectFactory.h"
#include "ContentImporter.h"

namespace Myoushu
{
	/**
	 * An interface for a factory that must be implemented to create ContentImporters. ContentImporters load content from scene files (such as DotScene) into
	 * the engine.
	 */
	class MYOUSHU_API ContentImporterFactory : public NamedObjectFactory<ContentImporter>
	{
		public:
			/** 
			 * Create an instance using with specified name. Extending classes can change
			 * the return type of this function to an appropriate type.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 */
			virtual ContentImporter* make(const std::string& name) = 0;

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual ContentImporter* make(const std::string& className, const std::string& name) throw (Exception) = 0;

	}; // class ContentImporterFactory
} // namespace Myoushu

#endif

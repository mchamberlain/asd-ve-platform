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
along with The ASD Assist VE Platform.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file EducationalQuestionsManager.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef ASTT_EDUCATIONAL_QUESTIONS_MANAGER_H
#define ASTT_EDUCATIONAL_QUESTIONS_MANAGER_H

#include <map>
#include <string>

#include "Poco/RWLock.h"
#include "Poco/AutoPtr.h"

#include "OgreSingleton.h"

#include "ASTTPlatform.h"
#include "EducationalQuestionsCategory.h"

namespace Educational
{
	/**
	 * A singleton manager class that manages categories of educational questions (such as math or language problems).
	 */
	class ASTT_API EducationalQuestionsManager : public Ogre::Singleton<EducationalQuestionsManager>
	{
		public:
			/** Type definition for a map of category names (strings) to pointers to EducationalQuestionsCategory instances. */
			typedef std::map<std::string, Poco::AutoPtr<EducationalQuestionsCategory> > CategoryMap;
			/** Type definition of an entry in CategoryMap */
			typedef std::pair<std::string, Poco::AutoPtr<EducationalQuestionsCategory> > CategoryMapEntry;
			/** Type definition of an iterator over the entries in a CategoryMap. */
			typedef CategoryMap::iterator CategoryMapIterator;
			/** Type definition of an const_iterator over the entries in a CategoryMap. */
			typedef CategoryMap::const_iterator CategoryMapConstIterator;

			/** Constructor */
			EducationalQuestionsManager();

			/** Destructor */
			virtual ~EducationalQuestionsManager();

			/**
			 * Loads a category from the specified file in the specified resource group. The default
			 * implementation loads a problem set from a category file saved in the XML format.
			 * @param filename The file name of the file to load.
			 * @param resourceGroup The resource group that contains the file to load. Defaults to "".
			 * @throws Myoushu::Exception::E_FILE_NOT_FOUND if the specified file could not be found.
			 */
			virtual void loadCategoryFile(const std::string& filename, const std::string& resourceGroup = "") throw (Myoushu::Exception);

			/** 
			 * Gets an educational category by name. 
			 * @param name The name of the category to fetch.
			 * @return An EducationalQuestionsCategory instance if an instance with the specified name was
			 *		   found, NULL otherwise.
			 */
			EducationalQuestionsCategory* getCategory(const std::string& name);

			/** 
			 * Gets an educational category by name. 
			 * @param name The name of the category to fetch.
			 * @return An EducationalQuestionsCategory instance if an instance with the specified name was
			 *		   found, NULL otherwise.
			 */
			const EducationalQuestionsCategory* getCategory(const std::string& name) const;

			/** Remove and destroy a category by name. */
			void destroyCategory(const std::string& name);

			/** Remove and destroy all categories. */
			void destroyAll();

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** CategoryMap that maps category names to their respective EducationalQuestionsCategory instance. */
			CategoryMap mCategoryMap;

			/**
			 * Handles escape characters such as '\"' and processes and translates substrings bewteen double-quotes (").
			 * @param string The string to clean and translate its substrings.
			 * @return The cleaned and translated string.
			 */
			Ogre::UTFString cleanAndTranslateString(const Ogre::UTFString& string);

	}; // class EducationalQuestionsManager

} // namespace Educational

#endif

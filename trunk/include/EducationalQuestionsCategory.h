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
 * @file EducationalQuestionsCategory.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef ASTT_EDUCATIONAL_QUESTIONS_CATEGORY_H
#define ASTT_EDUCATIONAL_QUESTIONS_CATEGORY_H

#include "Poco/RefCountedObject.h"

#include "NamedInstance.h"
#include "NamedObjectFactory.h"

#include "ASTTPlatform.h"
#include "EducationalQuestion.h"

namespace Educational
{
	/**
	 * A category of EducationalQuestion instances. This class is a factory that creates EducationalQuestion instances.
	 * Typically the EducationalQuestionsManager will read categories of questions from a file and create EducationalQuestionsCategory
	 * instances and then use these instances to create EducationalQuestion instances and populate them.
	 */
	class ASTT_API EducationalQuestionsCategory : public Myoushu::NamedInstance, public Myoushu::NamedObjectFactory<EducationalQuestion>, public Poco::RefCountedObject
	{
		public:
			/** 
			 * Constructor. 
			 * @param name The name of this category.
			 */
			EducationalQuestionsCategory(const std::string& name = "EducationalQuestionsCategory");

			/** Destructor. */
			virtual ~EducationalQuestionsCategory();

			/** Gets the name of this category. */
			std::string getName() const;

			/** 
			 * Create an instance using with specified name. Extending classes can change
			 * the return type of this function to an appropriate type.
			 * @param name The name for the instance to create.
			 * @return The newly created instance or an instance with the same name that already exists.
			 */
			virtual EducationalQuestion* make(const std::string& name);

			/** 
			 * Create an instance of the specified className with the specified instance name. Extending classes can change
			 * the return type of this function to an appropriate type. This function is useful for factories that can
			 * create instances of different classes in an inheritence hierarchy.
			 * @param className The name of the class to create an instance of.
			 * @param name The name for the instance to create.
			 * @return The newly created instance or an instance with the same name that already exists.
			 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
			 */
			virtual EducationalQuestion* make(const std::string& className, const std::string& name) throw (Myoushu::Exception);

			/**
			 * Find an EducationalQuestion instance in this category by name.
			 * @param name The name of the object to find.
			 * @return A pointer to the instance with the specified name,
			 *		   or NULL if no such instance could be found.
			 */
			virtual EducationalQuestion* findByName(const std::string &name);

			/** Sets the description of this category. */
			void setDescription(const std::string& description);

			/** Gets the description of this category. */
			std::string getDescription() const;

			/**
			 * Gets a vector of question names. The name of a question can be used to get the EducationalQuestion
			 * instance by using the findByName() function.
			 */
			void getQuestionNames(std::vector<std::string>& questionNames);

			/** Gets a vector of all the EducationalQuestion instances in this category. */
			void getQuestions(std::vector<EducationalQuestion*>& questions);

		protected:
			std::string mDescription;

	}; // class EducationalQuestionsCategory

	// inlines

	inline std::string EducationalQuestionsCategory::getName() const
	{
		return Myoushu::NamedInstance::getName();
	}

	inline EducationalQuestion* EducationalQuestionsCategory::findByName(const Ogre::String &name)
	{
		return static_cast<EducationalQuestion*>(NamedObjectFactory<EducationalQuestion>::findByName(name));
	}

	inline void EducationalQuestionsCategory::setDescription(const std::string& description)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mDescription = description;
	}

	inline std::string EducationalQuestionsCategory::getDescription() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mDescription;
	}

} // namespace Educational

#endif

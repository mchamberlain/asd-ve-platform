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
 * @file EducationalQuestionsCategory.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "EducationalQuestionsCategory.h"
#include "EngineLog.h"

namespace Educational
{
	EducationalQuestionsCategory::EducationalQuestionsCategory(const std::string& name) : NamedInstance(name)
	{
	}

	EducationalQuestionsCategory::~EducationalQuestionsCategory()
	{
	}

	EducationalQuestion* EducationalQuestionsCategory::make(const std::string& name)
	{
		EducationalQuestion *pQuestion;

		pQuestion = static_cast<EducationalQuestion*>(findByName(name));

		if (pQuestion == NULL)
		{
			// Create new instance
			pQuestion = new EducationalQuestion(name);

			// The instance to the factory
			add(pQuestion);
		}

		return pQuestion;
	}

	EducationalQuestion* EducationalQuestionsCategory::make(const std::string& className, const std::string& name) throw (Myoushu::Exception)
	{
		EducationalQuestion *pQuestion;

		pQuestion = static_cast<EducationalQuestion*>(findByName(name));

		if (pQuestion != NULL)
		{
			return pQuestion;
		}

		if (className == NamedObject<EducationalQuestion>::getStaticClassName())
		{
			pQuestion = new EducationalQuestion(name);

			add(pQuestion);
		}

		return pQuestion;
	}

	void EducationalQuestionsCategory::getQuestionNames(std::vector<std::string>& questionNames)
	{
		ConstIterator iter;
		ConstIterator endIter;

		iter = begin();
		endIter = end();
		Poco::ScopedRWLock lock(rwLock, false);

		questionNames.clear();
		for (; iter != endIter; ++iter)
		{
			questionNames.push_back(iter->first);
		}
	}

	void EducationalQuestionsCategory::getQuestions(std::vector<EducationalQuestion*>& questions)
	{
		Iterator iter;
		Iterator endIter;

		iter = begin();
		endIter = end();
		Poco::ScopedRWLock lock(rwLock, false);

		questions.clear();
		for (; iter != endIter; ++iter)
		{
			questions.push_back(iter->second);
		}
	}

} // namespace Educational

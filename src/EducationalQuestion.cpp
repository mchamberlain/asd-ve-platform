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
 * @file EducationalQuestion.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include <algorithm>

#include "EngineLog.h"

#include "EducationalQuestion.h"

CLASS_NAME(Educational::EducationalQuestion, "Educational::EducationalQuestion");

namespace Educational
{

	EducationalQuestion::EducationalQuestion(const std::string& name) : Myoushu::NamedInstance(name)
	{
	}

	EducationalQuestion::~EducationalQuestion()
	{
	}

	bool EducationalQuestion::evaluateAnswer(const std::list<std::string>& answer) const
	{
		std::list<std::string>::const_iterator iter;
		unsigned int matchCount;

		Poco::ScopedRWLock lock(mRWLock, false);

		matchCount = 0;
		switch (mAnswerCondition)
		{
			case AC_EXACT:
				if (answer.size() != mCorrectAnswers.size())
				{
					return false;
				}
				return (answer == mCorrectAnswers);
				break;

			case AC_ALL_NO_ORDER:
				if (answer.size() != mCorrectAnswers.size())
				{
					return false;
				}
				for (iter = answer.begin(); iter != answer.end(); ++iter)
				{
					if (std::find(mCorrectAnswers.begin(), mCorrectAnswers.end(), *iter) != mCorrectAnswers.end())
					{
						matchCount++;
					}
				}
				return (matchCount == mCorrectAnswers.size());
				break;

			case AC_ONE_OF:
				if (answer.size() != 1)
				{
					return false;
				}
				return (std::find(mCorrectAnswers.begin(), mCorrectAnswers.end(), answer.front()) != mCorrectAnswers.end());
				break;

			case AC_UNKNOWN:
			default:
				LOG(Myoushu::EngineLog::LM_WARNING, "EducationalQuestion::evaluateAnswer(): Unknown AnswerCondition type: " << mAnswerCondition);
				break;
		}

		return false;
	}

} // namespace Educational

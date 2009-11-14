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
 * @file EducationalQuestion.h
 * @author ME Chamberlain
 * @date June 2009
 */

#ifndef ASTT_EDUCATIONAL_QUESTION_H
#define ASTT_EDUCATIONAL_QUESTION_H

#include <list>
#include <string>

#include "Poco/RWLock.h"
#include "Poco/RefCountedObject.h"

#include "NamedInstance.h"
#include "NamedObject.h"

#include "ASTTPlatform.h"

namespace Educational
{
	class ASTT_API EducationalQuestion : public Myoushu::NamedInstance, public Myoushu::NamedObject<EducationalQuestion>, public Poco::RefCountedObject
	{
		public:
			/** An enumeration of conditions under which an answer is considered as correct. */
			enum AnswerCondition
			{
				/** An unknown type */
				AC_UNKNOWN = 0,
				/** An answer must exactly match the answers in mCorrectAnswers, including order. */
				AC_EXACT,
				/** An answer must contain all of the answers in mCorrectAnswers, but order is irrelevant. */
				AC_ALL_NO_ORDER,
				/** An answer must contain at least one of the answers in mCorrectAnswers. */
				AC_ONE_OF				
			};

			/**
			 * Constructor.
			 * @param name The name of this instance.
			 */
			EducationalQuestion(const std::string& name = "EducationalQuestion");

			/** Destructor. */
			virtual ~EducationalQuestion();

			CLASS_NAME_FUNCTIONS(EducationalQuestion);

			/** Sets the description for this question. */
			void setDescription(const std::string& description);

			/** Gets the description for this question. */
			std::string getDescription() const;

			/** 
			 * Sets the mQuestion string. Should not included any extra descriptions, i.e. for math
			 * it should only be something like '1 + 2' for language something like 'c_t' etc.
			 */
			void setQuestion(const std::string& question);

			/** Gets the mQuestion string. */
			std::string getQuestion() const;

			/** 
			 * Sets the mAnswerCondition value (see AnswerCondition) the condition under which an answer
			 * supplied by the user will be considered as correct.
			 */
			void setAnswerCondition(AnswerCondition answerCondition);

			/** Gets the mAnswerCondition field. */
			AnswerCondition getAnswerCondition() const;

			/**
			 * Sets the list of correct answers. evaluateAnswer uses this list in conjunction with
			 * mAnswerCondition to determine whether a user supplied answer is correct.
			 */
			void setCorrectAnswers(const std::list<std::string>& correctAnswers);

			/** Gets the list of correct answers. */
			std::list<std::string> getCorrectAnswers() const;

			/** Sets the list of possible answers (eg multiple choice questions). */
			void setPossibleAnswers(const std::list<std::string>& possibleAnswers);

			/** Gets the list of possible answers. */
			std::list<std::string> getPossibleAnswers() const;

			/**
			 * Test whether the answer list supplied by the user is correct. This method
			 * uses mCorrectAnswers in conjunction with mAnswerCondition to determine
			 * wheter answer represents the correct answer to this question.
			 * @retun true If answer is the correct answer, false otherwise.
			 */
			virtual bool evaluateAnswer(const std::list<std::string>& answer) const;

		protected:
			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** A broad description of the problem. */
			std::string mDescription;
			/** The specific question, i.e. 2 + 1 or c_t, without any extra descriptions. */
			std::string mQuestion;
			/** The condition under which an answer supplied by a user will be considered correct. */
			AnswerCondition mAnswerCondition;
			/**
			 * List of correct answers. An answer given by a user will be checked against this list
			 * under conditions specified by AnswerCondition.
			 */
			std::list<std::string> mCorrectAnswers;
			/** A list of possible answers that could be presented to the user in a multiple choice setup. */
			std::list<std::string> mPossibleAnswers;
		
	}; // class EducationalQuestion

	// inlines
	inline void EducationalQuestion::setDescription(const std::string& description)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mDescription = description;
	}

	inline std::string EducationalQuestion::getDescription() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mDescription;
	}

	inline void EducationalQuestion::setQuestion(const std::string& question)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mQuestion = question;
	}

	inline std::string EducationalQuestion::getQuestion() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mQuestion;
	}

	inline void EducationalQuestion::setAnswerCondition(AnswerCondition answerCondition)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mAnswerCondition = answerCondition;
	}

	inline EducationalQuestion::AnswerCondition EducationalQuestion::getAnswerCondition() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mAnswerCondition;
	}

	inline void EducationalQuestion::setCorrectAnswers(const std::list<std::string>& correctAnswers)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mCorrectAnswers = correctAnswers;
	}

	inline std::list<std::string> EducationalQuestion::getCorrectAnswers() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mCorrectAnswers;
	}

	inline void EducationalQuestion::setPossibleAnswers(const std::list<std::string>& possibleAnswers)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mPossibleAnswers = possibleAnswers;
	}

	inline std::list<std::string> EducationalQuestion::getPossibleAnswers() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mPossibleAnswers;
	}

} // namespace Educational

#endif

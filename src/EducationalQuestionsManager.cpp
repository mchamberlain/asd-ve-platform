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
 * @file EducationalQuestionsManager.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include <list>
#include <sstream>

#include "EducationalQuestionsManager.h"
#include "XMLCategoryFile.h"

#include "TextFileManager.h"

#include "EngineLog.h"
#include "DefaultTranslation.h"

namespace Educational
{
	EducationalQuestionsManager::EducationalQuestionsManager()
	{
	}

	EducationalQuestionsManager::~EducationalQuestionsManager()
	{
	}

	void EducationalQuestionsManager::loadCategoryFile(const std::string& filename, const std::string& resourceGroup) throw (Myoushu::Exception)
	{
		TextFileManager *pTxtFileManager;
		TextFilePtr pTxtFile;
		XMLCategoryFile xmlFile;
		Ogre::String fileData;
		std::stringstream sStr;
		EducationalQuestionsCategory *pCategory;
		EducationalQuestion *pQuestion;
		unsigned int questionCounter;
		std::stringstream problemKeyPrefix;

		// Get the TextFileManager, create it if it does not exist
		pTxtFileManager = TextFileManager::getSingletonPtr();
		if (pTxtFileManager == NULL)
		{
			pTxtFileManager = new TextFileManager();
		}

		pTxtFile = pTxtFileManager->load(filename, resourceGroup);
		if (pTxtFile.isNull())
		{
			LOG(Myoushu::EngineLog::LM_WARNING, "EducationalQuestionsManager::loadCategoryFile(): couldn't find file: " << filename << " in resource group " << resourceGroup);
			throw Myoushu::Exception(Myoushu::Exception::E_FILE_NOT_FOUND, "EducationalQuestionsManager::loadCategoryFile(): couldn't find file: " + filename + " in resource group " + resourceGroup);
		}

		// Load the text file with the XMLCategoryFile instance
		xmlFile.load(pTxtFile);

		// We can now extract the contents (questions) in the loaded category
		// We expect to see the following in the file:
		// name
		// description
		// problem[0..N-1] for N problems
		// problem[x].name
		// problem[x].question
		// problem[x].correctAnswer[0..K-1] for K correct answers
		// Optional:
		// problem[x].question[@jumble] boolean that indicates whether the text in the question should
		//									   be jumbled after translation (for certain language problems)
		// problem[x].description
		// problem[x].possibleAnswer[0..L-1] for L possible answers (multiple choice for instance)
		// problem[x].answerCondition for the conditions under which a user supplied answer should be
		//									   compared to the correct answer(s).
		
		questionCounter = 0;
		// Confirm that a category name and description is set.
		if ((!xmlFile.hasProperty("name")) || (!xmlFile.hasProperty("description")))
		{
			LOG(Myoushu::EngineLog::LM_WARNING, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file: " << filename);
			throw Myoushu::Exception(Myoushu::Exception::E_PARSE_ERROR, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file1: " + filename);
		}

		// Create the category instance
		pCategory = new EducationalQuestionsCategory(xmlFile.getString("name"));
		pCategory->setDescription(xmlFile.getString("description"));

		// Parse all problem entities defined in the file
		problemKeyPrefix.str("");
		problemKeyPrefix << "problem";
		while (xmlFile.hasProperty(problemKeyPrefix.str() + ".name"))
		{
			std::list<std::string> tempList;
			std::stringstream answersKeyPrefix;
			std::string tempString;
			unsigned int answersCounter;

			// Get a new EducationalQuestion instance
			pQuestion = pCategory->make(xmlFile.getString(problemKeyPrefix.str() + ".name"));

			// Set its description, if a description is included
			pQuestion->setDescription(xmlFile.getString(problemKeyPrefix.str() + ".description", ""));

			// Set its question field
			if (!xmlFile.hasProperty(problemKeyPrefix.str() + ".question"))
			{
				// Destroy the category
				delete pCategory;

				// Log and throw execption
				LOG(Myoushu::EngineLog::LM_WARNING, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file: " << filename << ", a problem element must include a question field.");
				throw Myoushu::Exception(Myoushu::Exception::E_PARSE_ERROR, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file: " + filename + ", a problem element must include a question field.");
			}
			pQuestion->setQuestion(xmlFile.getString(problemKeyPrefix.str() + ".question"));
			// Check whether the optional jumble property has been set on the question element
			if (xmlFile.hasProperty(problemKeyPrefix.str() + ".question[@jumble]"))
			{
				// TODO: jumble
			}

			// Set its correctAnswers list
			answersCounter = 0;
			answersKeyPrefix.str("");
			answersKeyPrefix << problemKeyPrefix.str() << ".correctAnswer";
			tempList.clear();

			while (xmlFile.hasProperty(answersKeyPrefix.str()))
			{
				// Add the answer string to the temporary list
				tempList.push_back(xmlFile.getString(answersKeyPrefix.str()));

				// Increment the answersCounter and update the answersKeyPrefix
				answersCounter++;
				answersKeyPrefix.str("");
				answersKeyPrefix << problemKeyPrefix.str() << ".correctAnswer[" << answersCounter << "]";
			}
			
			// Check that at least one answer was read
			if (answersCounter == 0)
			{
				// Destroy the category
				delete pCategory;

				// Log and throw execption
				LOG(Myoushu::EngineLog::LM_WARNING, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file: " << filename << ", at least one answer must be specified.");
				throw Myoushu::Exception(Myoushu::Exception::E_PARSE_ERROR, "EducationalQuestionsManager::loadCategoryFile(): error while parsing file: " + filename + ", at least one answer must be specified.");
			}
			// Set the correctAnswers list
			pQuestion->setCorrectAnswers(tempList);

			// Set its possibleAnswers list, if included
			answersCounter = 0;
			answersKeyPrefix.str("");
			answersKeyPrefix << problemKeyPrefix.str() << ".possibleAnswer";
			tempList.clear();
			while (xmlFile.hasProperty(answersKeyPrefix.str()))
			{
				// Add the answer string to the temporary list
				tempList.push_back(xmlFile.getString(answersKeyPrefix.str()));

				// Increment the answersCounter and update the answersKeyPrefix
				answersCounter++;
				answersKeyPrefix.str("");
				answersKeyPrefix << problemKeyPrefix.str() << ".possibleAnswer[" << answersCounter << "]";
			}
			
			// Check that at least one answer was read
			if (answersCounter > 0)
			{
				// Set the correctAnswers list
				pQuestion->setCorrectAnswers(tempList);
			}

			// Set its answerCondition, if included
			if (xmlFile.hasProperty(problemKeyPrefix.str() + ".answerCondition"))
			{
				tempString = xmlFile.getString(problemKeyPrefix.str() + ".answerCondition");
				if (tempString == "allNoOrder")
				{
					pQuestion->setAnswerCondition(EducationalQuestion::AC_ALL_NO_ORDER);
				}
				else if (tempString == "oneOf")
				{
					pQuestion->setAnswerCondition(EducationalQuestion::AC_ONE_OF);
				}
				else
				{
					pQuestion->setAnswerCondition(EducationalQuestion::AC_EXACT);
				}
			}
			else
			{
				pQuestion->setAnswerCondition(EducationalQuestion::AC_EXACT);
			}

			// Increment the questionCounter and set the next problemKeyPrefix
			questionCounter++;
			problemKeyPrefix.str("");
			problemKeyPrefix << "problem[" << questionCounter << "]";
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		mCategoryMap.insert(CategoryMapEntry(pCategory->getName(), pCategory));
	}

	EducationalQuestionsCategory* EducationalQuestionsManager::getCategory(const std::string& name)
	{
		CategoryMapIterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);	

		iter = mCategoryMap.find(name);

		if (iter == mCategoryMap.end())
		{
			return NULL;
		}

		return iter->second;
	}

	const EducationalQuestionsCategory* EducationalQuestionsManager::getCategory(const std::string& name) const
	{
		CategoryMapConstIterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);	

		iter = mCategoryMap.find(name);

		if (iter == mCategoryMap.end())
		{
			return NULL;
		}

		return iter->second;
	}

	void EducationalQuestionsManager::destroyCategory(const std::string& name)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mCategoryMap.erase(name);
	}

	void EducationalQuestionsManager::destroyAll()
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mCategoryMap.clear();
	}

	Ogre::UTFString EducationalQuestionsManager::cleanAndTranslateString(const Ogre::UTFString& string)
	{
		Ogre::UTFString result;
		Ogre::UTFString toTranslate;
		Ogre::UTFString::const_iterator iter;
		Myoushu::DefaultTranslation *pTranslation;
		bool translate;
		bool verbatimNext;

		// Get the Myoushu::DefaultTranslation instance
		pTranslation = Myoushu::DefaultTranslation::getSingletonPtr();
		if (pTranslation == NULL)
		{
			pTranslation = new Myoushu::DefaultTranslation();
		}

		translate = false;
		verbatimNext = false;
		for (iter = string.begin(); iter != string.end(); ++iter)
		{
			Ogre::UTFString::unicode_char wChar = *iter;

			switch (wChar)
			{
				case '\\':
					// Append the next character verbatim
					verbatimNext = true;
					break;
				case '"':
					if (translate)
					{
						// Translate the string that has been gathered in toTranslate using the Myoushu::Translation instance in pTranslate.
						Ogre::UTFString translatedString;

						pTranslation->translate(toTranslate, translatedString);
						result.append(translatedString);
						toTranslate.clear();
					}
					translate = !translate;
					break;
				default:
					if ((verbatimNext) || (!translate))
					{
						result.append(1, wChar);
					}
					else if (translate)
					{
						// When the translate flag is true, characters are concatenated to the toTranslate string and translated when the next " is read.
						toTranslate.append(1, wChar);
					}
					break;
			}

		}

		return result;
	}

} // namespace Educational

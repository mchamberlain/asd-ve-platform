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
 * @file Translation.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include <sstream>

#include "Platform.h"

#include "TextFileManager.h"

#include "Translation.h"
#include "EngineLog.h"

namespace Myoushu 
{
	Translation::Translation()
	{
	}

	Translation::~Translation()
	{
	}

	void Translation::loadTranslationFile(const std::string& filename, const std::string& resourceGroup) throw (Exception)
	{
		TextFileManager *pTxtFileManager;
		TextFilePtr pTxtFile;
		Ogre::UTFString currentContext;
		Ogre::UTFString untranslatedString;
		std::stringstream sStr;
		Ogre::UTFString token;
		Ogre::UTFString currentStr;
		bool expectedCtxt;
		bool expectedId;
		bool expectedStr;
		uint32 startIndex;

		const Ogre::UTFString msgidToken = "msgid";
		const Ogre::UTFString msgctxtToken = "msgctxt";
		const Ogre::UTFString msgstrToken = "msgstr";

		// Get the TextFileManager singleton, create it if it does not exist
		pTxtFileManager = TextFileManager::getSingletonPtr();
		if (pTxtFileManager == NULL)
		{
			pTxtFileManager = new TextFileManager();
		}

		// Load the translation file
		pTxtFile = pTxtFileManager->load(filename, resourceGroup);

		// Throw an exception if the file could not be loaded
		if (pTxtFile.isNull())
		{
			throw Exception(Exception::E_FILE_NOT_FOUND, "Translation::loadTranslationFile(): could not find translation file: " + filename + " in resource group " + resourceGroup + ".");
		}

		Poco::ScopedRWLock lock(mRWLock, true);

		expectedCtxt = true;
		expectedId = true;
		expectedStr = false;

		const Ogre::String& rawString = pTxtFile->getString();
		currentStr.clear();
		token.clear();

		// UTF-8 files could include a BOM character at the beginning of the file. We check if its there, if it
		// is we skip it and start processing from the fourth byte. If it is not present at the start of the file,
		// we just start processing from the first character.
		startIndex = 0;
		if (rawString.length() >= 3)
		{
			if ((static_cast<unsigned char>(rawString[0]) == 0xEFu) && (static_cast<unsigned char>(rawString[1]) == 0xBBu) && (static_cast<unsigned char>(rawString[2]) == 0xBFu))
			{
				// The BOM is included at the start of the file, ignore it
				startIndex = 3;
			}
		}

		Ogre::UTFString fileData(pTxtFile->getString().c_str() + startIndex);

		for (uint32 i = 0; i < fileData.length(); i++)
		{
			if (fileData[i] == '\r')
			{
				// Ignore carriage return
				continue;
			}
			else if ((currentStr.length() == 0) && ((fileData[i] == ' ') || (fileData[i] == '\t') || (fileData[i] == '\n')))
			{
				// Ignore whitespace if it will result in currentStr containing only whitespace
				continue;
			}
			else if (fileData[i] != '\n')
			{
				currentStr.append(1, fileData[i]);
			}

			if (token.length() == 0)
			{
				if (currentStr == msgctxtToken)
				{
					if (expectedCtxt)
					{
						token = currentStr;
						currentStr.clear();
						expectedCtxt = false;
					}
					else
					{
						// error
						LOG(EngineLog::LM_WARNING, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgctxt: " << filename);
						throw Exception(Exception::E_PARSE_ERROR, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgctxt: " + filename);
					}
				}
				else if (currentStr == msgidToken)
				{
					if (expectedId)
					{
						expectedId = false;
						expectedCtxt = false;
						expectedStr = true;
						token = currentStr;
						currentStr.clear();
					}
					else
					{
						// error
						LOG(EngineLog::LM_WARNING, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgid: " << filename);
						throw Exception(Exception::E_PARSE_ERROR, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgid: " + filename);
					}
				}
				else if (currentStr == msgstrToken)
				{
					if (expectedStr)
					{
						expectedId = true;
						expectedCtxt = true;
						expectedStr = false;
						token = currentStr;
						currentStr.clear();
					}
					else
					{
						// error
						LOG(EngineLog::LM_WARNING, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgstr: " << filename << " " << currentStr.asUTF8());
						throw Exception(Exception::E_PARSE_ERROR, "Translation::loadTranslationFile(): error while parsing translation file, unexpected msgstr: " + filename);
					}
				}
			}

			// End of line reached, check token and set appropriate string
			if (fileData[i] == '\n')
			{
				if (token == msgidToken)
				{
					untranslatedString = currentStr;
				}
				else if (token == msgctxtToken)
				{
					currentContext = currentStr;
				}
				else if (token == msgstrToken)
				{
					// Add the entry to the translation map
					mTranslationMap.insert(TranslationMapEntry(TranslationEntry(untranslatedString, currentContext), currentStr));

					untranslatedString.clear();
					currentContext.clear();
				}

				currentStr.clear();
				token.clear();
			}
		}
	}

	Ogre::UTFString Translation::translate(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context) const
	{
		TranslationMapConstIterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		iter = mTranslationMap.find(TranslationEntry(untranslatedString, context));
		if (iter == mTranslationMap.end())
		{
			// There is no such entry in the translation map, return the empty string
			return "";
		}
		
		return iter->second;
	}

	bool Translation::translate(const Ogre::UTFString& untranslatedString, Ogre::UTFString& translatedString, const Ogre::UTFString& context) const
	{
		TranslationMapConstIterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		iter = mTranslationMap.find(TranslationEntry(untranslatedString, context));
		if (iter == mTranslationMap.end())
		{
			// There is no such entry in the translation map, return false
			translatedString = untranslatedString;
			return false;
		}
		
		// Set the translated string and return true
		translatedString = iter->second;
		return true;
	}

	Translation::TranslationEntry::TranslationEntry() : mUntranslatedString(""), mContext("")
	{
	}

	Translation::TranslationEntry::TranslationEntry(const TranslationEntry& entry) : mUntranslatedString(entry.getUntranslatedString())
		, mContext(entry.getContext())
	{
	}

	Translation::TranslationEntry::TranslationEntry(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context)
		: mUntranslatedString(untranslatedString), mContext(context)
	{
	}

	Translation::TranslationEntry::~TranslationEntry()
	{
	}

	void Translation::TranslationEntry::set(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mUntranslatedString = untranslatedString;
		mContext = context;
	}

	Translation::TranslationEntry& Translation::TranslationEntry::operator=(const TranslationEntry& rhs)
	{
		Poco::ScopedRWLock lock(mRWLock, true);

		mUntranslatedString = rhs.getUntranslatedString();
		mContext = rhs.getContext();

		return *this;
	}

	bool Translation::TranslationEntry::operator<(const TranslationEntry& rhs) const
	{
		Ogre::UTFString thisString;
		Ogre::UTFString rhsString;

		Poco::ScopedRWLock lock(mRWLock, false);

		thisString = mUntranslatedString + "#" + mContext + "#";
		rhsString = rhs.getUntranslatedString() + "#" + rhs.getContext() + "#";

		return (thisString < rhsString);
	}

} // namespace Myoushu

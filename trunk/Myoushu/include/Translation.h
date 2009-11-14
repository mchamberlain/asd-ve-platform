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
 * @file Translation.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef MYOUSHU_TRANSLATION_H
#define MYOUSHU_TRANSLATION_H

#include <map>

#include "Poco/RWLock.h"

#include "Ogre.h"

#include "Platform.h"
#include "Exception.h"

namespace Myoushu 
{
	/**
	 * A simple implementation of a translation system. The main reason for doing our own implementation instead
	 * of using something like gettext is that we require functionality from all of our supported script interfaces
	 * as well.
	 * Translations are specified in simple text files. The file name should be <language>.tsl. The file contains entries
	 * of the form:
	 *
	 * msgid untranslated-string
	 * msgstr translated-string
	 *
	 * Where entries are separated with a blank line. Optionally contexts can also be specified:
	 *
	 * msgctxt context
	 * msgid untranslated-string
	 * msgstr translated-string
	 *
	 * An unspecified context is taken to be an empty string.
	 */
	class MYOUSHU_API Translation 
	{
		public:
			/** Constructor. */
			Translation();

			/** Destructor */
			virtual ~Translation();

			/**
			 * Loads the specified translation file. Does not clears any currently loaded translations, use the
			 * clear() function to clear any currently loaded translations.
			 * @param filename The name of the translation file.
			 * @param resourceGroup The resource group that contains the translation file.
			 * @throws Exception::E_FILE_NOT_FOUND if the file could not be found.
			 */
			virtual void loadTranslationFile(const std::string& filename, const std::string& resourceGroup) throw (Exception);

			/** Clear any currently loaded translation data. */
			virtual void clear();

			/**
			 * Searches for and returns the currently loaded translation for the specified untranslated string and its context.
			 * @param untranslatedString The untranslated string to fetch a translation for.
			 * @param context The context applicable to the untranslated string.
			 */
			virtual Ogre::UTFString translate(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context = "") const;

			/**
			 * Searches for and returns the currently loaded translation for the specified untranslated string and its context.
			 * @param untranslatedString The untranslated string to fetch a translation for.
			 * @param translatedString The Ogre::UTFString to store the translated string in.
			 * @param context The context applicable to the untranslated string.
			 * @return True if the translation was successfull, false otherwise (there was no available translation). If false is returned,
			 *		   translatedString is set to untranslatedString.
			 */
			virtual bool translate(const Ogre::UTFString& untranslatedString, Ogre::UTFString& translatedString, const Ogre::UTFString& context = "") const;

		protected:
			/**
			 * A simple inner class that is used as the keys in the translation map. It stores two strings, the first
			 * is the untranslated-string and the second the context identifier. These TranslationEntry instances
			 * are then mapped to their relevant translated strings.
			 */
			class TranslationEntry
			{
				public:
					/** Nullary Constructor. */
					TranslationEntry();

					/** 
					 * Clone constructor.
					 * This newly created instance is set to a copy of the values in entry.
					 */
					TranslationEntry(const TranslationEntry& entry);

					/**
					 * Constructor.
					 * @param untranslatedString The untranslated string/message.
					 * @param context The context applicable to the message.
					 */
					TranslationEntry(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context);

					/** Destructor */
					virtual ~TranslationEntry();

					/** Sets the untranslated string/message and its context. */
					void set(const Ogre::UTFString& untranslatedString, const Ogre::UTFString& context = "");

					/** Gets the untranslated string/message. */
					Ogre::UTFString getUntranslatedString() const;

					/** Gets the context applicable to the untranslated string/message. */
					Ogre::UTFString getContext() const;

					/** Tests whether this instance (untranslated string and context) is equal to the specified instance. */
					bool operator==(const TranslationEntry& rhs) const;

					/** 
					 * Tests whether this instance is less than the specified instance.
					 * This is done by concatening the strings (untranslated string and context) where the context
					 * string is placed between a pair of '#' characters.
					 */
					bool operator<(const TranslationEntry& rhs) const;

					/** 
					 * Sets the untranslated string/message and context of this instance to be equal to the
					 * untranslated string/message and context in the supplied instance.
					 */
					TranslationEntry& operator=(const TranslationEntry& rhs);

				protected:
					/** Read/write mutex for thread safety. */
					mutable Poco::RWLock mRWLock;
					/** The untranslated string/message. */
					Ogre::UTFString mUntranslatedString;
					/** The context applicable to the message. */
					Ogre::UTFString mContext;

			}; // TranslationEntry

			/** Type definition of the TranslationMap: map from TranslationEntry to its translated string. */
			typedef std::map<TranslationEntry, Ogre::UTFString> TranslationMap;
			/** Type definition of the entries in the TranslationMap: a pair of TranslationEntry and Ogre::UTFString. */
			typedef std::pair<TranslationEntry, Ogre::UTFString> TranslationMapEntry;
			/** Type definition to an iterator over the entries in a TranslationMap. */
			typedef TranslationMap::iterator TranslationMapIterator;
			/** Type definition to a const_iterator over the entries in a TranslationMap. */
			typedef TranslationMap::const_iterator TranslationMapConstIterator;

			/** Read/write mutex for thread safety. */
			mutable Poco::RWLock mRWLock;
			/** Map of TranslationEntry instance to their respective translation strings. */
			TranslationMap mTranslationMap;

	}; // Translation

	// inlines
	inline void Translation::clear()
	{
		Poco::ScopedRWLock lock(mRWLock, true);
		mTranslationMap.clear();
	}

	inline Ogre::UTFString Translation::TranslationEntry::getUntranslatedString() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mUntranslatedString;
	}

	inline Ogre::UTFString Translation::TranslationEntry::getContext() const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return mContext;
	}

	inline bool Translation::TranslationEntry::operator==(const TranslationEntry& rhs) const
	{
		Poco::ScopedRWLock lock(mRWLock, false);

		return ((mUntranslatedString == rhs.getUntranslatedString()) && (mContext == rhs.getContext()));
	}

} // namespace Myoushu

#endif

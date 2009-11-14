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
 * @file DefaultTranslation.h
 * @author ME Chamberlain
 * @date June 2008
 */

#ifndef MYOUSHU_DEFAULT_TRANSLATION_H
#define MYOUSHU_DEFAULT_TRANSLATION_H

#include "Platform.h"
#include "Singleton.h"
#include "Translation.h"

namespace Myoushu
{
	/**
	 * A singleton of the Translation class. This class serves as the global or default translation instance. It
	 * can be used to set the current language to be used engine-wide.
	 */
	class MYOUSHU_API DefaultTranslation : public Translation, public Ogre::Singleton<DefaultTranslation>
	{
		public:
			/** Constructor. */
			DefaultTranslation();

			/** Destructor. */
			virtual ~DefaultTranslation();

	}; // classname DefaultTranslation

} // namespace Myoushu

#endif

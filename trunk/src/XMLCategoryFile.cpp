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
 * @file XMLCategoryFile.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include <sstream>

#include "XMLCategoryFile.h"

namespace Educational
{
	XMLCategoryFile::XMLCategoryFile()
	{
	}

	XMLCategoryFile::~XMLCategoryFile()
	{
	}

	void XMLCategoryFile::load(const TextFilePtr pTxtFile) throw (Myoushu::Exception)
	{
		std::stringstream sStr;

		if (pTxtFile.isNull())
		{
			throw Myoushu::Exception(Myoushu::Exception::E_NULL_POINTER, "XMLCategoryFile::load(): pTxtFile is NULL!");
		}

		sStr.str(pTxtFile->getString());

		Poco::Util::XMLConfiguration::load(sStr);
	}

} // namespace Educational

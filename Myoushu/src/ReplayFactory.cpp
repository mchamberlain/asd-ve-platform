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
 * @file ReplayFactory.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "ReplayFactory.h"

namespace Myoushu
{
	ReplayFactory::ReplayFactory()
	{
	}

	ReplayFactory::~ReplayFactory()
	{
	}

	Replay* ReplayFactory::make(const std::string& replayName)
	{
		Replay *pReplay;
		std::string newName;

		newName = this->ensureUniqueName(replayName);

		pReplay = new Replay(newName);
		add(pReplay);

		return pReplay;
	}

	Replay* ReplayFactory::make(const std::string& replayName, bool ensureUniqueName)
	{
		Replay *pReplay;
		std::string newName;

		newName = this->ensureUniqueName(replayName);

		if (((newName != replayName) && (!ensureUniqueName)) || (newName == replayName))
		{
			// Create a new instance and add it to the factory
			pReplay = new Replay(newName);
			add(pReplay);
		}
		else
		{
			// Find the existing instance
			pReplay = static_cast<Replay*>(findByName(replayName));
		}

		return pReplay;
	}

	Replay* ReplayFactory::make(const std::string& className, const std::string& name) throw (Exception)
	{
		Replay *pReplay;

		pReplay = NULL;

		if (className == NamedObject<Replay>::getStaticClassName())
		{
			// Create Replay instance
			pReplay = new Replay(name);
			add(pReplay);
		}

		return pReplay;
	}

	Replay* ReplayFactory::make(const std::string& replayName, const std::string& resourceGroup, bool openForWrite, bool overwrite)
	{
		Replay *pReplay;
		std::string newName;

		newName = ensureUniqueName(replayName);

		// Create a new instance and add it to the factory
		pReplay = new Replay(newName);

		try
		{
			// Open for reading or writing, as appropriate
			if (!openForWrite)
			{
				// Open for reading
				pReplay->openForPlayback(resourceGroup);
			}
			else
			{
				// Open for writing
				pReplay->openForWriting(resourceGroup, overwrite);
			}
		}
		catch (Exception &e)
		{
			// An error occurred, destroy pReplay and rethrow the exception
			delete pReplay;
			pReplay = NULL;

			throw e;
		}

		if (pReplay != NULL)
		{
			add(pReplay);
		}

		return pReplay;
	}

} // namespace Myoushu

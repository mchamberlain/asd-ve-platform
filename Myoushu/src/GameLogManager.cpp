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
 * @file GameLogManager.cpp
 * @author ME Chamberlain
 * @date May 2009
 */

#include "GameLogManager.h"

namespace Myoushu
{
	GameLogManager::GameLogManager()
	{
	}

	GameLogManager::~GameLogManager()
	{
	}

	void GameLogManager::addEntity(GameLogEntity *pEntity) throw (Exception)
	{
		std::string name;

		// Check that pEntity is not NULL
		if (pEntity == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "GameLogManager::addEntity(): pEntity is NULL.");
		}

		if (pEntity->getName() != ensureUniqueName(pEntity->getName()))
		{
			// An entity with the same name already exists, throw an exception
			throw Exception(Exception::E_INVALID_PARAMETERS, "GameLogManager::addEntity(): an entity with the name " + pEntity->getName() + " already exists in this manager.");
		}

		add(pEntity);
	}

	GameLogEntity* GameLogManager::getEntity(const std::string& name)
	{
		return static_cast<GameLogEntity*>(findByName(name));
	}

} // namespace Myoushu

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
 * @file PoolObject.cpp
 * @author ME Chamberlain
 * @date July 2008
 */

#include "PoolObject.h"
#include "ObjectPoolBase.h"
#include "TimerTaskMessage.h"
#include "EngineLog.h"

namespace Myoushu
{

	CLASS_NAME(PoolObject, "Myoushu::PoolObject");

	PoolObject::PoolObject() : pool(NULL)
	{
	}

	PoolObject::PoolObject(ObjectPoolBase *pool) : pool(pool)
	{
	}

	PoolObject::~PoolObject()
	{
		pool = NULL;
	}

	void PoolObject::returnToPool(bool autoDelete)
	{
		// Check that the pool exists
		if (pool != NULL)
		{
			try
			{
				// Try to add the instance to the object pool
				pool->add(this, autoDelete);
			}
			catch (Exception& e)
			{
				LOG(EngineLog::LM_ERROR, "Caught exception when trying to return an object to its parent object pool: " << e.what());
				// if autoDelete is true delete the object
				if (autoDelete)
				{
					delete this;
				}
			}
			catch (...)
			{
				LOG(EngineLog::LM_ERROR, "Caught an unknown exception when trying to return an object to its parent object pool, probably the pool does not exist anymore.");
				// if autoDelete is true delete the object
				if (autoDelete)
				{
					delete this;
				}
			}
		}
		else {
			// If that failed (pool is full or doesn't exist), free the object directly
			if ((pool == NULL) && (autoDelete))
			{
				delete this;
			}
		}
	}

} // Myoushu
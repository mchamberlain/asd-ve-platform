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
 * @file NotificationObserverForFunctor.cpp
 * @author ME Chamberlain
 * @date June 2009
 */

#include "NotificationObserverForFunctor.h"

namespace Myoushu
{
	NotificationObserverForFunctor::NotificationObserverForFunctor()
	{
	}

	NotificationObserverForFunctor::~NotificationObserverForFunctor()
	{
	}

	void NotificationObserverForFunctor::getMessageTypes(std::list<std::string> &messageTypeList) const
	{
		std::map<std::string, FunctorBase*>::const_iterator iter;

		Poco::ScopedRWLock lock(mRWLock, false);

		messageTypeList.clear();
		for (iter = mFunctorMap.begin(); iter != mFunctorMap.end(); ++iter)
		{
			messageTypeList.push_back(iter->first);
		}
	}

	FunctorBase* NotificationObserverForFunctor::removeFunctor(const std::string& messageType)
	{
		std::map<std::string, FunctorBase*>::iterator iter;
		FunctorBase *pFunctor;

		Poco::ScopedRWLock lock(mRWLock, true);

		// Find the Functor mapped to the supplied message type
		iter = mFunctorMap.find(messageType);
		// If the there is no such mapping, return NULL
		if (iter == mFunctorMap.end())
		{
			return NULL;
		}

		// If the mapping exists, remove it from the map and return the mapped FunctorBase instance
		pFunctor = iter->second;
		mFunctorMap.erase(iter);

		return pFunctor;
	}

} // namespace Myoushu

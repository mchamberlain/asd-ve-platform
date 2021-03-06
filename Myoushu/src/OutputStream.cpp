/*
This file is part of the ASD Assist VE Platform.

For the latest info, see http://asd-ve-platform.sourceforge.net/

Copyright (c) 2009 Morn� Chamberlain & Stellenbosch University

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
 * @file OutputStream.cpp
 * @author ME Chamberlain
 * @date May 2008
 */

#include "OutputStream.h"

namespace Myoushu
{
	OutputStream::OutputStream(std::ostream &out) : out(out)
	{
	}

	OutputStream::~OutputStream()
	{
	}

	OutputStream& OutputStream::operator<<(const std::string& message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << message;

		return *this;
	}

	OutputStream& OutputStream::operator<<(const char* message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << message;

		return *this;
	}

	OutputStream& OutputStream::operator<<(const char& message)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << message;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const bool& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const short& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const unsigned short& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const int& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const unsigned int& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const long& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const unsigned long& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const float& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const double& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const long double& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

	OutputStream& OutputStream::operator<< (const void*& val)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		// Output the message
		out << val;

		return *this;
	}

} // Myoushu

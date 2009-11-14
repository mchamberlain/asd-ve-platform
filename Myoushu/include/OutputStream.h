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
 * @file OutputStream.h
 * @author ME Chamberlain
 * @date May 2008
 */

#ifndef OUTPUT_STREAM_H
#define OUTPUT_STREAM_H

#include <ostream>

#include "Poco/RWLock.h"

#include "Platform.h"
#include "Exception.h"

namespace Myoushu
{
	/**
	 * Base class for classes that can serve as output streams. This class requires a std::ostream that it
	 * uses for output. The user must initialize and pass a std::ostream to the constructor of an instance of
	 * this class.
	 */
	class MYOUSHU_API OutputStream
	{
		public:
			/**
			 * Constructor.
			 * @param ostream A reference to a std C++ ostream to use.
			 */
			OutputStream(std::ostream &out);

			/** Destructor */
			virtual ~OutputStream();

			/** Write the specified message.
			 * @param message The message to write.
			 */
			virtual OutputStream& operator<<(const std::string& message);

			/** Write the specified message.
			 * @param message The message to write.
			 */
			virtual OutputStream& operator<<(const char* message);

			/** Write the specified message.
			 * @param message The message to write.
			 */
			virtual OutputStream& operator<<(const char& message);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const bool& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const short& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const unsigned short& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const int& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const unsigned int& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const long& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const unsigned long& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const float& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const double& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const long double& val);

			/** Write the specified value.
			 * @param val The value to write.
			 */
			virtual OutputStream& operator<< (const void*& val);

		protected:
			/** Read/write lock for thread safety */
			mutable Poco::RWLock rwLock;
			/** std C++ output stream instance to use */
			std::ostream &out;
	};
} // Myoushu

#endif

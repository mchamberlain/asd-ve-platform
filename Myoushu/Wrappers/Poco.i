%module Poco
%{
	#include "Poco/ReferenceCounterBase.h"
	#include "Poco/RefCountedObject.h"
	#include "Poco/AutoPtr.h"
	#include "Poco/Util/AbstractConfiguration.h"
	#include "Poco/Util/MapConfiguration.h"
%}

#ifdef Foundation_API
#	undef Foundation_API
#endif
#define Foundation_API

#ifdef Util_API
#	undef Util_API
#endif
#define Util_API

// Proper Java enums
#ifdef SWIGJAVA
%include "enums.swg"
#endif

%include "std_string.i"

%include "../../3rdparty/poco-1.3.2/Foundation/include/Poco/ReferenceCounterBase.h"
%include "../../3rdparty/poco-1.3.2/Foundation/include/Poco/RefCountedObject.h"
%include "../../3rdparty/poco-1.3.2/Foundation/include/Poco/AutoPtr.h"
%include "../../3rdparty/poco-1.3.2/Util/include/Poco/Util/AbstractConfiguration.h"
%include "../../3rdparty/poco-1.3.2/Util/include/Poco/Util/MapConfiguration.h"

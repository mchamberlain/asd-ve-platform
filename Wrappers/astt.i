%module ASTT

%{
	// To solve std::max and std::min issues with MSVC
	#define NOMINMAX
	
	#ifdef SWIGLUA
	// Ensure that the ASTTLua.h file is not included with the ASTTLua.cpp file
	#	define ASTT_LUA_H
	#endif
	
	#include <string>
	#include <list>
	#include <map>
	#include <vector>
	
	#include "ASTTPlatform.h"
	#include "EducationalQuestion.h"
	#include "EducationalQuestionsCategory.h"
	#include "EducationalQuestionsManager.h"
	#include "XMLCategoryFile.h"
	
	#ifdef SWIGJAVA
	#	include "JavaFunctor.h"
	#endif
	
%}

#ifdef SWIGJAVA
/* Modify the default javabody typemap so that we have public access to the constructors of the proxy classes that creates java instances
   from the supplied pointer to the instance in C++. This allows us to ease passing objects as parameters in functors as we just pass the C++
   pointer and then create the relevant Java object around it when the Java method is invoked through the functor.
*/
%typemap(javabody) SWIGTYPE %{
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

%typemap(javabody_derived) SWIGTYPE %{
  private long swigCPtr;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    super($imclassname.SWIG$javaclassnameUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}
#endif

#ifdef SWIGLUA
	%include "luatypemaps.swg"
#endif

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"

%template(VectorInt) std::vector<int>;
%template(VectorUInt) std::vector<unsigned int>;
%template(VectorChar) std::vector<char>;
%template(VectorDouble) std::vector<double>;
%template(VectorFloat) std::vector<float>;
%template(VectorLong) std::vector<long>;
%template(VectorBool) std::vector<bool>;
%template(VectorString) std::vector<std::string>;

%template(ListInt) std::list<int>;
%template(ListUInt) std::list<unsigned int>;
%template(ListChar) std::list<char>;
%template(ListDouble) std::list<double>;
%template(ListFloat) std::list<float>;
%template(ListLong) std::list<long>;
%template(ListBool) std::list<bool>;
%template(ListString) std::list<std::string>;

%include "../3rdparty/ogre/ogremain/include/OgreSingleton.h"

%template(Singleton_EducationalQuestionsManager) Ogre::Singleton<Educational::EducationalQuestionsManager>;

%include "ASTTPlatform.h"
%include "EducationalQuestion.h"
%include "EducationalQuestionsCategory.h"
%include "EducationalQuestionsManager.h"
%include "XMLCategoryFile.h"

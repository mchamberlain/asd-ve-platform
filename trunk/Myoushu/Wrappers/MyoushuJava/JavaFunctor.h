/**
 * @file JavaFunctor.h
 * @author ME Chamberlain
 * @date January 2009
 */

#ifndef JAVA_FUNCTOR_H
#define JAVA_FUNCTOR_H

#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <assert.h>

#include "Poco/RWLock.h"
#include "jni.h"

#include "MyoushuJavaPlatform.h"
#include "FunctorBase.h"
#include "Cloneable.h"

namespace Myoushu
{
	/**
	 * A java function wrapper that allows functions with up to three parameters. All parameters are stored "by-value" in the functor
	 * instance. For pointer types use references instead of pointers as the functor converts everything into pointers
	 * internally.
	 */
	class MYOUSHU_JAVA_API JavaFunctor : public FunctorBase, public NamedObject<JavaFunctor>
	{
		public:
			/**
			 * Constructor.
			 * @param name Instance name.
			 */
			JavaFunctor(const std::string& name = "JavaFunctor");

			/**
			 * Constructor for a Java Function with no parameters.
			 * @param functionName The Java function name.
			 */
			JavaFunctor(unsigned int numParams);

			/** Destructor */
			virtual ~JavaFunctor();

			CLASS_NAME_FUNCTIONS(JavaFunctor);

			/** Sets the number of parameters that this functor can pass to its underlying function. */
			void setNumParams(unsigned int numParams);

			/** Gets the number of parameters that this functor can pass to its underlying function. */
			unsigned int getNumParams() const;

			/**
			 * Set the a parameter to pass to the wrapped function.
			 * @param index The index of the parameter to set, starts from 0.
			 * @param parameter The value to set the parameter too.
			 */
			void setParameter(unsigned int index, jvalue parameter);

			/**
			 * Set the a parameter to pass to the wrapped function.
			 * @param index The index of the parameter to set, starts from 0.
			 * @param parameter The value to set the parameter too. It is assumed that a jvalue is saved in the mLong field in v.
			 */
			virtual void setParameter(unsigned int index, Value v) throw (Exception);

			/**
			 * Clones the functor.
			 * @return A new cloned instance.
			 */
			Cloneable* clone() const;

			/** 
			 * Sets the JNI environment to use and the ID of the Java method to call. This method should be called by a
			 * JNI wrapper method from Java.
			 * @param pEnv Pointer to the JNIEnv instance to use.
			 * @param cls The Java class object that contains the method. Needed in the case of static methods.
			 * @param obj The jobject that contains this method. This must be NULL for static methods.
			 * @param methodID The ID of the Java method to call.
			 */
			void setMethod(JavaVM *pJVM, jclass cls, jobject obj, jmethodID methodID);

			/** Stub method so that SWIG generates a compatible method in the Java interface for our JNI method declared below this class. */
			void setMethod(jobject, char *, char *);

			/**
			 * Execute the Java function that is wrapped in this functor.
			 * @return The value the Java function returned.
			 * @throws Exception::E_NULL_POINTER if any required pointer is NULL, most importantly pEnv.
			 * @throws Exception::E_INVALID_PARAMETER if one of the parameters that should be passed to the JAVA function is not defined 
			 *			in the JAVA state.
			 */
			void operator()() throw (Exception);

		protected:
			/** Read/write mutex for thread safety */
			mutable Poco::RWLock rwLock;

		private:
			/** The number of parameters the function takes */
			unsigned int mNumParams;
			/** The parameters that should be passed to the java method */
			jvalue *mpParameters;
			/** The JVM instance to use when calling the method. */
			JavaVM *mpJVM;
			/** The Java class object required in the case of static methods. */
			jclass mClass;
			/** The object that contains the method to call. Must be NULL in the case of static methods. */
			jobject mObj;
			/** The java method to call, this is set by the setMethod function. */
			jmethodID mMethodID;
	};

	// inlines
	inline void JavaFunctor::setParameter(unsigned int index, jvalue parameter)
	{
		if (index >= mNumParams)
		{
			throw Exception(Exception::E_INDEX_OUT_OF_BOUNDS, "JavaFunctor::setParameter(): index out of bounds.");
		}

		Poco::ScopedRWLock lock(rwLock, true);

		mpParameters[index] = parameter;
	}

	inline unsigned int JavaFunctor::getNumParams() const
	{
		Poco::ScopedRWLock lock(rwLock, false);

		return mNumParams;
	}

} // Myoushu

#ifndef SWIGJAVA
/**
 * Global function that wraps Myoushu::JavaFunctor::setMethod().
 * @param pEnv The JNI environment.
 * @param cls The Java proxy class containing the function.
 * @param jarg1 The JavaFunctor instance this method is called on.
 * @param _jarg1 A jobject reference to the Java version JavaFunctor instance this method is called on.
 * @param obj The Java Object that contains the method to be called by the functor.
 * @param methodName The name of the method to be called by the functor.
 * @param methodSignature The signature of the method to be called by the functor.
 */
extern "C"
{
	JNIEXPORT void JNICALL Java_MyoushuJava_MyoushuJNI_JavaFunctor_1setMethod(JNIEnv *pEnv, jclass cls, jlong jarg1, jobject _jarg1, jobject obj, jstring methodName, jstring methodSignature);
}
#endif

#endif

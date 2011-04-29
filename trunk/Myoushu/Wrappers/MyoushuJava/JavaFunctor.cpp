/**
 * @file JavaFunctor.cpp
 * @author ME Chamberlain
 * @date January 2009
 */

#include <iostream>

#include "Poco/RefCountedObject.h"

#include "JavaFunctor.h"
#include "EngineLog.h"
#include "Message.h"

namespace Myoushu
{
	CLASS_NAME(JavaFunctor, "Myoushu::JavaFunctor");

	JavaFunctor::JavaFunctor(const std::string& name) : FunctorBase(name), mNumParams(0), mpParameters(NULL), mpJVM(NULL), mClass(NULL), mObj(NULL), mMethodID(NULL)
	{
	}

	JavaFunctor::JavaFunctor(unsigned int numParams) : mNumParams(numParams), mpJVM(NULL), mClass(NULL), mObj(NULL), mMethodID(NULL)
	{
		if (mNumParams > 0)
		{
			mpParameters = new jvalue[mNumParams];
		}
		else
		{
			mpParameters = NULL;
		}
	}

	JavaFunctor::~JavaFunctor()
	{
		JNIEnv *pEnv;

		if (mpParameters)
		{
			delete [] mpParameters;
			mpParameters = NULL;
		}
		// If we have the JVM instance then we possibly have a global object reference from a previous setMethod call. Thus
		// we must release said reference otherwise the Java garbage collector will not be able to release the object.
		if (mpJVM != NULL)
		{
			mpJVM->AttachCurrentThread(reinterpret_cast<void**>(&pEnv), NULL);
			if (mObj != NULL)
			{
				pEnv->DeleteGlobalRef(mObj);
				mObj = NULL;
			}
			mpJVM->DetachCurrentThread();
			mpJVM = NULL;
		}
	}

	void JavaFunctor::setNumParams(unsigned int numParams)
	{
		Poco::ScopedRWLock lock(rwLock, true);

		mNumParams = numParams;
		if (mpParameters != NULL)
		{
			delete [] mpParameters;
			mpParameters = NULL;
		}
		mpParameters = new jvalue[mNumParams];
	}

	Cloneable* JavaFunctor::clone() const
	{
		JavaFunctor *newFunctor;

		Poco::ScopedRWLock lock(rwLock, false);

		newFunctor = new JavaFunctor(mNumParams);

		newFunctor->setMethod(mpJVM, mClass, mObj, mMethodID);

		return newFunctor;
	}

	void JavaFunctor::setParameter(unsigned int index, Value v) throw (Exception)
	{
		setParameter(index, v.getJValue( true ));
	}

	void JavaFunctor::setMethod(JavaVM *pJVM, jclass cls, jobject obj, jmethodID methodID)
	{
		JNIEnv *pEnv;

		Poco::ScopedRWLock lock(rwLock, true);

		// If we have the JVM instance then we possibly have a global object reference from a previous setMethod call. Thus
		// we must release said reference otherwise the Java garbage collector will not be able to release the object.
		if (mpJVM != NULL)
		{
			mpJVM->AttachCurrentThread(reinterpret_cast<void**>(&pEnv), NULL);
			if (mObj != NULL)
			{
				pEnv->DeleteGlobalRef(mObj);
			}
			mpJVM->DetachCurrentThread();
		}

		mpJVM = pJVM;
		mClass = cls;
		mObj = obj;
		mMethodID = methodID;
	}

	void JavaFunctor::operator()() throw (Exception)
	{
		JNIEnv *pEnv;

		Poco::ScopedRWLock lock(rwLock, false);

		if (mpJVM == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Myoushu::JavaFunctor::operator()(): mpJVM is NULL.");
		}

		if (mMethodID == NULL)
		{
			throw Exception(Exception::E_NULL_POINTER, "Myoushu::JavaFunctor::operator()(): mMethodID is NULL: not method has been set.");
		}

		if (mObj == NULL)
		{
			// Static method
			if (mClass == NULL)
			{
				throw Exception(Exception::E_NULL_POINTER, "Myoushu::JavaFunctor::operator()(): mClass is NULL with a static method.");
			}

			mpJVM->AttachCurrentThread(reinterpret_cast<void**>(&pEnv), NULL);
			pEnv->CallStaticVoidMethodA(mClass, mMethodID, mpParameters);
			mpJVM->DetachCurrentThread();
		}
		else
		{
			// Non-static method
			mpJVM->AttachCurrentThread(reinterpret_cast<void**>(&pEnv), NULL);
			pEnv->CallVoidMethodA(mObj, mMethodID, mpParameters);
			mpJVM->DetachCurrentThread();
		}
	}


} // Myoushu

JNIEXPORT void JNICALL Java_MyoushuJava_MyoushuJNI_JavaFunctor_1setMethod(JNIEnv *pEnv, jclass cls, jlong jarg1, jobject _jarg1, jobject obj, jstring methodName, jstring methodSignature)
{
	Myoushu::JavaFunctor *functor;
	std::string pMethodName;
	std::string pMethodSignature;
	const char *pStr;
	jclass targetClass;
	jmethodID methodID;
	JavaVM *jvm;

	//(void)_jarg1;

	//functor = *(Myoushu::JavaFunctor **)&jarg1;
	functor = reinterpret_cast<Myoushu::JavaFunctor*>(jarg1);

	pStr = pEnv->GetStringUTFChars(methodName, 0);
	pMethodName.assign(pStr);
	pEnv->ReleaseStringUTFChars(methodName, pStr);

	pStr = pEnv->GetStringUTFChars(methodSignature, 0);
	pMethodSignature.assign(pStr);
	pEnv->ReleaseStringUTFChars(methodSignature, pStr);

	targetClass = pEnv->GetObjectClass(obj);
	obj = pEnv->NewGlobalRef(obj);
	methodID = pEnv->GetMethodID(targetClass, pMethodName.c_str(), pMethodSignature.c_str());

	pEnv->GetJavaVM(&jvm);
	functor->setMethod(jvm, targetClass, obj, methodID);
}

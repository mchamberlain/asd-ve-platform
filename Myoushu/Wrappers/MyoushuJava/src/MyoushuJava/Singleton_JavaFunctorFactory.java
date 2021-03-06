/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_JavaFunctorFactory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_JavaFunctorFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_JavaFunctorFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_JavaFunctorFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_JavaFunctorFactory() {
    this(MyoushuJNI.new_Singleton_JavaFunctorFactory(), true);
  }

  public static JavaFunctorFactory getSingleton() {
    return new JavaFunctorFactory(MyoushuJNI.Singleton_JavaFunctorFactory_getSingleton(), false);
  }

  public static JavaFunctorFactory getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_JavaFunctorFactory_getSingletonPtr();
    return (cPtr == 0) ? null : new JavaFunctorFactory(cPtr, false);
  }

}

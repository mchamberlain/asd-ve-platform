/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_ReplayFactory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_ReplayFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_ReplayFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_ReplayFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_ReplayFactory() {
    this(MyoushuJNI.new_Singleton_ReplayFactory(), true);
  }

  public static ReplayFactory getSingleton() {
    return new ReplayFactory(MyoushuJNI.Singleton_ReplayFactory_getSingleton(), false);
  }

  public static ReplayFactory getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_ReplayFactory_getSingletonPtr();
    return (cPtr == 0) ? null : new ReplayFactory(cPtr, false);
  }

}
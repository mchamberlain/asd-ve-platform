/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_NetworkListenTask {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_NetworkListenTask(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_NetworkListenTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_NetworkListenTask(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_NetworkListenTask() {
    this(MyoushuJNI.new_Singleton_NetworkListenTask(), true);
  }

  public static NetworkListenTask getSingleton() {
    return new NetworkListenTask(MyoushuJNI.Singleton_NetworkListenTask_getSingleton(), false);
  }

  public static NetworkListenTask getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_NetworkListenTask_getSingletonPtr();
    return (cPtr == 0) ? null : new NetworkListenTask(cPtr, false);
  }

}

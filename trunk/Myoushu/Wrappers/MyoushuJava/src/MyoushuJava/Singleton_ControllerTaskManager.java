/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_ControllerTaskManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_ControllerTaskManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_ControllerTaskManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_ControllerTaskManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_ControllerTaskManager() {
    this(MyoushuJNI.new_Singleton_ControllerTaskManager(), true);
  }

  public static ControllerTaskManager getSingleton() {
    return new ControllerTaskManager(MyoushuJNI.Singleton_ControllerTaskManager_getSingleton(), false);
  }

  public static ControllerTaskManager getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_ControllerTaskManager_getSingletonPtr();
    return (cPtr == 0) ? null : new ControllerTaskManager(cPtr, false);
  }

}

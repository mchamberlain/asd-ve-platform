/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_GUIManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_GUIManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_GUIManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_GUIManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_GUIManager() {
    this(MyoushuJNI.new_Singleton_GUIManager(), true);
  }

  public static GUIManager getSingleton() {
    return new GUIManager(MyoushuJNI.Singleton_GUIManager_getSingleton(), false);
  }

  public static GUIManager getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_GUIManager_getSingletonPtr();
    return (cPtr == 0) ? null : new GUIManager(cPtr, false);
  }

}

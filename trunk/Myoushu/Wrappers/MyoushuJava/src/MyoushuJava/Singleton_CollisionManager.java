/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_CollisionManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_CollisionManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_CollisionManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_CollisionManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_CollisionManager() {
    this(MyoushuJNI.new_Singleton_CollisionManager(), true);
  }

  public static CollisionManager getSingleton() {
    return new CollisionManager(MyoushuJNI.Singleton_CollisionManager_getSingleton(), false);
  }

  public static CollisionManager getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_CollisionManager_getSingletonPtr();
    return (cPtr == 0) ? null : new CollisionManager(cPtr, false);
  }

}
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_ObjectPool_ReplayMessage {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_ObjectPool_ReplayMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_ObjectPool_ReplayMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Singleton_ObjectPool_ReplayMessage(swigCPtr);
    }
    swigCPtr = 0;
  }

  public Singleton_ObjectPool_ReplayMessage() {
    this(MyoushuJNI.new_Singleton_ObjectPool_ReplayMessage(), true);
  }

  public static ObjectPool_ReplayMessage getSingleton() {
    return new ObjectPool_ReplayMessage(MyoushuJNI.Singleton_ObjectPool_ReplayMessage_getSingleton(), false);
  }

  public static ObjectPool_ReplayMessage getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_ObjectPool_ReplayMessage_getSingletonPtr();
    return (cPtr == 0) ? null : new ObjectPool_ReplayMessage(cPtr, false);
  }

}

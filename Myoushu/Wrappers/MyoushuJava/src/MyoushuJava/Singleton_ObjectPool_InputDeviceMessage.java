/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_ObjectPool_InputDeviceMessage {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_ObjectPool_InputDeviceMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_ObjectPool_InputDeviceMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Singleton_ObjectPool_InputDeviceMessage(swigCPtr);
    }
    swigCPtr = 0;
  }

  public Singleton_ObjectPool_InputDeviceMessage() {
    this(MyoushuJNI.new_Singleton_ObjectPool_InputDeviceMessage(), true);
  }

  public static ObjectPool_InputDeviceMessage getSingleton() {
    return new ObjectPool_InputDeviceMessage(MyoushuJNI.Singleton_ObjectPool_InputDeviceMessage_getSingleton(), false);
  }

  public static ObjectPool_InputDeviceMessage getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_ObjectPool_InputDeviceMessage_getSingletonPtr();
    return (cPtr == 0) ? null : new ObjectPool_InputDeviceMessage(cPtr, false);
  }

}
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_NetworkManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_NetworkManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_NetworkManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_NetworkManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_NetworkManager() {
    this(MyoushuJNI.new_Singleton_NetworkManager(), true);
  }

  public static NetworkManager getSingleton() {
    return new NetworkManager(MyoushuJNI.Singleton_NetworkManager_getSingleton(), false);
  }

  public static NetworkManager getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_NetworkManager_getSingletonPtr();
    return (cPtr == 0) ? null : new NetworkManager(cPtr, false);
  }

}

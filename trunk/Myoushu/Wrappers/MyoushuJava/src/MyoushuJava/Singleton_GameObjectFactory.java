/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_GameObjectFactory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_GameObjectFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_GameObjectFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_GameObjectFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_GameObjectFactory() {
    this(MyoushuJNI.new_Singleton_GameObjectFactory(), true);
  }

  public static GameObjectFactory getSingleton() {
    return new GameObjectFactory(MyoushuJNI.Singleton_GameObjectFactory_getSingleton(), false);
  }

  public static GameObjectFactory getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_GameObjectFactory_getSingletonPtr();
    return (cPtr == 0) ? null : new GameObjectFactory(cPtr, false);
  }

}

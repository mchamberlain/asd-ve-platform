/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_SceneFactory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_SceneFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_SceneFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_SceneFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_SceneFactory() {
    this(MyoushuJNI.new_Singleton_SceneFactory(), true);
  }

  public static SceneFactory getSingleton() {
    return new SceneFactory(MyoushuJNI.Singleton_SceneFactory_getSingleton(), false);
  }

  public static SceneFactory getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_SceneFactory_getSingletonPtr();
    return (cPtr == 0) ? null : new SceneFactory(cPtr, false);
  }

}

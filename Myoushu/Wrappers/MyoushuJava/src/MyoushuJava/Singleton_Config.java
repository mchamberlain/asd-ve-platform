/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_Config {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_Config(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_Config obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_Config(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_Config() {
    this(MyoushuJNI.new_Singleton_Config(), true);
  }

  public static Config getSingleton() {
    return new Config(MyoushuJNI.Singleton_Config_getSingleton(), false);
  }

  public static Config getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_Config_getSingletonPtr();
    return (cPtr == 0) ? null : new Config(cPtr, false);
  }

}

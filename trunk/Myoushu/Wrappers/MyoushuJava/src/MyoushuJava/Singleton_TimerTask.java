/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_TimerTask {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_TimerTask(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_TimerTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Singleton_TimerTask(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Singleton_TimerTask() {
    this(MyoushuJNI.new_Singleton_TimerTask(), true);
  }

  public static TimerTask getSingleton() {
    return new TimerTask(MyoushuJNI.Singleton_TimerTask_getSingleton(), false);
  }

  public static TimerTask getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_TimerTask_getSingletonPtr();
    return (cPtr == 0) ? null : new TimerTask(cPtr, false);
  }

}

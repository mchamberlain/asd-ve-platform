/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Singleton_SQLiteGameLogManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Singleton_SQLiteGameLogManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Singleton_SQLiteGameLogManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Singleton_SQLiteGameLogManager(swigCPtr);
    }
    swigCPtr = 0;
  }

  public Singleton_SQLiteGameLogManager() {
    this(MyoushuJNI.new_Singleton_SQLiteGameLogManager(), true);
  }

  public static SQLiteGameLogManager getSingleton() {
    return new SQLiteGameLogManager(MyoushuJNI.Singleton_SQLiteGameLogManager_getSingleton(), false);
  }

  public static SQLiteGameLogManager getSingletonPtr() {
    long cPtr = MyoushuJNI.Singleton_SQLiteGameLogManager_getSingletonPtr();
    return (cPtr == 0) ? null : new SQLiteGameLogManager(cPtr, false);
  }

}

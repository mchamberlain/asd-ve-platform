/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class FunctorManager extends Singleton_FunctorManager {
  private long swigCPtr;

  public FunctorManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGFunctorManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(FunctorManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_FunctorManager(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public FunctorManager() {
    this(MyoushuJNI.new_FunctorManager(), true);
  }

  public void registerFunctorFactory(FunctorFactory pFunctorFactory, String className) {
    MyoushuJNI.FunctorManager_registerFunctorFactory(swigCPtr, this, FunctorFactory.getCPtr(pFunctorFactory), pFunctorFactory, className);
  }

  public FunctorFactory unregisterFunctorFactory(String className) {
    long cPtr = MyoushuJNI.FunctorManager_unregisterFunctorFactory(swigCPtr, this, className);
    return (cPtr == 0) ? null : new FunctorFactory(cPtr, false);
  }

  public FunctorBase make(String className, String instanceName) {
    long cPtr = MyoushuJNI.FunctorManager_make(swigCPtr, this, className, instanceName);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public boolean destroy(FunctorBase pInstance) {
    return MyoushuJNI.FunctorManager_destroy(swigCPtr, this, FunctorBase.getCPtr(pInstance), pInstance);
  }

}

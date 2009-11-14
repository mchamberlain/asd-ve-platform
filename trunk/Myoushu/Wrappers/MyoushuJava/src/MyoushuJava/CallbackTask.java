/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class CallbackTask extends Task {
  private long swigCPtr;

  public CallbackTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCallbackTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(CallbackTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_CallbackTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public CallbackTask(int priority, String name, long executionInterval, long iterationLimit) {
    this(MyoushuJNI.new_CallbackTask__SWIG_0(priority, name, executionInterval, iterationLimit), true);
  }

  public CallbackTask(int priority, String name, long executionInterval) {
    this(MyoushuJNI.new_CallbackTask__SWIG_1(priority, name, executionInterval), true);
  }

  public CallbackTask(int priority, String name) {
    this(MyoushuJNI.new_CallbackTask__SWIG_2(priority, name), true);
  }

  public CallbackTask() {
    this(MyoushuJNI.new_CallbackTask__SWIG_3(), true);
  }

  public String getClassName() {
    return MyoushuJNI.CallbackTask_getClassName(swigCPtr, this);
  }

  public void init() {
    MyoushuJNI.CallbackTask_init(swigCPtr, this);
  }

  public void suspend() {
    MyoushuJNI.CallbackTask_suspend(swigCPtr, this);
  }

  public void execute(long timeDelta) {
    MyoushuJNI.CallbackTask_execute(swigCPtr, this, timeDelta);
  }

  public void kill() {
    MyoushuJNI.CallbackTask_kill(swigCPtr, this);
  }

  public void setInitCallback(FunctorBase pFunctor) {
    MyoushuJNI.CallbackTask_setInitCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setInitCallback(String luaFunctionName) {
    MyoushuJNI.CallbackTask_setInitCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setSuspendCallback(FunctorBase pFunctor) {
    MyoushuJNI.CallbackTask_setSuspendCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setSuspendCallback(String luaFunctionName) {
    MyoushuJNI.CallbackTask_setSuspendCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setExecuteCallback(FunctorBase pFunctor) {
    MyoushuJNI.CallbackTask_setExecuteCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setExecuteCallback(String luaFunctionName) {
    MyoushuJNI.CallbackTask_setExecuteCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setKillCallback(FunctorBase pFunctor) {
    MyoushuJNI.CallbackTask_setKillCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setKillCallback(String luaFunctionName) {
    MyoushuJNI.CallbackTask_setKillCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public FunctorBase getInitCallback() {
    long cPtr = MyoushuJNI.CallbackTask_getInitCallback(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public FunctorBase getSuspendCallback() {
    long cPtr = MyoushuJNI.CallbackTask_getSuspendCallback(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public FunctorBase getExecuteCallback() {
    long cPtr = MyoushuJNI.CallbackTask_getExecuteCallback(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public FunctorBase getKillCallback() {
    long cPtr = MyoushuJNI.CallbackTask_getKillCallback(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

}

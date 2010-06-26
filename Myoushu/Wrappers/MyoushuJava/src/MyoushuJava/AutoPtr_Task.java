/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_Task {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_Task(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_Task obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_Task(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_Task() {
    this(MyoushuJNI.new_AutoPtr_Task__SWIG_0(), true);
  }

  public AutoPtr_Task(Task ptr) {
    this(MyoushuJNI.new_AutoPtr_Task__SWIG_1(Task.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Task(Task ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_Task__SWIG_2(Task.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_Task(AutoPtr_Task ptr) {
    this(MyoushuJNI.new_AutoPtr_Task__SWIG_3(AutoPtr_Task.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Task assign(Task ptr) {
    return new AutoPtr_Task(MyoushuJNI.AutoPtr_Task_assign__SWIG_0(swigCPtr, this, Task.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_Task assign(Task ptr, boolean shared) {
    return new AutoPtr_Task(MyoushuJNI.AutoPtr_Task_assign__SWIG_1(swigCPtr, this, Task.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_Task assign(AutoPtr_Task ptr) {
    return new AutoPtr_Task(MyoushuJNI.AutoPtr_Task_assign__SWIG_2(swigCPtr, this, AutoPtr_Task.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_Task ptr) {
    MyoushuJNI.AutoPtr_Task_swap(swigCPtr, this, AutoPtr_Task.getCPtr(ptr), ptr);
  }

  public Task __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_Task___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Task(cPtr, false);
  }

  public Task __ref__() {
    return new Task(MyoushuJNI.AutoPtr_Task___ref____SWIG_0(swigCPtr, this), false);
  }

  public Task get() {
    long cPtr = MyoushuJNI.AutoPtr_Task_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Task(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_Task_isNull(swigCPtr, this);
  }

  public Task duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_Task_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new Task(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_Task_getClassName(swigCPtr, this);
  }

  public int getPriority() {
    return MyoushuJNI.AutoPtr_Task_getPriority(swigCPtr, this);
  }

  public long getExecutionInterval() {
    return MyoushuJNI.AutoPtr_Task_getExecutionInterval(swigCPtr, this);
  }

  public long getIterationLimit() {
    return MyoushuJNI.AutoPtr_Task_getIterationLimit(swigCPtr, this);
  }

  public Task.TaskState getState() {
    return Task.TaskState.swigToEnum(MyoushuJNI.AutoPtr_Task_getState(swigCPtr, this));
  }

  public long getTimeLastExecuted() {
    return MyoushuJNI.AutoPtr_Task_getTimeLastExecuted(swigCPtr, this);
  }

  public String getName() {
    return MyoushuJNI.AutoPtr_Task_getName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Task_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Task_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public void release() {
    MyoushuJNI.AutoPtr_Task_release(swigCPtr, this);
  }

  public int referenceCount() {
    return MyoushuJNI.AutoPtr_Task_referenceCount(swigCPtr, this);
  }

}

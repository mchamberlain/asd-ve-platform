/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_Replay {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_Replay(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_Replay obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_AutoPtr_Replay(swigCPtr);
    }
    swigCPtr = 0;
  }

  public AutoPtr_Replay() {
    this(MyoushuJNI.new_AutoPtr_Replay__SWIG_0(), true);
  }

  public AutoPtr_Replay(Replay ptr) {
    this(MyoushuJNI.new_AutoPtr_Replay__SWIG_1(Replay.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Replay(Replay ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_Replay__SWIG_2(Replay.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_Replay(AutoPtr_Replay ptr) {
    this(MyoushuJNI.new_AutoPtr_Replay__SWIG_3(AutoPtr_Replay.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Replay assign(Replay ptr) {
    return new AutoPtr_Replay(MyoushuJNI.AutoPtr_Replay_assign__SWIG_0(swigCPtr, this, Replay.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_Replay assign(Replay ptr, boolean shared) {
    return new AutoPtr_Replay(MyoushuJNI.AutoPtr_Replay_assign__SWIG_1(swigCPtr, this, Replay.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_Replay assign(AutoPtr_Replay ptr) {
    return new AutoPtr_Replay(MyoushuJNI.AutoPtr_Replay_assign__SWIG_2(swigCPtr, this, AutoPtr_Replay.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_Replay ptr) {
    MyoushuJNI.AutoPtr_Replay_swap(swigCPtr, this, AutoPtr_Replay.getCPtr(ptr), ptr);
  }

  public Replay __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_Replay___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public Replay __ref__() {
    return new Replay(MyoushuJNI.AutoPtr_Replay___ref____SWIG_0(swigCPtr, this), false);
  }

  public Replay get() {
    long cPtr = MyoushuJNI.AutoPtr_Replay_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_Replay_isNull(swigCPtr, this);
  }

  public Replay duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_Replay_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_Replay_getClassName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Replay_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Replay_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public String getName() {
    return MyoushuJNI.AutoPtr_Replay_getName(swigCPtr, this);
  }

  public void release() {
    MyoushuJNI.AutoPtr_Replay_release(swigCPtr, this);
  }

  public int referenceCount() {
    return MyoushuJNI.AutoPtr_Replay_referenceCount(swigCPtr, this);
  }

}
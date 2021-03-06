/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_FunctorBase {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_FunctorBase(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_FunctorBase obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_FunctorBase(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_FunctorBase() {
    this(MyoushuJNI.new_AutoPtr_FunctorBase__SWIG_0(), true);
  }

  public AutoPtr_FunctorBase(FunctorBase ptr) {
    this(MyoushuJNI.new_AutoPtr_FunctorBase__SWIG_1(FunctorBase.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_FunctorBase(FunctorBase ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_FunctorBase__SWIG_2(FunctorBase.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_FunctorBase(AutoPtr_FunctorBase ptr) {
    this(MyoushuJNI.new_AutoPtr_FunctorBase__SWIG_3(AutoPtr_FunctorBase.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_FunctorBase assign(FunctorBase ptr) {
    return new AutoPtr_FunctorBase(MyoushuJNI.AutoPtr_FunctorBase_assign__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_FunctorBase assign(FunctorBase ptr, boolean shared) {
    return new AutoPtr_FunctorBase(MyoushuJNI.AutoPtr_FunctorBase_assign__SWIG_1(swigCPtr, this, FunctorBase.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_FunctorBase assign(AutoPtr_FunctorBase ptr) {
    return new AutoPtr_FunctorBase(MyoushuJNI.AutoPtr_FunctorBase_assign__SWIG_2(swigCPtr, this, AutoPtr_FunctorBase.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_FunctorBase ptr) {
    MyoushuJNI.AutoPtr_FunctorBase_swap(swigCPtr, this, AutoPtr_FunctorBase.getCPtr(ptr), ptr);
  }

  public FunctorBase __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_FunctorBase___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public FunctorBase __ref__() {
    return new FunctorBase(MyoushuJNI.AutoPtr_FunctorBase___ref____SWIG_0(swigCPtr, this), false);
  }

  public FunctorBase get() {
    long cPtr = MyoushuJNI.AutoPtr_FunctorBase_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_FunctorBase_isNull(swigCPtr, this);
  }

  public FunctorBase duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_FunctorBase_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new FunctorBase(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_FunctorBase_getClassName(swigCPtr, this);
  }

  public void release() {
    MyoushuJNI.AutoPtr_FunctorBase_release(swigCPtr, this);
  }

  public int referenceCount() {
    return MyoushuJNI.AutoPtr_FunctorBase_referenceCount(swigCPtr, this);
  }

  public String getName() {
    return MyoushuJNI.AutoPtr_FunctorBase_getName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_FunctorBase_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_FunctorBase_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_GameLogEntity {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_GameLogEntity(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_GameLogEntity obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_GameLogEntity(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_GameLogEntity() {
    this(MyoushuJNI.new_AutoPtr_GameLogEntity__SWIG_0(), true);
  }

  public AutoPtr_GameLogEntity(GameLogEntity ptr) {
    this(MyoushuJNI.new_AutoPtr_GameLogEntity__SWIG_1(GameLogEntity.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_GameLogEntity(GameLogEntity ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_GameLogEntity__SWIG_2(GameLogEntity.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_GameLogEntity(AutoPtr_GameLogEntity ptr) {
    this(MyoushuJNI.new_AutoPtr_GameLogEntity__SWIG_3(AutoPtr_GameLogEntity.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_GameLogEntity assign(GameLogEntity ptr) {
    return new AutoPtr_GameLogEntity(MyoushuJNI.AutoPtr_GameLogEntity_assign__SWIG_0(swigCPtr, this, GameLogEntity.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_GameLogEntity assign(GameLogEntity ptr, boolean shared) {
    return new AutoPtr_GameLogEntity(MyoushuJNI.AutoPtr_GameLogEntity_assign__SWIG_1(swigCPtr, this, GameLogEntity.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_GameLogEntity assign(AutoPtr_GameLogEntity ptr) {
    return new AutoPtr_GameLogEntity(MyoushuJNI.AutoPtr_GameLogEntity_assign__SWIG_2(swigCPtr, this, AutoPtr_GameLogEntity.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_GameLogEntity ptr) {
    MyoushuJNI.AutoPtr_GameLogEntity_swap(swigCPtr, this, AutoPtr_GameLogEntity.getCPtr(ptr), ptr);
  }

  public GameLogEntity __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogEntity___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public GameLogEntity __ref__() {
    return new GameLogEntity(MyoushuJNI.AutoPtr_GameLogEntity___ref____SWIG_0(swigCPtr, this), false);
  }

  public GameLogEntity get() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogEntity_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_GameLogEntity_isNull(swigCPtr, this);
  }

  public GameLogEntity duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogEntity_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_GameLogEntity_getClassName(swigCPtr, this);
  }

  public VectorString getAttributeNames() {
    return new VectorString(MyoushuJNI.AutoPtr_GameLogEntity_getAttributeNames(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator begin() {
    return new SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_begin__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator end() {
    return new SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_end__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator attributeNamesBegin() {
    return new SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_attributeNamesBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator attributeNamesEnd() {
    return new SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_attributeNamesEnd(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_std__string_t__const_iterator keyAttributesBegin() {
    return new SWIGTYPE_p_std__listT_std__string_t__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_keyAttributesBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_std__string_t__const_iterator keyAttributesEnd() {
    return new SWIGTYPE_p_std__listT_std__string_t__const_iterator(MyoushuJNI.AutoPtr_GameLogEntity_keyAttributesEnd(swigCPtr, this), true);
  }

  public String getName() {
    return MyoushuJNI.AutoPtr_GameLogEntity_getName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_GameLogEntity_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_GameLogEntity_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public void release() {
    MyoushuJNI.AutoPtr_GameLogEntity_release(swigCPtr, this);
  }

  public int referenceCount() {
    return MyoushuJNI.AutoPtr_GameLogEntity_referenceCount(swigCPtr, this);
  }

}

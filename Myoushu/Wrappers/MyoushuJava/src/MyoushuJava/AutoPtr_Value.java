/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_Value {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_Value(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_Value obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_Value(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_Value() {
    this(MyoushuJNI.new_AutoPtr_Value__SWIG_0(), true);
  }

  public AutoPtr_Value(Value ptr) {
    this(MyoushuJNI.new_AutoPtr_Value__SWIG_1(Value.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Value(Value ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_Value__SWIG_2(Value.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_Value(AutoPtr_Value ptr) {
    this(MyoushuJNI.new_AutoPtr_Value__SWIG_3(AutoPtr_Value.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_Value assign(Value ptr) {
    return new AutoPtr_Value(MyoushuJNI.AutoPtr_Value_assign__SWIG_0(swigCPtr, this, Value.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_Value assign(Value ptr, boolean shared) {
    return new AutoPtr_Value(MyoushuJNI.AutoPtr_Value_assign__SWIG_1(swigCPtr, this, Value.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_Value assign(AutoPtr_Value ptr) {
    return new AutoPtr_Value(MyoushuJNI.AutoPtr_Value_assign__SWIG_2(swigCPtr, this, AutoPtr_Value.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_Value ptr) {
    MyoushuJNI.AutoPtr_Value_swap(swigCPtr, this, AutoPtr_Value.getCPtr(ptr), ptr);
  }

  public Value __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_Value___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Value(cPtr, false);
  }

  public Value __ref__() {
    return new Value(MyoushuJNI.AutoPtr_Value___ref____SWIG_0(swigCPtr, this), false);
  }

  public Value get() {
    long cPtr = MyoushuJNI.AutoPtr_Value_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Value(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_Value_isNull(swigCPtr, this);
  }

  public Value duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_Value_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new Value(cPtr, false);
  }

  public char getChar() {
    return MyoushuJNI.AutoPtr_Value_getChar(swigCPtr, this);
  }

  public short getUnsignedChar() {
    return MyoushuJNI.AutoPtr_Value_getUnsignedChar(swigCPtr, this);
  }

  public short getShort() {
    return MyoushuJNI.AutoPtr_Value_getShort(swigCPtr, this);
  }

  public int getUnsignedShort() {
    return MyoushuJNI.AutoPtr_Value_getUnsignedShort(swigCPtr, this);
  }

  public int getInt() {
    return MyoushuJNI.AutoPtr_Value_getInt(swigCPtr, this);
  }

  public long getUnsignedInt() {
    return MyoushuJNI.AutoPtr_Value_getUnsignedInt(swigCPtr, this);
  }

  public int getLong() {
    return MyoushuJNI.AutoPtr_Value_getLong(swigCPtr, this);
  }

  public long getUnsignedLong() {
    return MyoushuJNI.AutoPtr_Value_getUnsignedLong(swigCPtr, this);
  }

  public float getFloat() {
    return MyoushuJNI.AutoPtr_Value_getFloat(swigCPtr, this);
  }

  public double getDouble() {
    return MyoushuJNI.AutoPtr_Value_getDouble(swigCPtr, this);
  }

  public String getString() {
    return MyoushuJNI.AutoPtr_Value_getString(swigCPtr, this);
  }

  public NamedInstance getNamedInstance() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getNamedInstance(swigCPtr, this);
    return (cPtr == 0) ? null : new NamedInstance(cPtr, false);
  }

  public SWIGTYPE_p_void getVoidPtr() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getVoidPtr(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public NamedInstance getConstNamedInstance() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getConstNamedInstance(swigCPtr, this);
    return (cPtr == 0) ? null : new NamedInstance(cPtr, false);
  }

  public SWIGTYPE_p_void getConstVoidPtr() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getConstVoidPtr(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public Message getConstMessage() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getConstMessage(swigCPtr, this);
    return (cPtr == 0) ? null : new Message(cPtr, false);
  }

  public RefCountedObject getConstRefCountedObject() {
    long cPtr = MyoushuJNI.AutoPtr_Value_getConstRefCountedObject(swigCPtr, this);
    return (cPtr == 0) ? null : new RefCountedObject(cPtr, false);
  }

  public SWIGTYPE_p_jvalue getJValue(boolean convert) {
    return new SWIGTYPE_p_jvalue(MyoushuJNI.AutoPtr_Value_getJValue__SWIG_0(swigCPtr, this, convert), true);
  }

  public SWIGTYPE_p_jvalue getJValue() {
    return new SWIGTYPE_p_jvalue(MyoushuJNI.AutoPtr_Value_getJValue__SWIG_1(swigCPtr, this), true);
  }

  public Value.ValueType getType() {
    return Value.ValueType.swigToEnum(MyoushuJNI.AutoPtr_Value_getType(swigCPtr, this));
  }

  public boolean getAutoPtr() {
    return MyoushuJNI.AutoPtr_Value_getAutoPtr(swigCPtr, this);
  }

  public String toString() {
    return MyoushuJNI.AutoPtr_Value_toString(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Value_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_Value_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public void release() {
    MyoushuJNI.AutoPtr_Value_release(swigCPtr, this);
  }

  public int referenceCount() {
    return MyoushuJNI.AutoPtr_Value_referenceCount(swigCPtr, this);
  }

}

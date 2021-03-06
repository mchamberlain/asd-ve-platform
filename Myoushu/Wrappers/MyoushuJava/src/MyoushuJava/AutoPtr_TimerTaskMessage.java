/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_TimerTaskMessage {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_TimerTaskMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_TimerTaskMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_TimerTaskMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_TimerTaskMessage() {
    this(MyoushuJNI.new_AutoPtr_TimerTaskMessage__SWIG_0(), true);
  }

  public AutoPtr_TimerTaskMessage(TimerTaskMessage ptr) {
    this(MyoushuJNI.new_AutoPtr_TimerTaskMessage__SWIG_1(TimerTaskMessage.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_TimerTaskMessage(TimerTaskMessage ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_TimerTaskMessage__SWIG_2(TimerTaskMessage.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_TimerTaskMessage(AutoPtr_TimerTaskMessage ptr) {
    this(MyoushuJNI.new_AutoPtr_TimerTaskMessage__SWIG_3(AutoPtr_TimerTaskMessage.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_TimerTaskMessage assign(TimerTaskMessage ptr) {
    return new AutoPtr_TimerTaskMessage(MyoushuJNI.AutoPtr_TimerTaskMessage_assign__SWIG_0(swigCPtr, this, TimerTaskMessage.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_TimerTaskMessage assign(TimerTaskMessage ptr, boolean shared) {
    return new AutoPtr_TimerTaskMessage(MyoushuJNI.AutoPtr_TimerTaskMessage_assign__SWIG_1(swigCPtr, this, TimerTaskMessage.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_TimerTaskMessage assign(AutoPtr_TimerTaskMessage ptr) {
    return new AutoPtr_TimerTaskMessage(MyoushuJNI.AutoPtr_TimerTaskMessage_assign__SWIG_2(swigCPtr, this, AutoPtr_TimerTaskMessage.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_TimerTaskMessage ptr) {
    MyoushuJNI.AutoPtr_TimerTaskMessage_swap(swigCPtr, this, AutoPtr_TimerTaskMessage.getCPtr(ptr), ptr);
  }

  public TimerTaskMessage __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_TimerTaskMessage___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new TimerTaskMessage(cPtr, false);
  }

  public TimerTaskMessage __ref__() {
    return new TimerTaskMessage(MyoushuJNI.AutoPtr_TimerTaskMessage___ref____SWIG_0(swigCPtr, this), false);
  }

  public TimerTaskMessage get() {
    long cPtr = MyoushuJNI.AutoPtr_TimerTaskMessage_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new TimerTaskMessage(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_TimerTaskMessage_isNull(swigCPtr, this);
  }

  public TimerTaskMessage duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_TimerTaskMessage_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new TimerTaskMessage(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_TimerTaskMessage_getClassName(swigCPtr, this);
  }

  public TimerTaskMessage.TimerTaskMessageType getMessageType() {
    return TimerTaskMessage.TimerTaskMessageType.swigToEnum(MyoushuJNI.AutoPtr_TimerTaskMessage_getMessageType(swigCPtr, this));
  }

  public long getAbsTime() {
    return MyoushuJNI.AutoPtr_TimerTaskMessage_getAbsTime(swigCPtr, this);
  }

  public long getDelta() {
    return MyoushuJNI.AutoPtr_TimerTaskMessage_getDelta(swigCPtr, this);
  }

  public void clone(TimerTaskMessage dest) {
    MyoushuJNI.AutoPtr_TimerTaskMessage_clone(swigCPtr, this, TimerTaskMessage.getCPtr(dest), dest);
  }

  public SWIGTYPE_p_Poco__Net__IPAddress getCreator() {
    return new SWIGTYPE_p_Poco__Net__IPAddress(MyoushuJNI.AutoPtr_TimerTaskMessage_getCreator(swigCPtr, this), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_TimerTaskMessage_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_TimerTaskMessage_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}

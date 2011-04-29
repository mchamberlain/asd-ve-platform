/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class AutoPtr_GameLogMessage {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public AutoPtr_GameLogMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(AutoPtr_GameLogMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_AutoPtr_GameLogMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public AutoPtr_GameLogMessage() {
    this(MyoushuJNI.new_AutoPtr_GameLogMessage__SWIG_0(), true);
  }

  public AutoPtr_GameLogMessage(GameLogMessage ptr) {
    this(MyoushuJNI.new_AutoPtr_GameLogMessage__SWIG_1(GameLogMessage.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_GameLogMessage(GameLogMessage ptr, boolean shared) {
    this(MyoushuJNI.new_AutoPtr_GameLogMessage__SWIG_2(GameLogMessage.getCPtr(ptr), ptr, shared), true);
  }

  public AutoPtr_GameLogMessage(AutoPtr_GameLogMessage ptr) {
    this(MyoushuJNI.new_AutoPtr_GameLogMessage__SWIG_3(AutoPtr_GameLogMessage.getCPtr(ptr), ptr), true);
  }

  public AutoPtr_GameLogMessage assign(GameLogMessage ptr) {
    return new AutoPtr_GameLogMessage(MyoushuJNI.AutoPtr_GameLogMessage_assign__SWIG_0(swigCPtr, this, GameLogMessage.getCPtr(ptr), ptr), false);
  }

  public AutoPtr_GameLogMessage assign(GameLogMessage ptr, boolean shared) {
    return new AutoPtr_GameLogMessage(MyoushuJNI.AutoPtr_GameLogMessage_assign__SWIG_1(swigCPtr, this, GameLogMessage.getCPtr(ptr), ptr, shared), false);
  }

  public AutoPtr_GameLogMessage assign(AutoPtr_GameLogMessage ptr) {
    return new AutoPtr_GameLogMessage(MyoushuJNI.AutoPtr_GameLogMessage_assign__SWIG_2(swigCPtr, this, AutoPtr_GameLogMessage.getCPtr(ptr), ptr), false);
  }

  public void swap(AutoPtr_GameLogMessage ptr) {
    MyoushuJNI.AutoPtr_GameLogMessage_swap(swigCPtr, this, AutoPtr_GameLogMessage.getCPtr(ptr), ptr);
  }

  public GameLogMessage __deref__() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogMessage___deref____SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogMessage(cPtr, false);
  }

  public GameLogMessage __ref__() {
    return new GameLogMessage(MyoushuJNI.AutoPtr_GameLogMessage___ref____SWIG_0(swigCPtr, this), false);
  }

  public GameLogMessage get() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogMessage_get__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogMessage(cPtr, false);
  }

  public boolean isNull() {
    return MyoushuJNI.AutoPtr_GameLogMessage_isNull(swigCPtr, this);
  }

  public GameLogMessage duplicate() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogMessage_duplicate(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogMessage(cPtr, false);
  }

  public String getClassName() {
    return MyoushuJNI.AutoPtr_GameLogMessage_getClassName(swigCPtr, this);
  }

  public GameLogMessage.GameLogMessageType getMessageType() {
    return GameLogMessage.GameLogMessageType.swigToEnum(MyoushuJNI.AutoPtr_GameLogMessage_getMessageType(swigCPtr, this));
  }

  public GameLogEntity getGameLogEntity() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogMessage_getGameLogEntity(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public GameLogEntityEntry getGameLogEntityEntry() {
    long cPtr = MyoushuJNI.AutoPtr_GameLogMessage_getGameLogEntityEntry(swigCPtr, this);
    return (cPtr == 0) ? null : new GameLogEntityEntry(cPtr, false);
  }

  public String getEntityName() {
    return MyoushuJNI.AutoPtr_GameLogMessage_getEntityName(swigCPtr, this);
  }

  public ListString getEntryPrimaryKey() {
    return new ListString(MyoushuJNI.AutoPtr_GameLogMessage_getEntryPrimaryKey(swigCPtr, this), true);
  }

  public SWIGTYPE_p_uint32_t getActionID() {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_GameLogMessage_getActionID(swigCPtr, this), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_GameLogMessage_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.AutoPtr_GameLogMessage_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_Poco__Net__IPAddress getCreator() {
    return new SWIGTYPE_p_Poco__Net__IPAddress(MyoushuJNI.AutoPtr_GameLogMessage_getCreator(swigCPtr, this), true);
  }

}
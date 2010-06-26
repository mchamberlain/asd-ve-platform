/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ReplayMessage extends Message {
  private long swigCPtr;

  public ReplayMessage(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGReplayMessageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ReplayMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ReplayMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ReplayMessage() {
    this(MyoushuJNI.new_ReplayMessage__SWIG_0(), true);
  }

  public ReplayMessage(ReplayMessage.ReplayMessageType messageType, String replayName) {
    this(MyoushuJNI.new_ReplayMessage__SWIG_1(messageType.swigValue(), replayName), true);
  }

  public String getClassName() {
    return MyoushuJNI.ReplayMessage_getClassName(swigCPtr, this);
  }

  public ReplayMessage.ReplayMessageType getMessageType() {
    return ReplayMessage.ReplayMessageType.swigToEnum(MyoushuJNI.ReplayMessage_getMessageType(swigCPtr, this));
  }

  public void setMessageType(ReplayMessage.ReplayMessageType type) {
    MyoushuJNI.ReplayMessage_setMessageType(swigCPtr, this, type.swigValue());
  }

  public String getReplayName() {
    return MyoushuJNI.ReplayMessage_getReplayName(swigCPtr, this);
  }

  public void setReplayName(String replayName) {
    MyoushuJNI.ReplayMessage_setReplayName(swigCPtr, this, replayName);
  }

  public Replay getReplay() {
    long cPtr = MyoushuJNI.ReplayMessage_getReplay(swigCPtr, this);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public void setReplay(Replay pReplay) {
    MyoushuJNI.ReplayMessage_setReplay(swigCPtr, this, Replay.getCPtr(pReplay), pReplay);
  }

  public void clear() {
    MyoushuJNI.ReplayMessage_clear(swigCPtr, this);
  }

  public enum ReplayMessageType {
    RM_UNKNOWN(MyoushuJNI.ReplayMessage_RM_UNKNOWN_get()),
    RM_START_RECORDING,
    RM_START_PLAYBACK,
    RM_STOP,
    RM_PAUSE,
    RM_RESUME;

    public final int swigValue() {
      return swigValue;
    }

    public static ReplayMessageType swigToEnum(int swigValue) {
      ReplayMessageType[] swigValues = ReplayMessageType.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (ReplayMessageType swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + ReplayMessageType.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private ReplayMessageType() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private ReplayMessageType(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private ReplayMessageType(ReplayMessageType swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

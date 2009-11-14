/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class InputDeviceMessage extends NamedObject_InputDeviceMessage {
  private long swigCPtr;

  public InputDeviceMessage(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGInputDeviceMessageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(InputDeviceMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_InputDeviceMessage(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static long getDS_BUTTON_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_BUTTON_INDEX_get();
  }

  public static long getDS_BUTTONS_STATE_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_BUTTONS_STATE_INDEX_get();
  }

  public static long getDS_X_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_X_INDEX_get();
  }

  public static long getDS_Y_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_Y_INDEX_get();
  }

  public static long getDS_Z_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_Z_INDEX_get();
  }

  public static long getDS_X_REL_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_X_REL_INDEX_get();
  }

  public static long getDS_Y_REL_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_Y_REL_INDEX_get();
  }

  public static long getDS_Z_REL_INDEX() {
    return MyoushuJNI.InputDeviceMessage_DS_Z_REL_INDEX_get();
  }

  public InputDeviceMessage(InputDevice inputDevice) {
    this(MyoushuJNI.new_InputDeviceMessage__SWIG_0(InputDevice.getCPtr(inputDevice), inputDevice), true);
  }

  public InputDeviceMessage() {
    this(MyoushuJNI.new_InputDeviceMessage__SWIG_1(), true);
  }

  public InputDeviceMessage(InputDevice inputDevice, InputDeviceMessage.DeviceAction deviceAction, InputDevice.InputDeviceType deviceType, SWIGTYPE_p_int deviceState, Vector3 actionVector, SWIGTYPE_p_std__string inputIdentifiers) {
    this(MyoushuJNI.new_InputDeviceMessage__SWIG_2(InputDevice.getCPtr(inputDevice), inputDevice, deviceAction.swigValue(), deviceType.swigValue(), SWIGTYPE_p_int.getCPtr(deviceState), Vector3.getCPtr(actionVector), actionVector, SWIGTYPE_p_std__string.getCPtr(inputIdentifiers)), true);
  }

  public String getClassName() {
    return MyoushuJNI.InputDeviceMessage_getClassName(swigCPtr, this);
  }

  public InputDevice getInputDevice() {
    long cPtr = MyoushuJNI.InputDeviceMessage_getInputDevice(swigCPtr, this);
    return (cPtr == 0) ? null : new InputDevice(cPtr, false);
  }

  public void setInputDevice(InputDevice inputDevice) {
    MyoushuJNI.InputDeviceMessage_setInputDevice(swigCPtr, this, InputDevice.getCPtr(inputDevice), inputDevice);
  }

  public InputDevice.InputDeviceType getDeviceType() {
    return InputDevice.InputDeviceType.swigToEnum(MyoushuJNI.InputDeviceMessage_getDeviceType(swigCPtr, this));
  }

  public InputDeviceMessage.DeviceAction getDeviceAction() {
    return InputDeviceMessage.DeviceAction.swigToEnum(MyoushuJNI.InputDeviceMessage_getDeviceAction(swigCPtr, this));
  }

  public float getActionVector(long index) {
    return MyoushuJNI.InputDeviceMessage_getActionVector__SWIG_0(swigCPtr, this, index);
  }

  public void getActionVector(Vector3 destVector) {
    MyoushuJNI.InputDeviceMessage_getActionVector__SWIG_1(swigCPtr, this, Vector3.getCPtr(destVector), destVector);
  }

  public int getDeviceState(long index) {
    return MyoushuJNI.InputDeviceMessage_getDeviceState(swigCPtr, this, index);
  }

  public void setDeviceType(InputDevice.InputDeviceType deviceType) {
    MyoushuJNI.InputDeviceMessage_setDeviceType(swigCPtr, this, deviceType.swigValue());
  }

  public void setDeviceAction(InputDeviceMessage.DeviceAction deviceAction) {
    MyoushuJNI.InputDeviceMessage_setDeviceAction(swigCPtr, this, deviceAction.swigValue());
  }

  public void setDeviceState(long index, int value) {
    MyoushuJNI.InputDeviceMessage_setDeviceState(swigCPtr, this, index, value);
  }

  public void setActionVector(long index, float value) {
    MyoushuJNI.InputDeviceMessage_setActionVector__SWIG_0(swigCPtr, this, index, value);
  }

  public void setActionVector(Vector3 otherVector) {
    MyoushuJNI.InputDeviceMessage_setActionVector__SWIG_1(swigCPtr, this, Vector3.getCPtr(otherVector), otherVector);
  }

  public String getInputIdentifier(long index) {
    return MyoushuJNI.InputDeviceMessage_getInputIdentifier(swigCPtr, this, index);
  }

  public void setInputIdentifier(long index, String inputIdentifier) {
    MyoushuJNI.InputDeviceMessage_setInputIdentifier(swigCPtr, this, index, inputIdentifier);
  }

  public void clear() {
    MyoushuJNI.InputDeviceMessage_clear(swigCPtr, this);
  }

  public void clone(InputDeviceMessage dest) {
    MyoushuJNI.InputDeviceMessage_clone(swigCPtr, this, InputDeviceMessage.getCPtr(dest), dest);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.InputDeviceMessage_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.InputDeviceMessage_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.InputDeviceMessage_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.InputDeviceMessage_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public enum DeviceAction {
    DA_PRESS,
    DA_RELEASE,
    DA_MOVE;

    public final int swigValue() {
      return swigValue;
    }

    public static DeviceAction swigToEnum(int swigValue) {
      DeviceAction[] swigValues = DeviceAction.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (DeviceAction swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + DeviceAction.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private DeviceAction() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private DeviceAction(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private DeviceAction(DeviceAction swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

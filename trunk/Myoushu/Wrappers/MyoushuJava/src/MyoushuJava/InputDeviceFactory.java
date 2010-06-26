/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class InputDeviceFactory extends Singleton_InputDeviceFactory {
  private long swigCPtr;

  public InputDeviceFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGInputDeviceFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(InputDeviceFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_InputDeviceFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public InputDeviceFactory() {
    this(MyoushuJNI.new_InputDeviceFactory(), true);
  }

  public AutoPtr_KeyboardOISInputDevice make(SWIGTYPE_p_OIS__Keyboard oisKeyboard, String name) {
    return new AutoPtr_KeyboardOISInputDevice(MyoushuJNI.InputDeviceFactory_make__SWIG_0(swigCPtr, this, SWIGTYPE_p_OIS__Keyboard.getCPtr(oisKeyboard), name), true);
  }

  public AutoPtr_MouseOISInputDevice make(SWIGTYPE_p_OIS__Mouse oisMouse, String name) {
    return new AutoPtr_MouseOISInputDevice(MyoushuJNI.InputDeviceFactory_make__SWIG_1(swigCPtr, this, SWIGTYPE_p_OIS__Mouse.getCPtr(oisMouse), name), true);
  }

  public AutoPtr_InputDevice getInputDevice(String name) {
    return new AutoPtr_InputDevice(MyoushuJNI.InputDeviceFactory_getInputDevice(swigCPtr, this, name), true);
  }

  public SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__iterator getDevicesIteratorBegin() {
    return new SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__iterator(MyoushuJNI.InputDeviceFactory_getDevicesIteratorBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__iterator getDevicesIteratorEnd() {
    return new SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__iterator(MyoushuJNI.InputDeviceFactory_getDevicesIteratorEnd(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__const_iterator getDevicesConstIteratorBegin() {
    return new SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__const_iterator(MyoushuJNI.InputDeviceFactory_getDevicesConstIteratorBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__const_iterator getDevicesConstIteratorEnd() {
    return new SWIGTYPE_p_std__listT_Poco__AutoPtrT_Myoushu__InputDevice_t_t__const_iterator(MyoushuJNI.InputDeviceFactory_getDevicesConstIteratorEnd(swigCPtr, this), true);
  }

}

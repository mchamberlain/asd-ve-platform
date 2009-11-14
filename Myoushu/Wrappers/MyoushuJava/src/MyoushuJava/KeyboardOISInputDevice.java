/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class KeyboardOISInputDevice extends OISInputDevice_OIS_Keyboard {
  private long swigCPtr;

  public KeyboardOISInputDevice(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGKeyboardOISInputDeviceUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(KeyboardOISInputDevice obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_KeyboardOISInputDevice(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static String getINPUT_DEVICE_NAME() {
    return MyoushuJNI.KeyboardOISInputDevice_INPUT_DEVICE_NAME_get();
  }

  public KeyboardOISInputDevice(String name, SWIGTYPE_p_OIS__Keyboard oisKeyboard) {
    this(MyoushuJNI.new_KeyboardOISInputDevice(name, SWIGTYPE_p_OIS__Keyboard.getCPtr(oisKeyboard)), true);
  }

  public String getInputEventString(String inputIdentifier) {
    return MyoushuJNI.KeyboardOISInputDevice_getInputEventString(swigCPtr, this, inputIdentifier);
  }

  public int getInputCodeFromInputIdentifier(String inputIdentifier) {
    return MyoushuJNI.KeyboardOISInputDevice_getInputCodeFromInputIdentifier(swigCPtr, this, inputIdentifier);
  }

  public String getInputIdentifierFromInputCode(int inputCode) {
    return MyoushuJNI.KeyboardOISInputDevice_getInputIdentifierFromInputCode(swigCPtr, this, inputCode);
  }

  public void capture() {
    MyoushuJNI.KeyboardOISInputDevice_capture(swigCPtr, this);
  }

  public boolean keyPressed(SWIGTYPE_p_OIS__KeyEvent arg) {
    return MyoushuJNI.KeyboardOISInputDevice_keyPressed(swigCPtr, this, SWIGTYPE_p_OIS__KeyEvent.getCPtr(arg));
  }

  public boolean keyReleased(SWIGTYPE_p_OIS__KeyEvent arg) {
    return MyoushuJNI.KeyboardOISInputDevice_keyReleased(swigCPtr, this, SWIGTYPE_p_OIS__KeyEvent.getCPtr(arg));
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Config extends MapConfiguration {
  private long swigCPtr;

  public Config(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGConfigUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Config obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Config(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Config() {
    this(MyoushuJNI.new_Config(), true);
  }

  public void loadConfig(String filename) {
    MyoushuJNI.Config_loadConfig(swigCPtr, this, filename);
  }

  public void bindInputAction(InputDevice inputDevice, String inputIdentifier, String inputAction) {
    MyoushuJNI.Config_bindInputAction(swigCPtr, this, InputDevice.getCPtr(inputDevice), inputDevice, inputIdentifier, inputAction);
  }

  public void unbindInputAction(InputDevice inputDevice, String inputIdentifier, String inputAction) {
    MyoushuJNI.Config_unbindInputAction(swigCPtr, this, InputDevice.getCPtr(inputDevice), inputDevice, inputIdentifier, inputAction);
  }

  public static String getVID_WIDTH() {
    return MyoushuJNI.Config_VID_WIDTH_get();
  }

  public static String getVID_HEIGHT() {
    return MyoushuJNI.Config_VID_HEIGHT_get();
  }

  public static String getVID_BITS() {
    return MyoushuJNI.Config_VID_BITS_get();
  }

  public static String getVID_FULLSCREEN() {
    return MyoushuJNI.Config_VID_FULLSCREEN_get();
  }

  public static String getVID_VSYNC() {
    return MyoushuJNI.Config_VID_VSYNC_get();
  }

  public static String getVID_ANTIALIASING() {
    return MyoushuJNI.Config_VID_ANTIALIASING_get();
  }

  public static String getVID_ANISOTROPIC_FILTERING() {
    return MyoushuJNI.Config_VID_ANISOTROPIC_FILTERING_get();
  }

  public static String getINPUT_PREFIX() {
    return MyoushuJNI.Config_INPUT_PREFIX_get();
  }

  public static String getINPUT_MOUSE_SENSITIVITY() {
    return MyoushuJNI.Config_INPUT_MOUSE_SENSITIVITY_get();
  }

}

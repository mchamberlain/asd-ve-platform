/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class OISInputDevice_OIS_Mouse {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public OISInputDevice_OIS_Mouse(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(OISInputDevice_OIS_Mouse obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_OISInputDevice_OIS_Mouse(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public OISInputDevice_OIS_Mouse(SWIGTYPE_p_OIS__Mouse oisDevice) {
    this(MyoushuJNI.new_OISInputDevice_OIS_Mouse(SWIGTYPE_p_OIS__Mouse.getCPtr(oisDevice)), true);
  }

  public void capture() {
    MyoushuJNI.OISInputDevice_OIS_Mouse_capture(swigCPtr, this);
  }

  public SWIGTYPE_p_OIS__Mouse getOISDevice() {
    long cPtr = MyoushuJNI.OISInputDevice_OIS_Mouse_getOISDevice(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_OIS__Mouse(cPtr, false);
  }

}

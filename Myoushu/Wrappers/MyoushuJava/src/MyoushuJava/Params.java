/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Params {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Params(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Params obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Params(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void process(String arg0) {
    MyoushuJNI.Params_process(swigCPtr, this, arg0);
  }

  public SWIGTYPE_p_std__vectorT_std__pairT_std__string_std__string_t_t fromString(String arg0) {
    return new SWIGTYPE_p_std__vectorT_std__pairT_std__string_std__string_t_t(MyoushuJNI.Params_fromString(swigCPtr, this, arg0), true);
  }

  public void setToDefault() {
    MyoushuJNI.Params_setToDefault(swigCPtr, this);
  }

  public Params() {
    this(MyoushuJNI.new_Params(), true);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class OutputStream {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public OutputStream(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(OutputStream obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_OutputStream(swigCPtr);
    }
    swigCPtr = 0;
  }

  public OutputStream(SWIGTYPE_p_std__ostream out) {
    this(MyoushuJNI.new_OutputStream(SWIGTYPE_p_std__ostream.getCPtr(out)), true);
  }

}
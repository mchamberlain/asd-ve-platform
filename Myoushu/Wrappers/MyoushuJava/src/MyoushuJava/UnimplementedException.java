/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class UnimplementedException extends OgreException {
  private long swigCPtr;

  public UnimplementedException(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGUnimplementedExceptionUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(UnimplementedException obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_UnimplementedException(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public UnimplementedException(int number, String description, String source, String file, int line) {
    this(MyoushuJNI.new_UnimplementedException(number, description, source, file, line), true);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Prism extends Shape {
  private long swigCPtr;

  public Prism(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGPrismUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Prism obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Prism(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Prism(PrismShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t arg2) {
    this(MyoushuJNI.new_Prism(PrismShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t.getCPtr(arg2)), true);
  }

}

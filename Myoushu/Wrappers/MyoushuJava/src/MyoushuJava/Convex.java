/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Convex extends Shape {
  private long swigCPtr;

  public Convex(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGConvexUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Convex obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Convex(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Convex(ConvexShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t arg2) {
    this(MyoushuJNI.new_Convex(ConvexShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t.getCPtr(arg2)), true);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Capsule extends Shape {
  private long swigCPtr;

  public Capsule(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCapsuleUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Capsule obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Capsule(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public Capsule(CapsuleShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t arg2) {
    this(MyoushuJNI.new_Capsule__SWIG_0(CapsuleShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t.getCPtr(arg2)), true);
  }

  public Capsule(CapsuleShape arg0, NxOgre_Actor arg1) {
    this(MyoushuJNI.new_Capsule__SWIG_1(CapsuleShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1), true);
  }

}

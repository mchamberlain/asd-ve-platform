/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Cube extends Shape {
  private long swigCPtr;

  public Cube(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCubeUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Cube obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Cube(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Cube(CubeShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t arg2, SWIGTYPE_p_NxOgre__Skeleton s) {
    this(MyoushuJNI.new_Cube__SWIG_0(CubeShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t.getCPtr(arg2), SWIGTYPE_p_NxOgre__Skeleton.getCPtr(s)), true);
  }

  public Cube(CubeShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t arg2) {
    this(MyoushuJNI.new_Cube__SWIG_1(CubeShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxArrayT_NxShapeDesc_p_t.getCPtr(arg2)), true);
  }

  public Cube(CubeShape arg0, NxOgre_Actor arg1, SWIGTYPE_p_NxOgre__Skeleton s) {
    this(MyoushuJNI.new_Cube__SWIG_2(CubeShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, SWIGTYPE_p_NxOgre__Skeleton.getCPtr(s)), true);
  }

  public Cube(CubeShape arg0, NxOgre_Actor arg1) {
    this(MyoushuJNI.new_Cube__SWIG_3(CubeShape.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1), true);
  }

  public void copyTo(NxOgre_Actor arg0) {
    MyoushuJNI.Cube_copyTo(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0);
  }

  public void moveTo(NxOgre_Actor arg0) {
    MyoushuJNI.Cube_moveTo(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0);
  }

  public SWIGTYPE_p_NxShape getNxShape() {
    long cPtr = MyoushuJNI.Cube_getNxShape(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxShape(cPtr, false);
  }

  public void releaseShape() {
    MyoushuJNI.Cube_releaseShape(swigCPtr, this);
  }

}

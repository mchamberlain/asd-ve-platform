/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class CubeShape extends ShapeBlueprint {
  private long swigCPtr;

  public CubeShape(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCubeShapeUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(CubeShape obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_CubeShape(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public CubeShape(float width, float height, float length, ShapeParams arg3) {
    this(MyoushuJNI.new_CubeShape__SWIG_0(width, height, length, ShapeParams.getCPtr(arg3), arg3), true);
  }

  public CubeShape(float width, float height, float length) {
    this(MyoushuJNI.new_CubeShape__SWIG_1(width, height, length), true);
  }

  public CubeShape(float cubed, ShapeParams arg1) {
    this(MyoushuJNI.new_CubeShape__SWIG_2(cubed, ShapeParams.getCPtr(arg1), arg1), true);
  }

  public CubeShape(float cubed) {
    this(MyoushuJNI.new_CubeShape__SWIG_3(cubed), true);
  }

}

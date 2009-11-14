/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class SphereShape extends ShapeBlueprint {
  private long swigCPtr;

  public SphereShape(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGSphereShapeUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SphereShape obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_SphereShape(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public SphereShape(float radius, ShapeParams arg1) {
    this(MyoushuJNI.new_SphereShape__SWIG_0(radius, ShapeParams.getCPtr(arg1), arg1), true);
  }

  public SphereShape(float radius) {
    this(MyoushuJNI.new_SphereShape__SWIG_1(radius), true);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class PrismShape extends ShapeBlueprint {
  private long swigCPtr;

  public PrismShape(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGPrismShapeUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(PrismShape obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_PrismShape(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public PrismShape(float radius, float height, long nbSides, ShapeParams arg3) {
    this(MyoushuJNI.new_PrismShape__SWIG_0(radius, height, nbSides, ShapeParams.getCPtr(arg3), arg3), true);
  }

  public PrismShape(float radius, float height, long nbSides) {
    this(MyoushuJNI.new_PrismShape__SWIG_1(radius, height, nbSides), true);
  }

}

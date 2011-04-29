/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ShapeBlueprint {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ShapeBlueprint(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ShapeBlueprint obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ShapeBlueprint(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ShapeBlueprint() {
    this(MyoushuJNI.new_ShapeBlueprint__SWIG_0(), true);
  }

  public ShapeBlueprint(ShapeParams arg0) {
    this(MyoushuJNI.new_ShapeBlueprint__SWIG_1(ShapeParams.getCPtr(arg0), arg0), true);
  }

  public static ShapeBlueprint getDefaultShape() {
    long cPtr = MyoushuJNI.ShapeBlueprint_getDefaultShape();
    return (cPtr == 0) ? null : new ShapeBlueprint(cPtr, false);
  }

  public boolean isShared() {
    return MyoushuJNI.ShapeBlueprint_isShared(swigCPtr, this);
  }

  public void setShared(boolean s) {
    MyoushuJNI.ShapeBlueprint_setShared(swigCPtr, this, s);
  }

  public void setMParams(ShapeParams value) {
    MyoushuJNI.ShapeBlueprint_mParams_set(swigCPtr, this, ShapeParams.getCPtr(value), value);
  }

  public ShapeParams getMParams() {
    long cPtr = MyoushuJNI.ShapeBlueprint_mParams_get(swigCPtr, this);
    return (cPtr == 0) ? null : new ShapeParams(cPtr, false);
  }

}
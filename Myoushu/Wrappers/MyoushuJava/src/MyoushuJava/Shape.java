/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Shape {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Shape(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Shape obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Shape(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Shape(NxOgre_Actor arg0) {
    this(MyoushuJNI.new_Shape(NxOgre_Actor.getCPtr(arg0), arg0), true);
  }

  public void simulate(float arg0) {
    MyoushuJNI.Shape_simulate(swigCPtr, this, arg0);
  }

  public void render(float arg0) {
    MyoushuJNI.Shape_render(swigCPtr, this, arg0);
  }

  public ShapeBlueprint getBlueprint() {
    long cPtr = MyoushuJNI.Shape_getBlueprint(swigCPtr, this);
    return (cPtr == 0) ? null : new ShapeBlueprint(cPtr, false);
  }

  public void copyTo(NxOgre_Actor arg0) {
    MyoushuJNI.Shape_copyTo__SWIG_0(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0);
  }

  public void copyTo(NxOgre_Actor arg0, Vector3 positionOverride) {
    MyoushuJNI.Shape_copyTo__SWIG_1(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(positionOverride), positionOverride);
  }

  public void moveTo(NxOgre_Actor arg0) {
    MyoushuJNI.Shape_moveTo__SWIG_0(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0);
  }

  public void moveTo(NxOgre_Actor arg0, Vector3 positionOverride) {
    MyoushuJNI.Shape_moveTo__SWIG_1(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(positionOverride), positionOverride);
  }

  public SWIGTYPE_p_NxShape getNxShape() {
    long cPtr = MyoushuJNI.Shape_getNxShape(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxShape(cPtr, false);
  }

  public void releaseShape() {
    MyoushuJNI.Shape_releaseShape(swigCPtr, this);
  }

  public SWIGTYPE_p_NxOgre__Skeleton getSkeleton() {
    long cPtr = MyoushuJNI.Shape_getSkeleton(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__Skeleton(cPtr, false);
  }

  public long getIndex() {
    return MyoushuJNI.Shape_getIndex(swigCPtr, this);
  }

  public void setIndex(long index) {
    MyoushuJNI.Shape_setIndex(swigCPtr, this, index);
  }

}
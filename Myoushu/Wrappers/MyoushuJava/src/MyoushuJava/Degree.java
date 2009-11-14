/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Degree {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Degree(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Degree obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Degree(swigCPtr);
    }
    swigCPtr = 0;
  }

  public Degree(float d) {
    this(MyoushuJNI.new_Degree__SWIG_0(d), true);
  }

  public Degree() {
    this(MyoushuJNI.new_Degree__SWIG_1(), true);
  }

  public Degree(Radian r) {
    this(MyoushuJNI.new_Degree__SWIG_2(Radian.getCPtr(r), r), true);
  }

  public float valueDegrees() {
    return MyoushuJNI.Degree_valueDegrees(swigCPtr, this);
  }

  public float valueRadians() {
    return MyoushuJNI.Degree_valueRadians(swigCPtr, this);
  }

  public float valueAngleUnits() {
    return MyoushuJNI.Degree_valueAngleUnits(swigCPtr, this);
  }

}

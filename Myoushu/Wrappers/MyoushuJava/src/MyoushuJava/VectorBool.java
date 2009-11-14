/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class VectorBool {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public VectorBool(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(VectorBool obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_VectorBool(swigCPtr);
    }
    swigCPtr = 0;
  }

  public VectorBool() {
    this(MyoushuJNI.new_VectorBool__SWIG_0(), true);
  }

  public VectorBool(long n) {
    this(MyoushuJNI.new_VectorBool__SWIG_1(n), true);
  }

  public long size() {
    return MyoushuJNI.VectorBool_size(swigCPtr, this);
  }

  public long capacity() {
    return MyoushuJNI.VectorBool_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MyoushuJNI.VectorBool_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return MyoushuJNI.VectorBool_isEmpty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.VectorBool_clear(swigCPtr, this);
  }

  public void add(boolean x) {
    MyoushuJNI.VectorBool_add(swigCPtr, this, x);
  }

  public boolean get(int i) {
    return MyoushuJNI.VectorBool_get(swigCPtr, this, i);
  }

  public void set(int i, boolean val) {
    MyoushuJNI.VectorBool_set(swigCPtr, this, i, val);
  }

}
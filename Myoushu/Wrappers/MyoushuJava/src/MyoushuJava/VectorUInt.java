/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class VectorUInt {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public VectorUInt(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(VectorUInt obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_VectorUInt(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public VectorUInt() {
    this(MyoushuJNI.new_VectorUInt__SWIG_0(), true);
  }

  public VectorUInt(long n) {
    this(MyoushuJNI.new_VectorUInt__SWIG_1(n), true);
  }

  public long size() {
    return MyoushuJNI.VectorUInt_size(swigCPtr, this);
  }

  public long capacity() {
    return MyoushuJNI.VectorUInt_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    MyoushuJNI.VectorUInt_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return MyoushuJNI.VectorUInt_isEmpty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.VectorUInt_clear(swigCPtr, this);
  }

  public void add(long x) {
    MyoushuJNI.VectorUInt_add(swigCPtr, this, x);
  }

  public long get(int i) {
    return MyoushuJNI.VectorUInt_get(swigCPtr, this, i);
  }

  public void set(int i, long val) {
    MyoushuJNI.VectorUInt_set(swigCPtr, this, i, val);
  }

}

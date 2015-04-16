/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ASTTJava;

public class VectorChar {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public VectorChar(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(VectorChar obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        ASTTJNI.delete_VectorChar(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public VectorChar() {
    this(ASTTJNI.new_VectorChar__SWIG_0(), true);
  }

  public VectorChar(long n) {
    this(ASTTJNI.new_VectorChar__SWIG_1(n), true);
  }

  public long size() {
    return ASTTJNI.VectorChar_size(swigCPtr, this);
  }

  public long capacity() {
    return ASTTJNI.VectorChar_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    ASTTJNI.VectorChar_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return ASTTJNI.VectorChar_isEmpty(swigCPtr, this);
  }

  public void clear() {
    ASTTJNI.VectorChar_clear(swigCPtr, this);
  }

  public void add(char x) {
    ASTTJNI.VectorChar_add(swigCPtr, this, x);
  }

  public char get(int i) {
    return ASTTJNI.VectorChar_get(swigCPtr, this, i);
  }

  public void set(int i, char val) {
    ASTTJNI.VectorChar_set(swigCPtr, this, i, val);
  }

}
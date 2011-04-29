/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListFloat {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListFloat(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListFloat obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ListFloat(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ListFloat() {
    this(MyoushuJNI.new_ListFloat__SWIG_0(), true);
  }

  public ListFloat(ListFloat arg0) {
    this(MyoushuJNI.new_ListFloat__SWIG_1(ListFloat.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListFloat_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListFloat_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListFloat_clear(swigCPtr, this);
  }

  public void push_back(float val) {
    MyoushuJNI.ListFloat_push_back(swigCPtr, this, val);
  }

  public void pop_back() {
    MyoushuJNI.ListFloat_pop_back(swigCPtr, this);
  }

  public float front() {
    return MyoushuJNI.ListFloat_front(swigCPtr, this);
  }

  public float back() {
    return MyoushuJNI.ListFloat_back(swigCPtr, this);
  }

}
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListDouble {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListDouble(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListDouble obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ListDouble(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ListDouble() {
    this(MyoushuJNI.new_ListDouble__SWIG_0(), true);
  }

  public ListDouble(ListDouble arg0) {
    this(MyoushuJNI.new_ListDouble__SWIG_1(ListDouble.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListDouble_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListDouble_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListDouble_clear(swigCPtr, this);
  }

  public void push_back(double val) {
    MyoushuJNI.ListDouble_push_back(swigCPtr, this, val);
  }

  public void pop_back() {
    MyoushuJNI.ListDouble_pop_back(swigCPtr, this);
  }

  public double front() {
    return MyoushuJNI.ListDouble_front(swigCPtr, this);
  }

  public double back() {
    return MyoushuJNI.ListDouble_back(swigCPtr, this);
  }

}

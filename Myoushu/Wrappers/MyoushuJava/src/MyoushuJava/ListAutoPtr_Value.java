/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListAutoPtr_Value {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListAutoPtr_Value(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListAutoPtr_Value obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ListAutoPtr_Value(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ListAutoPtr_Value() {
    this(MyoushuJNI.new_ListAutoPtr_Value__SWIG_0(), true);
  }

  public ListAutoPtr_Value(ListAutoPtr_Value arg0) {
    this(MyoushuJNI.new_ListAutoPtr_Value__SWIG_1(ListAutoPtr_Value.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListAutoPtr_Value_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListAutoPtr_Value_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListAutoPtr_Value_clear(swigCPtr, this);
  }

  public void push_back(AutoPtr_Value val) {
    MyoushuJNI.ListAutoPtr_Value_push_back(swigCPtr, this, AutoPtr_Value.getCPtr(val), val);
  }

  public void pop_back() {
    MyoushuJNI.ListAutoPtr_Value_pop_back(swigCPtr, this);
  }

  public AutoPtr_Value front() {
    return new AutoPtr_Value(MyoushuJNI.ListAutoPtr_Value_front(swigCPtr, this), true);
  }

  public AutoPtr_Value back() {
    return new AutoPtr_Value(MyoushuJNI.ListAutoPtr_Value_back(swigCPtr, this), true);
  }

}

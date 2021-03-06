/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListLong {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListLong(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListLong obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ListLong(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ListLong() {
    this(MyoushuJNI.new_ListLong__SWIG_0(), true);
  }

  public ListLong(ListLong arg0) {
    this(MyoushuJNI.new_ListLong__SWIG_1(ListLong.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListLong_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListLong_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListLong_clear(swigCPtr, this);
  }

  public void push_back(int val) {
    MyoushuJNI.ListLong_push_back(swigCPtr, this, val);
  }

  public void pop_back() {
    MyoushuJNI.ListLong_pop_back(swigCPtr, this);
  }

  public int front() {
    return MyoushuJNI.ListLong_front(swigCPtr, this);
  }

  public int back() {
    return MyoushuJNI.ListLong_back(swigCPtr, this);
  }

}

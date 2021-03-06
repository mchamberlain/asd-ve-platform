/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListInt {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListInt(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListInt obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ListInt(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ListInt() {
    this(MyoushuJNI.new_ListInt__SWIG_0(), true);
  }

  public ListInt(ListInt arg0) {
    this(MyoushuJNI.new_ListInt__SWIG_1(ListInt.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListInt_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListInt_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListInt_clear(swigCPtr, this);
  }

  public void push_back(int val) {
    MyoushuJNI.ListInt_push_back(swigCPtr, this, val);
  }

  public void pop_back() {
    MyoushuJNI.ListInt_pop_back(swigCPtr, this);
  }

  public int front() {
    return MyoushuJNI.ListInt_front(swigCPtr, this);
  }

  public int back() {
    return MyoushuJNI.ListInt_back(swigCPtr, this);
  }

}

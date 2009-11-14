/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ListString {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ListString(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ListString obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_ListString(swigCPtr);
    }
    swigCPtr = 0;
  }

  public ListString() {
    this(MyoushuJNI.new_ListString__SWIG_0(), true);
  }

  public ListString(ListString arg0) {
    this(MyoushuJNI.new_ListString__SWIG_1(ListString.getCPtr(arg0), arg0), true);
  }

  public long size() {
    return MyoushuJNI.ListString_size(swigCPtr, this);
  }

  public boolean empty() {
    return MyoushuJNI.ListString_empty(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ListString_clear(swigCPtr, this);
  }

  public void push_back(String val) {
    MyoushuJNI.ListString_push_back(swigCPtr, this, val);
  }

  public void pop_back() {
    MyoushuJNI.ListString_pop_back(swigCPtr, this);
  }

  public String front() {
    return MyoushuJNI.ListString_front(swigCPtr, this);
  }

  public String back() {
    return MyoushuJNI.ListString_back(swigCPtr, this);
  }

}
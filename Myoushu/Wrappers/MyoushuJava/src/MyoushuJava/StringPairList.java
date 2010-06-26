/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class StringPairList {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public StringPairList(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(StringPairList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_StringPairList(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void parseCSString(String str) {
    MyoushuJNI.StringPairList_parseCSString(swigCPtr, this, str);
  }

  public String get(String key) {
    return MyoushuJNI.StringPairList_get(swigCPtr, this, key);
  }

  public boolean end() {
    return MyoushuJNI.StringPairList_end(swigCPtr, this);
  }

  public void insert(String ts, String t) {
    MyoushuJNI.StringPairList_insert(swigCPtr, this, ts, t);
  }

  public SWIGTYPE_p_std__pairT_std__string_std__string_t begin() {
    return new SWIGTYPE_p_std__pairT_std__string_std__string_t(MyoushuJNI.StringPairList_begin(swigCPtr, this), true);
  }

  public boolean hasKey(String key) {
    return MyoushuJNI.StringPairList_hasKey(swigCPtr, this, key);
  }

  public String getFirstOf(String key) {
    return MyoushuJNI.StringPairList_getFirstOf(swigCPtr, this, key);
  }

  public boolean hasNext() {
    return MyoushuJNI.StringPairList_hasNext(swigCPtr, this);
  }

  public SWIGTYPE_p_std__pairT_std__string_std__string_t next() {
    return new SWIGTYPE_p_std__pairT_std__string_std__string_t(MyoushuJNI.StringPairList_next(swigCPtr, this), true);
  }

  public long count() {
    return MyoushuJNI.StringPairList_count(swigCPtr, this);
  }

  public void empty() {
    MyoushuJNI.StringPairList_empty(swigCPtr, this);
  }

  public void dumpToConsole() {
    MyoushuJNI.StringPairList_dumpToConsole(swigCPtr, this);
  }

  public void setItems(SWIGTYPE_p_std__listT_std__pairT_std__string_std__string_t_t value) {
    MyoushuJNI.StringPairList_items_set(swigCPtr, this, SWIGTYPE_p_std__listT_std__pairT_std__string_std__string_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_std__listT_std__pairT_std__string_std__string_t_t getItems() {
    long cPtr = MyoushuJNI.StringPairList_items_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_std__listT_std__pairT_std__string_std__string_t_t(cPtr, false);
  }

  public void setMIterator(SWIGTYPE_p_NxOgre__StringPairList__Type__iterator value) {
    MyoushuJNI.StringPairList_mIterator_set(swigCPtr, this, SWIGTYPE_p_NxOgre__StringPairList__Type__iterator.getCPtr(value));
  }

  public SWIGTYPE_p_NxOgre__StringPairList__Type__iterator getMIterator() {
    return new SWIGTYPE_p_NxOgre__StringPairList__Type__iterator(MyoushuJNI.StringPairList_mIterator_get(swigCPtr, this), true);
  }

  public StringPairList() {
    this(MyoushuJNI.new_StringPairList(), true);
  }

}

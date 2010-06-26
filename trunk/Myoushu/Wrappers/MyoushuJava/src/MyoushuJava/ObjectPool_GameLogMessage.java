/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ObjectPool_GameLogMessage {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ObjectPool_GameLogMessage(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ObjectPool_GameLogMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ObjectPool_GameLogMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ObjectPool_GameLogMessage(long maxNumberOfObjects) {
    this(MyoushuJNI.new_ObjectPool_GameLogMessage__SWIG_0(maxNumberOfObjects), true);
  }

  public ObjectPool_GameLogMessage() {
    this(MyoushuJNI.new_ObjectPool_GameLogMessage__SWIG_1(), true);
  }

  public PoolObject add(PoolObject object, boolean autoDelete) {
    long cPtr = MyoushuJNI.ObjectPool_GameLogMessage_add__SWIG_0(swigCPtr, this, PoolObject.getCPtr(object), object, autoDelete);
    return (cPtr == 0) ? null : new PoolObject(cPtr, false);
  }

  public PoolObject add(PoolObject object) {
    long cPtr = MyoushuJNI.ObjectPool_GameLogMessage_add__SWIG_1(swigCPtr, this, PoolObject.getCPtr(object), object);
    return (cPtr == 0) ? null : new PoolObject(cPtr, false);
  }

  public SWIGTYPE_p_Myoushu__GameLogMessage get(boolean autoCreate) {
    long cPtr = MyoushuJNI.ObjectPool_GameLogMessage_get__SWIG_0(swigCPtr, this, autoCreate);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Myoushu__GameLogMessage(cPtr, false);
  }

  public SWIGTYPE_p_Myoushu__GameLogMessage get() {
    long cPtr = MyoushuJNI.ObjectPool_GameLogMessage_get__SWIG_1(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Myoushu__GameLogMessage(cPtr, false);
  }

}

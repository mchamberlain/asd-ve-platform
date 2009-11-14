/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class PoolObject extends NamedObject_PoolObject {
  private long swigCPtr;

  public PoolObject(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGPoolObjectUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(PoolObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_PoolObject(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public String getClassName() {
    return MyoushuJNI.PoolObject_getClassName(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.PoolObject_clear(swigCPtr, this);
  }

  public void returnToPool(boolean autoDelete) {
    MyoushuJNI.PoolObject_returnToPool__SWIG_0(swigCPtr, this, autoDelete);
  }

  public void returnToPool() {
    MyoushuJNI.PoolObject_returnToPool__SWIG_1(swigCPtr, this);
  }

}

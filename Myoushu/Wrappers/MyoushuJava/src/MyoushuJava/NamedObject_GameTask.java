/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NamedObject_GameTask extends NamedObjectBase {
  private long swigCPtr;

  public NamedObject_GameTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNamedObject_GameTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NamedObject_GameTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_NamedObject_GameTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public static String getStaticClassName() {
    return MyoushuJNI.NamedObject_GameTask_getStaticClassName();
  }

  public static GameTask staticCastPtr(SWIGTYPE_p_void p) {
    long cPtr = MyoushuJNI.NamedObject_GameTask_staticCastPtr(SWIGTYPE_p_void.getCPtr(p));
    return (cPtr == 0) ? null : new GameTask(cPtr, false);
  }

}

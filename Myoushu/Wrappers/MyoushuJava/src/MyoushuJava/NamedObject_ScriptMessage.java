/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NamedObject_ScriptMessage extends NamedObjectBase {
  private long swigCPtr;

  public NamedObject_ScriptMessage(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNamedObject_ScriptMessageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NamedObject_ScriptMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NamedObject_ScriptMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static String getStaticClassName() {
    return MyoushuJNI.NamedObject_ScriptMessage_getStaticClassName();
  }

  public static ScriptMessage staticCastPtr(SWIGTYPE_p_void p) {
    long cPtr = MyoushuJNI.NamedObject_ScriptMessage_staticCastPtr(SWIGTYPE_p_void.getCPtr(p));
    return (cPtr == 0) ? null : new ScriptMessage(cPtr, false);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class IWidgetCreator {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public IWidgetCreator(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IWidgetCreator obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_IWidgetCreator(swigCPtr);
    }
    swigCPtr = 0;
  }

  public void _linkChildWidget(Widget _widget) {
    MyoushuJNI.IWidgetCreator__linkChildWidget(swigCPtr, this, Widget.getCPtr(_widget), _widget);
  }

  public void _unlinkChildWidget(Widget _widget) {
    MyoushuJNI.IWidgetCreator__unlinkChildWidget(swigCPtr, this, Widget.getCPtr(_widget), _widget);
  }

}

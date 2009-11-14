/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ControllerTaskManager extends Singleton_ControllerTaskManager {
  private long swigCPtr;

  public ControllerTaskManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGControllerTaskManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ControllerTaskManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_ControllerTaskManager(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public ControllerTaskManager() {
    this(MyoushuJNI.new_ControllerTaskManager(), true);
  }

  public void addController(Controller controller) {
    MyoushuJNI.ControllerTaskManager_addController__SWIG_0(swigCPtr, this, Controller.getCPtr(controller), controller);
  }

  public boolean addController(String name) {
    return MyoushuJNI.ControllerTaskManager_addController__SWIG_1(swigCPtr, this, name);
  }

  public void removeController(Controller controller) {
    MyoushuJNI.ControllerTaskManager_removeController__SWIG_0(swigCPtr, this, Controller.getCPtr(controller), controller);
  }

  public boolean removeController(String name) {
    return MyoushuJNI.ControllerTaskManager_removeController__SWIG_1(swigCPtr, this, name);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class PhysicsTask extends Task {
  private long swigCPtr;

  public PhysicsTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGPhysicsTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(PhysicsTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_PhysicsTask(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public PhysicsTask(int priority, String name, long executionInterval, long iterationLimit) {
    this(MyoushuJNI.new_PhysicsTask__SWIG_0(priority, name, executionInterval, iterationLimit), true);
  }

  public PhysicsTask(int priority, String name, long executionInterval) {
    this(MyoushuJNI.new_PhysicsTask__SWIG_1(priority, name, executionInterval), true);
  }

  public PhysicsTask(int priority, String name) {
    this(MyoushuJNI.new_PhysicsTask__SWIG_2(priority, name), true);
  }

  public PhysicsTask() {
    this(MyoushuJNI.new_PhysicsTask__SWIG_3(), true);
  }

  public String getClassName() {
    return MyoushuJNI.PhysicsTask_getClassName(swigCPtr, this);
  }

  public void init() {
    MyoushuJNI.PhysicsTask_init(swigCPtr, this);
  }

  public void suspend() {
    MyoushuJNI.PhysicsTask_suspend(swigCPtr, this);
  }

  public void execute(long timeDelta) {
    MyoushuJNI.PhysicsTask_execute(swigCPtr, this, timeDelta);
  }

  public void kill() {
    MyoushuJNI.PhysicsTask_kill(swigCPtr, this);
  }

  public SWIGTYPE_p_NxOgre__World getWorld() {
    long cPtr = MyoushuJNI.PhysicsTask_getWorld(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__World(cPtr, false);
  }

  public void receiveTimerTaskMessage(AutoPtr_TimerTaskMessage message) {
    MyoushuJNI.PhysicsTask_receiveTimerTaskMessage(swigCPtr, this, AutoPtr_TimerTaskMessage.getCPtr(message), message);
  }

}

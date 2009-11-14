/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class TimerTask extends NamedObject_TimerTask {
  private long swigCPtr;

  public TimerTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGTimerTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(TimerTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_TimerTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public TimerTask(int priority, String name) {
    this(MyoushuJNI.new_TimerTask__SWIG_0(priority, name), true);
  }

  public TimerTask() {
    this(MyoushuJNI.new_TimerTask__SWIG_1(), true);
  }

  public String getClassName() {
    return MyoushuJNI.TimerTask_getClassName(swigCPtr, this);
  }

  public void setState(Task.TaskState state) {
    MyoushuJNI.TimerTask_setState(swigCPtr, this, state.swigValue());
  }

  public void init() {
    MyoushuJNI.TimerTask_init(swigCPtr, this);
  }

  public void suspend() {
    MyoushuJNI.TimerTask_suspend(swigCPtr, this);
  }

  public void kill() {
    MyoushuJNI.TimerTask_kill(swigCPtr, this);
  }

  public void resetStats() {
    MyoushuJNI.TimerTask_resetStats(swigCPtr, this);
  }

  public void execute(long timeDelta) {
    MyoushuJNI.TimerTask_execute(swigCPtr, this, timeDelta);
  }

  public long getDelta() {
    return MyoushuJNI.TimerTask_getDelta(swigCPtr, this);
  }

  public long getAbsTime() {
    return MyoushuJNI.TimerTask_getAbsTime(swigCPtr, this);
  }

  public long getIterationCnt() {
    return MyoushuJNI.TimerTask_getIterationCnt(swigCPtr, this);
  }

  public long getSmallestTimeDelta() {
    return MyoushuJNI.TimerTask_getSmallestTimeDelta(swigCPtr, this);
  }

  public long getLargestTimeDelta() {
    return MyoushuJNI.TimerTask_getLargestTimeDelta(swigCPtr, this);
  }

  public long getAbsTimeMillis() {
    return MyoushuJNI.TimerTask_getAbsTimeMillis(swigCPtr, this);
  }

}

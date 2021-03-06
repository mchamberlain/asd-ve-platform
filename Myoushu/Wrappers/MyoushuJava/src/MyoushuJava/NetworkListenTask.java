/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NetworkListenTask extends ConcurrentTask {
  private long swigCPtr;

  public NetworkListenTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNetworkListenTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NetworkListenTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NetworkListenTask(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public NetworkListenTask(String name, int priority, long executionInterval, long iterationLimit) {
    this(MyoushuJNI.new_NetworkListenTask__SWIG_0(name, priority, executionInterval, iterationLimit), true);
  }

  public NetworkListenTask(String name, int priority, long executionInterval) {
    this(MyoushuJNI.new_NetworkListenTask__SWIG_1(name, priority, executionInterval), true);
  }

  public NetworkListenTask(String name, int priority) {
    this(MyoushuJNI.new_NetworkListenTask__SWIG_2(name, priority), true);
  }

  public String getClassName() {
    return MyoushuJNI.NetworkListenTask_getClassName(swigCPtr, this);
  }

  public void setNetworkListenBehaviour(NetworkListenBehaviour listenBehaviour) {
    MyoushuJNI.NetworkListenTask_setNetworkListenBehaviour(swigCPtr, this, NetworkListenBehaviour.getCPtr(listenBehaviour), listenBehaviour);
  }

  public NetworkListenBehaviour getNetworkListenBehaviour() {
    long cPtr = MyoushuJNI.NetworkListenTask_getNetworkListenBehaviour__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new NetworkListenBehaviour(cPtr, false);
  }

  public void init() {
    MyoushuJNI.NetworkListenTask_init(swigCPtr, this);
  }

  public void suspend() {
    MyoushuJNI.NetworkListenTask_suspend(swigCPtr, this);
  }

  public void execute(long timeDelta) {
    MyoushuJNI.NetworkListenTask_execute(swigCPtr, this, timeDelta);
  }

  public void kill() {
    MyoushuJNI.NetworkListenTask_kill(swigCPtr, this);
  }

  public void run() {
    MyoushuJNI.NetworkListenTask_run(swigCPtr, this);
  }

}

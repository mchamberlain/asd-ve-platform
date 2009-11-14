/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NetworkTransmitTask extends Task {
  private long swigCPtr;

  public NetworkTransmitTask(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNetworkTransmitTaskUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NetworkTransmitTask obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_NetworkTransmitTask(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public NetworkTransmitTask(int priority, String name, long executionInterval, long iterationLimit) {
    this(MyoushuJNI.new_NetworkTransmitTask__SWIG_0(priority, name, executionInterval, iterationLimit), true);
  }

  public NetworkTransmitTask(int priority, String name, long executionInterval) {
    this(MyoushuJNI.new_NetworkTransmitTask__SWIG_1(priority, name, executionInterval), true);
  }

  public NetworkTransmitTask(int priority, String name) {
    this(MyoushuJNI.new_NetworkTransmitTask__SWIG_2(priority, name), true);
  }

  public NetworkTransmitTask() {
    this(MyoushuJNI.new_NetworkTransmitTask__SWIG_3(), true);
  }

  public String getClassName() {
    return MyoushuJNI.NetworkTransmitTask_getClassName(swigCPtr, this);
  }

  public void init() {
    MyoushuJNI.NetworkTransmitTask_init(swigCPtr, this);
  }

  public void suspend() {
    MyoushuJNI.NetworkTransmitTask_suspend(swigCPtr, this);
  }

  public void execute(long timeDelta) {
    MyoushuJNI.NetworkTransmitTask_execute(swigCPtr, this, timeDelta);
  }

  public void kill() {
    MyoushuJNI.NetworkTransmitTask_kill(swigCPtr, this);
  }

  public NetworkTransmitBehaviour getNetworkTransmitBehaviour() {
    long cPtr = MyoushuJNI.NetworkTransmitTask_getNetworkTransmitBehaviour__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new NetworkTransmitBehaviour(cPtr, false);
  }

  public void setNetworkTransmitBehaviour(NetworkTransmitBehaviour pBehaviour) {
    MyoushuJNI.NetworkTransmitTask_setNetworkTransmitBehaviour(swigCPtr, this, NetworkTransmitBehaviour.getCPtr(pBehaviour), pBehaviour);
  }

}

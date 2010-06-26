/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class DefaultNetworkTransmitBehaviour extends NetworkTransmitBehaviour {
  private long swigCPtr;

  public DefaultNetworkTransmitBehaviour(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGDefaultNetworkTransmitBehaviourUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(DefaultNetworkTransmitBehaviour obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_DefaultNetworkTransmitBehaviour(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public DefaultNetworkTransmitBehaviour() {
    this(MyoushuJNI.new_DefaultNetworkTransmitBehaviour(), true);
  }

  public void init() {
    MyoushuJNI.DefaultNetworkTransmitBehaviour_init(swigCPtr, this);
  }

  public void update() {
    MyoushuJNI.DefaultNetworkTransmitBehaviour_update(swigCPtr, this);
  }

  public void receiveNetworkMessage(AutoPtr_NetworkMessage message) {
    MyoushuJNI.DefaultNetworkTransmitBehaviour_receiveNetworkMessage(swigCPtr, this, AutoPtr_NetworkMessage.getCPtr(message), message);
  }

}

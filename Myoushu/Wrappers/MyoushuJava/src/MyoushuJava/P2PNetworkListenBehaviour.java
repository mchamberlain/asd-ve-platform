/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class P2PNetworkListenBehaviour extends NetworkListenBehaviour {
  private long swigCPtr;

  public P2PNetworkListenBehaviour(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGP2PNetworkListenBehaviourUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(P2PNetworkListenBehaviour obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_P2PNetworkListenBehaviour(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public P2PNetworkListenBehaviour() {
    this(MyoushuJNI.new_P2PNetworkListenBehaviour(), true);
  }

  public String getClassName() {
    return MyoushuJNI.P2PNetworkListenBehaviour_getClassName(swigCPtr, this);
  }

  public void processReceivedMessage(SWIGTYPE_p_Poco__Net__IPAddress source, String buffer, int length) {
    MyoushuJNI.P2PNetworkListenBehaviour_processReceivedMessage(swigCPtr, this, SWIGTYPE_p_Poco__Net__IPAddress.getCPtr(source), buffer, length);
  }

}

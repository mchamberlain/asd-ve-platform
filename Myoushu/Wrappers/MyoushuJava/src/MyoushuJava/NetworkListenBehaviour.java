/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NetworkListenBehaviour extends NamedObject_NetworkListenBehaviour {
  private long swigCPtr;

  public NetworkListenBehaviour(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNetworkListenBehaviourUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NetworkListenBehaviour obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NetworkListenBehaviour(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public String getClassName() {
    return MyoushuJNI.NetworkListenBehaviour_getClassName(swigCPtr, this);
  }

  public void processReceivedMessage(SWIGTYPE_p_Poco__Net__IPAddress source, String buffer, int length) {
    MyoushuJNI.NetworkListenBehaviour_processReceivedMessage(swigCPtr, this, SWIGTYPE_p_Poco__Net__IPAddress.getCPtr(source), buffer, length);
  }

  public void setNetworkMessageCallback(NetworkMessage.NetworkMessageType messageType, SWIGTYPE_p_Myoushu__ActionStringCallbackBaseT_bool_Myoushu__NetworkMessage_t pCallback) {
    MyoushuJNI.NetworkListenBehaviour_setNetworkMessageCallback__SWIG_0(swigCPtr, this, messageType.swigValue(), SWIGTYPE_p_Myoushu__ActionStringCallbackBaseT_bool_Myoushu__NetworkMessage_t.getCPtr(pCallback));
  }

  public void setNetworkMessageCallback(NetworkMessage.NetworkMessageType messageType, SWIGTYPE_p_Myoushu__ActionStringCallbackT_bool_Myoushu__NetworkMessage_t__ActionStringCallbackGlobalFunction pCallback) {
    MyoushuJNI.NetworkListenBehaviour_setNetworkMessageCallback__SWIG_1(swigCPtr, this, messageType.swigValue(), SWIGTYPE_p_Myoushu__ActionStringCallbackT_bool_Myoushu__NetworkMessage_t__ActionStringCallbackGlobalFunction.getCPtr(pCallback));
  }

  public void setNetworkMessageCallback(NetworkMessage.NetworkMessageType messageType, SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__NetworkMessage_t__ActionStringCallbackLuaFunctor pCallback) {
    MyoushuJNI.NetworkListenBehaviour_setNetworkMessageCallback__SWIG_2(swigCPtr, this, messageType.swigValue(), SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__NetworkMessage_t__ActionStringCallbackLuaFunctor.getCPtr(pCallback));
  }

  public void setNetworkMessageCallback(NetworkMessage.NetworkMessageType messageType, String callback) {
    MyoushuJNI.NetworkListenBehaviour_setNetworkMessageCallback__SWIG_3(swigCPtr, this, messageType.swigValue(), callback);
  }

}

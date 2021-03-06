/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ServerRecord extends HostRecord {
  private long swigCPtr;

  public ServerRecord(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGServerRecordUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ServerRecord obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ServerRecord(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ServerRecord(SWIGTYPE_p_Poco__Net__HostEntry hostEntry) {
    this(MyoushuJNI.new_ServerRecord__SWIG_0(SWIGTYPE_p_Poco__Net__HostEntry.getCPtr(hostEntry)), true);
  }

  public ServerRecord(SWIGTYPE_p_Poco__Net__IPAddress ipAddress, String name) {
    this(MyoushuJNI.new_ServerRecord__SWIG_1(SWIGTYPE_p_Poco__Net__IPAddress.getCPtr(ipAddress), name), true);
  }

  public String getClassName() {
    return MyoushuJNI.ServerRecord_getClassName(swigCPtr, this);
  }

}

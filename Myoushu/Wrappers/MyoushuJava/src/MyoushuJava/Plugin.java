/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Plugin extends NamedInstance {
  private long swigCPtr;

  public Plugin(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGPluginUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Plugin obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Plugin(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void install() {
    MyoushuJNI.Plugin_install(swigCPtr, this);
  }

  public void initialise() {
    MyoushuJNI.Plugin_initialise(swigCPtr, this);
  }

  public void shutdown() {
    MyoushuJNI.Plugin_shutdown(swigCPtr, this);
  }

  public void uninstall() {
    MyoushuJNI.Plugin_uninstall(swigCPtr, this);
  }

}
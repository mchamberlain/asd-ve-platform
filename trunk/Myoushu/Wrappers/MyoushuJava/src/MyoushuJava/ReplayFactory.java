/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ReplayFactory extends NamedObjectFactory_Replay {
  private long swigCPtr;

  public ReplayFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGReplayFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ReplayFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_ReplayFactory(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public ReplayFactory() {
    this(MyoushuJNI.new_ReplayFactory(), true);
  }

  public NamedInstance findByName(String replayName) {
    long cPtr = MyoushuJNI.ReplayFactory_findByName(swigCPtr, this, replayName);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public Replay make(String replayName, boolean ensureUniqueName) {
    long cPtr = MyoushuJNI.ReplayFactory_make__SWIG_0(swigCPtr, this, replayName, ensureUniqueName);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public Replay make(String replayName, String resourceGroup, boolean openForWrite, boolean overwrite) {
    long cPtr = MyoushuJNI.ReplayFactory_make__SWIG_1(swigCPtr, this, replayName, resourceGroup, openForWrite, overwrite);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public Replay make(String replayName, String resourceGroup, boolean openForWrite) {
    long cPtr = MyoushuJNI.ReplayFactory_make__SWIG_2(swigCPtr, this, replayName, resourceGroup, openForWrite);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

}

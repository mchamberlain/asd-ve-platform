/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NamedObjectFactory_Replay extends NamedObjectFactoryBase {
  private long swigCPtr;

  public NamedObjectFactory_Replay(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNamedObjectFactory_ReplayUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NamedObjectFactory_Replay obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NamedObjectFactory_Replay(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Replay_t_t__const_iterator begin() {
    return new SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Replay_t_t__const_iterator(MyoushuJNI.NamedObjectFactory_Replay_begin__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Replay_t_t__const_iterator end() {
    return new SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Replay_t_t__const_iterator(MyoushuJNI.NamedObjectFactory_Replay_end__SWIG_0(swigCPtr, this), true);
  }

  public void add(Replay obj) {
    MyoushuJNI.NamedObjectFactory_Replay_add(swigCPtr, this, Replay.getCPtr(obj), obj);
  }

  public boolean remove(Replay obj) {
    return MyoushuJNI.NamedObjectFactory_Replay_remove(swigCPtr, this, Replay.getCPtr(obj), obj);
  }

  public boolean removeByName(String name) {
    return MyoushuJNI.NamedObjectFactory_Replay_removeByName(swigCPtr, this, name);
  }

  public Replay find(String name) {
    long cPtr = MyoushuJNI.NamedObjectFactory_Replay_find(swigCPtr, this, name);
    return (cPtr == 0) ? null : new Replay(cPtr, false);
  }

  public NamedInstance findByName(String name) {
    long cPtr = MyoushuJNI.NamedObjectFactory_Replay_findByName(swigCPtr, this, name);
    return (cPtr == 0) ? null : new NamedInstance(cPtr, false);
  }

  public void clear() {
    MyoushuJNI.NamedObjectFactory_Replay_clear(swigCPtr, this);
  }

  public void acquireReadLock() {
    MyoushuJNI.NamedObjectFactory_Replay_acquireReadLock(swigCPtr, this);
  }

  public void releaseLock() {
    MyoushuJNI.NamedObjectFactory_Replay_releaseLock(swigCPtr, this);
  }

}

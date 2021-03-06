/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NamedObjectFactory_Sound extends NamedObjectFactoryBase {
  private long swigCPtr;

  public NamedObjectFactory_Sound(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNamedObjectFactory_SoundUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NamedObjectFactory_Sound obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NamedObjectFactory_Sound(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Sound_t_t__const_iterator begin() {
    return new SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Sound_t_t__const_iterator(MyoushuJNI.NamedObjectFactory_Sound_begin__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Sound_t_t__const_iterator end() {
    return new SWIGTYPE_p_std__mapT_Ogre__String_Poco__AutoPtrT_Myoushu__Sound_t_t__const_iterator(MyoushuJNI.NamedObjectFactory_Sound_end__SWIG_0(swigCPtr, this), true);
  }

  public void add(Sound obj) {
    MyoushuJNI.NamedObjectFactory_Sound_add(swigCPtr, this, Sound.getCPtr(obj), obj);
  }

  public boolean remove(Sound obj) {
    return MyoushuJNI.NamedObjectFactory_Sound_remove(swigCPtr, this, Sound.getCPtr(obj), obj);
  }

  public boolean removeByName(String name) {
    return MyoushuJNI.NamedObjectFactory_Sound_removeByName(swigCPtr, this, name);
  }

  public Sound find(String name) {
    long cPtr = MyoushuJNI.NamedObjectFactory_Sound_find(swigCPtr, this, name);
    return (cPtr == 0) ? null : new Sound(cPtr, false);
  }

  public NamedInstance findByName(String name) {
    long cPtr = MyoushuJNI.NamedObjectFactory_Sound_findByName(swigCPtr, this, name);
    return (cPtr == 0) ? null : new NamedInstance(cPtr, false);
  }

  public void clear() {
    MyoushuJNI.NamedObjectFactory_Sound_clear(swigCPtr, this);
  }

  public void acquireReadLock() {
    MyoushuJNI.NamedObjectFactory_Sound_acquireReadLock(swigCPtr, this);
  }

  public void releaseLock() {
    MyoushuJNI.NamedObjectFactory_Sound_releaseLock(swigCPtr, this);
  }

}

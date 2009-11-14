/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class MovableObjectFactory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public MovableObjectFactory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(MovableObjectFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_MovableObjectFactory(swigCPtr);
    }
    swigCPtr = 0;
  }

  public String getType() {
    return MyoushuJNI.MovableObjectFactory_getType(swigCPtr, this);
  }

  public MovableObject createInstance(String name, SWIGTYPE_p_Ogre__SceneManager manager, SWIGTYPE_p_std__mapT_std__string_std__string_t params) {
    long cPtr = MyoushuJNI.MovableObjectFactory_createInstance__SWIG_0(swigCPtr, this, name, SWIGTYPE_p_Ogre__SceneManager.getCPtr(manager), SWIGTYPE_p_std__mapT_std__string_std__string_t.getCPtr(params));
    return (cPtr == 0) ? null : new MovableObject(cPtr, false);
  }

  public MovableObject createInstance(String name, SWIGTYPE_p_Ogre__SceneManager manager) {
    long cPtr = MyoushuJNI.MovableObjectFactory_createInstance__SWIG_1(swigCPtr, this, name, SWIGTYPE_p_Ogre__SceneManager.getCPtr(manager));
    return (cPtr == 0) ? null : new MovableObject(cPtr, false);
  }

  public void destroyInstance(MovableObject obj) {
    MyoushuJNI.MovableObjectFactory_destroyInstance(swigCPtr, this, MovableObject.getCPtr(obj), obj);
  }

  public boolean requestTypeFlags() {
    return MyoushuJNI.MovableObjectFactory_requestTypeFlags(swigCPtr, this);
  }

  public void _notifyTypeFlags(long flag) {
    MyoushuJNI.MovableObjectFactory__notifyTypeFlags(swigCPtr, this, flag);
  }

  public long getTypeFlags() {
    return MyoushuJNI.MovableObjectFactory_getTypeFlags(swigCPtr, this);
  }

}

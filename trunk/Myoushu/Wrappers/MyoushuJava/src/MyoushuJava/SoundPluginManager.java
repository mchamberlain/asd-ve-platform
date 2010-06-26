/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class SoundPluginManager extends Singleton_SoundPluginManager {
  private long swigCPtr;

  public SoundPluginManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGSoundPluginManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SoundPluginManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_SoundPluginManager(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SoundPluginManager() {
    this(MyoushuJNI.new_SoundPluginManager(), true);
  }

  public void registerSoundFactory(SoundFactory pSoundFactory, String className) {
    MyoushuJNI.SoundPluginManager_registerSoundFactory(swigCPtr, this, SoundFactory.getCPtr(pSoundFactory), pSoundFactory, className);
  }

  public SoundFactory unregisterSoundFactory(String className) {
    long cPtr = MyoushuJNI.SoundPluginManager_unregisterSoundFactory(swigCPtr, this, className);
    return (cPtr == 0) ? null : new SoundFactory(cPtr, false);
  }

  public SoundFactory getFactoryFor(String className) {
    long cPtr = MyoushuJNI.SoundPluginManager_getFactoryFor(swigCPtr, this, className);
    return (cPtr == 0) ? null : new SoundFactory(cPtr, false);
  }

  public Sound make(String className, String instanceName) {
    long cPtr = MyoushuJNI.SoundPluginManager_make(swigCPtr, this, className, instanceName);
    return (cPtr == 0) ? null : new Sound(cPtr, false);
  }

  public boolean destroy(Sound pInstance) {
    return MyoushuJNI.SoundPluginManager_destroy(swigCPtr, this, Sound.getCPtr(pInstance), pInstance);
  }

}

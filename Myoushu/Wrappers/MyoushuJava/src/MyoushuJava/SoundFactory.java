/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class SoundFactory extends NamedObjectFactory_Sound {
  private long swigCPtr;

  public SoundFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGSoundFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SoundFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_SoundFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public StaticSound makeStaticSound(String name, String filePath, boolean loop, boolean preBuffer) {
    long cPtr = MyoushuJNI.SoundFactory_makeStaticSound__SWIG_0(swigCPtr, this, name, filePath, loop, preBuffer);
    return (cPtr == 0) ? null : new StaticSound(cPtr, false);
  }

  public StaticSound makeStaticSound(String name, String filePath, boolean loop) {
    long cPtr = MyoushuJNI.SoundFactory_makeStaticSound__SWIG_1(swigCPtr, this, name, filePath, loop);
    return (cPtr == 0) ? null : new StaticSound(cPtr, false);
  }

  public StaticSound makeStaticSound(String name, String filePath) {
    long cPtr = MyoushuJNI.SoundFactory_makeStaticSound__SWIG_2(swigCPtr, this, name, filePath);
    return (cPtr == 0) ? null : new StaticSound(cPtr, false);
  }

  public StreamSound makeStreamSound(String name, String filePath, boolean loop, boolean preBuffer) {
    long cPtr = MyoushuJNI.SoundFactory_makeStreamSound__SWIG_0(swigCPtr, this, name, filePath, loop, preBuffer);
    return (cPtr == 0) ? null : new StreamSound(cPtr, false);
  }

  public StreamSound makeStreamSound(String name, String filePath, boolean loop) {
    long cPtr = MyoushuJNI.SoundFactory_makeStreamSound__SWIG_1(swigCPtr, this, name, filePath, loop);
    return (cPtr == 0) ? null : new StreamSound(cPtr, false);
  }

  public StreamSound makeStreamSound(String name, String filePath) {
    long cPtr = MyoushuJNI.SoundFactory_makeStreamSound__SWIG_2(swigCPtr, this, name, filePath);
    return (cPtr == 0) ? null : new StreamSound(cPtr, false);
  }

  public void destroyInstance(Sound pInstance) {
    MyoushuJNI.SoundFactory_destroyInstance(swigCPtr, this, Sound.getCPtr(pInstance), pInstance);
  }

  public void destroyAll() {
    MyoushuJNI.SoundFactory_destroyAll(swigCPtr, this);
  }

}
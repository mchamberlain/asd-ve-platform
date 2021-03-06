/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class SoundManager {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public SoundManager(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(SoundManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_SoundManager(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setMasterVolume(float vol) {
    MyoushuJNI.SoundManager_setMasterVolume(swigCPtr, this, vol);
  }

  public float getMasterVolume() {
    return MyoushuJNI.SoundManager_getMasterVolume(swigCPtr, this);
  }

  public void playSound(String sName) {
    MyoushuJNI.SoundManager_playSound(swigCPtr, this, sName);
  }

  public void pauseSound(String sName) {
    MyoushuJNI.SoundManager_pauseSound(swigCPtr, this, sName);
  }

  public void stopSound(String sName) {
    MyoushuJNI.SoundManager_stopSound(swigCPtr, this, sName);
  }

  public void stopAllSounds() {
    MyoushuJNI.SoundManager_stopAllSounds(swigCPtr, this);
  }

  public void pauseAllSounds() {
    MyoushuJNI.SoundManager_pauseAllSounds(swigCPtr, this);
  }

  public void resumeAllPausedSounds() {
    MyoushuJNI.SoundManager_resumeAllPausedSounds(swigCPtr, this);
  }

  public MovableObject getListener() {
    long cPtr = MyoushuJNI.SoundManager_getListener(swigCPtr, this);
    return (cPtr == 0) ? null : new MovableObject(cPtr, false);
  }

}

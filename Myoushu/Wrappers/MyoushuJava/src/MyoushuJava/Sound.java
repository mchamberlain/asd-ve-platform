/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Sound extends NamedInstance {
  private long swigCPtr;

  public Sound(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGSoundUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Sound obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Sound(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public String getClassName() {
    return MyoushuJNI.Sound_getClassName(swigCPtr, this);
  }

  public void play() {
    MyoushuJNI.Sound_play(swigCPtr, this);
  }

  public void pause() {
    MyoushuJNI.Sound_pause(swigCPtr, this);
  }

  public void stop() {
    MyoushuJNI.Sound_stop(swigCPtr, this);
  }

  public MovableObject getMovableObject() {
    long cPtr = MyoushuJNI.Sound_getMovableObject(swigCPtr, this);
    return (cPtr == 0) ? null : new MovableObject(cPtr, false);
  }

  public void setLoop(boolean loop) {
    MyoushuJNI.Sound_setLoop(swigCPtr, this, loop);
  }

  public boolean isPlaying() {
    return MyoushuJNI.Sound_isPlaying(swigCPtr, this);
  }

  public boolean isPaused() {
    return MyoushuJNI.Sound_isPaused(swigCPtr, this);
  }

  public boolean isStopped() {
    return MyoushuJNI.Sound_isStopped(swigCPtr, this);
  }

  public void setVolume(float volume) {
    MyoushuJNI.Sound_setVolume(swigCPtr, this, volume);
  }

  public float getVolume() {
    return MyoushuJNI.Sound_getVolume(swigCPtr, this);
  }

  public void setPitch(float pitch) {
    MyoushuJNI.Sound_setPitch(swigCPtr, this, pitch);
  }

  public float getPitch() {
    return MyoushuJNI.Sound_getPitch(swigCPtr, this);
  }

  public float getAudioLength() {
    return MyoushuJNI.Sound_getAudioLength(swigCPtr, this);
  }

  public void setFinishedCallback(String luaFunctionName, boolean enabled) {
    MyoushuJNI.Sound_setFinishedCallback__SWIG_0(swigCPtr, this, luaFunctionName, enabled);
  }

  public void setFinishedCallback(String luaFunctionName) {
    MyoushuJNI.Sound_setFinishedCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setFinishedCallback(FunctorBase pFunctor, boolean enabled) {
    MyoushuJNI.Sound_setFinishedCallback__SWIG_2(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor, enabled);
  }

  public void setFinishedCallback(FunctorBase pFunctor) {
    MyoushuJNI.Sound_setFinishedCallback__SWIG_3(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setFinishedCallbackEnabled(boolean enabled) {
    MyoushuJNI.Sound_setFinishedCallbackEnabled(swigCPtr, this, enabled);
  }

  public void setLoopCallback(String luaFunctionName, boolean enabled) {
    MyoushuJNI.Sound_setLoopCallback__SWIG_0(swigCPtr, this, luaFunctionName, enabled);
  }

  public void setLoopCallback(String luaFunctionName) {
    MyoushuJNI.Sound_setLoopCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setLoopCallback(FunctorBase pFunctor, boolean enabled) {
    MyoushuJNI.Sound_setLoopCallback__SWIG_2(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor, enabled);
  }

  public void setLoopCallback(FunctorBase pFunctor) {
    MyoushuJNI.Sound_setLoopCallback__SWIG_3(swigCPtr, this, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void setLoopCallbackEnabled(boolean enabled) {
    MyoushuJNI.Sound_setLoopCallbackEnabled(swigCPtr, this, enabled);
  }

}

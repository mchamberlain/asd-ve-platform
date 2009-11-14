/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class VideoTaskManager extends Singleton_VideoTaskManager {
  private long swigCPtr;

  public VideoTaskManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGVideoTaskManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(VideoTaskManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_VideoTaskManager(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public VideoTaskManager() {
    this(MyoushuJNI.new_VideoTaskManager(), true);
  }

  public RenderWindow getRenderWindow(String name) {
    long cPtr = MyoushuJNI.VideoTaskManager_getRenderWindow__SWIG_0(swigCPtr, this, name);
    return (cPtr == 0) ? null : new RenderWindow(cPtr, false);
  }

  public RenderWindow getRenderWindow() {
    long cPtr = MyoushuJNI.VideoTaskManager_getRenderWindow__SWIG_1(swigCPtr, this);
    return (cPtr == 0) ? null : new RenderWindow(cPtr, false);
  }

  public void showFPS(boolean show) {
    MyoushuJNI.VideoTaskManager_showFPS(swigCPtr, this, show);
  }

}

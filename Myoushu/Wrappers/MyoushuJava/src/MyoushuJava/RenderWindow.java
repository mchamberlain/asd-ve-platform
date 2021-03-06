/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class RenderWindow extends RenderTarget {
  private long swigCPtr;

  public RenderWindow(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGRenderWindowUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(RenderWindow obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_RenderWindow(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void create(String name, long width, long height, boolean fullScreen, SWIGTYPE_p_std__mapT_std__string_std__string_t miscParams) {
    MyoushuJNI.RenderWindow_create(swigCPtr, this, name, width, height, fullScreen, SWIGTYPE_p_std__mapT_std__string_std__string_t.getCPtr(miscParams));
  }

  public void setFullscreen(boolean fullScreen, long width, long height) {
    MyoushuJNI.RenderWindow_setFullscreen(swigCPtr, this, fullScreen, width, height);
  }

  public void destroy() {
    MyoushuJNI.RenderWindow_destroy(swigCPtr, this);
  }

  public void resize(long width, long height) {
    MyoushuJNI.RenderWindow_resize(swigCPtr, this, width, height);
  }

  public void windowMovedOrResized() {
    MyoushuJNI.RenderWindow_windowMovedOrResized(swigCPtr, this);
  }

  public void reposition(int left, int top) {
    MyoushuJNI.RenderWindow_reposition(swigCPtr, this, left, top);
  }

  public boolean isVisible() {
    return MyoushuJNI.RenderWindow_isVisible(swigCPtr, this);
  }

  public void setVisible(boolean visible) {
    MyoushuJNI.RenderWindow_setVisible(swigCPtr, this, visible);
  }

  public boolean isActive() {
    return MyoushuJNI.RenderWindow_isActive(swigCPtr, this);
  }

  public boolean isClosed() {
    return MyoushuJNI.RenderWindow_isClosed(swigCPtr, this);
  }

  public boolean isPrimary() {
    return MyoushuJNI.RenderWindow_isPrimary(swigCPtr, this);
  }

  public boolean isFullScreen() {
    return MyoushuJNI.RenderWindow_isFullScreen(swigCPtr, this);
  }

  public void getMetrics(SWIGTYPE_p_unsigned_int width, SWIGTYPE_p_unsigned_int height, SWIGTYPE_p_unsigned_int colourDepth, SWIGTYPE_p_int left, SWIGTYPE_p_int top) {
    MyoushuJNI.RenderWindow_getMetrics(swigCPtr, this, SWIGTYPE_p_unsigned_int.getCPtr(width), SWIGTYPE_p_unsigned_int.getCPtr(height), SWIGTYPE_p_unsigned_int.getCPtr(colourDepth), SWIGTYPE_p_int.getCPtr(left), SWIGTYPE_p_int.getCPtr(top));
  }

  public SWIGTYPE_p_Ogre__PixelFormat suggestPixelFormat() {
    return new SWIGTYPE_p_Ogre__PixelFormat(MyoushuJNI.RenderWindow_suggestPixelFormat(swigCPtr, this), true);
  }

  public boolean isDeactivatedOnFocusChange() {
    return MyoushuJNI.RenderWindow_isDeactivatedOnFocusChange(swigCPtr, this);
  }

  public void setDeactivateOnFocusChange(boolean deactivate) {
    MyoushuJNI.RenderWindow_setDeactivateOnFocusChange(swigCPtr, this, deactivate);
  }

}

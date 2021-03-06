/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Viewport {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Viewport(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Viewport obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Viewport(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Viewport(Camera camera, RenderTarget target, float left, float top, float width, float height, int ZOrder) {
    this(MyoushuJNI.new_Viewport(Camera.getCPtr(camera), camera, RenderTarget.getCPtr(target), target, left, top, width, height, ZOrder), true);
  }

  public void _updateDimensions() {
    MyoushuJNI.Viewport__updateDimensions(swigCPtr, this);
  }

  public void update() {
    MyoushuJNI.Viewport_update(swigCPtr, this);
  }

  public RenderTarget getTarget() {
    long cPtr = MyoushuJNI.Viewport_getTarget(swigCPtr, this);
    return (cPtr == 0) ? null : new RenderTarget(cPtr, false);
  }

  public Camera getCamera() {
    long cPtr = MyoushuJNI.Viewport_getCamera(swigCPtr, this);
    return (cPtr == 0) ? null : new Camera(cPtr, false);
  }

  public void setCamera(Camera cam) {
    MyoushuJNI.Viewport_setCamera(swigCPtr, this, Camera.getCPtr(cam), cam);
  }

  public int getZOrder() {
    return MyoushuJNI.Viewport_getZOrder(swigCPtr, this);
  }

  public float getLeft() {
    return MyoushuJNI.Viewport_getLeft(swigCPtr, this);
  }

  public float getTop() {
    return MyoushuJNI.Viewport_getTop(swigCPtr, this);
  }

  public float getWidth() {
    return MyoushuJNI.Viewport_getWidth(swigCPtr, this);
  }

  public float getHeight() {
    return MyoushuJNI.Viewport_getHeight(swigCPtr, this);
  }

  public int getActualLeft() {
    return MyoushuJNI.Viewport_getActualLeft(swigCPtr, this);
  }

  public int getActualTop() {
    return MyoushuJNI.Viewport_getActualTop(swigCPtr, this);
  }

  public int getActualWidth() {
    return MyoushuJNI.Viewport_getActualWidth(swigCPtr, this);
  }

  public int getActualHeight() {
    return MyoushuJNI.Viewport_getActualHeight(swigCPtr, this);
  }

  public void setDimensions(float left, float top, float width, float height) {
    MyoushuJNI.Viewport_setDimensions(swigCPtr, this, left, top, width, height);
  }

  public void setBackgroundColour(ColourValue colour) {
    MyoushuJNI.Viewport_setBackgroundColour(swigCPtr, this, ColourValue.getCPtr(colour), colour);
  }

  public ColourValue getBackgroundColour() {
    return new ColourValue(MyoushuJNI.Viewport_getBackgroundColour(swigCPtr, this), false);
  }

  public void setClearEveryFrame(boolean clear, long buffers) {
    MyoushuJNI.Viewport_setClearEveryFrame__SWIG_0(swigCPtr, this, clear, buffers);
  }

  public void setClearEveryFrame(boolean clear) {
    MyoushuJNI.Viewport_setClearEveryFrame__SWIG_1(swigCPtr, this, clear);
  }

  public boolean getClearEveryFrame() {
    return MyoushuJNI.Viewport_getClearEveryFrame(swigCPtr, this);
  }

  public long getClearBuffers() {
    return MyoushuJNI.Viewport_getClearBuffers(swigCPtr, this);
  }

  public void setMaterialScheme(String schemeName) {
    MyoushuJNI.Viewport_setMaterialScheme(swigCPtr, this, schemeName);
  }

  public String getMaterialScheme() {
    return MyoushuJNI.Viewport_getMaterialScheme(swigCPtr, this);
  }

  public void getActualDimensions(SWIGTYPE_p_int left, SWIGTYPE_p_int top, SWIGTYPE_p_int width, SWIGTYPE_p_int height) {
    MyoushuJNI.Viewport_getActualDimensions(swigCPtr, this, SWIGTYPE_p_int.getCPtr(left), SWIGTYPE_p_int.getCPtr(top), SWIGTYPE_p_int.getCPtr(width), SWIGTYPE_p_int.getCPtr(height));
  }

  public boolean _isUpdated() {
    return MyoushuJNI.Viewport__isUpdated(swigCPtr, this);
  }

  public void _clearUpdatedFlag() {
    MyoushuJNI.Viewport__clearUpdatedFlag(swigCPtr, this);
  }

  public long _getNumRenderedFaces() {
    return MyoushuJNI.Viewport__getNumRenderedFaces(swigCPtr, this);
  }

  public long _getNumRenderedBatches() {
    return MyoushuJNI.Viewport__getNumRenderedBatches(swigCPtr, this);
  }

  public void setOverlaysEnabled(boolean enabled) {
    MyoushuJNI.Viewport_setOverlaysEnabled(swigCPtr, this, enabled);
  }

  public boolean getOverlaysEnabled() {
    return MyoushuJNI.Viewport_getOverlaysEnabled(swigCPtr, this);
  }

  public void setSkiesEnabled(boolean enabled) {
    MyoushuJNI.Viewport_setSkiesEnabled(swigCPtr, this, enabled);
  }

  public boolean getSkiesEnabled() {
    return MyoushuJNI.Viewport_getSkiesEnabled(swigCPtr, this);
  }

  public void setShadowsEnabled(boolean enabled) {
    MyoushuJNI.Viewport_setShadowsEnabled(swigCPtr, this, enabled);
  }

  public boolean getShadowsEnabled() {
    return MyoushuJNI.Viewport_getShadowsEnabled(swigCPtr, this);
  }

  public void setVisibilityMask(long mask) {
    MyoushuJNI.Viewport_setVisibilityMask(swigCPtr, this, mask);
  }

  public long getVisibilityMask() {
    return MyoushuJNI.Viewport_getVisibilityMask(swigCPtr, this);
  }

  public void setRenderQueueInvocationSequenceName(String sequenceName) {
    MyoushuJNI.Viewport_setRenderQueueInvocationSequenceName(swigCPtr, this, sequenceName);
  }

  public String getRenderQueueInvocationSequenceName() {
    return MyoushuJNI.Viewport_getRenderQueueInvocationSequenceName(swigCPtr, this);
  }

  public SWIGTYPE_p_Ogre__RenderQueueInvocationSequence _getRenderQueueInvocationSequence() {
    long cPtr = MyoushuJNI.Viewport__getRenderQueueInvocationSequence(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__RenderQueueInvocationSequence(cPtr, false);
  }

}

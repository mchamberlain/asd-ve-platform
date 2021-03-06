/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class RenderTarget {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public RenderTarget(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(RenderTarget obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_RenderTarget(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public String getName() {
    return MyoushuJNI.RenderTarget_getName(swigCPtr, this);
  }

  public void getMetrics(SWIGTYPE_p_unsigned_int width, SWIGTYPE_p_unsigned_int height, SWIGTYPE_p_unsigned_int colourDepth) {
    MyoushuJNI.RenderTarget_getMetrics(swigCPtr, this, SWIGTYPE_p_unsigned_int.getCPtr(width), SWIGTYPE_p_unsigned_int.getCPtr(height), SWIGTYPE_p_unsigned_int.getCPtr(colourDepth));
  }

  public long getWidth() {
    return MyoushuJNI.RenderTarget_getWidth(swigCPtr, this);
  }

  public long getHeight() {
    return MyoushuJNI.RenderTarget_getHeight(swigCPtr, this);
  }

  public long getColourDepth() {
    return MyoushuJNI.RenderTarget_getColourDepth(swigCPtr, this);
  }

  public void update(boolean swapBuffers) {
    MyoushuJNI.RenderTarget_update__SWIG_0(swigCPtr, this, swapBuffers);
  }

  public void update() {
    MyoushuJNI.RenderTarget_update__SWIG_1(swigCPtr, this);
  }

  public void swapBuffers(boolean waitForVSync) {
    MyoushuJNI.RenderTarget_swapBuffers__SWIG_0(swigCPtr, this, waitForVSync);
  }

  public void swapBuffers() {
    MyoushuJNI.RenderTarget_swapBuffers__SWIG_1(swigCPtr, this);
  }

  public Viewport addViewport(Camera cam, int ZOrder, float left, float top, float width, float height) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_0(swigCPtr, this, Camera.getCPtr(cam), cam, ZOrder, left, top, width, height);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public Viewport addViewport(Camera cam, int ZOrder, float left, float top, float width) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_1(swigCPtr, this, Camera.getCPtr(cam), cam, ZOrder, left, top, width);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public Viewport addViewport(Camera cam, int ZOrder, float left, float top) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_2(swigCPtr, this, Camera.getCPtr(cam), cam, ZOrder, left, top);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public Viewport addViewport(Camera cam, int ZOrder, float left) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_3(swigCPtr, this, Camera.getCPtr(cam), cam, ZOrder, left);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public Viewport addViewport(Camera cam, int ZOrder) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_4(swigCPtr, this, Camera.getCPtr(cam), cam, ZOrder);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public Viewport addViewport(Camera cam) {
    long cPtr = MyoushuJNI.RenderTarget_addViewport__SWIG_5(swigCPtr, this, Camera.getCPtr(cam), cam);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public int getNumViewports() {
    return MyoushuJNI.RenderTarget_getNumViewports(swigCPtr, this);
  }

  public Viewport getViewport(int index) {
    long cPtr = MyoushuJNI.RenderTarget_getViewport(swigCPtr, this, index);
    return (cPtr == 0) ? null : new Viewport(cPtr, false);
  }

  public void removeViewport(int ZOrder) {
    MyoushuJNI.RenderTarget_removeViewport(swigCPtr, this, ZOrder);
  }

  public void removeAllViewports() {
    MyoushuJNI.RenderTarget_removeAllViewports(swigCPtr, this);
  }

  public void getStatistics(SWIGTYPE_p_float lastFPS, SWIGTYPE_p_float avgFPS, SWIGTYPE_p_float bestFPS, SWIGTYPE_p_float worstFPS) {
    MyoushuJNI.RenderTarget_getStatistics__SWIG_0(swigCPtr, this, SWIGTYPE_p_float.getCPtr(lastFPS), SWIGTYPE_p_float.getCPtr(avgFPS), SWIGTYPE_p_float.getCPtr(bestFPS), SWIGTYPE_p_float.getCPtr(worstFPS));
  }

  public SWIGTYPE_p_Ogre__RenderTarget__FrameStats getStatistics() {
    return new SWIGTYPE_p_Ogre__RenderTarget__FrameStats(MyoushuJNI.RenderTarget_getStatistics__SWIG_1(swigCPtr, this), false);
  }

  public float getLastFPS() {
    return MyoushuJNI.RenderTarget_getLastFPS(swigCPtr, this);
  }

  public float getAverageFPS() {
    return MyoushuJNI.RenderTarget_getAverageFPS(swigCPtr, this);
  }

  public float getBestFPS() {
    return MyoushuJNI.RenderTarget_getBestFPS(swigCPtr, this);
  }

  public float getWorstFPS() {
    return MyoushuJNI.RenderTarget_getWorstFPS(swigCPtr, this);
  }

  public float getBestFrameTime() {
    return MyoushuJNI.RenderTarget_getBestFrameTime(swigCPtr, this);
  }

  public float getWorstFrameTime() {
    return MyoushuJNI.RenderTarget_getWorstFrameTime(swigCPtr, this);
  }

  public void resetStatistics() {
    MyoushuJNI.RenderTarget_resetStatistics(swigCPtr, this);
  }

  public void getCustomAttribute(String name, SWIGTYPE_p_void pData) {
    MyoushuJNI.RenderTarget_getCustomAttribute(swigCPtr, this, name, SWIGTYPE_p_void.getCPtr(pData));
  }

  public void addListener(SWIGTYPE_p_Ogre__RenderTargetListener listener) {
    MyoushuJNI.RenderTarget_addListener(swigCPtr, this, SWIGTYPE_p_Ogre__RenderTargetListener.getCPtr(listener));
  }

  public void removeListener(SWIGTYPE_p_Ogre__RenderTargetListener listener) {
    MyoushuJNI.RenderTarget_removeListener(swigCPtr, this, SWIGTYPE_p_Ogre__RenderTargetListener.getCPtr(listener));
  }

  public void removeAllListeners() {
    MyoushuJNI.RenderTarget_removeAllListeners(swigCPtr, this);
  }

  public void setPriority(short priority) {
    MyoushuJNI.RenderTarget_setPriority(swigCPtr, this, priority);
  }

  public short getPriority() {
    return MyoushuJNI.RenderTarget_getPriority(swigCPtr, this);
  }

  public boolean isActive() {
    return MyoushuJNI.RenderTarget_isActive(swigCPtr, this);
  }

  public void setActive(boolean state) {
    MyoushuJNI.RenderTarget_setActive(swigCPtr, this, state);
  }

  public void setAutoUpdated(boolean autoupdate) {
    MyoushuJNI.RenderTarget_setAutoUpdated(swigCPtr, this, autoupdate);
  }

  public boolean isAutoUpdated() {
    return MyoushuJNI.RenderTarget_isAutoUpdated(swigCPtr, this);
  }

  public void copyContentsToMemory(SWIGTYPE_p_Ogre__PixelBox dst, RenderTarget.FrameBuffer buffer) {
    MyoushuJNI.RenderTarget_copyContentsToMemory__SWIG_0(swigCPtr, this, SWIGTYPE_p_Ogre__PixelBox.getCPtr(dst), buffer.swigValue());
  }

  public void copyContentsToMemory(SWIGTYPE_p_Ogre__PixelBox dst) {
    MyoushuJNI.RenderTarget_copyContentsToMemory__SWIG_1(swigCPtr, this, SWIGTYPE_p_Ogre__PixelBox.getCPtr(dst));
  }

  public SWIGTYPE_p_Ogre__PixelFormat suggestPixelFormat() {
    return new SWIGTYPE_p_Ogre__PixelFormat(MyoushuJNI.RenderTarget_suggestPixelFormat(swigCPtr, this), true);
  }

  public void writeContentsToFile(String filename) {
    MyoushuJNI.RenderTarget_writeContentsToFile(swigCPtr, this, filename);
  }

  public String writeContentsToTimestampedFile(String filenamePrefix, String filenameSuffix) {
    return MyoushuJNI.RenderTarget_writeContentsToTimestampedFile(swigCPtr, this, filenamePrefix, filenameSuffix);
  }

  public boolean requiresTextureFlipping() {
    return MyoushuJNI.RenderTarget_requiresTextureFlipping(swigCPtr, this);
  }

  public long getTriangleCount() {
    return MyoushuJNI.RenderTarget_getTriangleCount(swigCPtr, this);
  }

  public long getBatchCount() {
    return MyoushuJNI.RenderTarget_getBatchCount(swigCPtr, this);
  }

  public void _notifyCameraRemoved(Camera cam) {
    MyoushuJNI.RenderTarget__notifyCameraRemoved(swigCPtr, this, Camera.getCPtr(cam), cam);
  }

  public boolean isPrimary() {
    return MyoushuJNI.RenderTarget_isPrimary(swigCPtr, this);
  }

  public boolean isHardwareGammaEnabled() {
    return MyoushuJNI.RenderTarget_isHardwareGammaEnabled(swigCPtr, this);
  }

  public long getFSAA() {
    return MyoushuJNI.RenderTarget_getFSAA(swigCPtr, this);
  }

  public SWIGTYPE_p_Ogre__RenderTarget__Impl _getImpl() {
    long cPtr = MyoushuJNI.RenderTarget__getImpl(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__RenderTarget__Impl(cPtr, false);
  }

  public enum StatFlags {
    SF_NONE(MyoushuJNI.RenderTarget_SF_NONE_get()),
    SF_FPS(MyoushuJNI.RenderTarget_SF_FPS_get()),
    SF_AVG_FPS(MyoushuJNI.RenderTarget_SF_AVG_FPS_get()),
    SF_BEST_FPS(MyoushuJNI.RenderTarget_SF_BEST_FPS_get()),
    SF_WORST_FPS(MyoushuJNI.RenderTarget_SF_WORST_FPS_get()),
    SF_TRIANGLE_COUNT(MyoushuJNI.RenderTarget_SF_TRIANGLE_COUNT_get()),
    SF_ALL(MyoushuJNI.RenderTarget_SF_ALL_get());

    public final int swigValue() {
      return swigValue;
    }

    public static StatFlags swigToEnum(int swigValue) {
      StatFlags[] swigValues = StatFlags.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (StatFlags swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + StatFlags.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private StatFlags() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private StatFlags(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private StatFlags(StatFlags swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

  public enum FrameBuffer {
    FB_FRONT,
    FB_BACK,
    FB_AUTO;

    public final int swigValue() {
      return swigValue;
    }

    public static FrameBuffer swigToEnum(int swigValue) {
      FrameBuffer[] swigValues = FrameBuffer.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (FrameBuffer swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + FrameBuffer.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private FrameBuffer() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private FrameBuffer(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private FrameBuffer(FrameBuffer swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

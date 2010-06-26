/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class IRenderTarget {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public IRenderTarget(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(IRenderTarget obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_IRenderTarget(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void begin() {
    MyoushuJNI.IRenderTarget_begin(swigCPtr, this);
  }

  public void end() {
    MyoushuJNI.IRenderTarget_end(swigCPtr, this);
  }

  public void doRender(SWIGTYPE_p_MyGUI__IVertexBuffer _buffer, SWIGTYPE_p_MyGUI__ITexture _texture, long _count) {
    MyoushuJNI.IRenderTarget_doRender__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__IVertexBuffer.getCPtr(_buffer), SWIGTYPE_p_MyGUI__ITexture.getCPtr(_texture), _count);
  }

  public void doRender(SWIGTYPE_p_MyGUI__IVertexBuffer _buffer, String _texture, long _count) {
    MyoushuJNI.IRenderTarget_doRender__SWIG_1(swigCPtr, this, SWIGTYPE_p_MyGUI__IVertexBuffer.getCPtr(_buffer), _texture, _count);
  }

  public RenderTargetInfo getInfo() {
    return new RenderTargetInfo(MyoushuJNI.IRenderTarget_getInfo(swigCPtr, this), false);
  }

}

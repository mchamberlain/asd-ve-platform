/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ImageIndexInfo {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ImageIndexInfo(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ImageIndexInfo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ImageIndexInfo(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ImageIndexInfo(String _texture, SWIGTYPE_p_MyGUI__types__TSizeT_int_t _size, float _rate, SWIGTYPE_p_std__vectorT_MyGUI__types__TPointT_int_t_t _frames) {
    this(MyoushuJNI.new_ImageIndexInfo(_texture, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_size), _rate, SWIGTYPE_p_std__vectorT_MyGUI__types__TPointT_int_t_t.getCPtr(_frames)), true);
  }

  public String getTexture() {
    return MyoushuJNI.ImageIndexInfo_texture_get(swigCPtr, this);
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t getSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.ImageIndexInfo_size_get(swigCPtr, this), false);
  }

  public float getRate() {
    return MyoushuJNI.ImageIndexInfo_rate_get(swigCPtr, this);
  }

  public SWIGTYPE_p_std__vectorT_MyGUI__types__TPointT_int_t_t getFrames() {
    return new SWIGTYPE_p_std__vectorT_MyGUI__types__TPointT_int_t_t(MyoushuJNI.ImageIndexInfo_frames_get(swigCPtr, this), false);
  }

}

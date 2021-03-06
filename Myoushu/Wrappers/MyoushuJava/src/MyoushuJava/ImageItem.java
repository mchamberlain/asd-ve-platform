/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ImageItem {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ImageItem(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ImageItem obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ImageItem(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ImageItem() {
    this(MyoushuJNI.new_ImageItem(), true);
  }

  public void setFrame_rate(float value) {
    MyoushuJNI.ImageItem_frame_rate_set(swigCPtr, this, value);
  }

  public float getFrame_rate() {
    return MyoushuJNI.ImageItem_frame_rate_get(swigCPtr, this);
  }

  public void setImages(SWIGTYPE_p_std__vectorT_MyGUI__types__TRectT_float_t_t value) {
    MyoushuJNI.ImageItem_images_set(swigCPtr, this, SWIGTYPE_p_std__vectorT_MyGUI__types__TRectT_float_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_std__vectorT_MyGUI__types__TRectT_float_t_t getImages() {
    long cPtr = MyoushuJNI.ImageItem_images_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_std__vectorT_MyGUI__types__TRectT_float_t_t(cPtr, false);
  }

}

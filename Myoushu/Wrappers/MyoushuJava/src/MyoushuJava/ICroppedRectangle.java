/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ICroppedRectangle {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ICroppedRectangle(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ICroppedRectangle obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ICroppedRectangle(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ICroppedRectangle() {
    this(MyoushuJNI.new_ICroppedRectangle(), true);
  }

  public ICroppedRectangle getCroppedParent() {
    long cPtr = MyoushuJNI.ICroppedRectangle_getCroppedParent(swigCPtr, this);
    return (cPtr == 0) ? null : new ICroppedRectangle(cPtr, false);
  }

  public void setCoord(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _value) {
    MyoushuJNI.ICroppedRectangle_setCoord(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_value));
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getCoord() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.ICroppedRectangle_getCoord(swigCPtr, this), false);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TPointT_int_t _value) {
    MyoushuJNI.ICroppedRectangle_setPosition(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TPointT_int_t.getCPtr(_value));
  }

  public SWIGTYPE_p_MyGUI__types__TPointT_int_t getPosition() {
    return new SWIGTYPE_p_MyGUI__types__TPointT_int_t(MyoushuJNI.ICroppedRectangle_getPosition(swigCPtr, this), true);
  }

  public void setSize(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _value) {
    MyoushuJNI.ICroppedRectangle_setSize(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_value));
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t getSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.ICroppedRectangle_getSize(swigCPtr, this), true);
  }

  public void setVisible(boolean _value) {
    MyoushuJNI.ICroppedRectangle_setVisible(swigCPtr, this, _value);
  }

  public boolean isVisible() {
    return MyoushuJNI.ICroppedRectangle_isVisible(swigCPtr, this);
  }

  public SWIGTYPE_p_MyGUI__types__TPointT_int_t getAbsolutePosition() {
    return new SWIGTYPE_p_MyGUI__types__TPointT_int_t(MyoushuJNI.ICroppedRectangle_getAbsolutePosition(swigCPtr, this), false);
  }

  public SWIGTYPE_p_MyGUI__types__TRectT_int_t getAbsoluteRect() {
    return new SWIGTYPE_p_MyGUI__types__TRectT_int_t(MyoushuJNI.ICroppedRectangle_getAbsoluteRect(swigCPtr, this), true);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getAbsoluteCoord() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.ICroppedRectangle_getAbsoluteCoord(swigCPtr, this), true);
  }

  public int getAbsoluteLeft() {
    return MyoushuJNI.ICroppedRectangle_getAbsoluteLeft(swigCPtr, this);
  }

  public int getAbsoluteTop() {
    return MyoushuJNI.ICroppedRectangle_getAbsoluteTop(swigCPtr, this);
  }

  public void setAlign(Align _value) {
    MyoushuJNI.ICroppedRectangle_setAlign(swigCPtr, this, Align.getCPtr(_value), _value);
  }

  public Align getAlign() {
    return new Align(MyoushuJNI.ICroppedRectangle_getAlign(swigCPtr, this), true);
  }

  public int getLeft() {
    return MyoushuJNI.ICroppedRectangle_getLeft(swigCPtr, this);
  }

  public int getRight() {
    return MyoushuJNI.ICroppedRectangle_getRight(swigCPtr, this);
  }

  public int getTop() {
    return MyoushuJNI.ICroppedRectangle_getTop(swigCPtr, this);
  }

  public int getBottom() {
    return MyoushuJNI.ICroppedRectangle_getBottom(swigCPtr, this);
  }

  public int getWidth() {
    return MyoushuJNI.ICroppedRectangle_getWidth(swigCPtr, this);
  }

  public int getHeight() {
    return MyoushuJNI.ICroppedRectangle_getHeight(swigCPtr, this);
  }

  public boolean _isMargin() {
    return MyoushuJNI.ICroppedRectangle__isMargin(swigCPtr, this);
  }

  public int _getViewLeft() {
    return MyoushuJNI.ICroppedRectangle__getViewLeft(swigCPtr, this);
  }

  public int _getViewRight() {
    return MyoushuJNI.ICroppedRectangle__getViewRight(swigCPtr, this);
  }

  public int _getViewTop() {
    return MyoushuJNI.ICroppedRectangle__getViewTop(swigCPtr, this);
  }

  public int _getViewBottom() {
    return MyoushuJNI.ICroppedRectangle__getViewBottom(swigCPtr, this);
  }

  public int _getViewWidth() {
    return MyoushuJNI.ICroppedRectangle__getViewWidth(swigCPtr, this);
  }

  public int _getViewHeight() {
    return MyoushuJNI.ICroppedRectangle__getViewHeight(swigCPtr, this);
  }

  public void _updateView() {
    MyoushuJNI.ICroppedRectangle__updateView(swigCPtr, this);
  }

  public void _correctView() {
    MyoushuJNI.ICroppedRectangle__correctView(swigCPtr, this);
  }

  public void _setAlign(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _oldsize, boolean _update) {
    MyoushuJNI.ICroppedRectangle__setAlign__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_oldsize), _update);
  }

  public void _setAlign(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _oldcoord, boolean _update) {
    MyoushuJNI.ICroppedRectangle__setAlign__SWIG_1(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_oldcoord), _update);
  }

  public void _setCroppedParent(ICroppedRectangle _parent) {
    MyoushuJNI.ICroppedRectangle__setCroppedParent(swigCPtr, this, ICroppedRectangle.getCPtr(_parent), _parent);
  }

  public SWIGTYPE_p_MyGUI__types__TRectT_int_t _getMargin() {
    return new SWIGTYPE_p_MyGUI__types__TRectT_int_t(MyoushuJNI.ICroppedRectangle__getMargin(swigCPtr, this), false);
  }

  public int _getMarginLeft() {
    return MyoushuJNI.ICroppedRectangle__getMarginLeft(swigCPtr, this);
  }

  public int _getMarginRight() {
    return MyoushuJNI.ICroppedRectangle__getMarginRight(swigCPtr, this);
  }

  public int _getMarginTop() {
    return MyoushuJNI.ICroppedRectangle__getMarginTop(swigCPtr, this);
  }

  public int _getMarginBottom() {
    return MyoushuJNI.ICroppedRectangle__getMarginBottom(swigCPtr, this);
  }

  public void show() {
    MyoushuJNI.ICroppedRectangle_show(swigCPtr, this);
  }

  public void hide() {
    MyoushuJNI.ICroppedRectangle_hide(swigCPtr, this);
  }

  public boolean isShow() {
    return MyoushuJNI.ICroppedRectangle_isShow(swigCPtr, this);
  }

}

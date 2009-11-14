/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class StaticText extends Widget {
  private long swigCPtr;

  public StaticText(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGStaticTextUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(StaticText obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      throw new UnsupportedOperationException("C++ destructor does not have public access");
    }
    swigCPtr = 0;
    super.delete();
  }

  public StaticText() {
    this(MyoushuJNI.new_StaticText(), true);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getTextRegion() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.StaticText_getTextRegion(swigCPtr, this), true);
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t getTextSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.StaticText_getTextSize(swigCPtr, this), true);
  }

  public void setFontName(String _value) {
    MyoushuJNI.StaticText_setFontName(swigCPtr, this, _value);
  }

  public String getFontName() {
    return MyoushuJNI.StaticText_getFontName(swigCPtr, this);
  }

  public void setFontHeight(int _value) {
    MyoushuJNI.StaticText_setFontHeight(swigCPtr, this, _value);
  }

  public int getFontHeight() {
    return MyoushuJNI.StaticText_getFontHeight(swigCPtr, this);
  }

  public void setTextAlign(Align _value) {
    MyoushuJNI.StaticText_setTextAlign(swigCPtr, this, Align.getCPtr(_value), _value);
  }

  public Align getTextAlign() {
    return new Align(MyoushuJNI.StaticText_getTextAlign(swigCPtr, this), true);
  }

  public void setTextColour(Colour _value) {
    MyoushuJNI.StaticText_setTextColour(swigCPtr, this, Colour.getCPtr(_value), _value);
  }

  public Colour getTextColour() {
    return new Colour(MyoushuJNI.StaticText_getTextColour(swigCPtr, this), false);
  }

  public void setProperty(String _key, String _value) {
    MyoushuJNI.StaticText_setProperty(swigCPtr, this, _key, _value);
  }

  public void _initialise(WidgetStyle _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, WidgetSkinInfo _info, Widget _parent, ICroppedRectangle _croppedParent, IWidgetCreator _creator, String _name) {
    MyoushuJNI.StaticText__initialise(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, WidgetSkinInfo.getCPtr(_info), _info, Widget.getCPtr(_parent), _parent, ICroppedRectangle.getCPtr(_croppedParent), _croppedParent, IWidgetCreator.getCPtr(_creator), _creator, _name);
  }

}

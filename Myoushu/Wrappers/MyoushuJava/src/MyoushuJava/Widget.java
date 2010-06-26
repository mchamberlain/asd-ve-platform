/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Widget extends ICroppedRectangle {
  private long swigCPtr;

  public Widget(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGWidgetUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Widget obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        throw new UnsupportedOperationException("C++ destructor does not have public access");
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Widget() {
    this(MyoushuJNI.new_Widget(), true);
  }

  public Widget createWidgetT(String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, String _name) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_0(swigCPtr, this, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_1(swigCPtr, this, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(String _type, String _skin, int _left, int _top, int _width, int _height, Align _align, String _name) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_2(swigCPtr, this, _type, _skin, _left, _top, _width, _height, Align.getCPtr(_align), _align, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(String _type, String _skin, int _left, int _top, int _width, int _height, Align _align) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_3(swigCPtr, this, _type, _skin, _left, _top, _width, _height, Align.getCPtr(_align), _align);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetRealT(String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_float_t _coord, Align _align, String _name) {
    long cPtr = MyoushuJNI.Widget_createWidgetRealT__SWIG_0(swigCPtr, this, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_float_t.getCPtr(_coord), Align.getCPtr(_align), _align, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetRealT(String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_float_t _coord, Align _align) {
    long cPtr = MyoushuJNI.Widget_createWidgetRealT__SWIG_1(swigCPtr, this, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_float_t.getCPtr(_coord), Align.getCPtr(_align), _align);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetRealT(String _type, String _skin, float _left, float _top, float _width, float _height, Align _align, String _name) {
    long cPtr = MyoushuJNI.Widget_createWidgetRealT__SWIG_2(swigCPtr, this, _type, _skin, _left, _top, _width, _height, Align.getCPtr(_align), _align, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetRealT(String _type, String _skin, float _left, float _top, float _width, float _height, Align _align) {
    long cPtr = MyoushuJNI.Widget_createWidgetRealT__SWIG_3(swigCPtr, this, _type, _skin, _left, _top, _width, _height, Align.getCPtr(_align), _align);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(WidgetStyle _style, String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, String _layer, String _name) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_4(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, _layer, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(WidgetStyle _style, String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, String _layer) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_5(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, _layer);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget createWidgetT(WidgetStyle _style, String _type, String _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align) {
    long cPtr = MyoushuJNI.Widget_createWidgetT__SWIG_6(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, _type, _skin, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public String getName() {
    return MyoushuJNI.Widget_getName(swigCPtr, this);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TPointT_int_t _value) {
    MyoushuJNI.Widget_setPosition__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TPointT_int_t.getCPtr(_value));
  }

  public void setSize(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _value) {
    MyoushuJNI.Widget_setSize__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_value));
  }

  public void setCoord(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _value) {
    MyoushuJNI.Widget_setCoord__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_value));
  }

  public void setPosition(int _left, int _top) {
    MyoushuJNI.Widget_setPosition__SWIG_1(swigCPtr, this, _left, _top);
  }

  public void setSize(int _width, int _height) {
    MyoushuJNI.Widget_setSize__SWIG_1(swigCPtr, this, _width, _height);
  }

  public void setCoord(int _left, int _top, int _width, int _height) {
    MyoushuJNI.Widget_setCoord__SWIG_1(swigCPtr, this, _left, _top, _width, _height);
  }

  public void setRealPosition(SWIGTYPE_p_MyGUI__types__TPointT_float_t _value) {
    MyoushuJNI.Widget_setRealPosition__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TPointT_float_t.getCPtr(_value));
  }

  public void setRealSize(SWIGTYPE_p_MyGUI__types__TSizeT_float_t _value) {
    MyoushuJNI.Widget_setRealSize__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_float_t.getCPtr(_value));
  }

  public void setRealCoord(SWIGTYPE_p_MyGUI__types__TCoordT_float_t _value) {
    MyoushuJNI.Widget_setRealCoord__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_float_t.getCPtr(_value));
  }

  public void setRealPosition(float _left, float _top) {
    MyoushuJNI.Widget_setRealPosition__SWIG_1(swigCPtr, this, _left, _top);
  }

  public void setRealSize(float _width, float _height) {
    MyoushuJNI.Widget_setRealSize__SWIG_1(swigCPtr, this, _width, _height);
  }

  public void setRealCoord(float _left, float _top, float _width, float _height) {
    MyoushuJNI.Widget_setRealCoord__SWIG_1(swigCPtr, this, _left, _top, _width, _height);
  }

  public void setVisible(boolean _value) {
    MyoushuJNI.Widget_setVisible(swigCPtr, this, _value);
  }

  public void setAlign(Align _value) {
    MyoushuJNI.Widget_setAlign(swigCPtr, this, Align.getCPtr(_value), _value);
  }

  public void setCaption(UString _value) {
    MyoushuJNI.Widget_setCaption(swigCPtr, this, UString.getCPtr(_value), _value);
  }

  public UString getCaption() {
    return new UString(MyoushuJNI.Widget_getCaption(swigCPtr, this), false);
  }

  public void setAlpha(float _value) {
    MyoushuJNI.Widget_setAlpha(swigCPtr, this, _value);
  }

  public float getAlpha() {
    return MyoushuJNI.Widget_getAlpha(swigCPtr, this);
  }

  public void setInheritsAlpha(boolean _value) {
    MyoushuJNI.Widget_setInheritsAlpha(swigCPtr, this, _value);
  }

  public boolean isInheritsAlpha() {
    return MyoushuJNI.Widget_isInheritsAlpha(swigCPtr, this);
  }

  public boolean setState(String _value) {
    return MyoushuJNI.Widget_setState(swigCPtr, this, _value);
  }

  public boolean isRootWidget() {
    return MyoushuJNI.Widget_isRootWidget(swigCPtr, this);
  }

  public Widget getParent() {
    long cPtr = MyoushuJNI.Widget_getParent(swigCPtr, this);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public SWIGTYPE_p_MyGUI__EnumeratorT_std__vectorT_MyGUI__Widget_p_t_t getEnumerator() {
    return new SWIGTYPE_p_MyGUI__EnumeratorT_std__vectorT_MyGUI__Widget_p_t_t(MyoushuJNI.Widget_getEnumerator(swigCPtr, this), true);
  }

  public long getChildCount() {
    return MyoushuJNI.Widget_getChildCount(swigCPtr, this);
  }

  public Widget getChildAt(long _index) {
    long cPtr = MyoushuJNI.Widget_getChildAt(swigCPtr, this, _index);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public Widget findWidget(String _name) {
    long cPtr = MyoushuJNI.Widget_findWidget(swigCPtr, this, _name);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public void setNeedKeyFocus(boolean _value) {
    MyoushuJNI.Widget_setNeedKeyFocus(swigCPtr, this, _value);
  }

  public boolean isNeedKeyFocus() {
    return MyoushuJNI.Widget_isNeedKeyFocus(swigCPtr, this);
  }

  public void setNeedMouseFocus(boolean _value) {
    MyoushuJNI.Widget_setNeedMouseFocus(swigCPtr, this, _value);
  }

  public boolean isNeedMouseFocus() {
    return MyoushuJNI.Widget_isNeedMouseFocus(swigCPtr, this);
  }

  public void setInheritsPick(boolean _value) {
    MyoushuJNI.Widget_setInheritsPick(swigCPtr, this, _value);
  }

  public boolean isInheritsPick() {
    return MyoushuJNI.Widget_isInheritsPick(swigCPtr, this);
  }

  public void setMaskPick(String _filename) {
    MyoushuJNI.Widget_setMaskPick(swigCPtr, this, _filename);
  }

  public void setEnabled(boolean _value) {
    MyoushuJNI.Widget_setEnabled(swigCPtr, this, _value);
  }

  public void setEnabledSilent(boolean _value) {
    MyoushuJNI.Widget_setEnabledSilent(swigCPtr, this, _value);
  }

  public boolean isEnabled() {
    return MyoushuJNI.Widget_isEnabled(swigCPtr, this);
  }

  public void setPointer(String _value) {
    MyoushuJNI.Widget_setPointer(swigCPtr, this, _value);
  }

  public String getPointer() {
    return MyoushuJNI.Widget_getPointer(swigCPtr, this);
  }

  public String getLayerName() {
    return MyoushuJNI.Widget_getLayerName(swigCPtr, this);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getClientCoord() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.Widget_getClientCoord(swigCPtr, this), true);
  }

  public Widget getClientWidget() {
    long cPtr = MyoushuJNI.Widget_getClientWidget(swigCPtr, this);
    return (cPtr == 0) ? null : new Widget(cPtr, false);
  }

  public ISubWidgetText getSubWidgetText() {
    long cPtr = MyoushuJNI.Widget_getSubWidgetText(swigCPtr, this);
    return (cPtr == 0) ? null : new ISubWidgetText(cPtr, false);
  }

  public ISubWidgetRect getSubWidgetMain() {
    long cPtr = MyoushuJNI.Widget_getSubWidgetMain(swigCPtr, this);
    return (cPtr == 0) ? null : new ISubWidgetRect(cPtr, false);
  }

  public void setNeedToolTip(boolean _value) {
    MyoushuJNI.Widget_setNeedToolTip(swigCPtr, this, _value);
  }

  public boolean getNeedToolTip() {
    return MyoushuJNI.Widget_getNeedToolTip(swigCPtr, this);
  }

  public void setEnableToolTip(boolean _value) {
    MyoushuJNI.Widget_setEnableToolTip(swigCPtr, this, _value);
  }

  public boolean getEnableToolTip() {
    return MyoushuJNI.Widget_getEnableToolTip(swigCPtr, this);
  }

  public void detachFromWidget(String _layer) {
    MyoushuJNI.Widget_detachFromWidget__SWIG_0(swigCPtr, this, _layer);
  }

  public void detachFromWidget() {
    MyoushuJNI.Widget_detachFromWidget__SWIG_1(swigCPtr, this);
  }

  public void attachToWidget(Widget _parent, WidgetStyle _style, String _layer) {
    MyoushuJNI.Widget_attachToWidget__SWIG_0(swigCPtr, this, Widget.getCPtr(_parent), _parent, WidgetStyle.getCPtr(_style), _style, _layer);
  }

  public void attachToWidget(Widget _parent, WidgetStyle _style) {
    MyoushuJNI.Widget_attachToWidget__SWIG_1(swigCPtr, this, Widget.getCPtr(_parent), _parent, WidgetStyle.getCPtr(_style), _style);
  }

  public void attachToWidget(Widget _parent) {
    MyoushuJNI.Widget_attachToWidget__SWIG_2(swigCPtr, this, Widget.getCPtr(_parent), _parent);
  }

  public void changeWidgetSkin(String _skinname) {
    MyoushuJNI.Widget_changeWidgetSkin(swigCPtr, this, _skinname);
  }

  public void setWidgetStyle(WidgetStyle _style, String _layer) {
    MyoushuJNI.Widget_setWidgetStyle__SWIG_0(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, _layer);
  }

  public void setWidgetStyle(WidgetStyle _style) {
    MyoushuJNI.Widget_setWidgetStyle__SWIG_1(swigCPtr, this, WidgetStyle.getCPtr(_style), _style);
  }

  public WidgetStyle getWidgetStyle() {
    return new WidgetStyle(MyoushuJNI.Widget_getWidgetStyle(swigCPtr, this), true);
  }

  public void setProperty(String _key, String _value) {
    MyoushuJNI.Widget_setProperty(swigCPtr, this, _key, _value);
  }

  public void _getContainer(Widget _container, SWIGTYPE_p_size_t _index) {
    MyoushuJNI.Widget__getContainer(swigCPtr, this, Widget.getCPtr(_container), _container, SWIGTYPE_p_size_t.getCPtr(_index));
  }

  public void _forcePeek(Widget _widget) {
    MyoushuJNI.Widget__forcePeek(swigCPtr, this, Widget.getCPtr(_widget), _widget);
  }

  public void _setUVSet(SWIGTYPE_p_MyGUI__types__TRectT_float_t _rect) {
    MyoushuJNI.Widget__setUVSet(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TRectT_float_t.getCPtr(_rect));
  }

  public void _setTextureName(String _texture) {
    MyoushuJNI.Widget__setTextureName(swigCPtr, this, _texture);
  }

  public String _getTextureName() {
    return MyoushuJNI.Widget__getTextureName(swigCPtr, this);
  }

  public IWidgetCreator _getIWidgetCreator() {
    long cPtr = MyoushuJNI.Widget__getIWidgetCreator(swigCPtr, this);
    return (cPtr == 0) ? null : new IWidgetCreator(cPtr, false);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t _getTextRegion() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.Widget__getTextRegion(swigCPtr, this), true);
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t _getTextSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.Widget__getTextSize(swigCPtr, this), true);
  }

  public void _setFontName(String _font) {
    MyoushuJNI.Widget__setFontName(swigCPtr, this, _font);
  }

  public String _getFontName() {
    return MyoushuJNI.Widget__getFontName(swigCPtr, this);
  }

  public void _setFontHeight(int _height) {
    MyoushuJNI.Widget__setFontHeight(swigCPtr, this, _height);
  }

  public int _getFontHeight() {
    return MyoushuJNI.Widget__getFontHeight(swigCPtr, this);
  }

  public void _setTextAlign(Align _align) {
    MyoushuJNI.Widget__setTextAlign(swigCPtr, this, Align.getCPtr(_align), _align);
  }

  public Align _getTextAlign() {
    return new Align(MyoushuJNI.Widget__getTextAlign(swigCPtr, this), true);
  }

  public void _setTextColour(Colour _colour) {
    MyoushuJNI.Widget__setTextColour(swigCPtr, this, Colour.getCPtr(_colour), _colour);
  }

  public Colour _getTextColour() {
    return new Colour(MyoushuJNI.Widget__getTextColour(swigCPtr, this), false);
  }

  public SWIGTYPE_p_MyGUI__ILayerItem getLayerItemByPoint(int _left, int _top) {
    long cPtr = MyoushuJNI.Widget_getLayerItemByPoint(swigCPtr, this, _left, _top);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__ILayerItem(cPtr, false);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getLayerItemCoord() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.Widget_getLayerItemCoord(swigCPtr, this), false);
  }

  public void setCaptionWithNewLine(String _value) {
    MyoushuJNI.Widget_setCaptionWithNewLine(swigCPtr, this, _value);
  }

  public void _initialise(WidgetStyle _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, WidgetSkinInfo _info, Widget _parent, ICroppedRectangle _croppedParent, IWidgetCreator _creator, String _name) {
    MyoushuJNI.Widget__initialise(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, WidgetSkinInfo.getCPtr(_info), _info, Widget.getCPtr(_parent), _parent, ICroppedRectangle.getCPtr(_croppedParent), _croppedParent, IWidgetCreator.getCPtr(_creator), _creator, _name);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord) {
    MyoushuJNI.Widget_setPosition__SWIG_2(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord));
  }

  public void setPosition(int _left, int _top, int _width, int _height) {
    MyoushuJNI.Widget_setPosition__SWIG_3(swigCPtr, this, _left, _top, _width, _height);
  }

  public void enableToolTip(boolean _enable) {
    MyoushuJNI.Widget_enableToolTip(swigCPtr, this, _enable);
  }

  public void setInheritsPeek(boolean _inherits) {
    MyoushuJNI.Widget_setInheritsPeek(swigCPtr, this, _inherits);
  }

  public boolean isInheritsPeek() {
    return MyoushuJNI.Widget_isInheritsPeek(swigCPtr, this);
  }

  public void setMaskPeek(String _filename) {
    MyoushuJNI.Widget_setMaskPeek(swigCPtr, this, _filename);
  }

  public SWIGTYPE_p_MyGUI__types__TCoordT_int_t getTextCoord() {
    return new SWIGTYPE_p_MyGUI__types__TCoordT_int_t(MyoushuJNI.Widget_getTextCoord(swigCPtr, this), true);
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t getTextSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.Widget_getTextSize(swigCPtr, this), true);
  }

  public void setColour(Colour _colour) {
    MyoushuJNI.Widget_setColour(swigCPtr, this, Colour.getCPtr(_colour), _colour);
  }

  public Colour getColour() {
    return new Colour(MyoushuJNI.Widget_getColour(swigCPtr, this), false);
  }

  public void setFontName(String _font) {
    MyoushuJNI.Widget_setFontName(swigCPtr, this, _font);
  }

  public String getFontName() {
    return MyoushuJNI.Widget_getFontName(swigCPtr, this);
  }

  public void setFontHeight(int _height) {
    MyoushuJNI.Widget_setFontHeight(swigCPtr, this, _height);
  }

  public int getFontHeight() {
    return MyoushuJNI.Widget_getFontHeight(swigCPtr, this);
  }

  public void setTextAlign(Align _align) {
    MyoushuJNI.Widget_setTextAlign(swigCPtr, this, Align.getCPtr(_align), _align);
  }

  public Align getTextAlign() {
    return new Align(MyoushuJNI.Widget_getTextAlign(swigCPtr, this), true);
  }

  public void setTextColour(Colour _colour) {
    MyoushuJNI.Widget_setTextColour(swigCPtr, this, Colour.getCPtr(_colour), _colour);
  }

  public Colour getTextColour() {
    return new Colour(MyoushuJNI.Widget_getTextColour(swigCPtr, this), false);
  }

}

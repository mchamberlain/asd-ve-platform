/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Edit extends StaticText {
  private long swigCPtr;

  public Edit(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGEditUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Edit obj) {
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

  public Edit() {
    this(MyoushuJNI.new_Edit(), true);
  }

  public void setTextIntervalColour(long _start, long _count, Colour _colour) {
    MyoushuJNI.Edit_setTextIntervalColour(swigCPtr, this, _start, _count, Colour.getCPtr(_colour), _colour);
  }

  public long getTextSelectionStart() {
    return MyoushuJNI.Edit_getTextSelectionStart(swigCPtr, this);
  }

  public long getTextSelectionEnd() {
    return MyoushuJNI.Edit_getTextSelectionEnd(swigCPtr, this);
  }

  public long getTextSelectionLength() {
    return MyoushuJNI.Edit_getTextSelectionLength(swigCPtr, this);
  }

  public UString getTextInterval(long _start, long _count) {
    return new UString(MyoushuJNI.Edit_getTextInterval(swigCPtr, this, _start, _count), true);
  }

  public void setTextSelection(long _start, long _end) {
    MyoushuJNI.Edit_setTextSelection(swigCPtr, this, _start, _end);
  }

  public void deleteTextSelection() {
    MyoushuJNI.Edit_deleteTextSelection(swigCPtr, this);
  }

  public UString getTextSelection() {
    return new UString(MyoushuJNI.Edit_getTextSelection(swigCPtr, this), true);
  }

  public boolean isTextSelection() {
    return MyoushuJNI.Edit_isTextSelection(swigCPtr, this);
  }

  public void setTextSelectionColour(Colour _value) {
    MyoushuJNI.Edit_setTextSelectionColour(swigCPtr, this, Colour.getCPtr(_value), _value);
  }

  public void setTextCursor(long _index) {
    MyoushuJNI.Edit_setTextCursor(swigCPtr, this, _index);
  }

  public long getTextCursor() {
    return MyoushuJNI.Edit_getTextCursor(swigCPtr, this);
  }

  public void setCaption(UString _value) {
    MyoushuJNI.Edit_setCaption(swigCPtr, this, UString.getCPtr(_value), _value);
  }

  public UString getCaption() {
    return new UString(MyoushuJNI.Edit_getCaption(swigCPtr, this), false);
  }

  public void setOnlyText(UString _value) {
    MyoushuJNI.Edit_setOnlyText(swigCPtr, this, UString.getCPtr(_value), _value);
  }

  public UString getOnlyText() {
    return new UString(MyoushuJNI.Edit_getOnlyText(swigCPtr, this), true);
  }

  public long getTextLength() {
    return MyoushuJNI.Edit_getTextLength(swigCPtr, this);
  }

  public void setOverflowToTheLeft(boolean _value) {
    MyoushuJNI.Edit_setOverflowToTheLeft(swigCPtr, this, _value);
  }

  public boolean getOverflowToTheLeft() {
    return MyoushuJNI.Edit_getOverflowToTheLeft(swigCPtr, this);
  }

  public void setMaxTextLength(long _value) {
    MyoushuJNI.Edit_setMaxTextLength(swigCPtr, this, _value);
  }

  public long getMaxTextLength() {
    return MyoushuJNI.Edit_getMaxTextLength(swigCPtr, this);
  }

  public void insertText(UString _text, long _index) {
    MyoushuJNI.Edit_insertText__SWIG_0(swigCPtr, this, UString.getCPtr(_text), _text, _index);
  }

  public void insertText(UString _text) {
    MyoushuJNI.Edit_insertText__SWIG_1(swigCPtr, this, UString.getCPtr(_text), _text);
  }

  public void addText(UString _text) {
    MyoushuJNI.Edit_addText(swigCPtr, this, UString.getCPtr(_text), _text);
  }

  public void eraseText(long _start, long _count) {
    MyoushuJNI.Edit_eraseText__SWIG_0(swigCPtr, this, _start, _count);
  }

  public void eraseText(long _start) {
    MyoushuJNI.Edit_eraseText__SWIG_1(swigCPtr, this, _start);
  }

  public void setEditReadOnly(boolean _value) {
    MyoushuJNI.Edit_setEditReadOnly(swigCPtr, this, _value);
  }

  public boolean getEditReadOnly() {
    return MyoushuJNI.Edit_getEditReadOnly(swigCPtr, this);
  }

  public void setEditPassword(boolean _value) {
    MyoushuJNI.Edit_setEditPassword(swigCPtr, this, _value);
  }

  public boolean getEditPassword() {
    return MyoushuJNI.Edit_getEditPassword(swigCPtr, this);
  }

  public void setEditMultiLine(boolean _value) {
    MyoushuJNI.Edit_setEditMultiLine(swigCPtr, this, _value);
  }

  public boolean getEditMultiLine() {
    return MyoushuJNI.Edit_getEditMultiLine(swigCPtr, this);
  }

  public void setEditStatic(boolean _value) {
    MyoushuJNI.Edit_setEditStatic(swigCPtr, this, _value);
  }

  public boolean getEditStatic() {
    return MyoushuJNI.Edit_getEditStatic(swigCPtr, this);
  }

  public void setPasswordChar(long _value) {
    MyoushuJNI.Edit_setPasswordChar__SWIG_0(swigCPtr, this, _value);
  }

  public void setPasswordChar(UString _char) {
    MyoushuJNI.Edit_setPasswordChar__SWIG_1(swigCPtr, this, UString.getCPtr(_char), _char);
  }

  public long getPasswordChar() {
    return MyoushuJNI.Edit_getPasswordChar(swigCPtr, this);
  }

  public void setEditWordWrap(boolean _value) {
    MyoushuJNI.Edit_setEditWordWrap(swigCPtr, this, _value);
  }

  public boolean getEditWordWrap() {
    return MyoushuJNI.Edit_getEditWordWrap(swigCPtr, this);
  }

  public void setTabPrinting(boolean _value) {
    MyoushuJNI.Edit_setTabPrinting(swigCPtr, this, _value);
  }

  public boolean getTabPrinting() {
    return MyoushuJNI.Edit_getTabPrinting(swigCPtr, this);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TPointT_int_t _value) {
    MyoushuJNI.Edit_setPosition__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TPointT_int_t.getCPtr(_value));
  }

  public void setSize(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _value) {
    MyoushuJNI.Edit_setSize__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_value));
  }

  public void setCoord(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _value) {
    MyoushuJNI.Edit_setCoord__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_value));
  }

  public void setPosition(int _left, int _top) {
    MyoushuJNI.Edit_setPosition__SWIG_1(swigCPtr, this, _left, _top);
  }

  public void setSize(int _width, int _height) {
    MyoushuJNI.Edit_setSize__SWIG_1(swigCPtr, this, _width, _height);
  }

  public void setCoord(int _left, int _top, int _width, int _height) {
    MyoushuJNI.Edit_setCoord__SWIG_1(swigCPtr, this, _left, _top, _width, _height);
  }

  public void setVisibleVScroll(boolean _value) {
    MyoushuJNI.Edit_setVisibleVScroll(swigCPtr, this, _value);
  }

  public boolean isVisibleVScroll() {
    return MyoushuJNI.Edit_isVisibleVScroll(swigCPtr, this);
  }

  public void setVisibleHScroll(boolean _value) {
    MyoushuJNI.Edit_setVisibleHScroll(swigCPtr, this, _value);
  }

  public boolean isVisibleHScroll() {
    return MyoushuJNI.Edit_isVisibleHScroll(swigCPtr, this);
  }

  public void setFontName(String _value) {
    MyoushuJNI.Edit_setFontName(swigCPtr, this, _value);
  }

  public void setFontHeight(int _value) {
    MyoushuJNI.Edit_setFontHeight(swigCPtr, this, _value);
  }

  public void setTextAlign(Align _value) {
    MyoushuJNI.Edit_setTextAlign(swigCPtr, this, Align.getCPtr(_value), _value);
  }

  public void setProperty(String _key, String _value) {
    MyoushuJNI.Edit_setProperty(swigCPtr, this, _key, _value);
  }

  public void setEventEditSelectAccept(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t value) {
    MyoushuJNI.Edit_eventEditSelectAccept_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t getEventEditSelectAccept() {
    long cPtr = MyoushuJNI.Edit_eventEditSelectAccept_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t(cPtr, false);
  }

  public void setEventEditTextChange(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t value) {
    MyoushuJNI.Edit_eventEditTextChange_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t getEventEditTextChange() {
    long cPtr = MyoushuJNI.Edit_eventEditTextChange_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate1T_MyGUI__WidgetPtr_t_delegates__CDelegate1T_MyGUI__EditPtr_t_t(cPtr, false);
  }

  public void _initialise(WidgetStyle _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, WidgetSkinInfo _info, Widget _parent, ICroppedRectangle _croppedParent, IWidgetCreator _creator, String _name) {
    MyoushuJNI.Edit__initialise(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, WidgetSkinInfo.getCPtr(_info), _info, Widget.getCPtr(_parent), _parent, ICroppedRectangle.getCPtr(_croppedParent), _croppedParent, IWidgetCreator.getCPtr(_creator), _creator, _name);
  }

  public void showVScroll(boolean _visible) {
    MyoushuJNI.Edit_showVScroll(swigCPtr, this, _visible);
  }

  public boolean isShowVScroll() {
    return MyoushuJNI.Edit_isShowVScroll(swigCPtr, this);
  }

  public void showHScroll(boolean _visible) {
    MyoushuJNI.Edit_showHScroll(swigCPtr, this, _visible);
  }

  public boolean isShowHScroll() {
    return MyoushuJNI.Edit_isShowHScroll(swigCPtr, this);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord) {
    MyoushuJNI.Edit_setPosition__SWIG_2(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord));
  }

  public void setPosition(int _left, int _top, int _width, int _height) {
    MyoushuJNI.Edit_setPosition__SWIG_3(swigCPtr, this, _left, _top, _width, _height);
  }

  public void setTextColour(Colour _colour) {
    MyoushuJNI.Edit_setTextColour__SWIG_0(swigCPtr, this, Colour.getCPtr(_colour), _colour);
  }

  public void setTextColour(long _start, long _count, Colour _colour) {
    MyoushuJNI.Edit_setTextColour__SWIG_1(swigCPtr, this, _start, _count, Colour.getCPtr(_colour), _colour);
  }

  public UString getText(long _start, long _count) {
    return new UString(MyoushuJNI.Edit_getText(swigCPtr, this, _start, _count), true);
  }

  public void setTextSelect(long _start, long _end) {
    MyoushuJNI.Edit_setTextSelect(swigCPtr, this, _start, _end);
  }

  public void deleteTextSelect() {
    MyoushuJNI.Edit_deleteTextSelect(swigCPtr, this);
  }

  public UString getSelectedText() {
    return new UString(MyoushuJNI.Edit_getSelectedText(swigCPtr, this), true);
  }

  public boolean isTextSelect() {
    return MyoushuJNI.Edit_isTextSelect(swigCPtr, this);
  }

  public void setTextSelectColour(Colour _colour) {
    MyoushuJNI.Edit_setTextSelectColour(swigCPtr, this, Colour.getCPtr(_colour), _colour);
  }

}

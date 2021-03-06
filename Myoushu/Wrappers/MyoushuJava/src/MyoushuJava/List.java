/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class List extends Widget {
  private long swigCPtr;

  public List(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGListUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(List obj) {
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

  public List() {
    this(MyoushuJNI.new_List(), true);
  }

  public long getItemCount() {
    return MyoushuJNI.List_getItemCount(swigCPtr, this);
  }

  public void insertItemAt(long _index, UString _name, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.List_insertItemAt__SWIG_0(swigCPtr, this, _index, UString.getCPtr(_name), _name, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void insertItemAt(long _index, UString _name) {
    MyoushuJNI.List_insertItemAt__SWIG_1(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public void addItem(UString _name, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.List_addItem__SWIG_0(swigCPtr, this, UString.getCPtr(_name), _name, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void addItem(UString _name) {
    MyoushuJNI.List_addItem__SWIG_1(swigCPtr, this, UString.getCPtr(_name), _name);
  }

  public void removeItemAt(long _index) {
    MyoushuJNI.List_removeItemAt(swigCPtr, this, _index);
  }

  public void removeAllItems() {
    MyoushuJNI.List_removeAllItems(swigCPtr, this);
  }

  public void swapItemsAt(long _index1, long _index2) {
    MyoushuJNI.List_swapItemsAt(swigCPtr, this, _index1, _index2);
  }

  public long findItemIndexWith(UString _name) {
    return MyoushuJNI.List_findItemIndexWith(swigCPtr, this, UString.getCPtr(_name), _name);
  }

  public long getIndexSelected() {
    return MyoushuJNI.List_getIndexSelected(swigCPtr, this);
  }

  public void setIndexSelected(long _index) {
    MyoushuJNI.List_setIndexSelected(swigCPtr, this, _index);
  }

  public void clearIndexSelected() {
    MyoushuJNI.List_clearIndexSelected(swigCPtr, this);
  }

  public void setItemDataAt(long _index, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.List_setItemDataAt(swigCPtr, this, _index, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void clearItemDataAt(long _index) {
    MyoushuJNI.List_clearItemDataAt(swigCPtr, this, _index);
  }

  public void setItemNameAt(long _index, UString _name) {
    MyoushuJNI.List_setItemNameAt(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public UString getItemNameAt(long _index) {
    return new UString(MyoushuJNI.List_getItemNameAt(swigCPtr, this, _index), false);
  }

  public void beginToItemAt(long _index) {
    MyoushuJNI.List_beginToItemAt(swigCPtr, this, _index);
  }

  public void beginToItemFirst() {
    MyoushuJNI.List_beginToItemFirst(swigCPtr, this);
  }

  public void beginToItemLast() {
    MyoushuJNI.List_beginToItemLast(swigCPtr, this);
  }

  public void beginToItemSelected() {
    MyoushuJNI.List_beginToItemSelected(swigCPtr, this);
  }

  public boolean isItemVisibleAt(long _index, boolean _fill) {
    return MyoushuJNI.List_isItemVisibleAt__SWIG_0(swigCPtr, this, _index, _fill);
  }

  public boolean isItemVisibleAt(long _index) {
    return MyoushuJNI.List_isItemVisibleAt__SWIG_1(swigCPtr, this, _index);
  }

  public boolean isItemSelectedVisible(boolean _fill) {
    return MyoushuJNI.List_isItemSelectedVisible__SWIG_0(swigCPtr, this, _fill);
  }

  public boolean isItemSelectedVisible() {
    return MyoushuJNI.List_isItemSelectedVisible__SWIG_1(swigCPtr, this);
  }

  public void setScrollVisible(boolean _visible) {
    MyoushuJNI.List_setScrollVisible(swigCPtr, this, _visible);
  }

  public void setScrollPosition(long _position) {
    MyoushuJNI.List_setScrollPosition(swigCPtr, this, _position);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TPointT_int_t _value) {
    MyoushuJNI.List_setPosition__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TPointT_int_t.getCPtr(_value));
  }

  public void setSize(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _value) {
    MyoushuJNI.List_setSize__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_value));
  }

  public void setCoord(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _value) {
    MyoushuJNI.List_setCoord__SWIG_0(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_value));
  }

  public void setPosition(int _left, int _top) {
    MyoushuJNI.List_setPosition__SWIG_1(swigCPtr, this, _left, _top);
  }

  public void setSize(int _width, int _height) {
    MyoushuJNI.List_setSize__SWIG_1(swigCPtr, this, _width, _height);
  }

  public void setCoord(int _left, int _top, int _width, int _height) {
    MyoushuJNI.List_setCoord__SWIG_1(swigCPtr, this, _left, _top, _width, _height);
  }

  public long getOptimalHeight() {
    return MyoushuJNI.List_getOptimalHeight(swigCPtr, this);
  }

  public void setProperty(String _key, String _value) {
    MyoushuJNI.List_setProperty(swigCPtr, this, _key, _value);
  }

  public void setEventListSelectAccept(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t value) {
    MyoushuJNI.List_eventListSelectAccept_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t getEventListSelectAccept() {
    long cPtr = MyoushuJNI.List_eventListSelectAccept_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t(cPtr, false);
  }

  public void setEventListChangePosition(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t value) {
    MyoushuJNI.List_eventListChangePosition_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t getEventListChangePosition() {
    long cPtr = MyoushuJNI.List_eventListChangePosition_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t(cPtr, false);
  }

  public void setEventListMouseItemActivate(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t value) {
    MyoushuJNI.List_eventListMouseItemActivate_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t getEventListMouseItemActivate() {
    long cPtr = MyoushuJNI.List_eventListMouseItemActivate_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t(cPtr, false);
  }

  public void setEventListMouseItemFocus(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t value) {
    MyoushuJNI.List_eventListMouseItemFocus_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t getEventListMouseItemFocus() {
    long cPtr = MyoushuJNI.List_eventListMouseItemFocus_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t(cPtr, false);
  }

  public void setEventListChangeScroll(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t value) {
    MyoushuJNI.List_eventListChangeScroll_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t getEventListChangeScroll() {
    long cPtr = MyoushuJNI.List_eventListChangeScroll_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__ListPtr_size_t_t_t(cPtr, false);
  }

  public void _checkAlign() {
    MyoushuJNI.List__checkAlign(swigCPtr, this);
  }

  public void _setItemFocus(long _position, boolean _focus) {
    MyoushuJNI.List__setItemFocus(swigCPtr, this, _position, _focus);
  }

  public void _sendEventChangeScroll(long _position) {
    MyoushuJNI.List__sendEventChangeScroll(swigCPtr, this, _position);
  }

  public void _initialise(WidgetStyle _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, WidgetSkinInfo _info, Widget _parent, ICroppedRectangle _croppedParent, IWidgetCreator _creator, String _name) {
    MyoushuJNI.List__initialise(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, WidgetSkinInfo.getCPtr(_info), _info, Widget.getCPtr(_parent), _parent, ICroppedRectangle.getCPtr(_croppedParent), _croppedParent, IWidgetCreator.getCPtr(_creator), _creator, _name);
  }

  public void setPosition(SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord) {
    MyoushuJNI.List_setPosition__SWIG_2(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord));
  }

  public void setPosition(int _left, int _top, int _width, int _height) {
    MyoushuJNI.List_setPosition__SWIG_3(swigCPtr, this, _left, _top, _width, _height);
  }

  public long getItemIndexSelected() {
    return MyoushuJNI.List_getItemIndexSelected(swigCPtr, this);
  }

  public void setItemSelectedAt(long _index) {
    MyoushuJNI.List_setItemSelectedAt(swigCPtr, this, _index);
  }

  public void clearItemSelected() {
    MyoushuJNI.List_clearItemSelected(swigCPtr, this);
  }

  public void insertItem(long _index, UString _item) {
    MyoushuJNI.List_insertItem(swigCPtr, this, _index, UString.getCPtr(_item), _item);
  }

  public void setItem(long _index, UString _item) {
    MyoushuJNI.List_setItem(swigCPtr, this, _index, UString.getCPtr(_item), _item);
  }

  public UString getItem(long _index) {
    return new UString(MyoushuJNI.List_getItem(swigCPtr, this, _index), false);
  }

  public void deleteItem(long _index) {
    MyoushuJNI.List_deleteItem(swigCPtr, this, _index);
  }

  public void deleteAllItems() {
    MyoushuJNI.List_deleteAllItems(swigCPtr, this);
  }

  public long findItem(UString _item) {
    return MyoushuJNI.List_findItem(swigCPtr, this, UString.getCPtr(_item), _item);
  }

  public long getItemSelect() {
    return MyoushuJNI.List_getItemSelect(swigCPtr, this);
  }

  public void resetItemSelect() {
    MyoushuJNI.List_resetItemSelect(swigCPtr, this);
  }

  public void setItemSelect(long _index) {
    MyoushuJNI.List_setItemSelect(swigCPtr, this, _index);
  }

  public void beginToIndex(long _index) {
    MyoushuJNI.List_beginToIndex(swigCPtr, this, _index);
  }

  public void beginToStart() {
    MyoushuJNI.List_beginToStart(swigCPtr, this);
  }

  public void beginToEnd() {
    MyoushuJNI.List_beginToEnd(swigCPtr, this);
  }

  public void beginToSelect() {
    MyoushuJNI.List_beginToSelect(swigCPtr, this);
  }

  public boolean isItemVisible(long _index, boolean _fill) {
    return MyoushuJNI.List_isItemVisible__SWIG_0(swigCPtr, this, _index, _fill);
  }

  public boolean isItemVisible(long _index) {
    return MyoushuJNI.List_isItemVisible__SWIG_1(swigCPtr, this, _index);
  }

  public boolean isItemSelectVisible(boolean _fill) {
    return MyoushuJNI.List_isItemSelectVisible__SWIG_0(swigCPtr, this, _fill);
  }

  public boolean isItemSelectVisible() {
    return MyoushuJNI.List_isItemSelectVisible__SWIG_1(swigCPtr, this);
  }

}

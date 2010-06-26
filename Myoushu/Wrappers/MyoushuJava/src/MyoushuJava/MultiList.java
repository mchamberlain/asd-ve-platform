/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class MultiList extends Widget {
  private long swigCPtr;

  public MultiList(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGMultiListUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MultiList obj) {
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

  public MultiList() {
    this(MyoushuJNI.new_MultiList(), true);
  }

  public long getColumnCount() {
    return MyoushuJNI.MultiList_getColumnCount(swigCPtr, this);
  }

  public void insertColumnAt(long _column, UString _name, int _width, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_insertColumnAt__SWIG_0(swigCPtr, this, _column, UString.getCPtr(_name), _name, _width, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void insertColumnAt(long _column, UString _name, int _width) {
    MyoushuJNI.MultiList_insertColumnAt__SWIG_1(swigCPtr, this, _column, UString.getCPtr(_name), _name, _width);
  }

  public void addColumn(UString _name, int _width, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_addColumn__SWIG_0(swigCPtr, this, UString.getCPtr(_name), _name, _width, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void addColumn(UString _name, int _width) {
    MyoushuJNI.MultiList_addColumn__SWIG_1(swigCPtr, this, UString.getCPtr(_name), _name, _width);
  }

  public void removeColumnAt(long _column) {
    MyoushuJNI.MultiList_removeColumnAt(swigCPtr, this, _column);
  }

  public void removeAllColumns() {
    MyoushuJNI.MultiList_removeAllColumns(swigCPtr, this);
  }

  public void setColumnNameAt(long _column, UString _name) {
    MyoushuJNI.MultiList_setColumnNameAt(swigCPtr, this, _column, UString.getCPtr(_name), _name);
  }

  public void setColumnWidthAt(long _column, int _width) {
    MyoushuJNI.MultiList_setColumnWidthAt(swigCPtr, this, _column, _width);
  }

  public UString getColumnNameAt(long _column) {
    return new UString(MyoushuJNI.MultiList_getColumnNameAt(swigCPtr, this, _column), false);
  }

  public int getColumnWidthAt(long _column) {
    return MyoushuJNI.MultiList_getColumnWidthAt(swigCPtr, this, _column);
  }

  public void sortByColumn(long _column, boolean _backward) {
    MyoushuJNI.MultiList_sortByColumn__SWIG_0(swigCPtr, this, _column, _backward);
  }

  public void sortByColumn(long _column) {
    MyoushuJNI.MultiList_sortByColumn__SWIG_1(swigCPtr, this, _column);
  }

  public void setColumnDataAt(long _index, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_setColumnDataAt(swigCPtr, this, _index, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void clearColumnDataAt(long _index) {
    MyoushuJNI.MultiList_clearColumnDataAt(swigCPtr, this, _index);
  }

  public long getItemCount() {
    return MyoushuJNI.MultiList_getItemCount(swigCPtr, this);
  }

  public void insertItemAt(long _index, UString _name, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_insertItemAt__SWIG_0(swigCPtr, this, _index, UString.getCPtr(_name), _name, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void insertItemAt(long _index, UString _name) {
    MyoushuJNI.MultiList_insertItemAt__SWIG_1(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public void addItem(UString _name, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_addItem__SWIG_0(swigCPtr, this, UString.getCPtr(_name), _name, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void addItem(UString _name) {
    MyoushuJNI.MultiList_addItem__SWIG_1(swigCPtr, this, UString.getCPtr(_name), _name);
  }

  public void removeItemAt(long _index) {
    MyoushuJNI.MultiList_removeItemAt(swigCPtr, this, _index);
  }

  public void removeAllItems() {
    MyoushuJNI.MultiList_removeAllItems(swigCPtr, this);
  }

  public void swapItemsAt(long _index1, long _index2) {
    MyoushuJNI.MultiList_swapItemsAt(swigCPtr, this, _index1, _index2);
  }

  public void setItemNameAt(long _index, UString _name) {
    MyoushuJNI.MultiList_setItemNameAt(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public UString getItemNameAt(long _index) {
    return new UString(MyoushuJNI.MultiList_getItemNameAt(swigCPtr, this, _index), false);
  }

  public long getIndexSelected() {
    return MyoushuJNI.MultiList_getIndexSelected(swigCPtr, this);
  }

  public void setIndexSelected(long _index) {
    MyoushuJNI.MultiList_setIndexSelected(swigCPtr, this, _index);
  }

  public void clearIndexSelected() {
    MyoushuJNI.MultiList_clearIndexSelected(swigCPtr, this);
  }

  public void setItemDataAt(long _index, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_setItemDataAt(swigCPtr, this, _index, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void clearItemDataAt(long _index) {
    MyoushuJNI.MultiList_clearItemDataAt(swigCPtr, this, _index);
  }

  public void setSubItemNameAt(long _column, long _index, UString _name) {
    MyoushuJNI.MultiList_setSubItemNameAt(swigCPtr, this, _column, _index, UString.getCPtr(_name), _name);
  }

  public UString getSubItemNameAt(long _column, long _index) {
    return new UString(MyoushuJNI.MultiList_getSubItemNameAt(swigCPtr, this, _column, _index), false);
  }

  public long findSubItemWith(long _column, UString _name) {
    return MyoushuJNI.MultiList_findSubItemWith(swigCPtr, this, _column, UString.getCPtr(_name), _name);
  }

  public void setSubItemDataAt(long _column, long _index, SWIGTYPE_p_Ogre__Any _data) {
    MyoushuJNI.MultiList_setSubItemDataAt(swigCPtr, this, _column, _index, SWIGTYPE_p_Ogre__Any.getCPtr(_data));
  }

  public void clearSubItemDataAt(long _column, long _index) {
    MyoushuJNI.MultiList_clearSubItemDataAt(swigCPtr, this, _column, _index);
  }

  public void _initialise(WidgetStyle _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t _coord, Align _align, WidgetSkinInfo _info, Widget _parent, ICroppedRectangle _croppedParent, IWidgetCreator _creator, String _name) {
    MyoushuJNI.MultiList__initialise(swigCPtr, this, WidgetStyle.getCPtr(_style), _style, SWIGTYPE_p_MyGUI__types__TCoordT_int_t.getCPtr(_coord), Align.getCPtr(_align), _align, WidgetSkinInfo.getCPtr(_info), _info, Widget.getCPtr(_parent), _parent, ICroppedRectangle.getCPtr(_croppedParent), _croppedParent, IWidgetCreator.getCPtr(_creator), _creator, _name);
  }

  public void setEventListSelectAccept(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t value) {
    MyoushuJNI.MultiList_eventListSelectAccept_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t getEventListSelectAccept() {
    long cPtr = MyoushuJNI.MultiList_eventListSelectAccept_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t(cPtr, false);
  }

  public void setEventListChangePosition(SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t value) {
    MyoushuJNI.MultiList_eventListChangePosition_set(swigCPtr, this, SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t.getCPtr(value));
  }

  public SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t getEventListChangePosition() {
    long cPtr = MyoushuJNI.MultiList_eventListChangePosition_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__EventPairT_delegates__CDelegate2T_MyGUI__WidgetPtr_size_t_t_delegates__CDelegate2T_MyGUI__MultiListPtr_size_t_t_t(cPtr, false);
  }

  public void setRequestOperatorLess(SWIGTYPE_p_delegates__CDelegate5T_MyGUI__MultiListPtr_size_t_MyGUI__UString_const_R_MyGUI__UString_const_R_bool_R_t value) {
    MyoushuJNI.MultiList_requestOperatorLess_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate5T_MyGUI__MultiListPtr_size_t_MyGUI__UString_const_R_MyGUI__UString_const_R_bool_R_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate5T_MyGUI__MultiListPtr_size_t_MyGUI__UString_const_R_MyGUI__UString_const_R_bool_R_t getRequestOperatorLess() {
    return new SWIGTYPE_p_delegates__CDelegate5T_MyGUI__MultiListPtr_size_t_MyGUI__UString_const_R_MyGUI__UString_const_R_bool_R_t(MyoushuJNI.MultiList_requestOperatorLess_get(swigCPtr, this), true);
  }

  public long getItemIndexSelected() {
    return MyoushuJNI.MultiList_getItemIndexSelected(swigCPtr, this);
  }

  public void setItemSelectedAt(long _index) {
    MyoushuJNI.MultiList_setItemSelectedAt(swigCPtr, this, _index);
  }

  public void clearItemSelected() {
    MyoushuJNI.MultiList_clearItemSelected(swigCPtr, this);
  }

  public long findItem(long _column, UString _name) {
    return MyoushuJNI.MultiList_findItem(swigCPtr, this, _column, UString.getCPtr(_name), _name);
  }

  public UString getSubItem(long _column, long _index) {
    return new UString(MyoushuJNI.MultiList_getSubItem(swigCPtr, this, _column, _index), false);
  }

  public void setSubItem(long _column, long _index, UString _name) {
    MyoushuJNI.MultiList_setSubItem(swigCPtr, this, _column, _index, UString.getCPtr(_name), _name);
  }

  public void deleteColumn(long _column) {
    MyoushuJNI.MultiList_deleteColumn(swigCPtr, this, _column);
  }

  public void deleteAllColumns() {
    MyoushuJNI.MultiList_deleteAllColumns(swigCPtr, this);
  }

  public int getColumnWidth(long _column) {
    return MyoushuJNI.MultiList_getColumnWidth(swigCPtr, this, _column);
  }

  public UString getColumnName(long _column) {
    return new UString(MyoushuJNI.MultiList_getColumnName(swigCPtr, this, _column), false);
  }

  public void setColumnWidth(long _column, int _width) {
    MyoushuJNI.MultiList_setColumnWidth(swigCPtr, this, _column, _width);
  }

  public void addColumn(int _width, UString _name) {
    MyoushuJNI.MultiList_addColumn__SWIG_2(swigCPtr, this, _width, UString.getCPtr(_name), _name);
  }

  public void setColumnName(long _column, UString _name) {
    MyoushuJNI.MultiList_setColumnName(swigCPtr, this, _column, UString.getCPtr(_name), _name);
  }

  public void insertColumn(long _column, int _width, UString _name) {
    MyoushuJNI.MultiList_insertColumn(swigCPtr, this, _column, _width, UString.getCPtr(_name), _name);
  }

  public long getItemSelect() {
    return MyoushuJNI.MultiList_getItemSelect(swigCPtr, this);
  }

  public void resetItemSelect() {
    MyoushuJNI.MultiList_resetItemSelect(swigCPtr, this);
  }

  public void setItemSelect(long _index) {
    MyoushuJNI.MultiList_setItemSelect(swigCPtr, this, _index);
  }

  public void insertItem(long _index, UString _name) {
    MyoushuJNI.MultiList_insertItem(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public void setItem(long _index, UString _name) {
    MyoushuJNI.MultiList_setItem(swigCPtr, this, _index, UString.getCPtr(_name), _name);
  }

  public UString getItem(long _index) {
    return new UString(MyoushuJNI.MultiList_getItem(swigCPtr, this, _index), false);
  }

  public void deleteItem(long _index) {
    MyoushuJNI.MultiList_deleteItem(swigCPtr, this, _index);
  }

  public void deleteAllItems() {
    MyoushuJNI.MultiList_deleteAllItems(swigCPtr, this);
  }

}

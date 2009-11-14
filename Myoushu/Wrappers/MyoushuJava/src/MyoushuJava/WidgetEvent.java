/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class WidgetEvent {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WidgetEvent(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WidgetEvent obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_WidgetEvent(swigCPtr);
    }
    swigCPtr = 0;
  }

  public void setEventMouseLostFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventMouseLostFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t getEventMouseLostFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventMouseLostFocus_get(swigCPtr, this), true);
  }

  public void setEventMouseSetFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventMouseSetFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t getEventMouseSetFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventMouseSetFocus_get(swigCPtr, this), true);
  }

  public void setEventMouseDrag(SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t value) {
    MyoushuJNI.WidgetEvent_eventMouseDrag_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t getEventMouseDrag() {
    return new SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t(MyoushuJNI.WidgetEvent_eventMouseDrag_get(swigCPtr, this), true);
  }

  public void setEventMouseMove(SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t value) {
    MyoushuJNI.WidgetEvent_eventMouseMove_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t getEventMouseMove() {
    return new SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_int_int_t(MyoushuJNI.WidgetEvent_eventMouseMove_get(swigCPtr, this), true);
  }

  public void setEventMouseWheel(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_int_t value) {
    MyoushuJNI.WidgetEvent_eventMouseWheel_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_int_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_int_t getEventMouseWheel() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_int_t(MyoushuJNI.WidgetEvent_eventMouseWheel_get(swigCPtr, this), true);
  }

  public void setEventMouseButtonPressed(SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t value) {
    MyoushuJNI.WidgetEvent_eventMouseButtonPressed_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t getEventMouseButtonPressed() {
    return new SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t(MyoushuJNI.WidgetEvent_eventMouseButtonPressed_get(swigCPtr, this), true);
  }

  public void setEventMouseButtonReleased(SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t value) {
    MyoushuJNI.WidgetEvent_eventMouseButtonReleased_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t getEventMouseButtonReleased() {
    return new SWIGTYPE_p_delegates__CDelegate4T_MyGUI__WidgetPtr_int_int_MyGUI__MouseButton_t(MyoushuJNI.WidgetEvent_eventMouseButtonReleased_get(swigCPtr, this), true);
  }

  public void setEventMouseButtonClick(SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventMouseButtonClick_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t getEventMouseButtonClick() {
    return new SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventMouseButtonClick_get(swigCPtr, this), true);
  }

  public void setEventMouseButtonDoubleClick(SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventMouseButtonDoubleClick_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t getEventMouseButtonDoubleClick() {
    return new SWIGTYPE_p_delegates__CDelegate1T_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventMouseButtonDoubleClick_get(swigCPtr, this), true);
  }

  public void setEventKeyLostFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventKeyLostFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t getEventKeyLostFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventKeyLostFocus_get(swigCPtr, this), true);
  }

  public void setEventKeySetFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t value) {
    MyoushuJNI.WidgetEvent_eventKeySetFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t getEventKeySetFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_t(MyoushuJNI.WidgetEvent_eventKeySetFocus_get(swigCPtr, this), true);
  }

  public void setEventKeyButtonPressed(SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__KeyCode_MyGUI__Char_t value) {
    MyoushuJNI.WidgetEvent_eventKeyButtonPressed_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__KeyCode_MyGUI__Char_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__KeyCode_MyGUI__Char_t getEventKeyButtonPressed() {
    return new SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__KeyCode_MyGUI__Char_t(MyoushuJNI.WidgetEvent_eventKeyButtonPressed_get(swigCPtr, this), true);
  }

  public void setEventKeyButtonReleased(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__KeyCode_t value) {
    MyoushuJNI.WidgetEvent_eventKeyButtonReleased_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__KeyCode_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__KeyCode_t getEventKeyButtonReleased() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_MyGUI__KeyCode_t(MyoushuJNI.WidgetEvent_eventKeyButtonReleased_get(swigCPtr, this), true);
  }

  public void setEventRootMouseChangeFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t value) {
    MyoushuJNI.WidgetEvent_eventRootMouseChangeFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t getEventRootMouseChangeFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t(MyoushuJNI.WidgetEvent_eventRootMouseChangeFocus_get(swigCPtr, this), true);
  }

  public void setEventRootKeyChangeFocus(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t value) {
    MyoushuJNI.WidgetEvent_eventRootKeyChangeFocus_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t getEventRootKeyChangeFocus() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_bool_t(MyoushuJNI.WidgetEvent_eventRootKeyChangeFocus_get(swigCPtr, this), true);
  }

  public void setEventToolTip(SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_ToolTipInfo_const_R_t value) {
    MyoushuJNI.WidgetEvent_eventToolTip_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_ToolTipInfo_const_R_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_ToolTipInfo_const_R_t getEventToolTip() {
    return new SWIGTYPE_p_delegates__CDelegate2T_MyGUI__WidgetPtr_ToolTipInfo_const_R_t(MyoushuJNI.WidgetEvent_eventToolTip_get(swigCPtr, this), true);
  }

  public void setEventActionInfo(SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_std__string_const_R_std__string_const_R_t value) {
    MyoushuJNI.WidgetEvent_eventActionInfo_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_std__string_const_R_std__string_const_R_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_std__string_const_R_std__string_const_R_t getEventActionInfo() {
    return new SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_std__string_const_R_std__string_const_R_t(MyoushuJNI.WidgetEvent_eventActionInfo_get(swigCPtr, this), true);
  }

  public void set_requestGetContainer(SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_R_size_t_R_t value) {
    MyoushuJNI.WidgetEvent__requestGetContainer_set(swigCPtr, this, SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_R_size_t_R_t.getCPtr(value));
  }

  public SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_R_size_t_R_t get_requestGetContainer() {
    return new SWIGTYPE_p_delegates__CDelegate3T_MyGUI__WidgetPtr_MyGUI__WidgetPtr_R_size_t_R_t(MyoushuJNI.WidgetEvent__requestGetContainer_get(swigCPtr, this), true);
  }

}

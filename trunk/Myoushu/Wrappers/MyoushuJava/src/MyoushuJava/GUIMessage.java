/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GUIMessage extends Message {
  private long swigCPtr;

  public GUIMessage(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGUIMessageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GUIMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GUIMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GUIMessage() {
    this(MyoushuJNI.new_GUIMessage(), true);
  }

  public String getClassName() {
    return MyoushuJNI.GUIMessage_getClassName(swigCPtr, this);
  }

  public GUIMessage.GUIMessageType getMessageType() {
    return GUIMessage.GUIMessageType.swigToEnum(MyoushuJNI.GUIMessage_getMessageType(swigCPtr, this));
  }

  public void setMessageType(GUIMessage.GUIMessageType messageType) {
    MyoushuJNI.GUIMessage_setMessageType(swigCPtr, this, messageType.swigValue());
  }

  public boolean isVisible() {
    return MyoushuJNI.GUIMessage_isVisible(swigCPtr, this);
  }

  public void setVisible(boolean visible) {
    MyoushuJNI.GUIMessage_setVisible(swigCPtr, this, visible);
  }

  public Vector2 getPosition() {
    return new Vector2(MyoushuJNI.GUIMessage_getPosition(swigCPtr, this), true);
  }

  public void setPosition(Vector2 position) {
    MyoushuJNI.GUIMessage_setPosition(swigCPtr, this, Vector2.getCPtr(position), position);
  }

  public Vector2 getSize() {
    return new Vector2(MyoushuJNI.GUIMessage_getSize(swigCPtr, this), true);
  }

  public void setSize(Vector2 size) {
    MyoushuJNI.GUIMessage_setSize(swigCPtr, this, Vector2.getCPtr(size), size);
  }

  public boolean getRelative() {
    return MyoushuJNI.GUIMessage_getRelative(swigCPtr, this);
  }

  public void setRelative(boolean relative) {
    MyoushuJNI.GUIMessage_setRelative(swigCPtr, this, relative);
  }

  public String getWidgetType() {
    return MyoushuJNI.GUIMessage_getWidgetType(swigCPtr, this);
  }

  public void setWidgetType(String widgetType) {
    MyoushuJNI.GUIMessage_setWidgetType(swigCPtr, this, widgetType);
  }

  public String getWidgetName() {
    return MyoushuJNI.GUIMessage_getWidgetName(swigCPtr, this);
  }

  public void setWidgetName(String widgetName) {
    MyoushuJNI.GUIMessage_setWidgetName(swigCPtr, this, widgetName);
  }

  public String getMessage() {
    return MyoushuJNI.GUIMessage_getMessage(swigCPtr, this);
  }

  public void setMessage(String message) {
    MyoushuJNI.GUIMessage_setMessage(swigCPtr, this, message);
  }

  public String getResourceGroup() {
    return MyoushuJNI.GUIMessage_getResourceGroup(swigCPtr, this);
  }

  public void setResourceGroup(String resourceGroup) {
    MyoushuJNI.GUIMessage_setResourceGroup(swigCPtr, this, resourceGroup);
  }

  public void clear() {
    MyoushuJNI.GUIMessage_clear(swigCPtr, this);
  }

  public enum GUIMessageType {
    GM_UNKNOWN(MyoushuJNI.GUIMessage_GM_UNKNOWN_get()),
    GM_TOGGLE_GUI_VISIBLE,
    GM_TOGGLE_CURSOR,
    GM_LOAD_LAYOUT,
    GM_CHANGE_SKIN,
    GM_TOGGLE_WIDGET_VISIBLE,
    GM_DESTROY,
    GM_CREATE,
    GM_SET_MOUSE_FOCUS,
    GM_SET_KEY_FOCUS,
    GM_TRANSLATE_WIDGETS,
    GM_TRANSLATE_WIDGET;

    public final int swigValue() {
      return swigValue;
    }

    public static GUIMessageType swigToEnum(int swigValue) {
      GUIMessageType[] swigValues = GUIMessageType.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (GUIMessageType swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + GUIMessageType.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private GUIMessageType() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private GUIMessageType(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private GUIMessageType(GUIMessageType swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

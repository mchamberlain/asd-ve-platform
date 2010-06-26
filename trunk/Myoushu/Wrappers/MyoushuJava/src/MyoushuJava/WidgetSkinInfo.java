/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class WidgetSkinInfo {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WidgetSkinInfo(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WidgetSkinInfo obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_WidgetSkinInfo(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public WidgetSkinInfo(String _name) {
    this(MyoushuJNI.new_WidgetSkinInfo(_name), true);
  }

  public void setInfo(SWIGTYPE_p_MyGUI__types__TSizeT_int_t _size, String _texture) {
    MyoushuJNI.WidgetSkinInfo_setInfo(swigCPtr, this, SWIGTYPE_p_MyGUI__types__TSizeT_int_t.getCPtr(_size), _texture);
  }

  public void addInfo(SubWidgetBinding _bind) {
    MyoushuJNI.WidgetSkinInfo_addInfo(swigCPtr, this, SubWidgetBinding.getCPtr(_bind), _bind);
  }

  public void addProperty(String _key, String _value) {
    MyoushuJNI.WidgetSkinInfo_addProperty(swigCPtr, this, _key, _value);
  }

  public void addChild(ChildSkinInfo _child) {
    MyoushuJNI.WidgetSkinInfo_addChild(swigCPtr, this, ChildSkinInfo.getCPtr(_child), _child);
  }

  public boolean loadMask(String _file) {
    return MyoushuJNI.WidgetSkinInfo_loadMask(swigCPtr, this, _file);
  }

  public void clear() {
    MyoushuJNI.WidgetSkinInfo_clear(swigCPtr, this);
  }

  public SWIGTYPE_p_MyGUI__types__TSizeT_int_t getSize() {
    return new SWIGTYPE_p_MyGUI__types__TSizeT_int_t(MyoushuJNI.WidgetSkinInfo_getSize(swigCPtr, this), false);
  }

  public String getTextureName() {
    return MyoushuJNI.WidgetSkinInfo_getTextureName(swigCPtr, this);
  }

  public SWIGTYPE_p_std__vectorT_MyGUI__SubWidgetInfo_t getBasisInfo() {
    return new SWIGTYPE_p_std__vectorT_MyGUI__SubWidgetInfo_t(MyoushuJNI.WidgetSkinInfo_getBasisInfo(swigCPtr, this), false);
  }

  public SWIGTYPE_p_std__mapT_std__string_std__vectorT_MyGUI__IStateInfo_p_t_t getStateInfo() {
    return new SWIGTYPE_p_std__mapT_std__string_std__vectorT_MyGUI__IStateInfo_p_t_t(MyoushuJNI.WidgetSkinInfo_getStateInfo(swigCPtr, this), false);
  }

  public SWIGTYPE_p_std__mapT_std__string_std__string_t getProperties() {
    return new SWIGTYPE_p_std__mapT_std__string_std__string_t(MyoushuJNI.WidgetSkinInfo_getProperties(swigCPtr, this), false);
  }

  public SWIGTYPE_p_std__vectorT_MyGUI__ChildSkinInfo_t getChild() {
    return new SWIGTYPE_p_std__vectorT_MyGUI__ChildSkinInfo_t(MyoushuJNI.WidgetSkinInfo_getChild(swigCPtr, this), false);
  }

  public SWIGTYPE_p_MyGUI__MaskPickInfo getMask() {
    long cPtr = MyoushuJNI.WidgetSkinInfo_getMask(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__MaskPickInfo(cPtr, false);
  }

  public String getSkinName() {
    return MyoushuJNI.WidgetSkinInfo_getSkinName(swigCPtr, this);
  }

}
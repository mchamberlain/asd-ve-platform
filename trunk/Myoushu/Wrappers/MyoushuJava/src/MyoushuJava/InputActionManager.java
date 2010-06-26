/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class InputActionManager extends Singleton_InputActionManager {
  private long swigCPtr;

  public InputActionManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGInputActionManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(InputActionManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_InputActionManager(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public InputActionManager() {
    this(MyoushuJNI.new_InputActionManager(), true);
  }

  public void disableCallbacks() {
    MyoushuJNI.InputActionManager_disableCallbacks__SWIG_0(swigCPtr, this);
  }

  public void disableCallbacks(ListString exceptions) {
    MyoushuJNI.InputActionManager_disableCallbacks__SWIG_1(swigCPtr, this, ListString.getCPtr(exceptions), exceptions);
  }

  public void enableCallbacks() {
    MyoushuJNI.InputActionManager_enableCallbacks(swigCPtr, this);
  }

  public boolean isCallbacksDisabled() {
    return MyoushuJNI.InputActionManager_isCallbacksDisabled(swigCPtr, this);
  }

  public boolean isCallbacksForActionEnabled(String action) {
    return MyoushuJNI.InputActionManager_isCallbacksForActionEnabled(swigCPtr, this, action);
  }

  public boolean actionExists(String inputAction) {
    return MyoushuJNI.InputActionManager_actionExists(swigCPtr, this, inputAction);
  }

  public void getInputActionCallbacks(String inputAction, SWIGTYPE_p_std__listT_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t_p_t list) {
    MyoushuJNI.InputActionManager_getInputActionCallbacks__SWIG_0(swigCPtr, this, inputAction, SWIGTYPE_p_std__listT_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t_p_t.getCPtr(list));
  }

  public SWIGTYPE_p_std__listT_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t_p_t getInputActionCallbacks(String inputAction) {
    long cPtr = MyoushuJNI.InputActionManager_getInputActionCallbacks__SWIG_1(swigCPtr, this, inputAction);
    return (cPtr == 0) ? null : new SWIGTYPE_p_std__listT_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t_p_t(cPtr, false);
  }

  public void addInputActionCallback(SWIGTYPE_p_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t inputActionCallback) {
    MyoushuJNI.InputActionManager_addInputActionCallback__SWIG_0(swigCPtr, this, SWIGTYPE_p_Myoushu__ActionStringCallbackBaseT_void_Myoushu__InputMessage_t.getCPtr(inputActionCallback));
  }

  public void addInputActionCallback(String inputAction, SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__InputMessage_t__ActionStringCallbackGlobalFunction functionPtr) {
    MyoushuJNI.InputActionManager_addInputActionCallback__SWIG_1(swigCPtr, this, inputAction, SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__InputMessage_t__ActionStringCallbackGlobalFunction.getCPtr(functionPtr));
  }

  public void addInputActionCallback(String inputAction, String luaFunction) {
    MyoushuJNI.InputActionManager_addInputActionCallback__SWIG_2(swigCPtr, this, inputAction, luaFunction);
  }

  public void addInputActionCallback(String inputAction, SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__InputMessage_t__ActionStringCallbackLuaFunctor luaFunction) {
    MyoushuJNI.InputActionManager_addInputActionCallback__SWIG_3(swigCPtr, this, inputAction, SWIGTYPE_p_Myoushu__ActionStringCallbackT_void_Myoushu__InputMessage_t__ActionStringCallbackLuaFunctor.getCPtr(luaFunction));
  }

  public void addInputActionCallback(String inputAction, FunctorBase pFunctor) {
    MyoushuJNI.InputActionManager_addInputActionCallback__SWIG_4(swigCPtr, this, inputAction, FunctorBase.getCPtr(pFunctor), pFunctor);
  }

  public void removeInputAction(String inputAction) {
    MyoushuJNI.InputActionManager_removeInputAction(swigCPtr, this, inputAction);
  }

}

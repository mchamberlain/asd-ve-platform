/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class LuaParser {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public LuaParser(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(LuaParser obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_LuaParser(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public LuaParser() {
    this(MyoushuJNI.new_LuaParser(), true);
  }

  public SWIGTYPE_p_lua_State getLuaState() {
    long cPtr = MyoushuJNI.LuaParser_getLuaState__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_lua_State(cPtr, false);
  }

  public void getLuaStateLock(boolean write) {
    MyoushuJNI.LuaParser_getLuaStateLock__SWIG_0(swigCPtr, this, write);
  }

  public void getLuaStateLock() {
    MyoushuJNI.LuaParser_getLuaStateLock__SWIG_1(swigCPtr, this);
  }

  public void releaseLuaStateLock() {
    MyoushuJNI.LuaParser_releaseLuaStateLock(swigCPtr, this);
  }

  public void execute(String script) {
    MyoushuJNI.LuaParser_execute(swigCPtr, this, script);
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Myoushu implements MyoushuConstants {
  public static int findCommandLineOpts(int numargs, SWIGTYPE_p_p_char argv, SWIGTYPE_p_std__mapT_std__string_bool_t unaryOptList, SWIGTYPE_p_std__mapT_std__string_std__string_t binOptList) {
    return MyoushuJNI.findCommandLineOpts(numargs, SWIGTYPE_p_p_char.getCPtr(argv), SWIGTYPE_p_std__mapT_std__string_bool_t.getCPtr(unaryOptList), SWIGTYPE_p_std__mapT_std__string_std__string_t.getCPtr(binOptList));
  }

  public static void NxThrow(String arg0, int arg1, String arg2, long arg3) {
    MyoushuJNI.NxThrow(arg0, arg1, arg2, arg3);
  }

  public static SWIGTYPE_p_NxVec3 getNxVec3Axis() {
    long cPtr = MyoushuJNI.NxVec3Axis_get();
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxVec3(cPtr, false);
  }

  public static void setNx_Version_Full(String value) {
    MyoushuJNI.Nx_Version_Full_set(value);
  }

  public static String getNx_Version_Full() {
    return MyoushuJNI.Nx_Version_Full_get();
  }

  public static int luaPrint(SWIGTYPE_p_lua_State L) {
    return MyoushuJNI.luaPrint(SWIGTYPE_p_lua_State.getCPtr(L));
  }

  public static void JavaFunctor_setMethod(long arg0, Object arg1, Object arg2, String arg3, String arg4) {
    MyoushuJNI.JavaFunctor_setMethod(arg0, arg1, arg2, arg3, arg4);
  }

}

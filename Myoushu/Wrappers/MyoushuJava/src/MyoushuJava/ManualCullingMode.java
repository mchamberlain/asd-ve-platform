/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum ManualCullingMode {
  MANUAL_CULL_NONE(MyoushuJNI.MANUAL_CULL_NONE_get()),
  MANUAL_CULL_BACK(MyoushuJNI.MANUAL_CULL_BACK_get()),
  MANUAL_CULL_FRONT(MyoushuJNI.MANUAL_CULL_FRONT_get());

  public final int swigValue() {
    return swigValue;
  }

  public static ManualCullingMode swigToEnum(int swigValue) {
    ManualCullingMode[] swigValues = ManualCullingMode.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (ManualCullingMode swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + ManualCullingMode.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private ManualCullingMode() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private ManualCullingMode(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private ManualCullingMode(ManualCullingMode swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}


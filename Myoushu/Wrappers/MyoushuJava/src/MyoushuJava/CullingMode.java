/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum CullingMode {
  CULL_NONE(MyoushuJNI.CULL_NONE_get()),
  CULL_CLOCKWISE(MyoushuJNI.CULL_CLOCKWISE_get()),
  CULL_ANTICLOCKWISE(MyoushuJNI.CULL_ANTICLOCKWISE_get());

  public final int swigValue() {
    return swigValue;
  }

  public static CullingMode swigToEnum(int swigValue) {
    CullingMode[] swigValues = CullingMode.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (CullingMode swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + CullingMode.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private CullingMode() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private CullingMode(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private CullingMode(CullingMode swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}


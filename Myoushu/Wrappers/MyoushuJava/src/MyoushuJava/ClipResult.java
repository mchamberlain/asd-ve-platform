/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum ClipResult {
  CLIPPED_NONE(MyoushuJNI.CLIPPED_NONE_get()),
  CLIPPED_SOME(MyoushuJNI.CLIPPED_SOME_get()),
  CLIPPED_ALL(MyoushuJNI.CLIPPED_ALL_get());

  public final int swigValue() {
    return swigValue;
  }

  public static ClipResult swigToEnum(int swigValue) {
    ClipResult[] swigValues = ClipResult.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (ClipResult swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + ClipResult.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private ClipResult() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private ClipResult(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private ClipResult(ClipResult swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

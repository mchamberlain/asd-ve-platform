/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum NxComparisonOperator {
  CO_MORE_THAN,
  CO_LESS_THAN,
  CO_EXACTLY,
  CO_NOT;

  public final int swigValue() {
    return swigValue;
  }

  public static NxComparisonOperator swigToEnum(int swigValue) {
    NxComparisonOperator[] swigValues = NxComparisonOperator.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (NxComparisonOperator swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + NxComparisonOperator.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private NxComparisonOperator() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private NxComparisonOperator(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private NxComparisonOperator(NxComparisonOperator swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}


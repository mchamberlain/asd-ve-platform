/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum WaveformType {
  WFT_SINE,
  WFT_TRIANGLE,
  WFT_SQUARE,
  WFT_SAWTOOTH,
  WFT_INVERSE_SAWTOOTH,
  WFT_PWM;

  public final int swigValue() {
    return swigValue;
  }

  public static WaveformType swigToEnum(int swigValue) {
    WaveformType[] swigValues = WaveformType.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (WaveformType swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + WaveformType.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private WaveformType() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private WaveformType(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private WaveformType(WaveformType swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}


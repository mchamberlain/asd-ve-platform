/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public enum ShadowTechnique {
  SHADOWTYPE_NONE(MyoushuJNI.SHADOWTYPE_NONE_get()),
  SHADOWDETAILTYPE_ADDITIVE(MyoushuJNI.SHADOWDETAILTYPE_ADDITIVE_get()),
  SHADOWDETAILTYPE_MODULATIVE(MyoushuJNI.SHADOWDETAILTYPE_MODULATIVE_get()),
  SHADOWDETAILTYPE_INTEGRATED(MyoushuJNI.SHADOWDETAILTYPE_INTEGRATED_get()),
  SHADOWDETAILTYPE_STENCIL(MyoushuJNI.SHADOWDETAILTYPE_STENCIL_get()),
  SHADOWDETAILTYPE_TEXTURE(MyoushuJNI.SHADOWDETAILTYPE_TEXTURE_get()),
  SHADOWTYPE_STENCIL_MODULATIVE(MyoushuJNI.SHADOWTYPE_STENCIL_MODULATIVE_get()),
  SHADOWTYPE_STENCIL_ADDITIVE(MyoushuJNI.SHADOWTYPE_STENCIL_ADDITIVE_get()),
  SHADOWTYPE_TEXTURE_MODULATIVE(MyoushuJNI.SHADOWTYPE_TEXTURE_MODULATIVE_get()),
  SHADOWTYPE_TEXTURE_ADDITIVE(MyoushuJNI.SHADOWTYPE_TEXTURE_ADDITIVE_get()),
  SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED(MyoushuJNI.SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED_get()),
  SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED(MyoushuJNI.SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED_get());

  public final int swigValue() {
    return swigValue;
  }

  public static ShadowTechnique swigToEnum(int swigValue) {
    ShadowTechnique[] swigValues = ShadowTechnique.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (ShadowTechnique swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + ShadowTechnique.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private ShadowTechnique() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private ShadowTechnique(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private ShadowTechnique(ShadowTechnique swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class MTRandom extends RandomBase {
  private long swigCPtr;

  public MTRandom(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGMTRandomUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MTRandom obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_MTRandom(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static long getW() {
    return MyoushuJNI.MTRandom_W_get();
  }

  public static long getN() {
    return MyoushuJNI.MTRandom_N_get();
  }

  public static long getM() {
    return MyoushuJNI.MTRandom_M_get();
  }

  public static long getR() {
    return MyoushuJNI.MTRandom_R_get();
  }

  public static long getA() {
    return MyoushuJNI.MTRandom_A_get();
  }

  public static long getU() {
    return MyoushuJNI.MTRandom_U_get();
  }

  public static long getS() {
    return MyoushuJNI.MTRandom_S_get();
  }

  public static long getB() {
    return MyoushuJNI.MTRandom_B_get();
  }

  public static long getT() {
    return MyoushuJNI.MTRandom_T_get();
  }

  public static long getC() {
    return MyoushuJNI.MTRandom_C_get();
  }

  public static long getL() {
    return MyoushuJNI.MTRandom_L_get();
  }

  public MTRandom() {
    this(MyoushuJNI.new_MTRandom__SWIG_0(), true);
  }

  public MTRandom(long seed) {
    this(MyoushuJNI.new_MTRandom__SWIG_1(seed), true);
  }

  public void seed(int seed) {
    MyoushuJNI.MTRandom_seed(swigCPtr, this, seed);
  }

  public long generate() {
    return MyoushuJNI.MTRandom_generate__SWIG_0(swigCPtr, this);
  }

  public int generate(int min, int max) {
    return MyoushuJNI.MTRandom_generate__SWIG_1(swigCPtr, this, min, max);
  }

  public double generateDouble() {
    return MyoushuJNI.MTRandom_generateDouble__SWIG_0(swigCPtr, this);
  }

  public double generateDouble(double min, double max) {
    return MyoushuJNI.MTRandom_generateDouble__SWIG_1(swigCPtr, this, min, max);
  }

  public long getIndex() {
    return MyoushuJNI.MTRandom_getIndex(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MTRandom_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MTRandom_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MTRandom_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MTRandom_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}
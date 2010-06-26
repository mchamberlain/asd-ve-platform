/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Math {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public Math(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(Math obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_Math(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Math(long trigTableSize) {
    this(MyoushuJNI.new_Math__SWIG_0(trigTableSize), true);
  }

  public Math() {
    this(MyoushuJNI.new_Math__SWIG_1(), true);
  }

  public static int IAbs(int iValue) {
    return MyoushuJNI.Math_IAbs(iValue);
  }

  public static int ICeil(float fValue) {
    return MyoushuJNI.Math_ICeil(fValue);
  }

  public static int IFloor(float fValue) {
    return MyoushuJNI.Math_IFloor(fValue);
  }

  public static int ISign(int iValue) {
    return MyoushuJNI.Math_ISign(iValue);
  }

  public static float Abs(float fValue) {
    return MyoushuJNI.Math_Abs__SWIG_0(fValue);
  }

  public static Degree Abs(Degree dValue) {
    return new Degree(MyoushuJNI.Math_Abs__SWIG_1(Degree.getCPtr(dValue), dValue), true);
  }

  public static Radian Abs(Radian rValue) {
    return new Radian(MyoushuJNI.Math_Abs__SWIG_2(Radian.getCPtr(rValue), rValue), true);
  }

  public static Radian ACos(float fValue) {
    return new Radian(MyoushuJNI.Math_ACos(fValue), true);
  }

  public static Radian ASin(float fValue) {
    return new Radian(MyoushuJNI.Math_ASin(fValue), true);
  }

  public static Radian ATan(float fValue) {
    return new Radian(MyoushuJNI.Math_ATan(fValue), true);
  }

  public static Radian ATan2(float fY, float fX) {
    return new Radian(MyoushuJNI.Math_ATan2(fY, fX), true);
  }

  public static float Ceil(float fValue) {
    return MyoushuJNI.Math_Ceil(fValue);
  }

  public static float Cos(Radian fValue, boolean useTables) {
    return MyoushuJNI.Math_Cos__SWIG_0(Radian.getCPtr(fValue), fValue, useTables);
  }

  public static float Cos(Radian fValue) {
    return MyoushuJNI.Math_Cos__SWIG_1(Radian.getCPtr(fValue), fValue);
  }

  public static float Cos(float fValue, boolean useTables) {
    return MyoushuJNI.Math_Cos__SWIG_2(fValue, useTables);
  }

  public static float Cos(float fValue) {
    return MyoushuJNI.Math_Cos__SWIG_3(fValue);
  }

  public static float Exp(float fValue) {
    return MyoushuJNI.Math_Exp(fValue);
  }

  public static float Floor(float fValue) {
    return MyoushuJNI.Math_Floor(fValue);
  }

  public static float Log(float fValue) {
    return MyoushuJNI.Math_Log(fValue);
  }

  public static float Pow(float fBase, float fExponent) {
    return MyoushuJNI.Math_Pow(fBase, fExponent);
  }

  public static float Sign(float fValue) {
    return MyoushuJNI.Math_Sign__SWIG_0(fValue);
  }

  public static Radian Sign(Radian rValue) {
    return new Radian(MyoushuJNI.Math_Sign__SWIG_1(Radian.getCPtr(rValue), rValue), true);
  }

  public static Degree Sign(Degree dValue) {
    return new Degree(MyoushuJNI.Math_Sign__SWIG_2(Degree.getCPtr(dValue), dValue), true);
  }

  public static float Sin(Radian fValue, boolean useTables) {
    return MyoushuJNI.Math_Sin__SWIG_0(Radian.getCPtr(fValue), fValue, useTables);
  }

  public static float Sin(Radian fValue) {
    return MyoushuJNI.Math_Sin__SWIG_1(Radian.getCPtr(fValue), fValue);
  }

  public static float Sin(float fValue, boolean useTables) {
    return MyoushuJNI.Math_Sin__SWIG_2(fValue, useTables);
  }

  public static float Sin(float fValue) {
    return MyoushuJNI.Math_Sin__SWIG_3(fValue);
  }

  public static float Sqr(float fValue) {
    return MyoushuJNI.Math_Sqr(fValue);
  }

  public static float Sqrt(float fValue) {
    return MyoushuJNI.Math_Sqrt__SWIG_0(fValue);
  }

  public static Radian Sqrt(Radian fValue) {
    return new Radian(MyoushuJNI.Math_Sqrt__SWIG_1(Radian.getCPtr(fValue), fValue), true);
  }

  public static Degree Sqrt(Degree fValue) {
    return new Degree(MyoushuJNI.Math_Sqrt__SWIG_2(Degree.getCPtr(fValue), fValue), true);
  }

  public static float InvSqrt(float fValue) {
    return MyoushuJNI.Math_InvSqrt(fValue);
  }

  public static float UnitRandom() {
    return MyoushuJNI.Math_UnitRandom();
  }

  public static float RangeRandom(float fLow, float fHigh) {
    return MyoushuJNI.Math_RangeRandom(fLow, fHigh);
  }

  public static float SymmetricRandom() {
    return MyoushuJNI.Math_SymmetricRandom();
  }

  public static float Tan(Radian fValue, boolean useTables) {
    return MyoushuJNI.Math_Tan__SWIG_0(Radian.getCPtr(fValue), fValue, useTables);
  }

  public static float Tan(Radian fValue) {
    return MyoushuJNI.Math_Tan__SWIG_1(Radian.getCPtr(fValue), fValue);
  }

  public static float Tan(float fValue, boolean useTables) {
    return MyoushuJNI.Math_Tan__SWIG_2(fValue, useTables);
  }

  public static float Tan(float fValue) {
    return MyoushuJNI.Math_Tan__SWIG_3(fValue);
  }

  public static float DegreesToRadians(float degrees) {
    return MyoushuJNI.Math_DegreesToRadians(degrees);
  }

  public static float RadiansToDegrees(float radians) {
    return MyoushuJNI.Math_RadiansToDegrees(radians);
  }

  public static void setAngleUnit(Math.AngleUnit unit) {
    MyoushuJNI.Math_setAngleUnit(unit.swigValue());
  }

  public static Math.AngleUnit getAngleUnit() {
    return Math.AngleUnit.swigToEnum(MyoushuJNI.Math_getAngleUnit());
  }

  public static float AngleUnitsToRadians(float units) {
    return MyoushuJNI.Math_AngleUnitsToRadians(units);
  }

  public static float RadiansToAngleUnits(float radians) {
    return MyoushuJNI.Math_RadiansToAngleUnits(radians);
  }

  public static float AngleUnitsToDegrees(float units) {
    return MyoushuJNI.Math_AngleUnitsToDegrees(units);
  }

  public static float DegreesToAngleUnits(float degrees) {
    return MyoushuJNI.Math_DegreesToAngleUnits(degrees);
  }

  public static boolean pointInTri2D(Vector2 p, Vector2 a, Vector2 b, Vector2 c) {
    return MyoushuJNI.Math_pointInTri2D(Vector2.getCPtr(p), p, Vector2.getCPtr(a), a, Vector2.getCPtr(b), b, Vector2.getCPtr(c), c);
  }

  public static boolean pointInTri3D(Vector3 p, Vector3 a, Vector3 b, Vector3 c, Vector3 normal) {
    return MyoushuJNI.Math_pointInTri3D(Vector3.getCPtr(p), p, Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, Vector3.getCPtr(normal), normal);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_Ogre__Plane plane) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_0(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_Ogre__Plane.getCPtr(plane)), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_Ogre__Sphere sphere, boolean discardInside) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_1(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_Ogre__Sphere.getCPtr(sphere), discardInside), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_Ogre__Sphere sphere) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_2(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_Ogre__Sphere.getCPtr(sphere)), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_Ogre__AxisAlignedBox box) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_3(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_Ogre__AxisAlignedBox.getCPtr(box)), true);
  }

  public static boolean intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_Ogre__AxisAlignedBox box, SWIGTYPE_p_float d1, SWIGTYPE_p_float d2) {
    return MyoushuJNI.Math_intersects__SWIG_4(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_Ogre__AxisAlignedBox.getCPtr(box), SWIGTYPE_p_float.getCPtr(d1), SWIGTYPE_p_float.getCPtr(d2));
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c, Vector3 normal, boolean positiveSide, boolean negativeSide) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_5(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, Vector3.getCPtr(normal), normal, positiveSide, negativeSide), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c, Vector3 normal, boolean positiveSide) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_6(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, Vector3.getCPtr(normal), normal, positiveSide), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c, Vector3 normal) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_7(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, Vector3.getCPtr(normal), normal), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c, boolean positiveSide, boolean negativeSide) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_8(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, positiveSide, negativeSide), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c, boolean positiveSide) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_9(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c, positiveSide), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, Vector3 a, Vector3 b, Vector3 c) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_10(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), Vector3.getCPtr(a), a, Vector3.getCPtr(b), b, Vector3.getCPtr(c), c), true);
  }

  public static boolean intersects(SWIGTYPE_p_Ogre__Sphere sphere, SWIGTYPE_p_Ogre__AxisAlignedBox box) {
    return MyoushuJNI.Math_intersects__SWIG_11(SWIGTYPE_p_Ogre__Sphere.getCPtr(sphere), SWIGTYPE_p_Ogre__AxisAlignedBox.getCPtr(box));
  }

  public static boolean intersects(SWIGTYPE_p_Ogre__Plane plane, SWIGTYPE_p_Ogre__AxisAlignedBox box) {
    return MyoushuJNI.Math_intersects__SWIG_12(SWIGTYPE_p_Ogre__Plane.getCPtr(plane), SWIGTYPE_p_Ogre__AxisAlignedBox.getCPtr(box));
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_std__vectorT_Ogre__Plane_t planeList, boolean normalIsOutside) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_13(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_std__vectorT_Ogre__Plane_t.getCPtr(planeList), normalIsOutside), true);
  }

  public static SWIGTYPE_p_std__pairT_bool_float_t intersects(SWIGTYPE_p_Ogre__Ray ray, SWIGTYPE_p_std__listT_Ogre__Plane_t planeList, boolean normalIsOutside) {
    return new SWIGTYPE_p_std__pairT_bool_float_t(MyoushuJNI.Math_intersects__SWIG_14(SWIGTYPE_p_Ogre__Ray.getCPtr(ray), SWIGTYPE_p_std__listT_Ogre__Plane_t.getCPtr(planeList), normalIsOutside), true);
  }

  public static boolean intersects(SWIGTYPE_p_Ogre__Sphere sphere, SWIGTYPE_p_Ogre__Plane plane) {
    return MyoushuJNI.Math_intersects__SWIG_15(SWIGTYPE_p_Ogre__Sphere.getCPtr(sphere), SWIGTYPE_p_Ogre__Plane.getCPtr(plane));
  }

  public static boolean RealEqual(float a, float b, float tolerance) {
    return MyoushuJNI.Math_RealEqual__SWIG_0(a, b, tolerance);
  }

  public static boolean RealEqual(float a, float b) {
    return MyoushuJNI.Math_RealEqual__SWIG_1(a, b);
  }

  public static Vector3 calculateTangentSpaceVector(Vector3 position1, Vector3 position2, Vector3 position3, float u1, float v1, float u2, float v2, float u3, float v3) {
    return new Vector3(MyoushuJNI.Math_calculateTangentSpaceVector(Vector3.getCPtr(position1), position1, Vector3.getCPtr(position2), position2, Vector3.getCPtr(position3), position3, u1, v1, u2, v2, u3, v3), true);
  }

  public static Matrix4 buildReflectionMatrix(SWIGTYPE_p_Ogre__Plane p) {
    return new Matrix4(MyoushuJNI.Math_buildReflectionMatrix(SWIGTYPE_p_Ogre__Plane.getCPtr(p)), true);
  }

  public static Vector4 calculateFaceNormal(Vector3 v1, Vector3 v2, Vector3 v3) {
    return new Vector4(MyoushuJNI.Math_calculateFaceNormal(Vector3.getCPtr(v1), v1, Vector3.getCPtr(v2), v2, Vector3.getCPtr(v3), v3), true);
  }

  public static Vector3 calculateBasicFaceNormal(Vector3 v1, Vector3 v2, Vector3 v3) {
    return new Vector3(MyoushuJNI.Math_calculateBasicFaceNormal(Vector3.getCPtr(v1), v1, Vector3.getCPtr(v2), v2, Vector3.getCPtr(v3), v3), true);
  }

  public static Vector4 calculateFaceNormalWithoutNormalize(Vector3 v1, Vector3 v2, Vector3 v3) {
    return new Vector4(MyoushuJNI.Math_calculateFaceNormalWithoutNormalize(Vector3.getCPtr(v1), v1, Vector3.getCPtr(v2), v2, Vector3.getCPtr(v3), v3), true);
  }

  public static Vector3 calculateBasicFaceNormalWithoutNormalize(Vector3 v1, Vector3 v2, Vector3 v3) {
    return new Vector3(MyoushuJNI.Math_calculateBasicFaceNormalWithoutNormalize(Vector3.getCPtr(v1), v1, Vector3.getCPtr(v2), v2, Vector3.getCPtr(v3), v3), true);
  }

  public static float gaussianDistribution(float x, float offset, float scale) {
    return MyoushuJNI.Math_gaussianDistribution__SWIG_0(x, offset, scale);
  }

  public static float gaussianDistribution(float x, float offset) {
    return MyoushuJNI.Math_gaussianDistribution__SWIG_1(x, offset);
  }

  public static float gaussianDistribution(float x) {
    return MyoushuJNI.Math_gaussianDistribution__SWIG_2(x);
  }

  public static Matrix4 makeViewMatrix(Vector3 position, Quaternion orientation, Matrix4 reflectMatrix) {
    return new Matrix4(MyoushuJNI.Math_makeViewMatrix__SWIG_0(Vector3.getCPtr(position), position, Quaternion.getCPtr(orientation), orientation, Matrix4.getCPtr(reflectMatrix), reflectMatrix), true);
  }

  public static Matrix4 makeViewMatrix(Vector3 position, Quaternion orientation) {
    return new Matrix4(MyoushuJNI.Math_makeViewMatrix__SWIG_1(Vector3.getCPtr(position), position, Quaternion.getCPtr(orientation), orientation), true);
  }

  public static float getPOS_INFINITY() {
    return MyoushuJNI.Math_POS_INFINITY_get();
  }

  public static float getNEG_INFINITY() {
    return MyoushuJNI.Math_NEG_INFINITY_get();
  }

  public static float getPI() {
    return MyoushuJNI.Math_PI_get();
  }

  public static float getTWO_PI() {
    return MyoushuJNI.Math_TWO_PI_get();
  }

  public static float getHALF_PI() {
    return MyoushuJNI.Math_HALF_PI_get();
  }

  public static float getFDeg2Rad() {
    return MyoushuJNI.Math_fDeg2Rad_get();
  }

  public static float getFRad2Deg() {
    return MyoushuJNI.Math_fRad2Deg_get();
  }

  public enum AngleUnit {
    AU_DEGREE,
    AU_RADIAN;

    public final int swigValue() {
      return swigValue;
    }

    public static AngleUnit swigToEnum(int swigValue) {
      AngleUnit[] swigValues = AngleUnit.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (AngleUnit swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + AngleUnit.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private AngleUnit() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private AngleUnit(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private AngleUnit(AngleUnit swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

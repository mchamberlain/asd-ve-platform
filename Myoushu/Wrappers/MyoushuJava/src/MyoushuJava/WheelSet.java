/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class WheelSet {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public WheelSet(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(WheelSet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_WheelSet(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static WheelSet createFourWheelSet(NxOgre_Actor arg0, Vector3 frontLeft, Vector3 backLeft, float radius, ShapeParams sp, WheelParams wp) {
    return new WheelSet(MyoushuJNI.WheelSet_createFourWheelSet__SWIG_0(NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(frontLeft), frontLeft, Vector3.getCPtr(backLeft), backLeft, radius, ShapeParams.getCPtr(sp), sp, WheelParams.getCPtr(wp), wp), true);
  }

  public static WheelSet createFourWheelSet(NxOgre_Actor arg0, Vector3 frontLeft, Vector3 backLeft, float radius, ShapeParams sp) {
    return new WheelSet(MyoushuJNI.WheelSet_createFourWheelSet__SWIG_1(NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(frontLeft), frontLeft, Vector3.getCPtr(backLeft), backLeft, radius, ShapeParams.getCPtr(sp), sp), true);
  }

  public static WheelSet createFourWheelSet(NxOgre_Actor arg0, Vector3 frontLeft, Vector3 backLeft, float radius) {
    return new WheelSet(MyoushuJNI.WheelSet_createFourWheelSet__SWIG_2(NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(frontLeft), frontLeft, Vector3.getCPtr(backLeft), backLeft, radius), true);
  }

  public static WheelSet createFourWheelSet(NxOgre_Actor arg0, Vector3 frontLeft, Vector3 backLeft) {
    return new WheelSet(MyoushuJNI.WheelSet_createFourWheelSet__SWIG_3(NxOgre_Actor.getCPtr(arg0), arg0, Vector3.getCPtr(frontLeft), frontLeft, Vector3.getCPtr(backLeft), backLeft), true);
  }

  public WheelSet() {
    this(MyoushuJNI.new_WheelSet(), true);
  }

  public void turn(Radian angle) {
    MyoushuJNI.WheelSet_turn(swigCPtr, this, Radian.getCPtr(angle), angle);
  }

  public void setMotorTorque(float torque) {
    MyoushuJNI.WheelSet_setMotorTorque(swigCPtr, this, torque);
  }

  public void setBrakeTorque(float torque) {
    MyoushuJNI.WheelSet_setBrakeTorque(swigCPtr, this, torque);
  }

  public void addMeshes(String meshName, Vector3 offset) {
    MyoushuJNI.WheelSet_addMeshes__SWIG_0(swigCPtr, this, meshName, Vector3.getCPtr(offset), offset);
  }

  public void addMeshes(String meshName) {
    MyoushuJNI.WheelSet_addMeshes__SWIG_1(swigCPtr, this, meshName);
  }

  public void attachDriveShaft(SWIGTYPE_p_NxOgre__DriveShaft arg0) {
    MyoushuJNI.WheelSet_attachDriveShaft(swigCPtr, this, SWIGTYPE_p_NxOgre__DriveShaft.getCPtr(arg0));
  }

  public void setFrontLeft(Wheel value) {
    MyoushuJNI.WheelSet_frontLeft_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getFrontLeft() {
    long cPtr = MyoushuJNI.WheelSet_frontLeft_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setFrontRight(Wheel value) {
    MyoushuJNI.WheelSet_frontRight_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getFrontRight() {
    long cPtr = MyoushuJNI.WheelSet_frontRight_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setBackLeft(Wheel value) {
    MyoushuJNI.WheelSet_backLeft_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getBackLeft() {
    long cPtr = MyoushuJNI.WheelSet_backLeft_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setBackRight(Wheel value) {
    MyoushuJNI.WheelSet_backRight_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getBackRight() {
    long cPtr = MyoushuJNI.WheelSet_backRight_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setMiddleLeft(Wheel value) {
    MyoushuJNI.WheelSet_middleLeft_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getMiddleLeft() {
    long cPtr = MyoushuJNI.WheelSet_middleLeft_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setMiddleRight(Wheel value) {
    MyoushuJNI.WheelSet_middleRight_set(swigCPtr, this, Wheel.getCPtr(value), value);
  }

  public Wheel getMiddleRight() {
    long cPtr = MyoushuJNI.WheelSet_middleRight_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Wheel(cPtr, false);
  }

  public void setMDriveShaft(SWIGTYPE_p_NxOgre__DriveShaft value) {
    MyoushuJNI.WheelSet_mDriveShaft_set(swigCPtr, this, SWIGTYPE_p_NxOgre__DriveShaft.getCPtr(value));
  }

  public SWIGTYPE_p_NxOgre__DriveShaft getMDriveShaft() {
    long cPtr = MyoushuJNI.WheelSet_mDriveShaft_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__DriveShaft(cPtr, false);
  }

  public void setMWheels(SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t value) {
    MyoushuJNI.WheelSet_mWheels_set(swigCPtr, this, SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t.getCPtr(value));
  }

  public SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t getMWheels() {
    long cPtr = MyoushuJNI.WheelSet_mWheels_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t(cPtr, false);
  }

  public void setDrive(SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t value) {
    MyoushuJNI.WheelSet_Drive_set(swigCPtr, this, SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t.getCPtr(value));
  }

  public SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t getDrive() {
    long cPtr = MyoushuJNI.WheelSet_Drive_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t(cPtr, false);
  }

  public void setSteering(SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t value) {
    MyoushuJNI.WheelSet_Steering_set(swigCPtr, this, SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t.getCPtr(value));
  }

  public SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t getSteering() {
    long cPtr = MyoushuJNI.WheelSet_Steering_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ListT_NxOgre__Wheel_p_t(cPtr, false);
  }

}

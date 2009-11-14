/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ActorParams extends Params {
  private long swigCPtr;

  public ActorParams(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGActorParamsUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ActorParams obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_ActorParams(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public ActorParams() {
    this(MyoushuJNI.new_ActorParams__SWIG_0(), true);
  }

  public ActorParams(String p) {
    this(MyoushuJNI.new_ActorParams__SWIG_1(p), true);
  }

  public void setToDefault() {
    MyoushuJNI.ActorParams_setToDefault(swigCPtr, this);
  }

  public void parse(SWIGTYPE_p_std__vectorT_std__pairT_std__string_std__string_t_t arg0) {
    MyoushuJNI.ActorParams_parse(swigCPtr, this, SWIGTYPE_p_std__vectorT_std__pairT_std__string_std__string_t_t.getCPtr(arg0));
  }

  public void fromNxActorDesc(SWIGTYPE_p_NxActorDesc arg0) {
    MyoushuJNI.ActorParams_fromNxActorDesc(swigCPtr, this, SWIGTYPE_p_NxActorDesc.getCPtr(arg0));
  }

  public void fromNxBodyDesc(SWIGTYPE_p_NxBodyDesc arg0) {
    MyoushuJNI.ActorParams_fromNxBodyDesc(swigCPtr, this, SWIGTYPE_p_NxBodyDesc.getCPtr(arg0));
  }

  public void setMDensity(float value) {
    MyoushuJNI.ActorParams_mDensity_set(swigCPtr, this, value);
  }

  public float getMDensity() {
    return MyoushuJNI.ActorParams_mDensity_get(swigCPtr, this);
  }

  public void setMActorFlags(long value) {
    MyoushuJNI.ActorParams_mActorFlags_set(swigCPtr, this, value);
  }

  public long getMActorFlags() {
    return MyoushuJNI.ActorParams_mActorFlags_get(swigCPtr, this);
  }

  public void setMGroupAsIndex(SWIGTYPE_p_NxActorGroup value) {
    MyoushuJNI.ActorParams_mGroupAsIndex_set(swigCPtr, this, SWIGTYPE_p_NxActorGroup.getCPtr(value));
  }

  public SWIGTYPE_p_NxActorGroup getMGroupAsIndex() {
    return new SWIGTYPE_p_NxActorGroup(MyoushuJNI.ActorParams_mGroupAsIndex_get(swigCPtr, this), true);
  }

  public void setMGroupAsName(String value) {
    MyoushuJNI.ActorParams_mGroupAsName_set(swigCPtr, this, value);
  }

  public String getMGroupAsName() {
    return MyoushuJNI.ActorParams_mGroupAsName_get(swigCPtr, this);
  }

  public void setMAngularDamping(float value) {
    MyoushuJNI.ActorParams_mAngularDamping_set(swigCPtr, this, value);
  }

  public float getMAngularDamping() {
    return MyoushuJNI.ActorParams_mAngularDamping_get(swigCPtr, this);
  }

  public void setMAngularVelocity(SWIGTYPE_p_NxVec3 value) {
    MyoushuJNI.ActorParams_mAngularVelocity_set(swigCPtr, this, SWIGTYPE_p_NxVec3.getCPtr(value));
  }

  public SWIGTYPE_p_NxVec3 getMAngularVelocity() {
    return new SWIGTYPE_p_NxVec3(MyoushuJNI.ActorParams_mAngularVelocity_get(swigCPtr, this), true);
  }

  public void setMCCDMotionThreshold(float value) {
    MyoushuJNI.ActorParams_mCCDMotionThreshold_set(swigCPtr, this, value);
  }

  public float getMCCDMotionThreshold() {
    return MyoushuJNI.ActorParams_mCCDMotionThreshold_get(swigCPtr, this);
  }

  public void setMBodyFlags(long value) {
    MyoushuJNI.ActorParams_mBodyFlags_set(swigCPtr, this, value);
  }

  public long getMBodyFlags() {
    return MyoushuJNI.ActorParams_mBodyFlags_get(swigCPtr, this);
  }

  public void setMLinearDamping(float value) {
    MyoushuJNI.ActorParams_mLinearDamping_set(swigCPtr, this, value);
  }

  public float getMLinearDamping() {
    return MyoushuJNI.ActorParams_mLinearDamping_get(swigCPtr, this);
  }

  public void setMLinearVelocity(SWIGTYPE_p_NxVec3 value) {
    MyoushuJNI.ActorParams_mLinearVelocity_set(swigCPtr, this, SWIGTYPE_p_NxVec3.getCPtr(value));
  }

  public SWIGTYPE_p_NxVec3 getMLinearVelocity() {
    return new SWIGTYPE_p_NxVec3(MyoushuJNI.ActorParams_mLinearVelocity_get(swigCPtr, this), true);
  }

  public void setMMass(float value) {
    MyoushuJNI.ActorParams_mMass_set(swigCPtr, this, value);
  }

  public float getMMass() {
    return MyoushuJNI.ActorParams_mMass_get(swigCPtr, this);
  }

  public void setMMassLocalPose(SWIGTYPE_p_NxMat34 value) {
    MyoushuJNI.ActorParams_mMassLocalPose_set(swigCPtr, this, SWIGTYPE_p_NxMat34.getCPtr(value));
  }

  public SWIGTYPE_p_NxMat34 getMMassLocalPose() {
    return new SWIGTYPE_p_NxMat34(MyoushuJNI.ActorParams_mMassLocalPose_get(swigCPtr, this), true);
  }

  public void setMMassSpaceInertia(SWIGTYPE_p_NxVec3 value) {
    MyoushuJNI.ActorParams_mMassSpaceInertia_set(swigCPtr, this, SWIGTYPE_p_NxVec3.getCPtr(value));
  }

  public SWIGTYPE_p_NxVec3 getMMassSpaceInertia() {
    return new SWIGTYPE_p_NxVec3(MyoushuJNI.ActorParams_mMassSpaceInertia_get(swigCPtr, this), true);
  }

  public void setMMaxAngularVelocity(float value) {
    MyoushuJNI.ActorParams_mMaxAngularVelocity_set(swigCPtr, this, value);
  }

  public float getMMaxAngularVelocity() {
    return MyoushuJNI.ActorParams_mMaxAngularVelocity_get(swigCPtr, this);
  }

  public void setMSleepAngularVelocity(float value) {
    MyoushuJNI.ActorParams_mSleepAngularVelocity_set(swigCPtr, this, value);
  }

  public float getMSleepAngularVelocity() {
    return MyoushuJNI.ActorParams_mSleepAngularVelocity_get(swigCPtr, this);
  }

  public void setMSleepDamping(float value) {
    MyoushuJNI.ActorParams_mSleepDamping_set(swigCPtr, this, value);
  }

  public float getMSleepDamping() {
    return MyoushuJNI.ActorParams_mSleepDamping_get(swigCPtr, this);
  }

  public void setMSleepEnergyThreshold(float value) {
    MyoushuJNI.ActorParams_mSleepEnergyThreshold_set(swigCPtr, this, value);
  }

  public float getMSleepEnergyThreshold() {
    return MyoushuJNI.ActorParams_mSleepEnergyThreshold_get(swigCPtr, this);
  }

  public void setMSleepLinearVelocity(float value) {
    MyoushuJNI.ActorParams_mSleepLinearVelocity_set(swigCPtr, this, value);
  }

  public float getMSleepLinearVelocity() {
    return MyoushuJNI.ActorParams_mSleepLinearVelocity_get(swigCPtr, this);
  }

  public void setMSolverIterationCount(long value) {
    MyoushuJNI.ActorParams_mSolverIterationCount_set(swigCPtr, this, value);
  }

  public long getMSolverIterationCount() {
    return MyoushuJNI.ActorParams_mSolverIterationCount_get(swigCPtr, this);
  }

  public void setMWakeUpCounter(float value) {
    MyoushuJNI.ActorParams_mWakeUpCounter_set(swigCPtr, this, value);
  }

  public float getMWakeUpCounter() {
    return MyoushuJNI.ActorParams_mWakeUpCounter_get(swigCPtr, this);
  }

  public void setMNodeName(String value) {
    MyoushuJNI.ActorParams_mNodeName_set(swigCPtr, this, value);
  }

  public String getMNodeName() {
    return MyoushuJNI.ActorParams_mNodeName_get(swigCPtr, this);
  }

  public void setMNodeScale(Vector3 value) {
    MyoushuJNI.ActorParams_mNodeScale_set(swigCPtr, this, Vector3.getCPtr(value), value);
  }

  public Vector3 getMNodeScale() {
    long cPtr = MyoushuJNI.ActorParams_mNodeScale_get(swigCPtr, this);
    return (cPtr == 0) ? null : new Vector3(cPtr, false);
  }

  public void setMNodeShadows(boolean value) {
    MyoushuJNI.ActorParams_mNodeShadows_set(swigCPtr, this, value);
  }

  public boolean getMNodeShadows() {
    return MyoushuJNI.ActorParams_mNodeShadows_get(swigCPtr, this);
  }

}
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class Actor extends NxOgre_Actor {
  private long swigCPtr;

  public Actor(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGActorUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(Actor obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_Actor(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

  public Actor(String Identifier, Scene arg1, boolean isActorBased) {
    this(MyoushuJNI.new_Actor__SWIG_0(Identifier, Scene.getCPtr(arg1), arg1, isActorBased), true);
  }

  public Actor(String Identifier, Scene arg1) {
    this(MyoushuJNI.new_Actor__SWIG_1(Identifier, Scene.getCPtr(arg1), arg1), true);
  }

  public Actor(String Identifier, Scene arg1, ShapeBlueprint arg2, Pose arg3, ActorParams arg4) {
    this(MyoushuJNI.new_Actor__SWIG_2(Identifier, Scene.getCPtr(arg1), arg1, ShapeBlueprint.getCPtr(arg2), arg2, Pose.getCPtr(arg3), arg3, ActorParams.getCPtr(arg4), arg4), true);
  }

  public Actor(String Identifier, Scene arg1, ShapeBlueprint arg2, Pose arg3) {
    this(MyoushuJNI.new_Actor__SWIG_3(Identifier, Scene.getCPtr(arg1), arg1, ShapeBlueprint.getCPtr(arg2), arg2, Pose.getCPtr(arg3), arg3), true);
  }

  public String getGroupName() {
    return MyoushuJNI.Actor_getGroupName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.Actor_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.Actor_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.Actor_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.Actor_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_NxScene getNxScene() {
    long cPtr = MyoushuJNI.Actor_getNxScene(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxScene(cPtr, false);
  }

  public boolean hasVisualisation() {
    return MyoushuJNI.Actor_hasVisualisation(swigCPtr, this);
  }

  public void simulate(float arg0) {
    MyoushuJNI.Actor_simulate(swigCPtr, this, arg0);
  }

  public void render(float arg0) {
    MyoushuJNI.Actor_render(swigCPtr, this, arg0);
  }

  public void shapeSimulate(float arg0) {
    MyoushuJNI.Actor_shapeSimulate(swigCPtr, this, arg0);
  }

  public void shapeRender(float arg0) {
    MyoushuJNI.Actor_shapeRender(swigCPtr, this, arg0);
  }

  public boolean isDead() {
    return MyoushuJNI.Actor_isDead(swigCPtr, this);
  }

  public NxOgre_Actor duplicate(String name, Pose p) {
    long cPtr = MyoushuJNI.Actor_duplicate(swigCPtr, this, name, Pose.getCPtr(p), p);
    return (cPtr == 0) ? null : new NxOgre_Actor(cPtr, false);
  }

  public void _createActor(ShapeBlueprint arg0, Pose arg1, ActorParams params) {
    MyoushuJNI.Actor__createActor(swigCPtr, this, ShapeBlueprint.getCPtr(arg0), arg0, Pose.getCPtr(arg1), arg1, ActorParams.getCPtr(params), params);
  }

  public void _destroyActor() {
    MyoushuJNI.Actor__destroyActor(swigCPtr, this);
  }

  public SWIGTYPE_p_NxActor getNxActor() {
    long cPtr = MyoushuJNI.Actor_getNxActor(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxActor(cPtr, false);
  }

  public void setName(String arg0) {
    MyoushuJNI.Actor_setName(swigCPtr, this, arg0);
  }

  public String getName() {
    return MyoushuJNI.Actor_getName(swigCPtr, this);
  }

  public void setGlobalPose(Pose arg0) {
    MyoushuJNI.Actor_setGlobalPose(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public Pose getGlobalPose() {
    return new Pose(MyoushuJNI.Actor_getGlobalPose(swigCPtr, this), true);
  }

  public Quaternion getGlobalOrientation() {
    return new Quaternion(MyoushuJNI.Actor_getGlobalOrientation(swigCPtr, this), true);
  }

  public void setGlobalOrientation(Quaternion arg0) {
    MyoushuJNI.Actor_setGlobalOrientation(swigCPtr, this, Quaternion.getCPtr(arg0), arg0);
  }

  public Vector3 getGlobalPosition() {
    return new Vector3(MyoushuJNI.Actor_getGlobalPosition(swigCPtr, this), true);
  }

  public void setGlobalPosition(Vector3 arg0) {
    MyoushuJNI.Actor_setGlobalPosition(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void moveGlobalPose(Pose arg0) {
    MyoushuJNI.Actor_moveGlobalPose(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public void moveGlobalPosition(Vector3 arg0) {
    MyoushuJNI.Actor_moveGlobalPosition(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void moveGlobalOrientation(Quaternion arg0) {
    MyoushuJNI.Actor_moveGlobalOrientation(swigCPtr, this, Quaternion.getCPtr(arg0), arg0);
  }

  public void moveTowards(Pose arg0, float force) {
    MyoushuJNI.Actor_moveTowards__SWIG_0(swigCPtr, this, Pose.getCPtr(arg0), arg0, force);
  }

  public void moveTowards(Pose arg0) {
    MyoushuJNI.Actor_moveTowards__SWIG_1(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public Shape addShape(ShapeBlueprint arg0) {
    long cPtr = MyoushuJNI.Actor_addShape(swigCPtr, this, ShapeBlueprint.getCPtr(arg0), arg0);
    return (cPtr == 0) ? null : new Shape(cPtr, false);
  }

  public void removeShape(Shape arg0) {
    MyoushuJNI.Actor_removeShape__SWIG_0(swigCPtr, this, Shape.getCPtr(arg0), arg0);
  }

  public void removeShape(long arg0) {
    MyoushuJNI.Actor_removeShape__SWIG_1(swigCPtr, this, arg0);
  }

  public long getNbShapes() {
    return MyoushuJNI.Actor_getNbShapes(swigCPtr, this);
  }

  public SWIGTYPE_p_NxOgre__ContainerT_unsigned_int_NxOgre__Shape_p_t getCollisionModel() {
    long cPtr = MyoushuJNI.Actor_getCollisionModel(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ContainerT_unsigned_int_NxOgre__Shape_p_t(cPtr, false);
  }

  public SWIGTYPE_p_NxOgre__ContainerT_unsigned_int_NxOgre__Shape_p_t getDynamicCollisionModel() {
    long cPtr = MyoushuJNI.Actor_getDynamicCollisionModel(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ContainerT_unsigned_int_NxOgre__Shape_p_t(cPtr, false);
  }

  public void setGroup(SWIGTYPE_p_NxOgre__ActorGroup arg0) {
    MyoushuJNI.Actor_setGroup__SWIG_0(swigCPtr, this, SWIGTYPE_p_NxOgre__ActorGroup.getCPtr(arg0));
  }

  public void setGroup(String GroupIdentifier) {
    MyoushuJNI.Actor_setGroup__SWIG_1(swigCPtr, this, GroupIdentifier);
  }

  public void setGroup(SWIGTYPE_p_NxActorGroup arg0) {
    MyoushuJNI.Actor_setGroup__SWIG_2(swigCPtr, this, SWIGTYPE_p_NxActorGroup.getCPtr(arg0));
  }

  public SWIGTYPE_p_NxOgre__ActorGroup getGroup() {
    long cPtr = MyoushuJNI.Actor_getGroup(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__ActorGroup(cPtr, false);
  }

  public void raiseActorFlag(SWIGTYPE_p_NxActorFlag arg0) {
    MyoushuJNI.Actor_raiseActorFlag(swigCPtr, this, SWIGTYPE_p_NxActorFlag.getCPtr(arg0));
  }

  public void clearActorFlag(SWIGTYPE_p_NxActorFlag arg0) {
    MyoushuJNI.Actor_clearActorFlag(swigCPtr, this, SWIGTYPE_p_NxActorFlag.getCPtr(arg0));
  }

  public boolean hasActorFlag(SWIGTYPE_p_NxActorFlag arg0) {
    return MyoushuJNI.Actor_hasActorFlag(swigCPtr, this, SWIGTYPE_p_NxActorFlag.getCPtr(arg0));
  }

  public boolean isDynamic() {
    return MyoushuJNI.Actor_isDynamic(swigCPtr, this);
  }

  public void setCMassOffsetLocalPose(Pose arg0) {
    MyoushuJNI.Actor_setCMassOffsetLocalPose(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public void setCMassOffsetLocalPosition(Vector3 arg0) {
    MyoushuJNI.Actor_setCMassOffsetLocalPosition(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void setCMassOffsetLocalOrientation(SWIGTYPE_p_NxMat33 arg0) {
    MyoushuJNI.Actor_setCMassOffsetLocalOrientation__SWIG_0(swigCPtr, this, SWIGTYPE_p_NxMat33.getCPtr(arg0));
  }

  public void setCMassOffsetLocalOrientation(Matrix3 arg0) {
    MyoushuJNI.Actor_setCMassOffsetLocalOrientation__SWIG_1(swigCPtr, this, Matrix3.getCPtr(arg0), arg0);
  }

  public void setCMassOffsetGlobalPose(Pose arg0) {
    MyoushuJNI.Actor_setCMassOffsetGlobalPose(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public void setCMassOffsetGlobalPosition(Vector3 arg0) {
    MyoushuJNI.Actor_setCMassOffsetGlobalPosition(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void setCMassOffsetGlobalOrientation(SWIGTYPE_p_NxMat33 arg0) {
    MyoushuJNI.Actor_setCMassOffsetGlobalOrientation__SWIG_0(swigCPtr, this, SWIGTYPE_p_NxMat33.getCPtr(arg0));
  }

  public void setCMassOffsetGlobalOrientation(Matrix3 arg0) {
    MyoushuJNI.Actor_setCMassOffsetGlobalOrientation__SWIG_1(swigCPtr, this, Matrix3.getCPtr(arg0), arg0);
  }

  public void setCMassGlobalPose(Pose arg0) {
    MyoushuJNI.Actor_setCMassGlobalPose(swigCPtr, this, Pose.getCPtr(arg0), arg0);
  }

  public void setCMassGlobalPosition(Vector3 arg0) {
    MyoushuJNI.Actor_setCMassGlobalPosition(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void setCMassGlobalOrientation(Quaternion arg0) {
    MyoushuJNI.Actor_setCMassGlobalOrientation(swigCPtr, this, Quaternion.getCPtr(arg0), arg0);
  }

  public Pose getCMassLocalPose() {
    return new Pose(MyoushuJNI.Actor_getCMassLocalPose(swigCPtr, this), true);
  }

  public Vector3 getCMassLocalPosition() {
    return new Vector3(MyoushuJNI.Actor_getCMassLocalPosition(swigCPtr, this), true);
  }

  public Quaternion getCMassLocalOrientation() {
    return new Quaternion(MyoushuJNI.Actor_getCMassLocalOrientation(swigCPtr, this), true);
  }

  public Pose getCMassGlobalPose() {
    return new Pose(MyoushuJNI.Actor_getCMassGlobalPose(swigCPtr, this), true);
  }

  public Vector3 getCMassGlobalPosition() {
    return new Vector3(MyoushuJNI.Actor_getCMassGlobalPosition(swigCPtr, this), true);
  }

  public Quaternion getCMassGlobalOrientation() {
    return new Quaternion(MyoushuJNI.Actor_getCMassGlobalOrientation(swigCPtr, this), true);
  }

  public void setMass(float arg0) {
    MyoushuJNI.Actor_setMass(swigCPtr, this, arg0);
  }

  public float getMass() {
    return MyoushuJNI.Actor_getMass(swigCPtr, this);
  }

  public void setMassSpaceInertiaTensor(Vector3 arg0) {
    MyoushuJNI.Actor_setMassSpaceInertiaTensor(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public Vector3 getMassSpaceInertiaTensor() {
    return new Vector3(MyoushuJNI.Actor_getMassSpaceInertiaTensor(swigCPtr, this), true);
  }

  public Matrix3 getGlobalInertiaTensor() {
    return new Matrix3(MyoushuJNI.Actor_getGlobalInertiaTensor(swigCPtr, this), true);
  }

  public Matrix3 getGlobalInertiaTensorInverse() {
    return new Matrix3(MyoushuJNI.Actor_getGlobalInertiaTensorInverse(swigCPtr, this), true);
  }

  public void updateMassFromShapeFromDensity(float arg0) {
    MyoushuJNI.Actor_updateMassFromShapeFromDensity(swigCPtr, this, arg0);
  }

  public void updateMassFromShapeAsMass(float arg0) {
    MyoushuJNI.Actor_updateMassFromShapeAsMass(swigCPtr, this, arg0);
  }

  public void setLinearDamping(float arg0) {
    MyoushuJNI.Actor_setLinearDamping(swigCPtr, this, arg0);
  }

  public float getLinearDamping() {
    return MyoushuJNI.Actor_getLinearDamping(swigCPtr, this);
  }

  public void setAngularDamping(float arg0) {
    MyoushuJNI.Actor_setAngularDamping(swigCPtr, this, arg0);
  }

  public float getAngularDamping() {
    return MyoushuJNI.Actor_getAngularDamping(swigCPtr, this);
  }

  public void setLinearVelocity(Vector3 arg0) {
    MyoushuJNI.Actor_setLinearVelocity(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void setAngularVelocity(Vector3 arg0) {
    MyoushuJNI.Actor_setAngularVelocity(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public Vector3 getLinearVelocity() {
    return new Vector3(MyoushuJNI.Actor_getLinearVelocity(swigCPtr, this), true);
  }

  public Vector3 getAngularVelocity() {
    return new Vector3(MyoushuJNI.Actor_getAngularVelocity(swigCPtr, this), true);
  }

  public void setMaxAngularVelocity(float arg0) {
    MyoushuJNI.Actor_setMaxAngularVelocity(swigCPtr, this, arg0);
  }

  public float getMaxAngularVelocity() {
    return MyoushuJNI.Actor_getMaxAngularVelocity(swigCPtr, this);
  }

  public void setCCDMotionThreshold(float arg0) {
    MyoushuJNI.Actor_setCCDMotionThreshold(swigCPtr, this, arg0);
  }

  public float getCCDMotionThreshold() {
    return MyoushuJNI.Actor_getCCDMotionThreshold(swigCPtr, this);
  }

  public void setLinearMomentum(Vector3 arg0) {
    MyoushuJNI.Actor_setLinearMomentum(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public void setAngularMomentum(Vector3 arg0) {
    MyoushuJNI.Actor_setAngularMomentum(swigCPtr, this, Vector3.getCPtr(arg0), arg0);
  }

  public Vector3 getLinearMomentum() {
    return new Vector3(MyoushuJNI.Actor_getLinearMomentum(swigCPtr, this), true);
  }

  public Vector3 getAngularMomentum() {
    return new Vector3(MyoushuJNI.Actor_getAngularMomentum(swigCPtr, this), true);
  }

  public void addForceAtPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addForceAtPos__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addForceAtPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addForceAtPos__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addForceAtPos(Vector3 force, Vector3 pos) {
    MyoushuJNI.Actor_addForceAtPos__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos);
  }

  public void addForceAtLocalPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addForceAtLocalPos__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addForceAtLocalPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addForceAtLocalPos__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addForceAtLocalPos(Vector3 force, Vector3 pos) {
    MyoushuJNI.Actor_addForceAtLocalPos__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos);
  }

  public void addLocalForceAtPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addLocalForceAtPos__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addLocalForceAtPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addLocalForceAtPos__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addLocalForceAtPos(Vector3 force, Vector3 pos) {
    MyoushuJNI.Actor_addLocalForceAtPos__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos);
  }

  public void addLocalForceAtLocalPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addLocalForceAtLocalPos__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addLocalForceAtLocalPos(Vector3 force, Vector3 pos, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addLocalForceAtLocalPos__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addLocalForceAtLocalPos(Vector3 force, Vector3 pos) {
    MyoushuJNI.Actor_addLocalForceAtLocalPos__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force, Vector3.getCPtr(pos), pos);
  }

  public void addForce(Vector3 force, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addForce__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addForce(Vector3 force, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addForce__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addForce(Vector3 force) {
    MyoushuJNI.Actor_addForce__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force);
  }

  public void addLocalForce(Vector3 force, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addLocalForce__SWIG_0(swigCPtr, this, Vector3.getCPtr(force), force, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addLocalForce(Vector3 force, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addLocalForce__SWIG_1(swigCPtr, this, Vector3.getCPtr(force), force, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addLocalForce(Vector3 force) {
    MyoushuJNI.Actor_addLocalForce__SWIG_2(swigCPtr, this, Vector3.getCPtr(force), force);
  }

  public void addTorque(Vector3 torque, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addTorque__SWIG_0(swigCPtr, this, Vector3.getCPtr(torque), torque, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addTorque(Vector3 torque, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addTorque__SWIG_1(swigCPtr, this, Vector3.getCPtr(torque), torque, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addTorque(Vector3 torque) {
    MyoushuJNI.Actor_addTorque__SWIG_2(swigCPtr, this, Vector3.getCPtr(torque), torque);
  }

  public void addLocalTorque(Vector3 torque, SWIGTYPE_p_NxForceMode mode, boolean wakeup) {
    MyoushuJNI.Actor_addLocalTorque__SWIG_0(swigCPtr, this, Vector3.getCPtr(torque), torque, SWIGTYPE_p_NxForceMode.getCPtr(mode), wakeup);
  }

  public void addLocalTorque(Vector3 torque, SWIGTYPE_p_NxForceMode mode) {
    MyoushuJNI.Actor_addLocalTorque__SWIG_1(swigCPtr, this, Vector3.getCPtr(torque), torque, SWIGTYPE_p_NxForceMode.getCPtr(mode));
  }

  public void addLocalTorque(Vector3 torque) {
    MyoushuJNI.Actor_addLocalTorque__SWIG_2(swigCPtr, this, Vector3.getCPtr(torque), torque);
  }

  public float computeKineticEnergy() {
    return MyoushuJNI.Actor_computeKineticEnergy(swigCPtr, this);
  }

  public Vector3 getPointVelocity(Vector3 point) {
    return new Vector3(MyoushuJNI.Actor_getPointVelocity(swigCPtr, this, Vector3.getCPtr(point), point), true);
  }

  public Vector3 getLocalPointVelocity(Vector3 point) {
    return new Vector3(MyoushuJNI.Actor_getLocalPointVelocity(swigCPtr, this, Vector3.getCPtr(point), point), true);
  }

  public boolean isGroupSleeping() {
    return MyoushuJNI.Actor_isGroupSleeping(swigCPtr, this);
  }

  public boolean isSleeping() {
    return MyoushuJNI.Actor_isSleeping(swigCPtr, this);
  }

  public float getSleepLinearVelocity() {
    return MyoushuJNI.Actor_getSleepLinearVelocity(swigCPtr, this);
  }

  public void setSleepLinearVelocity(float threshold) {
    MyoushuJNI.Actor_setSleepLinearVelocity(swigCPtr, this, threshold);
  }

  public float getSleepAngularVelocity() {
    return MyoushuJNI.Actor_getSleepAngularVelocity(swigCPtr, this);
  }

  public void setSleepAngularVelocity(float threshold) {
    MyoushuJNI.Actor_setSleepAngularVelocity(swigCPtr, this, threshold);
  }

  public float getSleepEnergyThreshold() {
    return MyoushuJNI.Actor_getSleepEnergyThreshold(swigCPtr, this);
  }

  public void setSleepEnergyThreshold(float threshold) {
    MyoushuJNI.Actor_setSleepEnergyThreshold(swigCPtr, this, threshold);
  }

  public void wakeUp(float wakeCounterValue) {
    MyoushuJNI.Actor_wakeUp__SWIG_0(swigCPtr, this, wakeCounterValue);
  }

  public void wakeUp() {
    MyoushuJNI.Actor_wakeUp__SWIG_1(swigCPtr, this);
  }

  public void putToSleep() {
    MyoushuJNI.Actor_putToSleep(swigCPtr, this);
  }

  public void raiseBodyFlag(SWIGTYPE_p_NxBodyFlag arg0) {
    MyoushuJNI.Actor_raiseBodyFlag(swigCPtr, this, SWIGTYPE_p_NxBodyFlag.getCPtr(arg0));
  }

  public void clearBodyFlag(SWIGTYPE_p_NxBodyFlag arg0) {
    MyoushuJNI.Actor_clearBodyFlag(swigCPtr, this, SWIGTYPE_p_NxBodyFlag.getCPtr(arg0));
  }

  public boolean hasBodyFlag(SWIGTYPE_p_NxBodyFlag arg0) {
    return MyoushuJNI.Actor_hasBodyFlag(swigCPtr, this, SWIGTYPE_p_NxBodyFlag.getCPtr(arg0));
  }

  public void setSolverIterationCount(long arg0) {
    MyoushuJNI.Actor_setSolverIterationCount(swigCPtr, this, arg0);
  }

  public long getSolverIterationCount() {
    return MyoushuJNI.Actor_getSolverIterationCount(swigCPtr, this);
  }

  public SWIGTYPE_p_void getNxActorUserData() {
    long cPtr = MyoushuJNI.Actor_getNxActorUserData(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public SWIGTYPE_p_NxOgre__FixedJoint joinWith(NxOgre_Actor arg0, SWIGTYPE_p_NxOgre__JointParams arg1) {
    long cPtr = MyoushuJNI.Actor_joinWith(swigCPtr, this, NxOgre_Actor.getCPtr(arg0), arg0, SWIGTYPE_p_NxOgre__JointParams.getCPtr(arg1));
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxOgre__FixedJoint(cPtr, false);
  }

  public void disable() {
    MyoushuJNI.Actor_disable(swigCPtr, this);
  }

  public void disableVisualisation() {
    MyoushuJNI.Actor_disableVisualisation(swigCPtr, this);
  }

  public long getBirthFrame() {
    return MyoushuJNI.Actor_getBirthFrame(swigCPtr, this);
  }

  public StringPairList saveCustom() {
    return new StringPairList(MyoushuJNI.Actor_saveCustom(swigCPtr, this), true);
  }

  public void restoreCustom(StringPairList arg0) {
    MyoushuJNI.Actor_restoreCustom(swigCPtr, this, StringPairList.getCPtr(arg0), arg0);
  }

}

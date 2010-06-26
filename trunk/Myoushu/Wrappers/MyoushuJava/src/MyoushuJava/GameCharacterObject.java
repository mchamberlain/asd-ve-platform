/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameCharacterObject extends GameObject {
  private long swigCPtr;

  public GameCharacterObject(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameCharacterObjectUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameCharacterObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameCharacterObject(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GameCharacterObject(String name, Scene scene, NxOgre_Character nxOgreCharacter, CharacterParams params) {
    this(MyoushuJNI.new_GameCharacterObject__SWIG_0(name, Scene.getCPtr(scene), scene, NxOgre_Character.getCPtr(nxOgreCharacter), nxOgreCharacter, CharacterParams.getCPtr(params), params), true);
  }

  public GameCharacterObject(String name, Scene scene, CharacterController characterController, Pose pose, CharacterParams params) {
    this(MyoushuJNI.new_GameCharacterObject__SWIG_1(name, Scene.getCPtr(scene), scene, CharacterController.getCPtr(characterController), characterController, Pose.getCPtr(pose), pose, CharacterParams.getCPtr(params), params), true);
  }

  public String getClassName() {
    return MyoushuJNI.GameCharacterObject_getClassName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObject_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObject_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObject_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObject_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public GameCharacterObjectAction addAction(String name, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour, boolean restartAnimation, boolean playCounter) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_0(swigCPtr, this, name, toggleAction, animationName, animBehaviour.swigValue(), restartAnimation, playCounter);
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public GameCharacterObjectAction addAction(String name, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour, boolean restartAnimation) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_1(swigCPtr, this, name, toggleAction, animationName, animBehaviour.swigValue(), restartAnimation);
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public GameCharacterObjectAction addAction(String name, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_2(swigCPtr, this, name, toggleAction, animationName, animBehaviour.swigValue());
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public GameCharacterObjectAction addAction(String name, boolean toggleAction, String animationName) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_3(swigCPtr, this, name, toggleAction, animationName);
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public GameCharacterObjectAction addAction(String name, boolean toggleAction) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_4(swigCPtr, this, name, toggleAction);
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public GameCharacterObjectAction addAction(String name) {
    long cPtr = MyoushuJNI.GameCharacterObject_addAction__SWIG_5(swigCPtr, this, name);
    return (cPtr == 0) ? null : new GameCharacterObjectAction(cPtr, false);
  }

  public void createNode() {
    MyoushuJNI.GameCharacterObject_createNode(swigCPtr, this);
  }

  public void attachMesh(String meshName) {
    MyoushuJNI.GameCharacterObject_attachMesh(swigCPtr, this, meshName);
  }

  public void attachSkeletonMesh(String meshName) {
    MyoushuJNI.GameCharacterObject_attachSkeletonMesh(swigCPtr, this, meshName);
  }

  public void bindFeet(String leftBone, String rightBone) {
    MyoushuJNI.GameCharacterObject_bindFeet(swigCPtr, this, leftBone, rightBone);
  }

  public void unBindFeet() {
    MyoushuJNI.GameCharacterObject_unBindFeet(swigCPtr, this);
  }

  public Vector3 getGlobalUpVector() {
    return new Vector3(MyoushuJNI.GameCharacterObject_getGlobalUpVector(swigCPtr, this), true);
  }

  public Vector3 getGlobalForwardVector() {
    return new Vector3(MyoushuJNI.GameCharacterObject_getGlobalForwardVector(swigCPtr, this), true);
  }

  public Vector3 getGlobalPosition() {
    return new Vector3(MyoushuJNI.GameCharacterObject_getGlobalPosition(swigCPtr, this), true);
  }

  public Quaternion getGlobalOrientation() {
    return new Quaternion(MyoushuJNI.GameCharacterObject_getGlobalOrientation(swigCPtr, this), true);
  }

  public void simulate(float dt) {
    MyoushuJNI.GameCharacterObject_simulate(swigCPtr, this, dt);
  }

  public void render(float dt) {
    MyoushuJNI.GameCharacterObject_render(swigCPtr, this, dt);
  }

  public void playAnimation(String animationName, boolean restart, boolean loop, boolean playCounter) {
    MyoushuJNI.GameCharacterObject_playAnimation__SWIG_0(swigCPtr, this, animationName, restart, loop, playCounter);
  }

  public void playAnimation(String animationName, boolean restart, boolean loop) {
    MyoushuJNI.GameCharacterObject_playAnimation__SWIG_1(swigCPtr, this, animationName, restart, loop);
  }

  public void playAnimation(String animationName, boolean restart) {
    MyoushuJNI.GameCharacterObject_playAnimation__SWIG_2(swigCPtr, this, animationName, restart);
  }

  public void playAnimation(String animationName) {
    MyoushuJNI.GameCharacterObject_playAnimation__SWIG_3(swigCPtr, this, animationName);
  }

  public void stopAnimation(String animationName, boolean playCounter) {
    MyoushuJNI.GameCharacterObject_stopAnimation__SWIG_0(swigCPtr, this, animationName, playCounter);
  }

  public void stopAnimation(String animationName) {
    MyoushuJNI.GameCharacterObject_stopAnimation__SWIG_1(swigCPtr, this, animationName);
  }

  public void setDirection(Radian direction) {
    MyoushuJNI.GameCharacterObject_setDirection__SWIG_0(swigCPtr, this, Radian.getCPtr(direction), direction);
  }

  public void setDirection(Quaternion direction) {
    MyoushuJNI.GameCharacterObject_setDirection__SWIG_1(swigCPtr, this, Quaternion.getCPtr(direction), direction);
  }

  public void setMovementDirection(Vector3 direction) {
    MyoushuJNI.GameCharacterObject_setMovementDirection(swigCPtr, this, Vector3.getCPtr(direction), direction);
  }

  public void setMovementVectorController(CharacterMovementVectorController movementVectorController) {
    MyoushuJNI.GameCharacterObject_setMovementVectorController(swigCPtr, this, CharacterMovementVectorController.getCPtr(movementVectorController), movementVectorController);
  }

  public void setPosition(Vector3 position) {
    MyoushuJNI.GameCharacterObject_setPosition(swigCPtr, this, Vector3.getCPtr(position), position);
  }

  public String getName() {
    return MyoushuJNI.GameCharacterObject_getName(swigCPtr, this);
  }

  public SceneNode getNode() {
    long cPtr = MyoushuJNI.GameCharacterObject_getNode__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new SceneNode(cPtr, false);
  }

  public Entity getEntity() {
    long cPtr = MyoushuJNI.GameCharacterObject_getEntity(swigCPtr, this);
    return (cPtr == 0) ? null : new Entity(cPtr, false);
  }

  public Scene getScene() {
    long cPtr = MyoushuJNI.GameCharacterObject_getScene(swigCPtr, this);
    return (cPtr == 0) ? null : new Scene(cPtr, false);
  }

  public SWIGTYPE_p_NxController getNxController() {
    long cPtr = MyoushuJNI.GameCharacterObject_getNxController(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxController(cPtr, false);
  }

  public float getMass() {
    return MyoushuJNI.GameCharacterObject_getMass(swigCPtr, this);
  }

}

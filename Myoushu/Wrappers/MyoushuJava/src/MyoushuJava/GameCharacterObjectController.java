/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameCharacterObjectController extends MoveableObjectController {
  private long swigCPtr;

  public GameCharacterObjectController(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameCharacterObjectControllerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameCharacterObjectController obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameCharacterObjectController(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GameCharacterObjectController() {
    this(MyoushuJNI.new_GameCharacterObjectController__SWIG_0(), true);
  }

  public GameCharacterObjectController(String name, GameCharacterObject character) {
    this(MyoushuJNI.new_GameCharacterObjectController__SWIG_1(name, GameCharacterObject.getCPtr(character), character), true);
  }

  public GameCharacterObjectController(String name, GameCharacterObject character, float maxMovementSpeed, float movementAcceleration, float maxRotationSpeed, float rotationAcceleration) {
    this(MyoushuJNI.new_GameCharacterObjectController__SWIG_2(name, GameCharacterObject.getCPtr(character), character, maxMovementSpeed, movementAcceleration, maxRotationSpeed, rotationAcceleration), true);
  }

  public String getClassName() {
    return MyoushuJNI.GameCharacterObjectController_getClassName(swigCPtr, this);
  }

  public void stop() {
    MyoushuJNI.GameCharacterObjectController_stop(swigCPtr, this);
  }

  public void bind(String inputAction, String characterAction, Vector3 direction, Vector3 rotationAxis, int deviceAxis, boolean once) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_0(swigCPtr, this, inputAction, characterAction, Vector3.getCPtr(direction), direction, Vector3.getCPtr(rotationAxis), rotationAxis, deviceAxis, once);
  }

  public void bind(String inputAction, String characterAction, Vector3 direction, Vector3 rotationAxis, int deviceAxis) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_1(swigCPtr, this, inputAction, characterAction, Vector3.getCPtr(direction), direction, Vector3.getCPtr(rotationAxis), rotationAxis, deviceAxis);
  }

  public void bind(String inputAction, String characterAction, Vector3 direction, Vector3 rotationAxis) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_2(swigCPtr, this, inputAction, characterAction, Vector3.getCPtr(direction), direction, Vector3.getCPtr(rotationAxis), rotationAxis);
  }

  public void bind(String inputAction, String characterAction, Vector3 direction) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_3(swigCPtr, this, inputAction, characterAction, Vector3.getCPtr(direction), direction);
  }

  public void bind(String inputAction, String characterAction, boolean once) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_4(swigCPtr, this, inputAction, characterAction, once);
  }

  public void bind(String inputAction, String characterAction) {
    MyoushuJNI.GameCharacterObjectController_bind__SWIG_5(swigCPtr, this, inputAction, characterAction);
  }

  public void processInputAction(InputMessage message) {
    MyoushuJNI.GameCharacterObjectController_processInputAction(swigCPtr, this, InputMessage.getCPtr(message), message);
  }

  public void move(SWIGTYPE_p_NxVec3 out, SWIGTYPE_p_NxVec3 moveVector, SWIGTYPE_p_NxQuat direction, SWIGTYPE_p_NxVec3 g, float t, NxOgre_Character character) {
    MyoushuJNI.GameCharacterObjectController_move(swigCPtr, this, SWIGTYPE_p_NxVec3.getCPtr(out), SWIGTYPE_p_NxVec3.getCPtr(moveVector), SWIGTYPE_p_NxQuat.getCPtr(direction), SWIGTYPE_p_NxVec3.getCPtr(g), t, NxOgre_Character.getCPtr(character), character);
  }

  public void update(long timeDelta) {
    MyoushuJNI.GameCharacterObjectController_update(swigCPtr, this, timeDelta);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectController_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectController_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectController_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectController_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}

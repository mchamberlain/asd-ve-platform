/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ControllerFactory extends NamedObjectFactory_Controller {
  private long swigCPtr;

  public ControllerFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGControllerFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ControllerFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ControllerFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ControllerFactory() {
    this(MyoushuJNI.new_ControllerFactory(), true);
  }

  public GameCharacterObjectController make(String name, GameCharacterObject character) {
    long cPtr = MyoushuJNI.ControllerFactory_make__SWIG_0(swigCPtr, this, name, GameCharacterObject.getCPtr(character), character);
    return (cPtr == 0) ? null : new GameCharacterObjectController(cPtr, false);
  }

  public CameraWithGameObjectController make(String name, Camera pCamera, GameObject pGameObject) {
    long cPtr = MyoushuJNI.ControllerFactory_make__SWIG_1(swigCPtr, this, name, Camera.getCPtr(pCamera), pCamera, GameObject.getCPtr(pGameObject), pGameObject);
    return (cPtr == 0) ? null : new CameraWithGameObjectController(cPtr, false);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset, double cameraDistance, double maxMovementSpeed, double movementAcceleration, double maxRotationSpeed, double rotationAcceleration) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_0(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset, cameraDistance, maxMovementSpeed, movementAcceleration, maxRotationSpeed, rotationAcceleration);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset, double cameraDistance, double maxMovementSpeed, double movementAcceleration, double maxRotationSpeed) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_1(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset, cameraDistance, maxMovementSpeed, movementAcceleration, maxRotationSpeed);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset, double cameraDistance, double maxMovementSpeed, double movementAcceleration) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_2(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset, cameraDistance, maxMovementSpeed, movementAcceleration);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset, double cameraDistance, double maxMovementSpeed) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_3(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset, cameraDistance, maxMovementSpeed);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset, double cameraDistance) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_4(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset, cameraDistance);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction, Vector3 cameraOffset) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_5(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction, Vector3.getCPtr(cameraOffset), cameraOffset);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction, String strafeRightCharacterAction) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_6(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction, strafeRightCharacterAction);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction, String strafeLeftCharacterAction) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_7(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction, strafeLeftCharacterAction);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction, String backwardCharacterAction) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_8(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction, backwardCharacterAction);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction, String forwardCharacterAction) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_9(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction, forwardCharacterAction);
  }

  public void makeGameCharacterObjectCameraControllerPair(String cameraControllerName, String characterControllerName, GameCharacterObject pCharacter, Camera pCamera, String moveForwardAction, String moveBackwardAction, String strafeLeftAction, String strafeRightAction, String lookUpAction, String lookDownAction, String lookLeftAction, String lookRightAction) {
    MyoushuJNI.ControllerFactory_makeGameCharacterObjectCameraControllerPair__SWIG_10(swigCPtr, this, cameraControllerName, characterControllerName, GameCharacterObject.getCPtr(pCharacter), pCharacter, Camera.getCPtr(pCamera), pCamera, moveForwardAction, moveBackwardAction, strafeLeftAction, strafeRightAction, lookUpAction, lookDownAction, lookLeftAction, lookRightAction);
  }

  public boolean destroy(Controller pController) {
    return MyoushuJNI.ControllerFactory_destroy__SWIG_0(swigCPtr, this, Controller.getCPtr(pController), pController);
  }

  public boolean destroy(String name) {
    return MyoushuJNI.ControllerFactory_destroy__SWIG_1(swigCPtr, this, name);
  }

}

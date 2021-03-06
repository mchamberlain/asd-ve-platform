/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class MoveableObjectController extends Controller {
  private long swigCPtr;

  public MoveableObjectController(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGMoveableObjectControllerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(MoveableObjectController obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_MoveableObjectController(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public MoveableObjectController(String name, float maxMovementSpeed, float movementAcceleration, float maxRotationSpeed, float rotationAcceleration) {
    this(MyoushuJNI.new_MoveableObjectController__SWIG_0(name, maxMovementSpeed, movementAcceleration, maxRotationSpeed, rotationAcceleration), true);
  }

  public MoveableObjectController(String name, float maxMovementSpeed, float movementAcceleration, float maxRotationSpeed) {
    this(MyoushuJNI.new_MoveableObjectController__SWIG_1(name, maxMovementSpeed, movementAcceleration, maxRotationSpeed), true);
  }

  public MoveableObjectController(String name, float maxMovementSpeed, float movementAcceleration) {
    this(MyoushuJNI.new_MoveableObjectController__SWIG_2(name, maxMovementSpeed, movementAcceleration), true);
  }

  public MoveableObjectController(String name, float maxMovementSpeed) {
    this(MyoushuJNI.new_MoveableObjectController__SWIG_3(name, maxMovementSpeed), true);
  }

  public MoveableObjectController(String name) {
    this(MyoushuJNI.new_MoveableObjectController__SWIG_4(name), true);
  }

  public float getMovementSpeed() {
    return MyoushuJNI.MoveableObjectController_getMovementSpeed(swigCPtr, this);
  }

  public void setMaxMovementSpeed(float maxMovementSpeed) {
    MyoushuJNI.MoveableObjectController_setMaxMovementSpeed(swigCPtr, this, maxMovementSpeed);
  }

  public float getMaxMovementSpeed() {
    return MyoushuJNI.MoveableObjectController_getMaxMovementSpeed(swigCPtr, this);
  }

  public float getMovementAcceleration() {
    return MyoushuJNI.MoveableObjectController_getMovementAcceleration(swigCPtr, this);
  }

  public void setMovementAcceleration(float movementAcceleration) {
    MyoushuJNI.MoveableObjectController_setMovementAcceleration(swigCPtr, this, movementAcceleration);
  }

  public float getRotationSpeed() {
    return MyoushuJNI.MoveableObjectController_getRotationSpeed(swigCPtr, this);
  }

  public void setMaxRotationSpeed(float maxRotationSpeed) {
    MyoushuJNI.MoveableObjectController_setMaxRotationSpeed(swigCPtr, this, maxRotationSpeed);
  }

  public float getMaxRotationSpeed() {
    return MyoushuJNI.MoveableObjectController_getMaxRotationSpeed(swigCPtr, this);
  }

  public void setRotationAcceleration(float rotationAcceleration) {
    MyoushuJNI.MoveableObjectController_setRotationAcceleration(swigCPtr, this, rotationAcceleration);
  }

  public float getRotationAcceleration() {
    return MyoushuJNI.MoveableObjectController_getRotationAcceleration(swigCPtr, this);
  }

  public void linkSpeedsWith(MoveableObjectController otherController) {
    MyoushuJNI.MoveableObjectController_linkSpeedsWith(swigCPtr, this, MoveableObjectController.getCPtr(otherController), otherController);
  }

  public void stop() {
    MyoushuJNI.MoveableObjectController_stop(swigCPtr, this);
  }

  public void update(long timeDelta) {
    MyoushuJNI.MoveableObjectController_update(swigCPtr, this, timeDelta);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MoveableObjectController_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MoveableObjectController_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MoveableObjectController_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.MoveableObjectController_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}

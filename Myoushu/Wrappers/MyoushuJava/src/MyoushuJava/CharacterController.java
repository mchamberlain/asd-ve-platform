/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class CharacterController extends CharacterMovementVectorController {
  private long swigCPtr;

  public CharacterController(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCharacterControllerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(CharacterController obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        throw new UnsupportedOperationException("C++ destructor does not have public access");
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public NxOgre_Character create(String name, Pose arg1, CharacterParams arg2, SWIGTYPE_p_NxOgre__Scene arg3) {
    long cPtr = MyoushuJNI.CharacterController_create(swigCPtr, this, name, Pose.getCPtr(arg1), arg1, CharacterParams.getCPtr(arg2), arg2, SWIGTYPE_p_NxOgre__Scene.getCPtr(arg3));
    return (cPtr == 0) ? null : new NxOgre_Character(cPtr, false);
  }

  public void destroy(String name) {
    MyoushuJNI.CharacterController_destroy(swigCPtr, this, name);
  }

  public NxOgre_Character get(String name) {
    long cPtr = MyoushuJNI.CharacterController_get(swigCPtr, this, name);
    return (cPtr == 0) ? null : new NxOgre_Character(cPtr, false);
  }

  public SWIGTYPE_p_NxControllerAction onShapeHit(SWIGTYPE_p_NxControllerShapeHit arg0) {
    return new SWIGTYPE_p_NxControllerAction(MyoushuJNI.CharacterController_onShapeHit(swigCPtr, this, SWIGTYPE_p_NxControllerShapeHit.getCPtr(arg0)), true);
  }

  public SWIGTYPE_p_NxControllerAction onControllerHit(SWIGTYPE_p_NxControllersHit arg0) {
    return new SWIGTYPE_p_NxControllerAction(MyoushuJNI.CharacterController_onControllerHit(swigCPtr, this, SWIGTYPE_p_NxControllersHit.getCPtr(arg0)), true);
  }

  public SWIGTYPE_p_NxControllerManager getNxControllerManager() {
    long cPtr = MyoushuJNI.CharacterController_getNxControllerManager(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_NxControllerManager(cPtr, false);
  }

  public void move(SWIGTYPE_p_NxVec3 out, SWIGTYPE_p_NxVec3 moveVector, SWIGTYPE_p_NxVec3 g, float t) {
    MyoushuJNI.CharacterController_move(swigCPtr, this, SWIGTYPE_p_NxVec3.getCPtr(out), SWIGTYPE_p_NxVec3.getCPtr(moveVector), SWIGTYPE_p_NxVec3.getCPtr(g), t);
  }

  public void addHitReport(SWIGTYPE_p_NxOgre__CharacterHitReport report) {
    MyoushuJNI.CharacterController_addHitReport(swigCPtr, this, SWIGTYPE_p_NxOgre__CharacterHitReport.getCPtr(report));
  }

}

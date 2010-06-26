/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameObject extends NamedObject_GameObject {
  private long swigCPtr;

  public GameObject(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameObjectUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameObject obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameObject(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GameObject(String name) {
    this(MyoushuJNI.new_GameObject(name), true);
  }

  public String getClassName() {
    return MyoushuJNI.GameObject_getClassName(swigCPtr, this);
  }

  public void addAction(GameObjectAction action) {
    MyoushuJNI.GameObject_addAction(swigCPtr, this, GameObjectAction.getCPtr(action), action);
  }

  public GameObjectAction getAction(String actionName) {
    long cPtr = MyoushuJNI.GameObject_getAction(swigCPtr, this, actionName);
    return (cPtr == 0) ? null : new GameObjectAction(cPtr, false);
  }

  public boolean startAction(String actionName) {
    return MyoushuJNI.GameObject_startAction(swigCPtr, this, actionName);
  }

  public boolean stopAction(String actionName) {
    return MyoushuJNI.GameObject_stopAction(swigCPtr, this, actionName);
  }

  public KeyValueProperties getProperties() {
    return new KeyValueProperties(MyoushuJNI.GameObject_getProperties__SWIG_0(swigCPtr, this), false);
  }

  public KeyValueProperties getPropertiesPtr() {
    long cPtr = MyoushuJNI.GameObject_getPropertiesPtr__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new KeyValueProperties(cPtr, false);
  }

  public Scene getScene() {
    long cPtr = MyoushuJNI.GameObject_getScene(swigCPtr, this);
    return (cPtr == 0) ? null : new Scene(cPtr, false);
  }

  public Vector3 getGlobalUpVector() {
    return new Vector3(MyoushuJNI.GameObject_getGlobalUpVector(swigCPtr, this), true);
  }

  public Vector3 getLocalUpVector() {
    return new Vector3(MyoushuJNI.GameObject_getLocalUpVector(swigCPtr, this), true);
  }

  public void setLocalUpVector(Vector3 upVector) {
    MyoushuJNI.GameObject_setLocalUpVector(swigCPtr, this, Vector3.getCPtr(upVector), upVector);
  }

  public Vector3 getGlobalForwardVector() {
    return new Vector3(MyoushuJNI.GameObject_getGlobalForwardVector(swigCPtr, this), true);
  }

  public Vector3 getLocalForwardVector() {
    return new Vector3(MyoushuJNI.GameObject_getLocalForwardVector(swigCPtr, this), true);
  }

  public void setLocalForwardVector(Vector3 forwardVector) {
    MyoushuJNI.GameObject_setLocalForwardVector(swigCPtr, this, Vector3.getCPtr(forwardVector), forwardVector);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameObject_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameObject_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameObject_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameObject_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

}

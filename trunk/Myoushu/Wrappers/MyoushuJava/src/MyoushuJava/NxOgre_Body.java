/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class NxOgre_Body extends NxOgre_Actor {
  private long swigCPtr;

  public NxOgre_Body(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGNxOgre_BodyUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(NxOgre_Body obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_NxOgre_Body(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public NxOgre_Body(String name, SWIGTYPE_p_NxOgre__Scene arg1) {
    this(MyoushuJNI.new_NxOgre_Body__SWIG_0(name, SWIGTYPE_p_NxOgre__Scene.getCPtr(arg1)), true);
  }

  public NxOgre_Body(String name, SWIGTYPE_p_NxOgre__Scene arg1, ShapeBlueprint arg2, Pose arg3, ActorParams arg4) {
    this(MyoushuJNI.new_NxOgre_Body__SWIG_1(name, SWIGTYPE_p_NxOgre__Scene.getCPtr(arg1), ShapeBlueprint.getCPtr(arg2), arg2, Pose.getCPtr(arg3), arg3, ActorParams.getCPtr(arg4), arg4), true);
  }

  public NxOgre_Body(String name, SWIGTYPE_p_NxOgre__Scene arg1, ShapeBlueprint arg2, Pose arg3) {
    this(MyoushuJNI.new_NxOgre_Body__SWIG_2(name, SWIGTYPE_p_NxOgre__Scene.getCPtr(arg1), ShapeBlueprint.getCPtr(arg2), arg2, Pose.getCPtr(arg3), arg3), true);
  }

  public boolean hasVisualisation() {
    return MyoushuJNI.NxOgre_Body_hasVisualisation(swigCPtr, this);
  }

  public SceneNode getNode() {
    long cPtr = MyoushuJNI.NxOgre_Body_getNode(swigCPtr, this);
    return (cPtr == 0) ? null : new SceneNode(cPtr, false);
  }

  public Entity getEntity() {
    long cPtr = MyoushuJNI.NxOgre_Body_getEntity(swigCPtr, this);
    return (cPtr == 0) ? null : new Entity(cPtr, false);
  }

  public void setNode(SceneNode arg0) {
    MyoushuJNI.NxOgre_Body_setNode(swigCPtr, this, SceneNode.getCPtr(arg0), arg0);
  }

  public void setEntity(Entity arg0) {
    MyoushuJNI.NxOgre_Body_setEntity(swigCPtr, this, Entity.getCPtr(arg0), arg0);
  }

  public void simulate(float arg0) {
    MyoushuJNI.NxOgre_Body_simulate(swigCPtr, this, arg0);
  }

  public void render(float arg0) {
    MyoushuJNI.NxOgre_Body_render(swigCPtr, this, arg0);
  }

  public StringPairList saveCustom() {
    return new StringPairList(MyoushuJNI.NxOgre_Body_saveCustom(swigCPtr, this), true);
  }

  public void restoreCustom(StringPairList arg0) {
    MyoushuJNI.NxOgre_Body_restoreCustom(swigCPtr, this, StringPairList.getCPtr(arg0), arg0);
  }

  public void disableVisualisation() {
    MyoushuJNI.NxOgre_Body_disableVisualisation(swigCPtr, this);
  }

}

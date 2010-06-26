/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameObjectFactory extends NamedObjectFactory_GameObject {
  private long swigCPtr;

  public GameObjectFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameObjectFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameObjectFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameObjectFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GameObjectFactory() {
    this(MyoushuJNI.new_GameObjectFactory(), true);
  }

  public GameActorObject makeActor(String name, Scene scene, ShapeBlueprint collisionShape, Pose initialPose, ActorParams arg4) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeActor__SWIG_0(swigCPtr, this, name, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose, ActorParams.getCPtr(arg4), arg4);
    return (cPtr == 0) ? null : new GameActorObject(cPtr, false);
  }

  public GameActorObject makeActor(String name, Scene scene, ShapeBlueprint collisionShape, Pose initialPose) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeActor__SWIG_1(swigCPtr, this, name, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose);
    return (cPtr == 0) ? null : new GameActorObject(cPtr, false);
  }

  public GameActorObject makeActor(String name, Scene scene, ShapeBlueprint collisionShape) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeActor__SWIG_2(swigCPtr, this, name, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape);
    return (cPtr == 0) ? null : new GameActorObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, ShapeBlueprint collisionShape, Pose initialPose, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_0(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, ShapeBlueprint collisionShape, Pose initialPose) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_1(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, ShapeBlueprint collisionShape) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_2(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, SceneNode sceneNode, Scene scene, ShapeBlueprint collisionShape, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_3(swigCPtr, this, name, meshName, SceneNode.getCPtr(sceneNode), sceneNode, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, SceneNode sceneNode, Scene scene, ShapeBlueprint collisionShape) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_4(swigCPtr, this, name, meshName, SceneNode.getCPtr(sceneNode), sceneNode, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, SceneNode sceneNode, Entity entity, Scene scene, ShapeBlueprint collisionShape, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_5(swigCPtr, this, name, SceneNode.getCPtr(sceneNode), sceneNode, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, SceneNode sceneNode, Entity entity, Scene scene, ShapeBlueprint collisionShape) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_6(swigCPtr, this, name, SceneNode.getCPtr(sceneNode), sceneNode, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, ShapeBlueprint collisionShape, Pose initialPose, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_7(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, ShapeBlueprint collisionShape, Pose initialPose) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_8(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape, Pose.getCPtr(initialPose), initialPose);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, ShapeBlueprint collisionShape) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_9(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, ShapeBlueprint.getCPtr(collisionShape), collisionShape);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, Pose initialPose, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_10(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, Pose.getCPtr(initialPose), initialPose, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, Pose initialPose) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_11(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, Pose.getCPtr(initialPose), initialPose);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, String collisionShapeFileName, ShapeParams shapeParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_12(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, Scene scene, String collisionShapeFileName) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_13(swigCPtr, this, name, meshName, Scene.getCPtr(scene), scene, collisionShapeFileName);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, SceneNode sceneNode, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_14(swigCPtr, this, name, meshName, SceneNode.getCPtr(sceneNode), sceneNode, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, SceneNode sceneNode, Scene scene, String collisionShapeFileName, ShapeParams shapeParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_15(swigCPtr, this, name, meshName, SceneNode.getCPtr(sceneNode), sceneNode, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, String meshName, SceneNode sceneNode, Scene scene, String collisionShapeFileName) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_16(swigCPtr, this, name, meshName, SceneNode.getCPtr(sceneNode), sceneNode, Scene.getCPtr(scene), scene, collisionShapeFileName);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, SceneNode sceneNode, Entity entity, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_17(swigCPtr, this, name, SceneNode.getCPtr(sceneNode), sceneNode, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, SceneNode sceneNode, Entity entity, Scene scene, String collisionShapeFileName, ShapeParams shapeParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_18(swigCPtr, this, name, SceneNode.getCPtr(sceneNode), sceneNode, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, SceneNode sceneNode, Entity entity, Scene scene, String collisionShapeFileName) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_19(swigCPtr, this, name, SceneNode.getCPtr(sceneNode), sceneNode, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, Pose initialPose, ActorParams actorParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_20(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, Pose.getCPtr(initialPose), initialPose, ActorParams.getCPtr(actorParams), actorParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, String collisionShapeFileName, ShapeParams shapeParams, Pose initialPose) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_21(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams, Pose.getCPtr(initialPose), initialPose);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, String collisionShapeFileName, ShapeParams shapeParams) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_22(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName, ShapeParams.getCPtr(shapeParams), shapeParams);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameBodyObject makeBody(String name, Entity entity, Scene scene, String collisionShapeFileName) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeBody__SWIG_23(swigCPtr, this, name, Entity.getCPtr(entity), entity, Scene.getCPtr(scene), scene, collisionShapeFileName);
    return (cPtr == 0) ? null : new GameBodyObject(cPtr, false);
  }

  public GameCharacterObject makeCharacter(String name, String meshName, String skeletonMeshName, Scene scene, Pose pose, CharacterParams params) {
    long cPtr = MyoushuJNI.GameObjectFactory_makeCharacter(swigCPtr, this, name, meshName, skeletonMeshName, Scene.getCPtr(scene), scene, Pose.getCPtr(pose), pose, CharacterParams.getCPtr(params), params);
    return (cPtr == 0) ? null : new GameCharacterObject(cPtr, false);
  }

  public void destroy(GameObject gameObject) {
    MyoushuJNI.GameObjectFactory_destroy(swigCPtr, this, GameObject.getCPtr(gameObject), gameObject);
  }

  public void destroyAllFromScene(Scene pScene) {
    MyoushuJNI.GameObjectFactory_destroyAllFromScene(swigCPtr, this, Scene.getCPtr(pScene), pScene);
  }

}

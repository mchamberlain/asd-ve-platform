/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class CollisionManager extends Singleton_CollisionManager {
  private long swigCPtr;

  public CollisionManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGCollisionManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(CollisionManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_CollisionManager(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public CollisionManager() {
    this(MyoushuJNI.new_CollisionManager(), true);
  }

  public void setActorGroupsCollidable(Scene pScene, String firstGroupName, String secondGroupName, CollisionManager.ContactPairFlag contactPairFlag, boolean twoWay) {
    MyoushuJNI.CollisionManager_setActorGroupsCollidable__SWIG_0(swigCPtr, this, Scene.getCPtr(pScene), pScene, firstGroupName, secondGroupName, contactPairFlag.swigValue(), twoWay);
  }

  public void setActorGroupsCollidable(Scene pScene, String firstGroupName, String secondGroupName, CollisionManager.ContactPairFlag contactPairFlag) {
    MyoushuJNI.CollisionManager_setActorGroupsCollidable__SWIG_1(swigCPtr, this, Scene.getCPtr(pScene), pScene, firstGroupName, secondGroupName, contactPairFlag.swigValue());
  }

  public CollisionManager.ContactPairFlag getActorGroupsCollidable(Scene pScene, String firstGroupName, String secondGroupName) {
    return CollisionManager.ContactPairFlag.swigToEnum(MyoushuJNI.CollisionManager_getActorGroupsCollidable(swigCPtr, this, Scene.getCPtr(pScene), pScene, firstGroupName, secondGroupName));
  }

  public void onStartTouch(NxOgre_Actor firstActor, NxOgre_Actor secondActor) {
    MyoushuJNI.CollisionManager_onStartTouch(swigCPtr, this, NxOgre_Actor.getCPtr(firstActor), firstActor, NxOgre_Actor.getCPtr(secondActor), secondActor);
  }

  public void onEndTouch(NxOgre_Actor firstActor, NxOgre_Actor secondActor) {
    MyoushuJNI.CollisionManager_onEndTouch(swigCPtr, this, NxOgre_Actor.getCPtr(firstActor), firstActor, NxOgre_Actor.getCPtr(secondActor), secondActor);
  }

  public void onTouch(NxOgre_Actor firstActor, NxOgre_Actor secondActor) {
    MyoushuJNI.CollisionManager_onTouch(swigCPtr, this, NxOgre_Actor.getCPtr(firstActor), firstActor, NxOgre_Actor.getCPtr(secondActor), secondActor);
  }

  public SWIGTYPE_p_NxOgre__CharacterHitReport__Response onActor(NxOgre_Character arg0, NxOgre_Actor arg1, Shape arg2, SWIGTYPE_p_NxOgre__ActorGroup arg3, SWIGTYPE_p_NxControllerShapeHit arg4) {
    return new SWIGTYPE_p_NxOgre__CharacterHitReport__Response(MyoushuJNI.CollisionManager_onActor(swigCPtr, this, NxOgre_Character.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, Shape.getCPtr(arg2), arg2, SWIGTYPE_p_NxOgre__ActorGroup.getCPtr(arg3), SWIGTYPE_p_NxControllerShapeHit.getCPtr(arg4)), true);
  }

  public SWIGTYPE_p_NxOgre__CharacterHitReport__Response onCharacterHit(NxOgre_Character arg0, NxOgre_Actor arg1, Shape arg2, SWIGTYPE_p_NxOgre__ActorGroup arg3, SWIGTYPE_p_NxControllersHit arg4) {
    return new SWIGTYPE_p_NxOgre__CharacterHitReport__Response(MyoushuJNI.CollisionManager_onCharacterHit(swigCPtr, this, NxOgre_Character.getCPtr(arg0), arg0, NxOgre_Actor.getCPtr(arg1), arg1, Shape.getCPtr(arg2), arg2, SWIGTYPE_p_NxOgre__ActorGroup.getCPtr(arg3), SWIGTYPE_p_NxControllersHit.getCPtr(arg4)), true);
  }

  public void setGlobalStartTouchCallback(FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setGlobalStartTouchCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setGlobalStartTouchCallback(String luaFunctionName) {
    MyoushuJNI.CollisionManager_setGlobalStartTouchCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setGlobalEndTouchCallback(FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setGlobalEndTouchCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setGlobalEndTouchCallback(String luaFunctionName) {
    MyoushuJNI.CollisionManager_setGlobalEndTouchCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setGlobalTouchCallback(FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setGlobalTouchCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setGlobalTouchCallback(String luaFunctionName) {
    MyoushuJNI.CollisionManager_setGlobalTouchCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setPerGroupStartTouchCallback(String groupName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerGroupStartTouchCallback__SWIG_0(swigCPtr, this, groupName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerGroupStartTouchCallback(String groupName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerGroupStartTouchCallback__SWIG_1(swigCPtr, this, groupName, luaFunctionName);
  }

  public void setPerGroupEndTouchCallback(String groupName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerGroupEndTouchCallback__SWIG_0(swigCPtr, this, groupName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerGroupEndTouchCallback(String groupName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerGroupEndTouchCallback__SWIG_1(swigCPtr, this, groupName, luaFunctionName);
  }

  public void setPerGroupTouchCallback(String groupName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerGroupTouchCallback__SWIG_0(swigCPtr, this, groupName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerGroupTouchCallback(String groupName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerGroupTouchCallback__SWIG_1(swigCPtr, this, groupName, luaFunctionName);
  }

  public void setPerActorStartTouchCallback(GameActorObject pGameActor, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorStartTouchCallback__SWIG_0(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorStartTouchCallback(String gameActorName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorStartTouchCallback__SWIG_1(swigCPtr, this, gameActorName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorStartTouchCallback(GameActorObject pGameActor, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorStartTouchCallback__SWIG_2(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, luaFunctionName);
  }

  public void setPerActorStartTouchCallback(String gameActorName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorStartTouchCallback__SWIG_3(swigCPtr, this, gameActorName, luaFunctionName);
  }

  public void setPerActorEndTouchCallback(GameActorObject pGameActor, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorEndTouchCallback__SWIG_0(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorEndTouchCallback(String gameActorName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorEndTouchCallback__SWIG_1(swigCPtr, this, gameActorName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorEndTouchCallback(GameActorObject pGameActor, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorEndTouchCallback__SWIG_2(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, luaFunctionName);
  }

  public void setPerActorEndTouchCallback(String gameActorName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorEndTouchCallback__SWIG_3(swigCPtr, this, gameActorName, luaFunctionName);
  }

  public void setPerActorTouchCallback(GameActorObject pGameActor, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorTouchCallback__SWIG_0(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorTouchCallback(String gameActorName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorTouchCallback__SWIG_1(swigCPtr, this, gameActorName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorTouchCallback(GameActorObject pGameActor, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorTouchCallback__SWIG_2(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, luaFunctionName);
  }

  public void setPerActorTouchCallback(String gameActorName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorTouchCallback__SWIG_3(swigCPtr, this, gameActorName, luaFunctionName);
  }

  public void enableActorCharacterCollisionReporting(Scene pScene) {
    MyoushuJNI.CollisionManager_enableActorCharacterCollisionReporting(swigCPtr, this, Scene.getCPtr(pScene), pScene);
  }

  public void setGlobalActorCharacterCallback(FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setGlobalActorCharacterCallback__SWIG_0(swigCPtr, this, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setGlobalActorCharacterCallback(String luaFunctionName) {
    MyoushuJNI.CollisionManager_setGlobalActorCharacterCallback__SWIG_1(swigCPtr, this, luaFunctionName);
  }

  public void setPerGroupCharacterCallback(String groupName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerGroupCharacterCallback__SWIG_0(swigCPtr, this, groupName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerGroupCharacterCallback(String groupName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerGroupCharacterCallback__SWIG_1(swigCPtr, this, groupName, luaFunctionName);
  }

  public void setPerActorCharacterCallback(GameActorObject pGameActor, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorCharacterCallback__SWIG_0(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorCharacterCallback(String gameActorName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerActorCharacterCallback__SWIG_1(swigCPtr, this, gameActorName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerActorCharacterCallback(GameActorObject pGameActor, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorCharacterCallback__SWIG_2(swigCPtr, this, GameActorObject.getCPtr(pGameActor), pGameActor, luaFunctionName);
  }

  public void setPerActorCharacterCallback(String gameActorName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerActorCharacterCallback__SWIG_3(swigCPtr, this, gameActorName, luaFunctionName);
  }

  public void setPerCharacterActorCallback(GameCharacterObject pGameCharacter, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerCharacterActorCallback__SWIG_0(swigCPtr, this, GameCharacterObject.getCPtr(pGameCharacter), pGameCharacter, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerCharacterActorCallback(String gameCharacterName, FunctorBase pCallback) {
    MyoushuJNI.CollisionManager_setPerCharacterActorCallback__SWIG_1(swigCPtr, this, gameCharacterName, FunctorBase.getCPtr(pCallback), pCallback);
  }

  public void setPerCharacterActorCallback(GameCharacterObject pGameCharacter, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerCharacterActorCallback__SWIG_2(swigCPtr, this, GameCharacterObject.getCPtr(pGameCharacter), pGameCharacter, luaFunctionName);
  }

  public void setPerCharacterActorCallback(String gameCharacterName, String luaFunctionName) {
    MyoushuJNI.CollisionManager_setPerCharacterActorCallback__SWIG_3(swigCPtr, this, gameCharacterName, luaFunctionName);
  }

  public enum ContactPairFlag {
    CP_IGNORE_PAIR(MyoushuJNI.CollisionManager_CP_IGNORE_PAIR_get()),
    CP_NOTIFY_ON_START_TOUCH(MyoushuJNI.CollisionManager_CP_NOTIFY_ON_START_TOUCH_get()),
    CP_NOTIFY_ON_END_TOUCH(MyoushuJNI.CollisionManager_CP_NOTIFY_ON_END_TOUCH_get()),
    CP_NOTIFY_ON_TOUCH(MyoushuJNI.CollisionManager_CP_NOTIFY_ON_TOUCH_get()),
    CP_NOTIFY_ALL(MyoushuJNI.CollisionManager_CP_NOTIFY_ALL_get());

    public final int swigValue() {
      return swigValue;
    }

    public static ContactPairFlag swigToEnum(int swigValue) {
      ContactPairFlag[] swigValues = ContactPairFlag.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (ContactPairFlag swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + ContactPairFlag.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private ContactPairFlag() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private ContactPairFlag(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private ContactPairFlag(ContactPairFlag swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

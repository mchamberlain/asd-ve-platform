/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameCharacterObjectAction extends GameObjectAction {
  private long swigCPtr;

  public GameCharacterObjectAction(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameCharacterObjectActionUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameCharacterObjectAction obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameCharacterObjectAction(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public GameCharacterObjectAction() {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_0(), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour, boolean restartAnimation, boolean playCounter) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_1(name, GameCharacterObject.getCPtr(character), character, toggleAction, animationName, animBehaviour.swigValue(), restartAnimation, playCounter), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour, boolean restartAnimation) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_2(name, GameCharacterObject.getCPtr(character), character, toggleAction, animationName, animBehaviour.swigValue(), restartAnimation), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character, boolean toggleAction, String animationName, GameCharacterObjectAction.AnimationBehaviour animBehaviour) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_3(name, GameCharacterObject.getCPtr(character), character, toggleAction, animationName, animBehaviour.swigValue()), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character, boolean toggleAction, String animationName) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_4(name, GameCharacterObject.getCPtr(character), character, toggleAction, animationName), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character, boolean toggleAction) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_5(name, GameCharacterObject.getCPtr(character), character, toggleAction), true);
  }

  public GameCharacterObjectAction(String name, GameCharacterObject character) {
    this(MyoushuJNI.new_GameCharacterObjectAction__SWIG_6(name, GameCharacterObject.getCPtr(character), character), true);
  }

  public String getClassName() {
    return MyoushuJNI.GameCharacterObjectAction_getClassName(swigCPtr, this);
  }

  public GameCharacterObject getGameCharacterObject() {
    long cPtr = MyoushuJNI.GameCharacterObjectAction_getGameCharacterObject(swigCPtr, this);
    return (cPtr == 0) ? null : new GameCharacterObject(cPtr, false);
  }

  public void startAction() {
    MyoushuJNI.GameCharacterObjectAction_startAction(swigCPtr, this);
  }

  public void stopAction() {
    MyoushuJNI.GameCharacterObjectAction_stopAction(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectAction_serialize__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t serialize(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectAction_serialize__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size, Serializable.SerializationTarget sTarget) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectAction_populateInstance__SWIG_0(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size), sTarget.swigValue()), true);
  }

  public SWIGTYPE_p_uint32_t populateInstance(SWIGTYPE_p_void pMem, SWIGTYPE_p_uint32_t size) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameCharacterObjectAction_populateInstance__SWIG_1(swigCPtr, this, SWIGTYPE_p_void.getCPtr(pMem), SWIGTYPE_p_uint32_t.getCPtr(size)), true);
  }

  public enum AnimationBehaviour {
    AM_LOOP,
    AM_ONCE,
    AM_ONE_FRAME,
    AM_NO_ANIMATION;

    public final int swigValue() {
      return swigValue;
    }

    public static AnimationBehaviour swigToEnum(int swigValue) {
      AnimationBehaviour[] swigValues = AnimationBehaviour.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (AnimationBehaviour swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + AnimationBehaviour.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private AnimationBehaviour() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private AnimationBehaviour(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private AnimationBehaviour(AnimationBehaviour swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

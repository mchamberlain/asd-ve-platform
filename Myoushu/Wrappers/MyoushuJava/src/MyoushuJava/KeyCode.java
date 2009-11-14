/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class KeyCode {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public KeyCode(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(KeyCode obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_KeyCode(swigCPtr);
    }
    swigCPtr = 0;
  }

  public KeyCode(KeyCode.Enum _value) {
    this(MyoushuJNI.new_KeyCode__SWIG_0(_value.swigValue()), true);
  }

  public KeyCode() {
    this(MyoushuJNI.new_KeyCode__SWIG_1(), true);
  }

  public KeyCode(KeyCodeObsolete _value) {
    this(MyoushuJNI.new_KeyCode__SWIG_2(_value.swigValue()), true);
  }

  public int toValue() {
    return MyoushuJNI.KeyCode_toValue(swigCPtr, this);
  }

  public enum Enum {
    None(MyoushuJNI.KeyCode_None_get()),
    Escape(MyoushuJNI.KeyCode_Escape_get()),
    One(MyoushuJNI.KeyCode_One_get()),
    Two(MyoushuJNI.KeyCode_Two_get()),
    Three(MyoushuJNI.KeyCode_Three_get()),
    Four(MyoushuJNI.KeyCode_Four_get()),
    Five(MyoushuJNI.KeyCode_Five_get()),
    Six(MyoushuJNI.KeyCode_Six_get()),
    Seven(MyoushuJNI.KeyCode_Seven_get()),
    Eight(MyoushuJNI.KeyCode_Eight_get()),
    Nine(MyoushuJNI.KeyCode_Nine_get()),
    Zero(MyoushuJNI.KeyCode_Zero_get()),
    Minus(MyoushuJNI.KeyCode_Minus_get()),
    Equals(MyoushuJNI.KeyCode_Equals_get()),
    Backspace(MyoushuJNI.KeyCode_Backspace_get()),
    Tab(MyoushuJNI.KeyCode_Tab_get()),
    Q(MyoushuJNI.KeyCode_Q_get()),
    W(MyoushuJNI.KeyCode_W_get()),
    E(MyoushuJNI.KeyCode_E_get()),
    R(MyoushuJNI.KeyCode_R_get()),
    T(MyoushuJNI.KeyCode_T_get()),
    Y(MyoushuJNI.KeyCode_Y_get()),
    U(MyoushuJNI.KeyCode_U_get()),
    I(MyoushuJNI.KeyCode_I_get()),
    O(MyoushuJNI.KeyCode_O_get()),
    P(MyoushuJNI.KeyCode_P_get()),
    LeftBracket(MyoushuJNI.KeyCode_LeftBracket_get()),
    RightBracket(MyoushuJNI.KeyCode_RightBracket_get()),
    Return(MyoushuJNI.KeyCode_Return_get()),
    LeftControl(MyoushuJNI.KeyCode_LeftControl_get()),
    A(MyoushuJNI.KeyCode_A_get()),
    S(MyoushuJNI.KeyCode_S_get()),
    D(MyoushuJNI.KeyCode_D_get()),
    F(MyoushuJNI.KeyCode_F_get()),
    G(MyoushuJNI.KeyCode_G_get()),
    H(MyoushuJNI.KeyCode_H_get()),
    J(MyoushuJNI.KeyCode_J_get()),
    K(MyoushuJNI.KeyCode_K_get()),
    L(MyoushuJNI.KeyCode_L_get()),
    Semicolon(MyoushuJNI.KeyCode_Semicolon_get()),
    Apostrophe(MyoushuJNI.KeyCode_Apostrophe_get()),
    Grave(MyoushuJNI.KeyCode_Grave_get()),
    LeftShift(MyoushuJNI.KeyCode_LeftShift_get()),
    Backslash(MyoushuJNI.KeyCode_Backslash_get()),
    Z(MyoushuJNI.KeyCode_Z_get()),
    X(MyoushuJNI.KeyCode_X_get()),
    C(MyoushuJNI.KeyCode_C_get()),
    V(MyoushuJNI.KeyCode_V_get()),
    B(MyoushuJNI.KeyCode_B_get()),
    N(MyoushuJNI.KeyCode_N_get()),
    M(MyoushuJNI.KeyCode_M_get()),
    Comma(MyoushuJNI.KeyCode_Comma_get()),
    Period(MyoushuJNI.KeyCode_Period_get()),
    Slash(MyoushuJNI.KeyCode_Slash_get()),
    RightShift(MyoushuJNI.KeyCode_RightShift_get()),
    Multiply(MyoushuJNI.KeyCode_Multiply_get()),
    LeftAlt(MyoushuJNI.KeyCode_LeftAlt_get()),
    Space(MyoushuJNI.KeyCode_Space_get()),
    Capital(MyoushuJNI.KeyCode_Capital_get()),
    F1(MyoushuJNI.KeyCode_F1_get()),
    F2(MyoushuJNI.KeyCode_F2_get()),
    F3(MyoushuJNI.KeyCode_F3_get()),
    F4(MyoushuJNI.KeyCode_F4_get()),
    F5(MyoushuJNI.KeyCode_F5_get()),
    F6(MyoushuJNI.KeyCode_F6_get()),
    F7(MyoushuJNI.KeyCode_F7_get()),
    F8(MyoushuJNI.KeyCode_F8_get()),
    F9(MyoushuJNI.KeyCode_F9_get()),
    F10(MyoushuJNI.KeyCode_F10_get()),
    NumLock(MyoushuJNI.KeyCode_NumLock_get()),
    ScrollLock(MyoushuJNI.KeyCode_ScrollLock_get()),
    Numpad7(MyoushuJNI.KeyCode_Numpad7_get()),
    Numpad8(MyoushuJNI.KeyCode_Numpad8_get()),
    Numpad9(MyoushuJNI.KeyCode_Numpad9_get()),
    Subtract(MyoushuJNI.KeyCode_Subtract_get()),
    Numpad4(MyoushuJNI.KeyCode_Numpad4_get()),
    Numpad5(MyoushuJNI.KeyCode_Numpad5_get()),
    Numpad6(MyoushuJNI.KeyCode_Numpad6_get()),
    Add(MyoushuJNI.KeyCode_Add_get()),
    Numpad1(MyoushuJNI.KeyCode_Numpad1_get()),
    Numpad2(MyoushuJNI.KeyCode_Numpad2_get()),
    Numpad3(MyoushuJNI.KeyCode_Numpad3_get()),
    Numpad0(MyoushuJNI.KeyCode_Numpad0_get()),
    Decimal(MyoushuJNI.KeyCode_Decimal_get()),
    OEM_102(MyoushuJNI.KeyCode_OEM_102_get()),
    F11(MyoushuJNI.KeyCode_F11_get()),
    F12(MyoushuJNI.KeyCode_F12_get()),
    F13(MyoushuJNI.KeyCode_F13_get()),
    F14(MyoushuJNI.KeyCode_F14_get()),
    F15(MyoushuJNI.KeyCode_F15_get()),
    Kana(MyoushuJNI.KeyCode_Kana_get()),
    ABNT_C1(MyoushuJNI.KeyCode_ABNT_C1_get()),
    Convert(MyoushuJNI.KeyCode_Convert_get()),
    NoConvert(MyoushuJNI.KeyCode_NoConvert_get()),
    Yen(MyoushuJNI.KeyCode_Yen_get()),
    ABNT_C2(MyoushuJNI.KeyCode_ABNT_C2_get()),
    NumpadEquals(MyoushuJNI.KeyCode_NumpadEquals_get()),
    PrevTrack(MyoushuJNI.KeyCode_PrevTrack_get()),
    At(MyoushuJNI.KeyCode_At_get()),
    Colon(MyoushuJNI.KeyCode_Colon_get()),
    Underline(MyoushuJNI.KeyCode_Underline_get()),
    Kanji(MyoushuJNI.KeyCode_Kanji_get()),
    Stop(MyoushuJNI.KeyCode_Stop_get()),
    AX(MyoushuJNI.KeyCode_AX_get()),
    Unlabeled(MyoushuJNI.KeyCode_Unlabeled_get()),
    NextTrack(MyoushuJNI.KeyCode_NextTrack_get()),
    NumpadEnter(MyoushuJNI.KeyCode_NumpadEnter_get()),
    RightControl(MyoushuJNI.KeyCode_RightControl_get()),
    Mute(MyoushuJNI.KeyCode_Mute_get()),
    Calculator(MyoushuJNI.KeyCode_Calculator_get()),
    PlayPause(MyoushuJNI.KeyCode_PlayPause_get()),
    MediaStop(MyoushuJNI.KeyCode_MediaStop_get()),
    VolumeDown(MyoushuJNI.KeyCode_VolumeDown_get()),
    VolumeUp(MyoushuJNI.KeyCode_VolumeUp_get()),
    WebHome(MyoushuJNI.KeyCode_WebHome_get()),
    NumpadComma(MyoushuJNI.KeyCode_NumpadComma_get()),
    Divide(MyoushuJNI.KeyCode_Divide_get()),
    SysRq(MyoushuJNI.KeyCode_SysRq_get()),
    RightAlt(MyoushuJNI.KeyCode_RightAlt_get()),
    Pause(MyoushuJNI.KeyCode_Pause_get()),
    Home(MyoushuJNI.KeyCode_Home_get()),
    ArrowUp(MyoushuJNI.KeyCode_ArrowUp_get()),
    PageUp(MyoushuJNI.KeyCode_PageUp_get()),
    ArrowLeft(MyoushuJNI.KeyCode_ArrowLeft_get()),
    ArrowRight(MyoushuJNI.KeyCode_ArrowRight_get()),
    End(MyoushuJNI.KeyCode_End_get()),
    ArrowDown(MyoushuJNI.KeyCode_ArrowDown_get()),
    PageDown(MyoushuJNI.KeyCode_PageDown_get()),
    Insert(MyoushuJNI.KeyCode_Insert_get()),
    Delete(MyoushuJNI.KeyCode_Delete_get()),
    LeftWindows(MyoushuJNI.KeyCode_LeftWindows_get()),
    RightWindow(MyoushuJNI.KeyCode_RightWindow_get()),
    RightWindows(MyoushuJNI.KeyCode_RightWindows_get()),
    AppMenu(MyoushuJNI.KeyCode_AppMenu_get()),
    Power(MyoushuJNI.KeyCode_Power_get()),
    Sleep(MyoushuJNI.KeyCode_Sleep_get()),
    Wake(MyoushuJNI.KeyCode_Wake_get()),
    WebSearch(MyoushuJNI.KeyCode_WebSearch_get()),
    WebFavorites(MyoushuJNI.KeyCode_WebFavorites_get()),
    WebRefresh(MyoushuJNI.KeyCode_WebRefresh_get()),
    WebStop(MyoushuJNI.KeyCode_WebStop_get()),
    WebForward(MyoushuJNI.KeyCode_WebForward_get()),
    WebBack(MyoushuJNI.KeyCode_WebBack_get()),
    MyComputer(MyoushuJNI.KeyCode_MyComputer_get()),
    Mail(MyoushuJNI.KeyCode_Mail_get()),
    MediaSelect(MyoushuJNI.KeyCode_MediaSelect_get());

    public final int swigValue() {
      return swigValue;
    }

    public static Enum swigToEnum(int swigValue) {
      Enum[] swigValues = Enum.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (Enum swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + Enum.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private Enum() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private Enum(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private Enum(Enum swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.39
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ErrorType {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ErrorType(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ErrorType obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      MyoushuJNI.delete_ErrorType(swigCPtr);
    }
    swigCPtr = 0;
  }

  public ErrorType(ErrorType.Enum _value) {
    this(MyoushuJNI.new_ErrorType__SWIG_0(_value.swigValue()), true);
  }

  public ErrorType() {
    this(MyoushuJNI.new_ErrorType__SWIG_1(), true);
  }

  public String print() {
    return MyoushuJNI.ErrorType_print(swigCPtr, this);
  }

  public enum Enum {
    OpenFileFail,
    CreateFileFail,
    IncorrectContent,
    NotClosedElements,
    NoXMLDeclaration,
    CloseNotOpenedElement,
    InconsistentOpenCloseElements,
    MoreThanOneXMLDeclaration,
    MoreThanOneRootElement,
    IncorrectAttribute,
    MAX;

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

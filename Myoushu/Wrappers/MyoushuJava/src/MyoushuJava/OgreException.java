/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class OgreException {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public OgreException(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(OgreException obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_OgreException(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public OgreException(int number, String description, String source) {
    this(MyoushuJNI.new_OgreException__SWIG_0(number, description, source), true);
  }

  public OgreException(int number, String description, String source, String type, String file, int line) {
    this(MyoushuJNI.new_OgreException__SWIG_1(number, description, source, type, file, line), true);
  }

  public OgreException(OgreException rhs) {
    this(MyoushuJNI.new_OgreException__SWIG_2(OgreException.getCPtr(rhs), rhs), true);
  }

  public String getFullDescription() {
    return MyoushuJNI.OgreException_getFullDescription(swigCPtr, this);
  }

  public int getNumber() {
    return MyoushuJNI.OgreException_getNumber(swigCPtr, this);
  }

  public String getSource() {
    return MyoushuJNI.OgreException_getSource(swigCPtr, this);
  }

  public String getFile() {
    return MyoushuJNI.OgreException_getFile(swigCPtr, this);
  }

  public int getLine() {
    return MyoushuJNI.OgreException_getLine(swigCPtr, this);
  }

  public String getDescription() {
    return MyoushuJNI.OgreException_getDescription(swigCPtr, this);
  }

  public String what() {
    return MyoushuJNI.OgreException_what(swigCPtr, this);
  }

  public enum ExceptionCodes {
    ERR_CANNOT_WRITE_TO_FILE,
    ERR_INVALID_STATE,
    ERR_INVALIDPARAMS,
    ERR_RENDERINGAPI_ERROR,
    ERR_DUPLICATE_ITEM,
    ERR_ITEM_NOT_FOUND,
    ERR_FILE_NOT_FOUND,
    ERR_INTERNAL_ERROR,
    ERR_RT_ASSERTION_FAILED,
    ERR_NOT_IMPLEMENTED;

    public final int swigValue() {
      return swigValue;
    }

    public static ExceptionCodes swigToEnum(int swigValue) {
      ExceptionCodes[] swigValues = ExceptionCodes.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (ExceptionCodes swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + ExceptionCodes.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private ExceptionCodes() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private ExceptionCodes(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private ExceptionCodes(ExceptionCodes swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

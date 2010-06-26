/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class KernelMessage extends NamedObject_KernelMessage {
  private long swigCPtr;

  public KernelMessage(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGKernelMessageUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(KernelMessage obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_KernelMessage(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public KernelMessage() {
    this(MyoushuJNI.new_KernelMessage__SWIG_0(), true);
  }

  public KernelMessage(KernelMessage.KernelMessageType type, Task task, String taskName) {
    this(MyoushuJNI.new_KernelMessage__SWIG_1(type.swigValue(), Task.getCPtr(task), task, taskName), true);
  }

  public KernelMessage(KernelMessage.KernelMessageType type, Task task) {
    this(MyoushuJNI.new_KernelMessage__SWIG_2(type.swigValue(), Task.getCPtr(task), task), true);
  }

  public KernelMessage(KernelMessage.KernelMessageType type) {
    this(MyoushuJNI.new_KernelMessage__SWIG_3(type.swigValue()), true);
  }

  public String getClassName() {
    return MyoushuJNI.KernelMessage_getClassName(swigCPtr, this);
  }

  public KernelMessage.KernelMessageType getMessageType() {
    return KernelMessage.KernelMessageType.swigToEnum(MyoushuJNI.KernelMessage_getMessageType(swigCPtr, this));
  }

  public void setMessageType(KernelMessage.KernelMessageType type) {
    MyoushuJNI.KernelMessage_setMessageType(swigCPtr, this, type.swigValue());
  }

  public Task getTask() {
    long cPtr = MyoushuJNI.KernelMessage_getTask(swigCPtr, this);
    return (cPtr == 0) ? null : new Task(cPtr, false);
  }

  public void setTask(Task task) {
    MyoushuJNI.KernelMessage_setTask(swigCPtr, this, Task.getCPtr(task), task);
  }

  public String getTaskName() {
    return MyoushuJNI.KernelMessage_getTaskName(swigCPtr, this);
  }

  public void setTaskName(String taskName) {
    MyoushuJNI.KernelMessage_setTaskName(swigCPtr, this, taskName);
  }

  public void clear() {
    MyoushuJNI.KernelMessage_clear(swigCPtr, this);
  }

  public void clone(KernelMessage dest) {
    MyoushuJNI.KernelMessage_clone(swigCPtr, this, KernelMessage.getCPtr(dest), dest);
  }

  public enum KernelMessageType {
    KM_SHUTDOWN(MyoushuJNI.KernelMessage_KM_SHUTDOWN_get()),
    KM_ADD_TASK,
    KM_REMOVE_TASK,
    KM_SUSPEND_TASK,
    KM_INIT_ALL_TASKS,
    KM_UNKNOWN;

    public final int swigValue() {
      return swigValue;
    }

    public static KernelMessageType swigToEnum(int swigValue) {
      KernelMessageType[] swigValues = KernelMessageType.class.getEnumConstants();
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (KernelMessageType swigEnum : swigValues)
        if (swigEnum.swigValue == swigValue)
          return swigEnum;
      throw new IllegalArgumentException("No enum " + KernelMessageType.class + " with value " + swigValue);
    }

    @SuppressWarnings("unused")
    private KernelMessageType() {
      this.swigValue = SwigNext.next++;
    }

    @SuppressWarnings("unused")
    private KernelMessageType(int swigValue) {
      this.swigValue = swigValue;
      SwigNext.next = swigValue+1;
    }

    @SuppressWarnings("unused")
    private KernelMessageType(KernelMessageType swigEnum) {
      this.swigValue = swigEnum.swigValue;
      SwigNext.next = this.swigValue+1;
    }

    private final int swigValue;

    private static class SwigNext {
      private static int next = 0;
    }
  }

}

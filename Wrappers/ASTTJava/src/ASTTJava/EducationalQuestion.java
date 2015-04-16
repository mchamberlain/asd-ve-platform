/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ASTTJava;

public class EducationalQuestion {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EducationalQuestion(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EducationalQuestion obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        ASTTJNI.delete_EducationalQuestion(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EducationalQuestion(String name) {
    this(ASTTJNI.new_EducationalQuestion__SWIG_0(name), true);
  }

  public EducationalQuestion() {
    this(ASTTJNI.new_EducationalQuestion__SWIG_1(), true);
  }

  public void setDescription(String description) {
    ASTTJNI.EducationalQuestion_setDescription(swigCPtr, this, description);
  }

  public String getDescription() {
    return ASTTJNI.EducationalQuestion_getDescription(swigCPtr, this);
  }

  public void setQuestion(String question) {
    ASTTJNI.EducationalQuestion_setQuestion(swigCPtr, this, question);
  }

  public String getQuestion() {
    return ASTTJNI.EducationalQuestion_getQuestion(swigCPtr, this);
  }

  public void setAnswerCondition(EducationalQuestion.AnswerCondition answerCondition) {
    ASTTJNI.EducationalQuestion_setAnswerCondition(swigCPtr, this, answerCondition.swigValue());
  }

  public EducationalQuestion.AnswerCondition getAnswerCondition() {
    return EducationalQuestion.AnswerCondition.swigToEnum(ASTTJNI.EducationalQuestion_getAnswerCondition(swigCPtr, this));
  }

  public void setCorrectAnswers(ListString correctAnswers) {
    ASTTJNI.EducationalQuestion_setCorrectAnswers(swigCPtr, this, ListString.getCPtr(correctAnswers), correctAnswers);
  }

  public ListString getCorrectAnswers() {
    return new ListString(ASTTJNI.EducationalQuestion_getCorrectAnswers(swigCPtr, this), true);
  }

  public void setPossibleAnswers(ListString possibleAnswers) {
    ASTTJNI.EducationalQuestion_setPossibleAnswers(swigCPtr, this, ListString.getCPtr(possibleAnswers), possibleAnswers);
  }

  public ListString getPossibleAnswers() {
    return new ListString(ASTTJNI.EducationalQuestion_getPossibleAnswers(swigCPtr, this), true);
  }

  public boolean evaluateAnswer(ListString answer) {
    return ASTTJNI.EducationalQuestion_evaluateAnswer(swigCPtr, this, ListString.getCPtr(answer), answer);
  }

  public final static class AnswerCondition {
    public final static AnswerCondition AC_UNKNOWN = new AnswerCondition("AC_UNKNOWN", ASTTJNI.EducationalQuestion_AC_UNKNOWN_get());
    public final static AnswerCondition AC_EXACT = new AnswerCondition("AC_EXACT");
    public final static AnswerCondition AC_ALL_NO_ORDER = new AnswerCondition("AC_ALL_NO_ORDER");
    public final static AnswerCondition AC_ONE_OF = new AnswerCondition("AC_ONE_OF");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static AnswerCondition swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + AnswerCondition.class + " with value " + swigValue);
    }

    private AnswerCondition(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private AnswerCondition(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private AnswerCondition(String swigName, AnswerCondition swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static AnswerCondition[] swigValues = { AC_UNKNOWN, AC_EXACT, AC_ALL_NO_ORDER, AC_ONE_OF };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}

/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package ASTTJava;

public class EducationalQuestionsCategory {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public EducationalQuestionsCategory(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(EducationalQuestionsCategory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        ASTTJNI.delete_EducationalQuestionsCategory(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public EducationalQuestionsCategory(String name) {
    this(ASTTJNI.new_EducationalQuestionsCategory__SWIG_0(name), true);
  }

  public EducationalQuestionsCategory() {
    this(ASTTJNI.new_EducationalQuestionsCategory__SWIG_1(), true);
  }

  public String getName() {
    return ASTTJNI.EducationalQuestionsCategory_getName(swigCPtr, this);
  }

  public EducationalQuestion make(String name) {
    long cPtr = ASTTJNI.EducationalQuestionsCategory_make__SWIG_0(swigCPtr, this, name);
    return (cPtr == 0) ? null : new EducationalQuestion(cPtr, false);
  }

  public EducationalQuestion make(String className, String name) {
    long cPtr = ASTTJNI.EducationalQuestionsCategory_make__SWIG_1(swigCPtr, this, className, name);
    return (cPtr == 0) ? null : new EducationalQuestion(cPtr, false);
  }

  public EducationalQuestion findByName(String name) {
    long cPtr = ASTTJNI.EducationalQuestionsCategory_findByName(swigCPtr, this, name);
    return (cPtr == 0) ? null : new EducationalQuestion(cPtr, false);
  }

  public void setDescription(String description) {
    ASTTJNI.EducationalQuestionsCategory_setDescription(swigCPtr, this, description);
  }

  public String getDescription() {
    return ASTTJNI.EducationalQuestionsCategory_getDescription(swigCPtr, this);
  }

  public void getQuestionNames(VectorString questionNames) {
    ASTTJNI.EducationalQuestionsCategory_getQuestionNames(swigCPtr, this, VectorString.getCPtr(questionNames), questionNames);
  }

  public void getQuestions(SWIGTYPE_p_std__vectorT_Educational__EducationalQuestion_p_t questions) {
    ASTTJNI.EducationalQuestionsCategory_getQuestions(swigCPtr, this, SWIGTYPE_p_std__vectorT_Educational__EducationalQuestion_p_t.getCPtr(questions));
  }

}
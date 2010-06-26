/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class SQLiteGameLogEntity extends GameLogEntity {
  private long swigCPtr;

  public SQLiteGameLogEntity(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGSQLiteGameLogEntityUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(SQLiteGameLogEntity obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_SQLiteGameLogEntity(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public SQLiteGameLogEntity(String name) {
    this(MyoushuJNI.new_SQLiteGameLogEntity__SWIG_0(name), true);
  }

  public SQLiteGameLogEntity() {
    this(MyoushuJNI.new_SQLiteGameLogEntity__SWIG_1(), true);
  }

  public SQLiteGameLogEntity(String name, VectorString attributeNames) {
    this(MyoushuJNI.new_SQLiteGameLogEntity__SWIG_2(name, VectorString.getCPtr(attributeNames), attributeNames), true);
  }

  public String getClassName() {
    return MyoushuJNI.SQLiteGameLogEntity_getClassName(swigCPtr, this);
  }

  public SWIGTYPE_p_uint32_t readEntry(ListString primaryKey) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.SQLiteGameLogEntity_readEntry(swigCPtr, this, ListString.getCPtr(primaryKey), primaryKey), true);
  }

  public boolean checkRead(SWIGTYPE_p_uint32_t readID) {
    return MyoushuJNI.SQLiteGameLogEntity_checkRead(swigCPtr, this, SWIGTYPE_p_uint32_t.getCPtr(readID));
  }

  public void readCompleted(SWIGTYPE_p_uint32_t readID) {
    MyoushuJNI.SQLiteGameLogEntity_readCompleted(swigCPtr, this, SWIGTYPE_p_uint32_t.getCPtr(readID));
  }

  public void commit() {
    MyoushuJNI.SQLiteGameLogEntity_commit(swigCPtr, this);
  }

  public boolean checkCommit() {
    return MyoushuJNI.SQLiteGameLogEntity_checkCommit(swigCPtr, this);
  }

  public void commitCompleted() {
    MyoushuJNI.SQLiteGameLogEntity_commitCompleted(swigCPtr, this);
  }

  public void update(boolean overwrite) {
    MyoushuJNI.SQLiteGameLogEntity_update__SWIG_0(swigCPtr, this, overwrite);
  }

  public void update() {
    MyoushuJNI.SQLiteGameLogEntity_update__SWIG_1(swigCPtr, this);
  }

  public boolean checkUpdate() {
    return MyoushuJNI.SQLiteGameLogEntity_checkUpdate(swigCPtr, this);
  }

  public void updateCompleted() {
    MyoushuJNI.SQLiteGameLogEntity_updateCompleted(swigCPtr, this);
  }

}

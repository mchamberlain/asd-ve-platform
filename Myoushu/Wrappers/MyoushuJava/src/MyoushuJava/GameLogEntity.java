/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameLogEntity extends NamedInstance {
  private long swigCPtr;

  public GameLogEntity(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameLogEntityUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameLogEntity obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameLogEntity(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public String getClassName() {
    return MyoushuJNI.GameLogEntity_getClassName(swigCPtr, this);
  }

  public void addAttributeToPrimaryKey(String attributeName) {
    MyoushuJNI.GameLogEntity_addAttributeToPrimaryKey(swigCPtr, this, attributeName);
  }

  public void addEntry(GameLogEntityEntry pEntry) {
    MyoushuJNI.GameLogEntity_addEntry__SWIG_0(swigCPtr, this, GameLogEntityEntry.getCPtr(pEntry), pEntry);
  }

  public GameLogEntityEntry addEntry(ListValue values) {
    long cPtr = MyoushuJNI.GameLogEntity_addEntry__SWIG_1(swigCPtr, this, ListValue.getCPtr(values), values);
    return (cPtr == 0) ? null : new GameLogEntityEntry(cPtr, false);
  }

  public GameLogEntityEntry getEntry(String primaryKey) {
    long cPtr = MyoushuJNI.GameLogEntity_getEntry__SWIG_0(swigCPtr, this, primaryKey);
    return (cPtr == 0) ? null : new GameLogEntityEntry(cPtr, false);
  }

  public GameLogEntityEntry getEntry(ListString primaryKey) {
    long cPtr = MyoushuJNI.GameLogEntity_getEntry__SWIG_1(swigCPtr, this, ListString.getCPtr(primaryKey), primaryKey);
    return (cPtr == 0) ? null : new GameLogEntityEntry(cPtr, false);
  }

  public String getPrimaryKeyFromEntry(GameLogEntityEntry pEntry) {
    return MyoushuJNI.GameLogEntity_getPrimaryKeyFromEntry(swigCPtr, this, GameLogEntityEntry.getCPtr(pEntry), pEntry);
  }

  public VectorString getAttributeNames() {
    return new VectorString(MyoushuJNI.GameLogEntity_getAttributeNames(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator begin() {
    return new SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator(MyoushuJNI.GameLogEntity_begin__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator end() {
    return new SWIGTYPE_p_Myoushu__GameLogEntity__KeyEntryMap__const_iterator(MyoushuJNI.GameLogEntity_end__SWIG_0(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator attributeNamesBegin() {
    return new SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator(MyoushuJNI.GameLogEntity_attributeNamesBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator attributeNamesEnd() {
    return new SWIGTYPE_p_Myoushu__GameLogEntityEntry__AttributeNamesVector__const_iterator(MyoushuJNI.GameLogEntity_attributeNamesEnd(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_std__string_t__const_iterator keyAttributesBegin() {
    return new SWIGTYPE_p_std__listT_std__string_t__const_iterator(MyoushuJNI.GameLogEntity_keyAttributesBegin(swigCPtr, this), true);
  }

  public SWIGTYPE_p_std__listT_std__string_t__const_iterator keyAttributesEnd() {
    return new SWIGTYPE_p_std__listT_std__string_t__const_iterator(MyoushuJNI.GameLogEntity_keyAttributesEnd(swigCPtr, this), true);
  }

  public void getPrimaryKeys(VectorString primaryKeysVector) {
    MyoushuJNI.GameLogEntity_getPrimaryKeys(swigCPtr, this, VectorString.getCPtr(primaryKeysVector), primaryKeysVector);
  }

  public SWIGTYPE_p_uint32_t readEntry(ListString primaryKey) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameLogEntity_readEntry(swigCPtr, this, ListString.getCPtr(primaryKey), primaryKey), true);
  }

  public boolean checkRead(SWIGTYPE_p_uint32_t readID) {
    return MyoushuJNI.GameLogEntity_checkRead(swigCPtr, this, SWIGTYPE_p_uint32_t.getCPtr(readID));
  }

  public void commit() {
    MyoushuJNI.GameLogEntity_commit(swigCPtr, this);
  }

  public boolean checkCommit() {
    return MyoushuJNI.GameLogEntity_checkCommit(swigCPtr, this);
  }

  public void update(boolean overwrite) {
    MyoushuJNI.GameLogEntity_update__SWIG_0(swigCPtr, this, overwrite);
  }

  public void update() {
    MyoushuJNI.GameLogEntity_update__SWIG_1(swigCPtr, this);
  }

  public boolean checkUpdate() {
    return MyoushuJNI.GameLogEntity_checkUpdate(swigCPtr, this);
  }

}
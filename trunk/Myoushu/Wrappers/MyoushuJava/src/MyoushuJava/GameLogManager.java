/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class GameLogManager extends NamedObjectFactory_GameLogEntity {
  private long swigCPtr;

  public GameLogManager(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGGameLogManagerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(GameLogManager obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_GameLogManager(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public void addEntity(GameLogEntity pEntity) {
    MyoushuJNI.GameLogManager_addEntity(swigCPtr, this, GameLogEntity.getCPtr(pEntity), pEntity);
  }

  public GameLogEntity makeEntity(String name, VectorString attributeNames) {
    long cPtr = MyoushuJNI.GameLogManager_makeEntity(swigCPtr, this, name, VectorString.getCPtr(attributeNames), attributeNames);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public GameLogEntity getEntity(String name) {
    long cPtr = MyoushuJNI.GameLogManager_getEntity(swigCPtr, this, name);
    return (cPtr == 0) ? null : new GameLogEntity(cPtr, false);
  }

  public SWIGTYPE_p_uint32_t readEntity(String name) {
    return new SWIGTYPE_p_uint32_t(MyoushuJNI.GameLogManager_readEntity(swigCPtr, this, name), true);
  }

  public boolean checkRead(SWIGTYPE_p_uint32_t readID) {
    return MyoushuJNI.GameLogManager_checkRead(swigCPtr, this, SWIGTYPE_p_uint32_t.getCPtr(readID));
  }

  public void commit() {
    MyoushuJNI.GameLogManager_commit(swigCPtr, this);
  }

  public boolean checkCommit() {
    return MyoushuJNI.GameLogManager_checkCommit(swigCPtr, this);
  }

  public void update() {
    MyoushuJNI.GameLogManager_update(swigCPtr, this);
  }

  public boolean checkUpdate() {
    return MyoushuJNI.GameLogManager_checkUpdate(swigCPtr, this);
  }

}

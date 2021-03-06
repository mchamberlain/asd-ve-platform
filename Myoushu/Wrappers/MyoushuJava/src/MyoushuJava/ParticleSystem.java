/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ParticleSystem extends MovableObject {
  private long swigCPtr;

  public ParticleSystem(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGParticleSystemUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ParticleSystem obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ParticleSystem(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ParticleSystem() {
    this(MyoushuJNI.new_ParticleSystem__SWIG_0(), true);
  }

  public ParticleSystem(String name, String resourceGroupName) {
    this(MyoushuJNI.new_ParticleSystem__SWIG_1(name, resourceGroupName), true);
  }

  public void setRenderer(String typeName) {
    MyoushuJNI.ParticleSystem_setRenderer(swigCPtr, this, typeName);
  }

  public SWIGTYPE_p_Ogre__ParticleSystemRenderer getRenderer() {
    long cPtr = MyoushuJNI.ParticleSystem_getRenderer(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__ParticleSystemRenderer(cPtr, false);
  }

  public String getRendererName() {
    return MyoushuJNI.ParticleSystem_getRendererName(swigCPtr, this);
  }

  public SWIGTYPE_p_Ogre__ParticleEmitter addEmitter(String emitterType) {
    long cPtr = MyoushuJNI.ParticleSystem_addEmitter(swigCPtr, this, emitterType);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__ParticleEmitter(cPtr, false);
  }

  public SWIGTYPE_p_Ogre__ParticleEmitter getEmitter(int index) {
    long cPtr = MyoushuJNI.ParticleSystem_getEmitter(swigCPtr, this, index);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__ParticleEmitter(cPtr, false);
  }

  public int getNumEmitters() {
    return MyoushuJNI.ParticleSystem_getNumEmitters(swigCPtr, this);
  }

  public void removeEmitter(int index) {
    MyoushuJNI.ParticleSystem_removeEmitter(swigCPtr, this, index);
  }

  public void removeAllEmitters() {
    MyoushuJNI.ParticleSystem_removeAllEmitters(swigCPtr, this);
  }

  public SWIGTYPE_p_Ogre__ParticleAffector addAffector(String affectorType) {
    long cPtr = MyoushuJNI.ParticleSystem_addAffector(swigCPtr, this, affectorType);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__ParticleAffector(cPtr, false);
  }

  public SWIGTYPE_p_Ogre__ParticleAffector getAffector(int index) {
    long cPtr = MyoushuJNI.ParticleSystem_getAffector(swigCPtr, this, index);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__ParticleAffector(cPtr, false);
  }

  public int getNumAffectors() {
    return MyoushuJNI.ParticleSystem_getNumAffectors(swigCPtr, this);
  }

  public void removeAffector(int index) {
    MyoushuJNI.ParticleSystem_removeAffector(swigCPtr, this, index);
  }

  public void removeAllAffectors() {
    MyoushuJNI.ParticleSystem_removeAllAffectors(swigCPtr, this);
  }

  public void clear() {
    MyoushuJNI.ParticleSystem_clear(swigCPtr, this);
  }

  public long getNumParticles() {
    return MyoushuJNI.ParticleSystem_getNumParticles(swigCPtr, this);
  }

  public SWIGTYPE_p_Ogre__Particle createParticle() {
    long cPtr = MyoushuJNI.ParticleSystem_createParticle(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__Particle(cPtr, false);
  }

  public SWIGTYPE_p_Ogre__Particle createEmitterParticle(String emitterName) {
    long cPtr = MyoushuJNI.ParticleSystem_createEmitterParticle(swigCPtr, this, emitterName);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__Particle(cPtr, false);
  }

  public SWIGTYPE_p_Ogre__Particle getParticle(long index) {
    long cPtr = MyoushuJNI.ParticleSystem_getParticle(swigCPtr, this, index);
    return (cPtr == 0) ? null : new SWIGTYPE_p_Ogre__Particle(cPtr, false);
  }

  public long getParticleQuota() {
    return MyoushuJNI.ParticleSystem_getParticleQuota(swigCPtr, this);
  }

  public void setParticleQuota(long quota) {
    MyoushuJNI.ParticleSystem_setParticleQuota(swigCPtr, this, quota);
  }

  public long getEmittedEmitterQuota() {
    return MyoushuJNI.ParticleSystem_getEmittedEmitterQuota(swigCPtr, this);
  }

  public void setEmittedEmitterQuota(long quota) {
    MyoushuJNI.ParticleSystem_setEmittedEmitterQuota(swigCPtr, this, quota);
  }

  public void _update(float timeElapsed) {
    MyoushuJNI.ParticleSystem__update(swigCPtr, this, timeElapsed);
  }

  public void setMaterialName(String name) {
    MyoushuJNI.ParticleSystem_setMaterialName(swigCPtr, this, name);
  }

  public String getMaterialName() {
    return MyoushuJNI.ParticleSystem_getMaterialName(swigCPtr, this);
  }

  public void _notifyCurrentCamera(Camera cam) {
    MyoushuJNI.ParticleSystem__notifyCurrentCamera(swigCPtr, this, Camera.getCPtr(cam), cam);
  }

  public void _notifyAttached(Node parent, boolean isTagPoint) {
    MyoushuJNI.ParticleSystem__notifyAttached__SWIG_0(swigCPtr, this, Node.getCPtr(parent), parent, isTagPoint);
  }

  public void _notifyAttached(Node parent) {
    MyoushuJNI.ParticleSystem__notifyAttached__SWIG_1(swigCPtr, this, Node.getCPtr(parent), parent);
  }

  public SWIGTYPE_p_Ogre__AxisAlignedBox getBoundingBox() {
    return new SWIGTYPE_p_Ogre__AxisAlignedBox(MyoushuJNI.ParticleSystem_getBoundingBox(swigCPtr, this), false);
  }

  public float getBoundingRadius() {
    return MyoushuJNI.ParticleSystem_getBoundingRadius(swigCPtr, this);
  }

  public void _updateRenderQueue(SWIGTYPE_p_Ogre__RenderQueue queue) {
    MyoushuJNI.ParticleSystem__updateRenderQueue(swigCPtr, this, SWIGTYPE_p_Ogre__RenderQueue.getCPtr(queue));
  }

  public void visitRenderables(SWIGTYPE_p_Ogre__Renderable__Visitor visitor, boolean debugRenderables) {
    MyoushuJNI.ParticleSystem_visitRenderables__SWIG_0(swigCPtr, this, SWIGTYPE_p_Ogre__Renderable__Visitor.getCPtr(visitor), debugRenderables);
  }

  public void visitRenderables(SWIGTYPE_p_Ogre__Renderable__Visitor visitor) {
    MyoushuJNI.ParticleSystem_visitRenderables__SWIG_1(swigCPtr, this, SWIGTYPE_p_Ogre__Renderable__Visitor.getCPtr(visitor));
  }

  public void fastForward(float time, float interval) {
    MyoushuJNI.ParticleSystem_fastForward__SWIG_0(swigCPtr, this, time, interval);
  }

  public void fastForward(float time) {
    MyoushuJNI.ParticleSystem_fastForward__SWIG_1(swigCPtr, this, time);
  }

  public void setSpeedFactor(float speedFactor) {
    MyoushuJNI.ParticleSystem_setSpeedFactor(swigCPtr, this, speedFactor);
  }

  public float getSpeedFactor() {
    return MyoushuJNI.ParticleSystem_getSpeedFactor(swigCPtr, this);
  }

  public void setIterationInterval(float iterationInterval) {
    MyoushuJNI.ParticleSystem_setIterationInterval(swigCPtr, this, iterationInterval);
  }

  public float getIterationInterval() {
    return MyoushuJNI.ParticleSystem_getIterationInterval(swigCPtr, this);
  }

  public static void setDefaultIterationInterval(float iterationInterval) {
    MyoushuJNI.ParticleSystem_setDefaultIterationInterval(iterationInterval);
  }

  public static float getDefaultIterationInterval() {
    return MyoushuJNI.ParticleSystem_getDefaultIterationInterval();
  }

  public void setNonVisibleUpdateTimeout(float timeout) {
    MyoushuJNI.ParticleSystem_setNonVisibleUpdateTimeout(swigCPtr, this, timeout);
  }

  public float getNonVisibleUpdateTimeout() {
    return MyoushuJNI.ParticleSystem_getNonVisibleUpdateTimeout(swigCPtr, this);
  }

  public static void setDefaultNonVisibleUpdateTimeout(float timeout) {
    MyoushuJNI.ParticleSystem_setDefaultNonVisibleUpdateTimeout(timeout);
  }

  public static float getDefaultNonVisibleUpdateTimeout() {
    return MyoushuJNI.ParticleSystem_getDefaultNonVisibleUpdateTimeout();
  }

  public String getMovableType() {
    return MyoushuJNI.ParticleSystem_getMovableType(swigCPtr, this);
  }

  public void _notifyParticleResized() {
    MyoushuJNI.ParticleSystem__notifyParticleResized(swigCPtr, this);
  }

  public void _notifyParticleRotated() {
    MyoushuJNI.ParticleSystem__notifyParticleRotated(swigCPtr, this);
  }

  public void setDefaultDimensions(float width, float height) {
    MyoushuJNI.ParticleSystem_setDefaultDimensions(swigCPtr, this, width, height);
  }

  public void setDefaultWidth(float width) {
    MyoushuJNI.ParticleSystem_setDefaultWidth(swigCPtr, this, width);
  }

  public float getDefaultWidth() {
    return MyoushuJNI.ParticleSystem_getDefaultWidth(swigCPtr, this);
  }

  public void setDefaultHeight(float height) {
    MyoushuJNI.ParticleSystem_setDefaultHeight(swigCPtr, this, height);
  }

  public float getDefaultHeight() {
    return MyoushuJNI.ParticleSystem_getDefaultHeight(swigCPtr, this);
  }

  public boolean getCullIndividually() {
    return MyoushuJNI.ParticleSystem_getCullIndividually(swigCPtr, this);
  }

  public void setCullIndividually(boolean cullIndividual) {
    MyoushuJNI.ParticleSystem_setCullIndividually(swigCPtr, this, cullIndividual);
  }

  public String getResourceGroupName() {
    return MyoushuJNI.ParticleSystem_getResourceGroupName(swigCPtr, this);
  }

  public String getOrigin() {
    return MyoushuJNI.ParticleSystem_getOrigin(swigCPtr, this);
  }

  public void _notifyOrigin(String origin) {
    MyoushuJNI.ParticleSystem__notifyOrigin(swigCPtr, this, origin);
  }

  public void setRenderQueueGroup(short queueID) {
    MyoushuJNI.ParticleSystem_setRenderQueueGroup(swigCPtr, this, queueID);
  }

  public void setSortingEnabled(boolean enabled) {
    MyoushuJNI.ParticleSystem_setSortingEnabled(swigCPtr, this, enabled);
  }

  public boolean getSortingEnabled() {
    return MyoushuJNI.ParticleSystem_getSortingEnabled(swigCPtr, this);
  }

  public void setBounds(SWIGTYPE_p_Ogre__AxisAlignedBox aabb) {
    MyoushuJNI.ParticleSystem_setBounds(swigCPtr, this, SWIGTYPE_p_Ogre__AxisAlignedBox.getCPtr(aabb));
  }

  public void setBoundsAutoUpdated(boolean autoUpdate, float stopIn) {
    MyoushuJNI.ParticleSystem_setBoundsAutoUpdated__SWIG_0(swigCPtr, this, autoUpdate, stopIn);
  }

  public void setBoundsAutoUpdated(boolean autoUpdate) {
    MyoushuJNI.ParticleSystem_setBoundsAutoUpdated__SWIG_1(swigCPtr, this, autoUpdate);
  }

  public void setKeepParticlesInLocalSpace(boolean keepLocal) {
    MyoushuJNI.ParticleSystem_setKeepParticlesInLocalSpace(swigCPtr, this, keepLocal);
  }

  public boolean getKeepParticlesInLocalSpace() {
    return MyoushuJNI.ParticleSystem_getKeepParticlesInLocalSpace(swigCPtr, this);
  }

  public void _updateBounds() {
    MyoushuJNI.ParticleSystem__updateBounds(swigCPtr, this);
  }

  public long getTypeFlags() {
    return MyoushuJNI.ParticleSystem_getTypeFlags(swigCPtr, this);
  }

}

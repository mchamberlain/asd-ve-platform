/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ILayer {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ILayer(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ILayer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ILayer(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public String getName() {
    return MyoushuJNI.ILayer_getName(swigCPtr, this);
  }

  public ILayerNode createChildItemNode() {
    long cPtr = MyoushuJNI.ILayer_createChildItemNode(swigCPtr, this);
    return (cPtr == 0) ? null : new ILayerNode(cPtr, false);
  }

  public void destroyChildItemNode(ILayerNode _node) {
    MyoushuJNI.ILayer_destroyChildItemNode(swigCPtr, this, ILayerNode.getCPtr(_node), _node);
  }

  public void upChildItemNode(ILayerNode _node) {
    MyoushuJNI.ILayer_upChildItemNode(swigCPtr, this, ILayerNode.getCPtr(_node), _node);
  }

  public SWIGTYPE_p_MyGUI__EnumeratorT_std__vectorT_MyGUI__ILayerNode_p_t_t getEnumerator() {
    return new SWIGTYPE_p_MyGUI__EnumeratorT_std__vectorT_MyGUI__ILayerNode_p_t_t(MyoushuJNI.ILayer_getEnumerator(swigCPtr, this), true);
  }

  public SWIGTYPE_p_MyGUI__ILayerItem getLayerItemByPoint(int _left, int _top) {
    long cPtr = MyoushuJNI.ILayer_getLayerItemByPoint(swigCPtr, this, _left, _top);
    return (cPtr == 0) ? null : new SWIGTYPE_p_MyGUI__ILayerItem(cPtr, false);
  }

  public void renderToTarget(IRenderTarget _target, boolean _update) {
    MyoushuJNI.ILayer_renderToTarget(swigCPtr, this, IRenderTarget.getCPtr(_target), _target, _update);
  }

}
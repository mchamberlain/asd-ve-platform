/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package MyoushuJava;

public class ContentImporterFactory extends NamedObjectFactory_ContentImporter {
  private long swigCPtr;

  public ContentImporterFactory(long cPtr, boolean cMemoryOwn) {
    super(MyoushuJNI.SWIGContentImporterFactoryUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr(ContentImporterFactory obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        MyoushuJNI.delete_ContentImporterFactory(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

}

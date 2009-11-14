%module Myoushu

%{
	// To solve std::max and std::min issues with MSVC
	#define NOMINMAX
	
	#ifdef SWIGLUA
	// Ensure that the MyoushuLua.h file is not included with the MyoushuLua.cpp file
	#	define MYOUSHU_LUA_H
	#endif
	
	#include <string>
	#include <list>
	#include <map>
	#include <vector>

	#include "ActionStringCallback.h"
	#include "ActionStringCallbackBase.h"
	#include "ActionStringClassCallback.h"
	#include "Actor.h"
	#include "AnimationManager.h"
	#include "AnimationTask.h"
	#include "AnimationTaskMessage.h"
	#include "Application.h"
	#include "ClientNetworkListenBehaviour.h"
	#include "ServerNetworkListenBehaviour.h"
	#include "ClientRecord.h"
	#include "ClientTask.h"
	#include "Cloneable.h"
	#include "FunctorBase.h"
	#include "ConcurrentTask.h"
	#include "Config.h"
	#include "Console.h"
	#include "Constants.h"
	#include "ContentImporter.h"
	#include "ContentImporterManager.h"
	#include "FunctorManager.h"
	#include "Controller.h"
	#include "ControllerFactory.h"
	#include "ControllerTask.h"
	#include "ControllerTaskManager.h"
	#include "ControllerTaskMessage.h"
	#include "DefaultNetworkListenBehaviour.h"
	#include "EngineLog.h"
	#include "Exception.h"
	#include "GameActorObject.h"
	#include "GameBodyObject.h"
	#include "GameCharacterObject.h"
	#include "GameCharacterObjectAction.h"
	#include "MoveableObjectController.h"
	#include "CameraWithGameObjectController.h"
	#include "GameCharacterObjectController.h"
	#include "GameCharacterObjectControllerBinding.h"
	#include "GameObject.h"
	#include "GameObjectAction.h"
	#include "GameObjectFactory.h"
	#include "GameTask.h"
	#include "GlobalLocks.h"
	#include "GUIManager.h"
	#include "GUIMessage.h"
	#include "GUITask.h"
	#include "HostRecord.h"
	#include "HumanInputDevice.h"
	#include "InputActionCallback.h"
	#include "InputActionCallbackBase.h"
	#include "InputActionManager.h"
	#include "InputDevice.h"
	#include "InputDeviceFactory.h"
	#include "InputDeviceMessage.h"
	#include "InputMessage.h"
	#include "InputTask.h"
	#include "Kernel.h"
	#include "KernelManager.h"
	#include "KernelMessage.h"
	#include "KeyboardInputDevice.h"
	#include "KeyboardOISInputDevice.h"
	#include "KeyValueProperties.h"
//	#include "LuaFunctor.h"
	#include "LuaFunctorBase.h"
	#include "LuaParser.h"
	#include "Message.h"
	#include "MessageQueue.h"
	#include "MouseInputDevice.h"
	#include "MouseOISInputDevice.h"
	#include "MyGUIConsole.h"
	#include "NamedInstance.h"
	#include "NamedObject.h"
	#include "NamedObjectBase.h"
	#include "NamedObjectFactory.h"
	#include "NamedObjectFactoryBase.h"
	#include "NamedObjectInstanceCreator.h"
	#include "NamedObjectInstanceCreatorManager.h"
	#include "NetworkListenBehaviour.h"
	#include "NetworkListenTask.h"
	#include "NetworkManager.h"
	#include "NetworkMessage.h"
	#include "NetworkMessageCallbackBase.h"
	#include "NetworkMessageCallback.h"
	#include "NetworkTransmitBehaviour.h"
	#include "DefaultNetworkTransmitBehaviour.h"
	#include "P2PNetworkTransmitBehaviour.h"
	#include "NetworkTransmitTask.h"
	#include "NotificationCenter.h"
	#include "NotificationManager.h"
	#include "ObjectFactory.h"
	#include "ObjectPool.h"
	#include "ObjectPoolBase.h"
	#include "OISInputDevice.h"
	#include "OutputStream.h"
	#include "P2PNetworkListenBehaviour.h"
	#include "PhysicsTask.h"
	#include "Platform.h"
	#include "PoolObject.h"
	#include "PoolObjectReferenceCounter.h"
	#include "Scene.h"
	#include "SceneFactory.h"
	#include "ScriptManager.h"
	#include "ScriptMessage.h"
	#include "ScriptTask.h"
	#include "Serializable.h"
	#include "ServerNetworkListenBehaviour.h"
	#include "ServerRecord.h"
	#include "Singleton.h"
	#include "Task.h"
	#include "TimerTask.h"
	#include "TimerTaskMessage.h"
	#include "Value.h"
	#include "VideoTaskMessage.h"
	#include "VideoTask.h"	
	#include "CallbackTask.h"
	#include "VideoTaskManager.h"
	#include "CollisionManager.h"
	#include "Sound.h"
	#include "StaticSound.h"
	#include "StreamSound.h"
	#include "SoundManager.h"
	#include "SoundFactory.h"
	#include "SoundPluginManager.h"
	#include "SQLiteGameLogManager.h"
	#include "Replay.h"
	#include "ReplayMessage.h"
	#include "ReplayFactory.h"
	#include "ReplayTaskManager.h"
	#include "ReplayTask.h"
	#include "RandomBase.h"
	#include "MTRandom.h"
	#include "Random.h"
	#include "Translation.h"
	#include "DefaultTranslation.h"
	
	// DotScene importer
//	#include "MyoushuDotSceneProcessorImpl.h"
	
	#ifdef SWIGJAVA
	#	include "JavaFunctor.h"
	#	include "JavaFunctorFactory.h"
	#endif
%}

#ifdef SWIGJAVA
/* Modify the default javabody typemap so that we have public access to the constructors of the proxy classes that creates java instances
   from the supplied pointer to the instance in C++. This allows us to ease passing objects as parameters in functors as we just pass the C++
   pointer and then create the relevant Java object around it when the Java method is invoked through the functor.
*/
%typemap(javabody) SWIGTYPE %{
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}

%typemap(javabody_derived) SWIGTYPE %{
  private long swigCPtr;

  public $javaclassname(long cPtr, boolean cMemoryOwn) {
    super($imclassname.SWIG$javaclassnameUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }
%}
#endif

#ifdef SWIGLUA
	%include "luatypemaps.swg"
#endif

#ifdef SWIGLUA
	%apply SWIGTYPE *DYNAMIC {Myoushu::FunctorBase *};
	// DYNAMIC CAST of FunctorBase
	%{
	static swig_type_info *
	_cast_Myoushu__FunctorBase(void **ptr) {
	#ifdef SWIGJAVA
	   Myoushu::JavaFunctor *p1 = dynamic_cast<Myoushu::JavaFunctor*>(reinterpret_cast<Myoushu::FunctorBase*>(*ptr));
	   if (p1) {
		  *ptr = reinterpret_cast<void*>(p1);
		  return SWIGTYPE_p_Myoushu__JavaFunctor;
	   }
	#endif
	   
	   Myoushu::LuaFunctorBase *p2 = dynamic_cast<Myoushu::LuaFunctorBase*>(reinterpret_cast<Myoushu::FunctorBase*>(*ptr));
	   if (p2) {
		  *ptr = reinterpret_cast<void*>(p2);
		  return SWIGTYPE_p_Myoushu__LuaFunctorBase;
	   }
	   
	   return 0;
	}
	%}
	DYNAMIC_CAST(SWIGTYPE_p_Myoushu__FunctorBase, _cast_Myoushu__FunctorBase);
	
	%apply SWIGTYPE *DYNAMIC {Myoushu::NetworkListenBehaviour *};
	// DYNAMIC CAST of NetworkListenBehaviour
	%{
	static swig_type_info *
	_cast_Myoushu__NetworkListenBehaviour(void **ptr) {
	   Myoushu::ServerNetworkListenBehaviour *p1 = dynamic_cast<Myoushu::ServerNetworkListenBehaviour*>(reinterpret_cast<Myoushu::NetworkListenBehaviour*>(*ptr));
	   if (p1) {
		  *ptr = reinterpret_cast<void*>(p1);
		  return SWIGTYPE_p_Myoushu__ServerNetworkListenBehaviour;
	   }
	   
	   Myoushu::ClientNetworkListenBehaviour *p2 = dynamic_cast<Myoushu::ClientNetworkListenBehaviour*>(reinterpret_cast<Myoushu::NetworkListenBehaviour*>(*ptr));
	   if (p2) {
		  *ptr = reinterpret_cast<void*>(p2);
		  return SWIGTYPE_p_Myoushu__ClientNetworkListenBehaviour;
	   }
	   
	   Myoushu::P2PNetworkListenBehaviour *p3 = dynamic_cast<Myoushu::P2PNetworkListenBehaviour*>(reinterpret_cast<Myoushu::NetworkListenBehaviour*>(*ptr));
	   if (p3) {
		  *ptr = reinterpret_cast<void*>(p3);
		  return SWIGTYPE_p_Myoushu__P2PNetworkListenBehaviour;
	   }
	   
	   return 0;
	}
	%}
	DYNAMIC_CAST(SWIGTYPE_p_Myoushu__NetworkListenBehaviour, _cast_Myoushu__NetworkListenBehaviour);
	
	%apply SWIGTYPE *DYNAMIC {Myoushu::NetworkTransmitBehaviour *};
	// DYNAMIC CAST of NetworkTransmitBehaviour
	%{
	static swig_type_info *
	_cast_Myoushu__NetworkTransmitBehaviour(void **ptr) {
	   Myoushu::P2PNetworkTransmitBehaviour *p1 = dynamic_cast<Myoushu::P2PNetworkTransmitBehaviour*>(reinterpret_cast<Myoushu::NetworkTransmitBehaviour*>(*ptr));
	   if (p1) {
		  *ptr = reinterpret_cast<void*>(p1);
		  return SWIGTYPE_p_Myoushu__P2PNetworkTransmitBehaviour;
	   }
	   
	   return 0;
	}
	%}
	DYNAMIC_CAST(SWIGTYPE_p_Myoushu__NetworkTransmitBehaviour, _cast_Myoushu__NetworkTransmitBehaviour);
	
	%apply SWIGTYPE *DYNAMIC {Myoushu::NamedInstance *};
	// DYNAMIC CAST of Myoushu::NamedInstance
	%{
	static swig_type_info *
	_cast_Myoushu__NamedInstance(void **ptr) {
   
	   Myoushu::GameCharacterObject *p4 = dynamic_cast<Myoushu::GameCharacterObject*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p4) {
		  *ptr = reinterpret_cast<void*>(p4);
		  return SWIGTYPE_p_Myoushu__GameCharacterObject;
	   }
		 
	   Myoushu::GameBodyObject *p3 = dynamic_cast<Myoushu::GameBodyObject*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p3) {
		  *ptr = reinterpret_cast<void*>(p3);
		  return SWIGTYPE_p_Myoushu__GameBodyObject;
	   }
	   
	   Myoushu::GameActorObject *p2 = dynamic_cast<Myoushu::GameActorObject*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p2) {
		  *ptr = reinterpret_cast<void*>(p2);
		  return SWIGTYPE_p_Myoushu__GameActorObject;
	   }
		 
	   Myoushu::GameObject *p1 = dynamic_cast<Myoushu::GameObject*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p1) {
		  *ptr = reinterpret_cast<void*>(p1);
		  return SWIGTYPE_p_Myoushu__GameObject;
	   }
	   
	   Myoushu::GameCharacterObjectController *p8 = dynamic_cast<Myoushu::GameCharacterObjectController*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p8) {
		  *ptr = reinterpret_cast<void*>(p8);
		  return SWIGTYPE_p_Myoushu__GameCharacterObjectController;
	   }
		 
	   Myoushu::CameraWithGameObjectController *p7 = dynamic_cast<Myoushu::CameraWithGameObjectController*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p7) {
		  *ptr = reinterpret_cast<void*>(p7);
		  return SWIGTYPE_p_Myoushu__CameraWithGameObjectController;
	   }
		 
	   Myoushu::MoveableObjectController *p6 = dynamic_cast<Myoushu::MoveableObjectController*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p6) {
		  *ptr = reinterpret_cast<void*>(p6);
		  return SWIGTYPE_p_Myoushu__MoveableObjectController;
	   }
		 
	   Myoushu::Controller *p5 = dynamic_cast<Myoushu::Controller*>(reinterpret_cast<Myoushu::NamedInstance*>(*ptr));
	   if (p5) {
		  *ptr = reinterpret_cast<void*>(p5);
		  return SWIGTYPE_p_Myoushu__Controller;
	   }
		 
	   return 0;
	}
	%}
	DYNAMIC_CAST(SWIGTYPE_p_Myoushu__NamedInstance, _cast_Myoushu__NamedInstance);
#endif

%include "std_string.i"
%include "std_vector.i"
%include "std_list.i"

%template(VectorInt) std::vector<int>;
%template(VectorUInt) std::vector<unsigned int>;
%template(VectorChar) std::vector<char>;
%template(VectorDouble) std::vector<double>;
%template(VectorFloat) std::vector<float>;
%template(VectorLong) std::vector<long>;
%template(VectorBool) std::vector<bool>;
%template(VectorString) std::vector<std::string>;
%template(VectorValue) std::vector<Myoushu::Value>;

%template(ListInt) std::list<int>;
%template(ListUInt) std::list<unsigned int>;
%template(ListChar) std::list<char>;
%template(ListDouble) std::list<double>;
%template(ListFloat) std::list<float>;
%template(ListLong) std::list<long>;
%template(ListBool) std::list<bool>;
%template(ListString) std::list<std::string>;
%template(ListValue) std::list<Myoushu::Value>;

%include "Poco.i"
%include "Ogre.i"
%include "NxOgre.i"
%include "MyGUI.i"

%include "Platform.h"

#ifdef MYOUSHU_API
#	undef MYOUSHU_API
#endif
#define MYOUSHU_API

#ifdef MYOUSHU_DOTSCENE_API
# undef MYOUSHU_DOTSCENE_API
#endif
#define MYOUSHU_DOTSCENE_API

#ifdef JNIEXPORT
#	undef JNIEXPORT
#endif
#define JNIEXPORT

#ifdef JNICALL
#	undef JNICALL
#endif
#define JNICALL

// Proper Java enums
#ifdef SWIGJAVA
%include "enums.swg"
#endif

%include "Exception.h"
%include "Serializable.h"
%include "NamedInstance.h"
%include "ActionStringCallback.h"
%include "ActionStringCallbackBase.h"
%include "ActionStringClassCallback.h"
%include "Constants.h"

%template(Singleton_AnimationManager) Ogre::Singleton<Myoushu::AnimationManager>;
%template(Singleton_Application) Ogre::Singleton<Myoushu::Application>;
%template(Singleton_Config) Ogre::Singleton<Myoushu::Config>;
%template(Singleton_Console) Ogre::Singleton<Myoushu::Console>;
%template(Singleton_ControllerFactory) Ogre::Singleton<Myoushu::ControllerFactory>;
%template(Singleton_ControllerTaskManager) Ogre::Singleton<Myoushu::ControllerTaskManager>;
%template(Singleton_EngineLog) Ogre::Singleton<Myoushu::EngineLog>;
%template(Singleton_GameObjectFactory) Ogre::Singleton<Myoushu::GameObjectFactory>;
%template(Singleton_GUIManager) Ogre::Singleton<Myoushu::GUIManager>;
%template(Singleton_InputActionManager) Ogre::Singleton<Myoushu::InputActionManager>;
%template(Singleton_InputDeviceFactory) Ogre::Singleton<Myoushu::InputDeviceFactory>;
%template(Singleton_SoundPluginManager) Ogre::Singleton<Myoushu::SoundPluginManager>;
%template(Singleton_Kernel) Ogre::Singleton<Myoushu::Kernel>;
%template(Singleton_KernelManager) Ogre::Singleton<Myoushu::KernelManager>;
%template(Singleton_NamedObjectInstanceCreatorManager) Ogre::Singleton<Myoushu::NamedObjectInstanceCreatorManager>;
%template(Singleton_NetworkListenTask) Ogre::Singleton<Myoushu::NetworkListenTask>;
%template(Singleton_NetworkManager) Ogre::Singleton<Myoushu::NetworkManager>;
%template(Singleton_NotificationManager) Ogre::Singleton<Myoushu::NotificationManager>;
%template(Singleton_SceneFactory) Ogre::Singleton<Myoushu::SceneFactory>;
%template(Singleton_ScriptManager) Ogre::Singleton<Myoushu::ScriptManager>;
%template(Singleton_TimerTask) Ogre::Singleton<Myoushu::TimerTask>;
%template(Singleton_VideoTaskManager) Ogre::Singleton<Myoushu::VideoTaskManager>;
%template(Singleton_CollisionManager) Ogre::Singleton<Myoushu::CollisionManager>;
%template(Singleton_SQLiteGameLogManager) Ogre::Singleton<Myoushu::SQLiteGameLogManager>;
%template(Singleton_ReplayTaskManager) Ogre::Singleton<Myoushu::ReplayTaskManager>;
%template(Singleton_ReplayFactory) Ogre::Singleton<Myoushu::ReplayFactory>;
%template(Singleton_Random) Ogre::Singleton<Myoushu::Random>;
%template(Singleton_ContentImporterManager) Ogre::Singleton<Myoushu::ContentImporterManager>;
%template(Singleton_FunctorManager) Ogre::Singleton<Myoushu::FunctorManager>;
%template(Singleton_DefaultTranslation) Ogre::Singleton<Myoushu::DefaultTranslation>;

%template(AutoPtr_AnimationTaskMessage) Poco::AutoPtr<Myoushu::AnimationTaskMessage>;
%template(AutoPtr_ControllerTaskMessage) Poco::AutoPtr<Myoushu::ControllerTaskMessage>;
%template(AutoPtr_GUIMessage) Poco::AutoPtr<Myoushu::GUIMessage>;
%template(AutoPtr_InputDevice) Poco::AutoPtr<Myoushu::InputDevice>;
%template(AutoPtr_InputDeviceMessage) Poco::AutoPtr<Myoushu::InputDeviceMessage>;
%template(AutoPtr_InputMessage) Poco::AutoPtr<Myoushu::InputMessage>;
%template(AutoPtr_KernelMessage) Poco::AutoPtr<Myoushu::KernelMessage>;
%template(AutoPtr_KeyboardOISInputDevice) Poco::AutoPtr<Myoushu::KeyboardOISInputDevice>;
%template(AutoPtr_Message) Poco::AutoPtr<Myoushu::Message>;
%template(AutoPtr_MouseOISInputDevice) Poco::AutoPtr<Myoushu::MouseOISInputDevice>;
%template(AutoPtr_NetworkMessage) Poco::AutoPtr<Myoushu::NetworkMessage>;
%template(AutoPtr_ScriptMessage) Poco::AutoPtr<Myoushu::ScriptMessage>;
%template(AutoPtr_Task) Poco::AutoPtr<Myoushu::Task>;
%template(AutoPtr_TimerTaskMessage) Poco::AutoPtr<Myoushu::TimerTaskMessage>;
%template(AutoPtr_Sound) Poco::AutoPtr<Myoushu::Sound>;
%template(AutoPtr_GameLogMessage) Poco::AutoPtr<Myoushu::GameLogMessage>;
%template(AutoPtr_GameLogEntity) Poco::AutoPtr<Myoushu::GameLogEntity>;
%template(AutoPtr_ReplayMessage) Poco::AutoPtr<Myoushu::ReplayMessage>;
%template(AutoPtr_Replay) Poco::AutoPtr<Myoushu::Replay>;
%template(AutoPtr_VideoTaskMessage) Poco::AutoPtr<Myoushu::VideoTaskMessage>;
%template(AutoPtr_ContentImporter) Poco::AutoPtr<Myoushu::ContentImporter>;
%template(AutoPtr_FunctorBase) Poco::AutoPtr<Myoushu::FunctorBase>;

%include "Singleton.h"
%include "OutputStream.h"

#ifdef SWIGJAVA
// Ignore clone() method with variant return type that has issues with Java
%ignore Myoushu::Cloneable::clone() const;
#endif
%include "Cloneable.h"

/* %include "GlobalLocks.h" */
%include "NamedObjectBase.h"
#ifdef SWIGJAVA
	%ignore *::castPtr(void*);
#endif
%include "NamedObject.h"

%template(NamedObject_AnimationTask) Myoushu::NamedObject<Myoushu::AnimationTask>;
%template(NamedObject_AnimationTaskMessage) Myoushu::NamedObject<Myoushu::AnimationTaskMessage>;
%template(NamedObject_Application) Myoushu::NamedObject<Myoushu::Application>;
%template(NamedObject_ClientNetworkListenBehaviour) Myoushu::NamedObject<Myoushu::ClientNetworkListenBehaviour>;
%template(NamedObject_ClientRecord) Myoushu::NamedObject<Myoushu::ClientRecord>;
%template(NamedObject_ConcurrentTask) Myoushu::NamedObject<Myoushu::ConcurrentTask>;
%template(NamedObject_Controller) Myoushu::NamedObject<Myoushu::Controller>;
%template(NamedObject_ControllerTask) Myoushu::NamedObject<Myoushu::ControllerTask>;
%template(NamedObject_ControllerTaskMessage) Myoushu::NamedObject<Myoushu::ControllerTaskMessage>;
%template(NamedObject_DefaultNetworkListenBehaviour) Myoushu::NamedObject<Myoushu::DefaultNetworkListenBehaviour>;
%template(NamedObject_GameObject) Myoushu::NamedObject<Myoushu::GameObject>;
%template(NamedObject_GameObjectAction) Myoushu::NamedObject<Myoushu::GameObjectAction>;
%template(NamedObject_GameActorObject) Myoushu::NamedObject<Myoushu::GameActorObject>;
%template(NamedObject_GameBodyObject) Myoushu::NamedObject<Myoushu::GameBodyObject>;
%template(NamedObject_GameCharacterObject) Myoushu::NamedObject<Myoushu::GameCharacterObject>;
%template(NamedObject_GameCharacterObjectAction) Myoushu::NamedObject<Myoushu::GameCharacterObjectAction>;
%template(NamedObject_GameCharacterObjectController) Myoushu::NamedObject<Myoushu::GameCharacterObjectController>;
%template(NamedObject_GameTask) Myoushu::NamedObject<Myoushu::GameTask>;
%template(NamedObject_GUIMessage) Myoushu::NamedObject<Myoushu::GUIMessage>;
%template(NamedObject_GUITask) Myoushu::NamedObject<Myoushu::GUITask>;
%template(NamedObject_HostRecord) Myoushu::NamedObject<Myoushu::HostRecord>;
%template(NamedObject_InputDeviceMessage) Myoushu::NamedObject<Myoushu::InputDeviceMessage>;
%template(NamedObject_InputMessage) Myoushu::NamedObject<Myoushu::InputMessage>;
%template(NamedObject_InputTask) Myoushu::NamedObject<Myoushu::InputTask>;
%template(NamedObject_KernelMessage) Myoushu::NamedObject<Myoushu::KernelMessage>;
%template(NamedObject_Message) Myoushu::NamedObject<Myoushu::Message>;
%template(NamedObject_NetworkListenBehaviour) Myoushu::NamedObject<Myoushu::NetworkListenBehaviour>;
%template(NamedObject_NetworkListenTask) Myoushu::NamedObject<Myoushu::NetworkListenTask>;
%template(NamedObject_NetworkMessage) Myoushu::NamedObject<Myoushu::NetworkMessage>;
%template(NamedObject_NetworkTransmitTask) Myoushu::NamedObject<Myoushu::NetworkTransmitTask>;
%template(NamedObject_P2PNetworkListenBehaviour) Myoushu::NamedObject<Myoushu::P2PNetworkListenBehaviour>;
%template(NamedObject_PoolObject) Myoushu::NamedObject<Myoushu::PoolObject>;
%template(NamedObject_PhysicsTask) Myoushu::NamedObject<Myoushu::PhysicsTask>;
%template(NamedObject_Scene) Myoushu::NamedObject<Myoushu::Scene>;
%template(NamedObject_ScriptMessage) Myoushu::NamedObject<Myoushu::ScriptMessage>;
%template(NamedObject_ScriptTask) Myoushu::NamedObject<Myoushu::ScriptTask>;
%template(NamedObject_ServerNetworkListenBehaviour) Myoushu::NamedObject<Myoushu::ServerNetworkListenBehaviour>;
%template(NamedObject_ServerRecord) Myoushu::NamedObject<Myoushu::ServerRecord>;
%template(NamedObject_Task) Myoushu::NamedObject<Myoushu::Task>;
%template(NamedObject_TimerTask) Myoushu::NamedObject<Myoushu::TimerTask>;
%template(NamedObject_TimerTaskMessage) Myoushu::NamedObject<Myoushu::TimerTaskMessage>;
%template(NamedObject_VideoTask) Myoushu::NamedObject<Myoushu::VideoTask>;
%template(NamedObject_CallbackTask) Myoushu::NamedObject<Myoushu::CallbackTask>;
%template(NamedObject_Sound) Myoushu::NamedObject<Myoushu::Sound>;
%template(NamedObject_StaticSound) Myoushu::NamedObject<Myoushu::StaticSound>;
%template(NamedObject_StreamSound) Myoushu::NamedObject<Myoushu::StreamSound>;
%template(NamedObject_GameLogEntity) Myoushu::NamedObject<Myoushu::GameLogEntity>;
%template(NamedObject_GameLogMessage) Myoushu::NamedObject<Myoushu::GameLogEntity>;
%template(NamedObject_SQLiteGameLogEntity) Myoushu::NamedObject<Myoushu::SQLiteGameLogEntity>;
%template(NamedObject_Replay) Myoushu::NamedObject<Myoushu::Replay>;
%template(NamedObject_VideoTask) Myoushu::NamedObject<Myoushu::VideoTask>;
%template(NamedObject_ContentImporter) Myoushu::NamedObject<Myoushu::ContentImporter>;
%template(NamedObject_FunctorBase) Myoushu::NamedObject<Myoushu::FunctorBase>;

%include "Plugin.h"

%include "PoolObjectReferenceCounter.h"
%include "PoolObject.h"

%ignore Myoushu::Value::getValue() const;

%include "Value.h"

%ignore Myoushu::FunctorBase::setParameter(unsigned int, Value);

%include "FunctorBase.h"
%include "Message.h"
%include "TimerTaskMessage.h"
%apply SWIGTYPE *DISOWN {Myoushu::Value* value};
%include "KeyValueProperties.h"
%include "ObjectFactory.h"
#ifdef SWIGJAVA
// Ignore make() methods with variant return types that has issues with Java
%ignore Myoushu::NamedObjectFactoryBase::make(const std::string&);
%ignore Myoushu::NamedObjectFactoryBase::make(const std::string&, const std::string&);
#endif
%include "NamedObjectFactoryBase.h"
%include "NamedObjectFactory.h"

%template(NamedObjectFactory_Controller) Myoushu::NamedObjectFactory<Myoushu::Controller>;
%template(NamedObjectFactory_GameObject) Myoushu::NamedObjectFactory<Myoushu::GameObject>;
%template(NamedObjectFactory_Scene) Myoushu::NamedObjectFactory<Myoushu::Scene>;
%template(NamedObjectFactory_Sound) Myoushu::NamedObjectFactory<Myoushu::Sound>;
%template(NamedObjectFactory_GameLogEntity) Myoushu::NamedObjectFactory<Myoushu::GameLogEntity>;
%template(NamedObjectFactory_Replay) Myoushu::NamedObjectFactory<Myoushu::Replay>;
%template(NamedObjectFactory_ContentImporter) Myoushu::NamedObjectFactory<Myoushu::ContentImporter>;
%template(NamedObjectFactory_FunctorBase) Myoushu::NamedObjectFactory<Myoushu::FunctorBase>;

// %include "ObjectPoolBase.h"
%include "ObjectPool.h"

%template(ObjectPool_AnimationTaskMessage) Myoushu::ObjectPool<Myoushu::AnimationTaskMessage>;
%template(ObjectPool_KernelMessage) Myoushu::ObjectPool<Myoushu::KernelMessage>;
%template(ObjectPool_GUIMessage) Myoushu::ObjectPool<Myoushu::GUIMessage>;
%template(ObjectPool_ControllerTaskMessage) Myoushu::ObjectPool<Myoushu::ControllerTaskMessage>;
%template(ObjectPool_InputDeviceMessage) Myoushu::ObjectPool<Myoushu::InputDeviceMessage>;
%template(ObjectPool_InputMessage) Myoushu::ObjectPool<Myoushu::InputMessage>;
%template(ObjectPool_ScriptMessage) Myoushu::ObjectPool<Myoushu::ScriptMessage>;
%template(ObjectPool_NetworkMessage) Myoushu::ObjectPool<Myoushu::NetworkMessage>;
%template(ObjectPool_TimerTaskMessage) Myoushu::ObjectPool<Myoushu::TimerTaskMessage>;
%template(ObjectPool_GameLogMessage) Myoushu::ObjectPool<Myoushu::GameLogMessage>;
%template(ObjectPool_ReplayMessage) Myoushu::ObjectPool<Myoushu::ReplayMessage>;
%template(ObjectPool_VideoTaskMessage) Myoushu::ObjectPool<Myoushu::VideoTaskMessage>;

%template(Singleton_ObjectPool_AnimationTaskMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::AnimationTaskMessage> >;
%template(Singleton_ObjectPool_KernelMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::KernelMessage> >;
%template(Singleton_ObjectPool_GUIMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::GUIMessage> >;
%template(Singleton_ObjectPool_ControllerTaskMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::ControllerTaskMessage> >;
%template(Singleton_ObjectPool_InputDeviceMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::InputDeviceMessage> >;
%template(Singleton_ObjectPool_InputMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::InputMessage> >;
%template(Singleton_ObjectPool_ScriptMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::ScriptMessage> >;
%template(Singleton_ObjectPool_NetworkMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::NetworkMessage> >;
%template(Singleton_ObjectPool_TimerTaskMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::TimerTaskMessage> >;
%template(Singleton_ObjectPool_GameLogMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::GameLogMessage> >;
%template(Singleton_ObjectPool_ReplayMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::ReplayMessage> >;
%template(Singleton_ObjectPool_VideoTaskMessage) Ogre::Singleton<Myoushu::ObjectPool<Myoushu::VideoTaskMessage> >;

%include "HostRecord.h"
%include "Task.h"
%include "LuaParser.h"

// Ignore some troublesome functions in Myoushu::Scene
%ignore Myoushu::Scene::getAnimationIterator();
%ignore Myoushu::Scene::getAnimationStateIterator();
%ignore Myoushu::Scene::getCameraIterator();
%ignore Myoushu::Scene::getShadowTextureConfigIterator() const;
%ignore Myoushu::Scene::getMovableObjectIterator(const Ogre::String&);

%include "Scene.h"
%include "Actor.h"
%include "AnimationTaskMessage.h"
%include "AnimationManager.h"
%include "AnimationTask.h"
%include "Application.h"
%include "NetworkMessage.h"
%include "NetworkMessageCallbackBase.h"
%include "NetworkMessageCallback.h"
%include "NetworkListenBehaviour.h"
%include "DefaultNetworkListenBehaviour.h"
%include "ClientNetworkListenBehaviour.h"
%include "ServerNetworkListenBehaviour.h"
%include "NetworkTransmitBehaviour.h"
/* %include "ClientRecord.h" */
%include "ClientTask.h"
%include "ConcurrentTask.h"
%include "InputDevice.h"
%include "InputDeviceMessage.h"
%include "InputMessage.h"
%include "DefaultNetworkTransmitBehaviour.h"
%include "P2PNetworkTransmitBehaviour.h"
%include "Config.h"
%include "Console.h"
%include "ContentImporter.h"
%include "Controller.h"
%include "EngineLog.h"
%include "GameObjectAction.h"
%apply SWIGTYPE *DISOWN {Myoushu::GameObjectAction* action};
%include "GameObject.h"
%include "GameActorObject.h"
%include "GameBodyObject.h"
%include "GameCharacterObjectAction.h"
%include "GameCharacterObject.h"
%include "MoveableObjectController.h"
%include "CameraWithGameObjectController.h"
%include "GameCharacterObjectController.h"
%include "GameCharacterObjectControllerBinding.h"
// All NxOgre::ShapeBluePrint* will be owned by C++ if passed to make* methods in the factory
%apply SWIGTYPE *DISOWN {NxOgre::ShapeBlueprint* collisionShape};
%include "GameObjectFactory.h"
%include "ControllerFactory.h"
%include "ControllerTaskMessage.h"
%include "ControllerTask.h"
%include "ControllerTaskManager.h"
%include "GameTask.h"
%include "GUIManager.h"
%include "GUIMessage.h"
%include "GUITask.h"
%include "HumanInputDevice.h"
%include "InputActionCallbackBase.h"
%include "InputActionCallback.h"
%apply SWIGTYPE *DISOWN {FunctorBase *pFunctor};
%include "InputActionManager.h"
%include "OISInputDevice.h"

%template(OISInputDevice_OIS_Mouse) Myoushu::OISInputDevice<OIS::Mouse>;
%template(OISInputDevice_OIS_Keyboard) Myoushu::OISInputDevice<OIS::Keyboard>;

%include "MouseInputDevice.h"
%include "MouseOISInputDevice.h"
%include "KeyboardInputDevice.h"
%include "KeyboardOISInputDevice.h"
%include "InputDeviceFactory.h"
%include "InputTask.h"
%include "KernelMessage.h"
%apply SWIGTYPE *DISOWN {Myoushu::Task *task};
%include "Kernel.h"
%include "LuaFunctorBase.h"
/* %include "LuaFunctor.h" */
/* %include "MessageQueue.h" */
%include "MyGUIConsole.h"
%include "NamedObjectInstanceCreator.h"
%include "NamedObjectInstanceCreatorManager.h"
%include "NetworkListenTask.h"
%include "NetworkManager.h"
%include "NetworkTransmitTask.h"
/* %include "NotificationCenter.h" */
%include "NotificationManager.h"

// Template instantiations for templated functions in NotitifcationManager
%template(addObserverFunctorAnimationTaskMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::AnimationTaskMessage>;
%template(addObserverFunctorControllerTaskMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::ControllerTaskMessage>;
%template(addObserverFunctorGameLogMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::GameLogMessage>;
%template(addObserverFunctorGUIMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::GUIMessage>;
%template(addObserverFunctorInputDeviceMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::InputDeviceMessage>;
%template(addObserverFunctorInputMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::InputMessage>;
%template(addObserverFunctorKernelMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::KernelMessage>;
%template(addObserverFunctorNetworkMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::NetworkMessage>;
%template(addObserverFunctorReplayMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::ReplayMessage>;
%template(addObserverFunctorScriptMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::ScriptMessage>;
%template(addObserverFunctorTimerTaskMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::TimerTaskMessage>;
%template(addObserverFunctorVideoTaskMessage) Myoushu::NotificationManager::addObserverFunctor<Myoushu::VideoTaskMessage>;

%template(removeObserverFunctorAnimationTaskMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::AnimationTaskMessage>;
%template(removeObserverFunctorControllerTaskMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::ControllerTaskMessage>;
%template(removeObserverFunctorGameLogMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::GameLogMessage>;
%template(removeObserverFunctorGUIMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::GUIMessage>;
%template(removeObserverFunctorInputDeviceMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::InputDeviceMessage>;
%template(removeObserverFunctorInputMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::InputMessage>;
%template(removeObserverFunctorKernelMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::KernelMessage>;
%template(removeObserverFunctorNetworkMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::NetworkMessage>;
%template(removeObserverFunctorReplayMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::ReplayMessage>;
%template(removeObserverFunctorScriptMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::ScriptMessage>;
%template(removeObserverFunctorTimerTaskMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::TimerTaskMessage>;
%template(removeObserverFunctorVideoTaskMessage) Myoushu::NotificationManager::removeObserverFunctor<Myoushu::VideoTaskMessage>;

//%include "OgreColladaContentImporter.h"
%include "P2PNetworkListenBehaviour.h"
%include "PhysicsTask.h"
%include "SceneFactory.h"
%include "ScriptManager.h"
%include "ScriptMessage.h"
%include "ScriptTask.h"
%include "ServerNetworkListenBehaviour.h"
%include "ServerRecord.h"
%include "TimerTask.h"
%include "VideoTaskMessage.h"
%include "VideoTask.h"
%include "CallbackTask.h"
%include "KernelManager.h"
%include "VideoTaskManager.h"
%include "CollisionManager.h"
%include "Sound.h"
%include "StaticSound.h"
%include "StreamSound.h"
%include "SoundManager.h"
%include "SoundFactory.h"
%include "SoundPluginManager.h"
%include "GameLogEntityEntry.h"
%include "GameLogEntity.h"
%include "SQLiteGameLogEntity.h"
%include "GameLogManager.h"
%include "SQLiteGameLogManager.h"
%include "Replay.h"
%include "ReplayMessage.h"
%include "ReplayFactory.h"
%include "ReplayTaskManager.h"
%include "ReplayTask.h"
%include "RandomBase.h"
%include "MTRandom.h"
%include "Random.h"
%include "ContentImporterFactory.h"
%include "ContentImporterManager.h"
%include "FunctorFactory.h"
%include "FunctorManager.h"
%include "Translation.h"
%include "DefaultTranslation.h"

// DotScene importer
//%include "../MyoushuDotScene/include/MyoushuDotSceneProcessorImpl.h"
	
#ifdef SWIGJAVA
	%include "MyoushuJavaPlatform.h"
	
	#ifdef MYOUSHU_JAVA_API
	#	undef MYOUSHU_JAVA_API
	#endif
	#define MYOUSHU_JAVA_API
	
	%ignore Myoushu::JavaFunctor::setMethod(JavaVM *, jclass, jobject, jmethodID);
	%native (JavaFunctor_setMethod) void Myoushu::JavaFunctor::setMethod(jlong, jobject, jobject, char *, char *);
	%include "JavaFunctor.h"
	
	%template(Singleton_JavaFunctorFactory) Ogre::Singleton<Myoushu::JavaFunctorFactory>;
	namespace Myoushu
	{
		// JavaFunctorFactory.h, cleaned
		class JavaFunctorFactory : public Ogre::Singleton<JavaFunctorFactory>
		{
			public:
				/** Constructor. */
				JavaFunctorFactory();

				/** Destructor. */
				virtual ~JavaFunctorFactory();

				/** 
				 * Create an instance using with specified name. Extending classes can change
				 * the return type of this function to an appropriate type.
				 * @param name The name for the instance to create.
				 * @return The newly created instance.
				 */
				JavaFunctor* make(const std::string& name);

				/** 
				 * Create an instance of the specified className with the specified instance name. Extending classes can change
				 * the return type of this function to an appropriate type. This function is useful for factories that can
				 * create instances of different classes in an inheritence hierarchy.
				 * @param className The name of the class to create an instance of.
				 * @param name The name for the instance to create.
				 * @return The newly created instance.
				 * @throws Exception::E_INVALID_PARAMETERS if this factory does not support the creation of instances of type className.
				 */
				FunctorBase* make(const std::string& className, const std::string& name) throw (Exception);

		}; // class FunctorFactory
	} // namespace Myoushu
#endif

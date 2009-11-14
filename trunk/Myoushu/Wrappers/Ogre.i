%module Ogre
%{
	#include "Ogre.h"
	typedef Ogre::String String;
	typedef Ogre::Node Node;
	typedef Ogre::Any Any;
	typedef Ogre::HardwareIndexBufferSharedPtr HardwareIndexBufferSharedPtr;
	typedef Ogre::PolygonMode PolygonMode;
	typedef Ogre::ShadowCameraSetupPtr ShadowCameraSetupPtr;
	typedef Ogre::ShadowTechnique ShadowTechnique;
	typedef Ogre::Node::TransformSpace TransformSpace;
	typedef Ogre::ShadowCaster ShadowCaster;
	typedef Ogre::ShadowCaster::ShadowRenderableListIterator ShadowRenderableListIterator;
	typedef Ogre::AnimableValuePtr AnimableValuePtr;
	typedef Ogre::PlaneBoundedVolumeList PlaneBoundedVolumeList;
	typedef Ogre::MovableObject MovableObject;
	typedef Ogre::PixelFormat PixelFormat;
	typedef Ogre::RenderTarget::FrameStats FrameStats;

%}

#ifdef _OgreExport
#	undef _OgreExport
#endif
#define _OgreExport

// Proper Java enums
#ifdef SWIGJAVA
%include "enums.swg"
#endif

%include "std_string.i"

typedef Ogre::String String;
typedef Ogre::Node Node;
typedef Ogre::Any Any;
typedef Ogre::HardwareIndexBufferSharedPtr HardwareIndexBufferSharedPtr;
typedef Ogre::PolygonMode PolygonMode;
typedef Ogre::ShadowCameraSetupPtr ShadowCameraSetupPtr;
typedef Ogre::ShadowTechnique ShadowTechnique;
typedef Ogre::Node::TransformSpace TransformSpace;
typedef Ogre::ShadowCaster ShadowCaster;
typedef Ogre::ShadowCaster::ShadowRenderableListIterator ShadowRenderableListIterator;
typedef Ogre::AnimableValuePtr AnimableValuePtr;
typedef Ogre::PlaneBoundedVolumeList PlaneBoundedVolumeList;
typedef Ogre::MovableObject MovableObject;
typedef Ogre::PixelFormat PixelFormat;
typedef Ogre::RenderTarget::FrameStats FrameStats;

%include "../../3rdparty/ogre/OgreMain/include/OgrePlatform.h"

// We have to define the compiler we are going to be using for Ogre
#ifdef OGRE_COMPILER
#	undef OGRE_COMPILER
#endif
#define OGRE_COMPILER OGRE_COMPILER_MSVC
#ifdef OGRE_COMP_VER
#	undef OGRE_COMP_VER
#endif
#define OGRE_COMP_VER 1500

%rename(OgreException) Ogre::Exception;
%include "../../3rdparty/ogre/OgreMain/include/OgreException.h"

%include "../../3rdparty/ogre/OgreMain/include/OgreString.h"
%include "../../3rdparty/ogre/OgreMain/include/OgrePrerequisites.h"

// We have to explicity define HashMap and HashSet to ::stdext if we are using MSVC and ::std otherwise
//#ifdef HashMap
//#	undef HashMap 
//#endif
//#ifdef HashSet
//#	undef HashSet 
//#endif
//#define HashMap ::std::tr1::unordered_map
//#define HashSet ::std::tr1::unordered_set
//#define HashMap ::__gnu_cxx::hash_map
//#define HashSet ::__gnu_cxx::hash_set
//#define HashMap ::std::hash_map
//#define HashSet ::std::hash_set
//#define HashMap ::stdext::hash_map
//#define HashSet ::stdext::hash_set

%include "../../3rdparty/ogre/OgreMain/include/OgreUTFString.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreException.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreIteratorWrappers.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreSingleton.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreCommon.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreMath.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreVector2.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreVector3.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreVector4.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreMatrix3.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreMatrix4.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreQuaternion.h"
%ignore Ogre::MovableObject::getShadowVolumeRenderableIterator(ShadowTechnique, const Light*, HardwareIndexBufferSharedPtr*, bool, Real, unsigned long);
%ignore Ogre::MovableObject::getShadowVolumeRenderableIterator(ShadowTechnique, const Light*, HardwareIndexBufferSharedPtr*, bool, Real);
%include "../../3rdparty/ogre/OgreMain/include/OgreMovableObject.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreNode.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreColourValue.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreLight.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreFrustum.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreCamera.h"
%ignore Ogre::Entity::getShadowVolumeRenderableIterator(ShadowTechnique, const Light*, HardwareIndexBufferSharedPtr*, bool, Real, unsigned long);
%ignore Ogre::Entity::getShadowVolumeRenderableIterator(ShadowTechnique, const Light*, HardwareIndexBufferSharedPtr*, bool, Real);
%include "../../3rdparty/ogre/OgreMain/include/OgreEntity.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreSceneNode.h"
%ignore Ogre::ParticleSystem::_getIterator();
%include "../../3rdparty/ogre/OgreMain/include/OgreParticleSystem.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreViewport.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreRenderTarget.h"
%include "../../3rdparty/ogre/OgreMain/include/OgreRenderWindow.h"

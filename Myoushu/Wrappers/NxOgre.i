%module NxOgre
%{
	#include "NxOgre.h"
%}

// Proper Java enums
#ifdef SWIGJAVA
%include "enums.swg"
#endif

typedef float 				NxReal;
typedef long long			NxI64;
typedef signed int			NxI32;
typedef signed short		NxI16;
typedef signed char			NxI8;

typedef unsigned long long	NxU64;
typedef unsigned int		NxU32;
typedef unsigned short		NxU16;
typedef unsigned char		NxU8;

typedef float				NxF32;
typedef double				NxF64;


%include "std_string.i"

%ignore NxOgre::Serialiser::exportWorldToString(NxOgre::Serialiser::BlueprintsFormat);
%ignore NxOgre::Serialiser::exportWorldToFile(NxOgre::Serialiser::BlueprintsFormat, NxString);
%ignore NxOgre::Serialiser::importWorldFromString(NxOgre::Serialiser::BlueprintsFormat, NxString);
%ignore NxOgre::Serialiser::importWorldFromFile(NxOgre::Serialiser::BlueprintsFormat, NxString);

%ignore NxOgre::simulateWorldGeometry(Scene*, const Ogre::String&);

%ignore NxOgre::WheelSet::attachNewWheel(NxReal, ShapeParams, WheelParams);
%ignore NxOgre::WheelSet::attachNewWheel(NxReal, ShapeParams);
%ignore NxOgre::WheelSet::attachNewWheel(NxReal, WheelParams);
%ignore NxOgre::WheelSet::attachNewWheel(NxReal);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, NxReal radius, ShapeParams, WheelParams);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, NxReal radius, ShapeParams);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, NxReal radius);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, NxReal radius, WheelParams);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, ShapeParams, WheelParams);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, WheelParams);
%ignore NxOgre::WheelSet::createSixWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, Ogre::Vector3, ShapeParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, NxReal radius, ShapeParams, WheelParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, NxReal radius, ShapeParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, NxReal radius);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, NxReal radius, WheelParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, ShapeParams, WheelParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, WheelParams);
%ignore NxOgre::WheelSet::createThreeWheelSet(Actor*, Ogre::Vector3, Ogre::Vector3, ShapeParams);

%ignore NxOgre::Wheel::addEntity(Ogre::String, Ogre::Vector3);
%ignore NxOgre::Wheel::addEntity(Ogre::String);

%rename (NxOgre_Actor) NxOgre::Actor;
%rename (NxOgre_Body) NxOgre::Body;
%rename (NxOgre_Character) NxOgre::Character;

#ifdef NX_USE_CHARACTER_API
#	undef NX_USE_CHARACTER_API
#endif
#define NX_USE_CHARACTER_API 1

#ifdef NxExport
#	undef NxExport
#endif
#define NxExport

%include "../../3rdparty/nxogre/include/NxOgrePrerequisites.h"
%include "../../3rdparty/nxogre/include/NxOgreContainer.h"
%include "../../3rdparty/nxogre/include/NxOgreParams.h"
%include "../../3rdparty/nxogre/include/NxOgrePose.h"
%include "../../3rdparty/nxogre/include/NxOgreShape.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeConvex.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeMesh.h"
%include "../../3rdparty/nxogre/include/NxOgreShapePrimitives.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeTerrain.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeWheel.h"

%ignore NxOgre::CubeShape::mShapeDescription;
%ignore NxOgre::CapsuleShape::mShapeDescription;
%ignore NxOgre::ConvexShape::mShapeDescription;
%ignore NxOgre::PrismShape::mShapeDescription;
%ignore NxOgre::TerrainShape::mShapeDescription;
%ignore NxOgre::GroundShape::mShapeDescription;
%ignore NxOgre::SphereShape::mShapeDescription;
%ignore NxOgre::TriangleMeshShape::mShapeDescription;
%ignore NxOgre::WheelShape::mShapeDescription;

%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprint.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprintConvex.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprintMesh.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprintPrimitives.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprintTerrain.h"
%include "../../3rdparty/nxogre/include/NxOgreShapeBlueprintWheel.h"
%include "../../3rdparty/nxogre/include/NxOgreCharacterController.h"
%ignore NxOgre::Actor::getScene();
%include "../../3rdparty/nxogre/include/NxOgreActor.h"
%include "../../3rdparty/nxogre/include/NxOgreBody.h"
%include "../../3rdparty/nxogre/include/NxOgreCharacter.h"

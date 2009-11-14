-- Some global vars
BINDIR = "bin/"
LIBDIR = "bin/"
OBJDIR = "build/"
if (windows) then
	PLATFORMDIR = "/windows/"
elseif (linux) then
	PLATFORMDIR = "/linux/"
elseif (macosx) then
	PLATFORMDIR = "/osx/"
end
DEBUGDIR = PLATFORMDIR .. "debug/"
RELEASEDIR = PLATFORMDIR .. "release/"
BUILDFLAGS = { "no-pch", "no-main" }

if (windows) then
	CGDIR = "C:/Program Files/NVIDIA Corporation/Cg"
	PHYSXPATH = "$(PHYSX_DIR)"
	OPENALPATH = "$(OPENAL_DIR)"
	JAVAHOME = "$(JAVA_HOME)"
elseif (linux) then
	CGDIR = "/usr"
	OPENALPATH = "/usr/include/OpenAL"
	JAVAHOME = "$JAVA_HOME"
	PHYSXPATH = "/usr/include/PhysX/v2.8.1"
end

-- Inserts the include paths of all Myoushu dependencies, including the Myoushu include paths
function insertMyoushuDependantIncludes(rootDir, thirdPartyDir, includesList)
	table.insert(includesList, {
		rootDir .. "Myoushu/include",
		rootDir .. "Myoushu/Wrappers/MyoushuLua",
		rootDir .. "Myoushu/MyoushuDotScene/include",
		thirdPartyDir .. "dotscene/DotSceneInterface/Include",
		thirdPartyDir .. "dotscene/XmlNodeProcessor",
		thirdPartyDir .. "ogreHDRCompositor/includes",
		thirdPartyDir .. "ois-1.0.0/include",
		thirdPartyDir .. "freetype-2.3.2/include",
		thirdPartyDir .. "freeimage-3.9.3/Source",
		thirdPartyDir .. "xerces-2.7.0/src",
		thirdPartyDir .. "addons/DotSceneLoader/include",
		thirdPartyDir .. "addons/MovableText/include",
		thirdPartyDir .. "addons/ogreopcode-0.1.3/include",
		thirdPartyDir .. "addons/ogreopcode-0.1.3/include/Opcode",
		thirdPartyDir .. "addons/ogreopcode-0.1.3/include/Opcode/Ice",
		thirdPartyDir .. "addons/ResourceManagers/TextFileManager/include",
		thirdPartyDir .. "boost-1.34/",
		thirdPartyDir .. "lua-5.1.3/src",
		thirdPartyDir .. "pcre-7.0/include",
		thirdPartyDir .. "poco-1.3.2/Foundation/include",
		thirdPartyDir .. "poco-1.3.2/Net/include",
		thirdPartyDir .. "poco-1.3.2/Util/include",
		thirdPartyDir .. "poco-1.3.2/XML/include",
		thirdPartyDir .. "ogre/OgreMain/include",
		thirdPartyDir .. "ogre/RenderSystems/GL/include",
		thirdPartyDir .. "ogre/RenderSystems/GL/include/GL",
		thirdPartyDir .. "ogre/RenderSystems/GL/src/atifs/include",
		thirdPartyDir .. "ogre/RenderSystems/GL/src/GLSL/include",
		thirdPartyDir .. "ogre/RenderSystems/GL/src/nvparse/",
		thirdPartyDir .. "ogre/PlugIns/OctreeSceneManager/include",
		thirdPartyDir .. "nxogre/include",
		thirdPartyDir .. "tinyxml/include",
		thirdPartyDir .. "zziplib-0.13.49",
		thirdPartyDir .. "zlib-1.2.3",
		thirdPartyDir .. "ois-1.0.0/include",
		thirdPartyDir .. "MyGUI_2.0.1_source/RenderSystems/Ogre/OgreRenderSystem/include",
		thirdPartyDir .. "MyGUI_2.0.1_source/MyGUIEngine/include",
		thirdPartyDir .. "MyGUI_2.0.1_source/LayoutEditor",
		thirdPartyDir .. "ogredotscene/trunk/OgreDotScene/OgreDotScene/include",
		thirdPartyDir .. "ogredotscene/trunk/FDotScene3.05B/FDotScene",
		thirdPartyDir .. "ogredotscene/trunk/FDotScene3.05B/FDotScene/LibXML/include",
		thirdPartyDir .. "ogg/include",
		thirdPartyDir .. "vorbis/include",
		thirdPartyDir .. "ogreoggsound/include",
		thirdPartyDir .. "boost-1.34",
		thirdPartyDir .. "sqlite",
		PHYSXPATH .. "/SDKs/Physics/include",
		PHYSXPATH .. "/SDKs/Foundation/include",
		PHYSXPATH .. "/SDKs/Cooking/include",
		PHYSXPATH .. "/SDKs/PhysXLoader/include",
		PHYSXPATH .. "/SDKs/NxCharacter/include",
		OPENALPATH .. "/include",
		JAVAHOME .. "/include",
		JAVAHOME .. "/include/win32"
		})
end

-- Inserts all libs needed to compile an app against Myoushu
function insertMyoushuDependantLibs(libsList)
	table.insert(libsList, {
		"ois",
		"addons",
		"DevIL",
		"ogremain",
		"ogreoctree",
		"nxogre",
		"pcre",
		"poco_foundation",
		"poco_util",
		"poco_net",
		"zzip",
		"zlib",
		"freetype",
		"freeimage",
		"lua",
		"tinyxml",
		"mygui",
		"mygui_ogrerendersystem",
		--"OgreCollada",
		"sqlite",
		"myoushu"
		})
end

-- Inserts all defines needed to compile an app against Myoushu
function insertMyoushuDependantDefines(definesList)
	if (windows) then
		table.insert(definesList, {"WIN32", "LUA_BUILD_AS_DLL", "POCO_NO_AUTOMATIC_LIBS", "OIS_DYNAMIC_LIB", "BOOST_THREAD_USE_DLL", "BOOST_THREAD_NO_LIB"})
	elseif (linux) then
		table.insert(definesList, {"LINUX", "NX_LINUX", "NXOGRE_LINUX", "BOOST_THREAD_NO_LIB"})
	end
end

project.name = "astt_all"
project.bindir = BINDIR .. PLATFORMDIR
project.libdir = LIBDIR .. PLATFORMDIR
project.objdir = OBJDIR

--SQLite (3rd party)
dopackage("3rdparty/sqlite/sqlite.lua")
-- Boost threads (3rd party)
dopackage("3rdparty/boost-1.34/boost_thread.lua")
-- 3rd party ogre addons
dopackage("3rdparty/addons/addons.lua")
--Freetype (3rd party)
dopackage("3rdparty/freetype-2.3.2/freetype.lua")
--FreeImage (3rd party)
dopackage("3rdparty/freeimage-3.9.3/freeimage.lua")
--tolua (3rd party)
--dopackage("3rdparty/tolua++-1.0.92/tolua.lua")
--Lua (3rd party)
dopackage("3rdparty/lua-5.1.3/lua")
--TinyXML (3rd party)
dopackage("3rdparty/tinyxml/tiny.lua")
--OIS (3rd party)
dopackage("3rdparty/ois-1.0.0/ois.lua")
--Ogre (3rd party)
dopackage("3rdparty/ogre/OgreMain/ogremain.lua")
--Ogre Octree Plugin(3rd party)
dopackage("3rdparty/ogre/PlugIns/ogreoctree.lua")
--Ogre ParticleFX Plugin (3rd party)
dopackage("3rdparty/ogre/PlugIns/ogreparticlefx.lua")
--Ogre CG plugin (3rd party)
dopackage("3rdparty/ogre/PlugIns/ogrecg.lua")
--Ogre OpenGL Render System (3rd party)
dopackage("3rdparty/ogre/RenderSystems/ogregl.lua")
if (windows) then
	--Ogre D3D 9 Render System (3rd party)
	dopackage("3rdparty/ogre/RenderSystems/ogred3d9.lua")
	--Ogre D3D 10 Render System (3rd party)
	dopackage("3rdparty/ogre/RenderSystems/ogred3d10.lua")
end
-- HDRLib addon for Ogre
dopackage("3rdparty/ogreHDRCompositor/ogreHDRCompositor.lua")
-- DotSceneFormat addon for Ogre
dopackage("3rdparty/dotscene/dotscene.lua")
--NxOgre PhysX Wrapper (3rd party)
dopackage("3rdparty/nxogre/nxogre.lua")
--Flour mesh converter for NxOgre (3rd party)
--dopackage("3rdparty/nxogre/flour.lua")
--DevIL (3rd party)
dopackage("3rdparty/DevIL/DevIL.lua")

--FCollada (3rd party)
--dopackage("3rdparty/fcollada-3.04e/fcollada.lua")

--dofile("3rdparty/ogrecollada/trunk/premake/config.lua")
--dofile("3rdparty/ogrecollada/trunk/premake/helpers.lua")

-- override objsdir set in OgreCollada's config.lua script
--objsdir = "../../../build/"

--LibXML
--dopackage("3rdparty/ogrecollada/trunk/premake/LibXML")
--FCollada
--dopackage("3rdparty/ogrecollada/trunk/premake/FCollada")
--OgreCollada
--dopackage("3rdparty/ogrecollada/trunk/premake/OgreCollada")
--ColladaViewer
--dopackage("3rdparty/ogrecollada/trunk/premake/ColladaViewer")
--PCRE (3rd party)
dopackage("3rdparty/pcre-7.0/pcre.lua")
--POCO (3rd party)
dopackage("3rdparty/poco-1.3.2/poco_foundation.lua")
dopackage("3rdparty/poco-1.3.2/poco_net.lua")
dopackage("3rdparty/poco-1.3.2/poco_xml.lua")
dopackage("3rdparty/poco-1.3.2/poco_util.lua")
--ZZip (3rd party)
dopackage("3rdparty/zziplib-0.13.49/zzip.lua")
--Zlib (3rd party)
dopackage("3rdparty/zlib-1.2.3/zlib.lua")
--MyGUI (3rd party)
dopackage("3rdparty/MyGUI_2.0.1_source/mygui.lua")
--MyGUI_OgreRenderSystem (3rd party)
dopackage("3rdparty/MyGUI_2.0.1_source/mygui_ogrerendersystem.lua")
-- OGG (3rd party)
dopackage("3rdparty/ogg/ogg.lua")
-- Vorbis (3rd party)
dopackage("3rdparty/vorbis/vorbis.lua")
-- OgreOggSound (3rd party)
dopackage("3rdparty/ogreoggsound/ogreoggsound.lua")

-- Myoushu Engine
dopackage("Myoushu/myoushu.lua")
-- MyoushuDotScene
dopackage("Myoushu/MyoushuDotScene/myoushuDotScene.lua")
-- MyoushuOgreOggSound
dopackage("Myoushu/MyoushuOgreOggSound/myoushuOgreOggSound.lua")
-- Myoushu Samples: SampleCubes
dopackage("Myoushu/Samples/SampleCubes/samplecubes.lua")
-- Myoushu Samples: SampleCollada
--dopackage("Myoushu/Samples/SampleCollada/samplecollada.lua")
-- Myoushu Samples: SampleCharacter
dopackage("Myoushu/Samples/SampleCharacter/samplecharacter.lua")
-- Myoushu Samples: SampleNetwork
dopackage("Myoushu/Samples/SampleNetwork/samplenetwork.lua")
-- Myoushu Samples: SampleDotScene
dopackage("Myoushu/Samples/SampleDotScene/sampledotscene.lua")
-- Myoushu Samples: SampleLua
dopackage("Myoushu/Samples/SampleLua/samplelua.lua")
-- Myoushu Samples: SampleGameLog
dopackage("Myoushu/Samples/SampleGameLog/samplegamelog.lua")

-- Myoushua Wrappers: Java
dopackage("Myoushu/Wrappers/MyoushuJava/MyoushuJava.lua")

--MyGUI Layouteditor(3rd party)
dopackage("3rdparty/MyGUI_2.0.1_source/mygui_layouteditor.lua")
--tolua binary	
--dopackage("3rdparty/tolua++-1.0.92/toluabin.lua")
--OgreXMLConverter
dopackage("3rdparty/ogrexmlconverter/ogrexmlconverter.lua")

-- Road to the Moon
dopackage("Road to the Moon/roadtothemoon.lua")
-- Social Skills
dopackage("Social Skills/socialskills.lua")

--inline astt binary
asttBin = newpackage()
asttBin.name = "astt"
asttBin.config["Debug"].target = asttBin.name .. "_d"

-- Project root directory
thirdPartyDir = "3rdparty/"
rootDir = ""

objDir = rootDir .. OBJDIR .. asttBin.name
binDir = rootDir .. BINDIR .. PLATFORMDIR
libDir = rootDir .. LIBDIR .. PLATFORMDIR
asttBin.libdir = libDir
asttBin.bindir = binDir
asttBin.config["Debug"].objdir = objDir .. DEBUGDIR
asttBin.config["Release"].objdir = objDir .. RELEASEDIR

table.insert(asttBin.config["Debug"].buildflags, BUILDFLAGS)
table.insert(asttBin.config["Release"].buildflags, BUILDFLAGS)

asttBin.kind = "dll"
asttBin.defines = { "ASTT_DLL", "POCO_NO_AUTOMATIC_LIBS" }
asttBin.language = "c++"

insertMyoushuDependantDefines(asttBin.defines)

asttBin.includepaths = { "include", "Wrappers/ASTTLua" }
insertMyoushuDependantIncludes(rootDir, thirdPartyDir, asttBin.includepaths)

asttBin.files = { matchfiles("Wrappers/ASTTLua/*.h"), matchfiles("Wrappers/ASTTLua/*.cpp"), matchfiles("include/*.h"), matchfiles("src/*.cpp") }
asttBin.excludes = { "src/winmain.cpp" }
asttBin.links = { }
insertMyoushuDependantLibs(asttBin.links)

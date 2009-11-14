package.name = "myoushu"
package.config["Debug"].target = package.name .. "_d"

-- Project root directory
thirdPartyDir = "../3rdparty/"
rootDir = thirdPartyDir .. "../"

objDir = rootDir .. OBJDIR ..package.name
binDir = rootDir .. BINDIR .. PLATFORMDIR
libDir = rootDir .. LIBDIR .. PLATFORMDIR
package.libdir = libDir
package.bindir = binDir
package.config["Debug"].objdir = objDir .. DEBUGDIR
package.config["Release"].objdir = objDir .. RELEASEDIR

table.insert(package.config["Debug"].buildflags, BUILDFLAGS)
table.insert(package.config["Release"].buildflags, BUILDFLAGS)

package.kind = "dll"
package.language = "c++"
package.includepaths = {
	"include",
	"Wrappers/MyoushuLua",
	"MyoushuDotScene/include",
	thirdPartyDir .. "dotscene/DotSceneInterface/Include",
	thirdPartyDir .. "dotscene/XmlNodeProcessor",
	thirdPartyDir .. "ogreHDRCompositor/includes",
	thirdPartyDir .. "ois-1.0.0/include",
	thirdPartyDir .. "freetype-2.3.2/include",
	thirdPartyDir .. "freeimage-3.9.3/Source",
	thirdPartyDir .. "addons/DotSceneLoader/include",
	thirdPartyDir .. "addons/MovableText/include",
	thirdPartyDir .. "addons/ogreopcode-0.1.3/include",
	thirdPartyDir .. "addons/ogreopcode-0.1.3/include/Opcode",
	thirdPartyDir .. "addons/ogreopcode-0.1.3/include/Opcode/Ice",
	thirdPartyDir .. "addons/ResourceManagers/TextFileManager/include",
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
	thirdPartyDir .. "ogrecollada/trunk/OgreCollada/OgreCollada/include",
	thirdPartyDir .. "ogrecollada/trunk/FCollada3.05B/FCollada",
	thirdPartyDir .. "ogrecollada/trunk/FCollada3.05B/FCollada/LibXML/include",
	thirdPartyDir .. "ogg/include",
	thirdPartyDir .. "vorbis/include",
	thirdPartyDir .. "boost-1.34",
	thirdPartyDir .. "ogreoggsound/include",
	thirdPartyDir .. "sqlite"
}
package.defines = { "SWIGRUNTIME=SWIGEXPORT" }
package.files = { matchfiles("include/*.h", "src/*.cpp", "Wrappers/MyoushuLua/*.h", "Wrappers/MyoushuLua/*.cpp") }
package.excludes = { "include/OgreColladaContentImporter.h", "src/OgreColladaContentImporter.cpp" }
package.links = { 
	"ois",
	"addons",
	"ogremain",
	"ogreoctree",
	"ogregl",
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
	"ogg",
	"vorbis",
	"ogreoggsound",
	"sqlite"
}

package.config["Debug"].defines = {
	"DEBUG",
	"_DEBUG",
	"_STLP_DEBUG",
	"MYOUSHU_DEBUG"
}
if (windows) then
	table.insert(package.links, {"ogred3d9"})
	table.insert(package.defines, { "WIN32", "MYOUSHU_DLL", "LUA_BUILD_AS_DLL", "POCO_NO_AUTOMATIC_LIBS", "OIS_DYNAMIC_LIB", "BOOST_THREAD_USE_DLL", "BOOST_THREAD_NO_LIB" })
	package.libpaths = {
		PHYSXPATH .. "/SDKs/lib/win32",
		OPENALPATH .. "/libs/Win32"
	}
elseif (linux) then
	table.insert(package.links, {"ogregl"})
	package.libpaths = {
		"/usr/lib/PhysX/v2.8.1/lib",
		OPENALPATH .. "/libs/Win32"
	}
	table.insert(package.defines, { "LINUX", "NX_LINUX", "NXOGRE_LINUX", "BOOST_THREAD_NO_LIB" })
end

table.insert(package.includepaths, {
	PHYSXPATH .. "/SDKs/Physics/include",
	PHYSXPATH .. "/SDKs/Foundation/include",
	PHYSXPATH .. "/SDKs/Cooking/include",
	PHYSXPATH .. "/SDKs/PhysXLoader/include",
	PHYSXPATH .. "/SDKs/NxCharacter/include",
	OPENALPATH .. "/include",
	JAVAHOME .. "/include",
	JAVAHOME .. "/include/win32"
})


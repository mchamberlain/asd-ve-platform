package.name = "myoushuOgreOggSound"
package.config["Debug"].target = package.name .. "_d"

-- Project root directory
thirdPartyDir = "../../3rdparty/"
rootDir = thirdPartyDir .. "../"

objDir = rootDir .. OBJDIR .. package.name
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

package.defines = { "MYOUSHU_OGRE_OGG_SOUND_DLL" }
insertMyoushuDependantDefines(package.defines)

package.includepaths = {
	"include"
}
insertMyoushuDependantIncludes(rootDir, thirdPartyDir, package.includepaths)

package.files = {	matchfiles(
	"include/*.h",
	"src/*.cpp"
)}

package.config["Debug"].defines = {
	"DEBUG",
	"_DEBUG",
	"_STLP_DEBUG"
}

package.links = { "myoushu", "ogremain", "ogreoggsound" }
package.libpaths = {}
insertMyoushuDependantLibs(package.links, package.libpaths, rootDir)

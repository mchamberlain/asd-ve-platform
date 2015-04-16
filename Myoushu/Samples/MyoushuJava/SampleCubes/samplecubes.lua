package.name = "SampleCubes"
package.config["Debug"].target = package.name .. "_d"

-- Project root directory
thirdPartyDir = "../../../3rdparty/"
rootDir = thirdPartyDir .. "../"

objDir = "./" .. OBJDIR .. package.name
binDir = "./" .. BINDIR .. PLATFORMDIR
libDir = "./" .. LIBDIR .. PLATFORMDIR
package.libdir = libDir
package.bindir = binDir
package.config["Debug"].objdir = objDir .. DEBUGDIR
package.config["Release"].objdir = objDir .. RELEASEDIR

table.insert(package.config["Debug"].buildflags, BUILDFLAGS)
table.insert(package.config["Release"].buildflags, BUILDFLAGS)

package.kind = "exe"
package.defines = {  }
package.language = "c++"

if (windows) then
	table.insert(package.defines, {"WIN32", "LUA_BUILD_AS_DLL", "POCO_NO_AUTOMATIC_LIBS", "OIS_DYNAMIC_LIB"})
elseif (linux) then
	table.insert(package.defines, {"LINUX", "NX_LINUX"})
end

package.includepaths = { "include" }
insertMyoushuDependantIncludes(rootDir, thirdPartyDir, package.includepaths)

package.files = { matchfiles("include/*.h"), matchfiles("src/*.cpp") }
package.excludes = { "src/winmain.cpp" }
package.libpaths = {}
insertMyoushuDependantLibs(package.links, package.libpaths, rootDir)

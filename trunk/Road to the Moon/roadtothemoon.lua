package.name = "RoadToTheMoon"
package.config["Debug"].target = package.name .. "_d"

-- Project root directory
thirdPartyDir = "../3rdparty/"
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

insertMyoushuDependantDefines(package.defines)

package.includepaths = { "include" }
insertMyoushuDependantIncludes(rootDir, thirdPartyDir, package.includepaths)

package.files = { matchfiles("include/*.h"), matchfiles("src/*.cpp") }
package.excludes = { "src/winmain.cpp" }
package.links = { "astt" }
insertMyoushuDependantLibs(package.links)

package.name = "MyoushuJava"
package.config["Debug"].target = package.name .. "_d"

-- Project root directory
thirdPartyDir = "../../../3rdparty/"
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
if (windows) then
	package.defines = { "MYOUSHU_JAVA_DLL" }
end
package.language = "c++"

insertMyoushuDependantDefines(package.defines)

package.includepaths = { }
insertMyoushuDependantIncludes(rootDir, thirdPartyDir, package.includepaths)

package.files = { matchfiles("*.h"), matchfiles("*.cpp") }
package.links = { }
insertMyoushuDependantLibs(package.links)

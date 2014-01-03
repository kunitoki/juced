
project.name = "FontSerialiser"
project.bindir = "../../../../../bin"
project.libdir = "../../../../../bin"
project.configs = { "Debug", "Release" }

package = newpackage()
package.name = "FontSerialiser"
package.target = "fontserialiser"
package.kind = "exe"
package.language = "c++"
package.objdir = project.bindir .. "/intermediate"
package.linkflags = { "static-runtime" }

package.config["Debug"].objdir       = package.objdir .. "/" .. project.name .. "Debug"
package.config["Debug"].defines      = { "LINUX=1", "DEBUG=1", "_DEBUG=1" };
package.config["Debug"].buildoptions = { "-D_DEBUG -ggdb" }

package.config["Release"].objdir     = package.objdir .. "/" .. project.name .. "Release"
package.config["Release"].defines    = { "LINUX=1", "NDEBUG=1" };

package.includepaths = { 
    "/usr/include",
    "/usr/include/freetype2"
}

package.libpaths = { 
    "/usr/X11R6/lib/"
}

package.links = { 
    "freetype", "pthread", "rt", "X11", "Xrender", "Xi", "GL", "GLU", "Xinerama", "asound"
}

package.files = { matchfiles (
    "../../*.h",
    "../../*.cpp"
    )
}

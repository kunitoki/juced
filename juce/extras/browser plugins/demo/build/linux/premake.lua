
project.name = "JuceBrowserPluginDemo"
project.bindir = "build"
project.libdir = "build"

project.configs = { "Debug", "Release" }

package = newpackage()
package.name = "JuceBrowserPluginDemo"
package.target = "JuceBrowserPluginDemo"
package.kind = "dll"
package.language = "c++"

package.objdir = "build/intermediate"
package.config["Debug"].objdir   = "build/intermediate/Debug"
package.config["Release"].objdir = "build/intermediate/Release"

package.config["Debug"].defines         = { "LINUX=1", "DEBUG=1", "_DEBUG=1" };
package.config["Debug"].buildoptions    = { "-ggdb -Wall" }

package.config["Release"].defines       = { "LINUX=1", "NDEBUG=1" };
package.config["Release"].buildoptions  = { "-O2 -Wall -fvisibility=hidden" }

package.buildoptions = { "-L/usr/lib/xulrunner" }

package.includepaths = { 
    "../../src/", 
    "../../../wrapper/", 
    "/usr/include/",
    "/usr/include/freetype2/",
    "/usr/include/nspr/",
    "/usr/include/xulrunner-1.9/stable/"
}

package.libpaths = { 
    "/usr/X11R6/lib/"
}

package.config["Debug"].links = { 
    "freetype", "pthread", "rt", "X11", "Xss", "GL", "GLU", "Xinerama", "asound"
}

package.config["Release"].links = { 
    "freetype", "pthread", "rt", "X11", "Xss", "GL", "GLU", "Xinerama", "asound"
}

package.linkflags = { "static-runtime" }

package.files = { matchfiles (
    "../../src/*.h",
    "../../src/*.cpp",
    "../../../wrapper/*.h",
    "../../../wrapper/*.cpp"
    )
}

package.postbuildcommands = {
    "sudo cp build/libJuceBrowserPluginDemo.so /usr/lib/nsbrowser/plugins/",
    "sudo cp build/libJuceBrowserPluginDemo.so /opt/opera/lib/opera/plugins/",
}


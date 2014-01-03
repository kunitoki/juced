project.name = "HybridReverb2vst"
project.bindir = "build"
project.libdir = "build"

project.configs = { "Release", "Debug" }

package = newpackage()
package.name = "HybridReverb2vst"
package.kind = "dll"
package.language = "c++"

package.objdir = "build/intermediate"
package.config["Debug"].objdir = "build/intermediate/Debug"
package.config["Release"].objdir = "build/intermediate/Release"

package.includepaths = {
    "/usr/include",
    "/usr/include/freetype2",
    "../../src",
    "../../../juce",
    "../../../vstsdk2.4",
    "../../../juce/extras/audio\ plugins",
    "../../../juce/extras/audio\ plugins/wrapper"
}

package.libpaths = {
    "../../../juce/bin/",
    "/usr/X11R6/lib/"
}

package.config["Debug"].links = {
    "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "juce_debug", "m", "gomp"
}

package.config["Release"].links = {
    "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "juce", "m", "gomp"
}

package.config["Debug"].buildoptions = {
" -O0 -march=pentium3 -fopenmp -DLINUX -DHYBRIDREVERB2_VST_PLUGIN",
" `pkg-config fftw3f --cflags`"
}

package.config["Release"].buildoptions = {
" -O2 -march=pentium3 -fomit-frame-pointer -funroll-loops -fopenmp -DLINUX -DHYBRIDREVERB2_VST_PLUGIN",
" `pkg-config fftw3f --cflags`"
}

package.linkoptions = {
"`pkg-config fftw3f --libs`"
}

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    ),
    matchfiles (
        "../../src/libHybridConv/*.c"
    )
}

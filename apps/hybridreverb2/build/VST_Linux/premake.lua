dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("HybridReverb2vst", "dll", true, false)

table.insert (package.defines, "HYBRIDREVERB2_VST_PLUGIN=1")

package.includepaths = { 
    "/usr/include",
    "/usr/include/freetype2",
    "../../src",
    "../../../../juce",
    "../../../../vst/vstsdk2.4",
    "../../../../juce/extras/audio\ plugins",
    "../../../../juce/extras/audio\ plugins/wrapper"
}

package.libpaths = { 
    "/usr/X11R6/lib/",
    "../../../bin/"
}

package.config["Debug"].links = { 
    "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "juce_debug", "m", "gomp"
}

package.config["Release"].links = { 
    "freetype", "pthread", "rt", "X11", "GL", "GLU", "Xinerama", "asound", "juce", "m", "gomp"
}

package.config["Debug"].buildoptions = {
" -O0 -march=pentium3 -fopenmp",
" `pkg-config fftw3f --cflags`"
}

package.config["Release"].buildoptions = {
" -O2 -march=pentium3 -fomit-frame-pointer -funroll-loops -fopenmp",
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

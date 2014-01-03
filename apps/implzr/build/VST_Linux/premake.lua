
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("implzr", "dll", true, false)

table.insert (package.defines, "LIBFV3_FLOAT=1")
table.insert (package.defines, "LIBSRATE2_FLOAT=1")
table.insert (package.defines, "XIMPLZR_VST_PLUGIN=1")
table.insert (package.links, "fftw3f")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}



dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("peggy2000vst", "dll", true, false)

table.insert (package.defines, "XPEGGY_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}



dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("drumsynthvst", "dll", true, false)

table.insert (package.defines, "XDRUMSYNTH_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


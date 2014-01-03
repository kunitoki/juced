
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("helixvst", "dll", true, false)

table.insert (package.defines, "HELIX_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.c",
        "../../src/*.cpp"
    )
}



dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("nekobeevst", "dll", true, false)

table.insert (package.defines, "XNEKOBEE_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


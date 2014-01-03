
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("analyzervst", "dll", true, false)

table.insert (package.defines, "XANALYZER_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


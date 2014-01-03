
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("vexvst", "dll", true, false)

table.insert (package.defines, "XVEX_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


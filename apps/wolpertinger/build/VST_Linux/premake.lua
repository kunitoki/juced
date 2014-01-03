
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("wolpertingervst", "dll", true, false)

table.insert (package.defines, "XWOLPERTINGER_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


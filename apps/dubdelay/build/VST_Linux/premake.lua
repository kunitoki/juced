
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("dubdelay", "dll", true, false)

table.insert (package.defines, "XDUBDELAY_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


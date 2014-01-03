
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("dubdelay", "exe", true, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


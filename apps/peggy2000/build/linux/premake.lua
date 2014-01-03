
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("peggy2000", "exe", true, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}

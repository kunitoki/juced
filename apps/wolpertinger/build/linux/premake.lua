
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("wolpertinger", "exe", true, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}

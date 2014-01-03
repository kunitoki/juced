
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("analyzer", "exe", true, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cc",
        "../../src/*.cpp"
    )
}


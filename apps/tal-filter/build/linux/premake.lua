
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("tal-filter", "exe", true, false)

table.insert (package.includepaths, 1, "../../src")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}

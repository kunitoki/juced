
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("jacked", "exe", true, false)

table.insert (package.includepaths, "../../src")
table.insert (package.links, "jack")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


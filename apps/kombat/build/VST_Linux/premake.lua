
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("kombat", "dll", true, false)

table.insert (package.includepaths, "../../src")

package.files = {
    matchfiles (
        "../../../../wrapper/*.h",
        "../../../../wrapper/*.cpp",
        "../../../../wrapper/formats/VST/*.cpp"
    ),
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


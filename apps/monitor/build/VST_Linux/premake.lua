
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("monitor", "dll", true, false)

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


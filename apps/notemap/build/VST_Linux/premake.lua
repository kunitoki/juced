
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("notemap", "dll", true, false)

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


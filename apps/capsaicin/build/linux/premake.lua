
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("capsaicin", "exe", true, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.c",
        "../../src/*.cpp"
    )
}

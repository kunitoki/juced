
dofile ("../../../tools/linux/premake.lua")

package = make_plugin_project ("unit_testing", "exe", true, false, "../../../bin")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


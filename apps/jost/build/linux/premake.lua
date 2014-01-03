
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("jost", "exe", true, false)
package = configure_jost_libraries (package, true)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


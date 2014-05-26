
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("jostvst", "dll", true, false)
package = configure_jost_libraries (package, false)

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


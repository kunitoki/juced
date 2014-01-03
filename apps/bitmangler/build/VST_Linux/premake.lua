
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("bitmanglervst", "dll", true, false)

table.insert (package.defines, "XBITMANGLER_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}



dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("tal-filtervst", "dll", true, false)

table.insert (package.includepaths, 1, "../../src")

table.insert (package.defines, "XTALFILTER_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


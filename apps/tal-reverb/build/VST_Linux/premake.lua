
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("tal-reverbvst", "dll", true, false)

table.insert (package.defines, "XTALREVERB_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp"
    )
}


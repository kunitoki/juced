
dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("soundcrabvst", "dll", true, false)

table.insert (package.includepaths, 1, "../../src")
table.insert (package.includepaths, 1, "../../src/Synth")
table.insert (package.defines, "HAVE_CONFIG_H=1")

table.insert (package.defines, "XSOUNDCRAB_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.c",
        "../../src/*.cpp"
    )
}



dofile ("../../../../tools/linux/premake.lua")

package = make_plugin_project ("eqinoxvst", "dll", true, false)
table.insert (package.defines, "XEQ_VST_PLUGIN=1")

package.files = {
    matchrecursive (
        "../../src/*.h",
        "../../src/*.cpp",
        "./exports.def"
    )
}


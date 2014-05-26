
--======================================================================================
function make_library_project (name) 

    print ("==== Configuring " .. name .. " ====")
    print ("Configuring GNU makefiles:")

    project.name = name
    project.bindir = "../../../bin"
    project.libdir = project.bindir

    project.configs = { "Debug", "Release", "Release32" }

    package = newpackage()
    package.name = project.name
    package.target = project.name
    package.kind = "lib"
    package.language = "c++"
    package.linkflags = { "static-runtime" }
    package.objdir = project.bindir .. "/intermediate_" .. OS
    package.defines = {}
    package.includepaths = {}
    package.libpaths = {}
    package.links = {}
    
    package.config["Debug"].target            = project.name .. "_debug"
    package.config["Debug"].objdir            = package.objdir .. "/" .. project.name .. "Debug"
    package.config["Debug"].defines           = { "DEBUG=1", "_DEBUG=1" }
    package.config["Debug"].buildoptions      = { "-O0 -g -Wall -fPIC" }
    package.config["Debug"].links             = { "dl" }

    package.config["Release"].target          = project.name
    package.config["Release"].objdir          = package.objdir .. "/" .. project.name .. "Release"
    package.config["Release"].defines         = { "NDEBUG=1" }
    package.config["Release"].buildoptions    = { "-O2 -pipe -fvisibility=hidden -Wall -fPIC" }
    package.config["Release"].buildflags      = configure_default_release_options ()
    package.config["Release"].links           = { "dl" }

    package.config["Release32"].target        = project.name .. "32"
    package.config["Release32"].objdir        = package.objdir .. "/" .. project.name .. "Release32"
    package.config["Release32"].defines       = { "NDEBUG=1" }
    package.config["Release32"].linkoptions   = { "-melf_i386" }
    package.config["Release32"].buildoptions  = { "-m32 -O2 -pipe -fvisibility=hidden -Wall -fPIC" }
    package.config["Release32"].buildflags    = configure_default_release_options ()
    package.config["Release32"].links         = { "dl" }

    package = configure_standard_options (package, false, false)

    return package
end

--======================================================================================
function make_plugin_project (name, kind, doAmalgama, libpath) 

    print ("==== Configuring " .. name .. " ====")
    print ("Configuring GNU makefiles:")

    finalRelease = false
    overrideAmalgama = false
    
    if overrideAmalgama then
        doAmalgama = true
    end

    if (libpath) then
    else
        libpath = "../../../../bin"
        if (finalRelease) then
            libpath = "../../bin"
        end
    end

    project.name = name
    project.bindir = libpath
    project.libdir = libpath
    project.configs = { "Debug", "Release" }

    if (target == "gnu") then
        table.insert (project.configs, "Release32")
    end

    package = newpackage()
    package.name = project.name
    package.target = package.name
    package.kind = kind
    package.language = "c++"
    package.linkflags = { "static-runtime" }
    package.objdir = project.bindir .. "/intermediate_" .. OS
    package.includepaths = {}
    package.defines = {}
    package.libpaths = { libpath }
    package.links = {}

    if (doAmalgama or finalRelease) then
        print ("...enabled AMALGAMA support")
        table.insert (package.defines, "JUCETICE_USE_AMALGAMA=1")
        if (finalRelease) then
            package.excludes = {
                "../../src/juce_amalgamated.cpp",
                "../../src/juce_amalgamated.h"
            }
        end
    end

    package = configure_standard_options (package, doAmalgama, true)

    return package
end

--======================================================================================
function configure_standard_options (package, doAmalgama, link_with_libraries)

    if (target == "gnu") then
        return configure_standard_options_gnu (package, doAmalgama, link_with_libraries)
    else
        return configure_standard_options_win (package, doAmalgama, link_with_libraries)
    end

end

--======================================================================================
function configure_standard_options_win (package, doAmalgama, link_with_libraries)

    addoption ("vstsdk-version",  "Specify version of VSTSDK (default 2.4)")

    if (package.kind == "dll") then
        package.targetprefix = ""
        package.targetextension = "dll"
    else
        package.kind = "winexe"
    end

    -- configuration setup ----------------------------------------------
    table.insert (package.defines, "WIN32=1")
    table.insert (package.includepaths, "../../src")
    table.insert (package.includepaths, "../../../../juce")
    table.insert (package.includepaths, "../../../../juce/src")
    table.insert (package.includepaths, "../../../../juce/extras/audio plugins")

    package.config["Debug"].target            = package.name .. "_debug"
    package.config["Debug"].objdir            = package.objdir .. "/" .. package.name .. "Debug"
    package.config["Debug"].defines           = { "DEBUG=1", "_DEBUG=1" }
    package.config["Debug"].buildoptions      = { "" }
    package.config["Debug"].buildflags        = { "no-pch" }
    package.config["Debug"].libpaths          = { "" }
    if (not doAmalgama) and (link_with_libraries) then
        package.config["Debug"].links         = { "juce_debug" }
    end

    package.config["Release"].target          = package.name
    package.config["Release"].objdir          = package.objdir .. "/" .. package.name .. "Release"
    package.config["Release"].defines         = { "NDEBUG=1" }
    package.config["Release"].buildoptions    = { "" }
    package.config["Release"].buildflags      = configure_default_release_options ()
    package.config["Release"].libpaths        = { "" }
    if (not doAmalgama) and (link_with_libraries) then
        package.config["Release"].links       = { "juce" }
    end

    -- configure step for libraries ---------------------------------------
    package = configure_vst_sdk (package, options["vstsdk-version"])

    return package
end

--======================================================================================
function configure_standard_options_gnu (package, doAmalgama, link_with_libraries)

    addoption ("disable-alsa",    "Disable ALSA support (this will disable also midi)")
    addoption ("disable-jack",    "Disable jack-audio-connection-kit")
    addoption ("disable-xshm",    "Disable SHM support for Xorg")
    addoption ("enable-opengl",   "enable OpenGL support (default disabled)")
    addoption ("enable-lash",     "Enable LASH support (default disabled)")
    addoption ("enable-xinerama", "Enable Xinerama support (default disabled)")
    addoption ("enable-glx",      "Enable GLX support for ARGB visuals (default disabled)")
    addoption ("enable-sqlite",   "Enable SQLITE support (default disabled)")
    addoption ("vstsdk-version",  "Specify version of VSTSDK (default 2.4)")

    if (package.kind == "dll") then
        package.targetprefix = ""
        package.targetextension = "so"
    end

    -- configuration setup ----------------------------------------------
    table.insert (package.defines, "LINUX=1")
    table.insert (package.links, "freetype")
    table.insert (package.links, "pthread")
    table.insert (package.links, "rt")
    table.insert (package.links, "dl")
    table.insert (package.links, "X11")
    table.insert (package.links, "Xext")
    table.insert (package.includepaths, "/usr/include")
    table.insert (package.includepaths, "/usr/include/freetype2")
    table.insert (package.includepaths, "../../../../juce")
    table.insert (package.includepaths, "../../../../juce/src")
    table.insert (package.includepaths, "../../../../juce/extras/audio plugins")
    table.insert (package.includepaths, "../../src")

    package.config["Debug"].target            = package.name .. "_debug"
    package.config["Debug"].objdir            = package.objdir .. "/" .. package.name .. "Debug"
    package.config["Debug"].defines           = { "DEBUG=1", "_DEBUG=1" }
    package.config["Debug"].buildoptions      = { "-O0 -g -Wall -fPIC" }
    package.config["Debug"].libpaths          = { "/usr/X11R6/lib/", "/usr/lib/" }
    if (not doAmalgama) and (link_with_libraries) then
        package.config["Debug"].links         = { "juce_debug" }
    end

    package.config["Release"].target          = package.name
    package.config["Release"].objdir          = package.objdir .. "/" .. package.name .. "Release"
    package.config["Release"].defines         = { "NDEBUG=1" }
    package.config["Release"].buildoptions    = { "-pipe -fvisibility=hidden -Wall -fPIC" }
    package.config["Release"].buildflags      = configure_default_release_options ()
    package.config["Release"].libpaths        = { "/usr/X11R6/lib/", "/usr/lib/" }
    if (not doAmalgama) and (link_with_libraries) then
        package.config["Release"].links       = { "juce" }
    end

    package.config["Release32"].target        = package.name .. "32"
    package.config["Release32"].objdir        = package.objdir .. "/" .. package.name .. "Release32"
    package.config["Release32"].defines       = { "NDEBUG=1" }
    package.config["Release32"].buildoptions  = { "-m32 -pipe -fvisibility=hidden -Wall -fPIC" }
    package.config["Release32"].buildflags    = configure_default_release_options ()
    package.config["Release32"].libpaths      = { "/usr/X11R6/lib32/", "/usr/lib32/" }
    package.config["Release32"].linkoptions   = { "-melf_i386" }
    if (not doAmalgama) and (link_with_libraries) then
        package.config["Release32"].links     = { "juce32" }
    end

    -- configure step for libraries ---------------------------------------
    if (os.fileexists ("/usr/include/X11/extensions/XShm.h")
        and not options["disable-xshm"]) then
        print ("...enabled XSHM support")
        table.insert (package.defines, "JUCE_USE_XSHM=1")
        if link_with_libraries then
        end
    end

    if (os.findlib ("Xinerama")
        and options["enable-xinerama"]) then
        print ("...enabled XINERAMA support")
        table.insert (package.defines, "JUCE_USE_XINERAMA=1")
        if link_with_libraries then
        end
    end

    if (os.findlib ("GL") and os.findlib ("GLU")
        and (options["enable-opengl"] or options["enable-glx"])) then
        print ("...enabled OPENGL support")
        table.insert (package.defines, "JUCE_OPENGL=1")
        if link_with_libraries then
            table.insert (package.links, "GL")
            table.insert (package.links, "GLU")
        end        

        if (options["enable-glx"]) then
            print ("...enabled GLX support")
            table.insert (package.defines, "JUCE_USE_GLX=1")
            if link_with_libraries then
                table.insert (package.links, "Xrender")
                table.insert (package.links, "Xi")
            end
        end
    end

    if (os.findlib ("sqlite3") and options["enable-sqlite"]) then
        print ("...enabled SQLITE3 support")
        table.insert (package.defines, "JUCE_SUPPORT_SQLITE=1")
        if link_with_libraries then
            table.insert (package.links, "sqlite3")
        end
    end

    -- enable these only if we are in standalone mode
    if (package.kind ~= "dll") then
    
        if (os.fileexists ("/usr/include/alsa/asoundlib.h")
            and os.findlib ("asound") 
            and not options["disable-alsa"]) then
            print ("...enabled ALSA support")
            table.insert (package.defines, "JUCE_ALSA=1")
            if link_with_libraries then
                table.insert (package.links, "asound")
            end
        end

        if (os.fileexists ("/usr/include/jack/jack.h")
            and os.findlib ("jack")
            and not options["disable-jack"]) then
            print ("...enabled JACK support")
            table.insert (package.defines, "JUCE_JACK=1")
            if link_with_libraries then
--                table.insert (package.links, "jack")
            end
        end

        if (os.fileexists ("/usr/include/lash-1.0/lash/lash.h")
            and os.findlib ("lash")
            and options["enable-lash"]) then
            print ("...enabled LASH support")
            table.insert (package.defines, "JUCE_LASH=1")
            table.insert (package.includepaths, "/usr/include/lash-1.0")
            if link_with_libraries then
                table.insert (package.links, "lash")
            end
        end
    end

    package = configure_vst_sdk (package, options["vstsdk-version"])

    return package
end

--======================================================================================
function configure_jost_libraries (package, standalone)

    addoption ("disable-vst",        "Disable VST support")
    -- addoption ("enable-surface",     "Enable surface component in debug mode (Disabled)")

    if (not standalone) then
        table.insert (package.defines, "JOST_VST_PLUGIN=1")
    end

    if not options["disable-vst"] then
        table.insert (package.defines, "JOST_USE_VST=1")
        print ("...enabled VST support")
    else
        table.insert (package.defines, "JOST_USE_VST=0")
    end

    if (target == "gnu") then

        addoption ("disable-ladspa",     "Disable LADSPA support")
        addoption ("disable-dssi",       "Disable DSSI support")
        addoption ("enable-jackbridge",  "Enable jack-audio-connection-kit 32/64 bit bridge (Disabled)")

        if (os.fileexists ("/usr/include/ladspa.h") and not options["disable-ladspa"]) then
            table.insert (package.defines, "JOST_USE_LADSPA=1")
            print ("...enabled LADSPA support")
        else
            table.insert (package.defines, "JOST_USE_LADSPA=0")
        end

        if (os.fileexists ("/usr/include/dssi.h") and not options["disable-dssi"]) then
            table.insert (package.defines, "JOST_USE_DSSI=1")
            print ("...enabled DSSI support")
        else
            table.insert (package.defines, "JOST_USE_DSSI=0")
        end

        if options["enable-jackbridge"] then
            table.insert (package.defines, "JOST_USE_JACKBRIDGE=1")
            print ("...enabled JACKBRIDGE support")
        else
            table.insert (package.defines, "JOST_USE_JACKBRIDGE=0")
        end
    end
    
    return package
end

--======================================================================================
function configure_vst_sdk (package, version)

    if (not version) then
        version = "2.4"
    end

    if (version == "2.3") then
        -- we use vstsdk 2.3
        print ("...enabled VSTSDK 2.3");
        table.insert (package.defines, "JUCE_USE_VSTSDK_2_4=0")
        table.insert (package.includepaths, "../../../../vst/vstsdk2.3")
        table.insert (package.includepaths, "../../../../vst/vstsdk2.3/source/common")
        table.insert (package.includepaths, "../../../../vstsdk2.3")
        table.insert (package.includepaths, "../../../../vstsdk2.3/source/common")
        table.insert (package.includepaths, "../../vst/vstsdk2.3")
        table.insert (package.includepaths, "../../vst/vstsdk2.3/source/common")
        table.insert (package.includepaths, "../../vstsdk2.3")
        table.insert (package.includepaths, "../../vstsdk2.3/source/common")
        if (target == "gnu") then
            table.insert (package.includepaths, "/usr/include/vstsdk2.3/source/common")
            table.insert (package.includepaths, "/usr/include/vst/source/common")
        end
    elseif (version == "2.4") then
        -- we use vstsdk 2.4
        print ("...enabled VSTSDK 2.4");
        table.insert (package.defines, "JUCE_USE_VSTSDK_2_4=1")
        table.insert (package.includepaths, "../../../../vst/vstsdk2.4/public.sdk/source/vst2.x")
        table.insert (package.includepaths, "../../../../vst/vstsdk2.4")
        table.insert (package.includepaths, "../../../../vstsdk2.4/public.sdk/source/vst2.x")
        table.insert (package.includepaths, "../../../../vstsdk2.4")
        table.insert (package.includepaths, "../../vst/vstsdk2.4/public.sdk/source/vst2.x")
        table.insert (package.includepaths, "../../vst/vstsdk2.4")
        table.insert (package.includepaths, "../../vstsdk2.4/public.sdk/source/vst2.x")
        table.insert (package.includepaths, "../../vstsdk2.4")
        if (target == "gnu") then
            table.insert (package.includepaths, "/usr/include/vstsdk2.4/public.sdk/source/vst2.x")
            table.insert (package.includepaths, "/usr/include/vst/public.sdk/source/vst2.x")
        end
    else
        -- unknown vstsdk
        print ("CANNOT SELECT VSTSDK WITH VERSION " .. version)
    end
    
    return package
end

--======================================================================================
function configure_default_release_options ()
    return { "no-symbols",
              "optimize-speed",
              "no-frame-pointer",
              "no-pch",
              "no-edit-and-continue" }
end


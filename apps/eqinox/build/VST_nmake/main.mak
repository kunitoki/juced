
!include <C:\VCToolkit\PlatformSDK\Make\winevc.mak>

PROGRAM=eqinox.dll

OBJ=..\..\src\Main.obj \
#    ..\..\src\StandardLibrary.obj \
	..\..\..\..\juce\juce_amalgamated.obj \
    ..\..\src\XEQComponent.obj \
    ..\..\src\XEQPlugin.obj \
    ..\..\src\Filters\jucetice_AnalogFilter.obj \
    ..\..\src\Filters\jucetice_EQ.obj \
    ..\..\src\Filters\jucetice_Limiter.obj \
    ..\..\src\Components\XEQAbout.obj \
    ..\..\src\Components\XEQGraph.obj \
    ..\..\src\Components\XEQMain.obj \
    ..\..\src\Components\XEQTabPanel.obj
    
LINKOBJ=Main.obj \
#    StandardLibrary.obj \
	juce_amalgamated.obj \
    XEQComponent.obj \
    XEQPlugin.obj \
    jucetice_AnalogFilter.obj \
    jucetice_EQ.obj \
    jucetice_Limiter.obj \
    XEQAbout.obj \
    XEQGraph.obj \
    XEQMain.obj \
    XEQTabPanel.obj 

INCLUDES=/I..\..\src \
         /I..\..\..\..\juce \
         /I..\..\..\..\wrapper \
         /I..\..\..\..\vst\vstsdk2.3\source\common

DEFINES=/DJUCETICE_USE_AMALGAMA=1 /DXEQ_VST_PLUGIN=1 /LD /MT
# /DJUCETICE_INCLUDE_MPCLIB_CODE=0 /DJUCETICE_INCLUDE_MADLIB_CODE=0

LINKOPTS=/DLL
# /DEF:exports.def /NODEFAULTLIB:libcmt.lib

all: $(PROGRAM)

.cpp.obj::
	$(VCCOMPILER) $(INCLUDES) $(DEFINES) $<

.c.obj::
	$(VCCOMPILER) $(INCLUDES) $(DEFINES) $<

$(PROGRAM): $(OBJ)
	$(VCLINKER) $(LINKOPTS) /OUT:$@ $(LINKOBJ)

clean:
	del *.dll
	del *.lib
	del *.obj
	del *.pdb
	del *.idb
	del *.exp


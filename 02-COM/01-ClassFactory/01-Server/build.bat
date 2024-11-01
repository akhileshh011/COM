cls

del *.obj
del *.dll
del *.lib
del *.exp

cl.exe /c /EHsc ClassFactoryDllServerWithRegFile.cpp

link.exe ClassFactoryDllServerWithRegFile.obj /DLL /DEF:ClassFactoryDllServerWithRegFile.def user32.lib /SUBSYSTEM:WINDOWS

@echo off
setlocal

rem This will use VS2022 for compiler
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x86

cl /nologo /MT /O2 create_font.c /I C:\Clibs\lpng1637\include /link /LIBPATH:C:\Clibs\lpng1637\lib libpng16.lib zlib.lib
endlocal

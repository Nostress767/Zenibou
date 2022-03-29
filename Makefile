cf=/c /utf-8 /nologo /W4 /MD /O2 /Iinclude /I. /Isrc
of=/Foobj\$(*B).o
lf=/NOLOGO /SUBSYSTEM:console /ENTRY:mainCRTStartup /LIBPATH:obj /LIBPATH:lib

ecf=/DRAYLIB
elf=raylib.lib

deps=obj\Clock.o obj\Input.o
edeps=obj\Clock.o obj\Input.o

Example: $(deps)
	cl $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) $(of) Example.c
	link $(lf) Example.o Zenibou.o Clock.o Input.o
	Example.exe

$(deps):
	if not exist obj mkdir obj
	cl $(cf) $(of) src\$(*B).c

clean:
	if exist obj\Example.o del obj\*.o
	if exist obj\Example.obj del obj\*.obj
	if exist Example.exe del Example.exe
	if exist Example.html del Example.html
	if exist Example.js del Example.js
	if exist Example.wasm del Example.wasm
	if exist Example del Example

ray: $(deps)
	cl $(ecf) $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) /Foobj\Example.o Example.c
	link $(lf) $(elf) Example.o Zenibou.o Clock.o Input.o
	Example.exe

web:
	setlocal
	call C:\emsdk\emsdk_env.bat
	emcc -o Example.html Example.c src/Zenibou.c src/Clock.c src/Input.c -Os -Wall ./lib/webraylib.a -I. -I./src -I./include -L. -L./lib -s USE_GLFW=3 -DPLATFORM_WEB -DRAYLIB
	endlocal
	start python -m http.server
	explorer "http://localhost:8000/Example.html" || ver > nul

libpng:
	if not exist lib mkdir lib
	if not exist include mkdir include
	if not exist external mkdir external
	if exist include\png.h del include\png.h
	if exist include\pngconf.h del include\pngconf.h
	if exist include\pnglibconf.h del include\pnglibconf.h
	if exist lib\libpng16.lib del lib\libpng16.lib
	if exist lib\zlib.lib del lib\zlib.lib
	cd external
	curl -L --output lpng1637.zip --url https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/lpng1637.zip/download
	curl -L --output zlib-1.2.11.zip --url https://sourceforge.net/projects/libpng/files/zlib/1.2.11/zlib1211.zip/download
	tar -xf lpng1637.zip
	tar -xf zlib-1.2.11.zip
	copy lpng1637\png.h ..\include\png.h
	copy lpng1637\pngconf.h ..\include\pngconf.h
	copy libpngreference\vstudio.sln lpng1637\projects\vstudio\vstudio.sln
	copy libpngreference\zlib.props lpng1637\projects\vstudio\zlib.props
	copy libpngreference\libpng.vcxproj lpng1637\projects\vstudio\libpng\libpng.vcxproj
	copy libpngreference\pnglibconf.vcxproj lpng1637\projects\vstudio\pnglibconf\pnglibconf.vcxproj
	copy libpngreference\zlib.vcxproj lpng1637\projects\vstudio\pnglibconf\zlib.vcxproj
	cd lpng1637\projects\vstudio
	msbuild vstudio.sln /p:Configuration="Release Library" /p:Platform="Win32" /p:PlatformToolset=v143
	copy "Release Library\libpng16.lib" ..\..\..\..\lib\libpng16.lib
	copy "Release Library\zlib.lib" ..\..\..\..\lib\zlib.lib
	cd ..\..\..
	copy lpng1637\pnglibconf.h ..\include\pnglibconf.h
	del lpng1637.zip
	del zlib-1.2.11.zip
	RMDIR "lpng1637" /S /Q
	RMDIR "zlib-1.2.11" /S /Q

raylib:
	if not exist include mkdir include
	if not exist lib mkdir lib
	if exist include\raylib.h del include\raylib.h
	if exist include\raymath.h del include\raymath.h
	if exist include\rlgl.h del include\rlgl.h
	if exist lib\raylib.lib del lib\raylib.lib
	cd external
	curl -L --output raylib-master.zip --url https://github.com/Nostress767/raylib/archive/refs/heads/master.zip
	tar -xf raylib-master.zip
	cd raylib-master\src
	copy raylib.h ..\..\..\include\raylib.h
	copy raymath.h ..\..\..\include\raymath.h
	copy rlgl.h ..\..\..\include\rlgl.h
	nmake
	copy raylib.lib ..\..\..\lib\raylib.lib
	cd ..\..
	del raylib-master.zip
	RMDIR "raylib-master" /S /Q

webraylib:
	if not exist include mkdir include
	if not exist lib mkdir lib
	if exist include\raylib.h del include\raylib.h
	if exist include\raymath.h del include\raymath.h
	if exist include\rlgl.h del include\rlgl.h
	if exist lib\webraylib.a del lib\webraylib.a
	cd external
	curl -L --output raylib-master.zip --url https://github.com/Nostress767/raylib/archive/refs/heads/master.zip
	tar -xf raylib-master.zip
	cd raylib-master\src
	copy raylib.h ..\..\..\include\raylib.h
	copy raymath.h ..\..\..\include\raymath.h
	copy rlgl.h ..\..\..\include\rlgl.h
	nmake web
	copy raylib.a ..\..\..\lib\webraylib.a
	cd ..\..
	del raylib-master.zip
	RMDIR "raylib-master" /S /Q

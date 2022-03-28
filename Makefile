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
raylib:
	if not exist include mkdir include
	if not exist lib mkdir lib
	if exist include\raylib.h del include\raylib.h
	if exist include\raymath.h del include\raymath.h
	if exist include\rlgl.h del include\rlgl.h
	if exist lib\raylib.lib del lib\raylib.lib
	cd external
	curl --output raylib-master.zip --url https://codeload.github.com/Nostress767/raylib/zip/refs/heads/master
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
	curl --output raylib-master.zip --url https://codeload.github.com/Nostress767/raylib/zip/refs/heads/master
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

cf=/c /utf-8 /F10000000 /nologo /W4 /MD /O2 /Iinclude /I.
of=/Foobj\$(*B).o
lf=/NOLOGO /SUBSYSTEM:console /ENTRY:mainCRTStartup /LIBPATH:obj

ecf=/DRAYLIB /I.\raylib\include
elf=/LIBPATH:.\raylib\lib traylib.lib

deps=obj\Clock.o obj\Input.o
edeps=obj\Clock.o obj\Input.o

Example: $(deps)
	cl $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) $(of) Example.c
	link $(lf) Example.o Zenibou.o Clock.o Input.o
	Example.exe

$(deps):
	mkdir obj || ver > nul
	cl $(cf) $(of) src\$(*B).c

clean:
	@del obj\*.o > nul 2> nul
	@del Example.exe > nul 2> nul
	@del Example.html > nul 2> nul
	@del Example.js > nul 2> nul
	@del Example.wasm > nul 2> nul

ray: $(deps)
	cl $(ecf) $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) /Foobj\Example.o Example.c
	link $(lf) $(elf) Example.o Zenibou.o Clock.o Input.o
	Example.exe

web:
	setlocal
	call C:\emsdk\emsdk_env.bat
	emcc -o Example.html Example.c src/Zenibou.c src/Clock.c src/Input.c -Os -Wall ./raylib/lib/raylib.a -I. -I./include -I./raylib/include -L. -L./raylib/lib -s USE_GLFW=3 -DPLATFORM_WEB -DRAYLIB
	endlocal
	start python -m http.server
	explorer "http://localhost:8000/Example.html" || ver > nul

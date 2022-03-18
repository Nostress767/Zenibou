cf=/c /utf-8 /F10000000 /nologo /W4 /MD /O2 /Iinclude /I.
of=/Foobj\$(*B).o
lf=/NOLOGO /SUBSYSTEM:console /ENTRY:mainCRTStartup /LIBPATH:obj

ecf=/DRAYLIB /I.\raylib\include
elf=/LIBPATH:.\raylib\lib raylib.lib

deps=obj\Clock.o obj\Input.o
edeps=obj\Clock.o obj\Input.o

Example: $(deps)
	cl $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) $(of) Example.c
	link $(lf) Example.o Zenibou.o Clock.o Input.o

$(deps):
	cl $(cf) $(of) src\$(*B).c

clean:
	@del obj\*.o > nul 2> nul
	@del Example.exe > nul 2> nul

ray: $(deps)
	cl $(ecf) $(cf) /Foobj\Zenibou.o src\Zenibou.c
	cl $(cf) /Foobj\Example.o Example.c
	link $(lf) $(elf) Example.o Zenibou.o Clock.o Input.o


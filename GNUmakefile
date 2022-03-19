cf=-c -finput-charset=UTF-8 -O2 -Iinclude -I.
of=-o $@
lf=-Lobj/

ecf=-DRAYLIB -Iraylib/include
elf=-Lraylib/lib -l:raylib.a -lGL -lm -lpthread -ldl -lrt -lX11

deps=obj/Clock.o obj/Input.o
edeps=obj/Clock.o obj/Input.o

Example: $(deps)
	gcc $(ecf) $(cf) -o obj/Zenibou.o src/Zenibou.c
	gcc $(cf) -o obj/Example.o Example.c
	gcc -Wl,-z,stack-size=10000000 -o $@ obj/$@.o obj/Zenibou.o $(deps) $(lf) $(elf)
#	./Example

$(deps):
	mkdir -p obj
	gcc $(cf) $(of) src/$(basename $(@F)).c

clean:
	$(RM) obj/*.o
	$(RM) Example.exe
	$(RM) Example.html
	$(RM) Example.js
	$(RM) Example.wasm
	$(RM) Example

#web:
#	setlocal
#	call C:\emsdk\emsdk_env.bat
#	emcc -o Example.html Example.c src/Zenibou.c src/Clock.c src/Input.c -Os -Wall ./raylib/lib/raylib.a -I. -I./raylib/include -L. -L./raylib/lib -s USE_GLFW=3 -DPLATFORM_WEB -DRAYLIB
#	endlocal
#	start python -m http.server
#	explorer "http://localhost:8000/Example.html" || ver > nul

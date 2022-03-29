# TODO: update this, based on Makefile
# TODO: fix web targets
cf=-c -finput-charset=UTF-8 -O2 -Iinclude -I. -Isrc
of=-o $@
lf=-Lobj/ -lgdi32 -mconsole
linuxlf=-Lobj/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

ecf=-DRAYLIB -Iraylib/include
elf=-Llib -lraylib -lgdi32 -lWinmm

deps=obj/Clock.o obj/Input.o
edeps=obj/Clock.o obj/Input.o

Example: $(deps)
	gcc $(cf) -o obj/Zenibou.o src/Zenibou.c
	gcc $(cf) -o obj/Example.o Example.c
	gcc -o $@ obj/$@.o obj/Zenibou.o $(deps) $(lf) 

ray: $(deps)
	gcc $(ecf) $(cf) -o obj/Zenibou.o src/Zenibou.c
	gcc $(cf) -o obj/Example.o Example.c
	gcc -o Example obj/Example.o obj/Zenibou.o $(deps) $(lf) $(elf)

linux: $(deps)
	gcc $(ecf) $(cf) -o obj/Zenibou.o src/Zenibou.c
	gcc $(ecf) $(cf) -o obj/Example.o Example.c
	gcc -o Example obj/Example.o obj/Zenibou.o $(deps) $(linuxlf)

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

raylib:
	mkdir -p include
	mkdir -p lib
	@[ -f ./include/raylib.h ] && rm ./include/raylib.h || true
	@[ -f ./include/raymath.h ] && rm ./include/raymath.h || true
	@[ -f ./include/rlgl.h ] && rm ./include/rlgl.h || true
	@[ -f ./lib/raylib.lib ] && rm ./lib/raylib.lib || true
	@[ -f ./external/raylib-master.zip ] || curl -L --output external/raylib-master.zip --url https://github.com/Nostress767/raylib/archive/refs/heads/master.zip
	@[ -f ./external/raylib-master/LICENSE ] || unzip external/raylib-master.zip -d external/
	cp external/raylib-master/src/raylib.h include/raylib.h
	cp external/raylib-master/src/raymath.h include/raymath.h
	cp external/raylib-master/src/rlgl.h include/rlgl.h
	cd external/raylib-master/src && make
	cp external/raylib-master/src/libraylib.a lib/raylib.lib
	@[ -f ./external/raylib-master.zip ] && rm external/raylib-master.zip
	@[ -f ./external/raylib-master/LICENSE ] && rm -rf external/raylib-master

linuxraylib:
	mkdir -p include
	mkdir -p lib
	@[ -f ./include/raylib.h ] && rm ./include/raylib.h || true
	@[ -f ./include/raymath.h ] && rm ./include/raymath.h || true
	@[ -f ./include/rlgl.h ] && rm ./include/rlgl.h || true
	@[ -f ./lib/raylib.lib ] && rm ./lib/raylib.lib || true
	@[ -f ./external/raylib-master.zip ] || curl -L --output external/raylib-master.zip --url https://github.com/Nostress767/raylib/archive/refs/heads/master.zip
	@[ -f ./external/raylib-master/LICENSE ] || cd external && bsdtar xf raylib-master.zip
	cp external/raylib-master/src/raylib.h include/raylib.h
	cp external/raylib-master/src/raymath.h include/raymath.h
	cp external/raylib-master/src/rlgl.h include/rlgl.h
	cd external/raylib-master/src && make
	cp external/raylib-master/src/libraylib.a lib/raylib.a
	@[ -f ./external/raylib-master.zip ] && rm external/raylib-master.zip
	@[ -f ./external/raylib-master/LICENSE ] && rm -rf external/raylib-master

#web:
#	setlocal
#	call C:\emsdk\emsdk_env.bat
#	emcc -o Example.html Example.c src/Zenibou.c src/Clock.c src/Input.c -Os -Wall ./raylib/lib/raylib.a -I. -I./raylib/include -L. -L./raylib/lib -s USE_GLFW=3 -DPLATFORM_WEB -DRAYLIB
#	endlocal
#	start python -m http.server
#	explorer "http://localhost:8000/Example.html" || ver > nul

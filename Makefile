# TODO: fix web targets
cf=-finput-charset=UTF-8 -O2
lf=-Lobj/ -lgdi32 -mconsole
linuxlf=-Lobj/ -Llib -l:raylib.a -lGL -lm -lpthread -ldl -lrt -lX11
ecf=-DRAYLIB -Iinclude
elf=-Llib -lraylib -lgdi32 -lWinmm

resources=Sound1.mp3 Sound2.mp3
linuxresources=

Example: $(resources)
	gcc $(cf) -o $@ $@.c $(addsuffix .o, $(basename $(resources))) $(lf)

ray: $(resources)
	gcc $(cf) $(ecf) -o Example Example.c $(lf) $(resources) $(elf)

linux: $(linuxresources)
	gcc $(cf) -o Example Example.c $(ecf) $(linuxlf) $(resources)

.PHONY: $(resources)
$(resources):
	objcopy -I binary -O pe-i386 -B i386 $@ $(basename $@).o

.PHONY: $(linuxresources)
$(linuxresources):
	objcopy -I binary -O elf32-i386 -B i386 $@ $(basename $@).o

clean:
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

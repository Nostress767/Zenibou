cf=-finput-charset=UTF-8

ifeq ($(OS),Windows_NT)
	lf:=-lgdi32 -mconsole -lxinput
else
	lf:=-lm -lX11 -lXi
endif

resources=Sound1.mp3 Sound2.mp3

Example: $(resources)
	gcc $(cf) -o $@ $@.c $(addsuffix .o, $(basename $(resources))) $(lf)

.PHONY: $(resources)
$(resources):
ifeq ($(OS),Windows_NT)
	objcopy -I binary -O pe-i386 -B i386 $@ $(basename $@).o
else
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $@ $(basename $@).o
endif

clean:
	$(RM) Example.exe
	$(RM) Example


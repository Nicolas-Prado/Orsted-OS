##Study: https://embarcados.com.br/introducao-ao-makefile/
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = build/loader.o build/kernel.o

build/%.o: src/%.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

build/%.o: src/%.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: build/linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin
##Study: https://embarcados.com.br/introducao-ao-makefile/
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = $(patsubst src/%.cpp,build/%.o,$(wildcard src/*.cpp)) $(patsubst src/%.s,build/%.o,$(wildcard src/*.s))

build/%.o: src/%.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

build/%.o: src/%.s
	as $(ASPARAMS) -o $@ $<

bin/mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mykernel.iso: bin/mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo ' boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=bin/$@ iso
	rm -rf iso

run: bin/mykernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "My Operating System" &

.PHONY: clean
clean:
	rm -f $(objects) bin/mykernel.bin bin/mykernel.iso
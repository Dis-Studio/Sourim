kernel_source_files := $(shell find src -name *.cpp)
kernel_object_files := $(patsubst src/%.cpp, build/%.o, $(kernel_source_files))

bootloader_asm_source_files := $(shell find src/bootloader -name *.asm)
bootloader_asm_object_files := $(patsubst src/bootloader/%.asm, build/bootloader/%.o, $(bootloader_asm_source_files))

all: build-x86_64

$(kernel_object_files): build/%.o : src/%.cpp
	mkdir -p $(dir $@)
	#x86_64-elf-
	g++ -c -ffreestanding $(patsubst build/%.o, src/%.cpp, $@) -I src -o $@

$(bootloader_asm_object_files): build/bootloader/%.o : src/bootloader/%.asm
	mkdir -p $(dir $@)# && \
	nasm -f elf64 $(patsubst build/bootloader/%.o, src/bootloader/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(bootloader_asm_object_files)
	mkdir -p dist/bootloader
	# && \
	#x86_64-elf-
	ld -n -o dist/bootloader/kernel.bin -T targets/bootloader/linker.ld $(kernel_object_files) $(bootloader_asm_object_files)
	cp dist/bootloader/kernel.bin targets/bootloader/iso/boot/kernel.bin
	grub-mkrescue /usr/lib/grub/i386-pc -o build.iso targets/bootloader/iso
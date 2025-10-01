all:
	$(MAKE) build
	$(MAKE) make_iso
	$(MAKE) run

build:
	# Assembler
	nasm -f elf32 src/IDT_handlers.S -o output/IDT_handlers.o
	nasm -f elf32 src/gdt.S -o output/gdt.o

	# C
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -Wall -c src/kernel.c -o output/kernel.o

	# Linker
	i386-elf-ld -m elf_i386 -T src/linker.ld --oformat elf32-i386 -o output/kernel.elf output/kernel.o output/IDT_handlers.o output/gdt.o

make_iso:
	# Make ISO
	cp output/kernel.elf iso/boot/
	grub-mkrescue -o output/os.iso ./iso/

run:
	qemu-system-i386 -cdrom output/os.iso

all:
	$(MAKE) bootloader
	$(MAKE) kernel
	cat output/boot.bin output/kernel.bin > output/os.img
	$(MAKE) run

bootloader:
	nasm -f bin source/boot.asm -o output/boot.bin

kernel:
	nasm -f elf32 source/IDT_handlers.asm -o output/IDT_handlers.o
	i386-elf-gcc -ffreestanding -m32 -fno-pie -nostdlib -Wall -c source/kernel.c -o output/kernel.o
	i386-elf-ld -T source/linker.ld -o output/kernel.bin output/kernel.o output/IDT_handlers.o --oformat binary

run:
	qemu-system-i386 -fda output/boot.bin -fdb output/kernel.bin

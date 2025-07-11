all:
	i386-elf-gcc -ffreestanding -m32 -fno-pie -nostdlib -Wall -c source/kernel.c -o output/kernel.o
	i386-elf-ld -T source/linker.ld -m elf_i386 -o output/kernel.elf output/kernel.o
	cp output/kernel.elf iso/os/boot/kernel.elf
	grub-mkrescue -o "iso/kernel.iso" "iso/os/"
	$(MAKE) run

run:
	qemu-system-x86_64 -cdrom "iso/kernel.iso"

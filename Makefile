all:
	$(MAKE) build
	$(MAKE) build_programs
	$(MAKE) make_iso
	$(MAKE) make_disk
	$(MAKE) run

build:
	mkdir -p ./output

	# Assembler
	nasm -f elf32 src/lib/asm.S -o output/asm.o
	nasm -f elf32 src/IDT_handlers.S -o output/IDT_handlers.o
	nasm -f elf32 src/gdt.S -o output/gdt.o
	nasm -f elf32 src/api/api.S -o output/api.o

	# C
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -Wall -c src/kernel.c -o output/kernel.o

	# Linker
	i386-elf-ld -m elf_i386 -T src/linker.ld --oformat elf32-i386 -o output/kernel.elf output/kernel.o output/IDT_handlers.o output/gdt.o output/api.o output/asm.o

build_programs:
	mkdir -p ./output/programs/

	# |
	# | Terminal
	# |

	# NASM
	nasm -f elf32 src/lib/asm.S -o output/programs/asm.o
	# C
	i386-elf-gcc -w -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -c src/programs/terminal.c -o output/programs/terminal.o
	# Linker
	i386-elf-ld -m elf_i386 -T src/programs/default_linker.ld -o output/programs/terminal.elf output/programs/asm.o output/programs/terminal.o
	i386-elf-objcopy -O binary output/programs/terminal.elf output/programs/terminal.bin

	# |
	# | Test
	# |

	i386-elf-gcc -w -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -c src/programs/uptime.c -o output/programs/uptime.o
	i386-elf-ld -m elf_i386 -T src/programs/program_linker.ld -o output/programs/uptime.elf output/programs/asm.o output/programs/uptime.o
	i386-elf-objcopy -O binary output/programs/uptime.elf output/programs/uptime.bin


make_iso:
	# Make ISO
	cp output/kernel.elf iso/boot/
	grub-mkrescue -o output/os.iso ./iso/

make_disk:
	# Make hard disk
	dd if=/dev/zero of=output/disk.img bs=512 count=20480
	# Write programs on the disk
	dd if=output/programs/terminal.bin of=output/disk.img bs=512 seek=0 conv=notrunc
	dd if=output/programs/uptime.bin of=output/disk.img bs=512 seek=20 conv=notrunc

run:
	qemu-system-i386 -no-reboot -no-shutdown -cdrom output/os.iso -hda output/disk.img -monitor stdio

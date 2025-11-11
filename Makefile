all:
	$(MAKE) build
	$(MAKE) build_programs
	$(MAKE) make_iso
	$(MAKE) make_disk
	$(MAKE) run

build:
	mkdir -p ./output/
	mkdir -p ./output/asm/
	mkdir -p ./output/api/
	mkdir -p ./output/drivers/
	mkdir -p ./output/libs/
	mkdir -p ./output/programs/

	# Assembler
	nasm -f elf32 src/libs/asm.S -o output/asm/asm.o
	nasm -f elf32 src/IDT_handlers.S -o output/asm/IDT_handlers.o
	nasm -f elf32 src/gdt.S -o output/asm/gdt.o
	nasm -f elf32 src/api/api.S -o output/asm/api.o

	# C
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/kernel.c -o output/kernel.o
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/IDT_PIC.c -o output/IDT_PIC.o

	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/api/api.c -o output/api/api.o
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/api/general_functions.c -o output/api/general_functions.o
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/api/kernel_functions.c -o output/api/kernel_functions.o
	i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c src/api/userspace_if.c -o output/api/userspace_if.c

	# Linker
	i386-elf-ld -m elf_i386 -T src/linker.ld --oformat elf32-i386 -o \
	output/kernel.elf \
	output/asm/asm.o \
	output/asm/IDT_handlers.o \
	output/asm/gdt.o \
	output/asm/api.o \
	output/kernel.o \
	output/IDT_PIC.o \
	output/api/api.o \
	output/api/general_functions.o \
	output/api/kernel_functions.o \
	output/api/userspace_if.c \




build_programs:
	mkdir -p ./output/programs/
	mkdir -p ./output/programs/term2/
	mkdir -p ./output/programs/uptime/
	mkdir -p ./output/programs/colorama/

	# NASM
	nasm -f elf32 src/libs/asm.S -o output/programs/asm.o

	# |
	# | Term2
	# |

	# C
	i386-elf-gcc -w -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -c src/programs/term2/term2.c -o output/programs/term2/term2.o
	# Linker
	i386-elf-ld -m elf_i386 -T src/programs/program_linker.ld -o output/programs/term2/term2.elf output/programs/asm.o output/programs/term2/term2.o output/libs/io.o output/libs/string.o output/libs/time.o output/libs/programs.o output/libs/ata.o
	i386-elf-objcopy -O binary output/programs/term2/term2.elf output/programs/term2/term2.bin

	# |
	# | Uptime
	# |

	i386-elf-gcc -w -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -c src/programs/uptime/uptime.c -o output/programs/uptime/uptime.o
	i386-elf-ld -m elf_i386 -T src/programs/program_linker.ld -o output/programs/uptime/uptime.elf output/programs/asm.o output/programs/uptime/uptime.o output/libs/io.o output/libs/string.o
	i386-elf-objcopy -O binary output/programs/uptime/uptime.elf output/programs/uptime/uptime.bin

	# |
	# | Colorama
	# |

	i386-elf-gcc -w -m32 -ffreestanding -fno-pie -fno-pic -nostdlib -c src/programs/colorama/colorama.c -o output/programs/colorama/colorama.o
	i386-elf-ld -m elf_i386 -T src/programs/program_linker.ld -o output/programs/colorama/colorama.elf output/programs/asm.o output/programs/colorama/colorama.o output/libs/io.o output/libs/string.o output/libs/time.o
	i386-elf-objcopy -O binary output/programs/colorama/colorama.elf output/programs/colorama/colorama.bin


make_iso:
	# Make ISO
	cp output/kernel.elf iso/boot/
	grub-mkrescue -o output/os.iso ./iso/

make_disk:
	# Make hard disk
	dd if=/dev/zero of=output/disk.img bs=512 count=20480
	# Write programs on the disk
	dd if=output/programs/term2/term2.bin of=output/disk.img bs=512 seek=0 conv=notrunc
	dd if=output/programs/uptime/uptime.bin of=output/disk.img bs=512 seek=20 conv=notrunc
	dd if=output/programs/colorama/colorama.bin of=output/disk.img bs=512 seek=40 conv=notrunc

run:
	qemu-system-i386 -no-reboot -monitor stdio \
	-drive file=output/disk.img,format=raw,if=ide,index=0,media=disk \
	-drive file=output/os.iso,format=raw,if=ide,index=1,media=cdrom

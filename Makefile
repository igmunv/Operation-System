

DRIVER_DIRS := $(wildcard src/drivers/*)
LIB_DIRS := $(wildcard src/libs/*.c)
OBJS := $(shell find output/ -name '*.o')


all:
	$(MAKE) build


drivers:
	@for dir in $(DRIVER_DIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "==> Building driver in $$dir"; \
			$(MAKE) -C $$dir; \
		else \
			echo "==> Skipping $$dir (no Makefile)"; \
		fi; \
	done


libs:
	mkdir -p output/libs
	for src in $$(find src/libs -type f -name '*.c'); do \
		obj=$$(echo $$src | sed 's|src/libs|output/libs|' | sed 's|\.c$$|.o|'); \
		echo "Compiling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		i386-elf-gcc -w -ffreestanding -m32 -fno-pie -nostdlib -c $$src -o $$obj; \
	done

	for src in $$(find src/libs -type f -name '*.S'); do \
		obj=$$(echo $$src | sed 's|src/libs|output/asm|' | sed 's|\.S$$|.o|'); \
		echo "Assembling $$src -> $$obj"; \
		mkdir -p $$(dirname $$obj); \
		nasm -f elf32 $$src -o $$obj; \
	done


kernel:



link:
	i386-elf-ld -m elf_i386 -T src/linker.ld --oformat elf32-i386 -o output/kernel.elf $(OBJS)


build:
	$(MAKE) drivers
	$(MAKE) libs
	$(MAKE) link


build1:
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

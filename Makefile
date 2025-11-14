

LIB_DIRS := $(wildcard src/libs/*.c)
OBJS := $(shell mkdir -p output; find output -name '*.o')

CC = i386-elf-gcc
CFLAGS = -w -ffreestanding -m32 -fno-pie -nostdlib

NS = nasm
NSFLAGS = -f elf32

LIBS_C := $(shell find src/libs -type f -name '*.c')
LIBS_S := $(shell find src/libs -type f -name '*.S')
KERNEL_C := $(shell find src/kernel -name *.c)
KERNEL_S := $(shell find src/kernel -name *.S)
API_C    := $(shell find src/api -name *.c)
API_S    := $(shell find src/api -name *.S)


define build-rule
    for src in $(1); do \
        obj=$$(echo $$src | sed 's|$(2)|$(3)|' | sed 's|$(4)$$|$(5)|'); \
        echo "Building $$src -> $$obj"; \
        mkdir -p $$(dirname $$obj); \
        if echo $$src | grep -q "\.c$$"; then \
            $(6) $(7) -c $$src -o $$obj; \
        else \
            $(6) $(7) $$src -o $$obj; \
        fi; \
    done
endef


all:
	$(MAKE) build
	$(MAKE) make_iso
	$(MAKE) make_disk
	$(MAKE) run



drivers:
	$(MAKE) -C ./src/drivers/


libs:
	mkdir -p output/libs
	$(call build-rule,$(LIBS_C),src/libs,output/libs,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(LIBS_S),src/libs,output/libs,.S,.o,$(NS),$(NSFLAGS))


kernel:
	mkdir -p output/kernel/
	$(call build-rule,$(KERNEL_C),src/kernel,output/kernel,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(KERNEL_S),src/kernel,output/kernel,.S,.o,$(NS),$(NSFLAGS))

	$(MAKE) k_api


k_api:
	mkdir -p output/api/
	$(call build-rule,$(API_C),src/api,output/api,.c,.o,$(CC),$(CFLAGS))
	$(call build-rule,$(API_S),src/api,output/api,.S,.o,$(NS),$(NSFLAGS))


link:
	i386-elf-ld -m elf_i386 -T src/linker.ld --oformat elf32-i386 -o output/kernel.elf $(OBJS)


clean:
	rm -rf output/


build:
	echo "\n --- --- clean --- --- \n"
	$(MAKE) clean
	echo "\n --- --- drivers --- --- \n"
	$(MAKE) drivers
	echo "\n --- --- libs --- --- \n"
	$(MAKE) libs
	echo "\n --- --- kernel --- --- \n"
	$(MAKE) kernel
	echo "\n --- --- link --- --- \n"
	$(MAKE) link


make_iso:
	# Make ISO
	cp output/kernel.elf iso/boot/
	grub-mkrescue -o output/os.iso ./iso/

make_disk:
	# Make hard disk
	dd if=/dev/zero of=output/disk.img bs=512 count=20480

run:
	qemu-system-i386 -no-reboot -monitor stdio \
	-drive file=output/disk.img,format=raw,if=ide,index=0,media=disk \
	-drive file=output/os.iso,format=raw,if=ide,index=1,media=cdrom \
	-d int,cpu_reset -D qemu.log

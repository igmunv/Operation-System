# Собираем все драйверы верхнего уровня
DRIVERS_SRC := $(wildcard *.c) $(wildcard *.S)
DRIVERS_OBJ := $(DRIVERS_SRC:.c=.o)
DRIVERS_OBJ := $(DRIVERS_OBJ:.S=.o)

# Находим директории драйверов
DRIVER_DIRS := $(filter-out .,$(wildcard */))

# Путь куда
DRIVER_OUTPUT = ../../output/drivers/

CC = i386-elf-gcc
CFLAGS = -w -ffreestanding -m32 -fno-pie -nostdlib

NS = nasm
NSFLAGS = -f elf32

all: $(DRIVERS_OBJ) drivers

# Сборка файлов в текущей папке
%.o: %.c
	mkdir -p $(DRIVER_OUTPUT)
	$(CC) $(CFLAGS) -c $< -o $(DRIVER_OUTPUT)$@

%.o: %.S
	mkdir -p $(DRIVER_OUTPUT)
	$(NS) $(NSFLAGS) $< -o $(DRIVER_OUTPUT)$@

# Сборка драйверов в подпапках
drivers:
	@for dir in $(DRIVER_DIRS); do \
		if [ -f $$dir/Makefile ] || [ -f $$dir/makefile ]; then \
			echo "==> Building driver in $$dir"; \
			$(MAKE) -C $$dir; \
		else \
			echo "==> Skipping $$dir (no Makefile)"; \
		fi; \
	done

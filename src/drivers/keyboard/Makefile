DRIVER_NAME = keyboard
SRC = keyboard.c
OBJ_DIR = ../../../output/drivers/$(DRIVER_NAME)
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

CC = i386-elf-gcc
CFLAGS = -w -ffreestanding -m32 -fno-pie -nostdlib


all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)

	$(CC) $(CFLAGS) -c $< -o $@

	nasm -f elf32 keyboard.S -o $(OBJ_DIR)/keyboardS.o

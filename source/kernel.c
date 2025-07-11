__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0,
    -(0x1BADB002)
};

#define VIDEO_BUFFER_PTR (0xb8000)
#define STACK_SIZE 4096

#include "types.c"
#include "asm.c"
#include "keyboard.c"
#include "string.c"
#include "terminal.c"

// выравнивает по 16 байтам. производительность \ требования инструкций \ в x86 обязан быть выровнен
__attribute__((aligned(16))) unsigned char KERNEL_STACK[STACK_SIZE];

void malloc(unsigned int size){ // size = bytes
	
}

void kmain(){
	terminal_init();
}	

void _start() {
	// инициализация стека
	// записываем в esp верхний адрес стека
	// r - говорит компилятору чтобы записал в любой регистр значение а потом в esp
	// KERNEL_STACK+STACK_SIZE - получение адреса верхушки стека
	asm volatile("mov %0, %%esp" :: "r"(KERNEL_STACK+STACK_SIZE));
	kmain();
	while (1) asm volatile("hlt");
}
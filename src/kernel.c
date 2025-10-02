

__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
	0x1BADB002,
	0,
	-(0x1BADB002)
};

// kernel
#include "asm.c"
#include "IDT_PIC.c"
#include "PIT.c"
// drivers
#include "drivers/keyboard.c"
#include "drivers/display.c"
// api
#include "api/api.c"
// other libs
#include "memory.c"
#include "string.c"
// programs
#include "programs/terminal.c"

extern void gdt_init();

void kmain(void){

	gdt_init();

    IDT_disable();
    PIC_remap();
    IDT_handlers_init();
    IDT_load();
    PIT_init(1000);
	api_init();
	IDT_enable();

	terminal_init();

	while(1)
	{
		asm("hlt");
	}
}

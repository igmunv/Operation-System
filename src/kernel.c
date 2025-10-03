__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
	0x1BADB002,
	0,
	-(0x1BADB002)
};

// kernel
#include "lib/asm.c"
#include "IDT_PIC.c"
// drivers
#include "drivers/drivers.c"
#include "drivers/keyboard.c"
#include "drivers/display.c"
#include "drivers/PIT.c"
// api
#include "api/api.c"
// libs
#include "lib/memory.c"
#include "lib/string.c"
#include "lib/time.c"
#include "lib/io.c"
// programs
#include "programs/terminal.c"

extern void gdt_init();

void kmain(void){

	// GDT table init
	gdt_init();

    interrupt_disable();

	// Add interrupt, handlers. Init
	drivers_init();
	api_init();

	// IDT setup
	PIC_remap();
	IDT_load();

	interrupt_enable();


	terminal_init();

	while(1)
	{
		asm("hlt");
	}
}

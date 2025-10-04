// GRUB header
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

// ASM-functions
extern void gdt_init();


// Main
void kmain(void){

	// GDT table init
	gdt_init();

	// Ints disable
    interrupt_disable();

	// Add interrupt, handlers. Init
	drivers_init();
	api_init();

	// IDT setup
	PIC_remap();
	IDT_load();

	// Ints enable
	interrupt_enable();


	// - - Test - -
	terminal_init();


	// Endless loop
	while(1)
	{
		asm("hlt");
	}
}

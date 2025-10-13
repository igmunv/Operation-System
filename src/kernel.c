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
#include "drivers/ata.c"
#include "drivers/progloader.c"
// api
#include "api/api.c"
// libs
#include "lib/memory.c"
#include "lib/string.c"
#include "lib/time.c"
#include "lib/io.c"
#include "lib/ata.c"


// ASM-functions
extern void gdt_init();


// Main
void kmain(void){

	// GDT table init
	gdt_init();

	// Ints disable
    interrupt_disable();

	// Add interrupt, handlers. Init before turning on ints
	drivers_init();
	api_init();

	// IDT setup
	PIC_remap();
	IDT_load();

	// Ints enable
	interrupt_enable();

	// Init after turning on ints
	drivers_init_late();

	// Start default program
	progloader_run_default();

	// Endless loop
	print("Kernel:");
	print("Endless loop...");
	while(1)
	{
		asm("hlt");
	}
}

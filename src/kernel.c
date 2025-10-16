// GRUB header
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
	0x1BADB002,
	0,
	-(0x1BADB002)
};


// libs
#include "libs/string.h"
#include "libs/time.h"
#include "libs/io.h"
#include "libs/ata.h"
#include "libs/shared_memory.h"
#include "libs/asm.h"

// Kernel
#include "gdt.h"
#include "IDT_PIC.h"
#include "memory.h"

// drivers
#include "drivers/drivers.h"
#include "drivers/keyboard.h"
#include "drivers/display.h"
#include "drivers/PIT.h"
#include "drivers/ata.h"
#include "drivers/progloader.h"

// api
#include "api/api.h"


// Loop
__attribute__((section(".kernel_loop"))) void kernel_loop(void) {
	while(1)
	{
		if (EXECUTE_PROGRAM == 0){
			progloader_run_program(EXECUTE_PROGRAM);
		}

		else{
			progloader_run_program(EXECUTE_PROGRAM);
			EXECUTE_PROGRAM = 0;
		}
	}
}


// Main
void kmain(void){

	// GDT table init
	gdt_init();

	// Shared memory init
	shared_memory_init();

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

	// Endless loop
	kernel_loop();
}

// GRUB header
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
	0x1BADB002,
	0,
	-(0x1BADB002)
};

#include "kernel.h"
#include "PIT.h"

// Kernel
#include "gdt.h"
#include "IDT_PIC.h"

// api
#include "../api/api.h"
#include "../api/kernel_functions.h"


unsigned int EXECUTE_PROGRAM = 0;


// Loop
__attribute__((section(".kernel_loop"))) void kernel_loop(void) {
	while(1)
	{
		if (EXECUTE_PROGRAM == 0){

		}

		else{

			EXECUTE_PROGRAM = 0;
		}
	}
}


// Main
void kmain(void){

	// GDT table init
	gdt_init();
	// Remap interrupts
	PIC_remap();
	// Init API
	api_init();

	devices_find();

	driver_manager();

	// Endless loop
	kernel_loop();
}

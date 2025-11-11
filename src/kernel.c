// GRUB header
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
	0x1BADB002,
	0,
	-(0x1BADB002)
};

#include "kernel.h"
#include "PIT.h"

// libs
#include "libs/string.h"
#include "libs/time.h"
#include "libs/io.h"
#include "libs/asm.h"
#include "libs/memory.h"

// Kernel
#include "gdt.h"
#include "IDT_PIC.h"

// drivers
#include "drivers/drivers.h"
#include "drivers/keyboard.h"
#include "drivers/display.h"
#include "drivers/ata.h"
#include "drivers/progloader.h"
#include "drivers/devices.h"

// api
#include "api/api.h"
#include "api/kernel_functions.h"


unsigned int EXECUTE_PROGRAM = 0;


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


// For kernel logs
// Without new line!
void kernel_log(unsigned char* text){

}


// Panic Mode
// where_function - в какой функции произошла ошибка
// text - текст ошибки
void kernel_panic(unsigned char* where_function, unsigned char* text){

	// Выключаем прерывания
	interrupt_disable();

	/*set_display_cursor_pos_x(0);
	_set_display_cursor_pos_y(0);
	kernel_log(" - - Kernel Panic - - ");
	display_new_line();

	// Выводим текст напрямую через драйвер, так как прерывания в данный момент не безопасны
	kernel_log(where_function);
	kernel_log("(): ");
	kernel_log(text);
	display_new_line();*/

	while(1) cpu_pause();

}


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

	// devices_find();
	// driver_manager();

	// Init after turning on ints
	drivers_init_late();

	// Endless loop
	kernel_loop();

	kernel_panic("kmain", "End");
}

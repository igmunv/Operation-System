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

#include "../libs/device.h"


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



// Слушаем клавиатуру (буффер клавиатуры)
void term_keyboard_listen(){

	unsigned char keyboard_buffer[16];
	unsigned int keyboard_buffer_tail;

	unsigned int dev1;
	struct dev_info* devs = (struct dev_info*)_get_device_info();
    for (unsigned int dev = 0; dev < _get_device_count(); dev++){
        if (devs[dev].classcode == VIRT_KEYBOARD_CONTROLLER && devs[dev].subclass == VIRT_KEYBOARD_LDEV){
			dev1 = dev;

			break;
        }
    }

	keyboard_buffer_tail = _get_keyboard_buffer_ptr(dev1);
    unsigned char* KEYBOARD_BUFFER = _get_keyboard_buffer(dev1);


	while(1){
		test();

		// Нажата клавиша
		if (keyboard_buffer_tail != _get_keyboard_buffer_ptr(dev1)){
			test();
		}


	}
}

void test(){
	struct dev_info* devs = (struct dev_info*)_get_device_info();
    for (unsigned int dev = 0; dev < _get_device_count(); dev++){
        if (devs[dev].classcode == VIRT_DISPLAY_CONTROLLER && devs[dev].subclass == VIRT_DISPLAY_VGATEXT){
            _clear_display(dev);
            _cursor_update(dev);
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

	term_keyboard_listen();
	// Endless loop
	kernel_loop();
}

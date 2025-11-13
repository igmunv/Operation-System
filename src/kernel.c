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
#include "libs/shared_memory.h"
#include "libs/asm.h"
#include "libs/memory.h"

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
#include "drivers/file_system.h"

// api
#include "api/api.h"


struct multiboot_struct{
	unsigned int flags;
	unsigned int mem_lower;
	unsigned int mem_upper;
	unsigned int boot_device;
	unsigned int cmdline;
	unsigned int mods_count;
	unsigned int mods_addr;
	unsigned char syms[12];
	unsigned int mmap_length;
	unsigned int mmap_addr;
	// Дальше не надо
} __attribute__((packed));

struct multiboot_mmap_struct {
	unsigned int size;      // размер структуры, обычно 20
	unsigned long addr;      // физический адрес начала области
	unsigned long len;       // длина области в байтах
	unsigned int type;      // тип области: 1 доступная (ram), 2 резерв, 3 acpi reclaimable, 4 acpi NVS, 5 bad memory (поврежденная)
} __attribute__((packed));


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
	for (short i = 0; text[i] != '\0'; i++)
		display_print_symbol(text[i], DISPLAY_CURSOR_POS_X, DISPLAY_CURSOR_POS_Y, 7, 0);
}


// Panic Mode
// where_function - в какой функции произошла ошибка
// text - текст ошибки
void kernel_panic(unsigned char* where_function, unsigned char* text){

	// Выключаем прерывания
	interrupt_disable();

	DISPLAY_CURSOR_POS_X = 0;
	DISPLAY_CURSOR_POS_Y = 0;
	kernel_log(" - - Kernel Panic - - ");
	display_new_line();

	// Выводим текст напрямую через драйвер, так как прерывания в данный момент не безопасны
	kernel_log(where_function);
	kernel_log("(): ");
	kernel_log(text);
	display_new_line();

	while(1) cpu_pause();

}

// Check System: memory, disks
void check_system(){

	// Devices
	char disk_flag = 0;
	for(int i = 0; i < DEVICE_COUNT; i++){
		struct dev_info devinfo = DEVICES_INFO[i];

		// Диск, размер больше 16 МБ
		if (devinfo.dev_type == 1 && devinfo.option1 >= 32768){
			disk_flag = 1;
		}
	}

	if (!disk_flag) kernel_panic("check_system", "The drive was not found or does not meet the requirements!");
}


// Main
void kmain(void){

	// GDT table init
	gdt_init();

	// Get Multiboot Info
	struct multiboot_struct* multiboot_info_addr = get_ebx();
	struct multiboot_struct multiboot_info = *multiboot_info_addr;

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

	// Check system: required: devices, disks, memory
	check_system();

	// Endless loop
	kernel_loop();

	kernel_panic("kmain", "End");
}

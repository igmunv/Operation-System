asm("jmp kmain");

// kernel
#include "asm.c"
#include "IDT_PIC.c"
#include "PIT.c"
// drivers
#include "drivers/keyboard.c"
#include "drivers/display.c"
// other libs
#include "memory.c"
#include "string.c"
// programs
#include "programs/terminal.c"

void kmain(void){

    IDT_disable();
    PIC_remap();
    IDT_handlers_init();
    IDT_load();
    PIT_init(1000);
	IDT_enable();

	terminal_init();

	while(1)
	{
		asm("hlt");
	}
}

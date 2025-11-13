// Функции API только для kernel space

#include "kernel_functions.h"
#include "../IDT_PIC.h"

void _int_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler){
    interrupt_disable();
    IDT_reg_handler(number, segm_sel, flags, handler);
    IDT_load();
    interrupt_enable();
}

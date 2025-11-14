// Функции API только для kernel space

#include "kernel_functions.h"
#include "../kernel/IDT_PIC.h"

void _int_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler){
    interrupt_disable();
    IDT_reg_handler(number, segm_sel, flags, handler);
    IDT_load();
    interrupt_enable();
}

void _pic_update_mask(unsigned char mst_sl, unsigned char bit, unsigned char value){
    PIC_update_mask(mst_sl, bit, value);
}

void _intr_enable(){
    interrupt_enable();
}

void _intr_disable(){
    interrupt_disable();
}

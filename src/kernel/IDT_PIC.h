#ifndef INCL_IDT_PIC
#define INCL_IDT_PIC

// Тип: указатель
typedef void (*intr_handler)();

void interrupt_enable();
void interrupt_disable();
void PIC_remap();
void IDT_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler);
void IDT_load();

#endif

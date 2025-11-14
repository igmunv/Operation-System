// Функции API только для kernel space

#ifndef INCL_API_KF
#define INCL_API_KF

typedef void (*intr_handler)();

void _int_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler);

// value: 0 - включает, 1 - выключает
void _pic_update_mask(unsigned char mst_sl, unsigned char bit, unsigned char value);

void _intr_enable();

void _intr_disable();


#include "general_functions.h"

#endif

// Функции API только для kernel space

#ifndef INCL_API_KF
#define INCL_API_KF

typedef void (*intr_handler)();

void _int_reg_handler(int number, unsigned short segm_sel, unsigned short flags, intr_handler handler);


#include "general_functions.h"

#endif

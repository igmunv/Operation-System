#ifndef INCL_DRIVER_KEYBOARD
#define INCL_DRIVER_KEYBOARD

#include "../../libs/device.h"

extern void* keyboard_funcs[];
void* keyboard_get_buffer();
unsigned int keyboard_get_buffer_ptr();
unsigned char keyboard_get_shift_pressed();
unsigned char keyboard_get_ctrl_pressed();
unsigned char keyboard_get_alt_pressed();
int keyboard_init(struct dev_info* device);

#endif

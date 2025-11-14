#ifndef INCL_DRIVER_KEYBOARD
#define INCL_DRIVER_KEYBOARD

#include "../../libs/device.h"

extern void* keyboard_funcs[];
int keyboard_init(struct dev_info* device);

#endif

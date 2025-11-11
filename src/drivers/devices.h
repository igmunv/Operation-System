#ifndef INCL_DRIVER_DEVICES
#define INCL_DRIVER_DEVICES

#include "../libs/device.h"

extern struct dev_info DEVICES_INFO[256];

void devices_registration();

int devices_find();

#endif


#include "driver_list.h"
#include "../libs/device.h"
#include "../libs/driver.h"

// - - Includes drivers - -
#include "pci/pci.h"
#include "ata/ata.h"
#include "display/display.h"
#include "keyboard/keyboard.h"

// - - Driver list - -
#define DRIVER_LIST \
    X(keyboard_driver,   "keyboard/keyboard.c", VIRT_KEYBOARD_CONTROLLER, VIRT_KEYBOARD_LDEV, keyboard_init, keyboard_funcs)

#define X(name, filename, subclass, classcode, init, funcs) { #name, filename, subclass, classcode, init, funcs },

struct driver_info drivers[] = {
    DRIVER_LIST
};


#undef X

#define X(name, filename, subclass, classcode, init, funcs) +1
const unsigned int driver_count = 0 DRIVER_LIST;

#undef X

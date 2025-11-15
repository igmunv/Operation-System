
#include "driver_list.h"
#include "../libs/device.h"
#include "../libs/driver.h"

// - - Includes drivers - -
#include "ata/ata.h"
#include "display/display.h"
#include "keyboard/keyboard.h"

// - - Driver list - -
#define DRIVER_LIST \
    X(keyboard_driver,   "keyboard.c", VIRT_KEYBOARD_CONTROLLER, VIRT_KEYBOARD_LDEV, keyboard_init, keyboard_funcs) \
    X(display_driver,   "display.c", VIRT_DISPLAY_CONTROLLER, VIRT_DISPLAY_VGATEXT, display_init, display_funcs)

#define X(name, filename, classcode, subclass, init, funcs) { #name, filename, classcode, subclass, init, funcs },

struct driver_info drivers[] = {
    DRIVER_LIST
};


#undef X

#define X(name, filename, classcode, subclass, init, funcs) +1
const unsigned int driver_count = 0 DRIVER_LIST;

#undef X

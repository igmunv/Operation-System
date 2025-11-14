#include "devices.h"
#include "../libs/device.h"
#include "pci/pci.h"


struct dev_info DEVICES_INFO[256];
unsigned int DEVICE_COUNT;


void device_registration(struct dev_info* device){
    DEVICES_INFO[DEVICE_COUNT] = *device;
    DEVICE_COUNT++;
}


//виртуальные устройства
void devices_virt(){
    // дисплей vga text mode
}


void devices_legacy_find(){

    // keyboard
    struct dev_info dev_keyb;
    dev_keyb.is_pci_dev = 0;
    dev_keyb.is_virt_dev = 1;

    dev_keyb.classcode = VIRT_KEYBOARD_CONTROLLER;
    dev_keyb.subclass = VIRT_KEYBOARD_LDEV;

    device_registration(&dev_keyb);

    // display
    struct dev_info dev_display;
    dev_display.is_pci_dev = 0;
    dev_display.is_virt_dev = 1;

    dev_display.classcode = VIRT_DISPLAY_CONTROLLER;
    dev_display.subclass = VIRT_DISPLAY_VGATEXT;

    device_registration(&dev_display);


}


int devices_find(){

    unsigned int old_device_count = DEVICE_COUNT;

    devices_virt();

    devices_legacy_find();

    pci_find_devices();

    // Возвращает то, сколько нашёл устройств
    return (DEVICE_COUNT-old_device_count);
}

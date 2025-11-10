#include "devices.h"
#include "../libs/shared_memory.h"
#include "../libs/device.h"
#include "pci.h"


void devices_registration(struct dev_info* device){
    DEVICES_INFO[DEVICE_COUNT] = *device;
}


//виртуальные устройства
void devices_virt(){
    // дисплей vga text mode
}


void devices_legacy_find(){
    // keyboard
}


int devices_find(){

    unsigned int old_device_count = DEVICE_COUNT;

    devices_virt();

    devices_legacy_find();

    pci_find_devices();

    // Возвращает то, сколько нашёл устройств
    return (DEVICE_COUNT-old_device_count);
}

#include "devices.h"
#include "../libs/shared_memory.h"
#include "pci.h"

int devices_find(){

    unsigned int old_device_count = DEVICE_COUNT;

    pci_find_devices();

    // Возвращает то, сколько нашёл устройств
    return (DEVICE_COUNT-old_device_count);
}

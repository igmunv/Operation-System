
#include "drivers.h"
#include "../libs/device.h"
#include "../libs/driver.h"

#include "driver_list.h"

#define MAX_DRIVER_COUNT 32

struct driver_info DRIVERS[MAX_DRIVER_COUNT];
unsigned int DRIVER_COUNT;

// Инициализация драйверов до включения прерываний
void drivers_init(){

    // Регистрация обработчиков для прерываний
    IDT_reg_handler(32, 0x08, 0x80 | 0x0E, asm_tick_handler);
    IDT_reg_handler(33, 0x08, 0x80 | 0x0E, asm_keyboard_handler);

    // Инициализация устройств
    PIT_init(1000);

}


void drivers_find(){
    DRIVER_COUNT = driver_count;
    for(int i = 0; i < DRIVER_COUNT; i++){
        DRIVERS[i] = drivers[i];
    }
}


int driver_get(struct dev_info* device, struct driver_info* result){
    /*
    Драйвер просто инициализирует устройство, делает прерывания, и всё!
    дальше уже он просто типо ждёт:
    когда будет прерывание
    либо когда юзер-space сделает syscall в ядро, а ядро уже вызовет драйвер
    **он просто реагирует!**
    */

    for (unsigned int driver_index = 0; driver_index < DRIVER_COUNT; driver_index++){
        struct driver_info* driver = &DRIVERS[driver_index];
        if ((driver->classcode == device->classcode) && (driver->subclass == device->subclass)){
            result = driver;
            return 0;
        }
    }

    return -1;

}


void driver_manager(){

    drivers_find();

    for (unsigned int device_index = 0; device_index < DEVICE_COUNT; device_index++){

        struct driver_info driver;
        driver_get(&DEVICES_INFO[device_index], &driver);

    }

}

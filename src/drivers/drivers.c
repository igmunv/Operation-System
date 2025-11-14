
#include "drivers.h"
#include "devices.h"
#include "../libs/device.h"
#include "../libs/driver.h"

#include "driver_list.h"

#define MAX_DRIVER_COUNT 32

struct driver_info DRIVERS[MAX_DRIVER_COUNT];
unsigned int DRIVER_COUNT;


// Регистрация драйвера для конкретного устройства
void driver_registration(struct driver_info* driver, struct dev_info* device){
    device->driver = driver;
}


// Функция должна найти драйвера, и записать их в DRIVERS
void drivers_find(){

    // пока что берет просто из статического списка drivers,
    // который собирается при компиляции
    DRIVER_COUNT = driver_count;
    for(int i = 0; i < DRIVER_COUNT; i++){
        DRIVERS[i] = drivers[i];
    }

}


// получает подходящий драйвер для устройства
int driver_get(struct dev_info* device, struct driver_info* result){
    //
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

            int (*init)(struct dev_info*) = (int (*)(struct dev_info*))(driver->init);
            int init_result = init(device);

            if (init_result == 1){
                result = driver;
                return 0;
            }

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

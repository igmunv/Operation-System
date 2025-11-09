
#include "drivers.h"
#include "ata.h"
#include "../IDT_PIC.h"
#include "../libs/device.h"
#include "../libs/shared_memory.h"

// Обработчики прерываний на ASM
extern void asm_tick_handler();
extern void asm_keyboard_handler();
extern void asm_floppy_handler();

// Инициализация драйверов до включения прерываний
void drivers_init(){

    // Регистрация обработчиков для прерываний
    IDT_reg_handler(32, 0x08, 0x80 | 0x0E, asm_tick_handler);
    IDT_reg_handler(33, 0x08, 0x80 | 0x0E, asm_keyboard_handler);

    // Инициализация устройств
    PIT_init(1000);

}

// Инициализация драйверов после включения прерываний
void drivers_init_late(){

    // Проверка подключен ли диск
    if (ata_driver_find_disks() == -1){
        // Нет, то паника
        kernel_panic("drivers_init_late", "Not Found ATA Disk!");
    }
    // Если подключен то работа продолжается

    progloader_init();
}


struct driver_info driver_get(struct dev_info* device){
    /*

    Драйвер просто инициализирует устройство, делает прерывания, и всё!
    дальше уже он просто типо ждёт:
    когда будет прерывание
    либо когда юзер-space сделает syscall в ядро, а ядро уже вызовет драйвер
    **он просто реагирует!**

    Здесь должен быть цикл который проходит по всем драйверам на диске
    и ищет подходящий, но пока что этого нет

    for ()
        if equal:
            ret driver
    ret 0; // not found

    */

    if (device->classcode == STORAGE_CONTROLLER){
        if (device->subclass == STORAGE_ATA_CONTROLLER){

        }
    }

}


void driver_manager(){

    for (unsigned int device_index = 0; device_index < DEVICE_COUNT; device_index++){

        struct driver_info driver = driver_get(&DEVICES_INFO[device_index]);

    }

}

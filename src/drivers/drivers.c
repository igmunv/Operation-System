
#include "drivers.h"
#include "ata.h"
#include "../IDT_PIC.h"

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

    // . Здесь должен быть поиск всех устройств по PCI
    //   а уже потом их инициализация если устройство определённого типа есть

    // Ищем диск и добавляем в устройства
    ata_driver_find_master_disks();


    fs_make(0);
    fs_mount(0);



    progloader_init();
}

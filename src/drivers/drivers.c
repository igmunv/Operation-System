
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

    // Проверка подключен ли диск
    if (ata_driver_find_disks() == -1){
        // Нет, то паника
        kernel_panic("drivers_init_late", "Not Found ATA Disk!");
    }
    // Если подключен то работа продолжается

    progloader_init();
}

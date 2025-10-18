#include "memory.h"
#include "libs/programs.h"
#include "drivers/device.h"

//
// Shared memory
//

// Программа
volatile int execute_program __attribute__((section(".os_data")));

// Буфер клавиатуры и указатель-счётчик буфера
volatile unsigned char keyboard_buffer[KEYBOARD_BUFFER_SIZE] __attribute__((section(".os_data")));
volatile unsigned char keyboard_buffer_ptr __attribute__((section(".os_data")));

// Флаги специальных клавиш
volatile char keyboard_shift_pressed __attribute__((section(".os_data")));
volatile char keyboard_ctrl_pressed __attribute__((section(".os_data")));
volatile char keyboard_alt_pressed __attribute__((section(".os_data")));

// Координаты курсора
volatile unsigned short display_cursor_pos_x __attribute__((section(".os_data")));
volatile unsigned short display_cursor_pos_y __attribute__((section(".os_data")));

// Количество тиков с момента запуска
volatile unsigned long ticks __attribute__((section(".os_data")));

// Программы
volatile struct program_info progloader_programs[MAX_PROGRAM_COUNT] __attribute__((section(".os_data")));

// Количество программ
volatile int progloader_program_count __attribute__((section(".os_data")));

// Устройства
volatile unsigned int dev_count __attribute__((section(".os_data")));
volatile struct dev_info devinfo[MAX_DEVICE_COUNT] __attribute__((section(".os_data")));




void shared_memory_init(){
    execute_program = 0;

    for (int i = 0; i < KEYBOARD_BUFFER_SIZE; i++){
        keyboard_buffer[i] = 0;
    }

    keyboard_buffer_ptr = 0;
    keyboard_shift_pressed = 0;
    keyboard_ctrl_pressed = 0;
    keyboard_alt_pressed = 0;

    display_cursor_pos_x = 0;
    display_cursor_pos_y = 0;

    ticks = 0;

    // Программы
    struct program_info program_info_null;
    for (int i = 0; i < 20; i++)
        program_info_null.name[i] = 0;
    struct header_info header_info_null;
    header_info_null.sector = 0;
    header_info_null.byte_index = 0;
    program_info_null.shi = header_info_null;
    program_info_null.ehi = header_info_null;

    for (int i = 0; i < MAX_PROGRAM_COUNT; i++){
        progloader_programs[i] = program_info_null;
    }

    progloader_program_count = 0;

    // Устройства
    dev_count = 0;

}

#include "api.h"
#include "../drivers/ata.h"
#include "../libs/shared_memory.h"

// Обработчик API прерывания дисплея
void api_display_handler(){

    unsigned char command_type = 0;
    unsigned char symbol = 0;
    unsigned short x = 0;
    unsigned short y = 0;
    unsigned char font_color = 0;
    unsigned char background_color = 0;
    short offset = 0;

    command_type = get_ah();

    // Print symbol
    if (command_type == 0){
        symbol = get_bl();
        x = get_dx();
        y = get_si();
        font_color = get_bh();
        background_color = get_cl();
        display_print_symbol(symbol, x, y, font_color, background_color);
    }

    // New line
    else if (command_type == 1){
        display_new_line();
    }

    // Cursor update
    else if (command_type == 2){
        display_cursor_update();
    }

    // Display clear
    else if (command_type == 3){
        display_clear();
    }

    // Get current symbol
    else if (command_type == 4){
        offset = get_cx();
        unsigned char* result = get_ebx();
        *result = display_get_current_symbol(offset);
    }

    // Delete current symbol
    else if (command_type == 5){
        offset = get_bx();
        display_delete_current_symbol(offset);
    }

    outb(0x20, 0x20);
}

// Обработчик API прерывания ATA диска
void api_ata_handler(){
    unsigned char command_type = 0;
    command_type = get_ah();

    if (command_type == 0){
        unsigned int lba = get_ebx();
        unsigned char* result = get_edx();
        ata_driver_read_sector(lba, result);
    }

    outb(0x20, 0x20);
}

// Обработчик API прерывания запуска программы
void api_execute_handler(){
    EXECUTE_PROGRAM = get_ebx();
    outb(0x20, 0x20);
}

struct syscall_result {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
};

void sys_print_text(){

}

void sys_new_line(){

}

void api_handler(){

    unsigned int syscall_number = get_eax();

    struct syscall_result r;

    switch(syscall_number){
        case 0x0:
            sys_print_text();
            break;
        case 0x1:
            sys_new_line();
            break;
    }

    outb(0x20, 0x20);

    __asm__ volatile(
        "movl %0, %%eax\n"
        "movl %1, %%ebx\n"
        "movl %2, %%ecx\n"
        "movl %3, %%edx\n"
        :
        : "r"(r.eax), "r"(r.ebx), "r"(r.ecx), "r"(r.edx)
        : "eax", "ebx", "ecx", "edx"
    );

}

// Регистрация API прерываний
void api_registration_functions(){
    // Не забывай: IRQ всегда делает только маленькую и быструю работу
    IDT_reg_handler(0x22, 0x08, 0x80 | 0x0E, api_asm_handler);
}


// Инициализация API
void api_init(){
    api_registration_functions();
}
